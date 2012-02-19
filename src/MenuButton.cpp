#include "MenuButton.hpp"
#include "MenuManager.hpp"
#include "Define.hpp"
#include "GSurface.hpp"
#include "MirageApp.hpp"
#include <SDL_ttf.h>

MenuButton::MenuButton(std::string string){
  Label   = string;  
  Origin  = ORIGIN_CENTER;  
}

int MenuButton::GetWidth() const {
  return Rect.w;
}

int MenuButton::GetHeight() const {
  return Rect.h;
}

MenuButton::~MenuButton(){ 
    
}

//implement
void MenuButton::OnRender(SDL_Surface* SurfDisplay) {
  GSurface::OnDraw(SurfDisplay, Surface, PosX, PosY);
}

void MenuButton::SetColor(SDL_Color color){
  Color = color;
  SDL_FreeSurface(Surface);
  Surface = TTF_RenderText_Solid(GSurface::FontRegular, Label.c_str(), Color);
  Rect.w = Surface->w;
  Rect.h = Surface->h;    
}  

void MenuButton::SetPosition(float x, float y){
  if (ORIGIN_CENTER == Origin) {
    PosX = x - Rect.w/2;
    PosY = y - Rect.h/2;    
  }
  else {
    PosX = x;
    PosY = y;
  }      
  Rect.x = PosX;
  Rect.y = PosY; 
}

void MenuButton::SetOrigin(int origin) {
  Origin = origin;
  //todo
}

void MenuButton::Setup(){
  Color   = mMenuManager->InactiveColor;
  Surface = TTF_RenderText_Solid(GSurface::FontRegular, Label.c_str(), Color);
  Rect.w   = Surface->w;
  Rect.h  = Surface->h; 
  //Color = mMenuManager->InactiveColor;  
  App->Log << Label << std::endl;
}

void MenuButton::Clean(){
  //mApp->Log << "Deleting MenuButton \"" << Label << "\": ";
  App->Log << "Deleting entry: " << Label << "... ";
  SDL_FreeSurface(Surface);
  App->Log << "deleted" << std::endl;
  //delete Label;
  //Label = NULL;
  //mApp->mLog << "Success!" << std::endl;
}


