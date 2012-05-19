#include "MenuTableEntry.hpp"
#include <sstream>
#include "GSurface.hpp"
#include "MirageApp.hpp"

MenuTableEntry::MenuTableEntry() {
  SurfaceNumber = NULL;
  SurfaceNickname = NULL;
  SurfaceInputType = NULL;
}

std::string MenuTableEntry::InputTypeToName(int type) {
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

void MenuTableEntry::Init() {
  std::stringstream ss;
  ss << Number;
  std::string s;
  s = ss.str();
  SurfaceNumber = TTF_RenderText_Solid(GSurface::FontRegular, s.c_str(), GSurface::ColorGreen);
  ss.str("");
  ss << InputTypeToName(InputType);
  s = ss.str();
  SurfaceInputType = TTF_RenderText_Solid(GSurface::FontRegular, s.c_str(), GSurface::ColorOption);
  SurfaceNickname = TTF_RenderText_Solid(GSurface::FontRegular, Nickname.c_str(), GSurface::ColorOption);
}

void MenuTableEntry::SetPosition(float x, float y) {  
  PosX = x;
  PosY = y;
}

void MenuTableEntry::SetColor(SDL_Color color) {
  Color = color;
}

void MenuTableEntry::SetOrigin(int origin) {
  Origin = origin;
}

void MenuTableEntry::Render(SDL_Surface* SurfDisplay) {
  if (SurfaceNumber != NULL)
    GSurface::Draw(SurfDisplay, SurfaceNumber, PosX, PosY);
  if (SurfaceNickname != NULL)
    GSurface::Draw(SurfDisplay, SurfaceNickname, PosX+20, PosY);
  if (SurfaceInputType != NULL)
    GSurface::Draw(SurfDisplay, SurfaceInputType, PosX+100, PosY);
}

int MenuTableEntry::GetWidth() const {
  return 0;
}

int MenuTableEntry::GetHeight() const {
  return 0;
}

void MenuTableEntry::Cleanup() {
 
  if (SurfaceNumber != NULL)
    SDL_FreeSurface(SurfaceNumber);
  
  if (SurfaceNickname != NULL)
    SDL_FreeSurface(SurfaceNickname);
  
  if (SurfaceInputType != NULL)
    SDL_FreeSurface(SurfaceInputType); 
  
}

MenuTableEntry::MenuTableEntry(const MenuTableEntry &entry)
  {
    PosX = entry.PosX;
    PosY = entry.PosY;
    Color = entry.Color;
    Origin = entry.Origin;
    App = entry.App;
    Number = entry.Number;
    InputType = entry.InputType;
    Nickname = entry.Nickname;
  }
  
MenuTableEntry& MenuTableEntry::operator= (const MenuTableEntry &entry)
  {
    // check for self-assignment by comparing the address of the
    // implicit object and the parameter
    if (this == &entry)
      return *this;
 
    // do the copy
    PosX = entry.PosX;
    PosY = entry.PosY;
    Color = entry.Color;
    Origin = entry.Origin;
    App = entry.App;
 
    // return the existing object
    return *this;
  }
