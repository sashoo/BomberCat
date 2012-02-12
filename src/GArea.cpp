#include "GArea.hpp"
#include "MirageApp.hpp"
#include "GPowerup.hpp"
#include "GSurface.hpp"

CArea CArea::AreaControl;

CArea::CArea() {  
  AreaWidth = 15;
  AreaHeight = 13;
  
  AreaBoundX = AreaWidth*TILE_SIZE;
  AreaBoundY = AreaWidth*TILE_SIZE;
  RenderBack = true;
  RenderCol = true;
  RenderFore = true;
}

void CArea::RegisterApp(MirageApp* app) {
  if (NULL != app)
    App = app;
}

int CArea::GetWidth() {
  return AreaWidth;
}

int CArea::GetHeight() {
  return AreaHeight;
}

int CArea::GetBoundX() {
  return AreaBoundX;
}

int CArea::GetBoundY() {
  return AreaBoundY;
}

bool CArea::OnLoad(char* File) {
  TileList.clear(); 

  // if((SurfTileset = GSurface::OnLoad(File)) == false) { 
  //   App->Log << "Failed to load tileset file" << std::endl;  
  //   return false;
  // }
  
  AreaBoundX = AreaWidth  * TILE_SIZE;
  AreaBoundY = AreaHeight * TILE_SIZE;

  //GenerateLevel();
  

  for(int Y = 0; Y < AreaHeight; Y++) {
    for(int X = 0; X < AreaWidth; X++) {
      int tempTile = 0;
      if (0 == X || AreaWidth -1 == X ||
      	  0 == Y || AreaHeight -1 == Y)
      	tempTile = 2;
      else if (0 == (X) % 2 &&
      	       0 == (Y) % 2)
      	tempTile = 2;
      else      
	tempTile = Srand::GetInt(0,1);

      // if (1 == tempTile) {
      // 	int chances = Srand::GetInt(0, 100);
      // 	if (chances <= 25) {
      // 	  int ptype = Srand::GetInt(0, 1);
	
      // 	  GPowerup* pup = new GPowerup();
      // 	  pup->PowerupType = ptype;
      // 	  pup->X = X*TILE_SIZE;
      // 	  pup->Y = Y*TILE_SIZE;
      // 	  GPowerup::PowerupList.push_back(pup);
      // 	}
      // }
      
      TileList.push_back(tempTile);      
    }   
  }  

  return true;
}

bool CArea::OnSave() {
  FILE* FileHandle = fopen("level-debug.log", "w");
  if(FileHandle == NULL) {
    return false;
  }
  
  int ID = 0;
 
   for(int Y = 0; Y < AreaHeight; Y++) {
    for(int X = 0; X < AreaWidth; X++) {     
      int tile = TileList[ID];
      fprintf(FileHandle, "%02x ", tile);   
      ID++;
    }
    fprintf(FileHandle, "\n");
  }

  fclose(FileHandle);
  return true;
}

void CArea::OnRenderBack(SDL_Surface* Surf_Display, int CameraX, int CameraY) {
  int TilesetWidth  = GSurface::SurfTile->w / TILE_SIZE;
  int TilesetHeight = GSurface::SurfTile->h / TILE_SIZE;
  int ID = 0;
  
  for(int Y = 0; Y < AreaHeight; Y++) {
    for(int X = 0; X < AreaWidth; X++) { 
      int tiletype = TileList[ID];
      if (0 != tiletype) {
	ID++;
	continue;
      }

      int tX = X * TILE_SIZE - CameraX;
      int tY = Y * TILE_SIZE - CameraY;

      int TilesetX = (tiletype % (TILE_SIZE*3)) * TILE_SIZE;
      //int TilesetY = (TileList[ID] / TilesetHeight) * TILE_SIZE;
      int TilesetY = 0;
	
      GSurface::OnDraw(Surf_Display, GSurface::SurfTile, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);

      ID++;
    }
  }  
}

void CArea::OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY) {
  
  int TilesetWidth  = GSurface::SurfTile->w / TILE_SIZE;
  int TilesetHeight = GSurface::SurfTile->h / TILE_SIZE;
  int ID = 0;

  
  for(int Y = 0; Y < AreaHeight; Y++) {
    for(int X = 0; X < AreaWidth; X++) { 
      int tiletype = TileList[ID];
      if (0 == tiletype) {
	ID++;
	continue;
      }

      int tX = X * TILE_SIZE - CameraX;
      int tY = Y * TILE_SIZE - CameraY;

      int TilesetX = (tiletype % (TILE_SIZE*3)) * TILE_SIZE;
      //int TilesetY = (TileList[ID] / TilesetHeight) * TILE_SIZE;
      int TilesetY = 0;
	
      GSurface::OnDraw(Surf_Display, GSurface::SurfTile, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);

      ID++;
    }
  }  
}

void CArea::OnCleanup() {
  // if(SurfTileset) {
  //   SDL_FreeSurface(SurfTileset);
  // }
 
}
 
int* CArea::GetTile(int X, int Y) {
  int ID = 0;
  ID = X / TILE_SIZE;
  ID = ID + AreaWidth * Y / TILE_SIZE;

  if (ID < 0 || ID >= TileList.size())
    return NULL;
  
  return &TileList[ID];  
}

bool CArea::SetTile(int X, int Y, int type) {  
  int ID = 0;
  ID = X / TILE_SIZE;
  ID = ID + AreaWidth * Y / TILE_SIZE;

  if (ID < 0 || ID >= TileList.size())
    return NULL;

  TileList[ID] = type;   
}

void CArea::PlacePowerups() {
  for(int Y = 0; Y < AreaHeight; Y++) {
    for(int X = 0; X < AreaWidth; X++) {
      int tempTile = *GetTile(X * TILE_SIZE, Y*TILE_SIZE);
      if (1 == tempTile) {
	int chances = Srand::GetInt(0, 100);
	if (chances <= 25) {
	  int ptype = Srand::GetInt(0, 1);
	
	  GPowerup* pup = new GPowerup();
	  pup->PowerupType = ptype;
	  pup->X = X*TILE_SIZE;
	  pup->Y = Y*TILE_SIZE;
	  GPowerup::PowerupList.push_back(pup);
	}
      }
      
      TileList.push_back(tempTile);      
    }   
  }  
}
  