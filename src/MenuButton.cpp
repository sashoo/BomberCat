#include "MenuButton.hpp"
#include "MenuManager.hpp"
#include "Define.hpp"
#include "GSurface.hpp"
#include "MirageApp.hpp"
#include <SDL_ttf.h>

MenuButton::MenuButton(std::string string){
  Label   = string;  
  Origin  = ORIGIN_TOP;  
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
void MenuButton::Render(SDL_Surface* SurfDisplay) {
  GSurface::Draw(SurfDisplay, Surface, PosX, PosY);
}

void MenuButton::SetColor(SDL_Color color){
  Color = color;
  SDL_FreeSurface(Surface);
  Surface = TTF_RenderText_Solid(GSurface::FontRegular, Label.c_str(), Color);
  Rect.w = Surface->w;
  Rect.h = Surface->h;    
}  

void MenuButton::SetPosition(float x, float y){
  MenuEntry::SetPosition(x, y);
}

void MenuButton::SetOrigin(int origin) {
  Origin = origin;
  //todo
}

void MenuButton::Init(){  
  Surface = TTF_RenderText_Solid(GSurface::FontRegular, Label.c_str(), GSurface::ColorRed);
  Rect.w   = Surface->w;
  Rect.h  = Surface->h; 
  //Color = mMenuManager->InactiveColor;  
  App->Log << Label << std::endl;
}

void MenuButton::Cleanup(){
  //mApp->Log << "Deleting MenuButton \"" << Label << "\": ";
  App->Log << "Deleting entry: " << Label << "... ";
  SDL_FreeSurface(Surface);
  App->Log << "deleted" << std::endl;
  //delete Label;
  //Label = NULL;
  //mApp->mLog << "Success!" << std::endl;
}


