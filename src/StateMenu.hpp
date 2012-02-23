#ifndef STATEMENU_HPP
#define STATEMENU_HPP

#include "IState.hpp"
#include "MenuManager.hpp"

class MirageApp;
class MenuManager;

class StateMenu : public IState {
private:
  StateMenu();  
  static StateMenu Instance;   
  MirageApp* App;
  MenuManager* mMenuManager;
  Uint32 OldTime;
public:
  // Core functions
  void Activate();
  void Deactivate();
  void Loop();
  void Render(SDL_Surface* SurfDisplay);

  // Input handling  
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnLButtonDown(int mX, int mY);  
  void OnRButtonDown(int mX, int mY);  
  void OnMButtonDown(int mX, int mY); 
  void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);

  // Get state instance
  static StateMenu* GetInstance();
};

void Options(MirageApp* app, void* pData);
#endif
