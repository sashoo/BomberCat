#ifndef STATEGAME_HPP
#define STATEGAME_HPP

#include "IState.hpp"

#include "GArea.hpp"
#include "GCamera.hpp"
#include "GEntity.hpp"
#include "GPlayer.hpp"
#include "GAI.hpp"

class MirageApp;

class StateGame : public IState {
private:
  StateGame();  
  static StateGame Instance; 
  //CPlayer* p1;
  //CPlayer p2; 
 
  bool CameraSwitch;
  Uint32 OldTime;
public:
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode); 

  void OnLButtonDown(int mX, int mY);
  void OnRButtonDown(int mX, int mY);
  void OnMButtonDown(int mX, int mY);

  void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value); 
  void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value); 
  void OnJoyButtonDown(Uint8 which, Uint8 button);

  void OnActivate();
  void OnDeactivate();
  void OnLoop();
  void OnRender(SDL_Surface* SurfDisplay);

  int CurLayer;
  int CurTileType;
  int CurJoystick;

  static StateGame* GetInstance();
};


#endif
