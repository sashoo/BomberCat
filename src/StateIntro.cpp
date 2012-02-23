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

void StateIntro::Activate() {
  SurfLogo = GSurface::Load("Resources/bots.png");
  StartTime = SDL_GetTicks();
}

void StateIntro::Deactivate() {
  if (SurfLogo) {
    SDL_FreeSurface(SurfLogo);
    SurfLogo = NULL;    
  }
}

void StateIntro::Loop() {
  if (StartTime + 1500 < SDL_GetTicks()) {
    StateManager::SetActiveState(APPSTATE_MENU);
  }
}

void StateIntro::Render(SDL_Surface* SurfDisplay) {
  if (SurfLogo) {
    GSurface::Draw(SurfDisplay, SurfLogo, 0, 0);
  }
}

StateIntro* StateIntro::GetInstance() {
  return &Instance;
}
