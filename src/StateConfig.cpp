#include "StateManager.hpp"

#include "StateConfig.hpp"

#include "GSurface.hpp"

#include "MenuButton.hpp"
#include "MenuTable.hpp"

StateConfig StateConfig::Instance;

StateConfig::StateConfig() {
  
}

void StateConfig::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode) {
   if (OldTime + 250 > SDL_GetTicks()) {
    return;
  }

   switch(sym) {
   case SDLK_ESCAPE: 
     StateManager::SetActiveState(APPSTATE_MENU);  
     //OnExit();
     break;
   default:
     StateManager::SetActiveState(APPSTATE_GAME);
   }
    
   

   
   
}

void StateConfig::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode) {
 
}

void StateConfig::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
  
  //mConfigManager->OnMouseMove(mX, mY, relX, relY, Left, Right, Middle);
}

void StateConfig::OnLButtonDown(int mX, int mY) {
  if (DotInRect(mX, mY, ButtonAdd->GetRect()))
    ButtonAdd->OnSelect(NULL, NULL);
  if (DotInRect(mX, mY, ButtonRemove->GetRect()))
    ButtonRemove->OnSelect(NULL, NULL);
  //mConfigManager->OnLButtonDown(mX, mY);
}
void StateConfig::OnRButtonDown(int mX, int mY) {  
  //mConfigManager->OnRButtonDown(mX, mY);
}
void StateConfig::OnMButtonDown(int mX, int mY) {  
  //mConfigManager->OnMButtonDown(mX, mY);
}

void StateConfig::Activate() {
  OldTime = SDL_GetTicks();
  App = StateManager::GetApp();

  PlayerTable = new MenuTable();
  PlayerTable->SetPosition(0.0f, 200.0f);
  PlayerTable->RegisterApp(App);  
  PlayerTable->Add();
  PlayerTable->Add();
  // MenuTableEntry entry;
  // entry.Number = PlayerTable->TotalPlayers;
  // entry.InputType = PlayerTable->TotalPlayers;
  // entry.Nickname = "Woof";
  // entry.RegisterApp(App);
  // PlayerTable->Entries.push_back(entry);
  // PlayerTable->TotalPlayers++;
  // entry.Number = PlayerTable->TotalPlayers;
  // entry.InputType = PlayerTable->TotalPlayers;

  // PlayerTable->Entries.push_back(entry);
  // PlayerTable->TotalPlayers = 2;
  PlayerTable->SetPosition(0, 32);
  PlayerTable->Init();

  
  ButtonAdd = new MenuButton("+");  
  ButtonAdd->RegisterApp(App);
  ButtonAdd->Init();
  ButtonAdd->SetOrigin(ORIGIN_TL);
  ButtonAdd->SetPosition(0 , 0);
  ButtonAdd->SetSelect([&](MirageApp* app, void* pData){PlayerTable->Add();});
  
  
  ButtonRemove = new MenuButton("-");
  ButtonRemove->RegisterApp(App);
  ButtonRemove->Init();
  ButtonRemove->SetOrigin(ORIGIN_TL);
  ButtonRemove->SetPosition(32 , 0);
  ButtonRemove->SetSelect([&](MirageApp* app, void* pData){PlayerTable->Remove();});

}

void StateConfig::Deactivate() {   
  ButtonAdd->Cleanup();
  delete ButtonAdd;

  ButtonRemove->Cleanup();
  delete ButtonRemove;

  PlayerTable->Cleanup();
  delete PlayerTable;
  
}

void StateConfig::Loop() {
  //mConfigManager->OnLoop();
}

void StateConfig::Render(SDL_Surface* SurfDisplay) {  
  ButtonAdd->Render(SurfDisplay);
  ButtonRemove->Render(SurfDisplay);
  PlayerTable->Render(SurfDisplay);
  //mConfigManager->Render(SurfDisplay);
}

StateConfig* StateConfig::GetInstance() {
  return &Instance;
}
