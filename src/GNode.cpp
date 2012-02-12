#include "GNode.hpp"

#include <cstddef>
#include "MirageApp.hpp"

GNode::GNode() {
  Open = true;
  X = 0;
  Y = 0;
  G = 0;
  H = 0;
  F = 0;
  Type = 0;
  Parent = NULL;
}

GNode::GNode(int x, int y) {
  Open = true;
  X = x;
  Y = y;
  G = 0;
  H = 0;
  F = 0;
  Type = 0;
  Parent = NULL;  
}

GNode::GNode(const GNode& gnode) {
  Open = gnode.Open;
  X = gnode.X;
  Y = gnode.Y;
  G = gnode.G;
  H = gnode.H;
  F = gnode.F;
  Type = gnode.Type;
  Parent = gnode.Parent;
}

GNode& GNode::operator= (const GNode& gnode) {
  Open = gnode.Open;
  X = gnode.X;
  Y = gnode.Y;
  G = gnode.G;
  H = gnode.H;
  F = gnode.F;
  Type = gnode.Type;
  Parent = gnode.Parent;
 
  return *this;
}

void GNode::CalcPoints() {
  void CalcG();
  void CalcH();
  void CalcF();
}

void GNode::CalcG(int dir) {
  if (NULL == Parent) {
    G = 0;
  }
  else {
    switch(dir) {
    case DIR_DIAG:
      G = Parent->G + PTS_DIAG;
      break;
      
    case DIR_HV:
    default:
      G = Parent->G + PTS_HV;
      break;
    }
    
  } // else
}

void GNode::CalcH(int destx, int desty) {
  // Manhattan distance
  H = 10*(abs(destx-X)+abs(desty-Y));
}

void GNode::CalcF(int destx, int desty, int dir) {
  CalcG(dir);
  CalcH(destx, desty);
  F = G + H;
}

void GNode::SetType(int type) {
  Type = type;
}

void GNode::Close() {
  Open = false;
}
int GNode::GetX() const {
  return X;
}
int GNode::GetY() const{
  return Y;
}
int GNode::GetG() const{
  return G;
}
int GNode::GetH() const{
  return H;
}
int GNode::GetF() const{
  return F;
}
int GNode::GetType() const {
  return Type;
}

bool GNode::IsOpen() const{
  return Open;
}

GNode* GNode::GetParent() const{
  return Parent;
}

// int GNode::SetX(int ) {
//   return X;
// }
// int GNode::SetY() {
//   return Y;
// }
// int GNode::SetG() {
//   return G;
// }
// int GNode::SetH() {
//   return H;
// }
// int GNode::SetType() {
//   return Type;
// }
void GNode::SetParent(GNode* parent) {
   Parent = parent;
}





// bool operator<(const GNode * a, const GNode * b)
// { 
//   return a->GetF() > b->GetF();
// }

bool operator== (GNode& gn1, GNode& gn2)
{
  return (gn1.GetX() == gn2.GetX() &&
	  gn1.GetY() == gn2.GetY());            
}

bool operator!= (GNode& gn1, GNode& gn2)
{
  return (!(gn1 == gn2));            
}

// GPath::App->Log << "Calling less\n";  
//   GPath::App->Log << "a.F: " << a.GetF() << std::endl;
//   GPath::App->Log << "b.F: " << b.GetF() << std::endl;
//   GPath::App->Log << "a.x: " << a.GetX() << std::endl;
//   GPath::App->Log << "a.y: " << a.GetY() << std::endl;
//   GPath::App->Log << "b.x: " << b.GetX() << std::endl;
//   GPath::App->Log << "b.y: " << b.GetY() << std::endl;

// GPath::App->Log << "a > right: " << (GetF() > right.GetF()) << std::endl;
