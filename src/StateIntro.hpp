#ifndef STATEINTRO_HPP
#define STATEINTRO_HPP

#include "IState.hpp"
class CSurface;

class StateIntro : public IState {
private:
  StateIntro();
  SDL_Surface* SurfLogo;
  Uint32 StartTime;
  static StateIntro Instance;
  
public:  
  // Core functions
  void Activate();
  void Deactivate();
  void Loop();
  void Render(SDL_Surface* SurfDisplay);

  // Input handling
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode);  
  void OnLButtonDown(int mX, int mY);

  // Return state instance
  static StateIntro* GetInstance();
};

#endif
