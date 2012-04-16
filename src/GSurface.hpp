#ifndef GSURFACE_HPP
#define GSURFACE_HPP

#include <SDL.h>
#include <SDL_ttf.h>

class GSurface {

public:
  GSurface();
  static SDL_Surface* Load(const char* filename);
  static bool Draw(SDL_Surface* SurfDest, SDL_Surface* SurfSrc, 
		     int x, int y);
  static bool Draw(SDL_Surface* SurfDest, SDL_Surface* SurfSrc, 
		     int x, int y, int x2, int y2, int w, int h);
  // static SDL_Surface* SDL_ScaleSurface(SDL_Surface* Surface, Uint16 Width, Uint16 Height);

  // these methods load resources from disk
  static bool LoadBombs();
  static bool LoadBombers();
  static bool LoadFlames();
  static bool LoadPowerups();
  static bool LoadTiles();    
  static bool LoadFontRegular();

  // these methods free resources loaded from disk
  static bool UnloadBombs();
  static bool UnloadBombers();
  static bool UnloadFlames();
  static bool UnloadPowerups();
  static bool UnloadTiles();
  static bool UnloadFontRegular();

  static void SetColor (SDL_Color& color, int r, int g, int b);
  static SDL_Color GetColor (int r, int g, int b);

  static SDL_Surface* SurfBomb;
  static SDL_Surface* SurfBomber;
  static SDL_Surface* SurfFlame;
  static SDL_Surface* SurfPowerup;
  static SDL_Surface* SurfTile;
  static TTF_Font*    FontRegular;

  static SDL_Color ColorRed;
  static SDL_Color ColorGreen;
  static SDL_Color ColorOption;
  static SDL_Color ColorActive;
  static SDL_Color ColorInactive;
};

bool DotInRect(int dotx, int doty, SDL_Rect rect);

#endif


