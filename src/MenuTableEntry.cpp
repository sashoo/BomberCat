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
  // if (SurfaceNumber != NULL)
  //   GSurface::Draw(SurfDisplay, SurfaceNumber, PosX, PosY);
  // if (SurfaceNickname != NULL)
  //   GSurface::Draw(SurfDisplay, SurfaceNickname, PosX+32, PosY);
  // if (SurfaceInputType)
  //   GSurface::Draw(SurfDisplay, SurfaceInputType, PosX+160, PosY);
}

int MenuTableEntry::GetWidth() const {
  return 0;
}

int MenuTableEntry::GetHeight() const {
  return 0;
}

void MenuTableEntry::Cleanup() {
  App->Log << "Cleaning...\n";
  if (SurfaceNumber != NULL)
    SDL_FreeSurface(SurfaceNumber);
  App->Log << "Cleaning...1\n";
  if (SurfaceNickname != NULL)
    SDL_FreeSurface(SurfaceNickname);
  App->Log << "Cleaning...2\n";
  if (SurfaceInputType != NULL)
    SDL_FreeSurface(SurfaceInputType); 
  App->Log << "Cleaning...3\n";
}
