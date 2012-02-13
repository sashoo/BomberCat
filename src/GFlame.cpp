#include "GFlame.hpp"
#include "GBomb.hpp"
#include "GBomber.hpp"
#include "GPowerup.hpp"
#include <sstream>

int GFlame::FlamesTotal = 0;
std::vector<GFlame*> GFlame::FlameList;

GFlame::GFlame() : STimer(40, 0, true), GEntity() {
  std::stringstream ss;
  ss << "Flame " << FlamesTotal;
  Name = ss.str();
  Width  = TILE_SIZE;
  Height = TILE_SIZE;
  //AnimControl.SetFrameRate(200);
  AnimControl.SetCurrentFrame(0);
  Type = ENTITY_TYPE_FLAME;
  CurrentFrameRow = 0;
  CurrentFrameCol = 0;
 
  FlameType = 0;
  FlamePower = 0;
  SpeedX = 0.f;
  SpeedY = 0.f;
  MaxSpeedX = 0.f;
  MaxSpeedY = 0.f;
  Frame = 0;
  ChainDirection = 0;
  //MaxFlamePower = 8;
  //Flags = ENTITY_FLAG_MAPONLY;
  Start();
  //CheckTouch();
  //app->Log << "TimeMax: " << TimeMax << std::endl;
  App->Log << "Name: " << Name << " created" << std::endl;
  FlamesTotal++;
}

bool GFlame::OnLoad() {
  return true;
}

void GFlame::OnLoop() { 
  STimer::OnLoop();
  GEntity::OnLoop();  
  //CheckTouch();
}

bool GFlame::OnTimeOut() {
  if (FlamePower < MaxFlamePower) {
    ++FlamePower;
    CheckBombers();
    //CheckPowerups();
    Frame = 4-abs(FlamePower-4);
    if (FlamePower == 2)
      CheckBombs();
    // AnimControl.SetCurrentFrame(4-abs(FlamePower-4));
    //AnimControl.SetCurrentFrame(FlamePower);
  }
  else {
    App->Log << "Name: " << Name << " died" << std::endl;
    Enabled = false;
    
  }
  return false; // FIXME
  // return srand() % 2
}
  
void GFlame::OnRender(SDL_Surface* SurfDisplay) {  
  // flametype defines sprite colon
  // flame power defines sprite row (GetCurrentFrame())
  GSurface::OnDraw(SurfDisplay, GSurface::SurfFlame, 
		   X-GCamera::CameraControl.GetX(), 
		   Y-GCamera::CameraControl.GetY(), 
		   Frame * Width, 
		   FlameType * Height, 
		   Width, Height); 

}

void GFlame::OnCleanup() {
  GEntity::OnCleanup();
  FlamesTotal--;
}

void GFlame::OnAnimate() {
  // Animation is handled by flame power
  // and internal timer
  // No code needed here
}

bool GFlame::OnCollision(GEntity* Entity) {
  return GEntity::OnCollision(Entity);
}

void GFlame::CheckBombs() {
  std::vector<GBomb*>::iterator bomb = GBomb::BombList.begin();
  while (bomb != GBomb::BombList.end()) {
    if ((*bomb)->X == X && 
	(*bomb)->Y == Y
	) {
     
      if (FlameType !=0) {
	(*bomb)->TimerState = TIMER_STATE_FINISHED;
	(*bomb)->ChainedFrom = (*bomb)->ChainedFrom | ChainDirection;
      }

    }
    bomb++;
  }
}

void GFlame::CheckBombers() {
 std::vector<GBomber*>::iterator bomber = GBomber::BomberList.begin();
  while (bomber != GBomber::BomberList.end()) {
    if ((*bomber)->Alive) {
      if ((*bomber)->IsHit(this)) {

	(*bomber)->Die();
	//(*bomber)->Enabled = false;
      }
      
    }
    bomber++;
  }
}

bool GFlame::CheckPowerups() {
  std::vector<GPowerup*>::iterator powerup = GPowerup::PowerupList.begin();
  while (powerup != GPowerup::PowerupList.end()) {
  
    if ((*powerup)->Collides(this)) { 
      (*powerup)->Enabled = false;
      return true;
      //(*powerup)->Enabled = false;
    }   
    powerup++;
  }
  return false;
}
