#ifndef STATECREDITS_HPP
#define STATECREDITS_HPP

#include "IState.hpp"
#include <SDL_ttf.h>

class StateCredits : public IState {
private:
  StateCredits();
  static StateCredits Instance;
  //TTF_Font*           Font;
  SDL_Surface*        Message;
  SDL_Surface*        Who;
  SDL_Surface*        Who2;
  SDL_Surface*        Orig;
  SDL_Surface*        Net;
  
  SDL_Surface*        Site;
  Uint32              OldTime;

public:
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode);  
  void OnLButtonDown(int mX, int mY);
  void OnActivate();
  void OnDeactivate();
  void OnLoop();
  void OnRender(SDL_Surface* SurfDisplay);
  static StateCredits* GetInstance();
};
  

#endif
