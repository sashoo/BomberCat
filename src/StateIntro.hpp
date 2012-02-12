#ifndef STATEINTRO_HPP
#define STATEINTRO_HPP

#include "IState.hpp"
class CSurface;

class StateIntro : public IState {
private:
  StateIntro();
  SDL_Surface* SurfLogo;
  int StartTime;
  static StateIntro Instance;
  
public:
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode);  
  void OnLButtonDown(int mX, int mY);
  void OnActivate();
  void OnDeactivate();
  void OnLoop();
  void OnRender(SDL_Surface* SurfDisplay);
  static StateIntro* GetInstance();
};

#endif
