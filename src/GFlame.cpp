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
  //App->Log << "Name: " << Name << " created" << std::endl;
  FlamesTotal++;
}

bool GFlame::Load() {
  return true;
}

void GFlame::Loop() { 
  STimer::Loop();
  GEntity::Loop();   
}

bool GFlame::OnTimeOut() {
  if (FlamePower < MaxFlamePower) {
    ++FlamePower;
    CheckBombers();   
    Frame = 4-abs(FlamePower-4);
    if (FlamePower == 2)
      CheckBombs();    
  }
  else {
    App->Log << "Name: " << Name << " died" << std::endl;
    Enabled = false;
    
  }
  return true;
}
  
void GFlame::Render(SDL_Surface* SurfDisplay) {  
  // flametype defines sprite colon
  // flame power defines sprite row (GetCurrentFrame())
  GSurface::Draw(SurfDisplay, GSurface::SurfFlame, 
		   X-GCamera::CameraControl.GetX(), 
		   Y-GCamera::CameraControl.GetY(), 
		   Frame * Width, 
		   FlameType * Height, 
		   Width, Height); 

}

void GFlame::Cleanup() {
  GEntity::Cleanup();
  FlamesTotal--;
}

void GFlame::Animate() {
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
