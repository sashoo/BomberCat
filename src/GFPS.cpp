#include "GFPS.hpp"

GFPS GFPS::FPSControl;

GFPS::GFPS() {
  OldTime = 0;
  LastTime = 0;
  SpeedFactor = 0.f;
  ScaleFactor = 32.f;
  Frames = 0;
  NumFrames = 0;
}

void GFPS::OnLoop() {
  if (OldTime + 1000 < SDL_GetTicks()) {
    OldTime = SDL_GetTicks();
    NumFrames = Frames;
    Frames = 0;
  }

  SpeedFactor = (SDL_GetTicks() - LastTime)/1000.f * ScaleFactor;
  LastTime = SDL_GetTicks();
  
  Frames++;
}

int GFPS::GetFPS() {
  return NumFrames;
}

float GFPS::GetSpeedFactor() const {
  return SpeedFactor;
}

float GFPS::GetScaleFactor() const {
  return ScaleFactor;
}

void GFPS::SetScaleFactor(float factor) {
  ScaleFactor = factor;
}
