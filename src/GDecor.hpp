#ifndef GDECOR_HPP
#define GDECOR_HPP

#include "GEntity.hpp"

enum {
  BURN_WALL,
  BURN_PUP
};

class GDecor : public GEntity {
private:
  static int DecorsTotal;

public:
  GDecor(int x, int y);
  int DecorType;
  static std::vector<GDecor*> DecorList;

  virtual bool Load();
  virtual void Loop();
  virtual void Animate();  
  virtual void Render(SDL_Surface* SurfDisplay);
  virtual void Cleanup();
 
};

#endif
