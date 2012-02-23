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

  virtual bool Load();
  virtual void Loop();
  virtual void Animate();
  virtual void Render(SDL_Surface* SurfDisplay);
  virtual void Cleanup();

  virtual bool OnCollision(GEntity* Entity); 

private:
  static int PowerupsTotal;
};

#endif
