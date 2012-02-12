#ifndef GNODE_HPP
#define GNODE_HPP
#include <stdlib.h>

enum {
  DIR_HV = 0,
  DIR_DIAG
};

const int PTS_HV   = 10;
const int PTS_DIAG = 14;

class GPaths;

class GNode {
public:
  GNode();
  GNode(int x, int y);
  GNode(const GNode& gnode);
  GNode& operator= (const GNode& gnode);

  void CalcPoints();
  void CalcG(int dir = 0);
  void CalcH(int dx, int dy);
  void CalcF(int destx, int desty, int dir); 
  void SetType(int type);
  void Close();

  int GetX() const;
  int GetY() const;
  int GetG() const;
  int GetH() const;
  int GetF() const;
  int GetType() const;
  GNode* GetParent() const;
  bool IsOpen() const;

  void SetParent(GNode* parent);

  bool operator<(GNode* right) const;
  
private:
  int Open;
  int X;
  int Y;

  int G;
  int H;
  int F;
  
  int Type;
  GNode* Parent;
  
};

//bool operator<(GNode * a, GNode * b);

bool operator== (GNode& gn1, GNode& gn2);
bool operator!= (GNode& gn1, GNode& gn2);

#endif 
