#ifndef GBOMBER_HPP
#define GBOMBER_HPP

#include "GEntity.hpp"

enum {
  STATE_ALIVE,
  STATE_DYING,
  STATE_DEAD
};

class GBomber : public GEntity {
public:
  GBomber();
  ~GBomber();
  static std::vector<GBomber*> BomberList;

  virtual bool OnLoad();
  virtual void OnLoop();
  virtual void OnRender(SDL_Surface* SurfDisplay);
  virtual void OnCleanup();
  virtual void OnAnimate();
  virtual bool OnCollision(GEntity* Entity);  

  virtual bool PosValid(int NewX, int NewY);
  virtual bool PosValidEntity(GEntity* Entity, int NewX, int NewY);
  //virtual bool PosValidBomb(CBomb* Entity, int NewX, int NewY);
  virtual bool PosValidTile(int* Tile);
  virtual bool IsHit(GEntity* entity);


  void PlaceBomber(int x, int y);
  void PlaceBomber(int playerNum); // players 1 to 8 (or maybe more?)

  void PlaceBomb();
  void Die();

  // int ColInnerX;
  // int ColInnerW;
  // int ColInnerY;
  // int ColInnerH;
  int HitX;
  int HitY;
  int HitW;
  int HitH;

  static int Bombers;
  int BomberID;
  int BomberState;
  bool Alive;

  int BombsPlaced;
  int BombsMax;
  int BlastRadius;
  //CBomb* LastBomb;

  static SDL_Surface* SurfBomb;
  static void CheckVictory();

};

#endif
