#ifndef STIMER_HPP
#define STIMER_HPP

#include <SDL.h>
#include <vector>

enum {
  TIMER_STATE_STOPPED = 0,
  TIMER_STATE_PAUSED,
  TIMER_STATE_TICKING,
  TIMER_STATE_FINISHED
};

class STimer {
public:
  static std::vector<STimer*> TimerList; 

  STimer(Uint32 timeMax = 0, Uint32 timePassed = 0, bool loop = false);

  Uint32 GetRelTimePassed();
  Uint32 GetAbsTimePassed();
  Uint32 GetTimeMax();
  
  void Start();
  void Pause();
  void Stop();

  void SetLoop(bool loop);

  void OnLoop();
  virtual bool OnTimeOut();

  int TimerState;
  bool Loop;

  Uint32 AbsoluteStartTime;
  Uint32 TimePassed;
  Uint32 TimeMax;
  

};

#endif
