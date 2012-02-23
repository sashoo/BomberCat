#include "MenuBoolOption.hpp"
#include "MenuManager.hpp"
#include "Define.hpp"
#include "GSurface.hpp"
#include "MirageApp.hpp"
#include <SDL_ttf.h>

int MenuBoolOption::HalfOffset = 0;

MenuBoolOption::MenuBoolOption(std::string label, std::string on, std::string off) {
  Label = label;   
  On = on;
  Off = off;
  Option = On;
  Origin = ORIGIN_TR; 
  Choice = true;
}

MenuBoolOption::~MenuBoolOption() {
}

void MenuBoolOption::OnLeft() {
  SetChoice(!Choice);
}

void MenuBoolOption::OnRight() {
  SetChoice(!Choice);
}

void MenuBoolOption::SetChoice (bool choice) {
  Choice = choice;
  if (SurfOption)
    SDL_FreeSurface(SurfOption);

  
  if (Choice) {
    Option = On;
    SurfOption = TTF_RenderText_Solid(GSurface::FontRegular, Option.c_str(), GSurface::ColorGreen);
  }
  else {
    Option = Off;
    SurfOption = TTF_RenderText_Solid(GSurface::FontRegular, Option.c_str(), GSurface::ColorRed);    
  }
}

void MenuBoolOption::Render(SDL_Surface* SurfDisplay) {
  //int lposx = PosX - SurfLabel->w - HalfOffset;
  GSurface::Draw(SurfDisplay, SurfLabel,  PosX, PosY);
  GSurface::Draw(SurfDisplay, SurfOption, PosX+Rect.w, PosY);
}

void MenuBoolOption::SetColor(SDL_Color color){
  Color = color;
  if (SurfLabel) 
    SDL_FreeSurface(SurfLabel);
  // if (SurfOption)
  //   SDL_FreeSurface(SurfOption);
  SurfLabel  = TTF_RenderText_Solid(GSurface::FontRegular, Label.c_str(),  Color);
  SetChoice(Choice);
  Rect.w = SurfLabel->w;
  Rect.h = SurfLabel->h;
}  

void MenuBoolOption::SetPosition(float x, float y){
  MenuEntry::SetPosition(x, y); 
}

void MenuBoolOption::SetOrigin(int origin) {
  Origin = origin;  
}

int MenuBoolOption::GetWidth() const {
  return Rect.w;
}

int MenuBoolOption::GetHeight() const {
  return Rect.h;
}

void MenuBoolOption::Cleanup() {
  App->Log << "Deleting entry: " << Label << "... ";
  SDL_FreeSurface(SurfLabel);
  SDL_FreeSurface(SurfOption);
  App->Log << "deleted" << std::endl;
}

void MenuBoolOption::Init() {
  //Index = 0;
  
  SurfLabel  = TTF_RenderText_Solid(GSurface::FontRegular,  Label.c_str(), GSurface::ColorActive);  
  SurfOption = TTF_RenderText_Solid(GSurface::FontRegular, Option.c_str(), GSurface::ColorInactive);  
  Rect.w = SurfLabel->w;
  Rect.h = SurfLabel->h;
  App->Log << Label << std::endl;
}







