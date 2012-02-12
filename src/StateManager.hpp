#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include <string>
#include "IState.hpp"
#include "MirageApp.hpp"

enum {
  APPSTATE_NONE,
  APPSTATE_INTRO,
  APPSTATE_MENU,
  APPSTATE_OPTIONS,
  APPSTATE_GAME,
  APPSTATE_INPUT,
  APPSTATE_CREDITS
};

class MirageApp;
class IState;

class StateManager {
private:  
  static IState* ActiveState;
  static MirageApp* App;    
public:  
  static void OnEvent(SDL_Event* Event);
  static void OnLoop();
  static void OnRender(SDL_Surface* SurfDisplay);
  static void SetActiveState(int stateID);
  static IState* GetActiveState();
  static void RegisterApp(MirageApp* app);      
  static MirageApp* GetApp();
};

#endif
