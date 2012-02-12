#include "GDecor.hpp"
#include <sstream>

int GDecor::DecorsTotal;
std::vector<GDecor*> GDecor::DecorList;

GDecor::GDecor(int x, int y){
  std::stringstream ss;
  X = x;
  Y = y;
  ss << "Decor " << DecorsTotal;
  Name = ss.str();
  Width  = TILE_SIZE;
  Height = TILE_SIZE;

  DecorType = BURN_WALL;

  SpeedX = 0.f;
  SpeedY = 0.f;
  MaxSpeedX = 0.f;
  MaxSpeedY = 0.f;

 
  App->Log << "Name: " << Name << " created" << std::endl;
  DecorsTotal++;
}

bool GDecor::OnLoad() { 
  AnimControl.MaxFrames = 5; 
  AnimControl.SetCurrentFrame(2);
  AnimControl.SetFrameRate(120);
  AnimControl.Mode = ANIM_MODE_DESCEND;
  AnimControl.MaxRow = 1;
  AnimControl.CurrentRow = 0;
 
  DecorList.push_back(this);
  return true;
}

void GDecor::OnLoop() {
  GEntity::OnLoop();
}

void GDecor::OnRender(SDL_Surface* SurfDisplay) {
  if (BURN_WALL == DecorType) {
    GSurface::OnDraw(SurfDisplay, GSurface::SurfTile, 
		     X-GCamera::CameraControl.GetX(), 
		     Y-GCamera::CameraControl.GetY(), 
		     AnimControl.GetCurrentFrame() * Width, 
		     CurrentFrameRow * Height, 
		     Width, Height); 
  }
}

void GDecor::OnAnimate() {
  if (AnimControl.OnAnimate()) {      
    Enabled = false;
  }
  CurrentFrameRow = AnimControl.CurrentRow;
}

void GDecor::OnCleanup() {
  GEntity::OnCleanup();
  DecorsTotal--;
}
