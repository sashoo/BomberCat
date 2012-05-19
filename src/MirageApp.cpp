#include <stdio.h>
#include <iostream>

#include <SDL_ttf.h>
#include "MirageApp.hpp"
#include "GBomber.hpp"

#define FPS 60
Uint32 wait = 1000.0f/FPS;
Uint32 framestart = 0;
Sint32 delay;

void print_usage(void)
{
  fprintf(stderr,  
    "Usage:\n"
    "\trobokot [-k kots] [-b bots] [-g gametype]\n"
    "\n"
    " -k kots\t\tset number of players (1-9)\n"
    " -b bots\t\tset number of bots (1-9)\n"
    " -g gametype\t\tset game mode, can be \"local\", \"client\" or \"server\"\n"
    " -h hostname\t\thostname to listen on or connect to\n"
    " -p port\t\tport\n"
  );
}

int main(int argc, char* argv[]) {
  MirageApp theApp;  

  if (argc > 0) 
    theApp.SetTerminal(true);
  
  for (int i = 1; i < argc; i++) {
    switch (argv[i][0]) {
    case '-': {
      if (strlen(argv[i]) > 2) {
        fputs("Illegal syntax: too many characters for a key\n", stderr);
        print_usage();
        exit(1);
      }

      switch (argv[i][1]) {
      case 'g': {
        i++;
        if (i >= argc) {
          fputs("Option -g requires an argument\n", stderr);
          print_usage();
          exit(1);
        }
        else {
          const char *net_type = argv[i];

          if (strcmp(net_type, "local") == 0) { 
            // it defaults to local anyway, though
            theApp.NetMode = GAME_LOCAL;
          } else if (strcmp(net_type, "server") == 0) {
            theApp.NetMode = GAME_SERVER;
          } else if (strcmp(net_type, "client") == 0) {
            theApp.NetMode = GAME_CLIENT;
          } else {
            fputs("Invalid argument for option -g\n", stderr);
            print_usage();
            exit(1);
          }
          theApp.SetLaunchState(APPSTATE_GAME, 0);
        }      
        break;
      }
      case 'k': {
        i++;
        if (i  >= argc) {
          fputs("Option -k requires an argument\n", stderr);
          print_usage();
          exit(1);
        } else {         
          int kots;

          if (sscanf(argv[i], "%d", &kots) != 1 || kots < 1 || kots > 9) {
            fputs("Invalid argument for option -k\n", stderr);
            print_usage();
            exit(1);
          }
          
          theApp.SetNumBombers(kots);
        }      
        break;  
      }
      case 'b': {
        i++;
        if (i >= argc) {
          fputs("Option -b requires an argument\n", stderr);
          print_usage();
          exit(1);
          
        } else {         
          int bots;
          if (sscanf(argv[i], "%d", &bots) != 1 || bots < 1 || bots > 9) {
            fputs("Invalid argument for option -b\n", stderr);
            print_usage();
            exit(1);
          }
          
          theApp.SetNumBots(bots);
        }      
        break;  
      }
      case 'p': {
        i++;
        if (i >= argc) {
          fputs("Option -p requires an argument\n", stderr);
          print_usage();
          exit(1);
        } else {
          theApp.Port = argv[i];
        }
        break;
      }

      case 'h': {
        i++;
        if (i >= argc) {
          fputs("Option -h requires an argument\n", stderr);
          print_usage();
          exit(1);
        } else {
          theApp.Host = argv[i];
        }
        break;
      }
      default:
        fprintf(stderr, "Invalid option '%s'\n", argv[i]);
        print_usage();
        exit(1);
        break;        
      
      }      
      break;
    } // case '-'
      
    default:
      fprintf(stderr, "Unexpected argument '%s'\n", argv[i]);
      print_usage();
      exit(1);
      break;      
    
    }
  }
  
  return theApp.OnExecute();
}
 
MirageApp::MirageApp()
:
    //Log(*new std::ofstream("log.txt"))    
    Log(std::cerr)
{
  //LogFile.assign("log.txt");
  //LogFile.assign("/dev/stderr");
  //Log.open(LogFile.c_str());
  //Log << "LogFile: " << LogFile << std::endl;
  Log << "MirageApp:MirageApp() constructor called" << std::endl; 
  SurfDisplay = NULL; 
  Running = true;
  Stick = NULL;
  SetDefaultKeys();
  Srand::SetTimeSeed();
  LaunchState = APPSTATE_INTRO;
  LaunchAttr = 0;
  Terminal = false;
  Bombers = 1;
  Bots = 0;

  Host = "0.0.0.0";
  Port = "8123";
  NetMode = GAME_LOCAL;  
}

MirageApp::~MirageApp()
{
    //delete &Log;
}

void MirageApp::SetLaunchState(int state, int attr) {
  if (state > 0 && state < APPSTATE_MAX)
    LaunchState = state;
  LaunchAttr = attr;
}

int MirageApp::GetLaunchState() const {
  return LaunchState;
}

int MirageApp::GetLaunchAttr() const {
  return LaunchAttr;
}

int MirageApp::GetNumBombers() const {
  return Bombers;
}

void MirageApp::SetNumBombers(int bombers) {
  Bombers = bombers;
}

void MirageApp::SetNumBots(int bots) {
  Bots = bots;
}

void MirageApp::SetConnectionMap(std::vector<KeyMap>& bomberMap){
  BomberMap = bomberMap;
}


int MirageApp::GetNumBots() const {
  return Bots;
}

void MirageApp::SetTerminal(bool terminal) {
  Terminal = terminal;
}

int MirageApp::OnExecute() {
  if (OnInit() == false)
    return -1;

  SDL_Event Event;
  
  while (Running) {
    while (SDL_PollEvent(&Event)) {
      OnEvent(&Event);
    }    
    OnLoop();
    OnRender();
    delay = wait -(SDL_GetTicks() -framestart);
    if (delay > 0)
      SDL_Delay((Uint32)delay);
    framestart = SDL_GetTicks();
  }
  
  OnCleanup();  
  return 0;
}

bool MirageApp::OnInit() {
  Log << "----------------------------------------" << std::endl;
  Log << "Calling MirageApp::OnInit()" << std::endl;
  
  Log << "Trying to init SDL... ";
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    Log << "Failed.\nExiting the program" << std::endl;
    return false;
  }
  Log << "Success!" << std::endl;  

  Log << "Initializing video mode... ";
  if ((SurfDisplay = SDL_SetVideoMode(GWIDTH, GHEIGHT, 32, /*SDL_FULLSCREEN | */SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    Log << "Failed.\nExiting the program" << std::endl;
    return false;
  }
  Log << "Success!" << std::endl;
  Log << "----------------------------------------" << std::endl;
  //Check if there's any joysticks 
  Log << "Searching for joysticks... ";
  int numjoysticks = SDL_NumJoysticks();
  if( numjoysticks < 1 ) { 
    Log << "No joysticks found" << std::endl;    
  }
  else {    
    Log << numjoysticks << " joysticks found" << std::endl;    
    for (int i = 0; i < numjoysticks; i++) {
      Log << "****************************************" << std::endl;      
      Log << "Joy " << i << ": " << SDL_JoystickName(i) << std::endl;
      Stick = SDL_JoystickOpen(i);
      Log << "Has " << SDL_JoystickNumAxes(Stick) << " axes" << std::endl;
      Log << "Has " << SDL_JoystickNumHats(Stick) << " hats" << std::endl;
      Log << "Has " << SDL_JoystickNumButtons(Stick) << " buttons" << std::endl;
      Log << "Has " << SDL_JoystickNumBalls(Stick) << " balls" << std::endl;            
      //SDL_JoystickClose(Stick);
    }
    Log << "****************************************" << std::endl;      
    //Stick = SDL_JoystickOpen( 1 );
  }
    

  Log << "Initializing SDL_TTF... ";
  if( TTF_Init() == -1 ) { 
    Log << "Failed.\nExiting the program" << std::endl;
    return false; 
  }
  Log << "Success" << std::endl;

  Log << "Loading font.ttf... ";
  if (!GSurface::LoadFontRegular()) {
    Log << "Failed.\nExiting the program" << std::endl;
    return false;
  }
  Log << "Success!" << std::endl;  
  
  SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 2);
  StateManager::RegisterApp(this);
  StateManager::SetActiveState(LaunchState);
 
  Log << "MirageApp::Init() completed successfully" << std::endl;    

  Key1.kUp    = SDLK_w;
  Key1.kDown  = SDLK_s;
  Key1.kLeft  = SDLK_a;
  Key1.kRight = SDLK_d;
  Key1.kBomb  = SDLK_e;

  Key2.kUp    = SDLK_i;
  Key2.kDown  = SDLK_k;
  Key2.kLeft  = SDLK_j;
  Key2.kRight = SDLK_l;
  Key2.kBomb  = SDLK_o;

  Key3.kUp    = SDLK_KP8;
  Key3.kDown  = SDLK_KP5;
  Key3.kLeft  = SDLK_KP4;
  Key3.kRight = SDLK_KP6;
  Key3.kBomb  = SDLK_KP9;

  Key4.kUp    = SDLK_UP;
  Key4.kDown  = SDLK_DOWN;
  Key4.kLeft  = SDLK_LEFT;
  Key4.kRight = SDLK_RIGHT;
  Key4.kBomb  = SDLK_SLASH;

  //Key1.Bomber->InputHandle = &Key1;

  Joy1.jUp.jEntity = JOY_AXIS;
  Joy1.jUp.Number = 1;
  Joy1.jUp.Value = -1;
  Joy1.Which = 0;

  Joy1.jDown.jEntity = JOY_AXIS;
  Joy1.jDown.Number = 1;
  Joy1.jDown.Value = 1;

  Joy1.jRight.jEntity = JOY_AXIS;
  Joy1.jRight.Number = 0;
  Joy1.jRight.Value = +1;

  Joy1.jLeft.jEntity = JOY_AXIS;
  Joy1.jLeft.Number = 0;
  Joy1.jLeft.Value = -1;

  Joy1.jBomb.jEntity = JOY_BUTTON;
  Joy1.jBomb.Number = 1;
  Joy1.jBomb.Value = 0;

  Joy2.Which = 1;
  Joy2.jUp.jEntity = JOY_AXIS;
  Joy2.jUp.Number = 1;
  Joy2.jUp.Value = -1;

  Joy2.jDown.jEntity = JOY_AXIS;
  Joy2.jDown.Number = 1;
  Joy2.jDown.Value = 1;

  Joy2.jRight.jEntity = JOY_AXIS;
  Joy2.jRight.Number = 0;
  Joy2.jRight.Value = +1;

  Joy2.jLeft.jEntity = JOY_AXIS;
  Joy2.jLeft.Number = 0;
  Joy2.jLeft.Value = -1;

  Joy2.jBomb.jEntity = JOY_BUTTON;
  Joy2.jBomb.Number = 1;
  Joy2.jBomb.Value = 0;

  Joy3.Which = 2;
  Joy3.jUp.jEntity = JOY_AXIS;
  Joy3.jUp.Number = 1;
  Joy3.jUp.Value = -1;

  Joy3.jDown.jEntity = JOY_AXIS;
  Joy3.jDown.Number = 1;
  Joy3.jDown.Value = 1;

  Joy3.jRight.jEntity = JOY_AXIS;
  Joy3.jRight.Number = 0;
  Joy3.jRight.Value = +1;

  Joy3.jLeft.jEntity = JOY_AXIS;
  Joy3.jLeft.Number = 0;
  Joy3.jLeft.Value = -1;

  Joy3.jBomb.jEntity = JOY_BUTTON;
  Joy3.jBomb.Number = 1;
  Joy3.jBomb.Value = 0;

  Joy4.Which = 3;
  Joy4.jUp.jEntity = JOY_AXIS;
  Joy4.jUp.Number = 1;
  Joy4.jUp.Value = -1;

  Joy4.jDown.jEntity = JOY_AXIS;
  Joy4.jDown.Number = 1;
  Joy4.jDown.Value = 1;

  Joy4.jRight.jEntity = JOY_AXIS;
  Joy4.jRight.Number = 0;
  Joy4.jRight.Value = +1;

  Joy4.jLeft.jEntity = JOY_AXIS;
  Joy4.jLeft.Number = 0;
  Joy4.jLeft.Value = -1;

  Joy4.jBomb.jEntity = JOY_BUTTON;
  Joy4.jBomb.Number = 1;
  Joy4.jBomb.Value = 0;
  // Joy1.jUp.jEntity = JOY_AXIS;
  // Joy1.jUp.Number = 0;
  // Joy1.jUp.Value = 1;
  

  return true;
}

void MirageApp::OnEvent(SDL_Event* Event) {
  GEvent::OnEvent(Event);
  StateManager::OnEvent(Event);
}

void MirageApp::OnExit() {
  Running = false;
}

void MirageApp::OnLoop() {
  
  StateManager::OnLoop();
  GFPS::FPSControl.OnLoop();

  char Buffer[255];
  sprintf(Buffer, "%d", GFPS::FPSControl.GetFPS());
  SDL_WM_SetCaption(Buffer, Buffer);
}

void MirageApp::OnRender() {
  SDL_FillRect(SurfDisplay, NULL, 0);
  StateManager::OnRender(SurfDisplay);  
  SDL_Flip(SurfDisplay);
}

void MirageApp::OnCleanup() {
  //SDL_FreeSurface(Example);
  StateManager::SetActiveState(APPSTATE_NONE);
  SDL_JoystickClose(Stick);
  
  SDL_FreeSurface(SurfDisplay);
  SDL_Quit();
}

// TTF_Font* MirageApp::GetFont() {
//   return Font;
// }

void MirageApp::SetDefaultKeys() {
  Keys["up"] = SDLK_UP;
  Keys["down"] = SDLK_DOWN;
  Keys["left"] = SDLK_LEFT;
  Keys["right"] = SDLK_RIGHT;     
}

Input* MirageApp::dev(int num){
  Log << "called with num = " << num << std::endl;
  switch(num){
    case 1:
      return &Key1;
      break;
    case 2:
      return &Key2;
      break;
    case 3:
      return &Key3;
      break;
    case 4:
      return &Key4;
      break;
    case 5:
      return &Joy1;
      break;
    case 6:
      return &Joy2;
      break;
    case 7:
      return &Joy3;
      break;
    case 8:
      return &Joy4;
      break;
    case 9:
    default:
      return NULL;
      break;
  }
}
