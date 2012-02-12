#include "GAI.hpp"
#include "GPoint.hpp"

GAI::GAI() {
  Type = ENTITY_TYPE_BOMBER_AI;
  OldTime = 0;
  AItask = 0;
  
}

GAI::~GAI() {
  App->Log << "AI Deleted!" << std::endl;
}

bool GAI::OnLoad() {     
  return GBomber::OnLoad();
}

void GAI::OnLoop() {
  UsePath();
  GBomber::OnLoop();
}

void GAI::OnRender(SDL_Surface* SurfDisplay) {
  GBomber::OnRender(SurfDisplay);  
}

void GAI::OnCleanup() {
  GBomber::OnCleanup();
}

void GAI::OnAnimate() {
  GBomber::OnAnimate();
}

void GAI::UsePath() {
  if (!PathManager.Path.empty()) {
    AItask = AI_GOING;
    std::vector<GPoint>::iterator it = PathManager.Path.end()-1;       
    GPoint dest;
    dest.x = it->x*TILE_SIZE+TILE_SIZE/2;
    dest.y = it->y*TILE_SIZE+TILE_SIZE/2;    
  
    float difx = (float)dest.x - cX;
    float dify = (float)dest.y - cY;

    // app->Log << "dest.x" << dest.x << std::endl;
    // app->Log << "dest.y" << dest.y << std::endl;
    if ( PathManager.Path.size() == 1) {
      App->Log << "cX" << cX << std::endl;
      App->Log << "cY" << cY << std::endl;
    }
    // app->Log << "difx" << difx << std::endl;
    // app->Log << "dify" << dify << std::endl;
    // MoveLeft = false;
    // MoveRight = false;
    // MoveUp = false;
    // MoveDown = false;

    //if (abs(difx

    //going x
    if (abs(difx) > abs(dify)) {
      if (abs(difx) < 0.1f) {
	PathManager.Path.erase(it);
      }
      else {
	if (difx > 0) {
	  MoveRight = true;
	  MoveLeft = false;
	  MoveDown = false;
	  MoveUp = false;
	}
	else if (difx < 0) {
	  MoveLeft = true;
	  MoveRight = false;
	  MoveDown = false;
	  MoveUp = false;
	}
      }      
    }
    else if (abs(difx) < abs(dify)) {
      if ((int)abs(dify) == 0.1f) {
	PathManager.Path.erase(it);
      }
      else {
	if (dify > 0) {
	  MoveDown = true;
	  MoveUp = false;
	  MoveRight = false;
	  MoveLeft = false;
	}
	else if (dify < 0 ) {
	  MoveUp = true;
	  MoveDown = false;
	  MoveRight = false;
	  MoveLeft = false;
	}
      }   
    } 
    else {
      PathManager.Path.erase(it);
    }
	    
     
    
  }
  else {
    X = (int)X;
    Y = (int)Y;
    AItask = AI_IDLE;
    MoveLeft = false;
    MoveRight = false;
    MoveUp = false;
    MoveDown = false;    
  }  
}

bool GAI::OnCollision(GEntity* Entity){
  //  Jump();
  return true; 
}

void GAI::PrintPath() {
  std::vector<GPoint>::reverse_iterator rit = PathManager.Path.rbegin();
  App->Log << "********************" << std::endl;
  App->Log << "Path for ID:" << BomberID << std::endl;
  while (rit != PathManager.Path.rend()) {
    App->Log << "X: " << rit->x << std::endl;
    App->Log << "Y: " << rit->y << std::endl;
    rit++;
  }
  App->Log << "quit" << std::endl;
}
