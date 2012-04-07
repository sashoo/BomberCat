#include "MenuTable.hpp"

int MenuTable::TotalPlayers = 0;

void MenuTable::MenuTable() {
  TableEntry entry;
  entry.Number = TotalPlayers;
  entry.Input = TotalPlayers;
  entry.Nickname = "Woof";
  Entries.push_back(entry);
  Entries.push_back(entry);
  TotalPlayers = 2;
}

void MenuTable::Add() {
  if (TotalPlayers < MAXCATS) {
    TotalPlayers += 1;
    TableEntry entry;
    entry.Number = TotalPlayers;
    entry.Input = TotalPlayers;
    entry.Nickname = "Woof";
    Entries.push_back(entry);
    Init();
  }      
}

void MenuTable::Remove() {
  if (TotalPlayers > 2) {
    TotalPlayers --;
    Entries.pop();
    Init();
  }
}

void MenuTable::Init() {
  auto iter = Entries.begin();
  int i;
  while (iter != Entries.end()) {
    iter.Init();
    iter.SetPosition(PosX, PosY*32);
    iter++;
    i++
  }
}

void Menutable::SetColor() {
  Color = color;
}

void MenuTable::SetOrigin(origin) {
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

