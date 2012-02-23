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

bool GPowerup::Load() {
  return true;
}

void GPowerup::Loop() {
  GEntity::Loop();
}

void GPowerup::Render(SDL_Surface* SurfDisplay) {
   GSurface::Draw(SurfDisplay, GSurface::SurfPowerup, 
		    X-GCamera::CameraControl.GetX(), 
		    Y-GCamera::CameraControl.GetY(), 
		    AnimControl.GetCurrentFrame() * Width, 
		    PowerupType * Height, 
		    Width, Height); 
}

void GPowerup::Cleanup() {
  GEntity::Cleanup();
  PowerupsTotal--;
}

void GPowerup::Animate() {
  AnimControl.Animate();
}

bool GPowerup::OnCollision(GEntity* Entity) {
  return GEntity::OnCollision(Entity);
}
