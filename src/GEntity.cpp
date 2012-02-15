#include "GEntity.hpp"
#include <cmath>

std::vector<GEntity*> GEntity::EntityList;
int GEntity::Entities = 0;
MirageApp* GEntity::App;

GEntity::GEntity(){
  ID = Entities;
  Entities++;
  SurfEntity = NULL;

  Name = "";

  X = 0;
  Y = 0;
  Width = 0;
  Height = 0;
  MoveLeft = false;
  MoveRight = false;
  MoveUp = false;
  MoveDown = false;

  Flags = 0;

  Type = ENTITY_TYPE_GENERIC;
  Enabled = true;
  
  //State = ENTITY_STATE_FALLING;
  //JumpPressed = false;

  SpeedX = 0.f;
  SpeedY = 0.f;  

  AccelX = 0;
  AccelY = 0;

  MaxSpeedX = 2.0;
  MaxSpeedY = 2.0;

  CurrentFrameCol = 0;
  CurrentFrameRow = 0;

  ColX = 0;
  ColY = 0;  
  ColW = 0;
  ColH = 0;  

  //AnimState = 0;
}

GEntity::~GEntity() {
}

void GEntity::RegisterApp(MirageApp* app){
  GEntity::App = app;
  app->Log << "GEntity has registered an app" << std::endl;
}

bool GEntity::OnLoad(std::string name, char* File, int width, int height, int maxFrames) {
  if ((SurfEntity = GSurface::OnLoad(File)) == NULL) {
    App->Log << "failed to load file:" << File << std::endl;
    return false;
  }
 
  Name = name;
  Width = width;
  Height = height;
  AnimControl.MaxFrames = maxFrames;
  EntityList.push_back(this);
  return true;  
}

void GEntity::OnLoop(){  
  cX = X + Width/2;
  cY = Y + (Height+ColY)/2;
 
    
  if (MoveLeft)
    SpeedX = -MaxSpeedX;
  else if (MoveRight)
    SpeedX =  MaxSpeedX;
  else
    SpeedX = 0;

  if (MoveUp)
    SpeedY = -MaxSpeedY;
  else if (MoveDown)
    SpeedY =  MaxSpeedY;
  else
    SpeedY = 0;


  OnAnimate();
  OnMove(SpeedX, SpeedY);  

  //AnimControl.OnAnimate();
}

void GEntity::OnRender(SDL_Surface* SurfDisplay) {
  if (SurfEntity == NULL || SurfDisplay == NULL) return;
  
  GSurface::OnDraw(SurfDisplay, SurfEntity, 
		   X-GCamera::CameraControl.GetX(), 
		   Y-GCamera::CameraControl.GetY(), 
		   (0+CurrentFrameCol + AnimControl.GetCurrentFrame())* Width, 
		   CurrentFrameRow * Height, 
		   Width, Height);
  
}

// void GEntity::OnRender(SDL_Surface* SurfDisplay, SDL_Surface* thing) {
//   if (SurfEntity == NULL || SurfDisplay == NULL) return;
  
//   GSurface::OnDraw(SurfDisplay, thing, 
// 		   X-GCamera::CameraControl.GetX(), 
// 		   Y-GCamera::CameraControl.GetY(), 
// 		   (0+CurrentFrameCol + AnimControl.GetCurrentFrame())* Width, 
// 		   CurrentFrameRow * Height, 
// 		   Width, Height);
  
// }

void GEntity::OnAnimate() {
  // No animations for generic Entity.
}

bool GEntity::OnCollision(GEntity* Entity) {
  // In this exact game this function seems to be useless.
  // However it is left. Just in case.
  return true;
}

void GEntity::DeleteObject(){
}

void GEntity::OnMove(float MoveX, float MoveY) {
  if (MoveX == 0 && MoveY == 0) return;
  
  double NewX = 0.0;
  double NewY = 0.0;

  //CanJump = false;
  //State = ENTITY_STATE_FALLING;
  // if (State != ENTITY_STATE_JUMPING)
  //   State = ENTITY_STATE_FALLING;

  MoveX *= GFPS::FPSControl.GetSpeedFactor();
  MoveY *= GFPS::FPSControl.GetSpeedFactor();

  if (MoveX != 0) {
    if (MoveX >= 0) NewX =  GFPS::FPSControl.GetSpeedFactor();
    else            NewX = -GFPS::FPSControl.GetSpeedFactor();
  }
  
  if (MoveY != 0) {
    if (MoveY >= 0) NewY =  GFPS::FPSControl.GetSpeedFactor();
    else            NewY = -GFPS::FPSControl.GetSpeedFactor();
  }

  while (true) {
    if(Flags & ENTITY_FLAG_GHOST) {
      PosValid((int)(X + NewX), (int)(Y + NewY)); 
      //We don't care about collisions, but we need to send events to other entities
 
      X += NewX;
      Y += NewY;
    }
    else {
      if(PosValid((int)(X + NewX), (int)(Y))) 
	X += NewX;
      else {
	//SpeedX = 0;      
	//SpeedX = 0;      
	//SpeedY = 0;      
	int tiley = cY / TILE_SIZE;
	int tilex;
	if (NewX > 0) {
	  // down
	  tilex = (cX + NewX) / TILE_SIZE + 1;
	}
	else if (NewX < 0) {
	  // up;
	  tilex = (cX + NewX) / TILE_SIZE - 1;
	}
	else {
	  tilex = (cX + NewX) / TILE_SIZE;
	}
	//int tiley = NewY / TILE_SIZE;
	int* Tile = CArea::AreaControl.GetTile(tilex * TILE_SIZE, tiley * TILE_SIZE);       
	if(PosValidTile(Tile) == false) {	
	  SpeedX = 0;
	}
	else {
	  NewX = 0;
	  // if (NewX != 0)
	  //   SpeedX = 0;
	  // else
	    Y = tiley * TILE_SIZE - ColY;	 
	  // int destX = tilex * TILE_SIZE - ColX;
	  // if (X < destX)
	  //   X += 1;//abs(NewY);//tilex * TILE_SIZE - ColX;	  
	  // if (X > destX)
	  //   X -= 1;//abs(NewY);//tilex * TILE_SIZE - ColX;
	}
      }
 
      if(PosValid((int)(X), (int)(Y + NewY))) 
	Y += NewY;	
      else {	
	//SpeedY = 0;  
	int tilex = cX / TILE_SIZE;
	int tiley;
	if (NewY > 0) {
	  // down
	  tiley = (cY + NewY) / TILE_SIZE + 1;
	}
	else if (NewY < 0) {
	  // up;
	  tiley = (cY + NewY) / TILE_SIZE - 1;
	}
	else {
	  tiley = (cY + NewY) / TILE_SIZE;
	}
	//int tiley = NewY / TILE_SIZE;
	int* Tile = CArea::AreaControl.GetTile(tilex * TILE_SIZE, tiley * TILE_SIZE);       
	if(PosValidTile(Tile) == false) {	
	  SpeedY = 0;
	}
	else {
	  NewY = 0;
	  // if (NewY != 0)
	  //   SpeedY = 0;
	  // else
	  X = tilex * TILE_SIZE - ColX;	 
	  // int destX = tilex * TILE_SIZE - ColX;
	  // if (X < destX)
	  //   X += 1;//abs(NewY);//tilex * TILE_SIZE - ColX;	  
	  // if (X > destX)
	  //   X -= 1;//abs(NewY);//tilex * TILE_SIZE - ColX;
	  
	}
	  
      }
    }
      
    MoveX += -NewX;
    MoveY += -NewY;
 
    if(NewX > 0 && MoveX <= 0) NewX = 0;
    if(NewX < 0 && MoveX >= 0) NewX = 0;
 
    if(NewY > 0 && MoveY <= 0) NewY = 0;
    if(NewY < 0 && MoveY >= 0) NewY = 0;
 
    if(MoveX == 0) NewX = 0;
    if(MoveY == 0) NewY = 0;
 
    if((MoveX == 0 && MoveY == 0)||(NewX  == 0 && NewY  == 0)){
      
      int StartX     = (NewX + ColX) / TILE_SIZE;
      int StartY     = (NewY + ColY) / TILE_SIZE;
 
      int EndX    = (NewX + ColX + Width  - ColW  - 1) / TILE_SIZE;
      int EndY    = (NewY + ColY + Height - ColH  - 1) / TILE_SIZE;
 
      for(int iY = StartY;iY <= EndY;iY++) {
      	for(int iX = StartX;iX <= EndX;iX++) {
      	  // int* Tile = CArea::AreaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE); 
      	  // if(PosValidTile(Tile) == false) {
      	  //   float depthX = 0.f;
      	  //   float depthY = 0.f;
	  //   if (Collides(iX * TILE_SIZE, iY * TILE_SIZE, 
	  // 		 TILE_SIZE, TILE_SIZE,
	  // 		 depthX, depthY)) {
	  //     if (abs(depthX) > abs(depthY))
	  // 	Y += depthY;
	  //     if (abs(depthX) < abs(depthY))
	  // 	X += depthX;	    
	  //   }	      
	  //     //isvalid = false;	
      	  // }
	  
      	}
      }

      break;
    }

  }
}

void GEntity::StopMove() {
  if(SpeedX > 0) {
    AccelX = -1;
  }
 
  if(SpeedX < 0) {
    AccelX = 1;
  }
 
  if(SpeedX < 2.0f && SpeedX > -2.0f) {
    AccelX = 0;
    SpeedX = 0;
  }

 if(SpeedY > 0) {
    AccelY = -1;
  }
 
  if(SpeedY < 0) {
    AccelY =  1;
  }

  if(SpeedY < 2.0f && SpeedY > -2.0f) {
    AccelY = 0;
    SpeedY = 0;
  }
}

bool GEntity::Collides(int oX, int oY, int oW, int oH) {
  int left1, left2;
  int right1, right2;
  int top1, top2;
  int bottom1, bottom2;
 
  int tX = (int)X + ColX;
  int tY = (int)Y + ColY;
 
  left1 = tX;
  left2 = oX;
 
  right1 = left1 + Width - 1 - ColW;
  right2 = oX + oW - 1;
 
  top1 = tY;
  top2 = oY;
 
  bottom1 = top1 + Height - 1 - ColH;
  bottom2 = oY + oH - 1;
 
 
  if (bottom1 < top2) return false;
  if (top1 > bottom2) return false;
 
  if (right1 < left2) return false;
  if (left1 > right2) return false;
 
  return true;
}

bool GEntity::Collides(int oX, int oY, int oW, int oH, float& depthX, float& depthY) {
  int left1, left2;
  int right1, right2;
  int top1, top2;
  int bottom1, bottom2;
 
  int tX = (int)X + ColX;
  int tY = (int)Y + ColY;
 
  left1 = tX;
  left2 = oX;
 
  right1 = left1 + Width - 1 - ColW;
  right2 = oX + oW - 1;
 
  top1 = tY;
  top2 = oY;
 
  bottom1 = top1 + Height - 1 - ColH;
  bottom2 = oY + oH - 1;

  float width1  = right1 - left1;
  float height1 = bottom1 - top1;
  float width2  = right2 - left2;
  float height2 = bottom2 - top2;

  float center1x = left1 + width1  / 2;
  float center1y = top1 + height1 / 2;
  float center2x = left2 + width2  / 2;
  float center2y = top2  + height2 / 2;
  //width1 -= 8;
  //height1 -= 8;

  float minDistX = (width1  + width2)  / 2;
  float minDistY = (height1 + height2) / 2;
  float distX = center1x-center2x;
  float distY = center1y-center2y;
 
  depthX = distX > 0 ? minDistX - distX : -minDistX - distX;
  depthY = distY > 0 ? minDistY - distY : -minDistY - distY;
 
  if (bottom1 < top2) return false;
  if (top1 > bottom2) return false;
 
  if (right1 < left2) return false;
  if (left1 > right2) return false;
 
  return true;
}

bool GEntity::Collides(GEntity* entity) {

  return Collides(entity->X+entity->ColX,
		  entity->Y+entity->ColY,
		  entity->Width-entity->ColW-1, 
		  entity->Height-entity->ColH-1);
}

bool GEntity::PosValid(int NewX, int NewY) {
  bool isvalid = true;
 
  int StartX     = (NewX + ColX) / TILE_SIZE;
  int StartY     = (NewY + ColY) / TILE_SIZE;
 
  int EndX    = (NewX + ColX + Width  - ColW  - 1) / TILE_SIZE;
  int EndY    = (NewY + ColY + Height - ColH  - 1) / TILE_SIZE;
 
  for(int iY = StartY;iY <= EndY;iY++) {
    for(int iX = StartX;iX <= EndX;iX++) {
      int* Tile = CArea::AreaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE); 
      if(PosValidTile(Tile) == false) {
	isvalid = false;
      }
    }
  }
 
  if(Flags & ENTITY_FLAG_MAPONLY) {
  }else{
    std::vector<GEntity*>::iterator entity = EntityList.begin();
    while(entity != EntityList.end()) {
      if(PosValidEntity(*entity, NewX, NewY) == false) {
	isvalid = false;
      }
      entity++;
    }
  }
 
  return isvalid;
}

bool GEntity::PosValidTile(int* Tile) {
  if(Tile == NULL) {
    return true;
  }
 
  if(*Tile != 0) {
    return false;
  }
 
  return true;
}

bool GEntity::PosValidEntity(GEntity* Entity, int NewX, int NewY) {
  if(// this != Entity &&
     Entity != NULL && Entity->Enabled &&
     Entity->Flags ^ ENTITY_FLAG_MAPONLY &&
     Entity->Collides(NewX + ColX, 
		      NewY + ColY, 
		      Width - ColW - 1, 
		      Height - ColH - 1) == true) {
 
    GEntityCol EntityCol;
 
    EntityCol.EntityA = this;
    EntityCol.EntityB = Entity;
 
    GEntityCol::EntityColList.push_back(EntityCol);
 
    return false;
  }
 
  return true;
}

void GEntity::OnCleanup() {
  if (SurfEntity) {
    SDL_FreeSurface(SurfEntity);
  }
  App->Log << Name << " Freed" << std::endl;

  SurfEntity = NULL;
}
  
  

