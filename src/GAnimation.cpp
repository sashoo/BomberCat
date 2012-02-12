#include "GAnimation.hpp"

GAnimation::GAnimation(){
  CurrentFrame = 0;
  MaxFrames = 0;
  FrameInc = 1;
  FrameRate = 150;
  OldTime = 0;
  Oscillate = false;
  Mode = ANIM_MODE_ONEROW;
}

bool GAnimation::OnAnimate() {
  if (OldTime + FrameRate > SDL_GetTicks())
    return false;

  OldTime = SDL_GetTicks();
  //if (ANIM_MODE_ONEROW == Mode) {
    
  CurrentFrame += FrameInc;
  
  if (Oscillate) {
    if (FrameInc > 0) {
      if (CurrentFrame >= MaxFrames - 1) {
	FrameInc = -FrameInc;
      }
    } else {
      if (CurrentFrame <= 0) {
	FrameInc = -FrameInc;
      }
    }
  } else {
    if (CurrentFrame >= MaxFrames ) {
      CurrentFrame = 0;
	
      if(ANIM_MODE_DESCEND == Mode) {
	CurrentRow++;
	if (CurrentRow > MaxRow)
	  return true;
      }

    }
  }
  return false;
  //} // ONEROW
}

void GAnimation::SetFrameRate(int rate) {
  FrameRate = rate;
}

void GAnimation::SetFrameInc(int inc) {
  FrameInc = inc;
}

void GAnimation::SetCurrentFrame(int frame) {
  if (frame < 0 || frame >= MaxFrames) return;

  CurrentFrame = frame;
}

int GAnimation::GetCurrentFrame() {
  return CurrentFrame;
}

