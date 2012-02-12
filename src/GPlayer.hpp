#ifndef GPLAYER_HPP
#define GPLAYER_HPP

#include "GEntity.hpp"
#include "GBomber.hpp"

class GPlayer : public GBomber {
public:
  GPlayer();
  ~GPlayer();
  bool OnLoad();
  void OnLoop();
  void OnRender(SDL_Surface* SurfDisplay);
  void OnCleanup();
  void OnAnimate();
  bool OnCollision(GEntity* Entity);
  
  void SetDefaultKeys();
  //void SetKeys(); 
  
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode); 

  void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value); 
  void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value); 
  void OnJoyButtonDown(Uint8 which, Uint8 button);

  std::map<std::string, int> Keys;
private:
  static int Players;
  int OldTime;
  int PlayerID;

};

#endif
