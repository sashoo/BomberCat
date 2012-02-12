#include "GPowerup.hpp"
#include <sstream>

int GPowerup::PowerupsTotal = 0;
std::vector<GPowerup*> GPowerup::PowerupList;

GPowerup::GPowerup() {
  std::stringstream ss;
  ss << "Powerup " << PowerupsTotal;
  //app->Log << "Name: " << Name << " created" << std::endl;
  Name = ss.str();
  X = 0;
  Y = 0;
  Width = TILE_SIZE;
  Height = TILE_SIZE;
  AnimControl.MaxFrames = 2;
  AnimControl.SetFrameRate(150);
  AnimControl.SetCurrentFrame(0);

  ColX = 8;
  ColW = 16;
  ColY = 8;
  ColH = 16;

  Type = ENTITY_TYPE_POWERUP;
  CurrentFrameRow = 0;
  CurrentFrameCol = 0;
  SpeedX = 0.f;
  SpeedY = 0.f;
  MaxSpeedX = 0.f;
  MaxSpeedY = 0.f;
  PowerupType = 0;
  App->Log << "Name: " << Name << " created" << std::endl;
  
  PowerupsTotal++;
}

bool GPowerup::OnLoad() {
  return true;
}

void GPowerup::OnLoop() {
  GEntity::OnLoop();
}

void GPowerup::OnRender(SDL_Surface* SurfDisplay) {
   GSurface::OnDraw(SurfDisplay, GSurface::SurfPowerup, 
		    X-GCamera::CameraControl.GetX(), 
		    Y-GCamera::CameraControl.GetY(), 
		    AnimControl.GetCurrentFrame() * Width, 
		    PowerupType * Height, 
		    Width, Height); 
}

void GPowerup::OnCleanup() {
  GEntity::OnCleanup();
  PowerupsTotal--;
}

void GPowerup::OnAnimate() {
  AnimControl.OnAnimate();
}

bool GPowerup::OnCollision(GEntity* Entity) {
  GEntity::OnCollision(Entity);
}
