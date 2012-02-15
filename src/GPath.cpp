#include "GPath.hpp"
#include "GPoint.hpp"
#include "GArea.hpp"
#include "Define.hpp"
#include "MirageApp.hpp"

MirageApp* GPath::App = NULL;

GPath::GPath() {
  CalcDiag = false; 
}

void GPath::RegisterApp(MirageApp* app) {
  if (app)
    App = app;
}

bool GPath::FindPath(int sx, int sy, int destx, int desty) {
  Path.clear();
  App->Log << "Pathfinding session started" << std::endl;
  App->Log << "sx : " << sx << std::endl;
  App->Log << "sy : " << sy << std::endl;
  App->Log << "destx : " << destx << std::endl;
  App->Log << "desty : " << desty << std::endl;
  DestX = destx; 
  DestY = desty;
  GetAreaBounds();

  if (destx == sx && desty == sy) //path found
    return true;  

  for(int y = 0; y < MaxY; y++) {
    for(int x = 0; x < MaxX; x++) {
      Nodes.push_back(NULL);      
    }
  }

  //App->Log << "Empty nodes ready\n";
      
  GNode* start = new GNode(sx, sy);  
  GNode* end = NULL;
  int type = GetTileType(sx, sy);
  start->SetType(type);
  start->CalcPoints();
  SetNode(start);
  Open.push(start);

  // App->Log << "start->GetX(): " << start->GetX() << std::endl;
  // App->Log << "start->GetY(): " << start->GetY() << std::endl;
  // App->Log << "Open.top(): " << Open.top() << std::endl;
  // App->Log << "Nodes.size(): " << Nodes.size() << std::endl;
  // App->Log << "Open.empty(): " << Open.empty() << std::endl;

  bool found = false;
 
  while (!Open.empty()) {
    //take the node with lowest F value
    GNode* node = Open.top();   
    
    //remove from open list
    node->Close();
    Open.pop();

    
    
    App->Log << "||||Chosen one X: " << node->GetX() << " Y: " << node->GetY() << std::endl;
    App->Log << "--------------------\n";
   
    
    if (node->GetX() == DestX &&
	node->GetY() == DestY) {
      // App->Log << "found\n";
      found = true;
      end = node;
      // break; doesn't work here, damn it!
      while (!Open.empty()) Open.pop();
    }
    
    if (!found)
      FindAdjacent(node);
  }
  
  if (found) {
    GNode* node = end;
    GPoint point;
    point.x = node->GetX();
    point.y = node->GetY();
    // App->Log << "point.x: " << point.x << std::endl;
    // App->Log << "point.y: " << point.y << std::endl;
    Path.push_back(point);
    while (true) {
      GPoint point;
      GNode* parent = node->GetParent();

      if (NULL == parent) {
	
	break;
      }

      if (*parent == *start)
	break;

      point.x = parent->GetX();
      point.y = parent->GetY();
      // App->Log << "point.x: " << point.x << std::endl;
      // App->Log << "point.y: " << point.y << std::endl;
      Path.push_back(point);
     
      //App->Log << "Parent: " << parent << std::endl;   
      node = node->GetParent();   
      //App->Log << "new node: " << node << std::endl;   
      
    }   
    // App->Log << "X:\n"; 
    // std::vector<GPoint>::iterator it = Path.begin();
    // while (it != Path.end()) {
    //   App->Log << "X: " << it->x << std::endl;
    //   App->Log << "Y: " << it->y << std::endl;
    //   it++;
    // }
    App->Log << "done\n";
    
  }
  
  Cleanup();
  
  return found;
}

int GPath::GetTileType(GNode* gnode) {
  return *CArea::AreaControl.GetTile(gnode->GetX()*TILE_SIZE, gnode->GetY()*TILE_SIZE);
}

int GPath::GetTileType(int x, int y) {
  return *CArea::AreaControl.GetTile(x*TILE_SIZE, y*TILE_SIZE);
}

bool GPath::IsWrongType(int type) {
  return (type > 0);
}

void GPath::GetAreaBounds() {
  MaxX = CArea::AreaControl.GetWidth();
  MaxY = CArea::AreaControl.GetHeight();
}

GNode* GPath::GetNode(int x, int y) {
  int ID = 0;
  ID = x ;
  ID = ID + CArea::AreaControl.GetWidth() * y ;

  if (ID < 0 || ID >= Nodes.size())
    return NULL;
  
  return Nodes[ID];  
}

void GPath::SetNode(GNode* gnode) {  
  // FIXME sane return value needed
  int x = gnode->GetX();
  int y = gnode->GetY();
  int ID = 0;
  ID = x ;
  ID = ID + CArea::AreaControl.GetWidth() * y ;

  if (ID < 0 || ID >= Nodes.size())
    return;

  Nodes[ID] = gnode;   
}

void GPath::FindAdjacent(GNode* gnode) {
  int x = gnode->GetX();
  int y = gnode->GetY(); 
 
  int dir = DIR_HV; 
 
  //App->Log << "Left\n";
  FindTile(gnode, x-1, y, dir);
  //App->Log << "Right\n";
  FindTile(gnode, x+1, y, dir);
  //App->Log << "Up\n";
  FindTile(gnode, x, y-1, dir);
  //App->Log << "Down\n";
  FindTile(gnode, x, y+1, dir);

  if (CalcDiag) {
    dir = DIR_DIAG;
    FindTile(gnode, x-1, y-1, dir);
    FindTile(gnode, x+1, y-1, dir);
    FindTile(gnode, x-1, y+1, dir);
    FindTile(gnode, x+1, y+1, dir);
  }
  //App->Log << "Quit adjacent\n";
}

void GPath::FindTile(GNode* gnode, int x, int y, int dir) {
  if(TileInBounds(x, y)) {
    //check whether we already have it
    GNode* node = GetNode(x, y);
    if (NULL == node) {     
      int type = GetTileType(x, y);
      if (!IsWrongType(type)) {
	GNode* node = new GNode(x, y);
	node->SetParent(gnode);
	node->CalcF(DestX, DestY, dir);
  	App->Log << "**********\n";
  	App->Log << "Open tile:\n";
	App->Log << "x: " << node->GetX();
	App->Log << " y: " << node->GetY();
	App->Log << " G: " << node->GetG();
	App->Log << " H: " << node->GetH();
	App->Log << " F: " << node->GetF() << std::endl;
	SetNode(node);
	Open.push(node);
      }
    } // null == node
    else if (node->IsOpen()) {      
      //check if this path is better
      int pts;
      if (DIR_HV == dir) 
	pts = PTS_HV;
      else
	pts = PTS_DIAG; 

      if (gnode->GetG() + pts < node->GetG()) {
	node->SetParent(gnode);
	node->CalcF(DestX, DestY, dir);	
      }	
    } //IsOpen()
  } // in bounds
}

bool GPath::TileInBounds(int x, int y) {
  return (x >= 0 && y >= 0 && x < MaxX && y < MaxY);
}

void GPath::Cleanup() {
  std::vector<GNode*>::iterator it = Nodes.begin();
  while (it != Nodes.end()) {
    if (!(*it)) {
      Nodes.erase(it);
      continue;
    }
    delete (*it);
    it++;
  }
  while (!Open.empty()) {
    Open.pop();
  }
  Nodes.clear();
}
