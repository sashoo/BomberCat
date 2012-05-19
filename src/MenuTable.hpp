#ifndef MENUTABLE_HPP
#define MENUTABLE_HPP

#include "MenuEntry.hpp"
#include "MenuTableEntry.hpp"
#include <vector>

struct KeyMap {
  int input;
  int bomber;
};

class MenuTable : public MenuEntry {

private:
  
  
public:
  static int TotalPlayers;
  MenuTable();
  void Add();
  void Remove();
  std::vector<MenuTableEntry*> Entries;
  std::vector<KeyMap> BomberMap;
  
  virtual void Init();    
  virtual void SetColor(SDL_Color color);    
  virtual void SetPosition(float x, float y);
  virtual void SetOrigin(int origin);
  virtual void Render(SDL_Surface* SurfDisplay);
  virtual int GetWidth() const;
  virtual int GetHeight() const;
  virtual void Cleanup(); 
  void FillMap();

 

};


#endif
