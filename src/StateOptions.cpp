#include "StateOptions.hpp"
#include "StateManager.hpp"
#include "GSurface.hpp"
#include "MenuButton.hpp"
#include "MenuOption.hpp"
#include "MenuValue.hpp"
#include "MenuBoolOption.hpp"

StateOptions StateOptions::Instance;

StateOptions::StateOptions() {
}

void Input(MirageApp* app, void* pData) {  
  StateManager::SetActiveState(APPSTATE_INPUT);
}

void MainMenu(MirageApp* app, void* pData) {
  StateManager::SetActiveState(APPSTATE_MENU);
}


void StateOptions::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode){
  mMenuManager->OnKeyUp(sym, mod, Unicode);
}

void StateOptions::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode){
 if (OldTime + 250 > SDL_GetTicks()) {
    return;
  }
  
  OldTime = SDL_GetTicks(); 
  mMenuManager->OnKeyDown(sym, mod, Unicode);  
}

void StateOptions::OnLButtonDown(int mX, int mY){
  mMenuManager->OnLButtonDown(mX, mY);
}
void StateOptions::OnRButtonDown(int mX, int mY) {  
  mMenuManager->OnRButtonDown(mX, mY);
}
void StateOptions::OnMButtonDown(int mX, int mY) {  
  mMenuManager->OnMButtonDown(mX, mY);
}

void StateOptions::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
  mMenuManager->OnMouseMove(mX, mY, relX, relY, Left, Right, Middle);
}


void StateOptions::Activate() {
  OldTime = SDL_GetTicks();
  mMenuManager = new MenuManager();
  App = StateManager::GetApp();
  mMenuManager->RegisterApp(App);
  //mMenuManager->Align(MM_CENTEREDOPTIONS);
  // mMenuManager->SetFont(GSurface::FontRegular);
  App->Log << "----------------------------------------" << std::endl;
  App->Log << "Activating entries" << std::endl;  

  mMenuManager->AddEntry(new MenuBoolOption("Full Screen:"));  
  mMenuManager->CurEntry()->SetSelect([&](MirageApp* App, void* ){ StateManager::SetActiveState(APPSTATE_INPUT);});    
  // mMenuManager->AddEntry(new MenuButton("Music:"));
  // mMenuManager->CurEntry()->OnSelect = Input; 
  // mMenuManager->AddEntry(new MenuButton("Sounds:"));
  // mMenuManager->CurEntry()->OnSelect = Input; 
  mMenuManager->AddEntry(new MenuButton("Configure input"));
  mMenuManager->CurEntry()->SetSelect([&](MirageApp* App, void* ){ StateManager::SetActiveState(APPSTATE_INPUT);});    

  mMenuManager->AddEntry(new MenuButton("Back"));
  mMenuManager->CurEntry()->SetSelect([](MirageApp* App, void*){ StateManager::SetActiveState(APPSTATE_MENU);});
  
  mMenuManager->SetEntry(0);
  
}

void StateOptions::Deactivate() {
  mMenuManager->Cleanup();
  delete mMenuManager;
}

void StateOptions::Loop() {
}

void StateOptions::Render(SDL_Surface* SurfDisplay) {
  mMenuManager->Render(SurfDisplay);  
}

StateOptions* StateOptions::GetInstance() {
  return &Instance;
}
