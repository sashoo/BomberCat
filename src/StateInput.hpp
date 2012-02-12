#ifndef STATEINOUT_HPP
#define STATEINPUT_HPP

#include "IState.hpp"
#include "MenuManager.hpp"

class MirageApp;
class MenuManager;

class StateInput : public IState {
private: 
  StateInput();
  static StateInput   Instance;
  MirageApp*          App;
  MenuManager*        mMenuManager;  
  Uint32              OldTime;

public:
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode);  
  void OnLButtonDown(int mX, int mY);
  //void OnLButtonUp(int mX, int mY); 
  void OnRButtonDown(int mX, int mY); 
  //void OnRButtonUp(int mX, int mY); 
  void OnMButtonDown(int mX, int mY); 
  //void OnMButtonUp(int mX, int mY);
  void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
  void OnActivate();
  void OnDeactivate();
  void OnLoop();
  void OnRender(SDL_Surface* SurfDisplay);

  static StateInput* GetInstance();
};

#endif