#ifndef MENUENTRY_HPP
#define MENUENTRY_HPP

#include <SDL.h>
#include <string>

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
  virtual void SetPosition(float x, float y) = 0;  
  virtual void SetOrigin(int origin) = 0;
  virtual void OnRender(SDL_Surface* SurfDisplay) = 0;
  virtual int GetWidth() const = 0;
  virtual int GetHeight() const = 0;
  virtual void Clean() = 0;  
  //std::string GetLabel() const {return mLabel;}
  virtual void* GetChoice(){}
  
protected:
  MenuManager*     mMenuManager;
  MirageApp*       App;
  float            PosX;
  float            PosY;
  SDL_Rect         Rect;
  SDL_Color        Color;  

  friend class MenuManager;

}; // class MenuEntry



#endif // MENUENTRY_HPP
