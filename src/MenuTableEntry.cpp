#include "MenuTableEntry.hpp"
#include <sstream>
#include "GSurface.hpp"

MenuTableEntry::MenuTableEntry() {
  
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
  SurfaceNumber = TTF_RenderText_Solid(GSurface::FontRegular, s.c_str(), GSurface::ColorOption);
  ss.str("");
  ss << InputTypeToName(InputType);
  s = ss.str();
  SurfaceInputType = TTF_RenderText_Solid(GSurface::FontRegular, s.c_str(), GSurface::ColorOption);
  SurfaceNickname = TTF_RenderText_Solid(GSurface::FontRegular, Nickname.c_str(), GSurface::ColorOption);
}

void MenuTableEntry::SetColor(SDL_Color color) {
  Color = color;
}

void MenuTableEntry::SetOrigin(int origin) {
  Origin = origin;
}

void MenuTableEntry::Render(SDL_Surface* SurfDisplay) {
  GSurface::Draw(SurfDisplay, SurfaceNumber, PosX, PosY);
  GSurface::Draw(SurfDisplay, SurfaceNickname, PosX+32, PosY);
  GSurface::Draw(SurfDisplay, SurfaceInputType, PosX+160, PosY);
}

int MenuTableEntry::GetWidth() const {
  return 0;
}

int MenuTableEntry::GetHeight() const {
  return 0;
}

void MenuTableEntry::Cleanup() {
  SDL_FreeSurface(SurfaceNumber);
  SDL_FreeSurface(SurfaceNickname);
  SDL_FreeSurface(SurfaceInputType); 
}
