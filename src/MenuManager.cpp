#include "MenuManager.hpp"
//#include "../../Consts.hpp"
#include "Define.hpp"
#include "MirageApp.hpp"
#include "MenuEntry.hpp"



MenuManager::MenuManager(){
  MMType = MM_CENTERED;
  Index = 0;  
  
  OldTime = 0;

  FontSize = 30;  
  //LineSpacing = Font->GetLineSpacing(FontSize);  
  App = NULL;
  LineSpacing = TTF_FontLineSkip(GSurface::FontRegular);
  //Font = NULL;
}

void MenuManager::Align(int align) {
  MMType = align;
}

void MenuManager::RegisterApp(MirageApp* app) {
  App = app;  
}

// void MenuManager::SetFont (TTF_Font* font) {
//   Font = font;
//   LineSpacing = TTF_FontLineSkip(Font);
// }

MenuManager::~MenuManager(){ 
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
  if (MM_LEFTALIGNED == MMType ) 
    posx -= width/2;
  
  for (iter = Entries.begin(); iter < Entries.end(); ++iter){  
    if (MM_LEFTALIGNED == MMType )
      (*iter)->SetOrigin(ORIGIN_TL);

    // if (MM_CENTERED == MMType )
    //   (*iter)->SetOrigin(ORIGIN_CENTER);

    // if (MM_CENTEREDOPTIONS == MMType )
    //   (*iter)->SetOrigin(ORIGIN_TR);
    
    (*iter)->SetPosition(posx, posy);    

    posy += diff;
  }  
}

void MenuManager::Render(SDL_Surface* SurfDisplay){
  std::vector<MenuEntry*>::iterator iter;
  for (iter = Entries.begin(); iter < Entries.end(); ++iter){
    (*iter)->Render(SurfDisplay);
  }   
}   

MirageApp* MenuManager::GetApp() const {
  return App;
}

int MenuManager::GetFontSize() const {
  return FontSize;
}

int MenuManager::GetLineSpacing() const {
  return LineSpacing;
}

MenuEntry* MenuManager::AddEntry(MenuEntry* entry){
  App->Log << "Adding entry: ";
  entry->RegisterManager(this);
  entry->RegisterApp(GetApp());  
  entry->Init();
  
  Entries.push_back(entry);
  SetEntry(Entries.size()-1);  
  UpdateRect();
  return entry;
}

void MenuManager::Cleanup(){
  App->Log << "----------------------------------------" << std::endl;
  App->Log << "Cleaning entries" << std::endl;
  std::vector<MenuEntry*>::iterator iter;
  for (iter = Entries.begin(); iter < Entries.end(); ++iter){
    (*iter)->Cleanup();    
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
  if(index < (int)Entries.size() && index >=0) {
    Entries[Index]->SetColor(GSurface::ColorInactive);
    Index = index;
    Entries[Index]->SetColor(GSurface::ColorActive);      
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

    case SDLK_LEFT: {
      CurEntry()->OnLeft();
      break;
    }

    case SDLK_RIGHT: {
      CurEntry()->OnRight();
      break;
    }

    case SDLK_RETURN: {
      CurEntry()->OnSelect(NULL, NULL);
      break;
    }

    default: {
      CurEntry()->OnKeyDown(sym, mod, Unicode);
      break;
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
  if(index < (int)Entries.size() && index >=0)
    return Entries[index];
  return NULL;
}

// MenuEntry& MenuManager::operator[] (const int index){
//   if(index < (int)Entries.size() && index >=0)
//     return *Entries[index];
  
// }
  

