#ifndef GPATHS_HPP
#define GPATHS_HPP

#include <vector>
#include <queue>
#include "GNode.hpp"
#include "GPoint.hpp"

class MirageApp;

struct cmp_nodes {
  bool operator()(GNode* a, GNode* b) {    
    return a->GetF() > b->GetF();
  }
};

// bool compare_nodes(const GNode* const & a, const GNode* const & b) {    
//   return a->GetF() > b->GetF();
// }

class GPath {
public:
  GPath();

  static MirageApp* App;
  static void RegisterApp(MirageApp* app);
  std::vector<GNode*> Nodes;  
  std::priority_queue<GNode*, std::vector<GNode*>, cmp_nodes > Open;
  //std::priority_queue<GNode*, std::vector<GNode*>, bool (*)(const GNode* const & a, const GNode* const & b) > Open(compare_nodes);
  std::vector<GPoint> Path;
  bool CalcDiag;

  bool FindPath(int sx, int sy, int destx, int desty);
  int GetTileType(int x, int y); // implementation depends on the actual game
  int GetTileType(GNode* gnode); // implementation depends on the actual game
  bool IsWrongType(int type);
  void GetAreaBounds();
  GNode* GetNode(int x, int y);
  void SetNode(GNode* gnode);
  void FindAdjacent(GNode* gnode);
  void FindTile(GNode* gnode, int x, int y, int dir);
  bool TileInBounds(int x, int y);
  void Cleanup();
  int MaxX;
  int MaxY;

private:
  int DestX;
  int DestY;
};

#endif
