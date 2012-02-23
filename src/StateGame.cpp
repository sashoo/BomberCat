#include <cassert>

#include "StateGame.hpp"
#include "StateManager.hpp"
#include "MirageApp.hpp"
#include "GBomb.hpp"
#include "GFlame.hpp"
#include "GDecor.hpp"
#include "GPowerup.hpp"
#include "GSurface.hpp"

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
   GArea::AreaControl.RenderFore = !GArea::AreaControl.RenderFore;
   break;
 }

 case SDLK_2: {
   if (OldTime + 150 > SDL_GetTicks()) 
     return;

   OldTime = SDL_GetTicks();
   GArea::AreaControl.RenderCol = !GArea::AreaControl.RenderCol;
   break;
 }

 case SDLK_3: {
   if (OldTime + 150 > SDL_GetTicks()) 
     return;

   OldTime = SDL_GetTicks();
   GArea::AreaControl.RenderBack = !GArea::AreaControl.RenderBack;
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
   GArea::AreaControl.OnSave();
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

void StateGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode){

  App->Key1.OnKeyUp(sym);

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
  int x = mX + GCamera::CameraControl.GetX();
  int y = mY + GCamera::CameraControl.GetY();
  x /= TILE_SIZE;
  y /= TILE_SIZE;
  GArea::AreaControl.SetTile(x*TILE_SIZE, y*TILE_SIZE, 0);
}  

void StateGame::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value) {
  App->Joy1.OnJoyAxis(which, axis, value);
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
  // if (which == CurJoystick) {
  //   if (0 == button)
  //     p1->JumpExp();    
  // }  
}
  
void StateGame::OnActivate() {
  GameTime = 0;
  GameStartTime = SDL_GetTicks();
 
  App = StateManager::GetApp();  
  GEntity::RegisterApp(App);
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

void StateGame::OnDeactivate() {
  delete Socket;
  Socket = NULL;

  UnloadFlames();
  UnloadBombs();
  UnloadBombers();
  UnloadPowerups();
  UnloadTiles();
 
  GEntity::EntityList.clear();  
  GArea::AreaControl.OnCleanup();
}

void StateGame::OnLoop() {  
  GameTime = SDL_GetTicks() - GameStartTime;

  App->Key1.HandleInput();
  App->Joy1.HandleInput();
  
  LoopFlames();
  LoopBombs();
  LoopDecor();
  LoopPowerups();
  LoopBombers();  
 
  GEntityCol::EntityColList.clear();  
}

void StateGame::InitBombers() {  
  if (NetMode != GAME_CLIENT) {
    int bombers = App->GetNumBombers();
    int bots = App->GetNumBots();
    int players = bombers - bots;
    for (int i = 0; i < bombers; i++) {     
      GBomber* b = new GBomber();  
      b->PlaceBomberByNum(i+1, bombers);  
      //if (i < players) {} else {}

      App->Log << "Loading bomber (bomber #" << i << ")";  
      if(b->OnLoad() == false) {
	App->Log << "Failed. Does it exist?\nExiting the program";
	return;
      }      
    } 
  App->Log << "Bombers loaded!" << std::endl;
  GArea::AreaControl.PlacePowerups(); 
  } 
  GCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
  GCamera::CameraControl.SetBounds(GArea::AreaControl.GetBoundX(),
				   GArea::AreaControl.GetBoundY());
  App->Log << "Camera set up" << std::endl;
  App->Key1.Bomber = GBomber::BomberList[0];
  App->Key1.Bomber->InputHandle = &App->Key1;
  //App->Joy1.Bomber = GBomber::BomberList[0];
}

bool StateGame::InitLevel() {
  App->Log << "Loading map file...\n";
  GArea::AreaControl.RegisterApp(App);
  if (GArea::AreaControl.OnLoad("Resources/tiles.png") == false) {
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

void StateGame::UnloadFlames() {
  GSurface::UnloadFlames();
  std::vector<GFlame*>::iterator flame = GFlame::FlameList.begin();
  while (flame != GFlame::FlameList.end()) {
    if (!(*flame)) {
      GFlame::FlameList.erase(flame);
      continue;
    }  
    (*flame)->OnCleanup();
    delete (*flame);      
    flame++;
  }
  GFlame::FlameList.clear();
}

void StateGame::UnloadBombs() {
  GSurface::UnloadBombs();
  std::vector<GBomb*>::iterator bomb = GBomb::BombList.begin();
  while (bomb != GBomb::BombList.end()) {
    if (!(*bomb)) {
      GBomb::BombList.erase(bomb);
      continue;
    }  
    (*bomb)->OnCleanup();
    delete (*bomb);      
    bomb++;
  }
  GBomb::BombList.clear();
}

void StateGame::UnloadBombers() {
  GSurface::UnloadBombers();
  std::vector<GBomber*>::iterator bomber = GBomber::BomberList.begin();
  while (bomber != GBomber::BomberList.end()) {
    if (!(*bomber)) {
      GBomber::BomberList.erase(bomber);
      continue;
    }  
    (*bomber)->OnCleanup();
    // that is ok
    // GEntity has virtual destructor
    // both AI and Player bombers are deleted properly
    delete (*bomber);      
    bomber++;
  }
  GBomber::BomberList.clear();
}

void StateGame::UnloadPowerups() {
  GSurface::UnloadPowerups();
  std::vector<GPowerup*>::iterator powerup = GPowerup::PowerupList.begin();
  while (powerup != GPowerup::PowerupList.end()) {
    if (!(*powerup)) {
      GPowerup::PowerupList.erase(powerup);
      continue;
    }  
    (*powerup)->OnCleanup();
    delete (*powerup);      
    powerup++;
  }
  GPowerup::PowerupList.clear();
}

void StateGame::UnloadTiles() {
  GSurface::UnloadTiles();
  std::vector<GDecor*>::iterator decor = GDecor::DecorList.begin();
  while (decor != GDecor::DecorList.end()) {
    if (!(*decor)) {
      GDecor::DecorList.erase(decor);
      continue;
    }  
    (*decor)->OnCleanup();
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
      (*flame)->OnCleanup();
      delete (*flame);      
      GFlame::FlameList.erase(flame);
      continue;
    }    

    (*flame)->OnLoop();
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
      (*iter)->OnCleanup();
      delete (*iter);      
      GBomb::BombList.erase(iter);
      continue;
    }    

    (*iter)->OnLoop();
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
      (*decor)->OnCleanup();
      delete (*decor);      
      GDecor::DecorList.erase(decor);
      continue;
    }    

    (*decor)->OnLoop();
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
      (*pup)->OnCleanup();
      delete (*pup);      
      GPowerup::PowerupList.erase(pup);
      continue;
    }    

    (*pup)->OnLoop();
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
      (*bomber)->OnCleanup();
      delete (*bomber);      
      GBomber::BomberList.erase(bomber);
      continue;
    }    

    (*bomber)->OnLoop();
    bomber++;
  }
}

void StateGame::LoopSockets() {
  if (Socket != NULL) {
    Socket->OnLoop();

    if (Socket->IsClosed()) {
      StateManager::SetActiveState(APPSTATE_MENU);  
    }   
  }
}

void StateGame::OnRender(SDL_Surface* SurfDisplay) {
  SDL_Rect Rect;
  Rect.x = 0;
  Rect.y = 0;
  Rect.w = GWIDTH;
  Rect.h = GHEIGHT;

  SDL_FillRect(SurfDisplay, &Rect, 0);
  
  GArea::AreaControl.OnRenderBack(SurfDisplay, GCamera::CameraControl.GetX(), GCamera::CameraControl.GetY());

  std::vector<GBomb*>::iterator bomb  = GBomb::BombList.begin(); 
  while(bomb != GBomb::BombList.end()) {
    if (!(*bomb)) continue;
    //p1->OnRender(SurfDisplay);
    (*bomb)->OnRender(SurfDisplay);
    bomb++;   
  }

  std::vector<GFlame*>::iterator flame  = GFlame::FlameList.begin(); 
  while(flame != GFlame::FlameList.end()) {
    if (!(*flame)) continue;
    //p1->OnRender(SurfDisplay);
    (*flame)->OnRender(SurfDisplay);
    flame++;   
  }
  
  std::vector<GPowerup*>::iterator pup  = GPowerup::PowerupList.begin(); 
  while(pup != GPowerup::PowerupList.end()) {
    if (!(*pup)) continue;
    (*pup)->OnRender(SurfDisplay);
    pup++;   
  }

  std::vector<GDecor*>::iterator decor  = GDecor::DecorList.begin(); 
  while(decor != GDecor::DecorList.end()) {
    if (!(*decor)) continue;
    //p1->OnRender(SurfDisplay);
    (*decor)->OnRender(SurfDisplay);
    decor++;   
  }


  GArea::AreaControl.OnRender(SurfDisplay, GCamera::CameraControl.GetX(), GCamera::CameraControl.GetY());

  std::vector<GBomber*>::iterator bomber  = GBomber::BomberList.begin(); 
  while(bomber != GBomber::BomberList.end()) {
    if (!(*bomber)) continue;
    (*bomber)->OnRender(SurfDisplay);
    bomber++;   
  }

  std::vector<GEntity*>::iterator iten = GEntity::EntityList.begin(); 
  while(iten != GEntity::EntityList.end()) {
    if (!(*iten)) continue;
    //p1->OnRender(SurfDisplay);
    (*iten)->OnRender(SurfDisplay);
    iten++;   
  }

 

 
  // GArea::AreaControl.OnForeRender(SurfDisplay, GCamera::CameraControl.GetX(), GCamera::CameraControl.GetY());
}

StateGame* StateGame::GetInstance() {
  return &Instance;
}
