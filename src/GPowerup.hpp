#ifndef GPOWERUP_HPP
#define GPOWERUP_HPP

#include "GEntity.hpp"

enum {
  POWERUP_BLAST,
  POWERUP_BOMB
};

class GPowerup : public GEntity {
public:
  GPowerup();
  int PowerupType;
  static std::vector<GPowerup*> PowerupList;

  virtual bool OnLoad();
  virtual void OnLoop();
  virtual void OnRender(SDL_Surface* SurfDisplay);
  virtual void OnCleanup();
  virtual void OnAnimate();
  virtual bool OnCollision(GEntity* Entity); 

private:
  static int PowerupsTotal;
};

#endif
