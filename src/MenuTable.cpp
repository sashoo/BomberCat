#include "MenuTable.hpp"
#include "MenuTableEntry.hpp"
#include "Define.hpp"
#include "MirageApp.hpp"

int MenuTable::TotalPlayers = 0;

MenuTable::MenuTable() {
  TotalPlayers = 0;
  PosX = 0.0f;
  PosY = 0.0f;
}

void MenuTable::Add() {
  if (TotalPlayers < MAXCATS) {
    TotalPlayers += 1;
    MenuTableEntry* entry = new MenuTableEntry();
    entry->Number = TotalPlayers;
    entry->InputType = TotalPlayers;
    entry->Nickname = "Woof";
    entry->RegisterApp(App);
    //entry->SetPosition(PosX+200, 100*TotalPlayers);
    //App->Log << "x: " << PosX << " y: " << PosY+(TotalPlayers)*100 << std::endl;
    //App->Log << "Players: " << TotalPlayers << std::endl;
    Entries.push_back(entry);
    Init();
  }      
}

void MenuTable::Remove() {
  if (TotalPlayers > 2) {
    TotalPlayers --;
    Entries.pop_back();
    Init();
  }
}

void MenuTable::Init() {
  App->Log << PosX << " " << PosY;
  auto iter = Entries.begin();
  int i = 0;
  while (iter != Entries.end()) {
    (*iter)->Init();
    (*iter)->SetPosition(PosX, this->PosY+32*i);
    iter++;
    i++;
  }
}

void MenuTable::SetColor(SDL_Color color) {
  Color = color;
}

void MenuTable::SetOrigin(int origin) {
  Origin = origin;
}

void MenuTable::Render(SDL_Surface* SurfDisplay) {
  auto iter = Entries.begin();
  while (iter != Entries.end()) {
    (*iter)->Render(SurfDisplay);
    iter++;
  }
}

int MenuTable::GetWidth() const {
  return 0;
}

int MenuTable::GetHeight() const {
  return 0;
}

void MenuTable::Cleanup() {
  auto iter = Entries.begin();
  while (iter != Entries.end()) {
    (*iter)->Cleanup();
    iter++;
  }
  Entries.clear();
}

void MenuTable::SetPosition(float x, float y) {
  PosX = x;
  PosY = y;
  int i = 0;
  auto iter = Entries.begin();
  while (iter != Entries.end()) {
    (*iter)->SetPosition(PosX, PosY+32*i);
    i++;
    iter++;
  }
}

void MenuTable::FillMap(){
  auto iter = Entries.begin();
  while (iter != Entries.end()) {
    KeyMap map;
    map.input = (*iter)->InputType;
    map.bomber = (*iter)->Number-1;
    BomberMap.push_back(map);
    iter++;
  }
}
//    if (ORIGIN_CENTER == Origin) {
//      PosX = x - Rect.w/2;
//      PosY = y - Rect.h/2;    
//    }
//    else if (ORIGIN_TL == Origin) {
//      PosX = x;
//      PosY = y;
//    }   
//    else if (ORIGIN_TR == Origin) {
//      PosX = x - Rect.w;
//      PosY = y;
//    } 
//    else if (ORIGIN_TOP == Origin) {
//      PosX = x - Rect.w/2;
//      PosY = y;
//    }  
//    else if (ORIGIN_TR == Origin) {
//      PosX = x - Rect.w;
//      PosY = y;
//    }      
//    Rect.x = PosX;
//    Rect.y = PosY; 
//  }  

