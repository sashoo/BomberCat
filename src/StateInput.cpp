#include "StateInput.hpp"
#include "StateManager.hpp"
#include "GSurface.hpp"
#include "MenuButton.hpp"
#include "StateMenu.hpp"

StateInput StateInput::Instance;

StateInput::StateInput() {
}

void Keyboard(MirageApp* app, void* pData) {  
  //StateManager::SetActiveState(APPSTATE_INPUT);
}

void Joystick(MirageApp* app, void* pData) {
  //StateManager::SetActiveState(APPSTATE_MENU);
}


void StateInput::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode){
  mMenuManager->OnKeyUp(sym, mod, Unicode);
}

void StateInput::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode){
 if (OldTime + 250 > SDL_GetTicks()) {
    return;
  }
  
  OldTime = SDL_GetTicks(); 
  mMenuManager->OnKeyDown(sym, mod, Unicode);  
}



void StateInput::OnLButtonDown(int mX, int mY){
  mMenuManager->OnLButtonDown(mX, mY);
}
void StateInput::OnRButtonDown(int mX, int mY) {  
  mMenuManager->OnRButtonDown(mX, mY);
}
void StateInput::OnMButtonDown(int mX, int mY) {  
  mMenuManager->OnMButtonDown(mX, mY);
}

void StateInput::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
  mMenuManager->OnMouseMove(mX, mY, relX, relY, Left, Right, Middle);
}


void StateInput::Activate() {
  OldTime = SDL_GetTicks();
  mMenuManager = new MenuManager();
  App = StateManager::GetApp();
  mMenuManager->RegisterApp(App); 
  App->Log << "----------------------------------------" << std::endl;
  App->Log << "Activating entries" << std::endl;

  mMenuManager->AddEntry(new MenuButton("Configure keyboard 1"));
  mMenuManager->CurEntry()->OnSelect = Keyboard; 
  mMenuManager->AddEntry(new MenuButton("Configure keyboard 2"));
  mMenuManager->CurEntry()->OnSelect = Keyboard; 
  mMenuManager->AddEntry(new MenuButton("Configure keyboard 3"));
  mMenuManager->CurEntry()->OnSelect = Keyboard; 
  mMenuManager->AddEntry(new MenuButton("Configure keyboard 4"));
  mMenuManager->CurEntry()->OnSelect = Keyboard; 
  mMenuManager->AddEntry(new MenuButton("Configure joystick 1"));
  mMenuManager->CurEntry()->OnSelect = Joystick; 
  mMenuManager->AddEntry(new MenuButton("Configure joystick 2"));
  mMenuManager->CurEntry()->OnSelect = Joystick; 
  mMenuManager->AddEntry(new MenuButton("Configure joystick 3"));
  mMenuManager->CurEntry()->OnSelect = Joystick; 
  mMenuManager->AddEntry(new MenuButton("Configure joystick 4"));
  mMenuManager->CurEntry()->OnSelect = Joystick; 

  mMenuManager->AddEntry(new MenuButton("Back"));
  mMenuManager->CurEntry()->OnSelect = Options;
  
  mMenuManager->SetEntry(0);
  
}

void StateInput::Deactivate() {
  mMenuManager->Cleanup();
  delete mMenuManager;
}

void StateInput::Loop() {
}

void StateInput::Render(SDL_Surface* SurfDisplay) {
  mMenuManager->Render(SurfDisplay);  
}

StateInput* StateInput::GetInstance() {
  return &Instance;
}
