#ifndef STATEOPTIONS_HPP
#define STATECREDITS_HPP

#include "IState.hpp"
#include <SDL_ttf.h>

class StateOptions : public IState {
private: 
  StateCredits();
  static StateCredits Instance;
  TTF_Font*           Font;
  Uint32              OldTime;

public:
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode);  
  void OnLButtonDown(int mX, int mY);
  void OnActivate();
  void OnDeactivate();
  void OnLoop();
  void OnRender(SDL_Surface* SurfDisplay);
  static StateOptions* GetInstance();
};

#endif
