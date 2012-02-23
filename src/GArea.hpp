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
class StateGame;

class GArea {
public:
  GArea();
  
  static GArea AreaControl;
  //std::vector<CMap> MapList;

  void RegisterApp(MirageApp* app);

  void Generate();
  bool Load(const char* File);
  bool Save();

  void RenderBack(SDL_Surface* SurfDisplay, int CameraX, int CameraY);
  void Render(SDL_Surface* SurfDisplay, int CameraX, int CameraY); 
  void Cleanup(); 

  void PlacePowerups();
  void SetStateGame(StateGame* state);
  
  // Area size in tiles
  int GetWidth();
  int GetHeight();  
    
  // Area size in pixels
  int GetBoundX();
  int GetBoundY();
 
  // Return tile type; arguments are pixels!
  int GetTile(int X, int Y);
  bool SetTile(int X, int Y, int type = 1);
  
  // Return tile type; arguments are tile coordinates
  int GetTileCoord(int X, int Y);
  bool SetTileCoord(int X, int Y, int type = 1);

  //int* GetTile(int X, int Y);
  //bool SetTile(int X, int Y, int type); 

  bool bRenderBack;
  bool bRenderCol;
  bool bRenderFore;  

  // an UnrealEngine-inspired variable
  // although it can be set on clients
  // it will be ignored by the net code
  bool bNetDirty;

private:  
  int AreaWidth;
  int AreaHeight;
  int AreaBoundX;
  int AreaBoundY;
  StateGame* pStateGame;
  std::string TilesetFilename;
  SDL_Surface* SurfTileset;
  std::vector<int> TileList;
  MirageApp* App;

};

#endif
