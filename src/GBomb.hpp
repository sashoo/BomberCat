#ifndef GBOMB_HPP
#define GBOMB_HPP

#include "GEntity.hpp"
#include "STimer.hpp"

class GBomber;

enum {
  BOMB_STATE_TICKING,
  BOMB_STATE_EXPLODING,
  BOMB_STATE_EXPLODED
};

class GBomb : public STimer, public GEntity {
public:
  GBomb() ;
  static std::vector <GBomb*> BombList;
  
  virtual bool OnLoad();
  virtual void OnLoop();
  virtual bool OnTimeOut();
  virtual void OnRender(SDL_Surface* SurfDisplay);
  virtual void OnCleanup();
  virtual void OnAnimate();
  virtual bool OnCollision(GEntity* Entity);  

  void PlaceFlames();
  void Explode();
  void CheckDir(int cx, int cy, int alttype);
  int Owner;
  bool JustPlaced;
  int State;
  int ChainedFrom;
  GBomber* Bomber;
private:
  static int BombsTotal;
  
};

#endif
