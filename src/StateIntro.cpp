#include "StateIntro.hpp"
#include "StateManager.hpp"
#include "GSurface.hpp"

StateIntro StateIntro::Instance;

StateIntro::StateIntro() {
  SurfLogo = NULL;
}

void StateIntro::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode){
  StateManager::SetActiveState(APPSTATE_MENU);
}

void StateIntro::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode){
}

void StateIntro::OnLButtonDown(int mX, int mY){
  StateManager::SetActiveState(APPSTATE_MENU);  
}

void StateIntro::OnActivate() {
  SurfLogo = GSurface::OnLoad((char*)"Resources/bots.png");
  StartTime = SDL_GetTicks();
}

void StateIntro::OnDeactivate() {
  if (SurfLogo) {
    SDL_FreeSurface(SurfLogo);
    SurfLogo = NULL;    
  }
}

void StateIntro::OnLoop() {
  if (StartTime + 1500 < SDL_GetTicks()) {
    StateManager::SetActiveState(APPSTATE_MENU);
  }
}

void StateIntro::OnRender(SDL_Surface* SurfDisplay) {
  if (SurfLogo) {
    GSurface::OnDraw(SurfDisplay, SurfLogo, 0, 0);
  }
}

StateIntro* StateIntro::GetInstance() {
  return &Instance;
}
