#ifndef GCAMERA_HPP
#define GCAMERA_HPP

#include <SDL.h>
#include "Define.hpp"

enum {
  TARGET_MODE_NORMAL = 0,
  TARGET_MODE_CENTER
};

class GCamera {
public:
  GCamera();
  static GCamera CameraControl;
  bool HasTarget;
  int TargetMode;
  void OnMove(int MoveX, int MoveY);
  //void OnLoop();
  int GetX();
  int GetY();
  void SetPos(int X, int Y);
  void SetTarget(float* X, float* Y, int w, int h);
  void SetBounds(int w, int h);

private:
  int X;
  int Y;
  int OffX;
  int OffY;
  int BoundX;
  int BoundY;
  float* TargetX;
  float* TargetY;  
  
};

#endif
