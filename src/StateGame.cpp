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
  std::vector<GBomber*>::iterator bomber = GBomber::BomberList.begin();
  while (bomber != GBomber::BomberList.end()) {
    if (ENTITY_TYPE_BOMBER_AI == (*bomber)->Type) {
      bomber++;
      continue;
    }
    GPlayer* player = dynamic_cast<GPlayer*>(*bomber);
    if (NULL != player)
      player->OnKeyDown(sym, mod, Unicode);
    bomber++;
  }
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
  std::vector<GBomber*>::iterator bomber = GBomber::BomberList.begin();
  while (bomber != GBomber::BomberList.end()) {
    if (ENTITY_TYPE_BOMBER_AI == (*bomber)->Type) {
      bomber++;
      continue;
    }
    GPlayer* player = dynamic_cast<GPlayer*>(*bomber);
    if (NULL != player)
      player->OnKeyUp(sym, mod, Unicode);
    bomber++;
  }
  
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

  std::vector<GBomber*>::iterator bomber = GBomber::BomberList.begin();
  while (bomber != GBomber::BomberList.end()) {
    if (ENTITY_TYPE_BOMBER_P == (*bomber)->Type) {
      bomber++;
      continue;
    }
    GAI* AI = dynamic_cast<GAI*>(*bomber);
    if (NULL != AI) {
      if(AI->PathManager.FindPath((int)AI->cX/TILE_SIZE, 
				  (int)AI->cY/TILE_SIZE, x, y))
	AI->PrintPath();      
    }
    bomber++;
  }
  
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
  //App->Log << "Loading powerups... ";
  App = StateManager::GetApp();  
  GEntity::RegisterApp(App);
  GPath::RegisterApp(App);
 
  GSurface::LoadBombs();
  GSurface::LoadBombers();
  GSurface::LoadFlames();
  //App->Log << "Loading powerups... ";
  GSurface::LoadPowerups();
  GSurface::LoadTiles();
  //App->Log << "finished loading powerups... ";

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

  App->Log << "Loading map file...\n";
  GArea::AreaControl.RegisterApp(App);
  if (GArea::AreaControl.OnLoad("Resources/tiles.png") == false) {
    App->Log << "Failed. Does it exist?\nExiting the program";
    return;
  }
  
  App->Log << " Map successfully loaded!" << std::endl;


  int bombers = App->GetNumBombers();
  int bots = App->GetNumBots();
  int players = bombers - bots;
  for (int i = 0; i < bombers; i++) {
    if (i < players) {
      GPlayer* p = new GPlayer();  
      p->PlaceBomberByNum(i+1, bombers);  

      App->Log << "Loading player (bomber #" << i << ")";  
      if(p->OnLoad() == false) {
	App->Log << "Failed. Does it exist?\nExiting the program";
	return;
      }
    }
    else {
      GAI* bot = new GAI();
      bot->PlaceBomberByNum(i+1, bombers);
      App->Log << "Loading bot1... ";  
      if(bot->OnLoad() == false) {
	App->Log << "Failed. Does it exist?\nExiting the program";
	return;
      }
    }
  } 
  
  App->Log << "Done!" << std::endl;  
  App->Log << "Entities set up" << std::endl;
  GArea::AreaControl.PlacePowerups();
  

  GCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
  //GCamera::CameraControl.SetTarget(&p1->X, &p1->Y, p1->Width, p1->Height);
  GCamera::CameraControl.SetBounds(GArea::AreaControl.GetBoundX(),
				   GArea::AreaControl.GetBoundY());
  App->Log << "Camera set up" << std::endl;
}

void StateGame::OnDeactivate() {
  delete Socket;
  Socket = NULL;

  GSurface::UnloadBombs();
  GSurface::UnloadBombers();
  GSurface::UnloadFlames();
  GSurface::UnloadPowerups();
  GSurface::UnloadTiles();

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

  // for (int i = 0; i < GEntity::EntityList.size(); i++) {
  //   if (!GEntity::EntityList[i]) continue;
    
  //   GEntity::EntityList[i]->OnCleanup();
  // }
  GEntity::EntityList.clear();
  GBomber::BomberList.clear();
  GBomb::BombList.clear();
  GPowerup::PowerupList.clear();
  GFlame::FlameList.clear();
  GDecor::DecorList.clear();

  GArea::AreaControl.OnCleanup();
}

void StateGame::OnLoop() {  
  GameTime = SDL_GetTicks() - GameStartTime;
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

 

  // std::vector<GEntity*>::iterator it2 = GEntity::EntityList.begin();
  // while (it2 != GEntity::EntityList.end()) {
  //   if (!(*it2)) {
  //     //GEntity::EntityList.erase(it2);
  //     continue;
  //   }  

  //   (*it2)->OnLoop();
  //   it2++;
  // }

  // for(unsigned int i = 0; i < GEntityCol::EntityColList.size();i++) {
  //   GEntity* EntityA = GEntityCol::EntityColList[i].EntityA;
  //   GEntity* EntityB = GEntityCol::EntityColList[i].EntityB;
 
  //   if(EntityA == NULL || EntityB == NULL) continue;
 
  //   if(EntityA->OnCollision(EntityB)) {
  //     EntityB->OnCollision(EntityA);
  //   }
  // }
 
  GEntityCol::EntityColList.clear();

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
