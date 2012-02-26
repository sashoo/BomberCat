#include "MenuValue.hpp"
#include "MenuManager.hpp"
#include "MenuDevice.hpp"
#include "Define.hpp"
#include "GSurface.hpp"
#include "MirageApp.hpp"
#include <SDL_ttf.h>

int MenuValue::HalfOffset = 0;

MenuValue::MenuValue(std::string label, std::string value) {
  Label = label;     
  Value = value;
  Origin = ORIGIN_TR;
  Index = 0;  
  ID = 0;
}

MenuValue::~MenuValue() {
}

void MenuValue::OnLeft() {
}

void MenuValue::OnRight() {
}

void MenuValue::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode) {  
  Parent->AssignSym(ID, sym);
}

void MenuValue::Render(SDL_Surface* SurfDisplay) {
  if (SurfLabel)
    GSurface::Draw(SurfDisplay, SurfLabel,  PosX, PosY);
  if (SurfValue)
    GSurface::Draw(SurfDisplay, SurfValue, PosX+Rect.w, PosY);
}

void MenuValue::SetColor(SDL_Color color){
  Color = color;
  if (SurfLabel) 
    SDL_FreeSurface(SurfLabel);
  if (SurfValue)
    SDL_FreeSurface(SurfValue);
  SurfLabel = TTF_RenderText_Solid(GSurface::FontRegular, Label.c_str(),  Color);  
  SurfValue = TTF_RenderText_Solid(GSurface::FontRegular, Value.c_str(), GSurface::ColorOption);
  Rect.w = SurfLabel->w;
  Rect.h = SurfLabel->h;
}  

void MenuValue::SetPosition(float x, float y){
  MenuEntry::SetPosition(x, y); 
}

void MenuValue::SetOrigin(int origin) {
  Origin = origin;  
}

int MenuValue::GetWidth() const {
  return Rect.w;
}

int MenuValue::GetHeight() const {
  return Rect.h;
}

void MenuValue::Cleanup() {
  if (SurfLabel)
    SDL_FreeSurface(SurfLabel);
  if (SurfValue)
    SDL_FreeSurface(SurfValue);  
}

void MenuValue::Init() {
  //Index = 0;  
  SurfLabel = TTF_RenderText_Solid(GSurface::FontRegular, Label.c_str(), GSurface::ColorOption);  
  SurfValue = TTF_RenderText_Solid(GSurface::FontRegular, Value.c_str(), GSurface::ColorOption);  
  Rect.w = SurfLabel->w;
  Rect.h = SurfLabel->h;
  App->Log << Label << std::endl;
}

void MenuValue::SetValue(std::string value) {
  Value = value;
  if (SurfValue) 
    SDL_FreeSurface(SurfValue);  
  SurfValue = TTF_RenderText_Solid(GSurface::FontRegular, Value.c_str(), GSurface::ColorOption);  
}
