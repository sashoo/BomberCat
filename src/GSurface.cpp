#include "GSurface.hpp"
#include <SDL_image.h>

SDL_Surface* GSurface::SurfBomb;
SDL_Surface* GSurface::SurfBomber;
SDL_Surface* GSurface::SurfFlame;
SDL_Surface* GSurface::SurfPowerup;
SDL_Surface* GSurface::SurfTile;
TTF_Font* GSurface::FontRegular;

SDL_Color GSurface::ColorRed = GetColor(255, 0, 0);
SDL_Color GSurface::ColorGreen = GetColor(0, 255, 0);
SDL_Color GSurface::ColorOption = GetColor(255, 255, 0);
SDL_Color GSurface::ColorActive = GetColor(30, 140, 230);
SDL_Color GSurface::ColorInactive = GetColor(180, 180, 180);

GSurface::GSurface() {
}

SDL_Surface* GSurface::Load(const char* filename){
  SDL_Surface* SurfTemp = NULL;
  SDL_Surface* SurfReturn = NULL;
  
  if ((SurfTemp = IMG_Load(filename)) == NULL) {
    return NULL;
  }
  
  SurfReturn = SDL_DisplayFormatAlpha(SurfTemp);
  SDL_FreeSurface(SurfTemp);
  return SurfReturn;
}

bool GSurface::Draw(SDL_Surface* SurfDest, 
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

bool GSurface::Draw(SDL_Surface* SurfDest, SDL_Surface* SurfSrc, 
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
  SurfBomb = GSurface::Load("Resources/bombs.png");
  return SurfBomb;
}

bool GSurface::LoadBombers() {
  SurfBomber = GSurface::Load("Resources/bots.png");
  return SurfBomber;
}

bool GSurface::LoadFlames() {
  SurfFlame = GSurface::Load("Resources/flames.png");
  return SurfFlame;
}

bool GSurface::LoadPowerups() {
  SurfPowerup = GSurface::Load("Resources/powerups.png");
  return SurfPowerup;
}

bool GSurface::LoadTiles() {
  SurfTile = GSurface::Load("Resources/tiles.png");
  return SurfTile;
}

bool GSurface::LoadFontRegular() {
  FontRegular = TTF_OpenFont("Resources/font.ttf", 18 );
  if (FontRegular == NULL) {   
    return false;
  }
  return true;
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

bool GSurface::UnloadFontRegular() { 
  if (FontRegular != NULL) {
    TTF_CloseFont(FontRegular);    
    return true;
  }
  return false;
}

void GSurface::SetColor(SDL_Color& color, int r, int g, int b) {
  color.r = r;
  color.g = g;
  color.b = b;
}

SDL_Color GSurface::GetColor(int r, int g, int b) {
  SDL_Color color;
  color.r = r;
  color.g = g;
  color.b = b;
  return color;
}
