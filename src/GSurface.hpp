#ifndef GSURFACE_HPP
#define GSURFACE_HPP

#include <SDL.h>

class GSurface {

public:
  GSurface();
  static SDL_Surface* OnLoad(const char* filename);
  static bool OnDraw(SDL_Surface* SurfDest, SDL_Surface* SurfSrc, 
		     int x, int y);
  static bool OnDraw(SDL_Surface* SurfDest, SDL_Surface* SurfSrc, 
		     int x, int y, int x2, int y2, int w, int h);
  // static SDL_Surface* SDL_ScaleSurface(SDL_Surface* Surface, Uint16 Width, Uint16 Height);

  static bool LoadBombs();
  static bool LoadBombers();
  static bool LoadFlames();
  static bool LoadPowerups();
  static bool LoadTiles();    

  static bool UnloadBombs();
  static bool UnloadBombers();
  static bool UnloadFlames();
  static bool UnloadPowerups();
  static bool UnloadTiles();

  static SDL_Surface* SurfBomb;
  static SDL_Surface* SurfBomber;
  static SDL_Surface* SurfFlame;
  static SDL_Surface* SurfPowerup;
  static SDL_Surface* SurfTile;
};


#endif
