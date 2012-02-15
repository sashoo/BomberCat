#ifndef GFLAME_HPP
#define GFLAME_HPP

#include "GEntity.hpp"
#include "STimer.hpp"
#include "GBomber.hpp"

enum {
  FLAME_CENTER=0,  
  FLAME_VERTICAL,   
  FLAME_HORIZONTAL, 
  FLAME_UP,         
  FLAME_RIGHT,      
  FLAME_DOWN,      
  FLAME_LEFT      
};  

enum { 
  FLAME_CHAIN_UP    = 0x00000001,
  FLAME_CHAIN_RIGHT = 0x00000002,
  FLAME_CHAIN_DOWN  = 0x00000004,
  FLAME_CHAIN_LEFT  = 0x00000008
};


const int MaxFlamePower = 8;

class GFlame : public STimer, public GEntity {  
public:
  GFlame();
  static std::vector<GFlame*> FlameList;

  virtual bool OnLoad();
  virtual void OnLoop();
  virtual bool OnTimeOut();
  virtual void OnRender(SDL_Surface* SurfDisplay);
  virtual void OnCleanup();
  virtual void OnAnimate();
  virtual bool OnCollision(GEntity* Entity);  

  //void CheckTouch();
  void CheckBombs();
  void CheckBombers();
  bool CheckPowerups(); // true if hits

  GBomber* Bomber;
  int FlameType;
  int FlamePower;
  int Frame;
  int ChainDirection;

private:
  static int FlamesTotal; 
  
};

#endif
