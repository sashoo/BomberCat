#include "MenuManager.hpp"
//#include "../../Consts.hpp"
#include "Define.hpp"
#include "MirageApp.hpp"
#include "MenuEntry.hpp"

bool DotInRect(int dotx, int doty, SDL_Rect rect) {
  if (dotx < rect.x || dotx > rect.x + rect.w ||
      doty < rect.y || doty > rect.y + rect.h)
    return false;
  return true;
}

MenuManager::MenuManager(){
  Index = 0; 
  //  ActiveColor = {30, 140, 230};
  ActiveColor.r = 30;
  ActiveColor.g = 140;
  ActiveColor.b = 230;
  OldTime = 0;
  //InactiveColor = {180, 180, 180}; 
  InactiveColor.r = 180;
  InactiveColor.g = 180;
  InactiveColor.b = 180;
  FontSize = 30;  
  //LineSpacing = Font->GetLineSpacing(FontSize);  
  App = NULL;
  Font = NULL;
}

void MenuManager::RegisterApp(MirageApp* app) {
  App = app;  
}

void MenuManager::SetFont (TTF_Font* font) {
  Font = font;
  LineSpacing = TTF_FontLineSkip(Font);
}

MenuManager::~MenuManager(){
  App->Log << "Entering MenuManager destructor" << std::endl;
  App->Log << "Leaving MenuManager destructor" << std::endl; 
  //App = NULL;
  //Font = NULL;  
}

void MenuManager::UpdateRect(){
  //float height = (FontSize+LineSpacing) * Entries.size();
  float height = 0.f;
  float width = Entries[0]->GetWidth();
  std::vector<MenuEntry*>::iterator iter;
  for (iter = Entries.begin(); iter < Entries.end(); ++iter){
    if ((*iter)->GetWidth() > width)
      width = (*iter)->GetWidth();
    height+=(*iter)->GetHeight();
  }
  Rect.w  = width;
  Rect.h  = height;
  float screenX = GWIDTH/2;
  float screenY = GHEIGHT/2;
  Rect.x = screenX-width/2;
  Rect.y = screenY-height/2; 
  float posx = screenX;
  float posy = Rect.y;
  float diff = /*FontSize + */LineSpacing;
  for (iter = Entries.begin(); iter < Entries.end(); ++iter){
    (*iter)->SetPosition(posx, posy);

    posy += diff;
  }  
}

void MenuManager::OnRender(SDL_Surface* SurfDisplay){
  std::vector<MenuEntry*>::iterator iter;
  for (iter = Entries.begin(); iter < Entries.end(); ++iter){
    (*iter)->OnRender(SurfDisplay);
  }   
}   

MirageApp* MenuManager::GetApp() const {
  return App;
}

TTF_Font* MenuManager::GetFont() const {
  return Font;
}

int MenuManager::GetFontSize() const {
  return FontSize;
}

int MenuManager::GetLineSpacing() const {
  return LineSpacing;
}

SDL_Color MenuManager::GetActiveColor() const {
  return ActiveColor;
}

SDL_Color MenuManager::GetInactiveColor() const {
  return InactiveColor;
}

MenuEntry* MenuManager::AddEntry(MenuEntry* entry){
  App->Log << "Adding entry: ";
  entry->RegisterManager(this);
  entry->RegisterApp(GetApp());  
  entry->Setup();
  
  Entries.push_back(entry);
  SetEntry(Entries.size()-1);  
  UpdateRect();
  return entry;
}

void MenuManager::CleanUp(){
  App->Log << "----------------------------------------" << std::endl;
  App->Log << "Cleaning entries" << std::endl;
  std::vector<MenuEntry*>::iterator iter;
  for (iter = Entries.begin(); iter < Entries.end(); ++iter){
    (*iter)->Clean();    
  }
  Entries.clear();
  App->Log << "All entries deleted from main menu" << std::endl;
}
  
MenuEntry* MenuManager::CurEntry() {
  return Entries[Index];
}

int MenuManager::GetIndex(){
  return Index;
}

void MenuManager::SetEntry(const int index){
  if(index < Entries.size() && index >=0) {
    Entries[Index]->SetColor(InactiveColor);
    Index = index;
    Entries[Index]->SetColor(ActiveColor);      
  }
}



void MenuManager::PrevEntry(){
  int index = Index-1;
  SetEntry(index);
}

void MenuManager::NextEntry(){
  int index = Index+1;
  SetEntry(index);
}

void MenuManager::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode) {
  if (OldTime + 150 > SDL_GetTicks()) 
     return;

  OldTime = SDL_GetTicks();
  
    switch (sym) {
    case SDLK_UP: {
      PrevEntry();
      break;
    }

    case SDLK_DOWN: {
      NextEntry();
      break;
    }

    case SDLK_RETURN: {
      CurEntry()->OnSelect(NULL, NULL);
      break;
    }

    default: {
    }

    }	      
}

void MenuManager::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode) {
}  

void MenuManager::OnLButtonDown(int mX, int mY) {
  std::vector<MenuEntry*>::iterator iter;
  for (iter = Entries.begin(); iter < Entries.end(); ++iter) {
    if (DotInRect(mX, mY, (*iter)->Rect)) {
      int i = std::distance(Entries.begin(), iter);
      SetEntry(i);
      CurEntry()->OnSelect(NULL, NULL);
      break;
    }
  }
 
}
void MenuManager::OnRButtonDown(int mX, int mY) {  
}

void MenuManager::OnMButtonDown(int mX, int mY) {  
}

void MenuManager::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {  
  std::vector<MenuEntry*>::iterator iter;
  for (iter = Entries.begin(); iter < Entries.end(); ++iter) {
    if (DotInRect(mX, mY, (*iter)->Rect)) {
      int i = std::distance(Entries.begin(), iter);
      SetEntry(i);
      break;
    }
  }
}


  
MenuEntry* MenuManager::at(const int index){
  if(index < Entries.size() && index >=0)
    return Entries[index];
}

MenuEntry& MenuManager::operator[] (const int index){
  if(index < Entries.size() && index >=0)
    return *Entries[index];
}
  

