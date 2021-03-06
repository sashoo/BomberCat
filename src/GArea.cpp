#include "GArea.hpp"
#include "MirageApp.hpp"
#include "GPowerup.hpp"
#include "GSurface.hpp"
#include "StateGame.hpp"

GArea GArea::AreaControl;

GArea::GArea() {
  // NOTE: network code currently assumes
  // a relatively small gaming area size
  // it will break if dimensions below are significantly changed
  AreaWidth = 15;
  AreaHeight = 13;
  
  AreaBoundX = AreaWidth*TILE_SIZE;
  AreaBoundY = AreaWidth*TILE_SIZE;
  bRenderBack = true;
  bRenderCol  = true;
  bRenderFore = true;
  pStateGame = NULL;
}

void GArea::RegisterApp(MirageApp* app) {
  if (NULL != app)
    App = app;
}

int GArea::GetWidth() {
  return AreaWidth;
}

int GArea::GetHeight() {
  return AreaHeight;
}

int GArea::GetBoundX() {
  return AreaBoundX;
}

int GArea::GetBoundY() {
  return AreaBoundY;
}

bool GArea::Load(const char* File) {
  TileList.clear(); 
  TileList.reserve(AreaWidth * AreaHeight);

  // if((SurfTileset = GSurface::OnLoad(File)) == false) { 
  //   App->Log << "Failed to load tileset file" << std::endl;  
  //   return false;
  // }
  
  AreaBoundX = AreaWidth  * TILE_SIZE;
  AreaBoundY = AreaHeight * TILE_SIZE;

  //GenerateLevel();
  
  // another networking note:
  // it assumes that tile id will fit in a single byte

  for(int Y = 0; Y < AreaHeight; Y++) {
    for(int X = 0; X < AreaWidth; X++) {
      int tempTile = 0;
      if (0 == X || AreaWidth -1 == X ||
      	  0 == Y || AreaHeight -1 == Y)
      	tempTile = 2;
      else if (pStateGame->NetMode == GAME_CLIENT)
          // create empty map for clients
          // actual contents will be replicated later
          tempTile = 0;
      else if (0 == (X) % 2 &&
      	       0 == (Y) % 2)
      	tempTile = 2;
      else {
	int chance = Srand::GetInt(0, 100);
	if (chance <= 95)
	  tempTile = 1;
	else
	  tempTile = 0;
      }

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

bool GArea::Save() {
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

void GArea::RenderBack(SDL_Surface* Surf_Display, int CameraX, int CameraY) {
  // int TilesetWidth  = GSurface::SurfTile->w / TILE_SIZE;
  // int TilesetHeight = GSurface::SurfTile->h / TILE_SIZE;
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
	
      GSurface::Draw(Surf_Display, GSurface::SurfTile, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);

      ID++;
    }
  }  
}

void GArea::Render(SDL_Surface* Surf_Display, int CameraX, int CameraY) {
  
  // int TilesetWidth  = GSurface::SurfTile->w / TILE_SIZE;
  // int TilesetHeight = GSurface::SurfTile->h / TILE_SIZE;
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
	
      GSurface::Draw(Surf_Display, GSurface::SurfTile, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);

      ID++;
    }
  }  
}

void GArea::Cleanup() {
  pStateGame = NULL;
  // if(SurfTileset) {
  //   SDL_FreeSurface(SurfTileset);
  // }
 
}
 
int GArea::GetTile(int X, int Y) {
  int ID = 0;
  ID = X / TILE_SIZE;
  ID = ID + AreaWidth * Y / TILE_SIZE;

  if (ID < 0 || ID >= (int)TileList.size())
    return -1;
  
  return TileList[ID];  
}

int GArea::GetTileCoord(int X, int Y) {
  int ID = 0;
  ID = X;
  ID = ID + AreaWidth * Y;
  if (ID < 0 || ID >= (int)TileList.size())
    return -1;
  
  return TileList[ID];  
}

bool GArea::SetTile(int X, int Y, int type) {  
  int ID = 0;
  ID = X / TILE_SIZE;
  ID = ID + AreaWidth * Y / TILE_SIZE;

  if (ID < 0 || ID >= (int)TileList.size())
    return NULL;

  TileList[ID] = type; 
  bNetDirty = true;
  return true;
}

bool GArea::SetTileCoord(int X, int Y, int type) {  
  int ID = 0;
  ID = X;
  ID = ID + AreaWidth * Y;

  if (ID < 0 || ID >= (int)TileList.size())
    return NULL;

  TileList[ID] = type; 
  return true;
}

void GArea::PlacePowerups() {
  for(int Y = 0; Y < AreaHeight; Y++) {
    for(int X = 0; X < AreaWidth; X++) {
      int tempTile = GetTileCoord(X , Y);
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
  
void GArea::SetStateGame(StateGame* state) {
  if (state != NULL) 
    pStateGame = state;
}
