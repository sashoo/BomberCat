#include "GBomber.hpp"
#include "GBomb.hpp"
#include "GPowerup.hpp"

int GBomber::Bombers = 0;
std::vector<GBomber*> GBomber::BomberList;

GBomber::GBomber() {
  BomberID = Bombers++;
  Name = "bomber";
  Width = 44;
  Height = 44;
  AnimControl.MaxFrames = 4; 
  AnimControl.SetFrameRate(150);
  //GEntity::OnLoad(name, File, width, height, maxFrames);

  ColX = 6;
  ColW = 12;
  ColY = 12;
  ColH = 12;

  //sometimes, magic just works  
  HitX = 16;
  HitY = 16;
  HitW = 32;
  HitH = 32;
  Alive = true;
  BomberState = STATE_ALIVE;
  // ColInnerX = ColX + 4;
  // ColInnerW = ColW + 8;
  // ColInnerY = ColY + 4;
  // ColInnerH = ColH + 8;
  MaxSpeedX = 4.0;
  MaxSpeedY = 4.0;

  Type = ENTITY_TYPE_BOMBER_AI;
  //Flags = ENTITY_FLAG_GHOST;
  
  BombsPlaced = 0;
  BombsMax = 1;
  BlastRadius = 2;
 
  //GEntity::GEntity();
}

GBomber::~GBomber() {
  App->Log << "Bomber Deleted" << std::endl;
  Bombers--;
}

bool GBomber::OnLoad() {
  BomberList.push_back(this);   
  return true;
}

void GBomber::OnLoop() {
  GEntity::OnLoop();  
  std::vector<GPowerup*>::iterator pup = GPowerup::PowerupList.begin();
  while (pup != GPowerup::PowerupList.end()) {       
    if (Collides(*pup)) {
      if (POWERUP_BLAST == (*pup)->PowerupType)
  	++BlastRadius;	
      else if (POWERUP_BOMB == (*pup)->PowerupType)
  	++BombsMax;
      App->Log << (*pup)->Name << " touched" << std::endl;
      (*pup)->Enabled = false;	 
    }   
    pup++;
  }
  if (BomberState == STATE_DYING) {
    
  }
}

void GBomber::OnRender(SDL_Surface* SurfDisplay) {
  GSurface::OnDraw(SurfDisplay, GSurface::SurfBomber, 
		   X-GCamera::CameraControl.GetX(), 
		   Y-GCamera::CameraControl.GetY(), 
		   (4*BomberID+CurrentFrameCol + AnimControl.GetCurrentFrame())* Width, 
		   CurrentFrameRow * Height, 
		   Width, Height);  
}

void GBomber::OnCleanup() {
  GEntity::OnCleanup();
}

void GBomber::OnAnimate() {
  if (BomberState == STATE_ALIVE) {
    if (MoveUp)
      CurrentFrameRow = 1;
    else if (MoveDown)
      CurrentFrameRow = 0;  
    else if (MoveLeft)
      CurrentFrameRow = 3;
    else if (MoveRight)
      CurrentFrameRow = 2;  
 
    if (SpeedX != 0 || SpeedY != 0)
      AnimControl.OnAnimate();
    else
      AnimControl.SetCurrentFrame(1);
  }
  else if (BomberState == STATE_DYING) {    
    if (AnimControl.OnAnimate()) {
      BomberState = STATE_DEAD;
      Alive = false;
      Enabled = false;
    }
    
    CurrentFrameRow = AnimControl.CurrentRow;
  }
}

bool GBomber::OnCollision(GEntity* Entity) {
  GEntity::OnCollision(Entity);
}

bool GBomber::IsHit(GEntity* entity) {
  int oX = entity->X+entity->ColX;
  int oY = entity->Y+entity->ColY;
  int oW = entity->Width-entity->ColW-1;
  int oH = entity->Height-entity->ColH-1;

  int left1, left2;
  int right1, right2;
  int top1, top2;
  int bottom1, bottom2;
 
  int tX = (int)X + ColX + HitX;
  int tY = (int)Y + ColY + HitY;
 
  left1 = tX;
  left2 = oX;
 
  right1 = left1 + Width - 1 - ColW - HitW;
  right2 = oX + oW - 1;
 
  top1 = tY;
  top2 = oY;
 
  bottom1 = top1 + Height - 1 - ColH - HitH;
  bottom2 = oY + oH - 1;  
 
  if (bottom1 < top2) return false;
  if (top1 > bottom2) return false;
 
  if (right1 < left2) return false;
  if (left1 > right2) return false;
 
  return true;
}

void GBomber::PlaceBomber(int x, int y) {
  X = x * TILE_SIZE - ColX;
  Y = y * TILE_SIZE - ColY;

  int xtile;
  int ytile;

  //center
  xtile = x;
  ytile = y;
  if (xtile > 0 && ytile > 0 && 
      xtile < CArea::AreaControl.GetWidth()  - 1 &&
      ytile < CArea::AreaControl.GetHeight() - 1)
    CArea::AreaControl.SetTile(xtile*TILE_SIZE, ytile*TILE_SIZE, 0);  

  //left
  xtile = x - 1;
  ytile = y;
  if (xtile > 0 && ytile > 0 && 
      xtile < CArea::AreaControl.GetWidth()  - 1 &&
      ytile < CArea::AreaControl.GetHeight() - 1)
    CArea::AreaControl.SetTile(xtile*TILE_SIZE, ytile*TILE_SIZE, 0);  

  //right
  xtile = x + 1;
  ytile = y;
  if (xtile > 0 && ytile > 0 && 
      xtile < CArea::AreaControl.GetWidth()  - 1 &&
      ytile < CArea::AreaControl.GetHeight() - 1)
    CArea::AreaControl.SetTile(xtile*TILE_SIZE, ytile*TILE_SIZE, 0);  

  //up
  xtile = x;
  ytile = y - 1;
  if (xtile > 0 && ytile > 0 && 
      xtile < CArea::AreaControl.GetWidth()  - 1 &&
      ytile < CArea::AreaControl.GetHeight() - 1)
    CArea::AreaControl.SetTile(xtile*TILE_SIZE, ytile*TILE_SIZE, 0);  

  //down
  xtile = x;
  ytile = y + 1;
  if (xtile > 0 && ytile > 0 && 
      xtile < CArea::AreaControl.GetWidth()  - 1 &&
      ytile < CArea::AreaControl.GetHeight() - 1)
    CArea::AreaControl.SetTile(xtile*TILE_SIZE, ytile*TILE_SIZE, 0);  
  
}

void GBomber::PlaceBomb() {
  if (BombsPlaced < BombsMax) {
    int posx = cX / TILE_SIZE;
    int posy = cY / TILE_SIZE;
    posx *= TILE_SIZE;
    posy *= TILE_SIZE;
    std::vector<GBomb*>::iterator it = GBomb::BombList.begin();
    while (it != GBomb::BombList.end()) {
      if (posx == (*it)->X && posy == (*it)->Y)
	return;
      it++;
    }
    GBomb* bomb = new GBomb();    
   
    bomb->X = posx;
    bomb->Y = posy;
    bomb->Owner = BomberID;
    bomb->Start();    
    bomb->Bomber = this;
    bomb->JustPlaced = true;
    GBomb::BombList.push_back(bomb);
    BombsPlaced++;
  }
}

bool GBomber::PosValid(int NewX, int NewY) {
  bool isvalid = true;
 
  int StartX     = (NewX + ColX) / TILE_SIZE;
  int StartY     = (NewY + ColY) / TILE_SIZE;
 
  int EndX    = (NewX + ColX + Width  - ColW  - 1) / TILE_SIZE;
  int EndY    = (NewY + ColY + Height - ColH  - 1) / TILE_SIZE;
  // int NewCX = NewX + Width/2;
  // int NewCY = NewY + Height/2;
  // int tileCX;
  // int tileCY;

  // int curtileCX = NewCX / TILE_SIZE;
  // curtileCX *= TILE_SIZE;
  // curtileCX += TILE_SIZE / 2;

  // int curtileCY = NewCY / TILE_SIZE;
  // curtileCY *= TILE_SIZE;
  // curtileCY += TILE_SIZE / 2;

  // //we are going:
  // if (NewX > X) {
  //   // right
  //   tileCX = curtileCX + TILE_SIZE;
  // }
  // else if (NewX < X) {
  //   // left;
  //   tileCX = curtileCX - TILE_SIZE;
  // }
  // else {
  //   tileCX = curtileCX;
  // }

  // if (NewY > Y) {
  //   // down
  //   tileCY = curtileCY + TILE_SIZE;
  // }
  // else if (NewY < Y) {
  //   // up;
  //   tileCY = curtileCY - TILE_SIZE;
  // }
  // else {
  //   tileCY = curtileCY;
  // }

  

  // int StartX     = (NewX + ColInnerX) / TILE_SIZE;
  // int StartY     = (NewY + ColInnerY) / TILE_SIZE;
 
  // int EndX    = (NewX + ColInnerX + Width  - ColInnerW  - 1) / TILE_SIZE;
  // int EndY    = (NewY + ColInnerY + Height - ColInnerH  - 1) / TILE_SIZE;



  // bool pathclear = true;
  // int cx;
  // int cy;

  for(int iY = StartY;iY <= EndY;iY++) {
    for(int iX = StartX;iX <= EndX;iX++) {
      int* Tile = CArea::AreaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE); 
      
      if(PosValidTile(Tile) == false) {	
		 
	isvalid = false;	
      }      
    }
  }
    
  // for(int iY = StartY;iY <= EndY;iY++) {
  //   for(int iX = StartX;iX <= EndX;iX++) {
  //     int* Tile = CArea::AreaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE); 
  //     int ax = iX * TILE_SIZE + TILE_SIZE / 2;
  //     int ay = iY * TILE_SIZE + TILE_SIZE / 2;
  //     if(PosValidTile(Tile) == false) {	
  // 	if (ax == tileCX && ay == tileCY) {
  // 	  pathclear = false;
  // 	}		 
  // 	isvalid = false;	
  //     }
  //     else {
  // 	if (ax == tileCX && ay == tileCY) {
  // 	  if (abs(NewCX - tileCX) < 4 && 
  // 	      abs(NewCY - tileCY) < 4) {
  // 	    pathclear = false;
  // 	  }
  // 	}	
  //     }
  //   }
  // }

  // if (pathclear && !isvalid) {
  //   isvalid = true;
  // }


  //app->Log << "I'm in\n";

  if(Flags & ENTITY_FLAG_MAPONLY) {
  }else{
   
    std::vector<GBomb*>::iterator bomb = GBomb::BombList.begin();
    while (bomb != GBomb::BombList.end()) {     
      if ((*bomb)->JustPlaced  && this == (*bomb)->Bomber ) {	
	if (PosValidEntity(*bomb, X, Y)) {
	    (*bomb)->JustPlaced = false;
	    bomb++;
	    continue;
	}
      }
      else {
	if (PosValidEntity(*bomb, NewX, NewY) == false) {
	  isvalid = false;
	}
      }
      
      bomb++;
    }

   
   
  }

  return isvalid;
}

bool GBomber::PosValidTile(int* Tile) {
  GEntity::PosValidTile(Tile);
}

bool GBomber::PosValidEntity(GEntity* Entity, int NewX, int NewY) {
  GEntity::PosValidEntity(Entity, NewX, NewY);
}

void GBomber::CheckVictory() {
  if ( GBomber::BomberList.size() == 0) {
    // draw
  } 
  else if ( GBomber::BomberList.size() == 1) {
    // GBomber::BomberList[0] is victorius
  }
  
  
}

void GBomber::Die() {
  Alive = false;
  BomberState = STATE_DYING;
  AnimControl.SetCurrentFrame(0);
  AnimControl.SetFrameRate(75);
  AnimControl.CurrentRow = 4;
  AnimControl.MaxRow = 7;
  AnimControl.Mode = ANIM_MODE_DESCEND;
  CheckVictory();
}

// bool GBomber::PosValidBomb(GBomb* Entity, int NewX, int NewY) {
//   if( Entity != NULL && Entity->Dead == false &&
//       Entity->Flags ^ ENTITY_FLAG_MAPONLY &&
//       Entity->Collides(NewX + ColX, 
// 		      NewY + ColY, 
// 		      Width - ColW - 1, 
// 		      Height - ColH - 1) == true) {
 
//     GEntityCol EntityCol;
 
//     EntityCol.EntityA = this;
//     EntityCol.EntityB = Entity;
 
//     GEntityCol::EntityColList.push_back(EntityCol);

   
    
//     // if (Entity->JustPlaced && Entity->Owner == BomberID) 
//     //   return true;
//     // else
//       return false;
   

     
 
//     //return false;
//   }
 
//   return true;
// }
