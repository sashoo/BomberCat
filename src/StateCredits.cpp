#include "StateCredits.hpp"
#include "StateManager.hpp"
#include "GSurface.hpp"

StateCredits StateCredits::Instance;

StateCredits::StateCredits() {  
  
}

void StateCredits::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode){  
  if (OldTime + 250 > SDL_GetTicks()) {
    return;
  }
  
  OldTime = SDL_GetTicks();
  StateManager::SetActiveState(APPSTATE_MENU);  
}

void StateCredits::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode){
}

void StateCredits::OnLButtonDown(int mX, int mY){
  StateManager::SetActiveState(APPSTATE_MENU);  
}

void StateCredits::OnActivate() {
  OldTime = SDL_GetTicks();
  SDL_Color white;
  white.r = 255;
  white.g = 255;
  white.b = 255;
  SDL_Color color;
  //color = {30, 140, 230};
  color.r = 30;
  color.g = 140;
  color.b = 230;  
 
  Message = TTF_RenderText_Solid(GSurface::FontRegular, "Programmers:", white);
  Who = TTF_RenderText_Solid(GSurface::FontRegular, "Alexander Paramonov", color);
  Who2 = TTF_RenderText_Solid(GSurface::FontRegular, "WGH", color);
  Orig = TTF_RenderText_Solid(GSurface::FontRegular, "Graphics:", white);
  Net = TTF_RenderText_Solid(GSurface::FontRegular, "Networking:", white);
  
  //Who2 = TTF_RenderText_Solid(GSurface::FontRegular, "Alexander Paramonov", color);

  Site  = TTF_RenderText_Solid(GSurface::FontRegular, "www.sashoo.org", color);
  //SurfLogo = GSurface::OnLoad("Resources/bots.png");
  //StartTime = SDL_GetTicks();
}

void StateCredits::OnDeactivate() {
  
  if (Message) {
    SDL_FreeSurface(Message);
    Message = NULL;    
  }
  if (Who) {
    SDL_FreeSurface(Who);
    Who = NULL;    
  }

  if (Net) {
    SDL_FreeSurface(Net);
    Net = NULL;
  }

  if (Orig) {
    SDL_FreeSurface(Orig);
    Orig = NULL;    
  }
  
  if (Site) {
    SDL_FreeSurface(Site);
    Site = NULL;    
  }
}

void StateCredits::OnLoop() {
  // if (OldTime + 150 < SDL_GetTicks()) {
    
  // } 
  
}

void StateCredits::OnRender(SDL_Surface* SurfDisplay) {
  if (Message) 
    GSurface::OnDraw(SurfDisplay, Message, 20, 20);
  if (Who) {
    GSurface::OnDraw(SurfDisplay, Who, 30, 40);
    GSurface::OnDraw(SurfDisplay, Who, 30, 160);
  }
  if (Who2) {
    GSurface::OnDraw(SurfDisplay, Who2, 30, 60);
    GSurface::OnDraw(SurfDisplay, Who2, 30, 110);
  }

  if (Net) 
    GSurface::OnDraw(SurfDisplay, Net, 20, 90); 

  if (Orig) 
    GSurface::OnDraw(SurfDisplay, Orig, 20, 140); 
    
  if (Site) 
    GSurface::OnDraw(SurfDisplay, Site, 100, 200);
  
}

StateCredits* StateCredits::GetInstance() {
  return &Instance;
}
