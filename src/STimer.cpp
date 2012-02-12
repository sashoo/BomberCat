#include "STimer.hpp"

std::vector<STimer*> STimer::TimerList;

STimer::STimer(Uint32 timeMax, Uint32 timePassed, bool loop){
  TimeMax = timeMax;
  TimePassed = timePassed;
  TimerState = TIMER_STATE_STOPPED;
  Loop = loop;
  TimerList.push_back(this);
}

Uint32 STimer::GetRelTimePassed() {
  return TimePassed;
}

Uint32 STimer::GetAbsTimePassed() {
  return TimePassed + AbsoluteStartTime;
}

Uint32 STimer::GetTimeMax() {
  return TimeMax;
}

void STimer::Start() {  
  if (TIMER_STATE_STOPPED == TimerState || TIMER_STATE_FINISHED) {   
    AbsoluteStartTime = SDL_GetTicks();
    TimePassed = 0;    
  }
  if (TIMER_STATE_PAUSED == TimerState || TIMER_STATE_TICKING) {
    // Nothing to change;    
  }
  TimerState = TIMER_STATE_TICKING;
}

void STimer::Pause() {
  TimerState = TIMER_STATE_PAUSED;
}

void STimer::Stop() {
  TimerState = TIMER_STATE_STOPPED;
  TimePassed = 0;
}

void STimer::SetLoop(bool loop) {
  Loop = loop;
}

void STimer::OnLoop() {
  switch (TimerState) {
    
  case TIMER_STATE_TICKING: {
    Uint32 elapsed = SDL_GetTicks()-AbsoluteStartTime;
    TimePassed = elapsed;
    if (TimePassed >= TimeMax) {
      if (Loop) {
	// not zero because we will most likely have
	// TimePassed some msecs higher than TimeMax
	// This extra time should be taken into account
	TimePassed = TimePassed - TimeMax;
	AbsoluteStartTime = SDL_GetTicks();
	OnTimeOut();
      }
      else {
	TimePassed = 0;
	TimerState = TIMER_STATE_FINISHED;

      }
    }
    break;
  }

  case TIMER_STATE_FINISHED:
    	OnTimeOut();
	break;

  case TIMER_STATE_PAUSED:   
  case TIMER_STATE_STOPPED:
  default:
    break;
  }
}

bool STimer::OnTimeOut() {
  return true;
}
  

