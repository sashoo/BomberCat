#ifndef GAREA_HPP
#define GAREA_HPP

//#include "CMap.hpp"
//#include "Srand.hpp"
#include <SDL.h>
#include <vector>
#include <stdio.h>
#include <string>
#include "GSurface.hpp"

class MirageApp;

class GArea {
public:
  GArea();
  
  static GArea AreaControl;
  //std::vector<CMap> MapList;

  void RegisterApp(MirageApp* app);

  void Generate();
  bool OnLoad(char* File);
  bool OnSave();

  void OnRenderBack(SDL_Surface* SurfDisplay, int CameraX, int CameraY);
  void OnRender(SDL_Surface* SurfDisplay, int CameraX, int CameraY);
 
  void OnCleanup(); 
  void PlacePowerups();
  
  // in tiles
  int GetWidth();
  int GetHeight();
    
  // in pixels
  int GetBoundX();
  int GetBoundY();
  
  //int* GetTile(int X, int Y);
  //bool SetTile(int X, int Y, int type); 

  bool RenderBack;
  bool RenderCol;
  bool RenderFore;

  //CMap* GetMap(int X, int Y); 
  int* GetTile(int X, int Y);
  bool SetTile(int X, int Y, int type = 1);

private:  
  int AreaWidth;
  int AreaHeight;
  int AreaBoundX;
  int AreaBoundY;
  std::string TilesetFilename;
  SDL_Surface* SurfTileset;
  std::vector<int> TileList;
  MirageApp* App;

};

#endif
