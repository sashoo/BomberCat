#ifndef GAI_HPP
#define GAI_HPP

#include "GEntity.hpp"
#include "GBomber.hpp"
#include "GPath.hpp"

enum {
  AI_GOING = 0,
  AI_IDLE
};

class GAI : public GBomber {
public:
  GAI();
  ~GAI();
  bool OnLoad();
  void OnLoop();
  void OnRender(SDL_Surface* SurfDisplay);
  void OnCleanup();
  void OnAnimate();
  bool OnCollision(GEntity* Entity);

  void PrintPath();
  void UsePath();
  void GoTile(int x, int y);

  GPath PathManager;
  
private:
  int OldTime;
  int AItask;
  bool FirstStep;

};

#endif
