#ifndef MENUTABLE_HPP
#define MENUTABLE_HPP

#include "MenuEntry.hpp"
#include "MenuTableEntry.hpp"
#include <vector>

class MenuTable : public MenuEntry {

private:
  static int TotalPlayers;
  std::vector<MenuTableEntry> Entries;
  
public:
  MenuTable();
  void Add();
  void Remove();
  virtual void Init();    
  virtual void SetColor(SDL_Color color);    
  virtual void SetPosition(float x, float y);
  virtual void SetOrigin(int origin);
  virtual void Render(SDL_Surface* SurfDisplay);
  virtual int GetWidth() const;
  virtual int GetHeight() const;
  virtual void Cleanup();  
};


#endif
