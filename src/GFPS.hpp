#ifndef GFPS_HPP
#define GFPS_HPP

#include <SDL.h>

class GFPS {
public:
  static GFPS FPSControl;
  GFPS();
  void OnLoop();
  int GetFPS();

  float GetSpeedFactor() const;

  float GetScaleFactor() const;
  void SetScaleFactor(float factor);

private:
  Uint32 OldTime;
  Uint32 LastTime;
  float SpeedFactor;
  float ScaleFactor;
  int NumFrames;
  int Frames; 

};

#endif
