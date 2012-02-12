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
  TTF_Font* GetFont();
  std::ofstream Log;
  //StateManager mStateManager;  

  void SetDefaultKeys();

private:
  bool            Running;
  TTF_Font*       Font;

  SDL_Surface*    SurfDisplay;
  std::string     LogFile; 
  
};
 
#endif
