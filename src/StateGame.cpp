#include <cassert>

#include "StateGame.hpp"
#include "StateManager.hpp"
#include "MirageApp.hpp"
#include "GBomb.hpp"
#include "GFlame.hpp"
#include "GDecor.hpp"
#include "GPowerup.hpp"
#include "GSurface.hpp"
#include <algorithm>

StateGame StateGame::Instance;

StateGame::StateGame() {
  OldTime = 0;
  CameraSwitch = false;
  CurTileType = 1;
  CurLayer = 2;
  CurJoystick = 0;
  NetMode = GAME_LOCAL;
  GameStartTime = SDL_GetTicks();
  GameTime = 0;
}

void StateGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode){
  //changeable player controls here, in ifs
  //switch-case if for invariant controls  
  
  App->Key1.OnKeyDown(sym);
  App->Key2.OnKeyDown(sym);
  App->Key3.OnKeyDown(sym);
  App->Key4.OnKeyDown(sym);

  // std::vector<GBomber*>::iterator bomber = GBomber::BomberList.begin();
  // while (bomber != GBomber::BomberList.end()) {
  //   if (ENTITY_TYPE_BOMBER_AI == (*bomber)->Type) {
  //     bomber++;
  //     continue;
  //   }
  //   GPlayer* player = dynamic_cast<GPlayer*>(*bomber);
  //   if (NULL != player)
  //     player->OnKeyDown(sym, mod, Unicode);
  //   bomber++;
  // }
  //p1->OnKeyDown(sym, mod, Unicode);
  
  switch(sym) {
 
 // case SDLK_w: {
 //   GCamera::CameraControl.OnMove(0, -5);
 //   break;
 // }

 // case SDLK_s: {
 //   GCamera::CameraControl.OnMove(0, 5);
 //   break;
 // }

 // case SDLK_a: {
 //   GCamera::CameraControl.OnMove(-5, 0);
 //   break;
 // }

 // case SDLK_d: {
 //   GCamera::CameraControl.OnMove(5, 0);
 //   break;
 // }

 case SDLK_1: {
   if (OldTime + 150 > SDL_GetTicks()) 
     return;

   OldTime = SDL_GetTicks();
   GArea::AreaControl.bRenderFore = !GArea::AreaControl.bRenderFore;
   break;
 }

 case SDLK_2: {
   if (OldTime + 150 > SDL_GetTicks()) 
     return;

   OldTime = SDL_GetTicks();
   GArea::AreaControl.bRenderCol = !GArea::AreaControl.bRenderCol;
   break;
 }

 case SDLK_3: {
   if (OldTime + 150 > SDL_GetTicks()) 
     return;

   OldTime = SDL_GetTicks();
   GArea::AreaControl.bRenderBack = !GArea::AreaControl.bRenderBack;
   break;
 }

 case SDLK_LEFTBRACKET: {
   if (OldTime + 150 > SDL_GetTicks()) 
     return;   

   OldTime = SDL_GetTicks();

   if (--CurTileType < 0)
     CurTileType = 255;
   break;
 }

case SDLK_RIGHTBRACKET: {
   if (OldTime + 150 > SDL_GetTicks()) 
     return;   

   OldTime = SDL_GetTicks();

   if (++CurTileType > 255)
     CurTileType = 0;
   break;
 } 
   
 case SDLK_c: {
   if (OldTime + 150 > SDL_GetTicks()) 
     return;

   OldTime = SDL_GetTicks();
   if (!CameraSwitch)
     GCamera::CameraControl.SetPos(GCamera::CameraControl.GetX(),
				   GCamera::CameraControl.GetY());
   else
     GCamera::CameraControl.SetPos(100, 100);
   CameraSwitch = !CameraSwitch;
   break;
 }

 case SDLK_F2: {
   if (OldTime + 150 > SDL_GetTicks()) 
     return;

   OldTime = SDL_GetTicks();
   GArea::AreaControl.Save();
   break;
 }

  case SDLK_ESCAPE: {
    StateManager::SetActiveState(APPSTATE_MENU);  
    //OnExit();
    break;
  }    
 
  default: {
  }

 }
}
//
void StateGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode){

  App->Key1.OnKeyUp(sym);
  App->Key2.OnKeyUp(sym);
  App->Key3.OnKeyUp(sym);
  App->Key4.OnKeyUp(sym);


  // std::vector<GBomber*>::iterator bomber = GBomber::BomberList.begin();
  // while (bomber != GBomber::BomberList.end()) {
  //   if (ENTITY_TYPE_BOMBER_AI == (*bomber)->Type) {
  //     bomber++;
  //     continue;
  //   }
  //   GPlayer* player = dynamic_cast<GPlayer*>(*bomber);
  //   if (NULL != player)
  //     player->OnKeyUp(sym, mod, Unicode);
  //   bomber++;
  // }
  
  // switch(sym)
  //{
  // case SDLK_LEFT: {
  //   p1.MoveLeft = false;
  //   break;
  // }
 
  // case SDLK_RIGHT: {
  //   p1.MoveRight = false;
  //   break;
  // }

 
  // default: {
  // }
  // }
}

void StateGame::OnLButtonDown(int mX, int mY) {
  if (NetMode != GAME_LOCAL) return;

  int x = mX + GCamera::CameraControl.GetX();
  int y = mY + GCamera::CameraControl.GetY();
  x /= TILE_SIZE;
  y /= TILE_SIZE;
  GArea::AreaControl.SetTile(x*TILE_SIZE, y*TILE_SIZE, CurTileType); 
}

void StateGame::OnRButtonDown(int mX, int mY) {
  int x = mX + GCamera::CameraControl.GetX();
  int y = mY + GCamera::CameraControl.GetY();
  x /= TILE_SIZE;
  y /= TILE_SIZE;

  // std::vector<GBomber*>::iterator bomber = GBomber::BomberList.begin();
  // while (bomber != GBomber::BomberList.end()) {
  //   if (ENTITY_TYPE_BOMBER_P == (*bomber)->Type) {
  //     bomber++;
  //     continue;
  //   }
  //   GAI* AI = dynamic_cast<GAI*>(*bomber);
  //   if (NULL != AI) {
  //     if(AI->PathManager.FindPath((int)AI->cX/TILE_SIZE, 
  // 				  (int)AI->cY/TILE_SIZE, x, y))
  // 	AI->PrintPath();      
  //   }
  //   bomber++;
  // }
  
  // CurTileType = *GArea::AreaControl.GetTile(x*TILE_SIZE, y*TILE_SIZE);
}

void StateGame::OnMButtonDown(int mX, int mY) {
  if (NetMode != GAME_LOCAL) return; 

  int x = mX + GCamera::CameraControl.GetX();
  int y = mY + GCamera::CameraControl.GetY();
  x /= TILE_SIZE;
  y /= TILE_SIZE;
  GArea::AreaControl.SetTile(x*TILE_SIZE, y*TILE_SIZE, 0);
}  

void StateGame::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value) {
  App->Joy1.OnJoyAxis(which, axis, value);
  App->Joy2.OnJoyAxis(which, axis, value);
  App->Joy3.OnJoyAxis(which, axis, value);
  App->Joy4.OnJoyAxis(which, axis, value);
  // if (which == CurJoystick) {
  //   if (0 == axis) {
  //     if(value > -8000 && value < 8000) { 
  // 	p1->MoveLeft = false;  
  //      	p1->MoveRight = false;
  //     } 
  //     else {
  // 	if( value < 0 ) 
  // 	  p1->MoveLeft = true; 	
  // 	if (value > 0)
  // 	  p1->MoveRight = true; 	
  //     } 
  //   }
  // }
}

void StateGame::OnJoyHat(Uint8 which, Uint8 hat, Uint8 value) {
  App->Joy1.OnJoyHat(which, hat, value);
  App->Joy2.OnJoyHat(which, hat, value);
  App->Joy3.OnJoyHat(which, hat, value);
  App->Joy4.OnJoyHat(which, hat, value);

  // if (which == CurJoystick) {
  //   if (0 == hat) {
  //     if (value & SDL_HAT_LEFT) {
  // 	p1->MoveLeft = true;
  // 	p1->MoveRight = false;
  //     }   

  //     else if (value & SDL_HAT_RIGHT) {    
  // 	p1->MoveLeft = false;   
  // 	p1->MoveRight = true;
  //     }

  //     else if (value & SDL_HAT_CENTERED) {
  // 	p1->MoveLeft = false; 
  // 	p1->MoveRight = false; 
  //     }

  //     else {	
  // 	p1->MoveLeft = false; 
  // 	p1->MoveRight = false; 
  //     }

  //     // else if (value & SDL_HAT_RIGHTDOWN) {
  //     // 	p1->MoveLeft = false;   
  //     // 	p1->MoveRight = true;
  //     // }

  //     // else if (value & SDL_HAT_RIGHTUP) {
  //     // 	p1->MoveLeft = false;   
  //     // 	p1->MoveRight = true;
  //     // }

  //     // else if (value & SDL_HAT_DOWN) {
  //     // 	p1->MoveLeft = false;   
  //     // 	p1->MoveRight = false;
  //     // }

  //     // else if (value & SDL_HAT_UP) {
  //     // 	p1->MoveLeft = false;   
  //     // 	p1->MoveRight = false;
  //     // }

  //     // else
  //     // 	p1->MoveRight = false;   
      

  //     // if (value & SDL_HAT_CENTERED){
  //     // 	p1->MoveRight = false;
  //     // 	p1->MoveLeft = false;
  //     // }
  //   }
    
  // } 
}

void StateGame::OnJoyButtonDown(Uint8 which, Uint8 button) {
  App->Joy1.OnJoyButtonDown(which, button);
  App->Joy2.OnJoyButtonDown(which, button);
  App->Joy3.OnJoyButtonDown(which, button);
  App->Joy4.OnJoyButtonDown(which, button);

  // if (which == CurJoystick) {
  //   if (0 == button)
  //     p1->JumpExp();    
  // }  
}

void StateGame::OnJoyButtonUp(Uint8 which, Uint8 button) {
  App->Joy1.OnJoyButtonUp(which, button);
  App->Joy2.OnJoyButtonUp(which, button);
  App->Joy3.OnJoyButtonUp(which, button);
  App->Joy4.OnJoyButtonUp(which, button);

  // if (which == CurJoystick) {
  //   if (0 == button)
  //     p1->JumpExp();    
  // }  
}

  
void StateGame::Activate() {
  GameTime = 0;
  GameStartTime = SDL_GetTicks();
 
  App = StateManager::GetApp();  
  GEntity::RegisterApp(App);
  GArea::AreaControl.SetStateGame(StateGame::GetInstance());
  //GPath::RegisterApp(App);
 
  GSurface::LoadBombs();
  GSurface::LoadBombers();
  GSurface::LoadFlames();  
  GSurface::LoadPowerups();
  GSurface::LoadTiles(); 

  InitNetwork();
  if (!InitLevel()) return; 
  InitBombers();        
}

void StateGame::Deactivate() {
  delete Socket;
  Socket = NULL;

  CleanupFlames();
  CleanupBombs();
  CleanupBombers();
  CleanupPowerups();
  CleanupTiles();
 
  GEntity::EntityList.clear();  
  GArea::AreaControl.Cleanup();
}

void StateGame::Loop() {  
  GameTime = SDL_GetTicks() - GameStartTime;
  auto iter = App->devs.begin();
  while (iter != App->devs.end()){
    (*iter)->HandleInput();
    iter++;
  }

  //App->Key1.HandleInput();
  //App->Key1.HandleInput();
  // App->Key2.HandleInput();
  // App->Key3.HandleInput();
  // App->Joy1.HandleInput();
  
  LoopFlames();
  LoopBombs();
  LoopDecor();
  LoopPowerups();
  LoopBombers();  
  LoopSockets();
 
  GEntityCol::EntityColList.clear();  
}

void StateGame::InitBombers() {  
  // keep in sync with CleanupBombers!
  if (NetMode != GAME_CLIENT) {
    int bombers = App->GetNumBombers();
    //int bots = App->GetNumBots();
    //int players = bombers - bots;
    for (int i = 0; i < bombers; i++) {     
      GBomber* b = GBomber::Create();  
      b->PlaceBomberByNum(i+1, bombers);  
      //if (i < players) {} else {}      
    } 
  App->Log << "Bombers loaded!" << std::endl;
  GArea::AreaControl.PlacePowerups(); 
  } 
  GCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
  GCamera::CameraControl.SetBounds(GArea::AreaControl.GetBoundX(),
				   GArea::AreaControl.GetBoundY());
  App->Log << "Camera set up" << std::endl;
  App->Log << "Making a test" << std::endl;
  if (NetMode != GAME_CLIENT) {
    // it will be connected later on clients
    App->Log << "counting connections" << std::endl;
    auto iter = App->BomberMap.begin();
    while (iter != App->BomberMap.end()){
      App->Log << "*****" << std::endl;
      App->Log << "input:  " << iter->input  << std::endl;
      App->Log << "bomber: " << iter->bomber << std::endl;
      App->dev(iter->input)->Connect(GBomber::BomberList[iter->bomber]);  
      App->devs.push_back(App->dev(iter->input));
      iter++;
    }
    //App->Log << "counting connections" << std::endl;
    //App->Key1.Connect(GBomber::BomberList[0]);  
    // App->Key2.Connect(GBomber::BomberList[1]);  
    // App->Key3.Connect(GBomber::BomberList[2]); 
    
    //App->Joy1.Bomber = GBomber::BomberList[0];
  }
}

bool StateGame::InitLevel() {
  App->Log << "Loading map file...\n";
  GArea::AreaControl.RegisterApp(App);
  if (GArea::AreaControl.Load("Resources/tiles.png") == false) {
    App->Log << "Failed. Does it exist?\nExiting the program";
    return false;
  }
  App->Log << " Map successfully loaded!" << std::endl;
  return true;
}

void StateGame::InitNetwork() {
  NetMode = App->NetMode;
  Socket = NULL;
  if (NetMode != GAME_LOCAL) {
    assert(App->Host != NULL);
    assert(App->Port != NULL);

    Socket = new UDPSocket(this, App); 
    if (NetMode == GAME_SERVER) {
      if (Socket->Listen(App->Host, App->Port) != 0) {
	Socket->CloseSocket();
	//return; 
      }
    } else if (NetMode == GAME_CLIENT) {
      if (Socket->Connect(App->Host, App->Port) != 0) {
	Socket->CloseSocket();
	//return;
      }
    } else {
      assert(0);
    }
  }
}

void StateGame::CleanupFlames() {
  GSurface::UnloadFlames();
  std::vector<GFlame*>::iterator flame = GFlame::FlameList.begin();
  while (flame != GFlame::FlameList.end()) {
    if (!(*flame)) {
      GFlame::FlameList.erase(flame);
      continue;
    }  
    (*flame)->Cleanup();
    delete (*flame);      
    flame++;
  }
  GFlame::FlameList.clear();
}

void StateGame::CleanupBombs() {
  GSurface::UnloadBombs();
  std::vector<GBomb*>::iterator bomb = GBomb::BombList.begin();
  while (bomb != GBomb::BombList.end()) {
    if (!(*bomb)) {
      GBomb::BombList.erase(bomb);
      continue;
    }  
    (*bomb)->Cleanup();
    delete (*bomb);      
    bomb++;
  }
  GBomb::BombList.clear();
}

void StateGame::CleanupBombers() {
  // keep in sync with InitBombers!
  App->Key1.Disconnect();

  GSurface::UnloadBombers();
  std::vector<GBomber*>::iterator bomber = GBomber::BomberList.begin();
  while (bomber != GBomber::BomberList.end()) {
    if (!(*bomber)) {
      GBomber::BomberList.erase(bomber);
      continue;
    }  
    (*bomber)->Cleanup();    
    delete (*bomber);      
    bomber++;
  }
  GBomber::BomberList.clear();
}

void StateGame::CleanupPowerups() {
  GSurface::UnloadPowerups();
  std::vector<GPowerup*>::iterator powerup = GPowerup::PowerupList.begin();
  while (powerup != GPowerup::PowerupList.end()) {
    if (!(*powerup)) {
      GPowerup::PowerupList.erase(powerup);
      continue;
    }  
    (*powerup)->Cleanup();
    delete (*powerup);      
    powerup++;
  }
  GPowerup::PowerupList.clear();
}

void StateGame::CleanupTiles() {
  GSurface::UnloadTiles();
  std::vector<GDecor*>::iterator decor = GDecor::DecorList.begin();
  while (decor != GDecor::DecorList.end()) {
    if (!(*decor)) {
      GDecor::DecorList.erase(decor);
      continue;
    }  
    (*decor)->Cleanup();
    delete (*decor);      
    decor++;
  }
  GDecor::DecorList.clear();
}

void StateGame::LoopFlames() {
  std::vector<GFlame*>::iterator flame = GFlame::FlameList.begin();
  while ( flame != GFlame::FlameList.end()) {
    if (!(*flame)) {
      GFlame::FlameList.erase(flame);
      continue;
    }  

    if (!(*flame) || !(*flame)->Enabled) {
      (*flame)->Cleanup();
      delete (*flame);      
      GFlame::FlameList.erase(flame);
      continue;
    }    

    (*flame)->Loop();
    flame++;
  }
}

void StateGame::LoopBombs() {
  std::vector<GBomb*>::iterator iter = GBomb::BombList.begin();
  while ( iter != GBomb::BombList.end()) {
    if (!(*iter)) {
      GBomb::BombList.erase(iter);
      continue;
    }  

    if (!(*iter) || !(*iter)->Enabled) {
      (*iter)->Cleanup();
      delete (*iter);      
      GBomb::BombList.erase(iter);
      continue;
    }    

    (*iter)->Loop();
    iter++;
  }
}

void StateGame::LoopDecor() {
  std::vector<GDecor*>::iterator decor = GDecor::DecorList.begin();
  while ( decor != GDecor::DecorList.end()) {
    if (!(*decor)) {
      GDecor::DecorList.erase(decor);
      continue;
    }  

    if (!(*decor) || !(*decor)->Enabled) {
      (*decor)->Cleanup();
      delete (*decor);      
      GDecor::DecorList.erase(decor);
      continue;
    }    

    (*decor)->Loop();
    decor++;
  }
}

void StateGame::LoopPowerups() {
  std::vector<GPowerup*>::iterator pup = GPowerup::PowerupList.begin();
  while ( pup != GPowerup::PowerupList.end()) {
    //App->Log << (*pup)->Name << ": " << std::endl;
    if (!(*pup)) {
      GPowerup::PowerupList.erase(pup);
      continue;
    }  

    if (!(*pup) || !(*pup)->Enabled) {
      (*pup)->Cleanup();
      delete (*pup);      
      GPowerup::PowerupList.erase(pup);
      continue;
    }    

    (*pup)->Loop();
    pup++;
  }
}

void StateGame::LoopBombers() {
  std::vector<GBomber*>::iterator bomber = GBomber::BomberList.begin();
  while ( bomber != GBomber::BomberList.end()) {
    //App->Log << (*bomber)->Name << ": " << std::endl;
    if (!(*bomber)) {
      GBomber::BomberList.erase(bomber);
      continue;
    }  

    if (!(*bomber) || !(*bomber)->Enabled) {
      (*bomber)->Cleanup();
      delete (*bomber);      
      GBomber::BomberList.erase(bomber);
      continue;
    }    

    (*bomber)->Loop();
    bomber++;
  }
}

void StateGame::LoopSockets() {
  if (Socket != NULL) {
    Socket->Loop();

    if (Socket->IsClosed()) {
      StateManager::SetActiveState(APPSTATE_MENU);  
    }   
  }
}

void StateGame::Render(SDL_Surface* SurfDisplay) {
  SDL_Rect Rect;
  Rect.x = 0;
  Rect.y = 0;
  Rect.w = GWIDTH;
  Rect.h = GHEIGHT;

  SDL_FillRect(SurfDisplay, &Rect, 0);
  
  GArea::AreaControl.RenderBack(SurfDisplay, GCamera::CameraControl.GetX(), GCamera::CameraControl.GetY());


  auto bomb  = GBomb::BombList.begin(); 
  while(bomb != GBomb::BombList.end()) {
    if (!(*bomb)) continue;
    //p1->OnRender(SurfDisplay);
    (*bomb)->Render(SurfDisplay);
    bomb++;   
  }

  auto flame  = GFlame::FlameList.begin(); 
  while(flame != GFlame::FlameList.end()) {
    if (!(*flame)) continue;
    //p1->OnRender(SurfDisplay);
    (*flame)->Render(SurfDisplay);
    flame++;   
  }
  
  std::vector<GPowerup*>::iterator pup  = GPowerup::PowerupList.begin(); 
  while(pup != GPowerup::PowerupList.end()) {
    if (!(*pup)) continue;
    (*pup)->Render(SurfDisplay);
    pup++;   
  }

  auto decor  = GDecor::DecorList.begin(); 
  while(decor != GDecor::DecorList.end()) {
    if (!(*decor)) continue;
    //p1->OnRender(SurfDisplay);
    (*decor)->Render(SurfDisplay);
    decor++;   
  }


  GArea::AreaControl.Render(SurfDisplay, GCamera::CameraControl.GetX(), GCamera::CameraControl.GetY());

  auto bomber  = GBomber::BomberList.begin(); 
  while(bomber != GBomber::BomberList.end()) {
    if (!(*bomber)) continue;
    (*bomber)->Render(SurfDisplay);
    bomber++;   
  }

  auto iten = GEntity::EntityList.begin(); 
  while(iten != GEntity::EntityList.end()) {
    if (!(*iten)) continue;
    //p1->OnRender(SurfDisplay);
    (*iten)->Render(SurfDisplay);
    iten++;   
  }
 
  // GArea::AreaControl.OnForeRender(SurfDisplay, GCamera::CameraControl.GetX(), GCamera::CameraControl.GetY());
}

StateGame* StateGame::GetInstance() {
  return &Instance;
}
