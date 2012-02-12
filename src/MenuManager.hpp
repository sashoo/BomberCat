#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
//#include "../../Core/App.hpp"

//#include "MenuButton.hpp"
//#include "MenuBoolOption.hpp"
//#include "MenuOption.hpp"
//class MenuButton;
//class MenuBoolOption;
//class MenuOption;
class MenuEntry;
class MirageApp;
        
class MenuManager{
public:
  MenuManager();
  ~MenuManager();   

  void RegisterApp(MirageApp* app);
  void SetFont(TTF_Font* font);
    
  void UpdateRect();
  void OnRender(SDL_Surface* SurfDisplay); //draw
  void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnLButtonDown(int mX, int mY); 
  void OnRButtonDown(int mX, int mY); 
  void OnMButtonDown(int mX, int mY); 
  void OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);
  MirageApp* GetApp() const;
  TTF_Font* GetFont() const;
  int GetFontSize() const;
  int GetLineSpacing() const;
  SDL_Color GetActiveColor() const;
  SDL_Color GetInactiveColor() const;

  // Entries    
  MenuEntry* AddEntry(MenuEntry* entry);
  void CleanUp();

  // access
  MenuEntry* CurEntry();
  int GetIndex();
  void SetEntry(const int index);
  void PrevEntry();
  void NextEntry();
  MenuEntry* at(const int index); 
  MenuEntry& operator[] (const int index);

  friend class MenuButton;

private:
  std::vector<MenuEntry*>  Entries;
  int                      Index;
  SDL_Color                ActiveColor;
  SDL_Color                InactiveColor;

  TTF_Font*                Font;
  int                      FontSize;
  int                      LineSpacing;
  MirageApp*               App;
  SDL_Rect                 Rect;
  long                     OldTime;   
};




#endif //MENUMANAGER_HPP
