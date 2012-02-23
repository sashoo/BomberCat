#include "StateManager.hpp"
#include "StateIntro.hpp"
#include "StateGame.hpp"
#include "StateMenu.hpp"
#include "StateCredits.hpp"
#include "StateOptions.hpp"
#include "StateInput.hpp"

IState* StateManager::ActiveState = 0;
MirageApp* StateManager::App = 0;

void StateManager::OnEvent(SDL_Event* Event) {
  if (ActiveState) ActiveState->OnEvent(Event);
}

void StateManager::OnLoop() {
  if (ActiveState) ActiveState->Loop();
  else App->OnExit();
}

void StateManager::OnRender(SDL_Surface* SurfDisplay) {
  if (ActiveState) ActiveState->Render(SurfDisplay);
}

void StateManager::SetActiveState(int stateID) {
  if (ActiveState) ActiveState->Deactivate();

  if(stateID == APPSTATE_NONE )    ActiveState = 0;
  if(stateID == APPSTATE_INTRO)    ActiveState = StateIntro::GetInstance();
  if(stateID == APPSTATE_MENU )    ActiveState = StateMenu::GetInstance();
  if(stateID == APPSTATE_OPTIONS)  ActiveState = StateOptions::GetInstance();
  if(stateID == APPSTATE_INPUT)    ActiveState = StateInput::GetInstance();
  if(stateID == APPSTATE_GAME )    ActiveState = StateGame::GetInstance(); 
  if(stateID == APPSTATE_CREDITS ) ActiveState = StateCredits::GetInstance();
  
  if (ActiveState) ActiveState->Activate();
}

IState* StateManager::GetActiveState() {
  return ActiveState;
}

void StateManager::RegisterApp(MirageApp* app) {
  App = app;
}

MirageApp* StateManager::GetApp(){
  return App;
}
  
