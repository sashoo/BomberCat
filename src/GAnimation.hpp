#ifndef GANIMATION_HPP
#define GANIMATION_HPP

#include <SDL.h>

enum {
  ANIM_MODE_ONEROW,   //cycles one row
  ANIM_MODE_DESCEND,  //when hits the end of the row, descends 
  ANIM_MODE_STATIC    //shows the same frame
};

class GAnimation {
public:
  GAnimation();

  // returns true if max (row|frame|whatever) is hit
  bool Animate(); 

  void SetFrameRate(int rate);
  void SetCurrentFrame(int frame);
  int GetCurrentFrame();
  void SetFrameInc(int inc);
    
  int MaxFrames;
  int CurrentRow;
  int MaxRow;
  int Mode;
  bool Oscillate;
  
private:
  int CurrentFrame;
  
  int FrameInc;
  

  int FrameRate;
  long OldTime;

};

#endif
