#include "MirageApp.hpp"
#include <SDL_ttf.h>
#include <stdio.h>
#define FPS 60
Uint32 wait = 1000.0f/FPS;
Uint32 framestart = 0;
Sint32 delay;

int main(int argc, char* argv[]) {
  MirageApp theApp;  
  int n, l;
  if (argc > 0) 
    theApp.SetTerminal(true);
  
  for (n = 1; n < argc; n++) {
    switch ((int)argv[n][0]) {
    case '-': {
      l = strlen(argv[n]);         
     
      if (l > 2) {
	puts( "Illegal syntax: too many characters for a key" );
	exit( 1 );
      }

      char ch = argv[n][1];
      switch (ch) {
      case 'g': {
	if( n + 1 >= argc ) {
	  puts( "Illegal syntax: no string provided" );
	  exit( 1 );
	}
	else {	 
	  //printf("test");
	  char par [256];
	  strcpy( par, argv[n+1] );
	  //printf ("your parameter is: %s", par);
	  if (0 == strcmp (par, "local")) 
	    theApp.SetLaunchState(APPSTATE_GAME, 0);
	}      
	break;  
      }
      case 'k': {
	if( n + 1 >= argc ) {
	  puts( "Illegal syntax: no value provided for kots");
	  exit( 1 );
	}
	else {	 
	  //printf("test");
	  char par [256];
	  strcpy( par, argv[n+1] );
	  long int k = atol(par);
	  if (k <= 0 || k > 9) {
	    puts("wrong number of kots");
	    exit(1);
	  }
	  int kots = (int)k;
	  
	  theApp.SetNumBombers(kots);
	}      
	break;  
      }
      case 'b': {
	if( n + 1 >= argc ) {
	  puts( "Illegal syntax: no value provided for bots");
	  exit( 1 );
	}
	else {	 
	  //printf("test");
	  char par [256];
	  strcpy( par, argv[n+1] );
	  long int b = atol(par);
	  if (b < 0 || b > 9) {
	    puts("wrong number of bots");
	    exit(1);
	  }
	  int bots = (int)b;
	  
	  theApp.SetNumBots(bots);
	}      
	break;  
      }

      default:
	printf("No such a key: \'%s\'\n", argv[n] );
	exit(1);
	break;	
      
      }      
      break;
    }
      
    default:       
      break;      
    
    }
  }
  
  return theApp.OnExecute();
}
 
MirageApp::MirageApp() {
  LogFile.assign("log.txt");
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
  Font = TTF_OpenFont("Resources/font.ttf", 18 );
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

TTF_Font* MirageApp::GetFont() {
  return Font;
}

void MirageApp::SetDefaultKeys() {
  Keys["up"] = SDLK_UP;
  Keys["down"] = SDLK_DOWN;
  Keys["left"] = SDLK_LEFT;
  Keys["right"] = SDLK_RIGHT;     
}
