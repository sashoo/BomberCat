#ifndef MENUENTRY_HPP
#define MENUENTRY_HPP

#include <SDL.h>
#include <string>
#include "Origin.hpp"

class MenuManager;
class MirageApp;

class MenuEntry{
public:
  MenuEntry(){}
  virtual ~MenuEntry(){}
  void (*OnSelect) (MirageApp* app, void* pData);  
  virtual void OnLeft (){} 
  virtual void OnRight(){}

  void RegisterManager(MenuManager* menuManager){mMenuManager = menuManager;}
  void RegisterApp(MirageApp* app) {App = app;}
  SDL_Rect GetRect() {return Rect;} 

  virtual void Setup() = 0;    
  virtual void SetColor(SDL_Color color) = 0;    
  virtual void SetPosition(float x, float y) {
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
  virtual void SetOrigin(int origin) = 0;
  virtual void OnRender(SDL_Surface* SurfDisplay) = 0;
  virtual int GetWidth() const = 0;
  virtual int GetHeight() const = 0;
  virtual void Clean() = 0;  
  //std::string GetLabel() const {return mLabel;}
  virtual void* GetChoice(){ return NULL; }
  
protected:
  MenuManager*     mMenuManager;
  MirageApp*       App;
  float            PosX;
  float            PosY;
  SDL_Rect         Rect;
  SDL_Color        Color;  
  int              Origin;

  friend class MenuManager;

}; // class MenuEntry



#endif // MENUENTRY_HPP
