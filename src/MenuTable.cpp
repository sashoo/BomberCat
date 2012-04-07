#include "MenuTable.hpp"
#include "MenuTableEntry.hpp"
#include "Define.hpp"

int MenuTable::TotalPlayers = 0;

MenuTable::MenuTable() {
  
}

void MenuTable::Add() {
  if (TotalPlayers < MAXCATS) {
    TotalPlayers += 1;
    MenuTableEntry entry;
    entry.Number = TotalPlayers;
    entry.InputType = TotalPlayers;
    entry.Nickname = "Woof";
    entry.RegisterApp(App);
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
  auto iter = Entries.begin();
  int i;
  while (iter != Entries.end()) {
    iter->Init();
    iter->SetPosition(PosX, PosY*32);

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
    iter->Render(SurfDisplay);
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
    iter->Cleanup();
    iter++;
  }
  Entries.clear();
}

void MenuTable::SetPosition(float x, float y) {
   if (ORIGIN_CENTER == Origin) {
     PosX = x - Rect.w/2;
     PosY = y - Rect.h/2;    
   }
   else if (ORIGIN_TL == Origin) {
     PosX = x;
     PosY = y;
   }   
   else if (ORIGIN_TR == Origin) {
     PosX = x - Rect.w;
     PosY = y;
   } 
   else if (ORIGIN_TOP == Origin) {
     PosX = x - Rect.w/2;
     PosY = y;
   }  
   else if (ORIGIN_TR == Origin) {
     PosX = x - Rect.w;
     PosY = y;
   }      
   Rect.x = PosX;
   Rect.y = PosY; 
 }  

