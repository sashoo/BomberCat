#include "MenuOption.hpp"
#include "MenuManager.hpp"
#include "Define.hpp"
#include "GSurface.hpp"
#include "MirageApp.hpp"
#include <SDL_ttf.h>

int MenuOption::HalfOffset = 0;

MenuOption::MenuOption(std::string label, std::vector<std::string>& list) {
  Label = label; 
  OptionList = list;
  Option = OptionList[0];
  Origin = ORIGIN_TR;
  Index = 0;  
}

MenuOption::~MenuOption() {
}

void MenuOption::OnLeft() {
  int index = Index - 1;
  SetEntry(index);
}

void MenuOption::OnRight() {
  int index = Index + 1;
  SetEntry(index);
}

void MenuOption::AddOption(std::string option ) {
  OptionList.push_back(option);
}

void MenuOption::Render(SDL_Surface* SurfDisplay) {
  //int lposx = PosX - SurfLabel->w - HalfOffset;
  GSurface::Draw(SurfDisplay, SurfLabel,  PosX, PosY);
  GSurface::Draw(SurfDisplay, SurfOption, PosX+Rect.w, PosY);
}

void MenuOption::SetColor(SDL_Color color){
  Color = color;
  if (SurfLabel) 
    SDL_FreeSurface(SurfLabel);
  if (SurfOption)
    SDL_FreeSurface(SurfOption);
  SurfLabel  = TTF_RenderText_Solid(GSurface::FontRegular, Label.c_str(),  Color);  
  SurfOption = TTF_RenderText_Solid(GSurface::FontRegular, Option.c_str(), GSurface::ColorOption);
  Rect.w = SurfLabel->w;
  Rect.h = SurfLabel->h;
}  

void MenuOption::SetPosition(float x, float y){
  MenuEntry::SetPosition(x, y); 
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

void MenuOption::Cleanup() {
  if (SurfLabel)
    SDL_FreeSurface(SurfLabel);
  if (SurfOption)
    SDL_FreeSurface(SurfOption);  
}


void MenuOption::Init() {
  //Index = 0;  
  SurfLabel = TTF_RenderText_Solid(GSurface::FontRegular, Label.c_str(), GSurface::ColorOption);  
  SurfOption = TTF_RenderText_Solid(GSurface::FontRegular, OptionList[Index].c_str(), GSurface::ColorOption);  
  Rect.w = SurfLabel->w;
  Rect.h = SurfLabel->h;
  App->Log << Label << std::endl;
}

void MenuOption::SetEntry(int index) {
  if (index >= 0 && !OptionList.empty() && index < OptionList.size()) {
    Index = index;
    Option = OptionList[Index]; 
    SetColor(Color);
  }
}






