#ifndef GBOMBER_HPP
#define GBOMBER_HPP

#include "GEntity.hpp"
#include "NetConnection.hpp"
#include "NetChannel.hpp"

struct Input;

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
  static GBomber* Create();

  virtual void Loop();  
  virtual void Render(SDL_Surface* SurfDisplay);
  virtual void Cleanup();
  virtual void Animate();

  virtual bool OnCollision(GEntity* Entity);  

  virtual bool PosValid(int NewX, int NewY);
  virtual bool PosValidEntity(GEntity* Entity, int NewX, int NewY);
  //virtual bool PosValidBomb(CBomb* Entity, int NewX, int NewY);
  virtual bool PosValidTile(int Tile);
  virtual bool IsHit(GEntity* entity);

  Input* InputHandle;

  void PlaceBomber(int x, int y);
  void PlaceBomberByNum(int num, int bombers); // players 1 to 8 (or maybe more?)

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
  int ColorID;
  int BomberState;
  bool Alive;

  int BombsPlaced;
  int BombsMax;
  int BlastRadius;
  //CBomb* LastBomb;
  
  // pointers to owner connections
  // _owner_ client <---> server
  NetConnection *netConnection;
  NetChannel_GBomber *netChannel;
  
  // sends move request to the server
  void ServerMove(bool up, bool down, bool left, bool right);

  static SDL_Surface* SurfBomb;
  static void CheckVictory();
};

#endif
