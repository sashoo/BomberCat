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

class MenuTableEntry : public MenuEntry { 
public:
  MenuTableEntry();
  static std::string InputTypeToName(int type);
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
