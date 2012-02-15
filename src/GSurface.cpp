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
  SurfBomb = GSurface::OnLoad((char*)"Resources/bombs.png");
  return SurfBomb;
}

bool GSurface::LoadBombers() {
  SurfBomber = GSurface::OnLoad((char*)"Resources/bots.png");
  return SurfBomber;
}

bool GSurface::LoadFlames() {
  SurfFlame = GSurface::OnLoad((char*)"Resources/flames.png");
  return SurfFlame;
}

bool GSurface::LoadPowerups() {
  SurfPowerup = GSurface::OnLoad((char*)"Resources/powerups.png");
  return SurfPowerup;
}

bool GSurface::LoadTiles() {
  SurfTile = GSurface::OnLoad((char*)"Resources/tiles.png");
  return SurfTile;
}

bool GSurface::UnloadBombs() {
  SDL_FreeSurface(SurfBomb);
  return true;
}

bool GSurface::UnloadBombers() {
  SDL_FreeSurface(SurfBomber);
  return true;
}

bool GSurface::UnloadFlames() {
  SDL_FreeSurface(SurfFlame);
  return true;
}
  
bool GSurface::UnloadPowerups() {
  SDL_FreeSurface(SurfPowerup);
  return true;
}

bool GSurface::UnloadTiles() {
  SDL_FreeSurface(SurfTile);
  return true;
}
