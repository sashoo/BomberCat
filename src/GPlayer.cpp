#include "GPlayer.hpp"

int GPlayer::Players = 0;

GPlayer::GPlayer() {
  PlayerID = Players++;
  Type = ENTITY_TYPE_BOMBER_P;
  OldTime = 0;
}

GPlayer::~GPlayer() {
  Players--;
  App->Log << "Player Deleted!" << std::endl;
}

bool GPlayer::OnLoad() {   
  SetDefaultKeys();
  return GBomber::OnLoad();
}

void GPlayer::OnLoop() {
  GBomber::OnLoop();
}

void GPlayer::OnRender(SDL_Surface* SurfDisplay) {
  GBomber::OnRender(SurfDisplay);  
}

void GPlayer::OnCleanup() {
  GBomber::OnCleanup();
}

void GPlayer::OnAnimate() {
  GBomber::OnAnimate();
}

bool GPlayer::OnCollision(GEntity* Entity){
  //  Jump();
  return true; 
}

void GPlayer::SetDefaultKeys() {
 //  if (PlayerID == 0) {
 //    Keys["up"] = SDLK_UP;
 //    Keys["down"] = SDLK_DOWN;
 //    Keys["left"] = SDLK_LEFT;
 //    Keys["right"] = SDLK_RIGHT;   
 //    Keys["bomb"] = SDLK_n;
 //  }
 // if (PlayerID == 1) {
 //    Keys["up"] = SDLK_w;
 //    Keys["down"] = SDLK_s;
 //    Keys["left"] = SDLK_a;
 //    Keys["right"] = SDLK_d;   
 //    Keys["bomb"] = SDLK_e;
 //  }
}

void GPlayer::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode) {
  // if(sym == Keys["up"]) 
  //   MoveUp = true;          

  // if(sym == Keys["down"]) 
  //   MoveDown = true;    
  

  // if(sym == Keys["left"]) 
  //   MoveLeft = true;    
  

  // if(sym == Keys["right"]) 
  //   MoveRight = true;    

  // if (sym == Keys["bomb"])  {
  //   if (!(OldTime + 100 > SDL_GetTicks())) {

  //     OldTime = SDL_GetTicks();
  //     PlaceBomb();
  //   }    
  // }
      
}
void GPlayer::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode) {
  // if(sym == Keys["left"]) 
  //   MoveLeft = false;      

  // if(sym == Keys["right"]) 
  //   MoveRight = false;   

  // if(sym == Keys["up"]) 
  //   MoveUp = false;   

  // if(sym == Keys["down"]) 
  //   MoveDown = false;    
}
void GPlayer::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value) {
}
void GPlayer::OnJoyHat(Uint8 which, Uint8 hat, Uint8 value) {
  
}
void GPlayer::OnJoyButtonDown(Uint8 which, Uint8 button) {
}
