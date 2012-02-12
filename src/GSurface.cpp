#include "GSurface.hpp"
#include <SDL_image.h>

SDL_Surface* GSurface::SurfBomb;
SDL_Surface* GSurface::SurfBomber;
SDL_Surface* GSurface::SurfFlame;
SDL_Surface* GSurface::SurfPowerup;
SDL_Surface* GSurface::SurfTile;

GSurface::GSurface() {

}

SDL_Surface* GSurface::OnLoad(char* filename){
  SDL_Surface* SurfTemp = NULL;
  SDL_Surface* SurfReturn = NULL;
  
  if ((SurfTemp = IMG_Load(filename)) == NULL) {
    return NULL;
  }
  
  SurfReturn = SDL_DisplayFormatAlpha(SurfTemp);
  SDL_FreeSurface(SurfTemp);
  return SurfReturn;
}

bool GSurface::OnDraw(SDL_Surface* SurfDest, 
			 SDL_Surface* SurfSrc, 
			 int x, int y) {
  if (SurfDest == NULL || SurfSrc == NULL) {
    return false;
  }

  SDL_Rect DestR;
  
  DestR.x = x;
  DestR.y = y;
  
  SDL_BlitSurface(SurfSrc, NULL, SurfDest, &DestR);
  return true;
}

bool GSurface::OnDraw(SDL_Surface* SurfDest, SDL_Surface* SurfSrc, 
		      int x, int y, int x2, int y2, int w, int h) {
  if (SurfDest == NULL || SurfSrc == NULL) {
    return false;
  }

  SDL_Rect DestR;
  
  DestR.x = x;
  DestR.y = y;

  SDL_Rect SrcR;
  SrcR.x = x2;
  SrcR.y = y2;
  SrcR.w = w;
  SrcR.h = h;

  SDL_BlitSurface(SurfSrc, &SrcR, SurfDest, &DestR);
  return true;  
}

// SDL_Surface* SDL_ScaleSurface(SDL_Surface* Surface, Uint16 Width, Uint16 Height) {
  
// }

bool GSurface::LoadBombs() {
  SurfBomb = GSurface::OnLoad("Resources/bombs.png");
}

bool GSurface::LoadBombers() {
  SurfBomber = GSurface::OnLoad("Resources/bots.png");
}

bool GSurface::LoadFlames() {
  SurfFlame = GSurface::OnLoad("Resources/flames.png");
}

bool GSurface::LoadPowerups() {
  SurfPowerup = GSurface::OnLoad("Resources/powerups.png");
}

bool GSurface::LoadTiles() {
  SurfTile = GSurface::OnLoad("Resources/tiles.png");
}

bool GSurface::UnloadBombs() {
  SDL_FreeSurface(SurfBomb);
}

bool GSurface::UnloadBombers() {
  SDL_FreeSurface(SurfBomber);
}

bool GSurface::UnloadFlames() {
  SDL_FreeSurface(SurfFlame);
}
  
bool GSurface::UnloadPowerups() {
  SDL_FreeSurface(SurfPowerup);
}

bool GSurface::UnloadTiles() {
  SDL_FreeSurface(SurfTile);
}
