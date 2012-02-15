#include "MenuOption.hpp"
#include "MenuManager.hpp"
#include "Define.hpp"
#include "GSurface.hpp"
#include "MirageApp.hpp"
#include <SDL_ttf.h>

MenuOption::MenuOption(std::string label, float halfOffset) {
  Label = label;
  HalfOffset = halfOffset;
  Index = 0;  
}

MenuOption::~MenuOption() {
}

void MenuOption::OnLeft() {
  int index = Index + 1;
  SetEntry(index);
}

void MenuOption::OnRight() {
  int index = Index - 1;
  SetEntry(index);
}

void MenuOption::OnRender(SDL_Surface* SurfDisplay) {
  int lposx = PosX - SurfLabel->w - HalfOffset;
  GSurface::OnDraw(SurfDisplay, SurfLabel,  lposx, PosY);
  GSurface::OnDraw(SurfDisplay, SurfOption, PosX+HalfOffset, PosY);
}

void MenuOption::SetColor(SDL_Color color){
  Color = color;
  SDL_FreeSurface(SurfLabel);
  SDL_FreeSurface(SurfOption);
  SurfLabel  = TTF_RenderText_Solid(mMenuManager->GetApp()->GetFont(), Label.c_str(),  Color);
  SurfOption = TTF_RenderText_Solid(mMenuManager->GetApp()->GetFont(), Option.c_str(), Color);
  Rect.w = SurfLabel->w + SurfOption->w + HalfOffset*2;
  Rect.h = SurfLabel->h + SurfOption->h;
}  

void MenuOption::SetPosition(float x, float y){
  PosX = x;
  PosY = y;
  Rect.x = PosX;
  Rect.y = PosY; 
}

void MenuOption::SetOrigin(int origin) {
  Origin = origin;  
}

int MenuOption::GetWidth() const {
  return Rect.w;
}

int MenuOption::GetHeight() const {
  return Rect.h;
}

void MenuOption::Clean() {
  App->Log << "Deleting entry: " << Label << "... ";
  SDL_FreeSurface(SurfLabel);
  SDL_FreeSurface(SurfOption);
  App->Log << "deleted" << std::endl;
}


void MenuOption::Setup() {
  Index = 0;
  Color = mMenuManager->GetInactiveColor();
  SurfLabel = TTF_RenderText_Solid(mMenuManager->GetApp()->GetFont(), Label.c_str(), Color);  
  Rect.w = SurfLabel->w + SurfOption->w + HalfOffset*2;
  Rect.h = SurfLabel->h + SurfOption->h;
  App->Log << Label << std::endl;
}

void MenuOption::SetEntry(unsigned int index) {
  if (index >= 0 && !OptionList.empty() && index < OptionList.size()) {
    Index = index;
    Option = OptionList[Index];     
    SDL_FreeSurface(SurfOption);  
    SurfOption = TTF_RenderText_Solid(mMenuManager->GetApp()->GetFont(), Option.c_str(), Color);
    Rect.w = SurfLabel->w + SurfOption->w + HalfOffset*2;
    Rect.h = SurfLabel->h + SurfOption->h; 
  }
}






