#ifndef   ISTATE_HPP
#define   ISTATE_HPP
 
#include "GEvent.hpp"
#include "MirageApp.hpp"

class MirageApp;

class IState : public GEvent {
public:
  IState();
  virtual void OnActivate() = 0;
  virtual void OnDeactivate() = 0;
  virtual void OnLoop() = 0;
  virtual void OnRender(SDL_Surface* SurfDisplay) = 0;
protected:
   MirageApp* App;
};

#endif
