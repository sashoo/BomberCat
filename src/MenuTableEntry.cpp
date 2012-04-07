#include "MenuTableEntry.hpp"

MenuTableEntry::MenuTableEntry() {
  
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

void MenutableEntry::SetColor() {
  Color = color;
}

void MenuTableEntry::SetOrigin(origin) {
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
