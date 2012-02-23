#ifndef GENTITY_HPP
#define GENTITY_HPP

#include <vector>

#include "GArea.hpp"
#include "GAnimation.hpp"
#include "GCamera.hpp"
#include "GFPS.hpp"
#include "GSurface.hpp"
#include <string>
#include "MirageApp.hpp"
#include "GInput.hpp"

class MirageApp;

enum {
  ENTITY_TYPE_GENERIC = 0,
  ENTITY_TYPE_BOMBER_AI,
  ENTITY_TYPE_BOMBER_P,
  ENTITY_TYPE_BOMB,
  ENTITY_TYPE_FLAME,
  ENTITY_TYPE_POWERUP,
  ENTITY_TYPE_MONSTER
};

enum {
  ENTITY_FLAG_NONE    = 0, 
  ENTITY_FLAG_GHOST   = 0x00000001,
  ENTITY_FLAG_MAPONLY = 0x00000002
};

// enum {
//   ENTITY_STATE_ALIVE = 0,
//   ENTITY_STATE_DYING,
//   ENTITY_STATE_DEAD 
// };

class GEntity {
public:
  GEntity();
  virtual ~GEntity();
  static std::vector<GEntity*> EntityList;
  static MirageApp* App;
  
  virtual bool Load(std::string name, char* File, int width, int height, int maxFrames);
  virtual void Loop();
  virtual void Render(SDL_Surface* SurfDisplay);  
  virtual void Cleanup();
  virtual void Animate();

  virtual bool OnCollision(GEntity* Entity);
  virtual void DeleteObject();
  static void RegisterApp(MirageApp* app);

  void Move(float MoveX, float MoveY);
  void StopMove();
  bool Collides(int oX, int oY, int oW, int oH);
  bool Collides(int oX, int oY, int oW, int oH, float& depthX, float& depthY);
  bool Collides(GEntity* entity);
 
  std::string Name;

  float X;
  float Y;
  float cX;
  float cY;
  int Width;
  int Height;
  bool MoveLeft;
  bool MoveRight;
  bool MoveUp;
  bool MoveDown; 
  //int AnimState;

  int Type;
  bool Enabled;
  int Flags;
  //int State; 

  float MaxSpeedX;
  float MaxSpeedY;

protected:
  static int Entities;
  int ID;
  
  GAnimation AnimControl;
  SDL_Surface* SurfEntity;  

  float SpeedX;
  float SpeedY;
  float AccelX;
  float AccelY;

  int CurrentFrameCol;
  int CurrentFrameRow;

  int ColX;
  int ColY;
  int ColW;
  int ColH;

  virtual bool PosValid(int NewX, int NewY);
  virtual bool PosValidTile(int* Tile);
  virtual bool PosValidEntity(GEntity* Entity, int NewX, int NewY);

  friend class GBomber;
};

class GEntityCol {
public: 
  static std::vector<GEntityCol> EntityColList;
  GEntity* EntityA;
  GEntity* EntityB;
  GEntityCol();
};

#endif
