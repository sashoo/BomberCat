#include "StateInput.hpp"
#include "StateManager.hpp"
#include "GSurface.hpp"
#include "MenuButton.hpp"
#include "MenuDevice.hpp"
#include "MenuValue.hpp"
#include "StateMenu.hpp"

StateInput StateInput::Instance;

StateInput::StateInput() {
  KeyInputHandle = NULL;
  JoyInputHandle = NULL;
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

  // std::vector<std::string> opts;
  // opts.push_back("Key-1");
  // opts.push_back("Key-2");
  // opts.push_back("Key-3");
  // opts.push_back("Key-4");
  // opts.push_back("Joy-1");
  // opts.push_back("Joy-2");
  // opts.push_back("Joy-3");
  // opts.push_back("Joy-4");



  MenuDevice* dev = new MenuDevice("Device Label:");
  mMenuManager->AddEntry(dev);
  mMenuManager->CurEntry()->OnSelect = Keyboard;   

  MenuValue* value = new MenuValue("Device Name:", "###");
  mMenuManager->AddEntry(value);
  mMenuManager->CurEntry()->OnSelect = Keyboard; 
  dev->AddValue(value);
  
  value = new MenuValue("Up:", "###");
  mMenuManager->AddEntry(value);
  mMenuManager->CurEntry()->OnSelect = Keyboard; 
  dev->AddValue(value);

  value = new MenuValue("Down:", "###");
  mMenuManager->AddEntry(value);
  mMenuManager->CurEntry()->OnSelect = Keyboard; 
  dev->AddValue(value);

  value = new MenuValue("Left:", "###");
  mMenuManager->AddEntry(value);
  mMenuManager->CurEntry()->OnSelect = Keyboard; 
  dev->AddValue(value);

  value = new MenuValue("Right:", "atata");
  mMenuManager->AddEntry(value);
  mMenuManager->CurEntry()->OnSelect = Keyboard; 
  dev->AddValue(value);

  value = new MenuValue("Bomb:", "atata");
  mMenuManager->AddEntry(value);
  mMenuManager->CurEntry()->OnSelect = Keyboard; 
  dev->AddValue(value); 

  mMenuManager->AddEntry(new MenuButton("Back"));
  mMenuManager->CurEntry()->OnSelect = Options;

  dev->AssignDevice();
  dev->UpdateValues();

  dev = NULL; // lol
  value = NULL;
  
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
