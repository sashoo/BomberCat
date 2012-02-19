#ifndef MIRAGEAPP_HPP
#define MIRAGEAPP_HPP
 
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <fstream>
#include <map>

#include "Define.hpp"

#include "StateManager.hpp"

#include "GFPS.hpp"
#include "GEvent.hpp"
#include "GSurface.hpp"
#include "Srand.hpp"
 
enum NetMode {
  GAME_LOCAL = 0,
  GAME_SERVER,
  GAME_CLIENT
};

class MirageApp : public GEvent  { 
public: 
  std::map<std::string, int> Keys;
  SDL_Joystick *Stick; 
  MirageApp(); 
  int OnExecute(); 

  bool OnInit(); 
  void OnEvent(SDL_Event* Event); 
    void OnExit();
  //void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
  //void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
  void OnLoop(); 
  void OnRender(); 
  void OnCleanup();  
  void SetLaunchState(int state, int attr);
  void SetTerminal(bool terminal);
  void SetNumBombers(int bombers);
  void SetNumBots(int bots);
  int GetLaunchState() const;
  int GetLaunchAttr() const;
  int GetNumBombers() const;
  int GetNumBots() const;
  //TTF_Font* GetFont();
  std::ofstream Log;
  //StateManager mStateManager;  

  void SetDefaultKeys();
  
  // networking
  const char *Host, *Port;
  enum NetMode NetMode;

private:
  bool            Running;
  //TTF_Font*       Font;

  SDL_Surface*    SurfDisplay;
  std::string     LogFile; 
  bool Terminal;
  int LaunchState;
  int LaunchAttr;
  int Bombers;
  int Bots;
  
};
 
#endif
