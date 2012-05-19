#ifndef MIRAGEAPP_HPP
#define MIRAGEAPP_HPP
 
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <fstream>
#include <map>

#include "Define.hpp"

#include "StateManager.hpp"

#include "GInput.hpp"
#include "GFPS.hpp"
#include "GEvent.hpp"
#include "GSurface.hpp"
#include "Srand.hpp"
#include "MenuTable.hpp"
 
enum NetMode {
  GAME_LOCAL = 0,
  GAME_SERVER,
  GAME_CLIENT
};

class MirageApp : public GEvent  { 
public: 
  std::map<std::string, int> Keys;
  SDL_Joystick *Stick; 
  std::vector<KeyMap> BomberMap;
  std::vector<Input*> devs;
  MirageApp(); 
  ~MirageApp();
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
  void SetConnectionMap(std::vector<KeyMap>& bomberMap);
  int GetLaunchState() const;
  int GetLaunchAttr() const;
  int GetNumBombers() const;
  int GetNumBots() const;
  Input* dev(int num);
  
  //Counts time since SDL was initialized, milliseconds
  Uint32 GetTimeReal() const {
    return SDL_GetTicks();
  }
  
  //TTF_Font* GetFont();
  std::ostream & Log;
  //StateManager mStateManager;  

  KeyInput Key1;
  KeyInput Key2;
  KeyInput Key3;
  KeyInput Key4;
  JoyInput Joy1;
  JoyInput Joy2;
  JoyInput Joy3;
  JoyInput Joy4;  

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
  
  Uint32 TimeReal;
  
};
 
#endif
