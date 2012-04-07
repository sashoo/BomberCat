#ifndef MENUTABLEENTRY_HPP
#define MENUTABLEENTRY_HPP

#include "MenuEntry.hpp"

enum InputType {
  Key1 = 1,
  Key2 = 2,
  Key3 = 3,
  Key4 = 4,
  Joy1 = 5,
  Joy2 = 6,
  Joy3 = 7,
  Joy4 = 8,
  Mouse = 9,
  AI = 10
};

std::string InputTypeToName(int type) {
  std::string out;
  switch(type) {
  case 1:
    out = "Key-1";
    break;
  case 2:
    out = "Key-2";
    break;
  case 3:
    out = "Key-3";
    break;
  case 4:
    out = "Key-4";
    break;  
  case 5:
    out = "Joy-1";
    break;
  case 6:
    out = "Joy-2";
    break;
  case 7:
    out = "Joy-3";
    break;
  case 8:
    out = "Joy-4";
    break;
  case 9:
    out = "Mouse";
    break;
  case 10:
    out = "AI";
    break;   
  default:
    out = "ERROR";
    break;
  }
  return out;
}

class MenuTableEntry : public MenuEntry { 
public:
  MenuTableEntry();
  int Number;
  int InputType;
  std::string Nickname;  
  virtual void Init();    
  virtual void SetColor(SDL_Color color);    
  //virtual void SetPosition(float x, float y)
  virtual void SetOrigin(int origin);
  virtual void Render(SDL_Surface* SurfDisplay);
  virtual int GetWidth() const;
  virtual int GetHeight() const;
  virtual void Cleanup();  
private:
  SDL_Surface* SurfaceNumber;
  SDL_Surface* SurfaceNickname;
  SDL_Surface* SurfaceInputType;

};

#endif
