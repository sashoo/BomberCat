#ifndef STATEGAME_HPP
#define STATEGAME_HPP

#include "IState.hpp"

#include "GArea.hpp"
#include "GCamera.hpp"
#include "GEntity.hpp"
//#include "GPlayer.hpp"
//#include "GAI.hpp"

class StateGame; // forward declaration for UDPSocket

#include "UDPSocket.hpp"

class MirageApp;

class StateGame : public IState {
private:
  StateGame();
  static StateGame Instance; 
  //CPlayer* p1;
  //CPlayer p2; 
 
  bool CameraSwitch;
  Uint32 OldTime;
  Uint32 GameStartTime;
  Uint32 GameTime;
public:

  void Activate();
  void Deactivate();
  void Loop();
  void Render(SDL_Surface* SurfDisplay);
  void SetTerminal(bool terminal);

  void InitNetwork();
  void InitBombers();
  bool InitLevel();

  void CleanupFlames();
  void CleanupBombs();
  void CleanupBombers();
  void CleanupPowerups();
  //Unloads Decor as well since they share the same file
  void CleanupTiles(); 

  void LoopFlames();
  void LoopBombs();
  void LoopDecor();
  void LoopPowerups();
  void LoopBombers();
  void LoopSockets();

  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode); 

  void OnLButtonDown(int mX, int mY);
  void OnRButtonDown(int mX, int mY);
  void OnMButtonDown(int mX, int mY);

  void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value); 
  void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value); 
  void OnJoyButtonDown(Uint8 which, Uint8 button);  

  //Counts time since StateGame was activated, milliseconds
  Uint32 GetGameTime() const {return GameTime;}

  GArea * GetGArea() {return &GArea::AreaControl;}

  int CurLayer;
  int CurTileType;
  int CurJoystick;
  int NetMode;

  UDPSocket *Socket;

  static StateGame* GetInstance();
};


#endif
