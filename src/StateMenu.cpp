#include "StateMenu.hpp"
#include "GSurface.hpp"
#include "StateManager.hpp"
#include "MirageApp.hpp"
#include "MenuButton.hpp"

StateMenu StateMenu::Instance;

void PlayGame(MirageApp* app, void* pData) {  
  StateManager::SetActiveState(APPSTATE_GAME);
}

void DoNothing(MirageApp* app, void* pData) {   
}

void Options(MirageApp* app, void* pData) {
  StateManager::SetActiveState(APPSTATE_OPTIONS);
}

void Credits(MirageApp* app, void* pData) {
  // if (NULL != app)
  StateManager::SetActiveState(APPSTATE_CREDITS);
}

void Exit(MirageApp* app, void* pData) {
  StateManager::SetActiveState(APPSTATE_NONE);  
}

StateMenu::StateMenu(){  
}

void StateMenu::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode) {
   if (OldTime + 250 > SDL_GetTicks()) {
    return;
  }
  
  OldTime = SDL_GetTicks(); 
  mMenuManager->OnKeyDown(sym, mod, Unicode);
}

void StateMenu::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode) {
  mMenuManager->OnKeyUp(sym, mod, Unicode);
}

void StateMenu::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
  mMenuManager->OnMouseMove(mX, mY, relX, relY, Left, Right, Middle);
}

void StateMenu::OnLButtonDown(int mX, int mY) {
  mMenuManager->OnLButtonDown(mX, mY);
}
void StateMenu::OnRButtonDown(int mX, int mY) {  
  mMenuManager->OnRButtonDown(mX, mY);
}
void StateMenu::OnMButtonDown(int mX, int mY) {  
  mMenuManager->OnMButtonDown(mX, mY);
}

    
void StateMenu::Activate() {
  OldTime = SDL_GetTicks();
  mMenuManager = new MenuManager();
  App = StateManager::GetApp();
  mMenuManager->RegisterApp(App);
  // mMenuManager->SetFont(GSurface::FontRegular);
  App->Log << "----------------------------------------" << std::endl;
  App->Log << "Activating entries" << std::endl;

  mMenuManager->AddEntry(new MenuButton("Offline game"));
  mMenuManager->CurEntry()->SetSelect([&](MirageApp* app, void* pData){
    App->NetMode = GAME_LOCAL;
    StateManager::SetActiveState(APPSTATE_CONFIG);
  });
  mMenuManager->AddEntry(new MenuButton("Host game"));
  mMenuManager->CurEntry()->SetSelect([&](MirageApp* app, void* pData){});
  mMenuManager->AddEntry(new MenuButton("Join game"));
  mMenuManager->CurEntry()->SetSelect([&](MirageApp* app, void* pData){});
  mMenuManager->AddEntry(new MenuButton("Options"));
  mMenuManager->CurEntry()->SetSelect([&](MirageApp* app, void* pData){StateManager::SetActiveState(APPSTATE_OPTIONS);});
  mMenuManager->AddEntry(new MenuButton("Credits"));
  mMenuManager->CurEntry()->SetSelect([&](MirageApp* app, void* pData){StateManager::SetActiveState(APPSTATE_CREDITS);});
  mMenuManager->AddEntry(new MenuButton("Quit"));
  mMenuManager->CurEntry()->SetSelect([&](MirageApp* app, void* pData){StateManager::SetActiveState(APPSTATE_NONE);});
  mMenuManager->SetEntry(0);
}

void StateMenu::Deactivate() {   
  mMenuManager->Cleanup();

  delete mMenuManager;  
}

void StateMenu::Loop() {
  //mMenuManager->OnLoop();
}

void StateMenu::Render(SDL_Surface* SurfDisplay) {  
  mMenuManager->Render(SurfDisplay);
}

StateMenu* StateMenu::GetInstance() {
  return &Instance;
}
