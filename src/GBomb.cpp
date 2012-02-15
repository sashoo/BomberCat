#include "GBomb.hpp"
#include "GBomber.hpp"
#include "sstream"
#include "GFlame.hpp"
#include "GDecor.hpp"

int GBomb::BombsTotal = 0;
std::vector<GBomb*> GBomb::BombList;

GBomb::GBomb() : STimer(2000), GEntity(){
  std::stringstream ss;
  ss << "Bomb " << BombsTotal;
  Name = ss.str();
  Width = TILE_SIZE;
  Height = TILE_SIZE;
  AnimControl.MaxFrames = 3;
  AnimControl.SetFrameRate(250);
  Type = ENTITY_TYPE_BOMB;
  CurrentFrameRow = 0;
  CurrentFrameCol = 0;
  SpeedX = 0.f;
  SpeedY = 0.f;
  MaxSpeedX = 0.f;
  MaxSpeedY = 0.f;
  ChainedFrom = 0; 
  JustPlaced = true;  
  State = BOMB_STATE_TICKING;
  //Flags = ENTITY_FLAG_MAPONLY;
  Start();
 
  //app->Log << "TimeMax: " << TimeMax << std::endl;
  BombsTotal++;
  
}

bool GBomb::OnLoad() {
  return true;
}

void GBomb::OnLoop() {
  if (BOMB_STATE_EXPLODED != State) {
    STimer::OnLoop();
    GEntity::OnLoop();
  }
}

bool GBomb::OnTimeOut() {
  State = BOMB_STATE_EXPLODING;
  Explode();    
  return true;
}

void GBomb::OnRender(SDL_Surface* SurfDisplay) {
  if (BOMB_STATE_EXPLODED != State) {
    GSurface::OnDraw(SurfDisplay, GSurface::SurfBomb, 
		     X-GCamera::CameraControl.GetX(), 
		     Y-GCamera::CameraControl.GetY(), 
		     (0+CurrentFrameCol + AnimControl.GetCurrentFrame())* Width, 
		     CurrentFrameRow * Height, 
		     Width, Height);
  }
}

void GBomb::OnCleanup() {
  GEntity::OnCleanup();
}

void GBomb::OnAnimate() {
  AnimControl.OnAnimate();
}

bool GBomb::OnCollision(GEntity* Entity) {
  return GEntity::OnCollision(Entity);
}

void GBomb::Explode() {
  // std::vector<GEntity*>::iterator iter;
  // for (iter = EntityList.begin(); iter != EntityList.end(); iter++) {
  //   if (*iter == this) {
  //     //delete *iter;
  //     //EntityList.erase(iter);
  //   }
  // }
  State = BOMB_STATE_EXPLODED;
  Bomber->BombsPlaced--;
  BombsTotal--;
  PlaceFlames();
  
  Enabled = false;
}

void GBomb::PlaceFlames() {
  int radius = Bomber->BlastRadius;
  GFlame* flame = new GFlame();
  flame->X = X;
  flame->Y = Y;
  GFlame::FlameList.push_back(flame);
  flame->CheckBombs();
  flame->CheckBombers();
  //flame->CheckPowerups();
  int centX = X;
  int centY = Y;

  if (! (ChainedFrom & FLAME_CHAIN_UP))
    CheckDir(centX, centY, FLAME_DOWN);
   
  if (! (ChainedFrom & FLAME_CHAIN_RIGHT))
    CheckDir(centX, centY, FLAME_LEFT);
   
  if (! (ChainedFrom & FLAME_CHAIN_DOWN))
    CheckDir(centX, centY, FLAME_UP);

  if (! (ChainedFrom & FLAME_CHAIN_LEFT))
    CheckDir(centX, centY, FLAME_RIGHT);

 
}
  
  
void GBomb::CheckDir(int cx, int cy, int alttype) {    
  int deftype = 0;
  int radius = Bomber->BlastRadius;
  int newx = cx;
  int newy = cy;
  
  for (int i = 1; i <= radius; i++) {
    if (alttype == FLAME_LEFT) {
      newx = cx - i*TILE_SIZE;
      deftype = FLAME_HORIZONTAL;
    }
    else if (alttype == FLAME_RIGHT) {
      newx = cx + i*TILE_SIZE;
      deftype = FLAME_HORIZONTAL;
    }
    else if (alttype == FLAME_UP) {
      newy = cy - i*TILE_SIZE;
      deftype = FLAME_VERTICAL;
    }
    else if (alttype == FLAME_DOWN) {
      newy = cy + i*TILE_SIZE;
      deftype = FLAME_VERTICAL;
    }
    
    //int newx = centX;
    //int newy = centY-TILE_SIZE*i;
    int* tile = CArea::AreaControl.GetTile(newx, newy);
    if (NULL == tile) break;
    if (*tile >= 0 && *tile <= 2) {
      GFlame* flame = new GFlame();
      flame->X = newx;
      flame->Y = newy;   
      int dir;
      if (FLAME_LEFT == alttype )
	dir = FLAME_CHAIN_LEFT;
      else if (FLAME_RIGHT == alttype )
 	dir = FLAME_CHAIN_RIGHT;
      else if (FLAME_UP == alttype )
 	dir = FLAME_CHAIN_UP;
      else if (FLAME_DOWN == alttype )
 	dir = FLAME_CHAIN_DOWN;

      flame->ChainDirection = dir;
     
      if (*tile == 1) {
	flame->FlameType = alttype;
	*tile = 0;
	GFlame::FlameList.push_back(flame);
	GDecor* decor = new GDecor(newx, newy);
	decor->OnLoad();
	break;
      }
      else if (*tile == 2) {
	flame->FlameType = alttype;
	GFlame::FlameList.push_back(flame);
	break;
      }
      else {
	if (i == radius)
	  flame->FlameType = alttype;
	else
	  flame->FlameType = deftype;	
	GFlame::FlameList.push_back(flame);
	if (flame->CheckPowerups()) {
	  flame->FlameType = alttype;
	  break;
	} 
      }	
      
      //flame->CheckTouch();
    }    
  } // for
}
