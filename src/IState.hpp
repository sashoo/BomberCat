#ifndef   ISTATE_HPP
#define   ISTATE_HPP
 
#include "GEvent.hpp"
#include "MirageApp.hpp"

class MirageApp;

class IState : public GEvent {
public:
  IState();
  virtual void Activate() = 0;
  virtual void Deactivate() = 0;
  virtual void Loop() = 0;
  virtual void Render(SDL_Surface* SurfDisplay) = 0;
protected:
   MirageApp* App;
};

#endif
