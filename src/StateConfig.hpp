#ifndef STATECONFIG_HPP
#define STATECONFIG_HPP

#include "IState.hpp"

class MirageApp;
class MenuTable;
class MenuButton;

class StateConfig : public IState {
private:
  
  MirageApp* App;
  //MenuManager* mMenuManager;
  Uint32 OldTime;
public:
  StateConfig();
  static StateConfig Instance;
  // Core Functions
  void Activate();
  void Deactivate();
  void Loop();
  void Render(SDL_Surface* SurfDisplay);

  MenuTable*  PlayerTable;
  MenuButton* ButtonAdd;
  MenuButton* ButtonRemove;

  //Input Handling
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnLButtonDown(int mX, int mY);  
  void OnRButtonDown(int mX, int mY);  
  void OnMButtonDown(int mX, int mY); 
  void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
  
  // Get state instance
  static StateConfig* GetInstance();
};

#endif
