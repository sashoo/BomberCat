#ifndef MENUENTRY_HPP
#define MENUENTRY_HPP

#include <SDL.h>
#include <string>
#include "Origin.hpp"
#include <functional>

class MenuManager;
class MirageApp;

class MenuEntry{
public:
  MenuEntry(){}
  virtual ~MenuEntry(){}
  void OnSelect(MirageApp* app, void* data) {
    if (SelectHandler)
      SelectHandler(app, data);
  }

  void SetSelect(std::function<void(MirageApp*, void*)> handler) {
    SelectHandler = handler;
  }

  //void (*OnSelect) (MirageApp* app, void* pData);  
  virtual void OnLeft (){} 
  virtual void OnRight(){}
  virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode) {}

  void RegisterManager(MenuManager* menuManager){mMenuManager = menuManager;}
  void RegisterApp(MirageApp* app) {App = app;}
  SDL_Rect GetRect() {return Rect;} 

  virtual void Init() = 0;    
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
  virtual void Render(SDL_Surface* SurfDisplay) = 0;
  virtual int GetWidth() const = 0;
  virtual int GetHeight() const = 0;
  virtual void Cleanup() = 0;  
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
  std::function<void(MirageApp*, void*)> SelectHandler;

  friend class MenuManager;

}; // class MenuEntry



#endif // MENUENTRY_HPP
