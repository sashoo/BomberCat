#include "MirageApp.hpp"
#include <SDL_ttf.h>
#include <stdio.h>
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
 
MirageApp::MirageApp() {
  //LogFile.assign("log.txt");
  LogFile.assign("/dev/stderr");
  Log.open(LogFile.c_str());
  Log << "LogFile: " << LogFile << std::endl;
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
      SDL_JoystickClose(Stick);
    }
    Log << "****************************************" << std::endl;      
    Stick = SDL_JoystickOpen( 0 );
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
