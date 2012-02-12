#include "GCamera.hpp"

GCamera GCamera::CameraControl;

GCamera::GCamera() {
  X = Y = 0;
  TargetX = TargetY = NULL;
  TargetMode = TARGET_MODE_NORMAL;
  HasTarget = false;
}

void GCamera::OnMove(int MoveX, int MoveY) {
  X += MoveX;
  Y += MoveY;
}

void GCamera::SetBounds(int w, int h) {
  BoundX = w;
  BoundY = h;
}
// void GCamera::OnLoop() {
//   if (HasTarget) {
//     if (TARGET_MODE_CENTER == TargetMode) {
//       X = *TargetX - GWIDTH/2;
//       Y = *TargetY - GHEIGHT/2;      
//     }
//   }
//   if (X < 0) X = 0;
//   if (Y < 0) Y = 0;
  
// }

int GCamera::GetX() {
  int result;
  if (TargetX != NULL) {    
    if (TargetMode == TARGET_MODE_CENTER) 
      result = *TargetX - GWIDTH/2+OffX;
    else
      result = *TargetX;  
    
  }
  else
    result = X;

   if (GWIDTH >= BoundX && TARGET_MODE_CENTER == TargetMode) {
     result = -(GWIDTH-BoundX)/2;
    return result;
   }

  if (result < 0) 
    result = 0;
  else if (result + GWIDTH > BoundX) 
    result = BoundX-GWIDTH;
  return result;  
}

int GCamera::GetY() {
  int result;
  if (TargetY != NULL) {
    if (TargetMode == TARGET_MODE_CENTER) 
      result = *TargetY - GHEIGHT/2+OffY;
    else    
      result = *TargetY;
  }
  else
    result = Y;


  if (GHEIGHT >= BoundY && TARGET_MODE_CENTER == TargetMode) {
    result = -(GHEIGHT-BoundY)/2;
    return result;
  }
  // if (BoundY <= MAP_HEIGHT*TILE_SIZE && TARGET_MODE_CENTER == TargetMode) {
  //   result = -MAP_HEIGHT*TILE_SIZE/2;
  //   return result;
  //  }

  if (result < 0) 
    result = 0;
  else if (result + GHEIGHT > BoundY) 
    result = BoundY-GHEIGHT;
  return result;  
}

void GCamera::SetPos(int X, int Y) {
  TargetX = NULL;
  TargetY = NULL;
  this->X = X;
  this->Y = Y;  
}

void GCamera::SetTarget(float* X, float* Y, int w, int h) {
  TargetX = X;
  TargetY = Y;
  OffX = w/2;
  OffY = h/2;
  HasTarget = true;
}
