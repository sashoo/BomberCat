#ifndef STATEOPTIONS_HPP
#define STATECREDITS_HPP

#include "IState.hpp"
#include "MenuManager.hpp"

class MirageApp;
class MenuManager;

class StateOptions : public IState {
private: 
  StateOptions();
  // instance of the current state
  static StateOptions Instance; 
  MirageApp*          App;      
  MenuManager*        mMenuManager;  
  Uint32              OldTime;

public:
  // [de]activates state
  void Activate();
  void Deactivate();
  
  // Core functions
  void Loop();
  void Render(SDL_Surface* SurfDisplay);

  // Input handling
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode);  
  void OnLButtonDown(int mX, int mY);  
  void OnRButtonDown(int mX, int mY);   
  void OnMButtonDown(int mX, int mY);  
  void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
  

  static StateOptions* GetInstance();
};

#endif
