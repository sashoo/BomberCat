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

enum {
  MM_LEFTALIGNED = 0,
  MM_CENTERED,
  MM_CENTEREDOPTIONS
};
        
class MenuManager{
public:
  MenuManager();
  ~MenuManager();     

  void RegisterApp(MirageApp* app);
  // void SetFont(TTF_Font* font);
  
  void Render(SDL_Surface* SurfDisplay); //draw
  //recalculate entries, align them properly, set big bounding rectangle
  //for MenuManager and indibidual rectangles for entries
  void UpdateRect();
  void Cleanup();

  // handle input
  void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode);
  void OnLButtonDown(int mX, int mY); 
  void OnRButtonDown(int mX, int mY); 
  void OnMButtonDown(int mX, int mY); 
  void OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);
  // aligns menu options according to MMType provided
  void Align(int align);
  MirageApp* GetApp() const;
  int GetFontSize() const;
  int GetLineSpacing() const; 
  int MMType;

  // Entries    
  MenuEntry* AddEntry(MenuEntry* entry);
 

  // access
  MenuEntry* CurEntry();
  int GetIndex();
  void SetEntry(const int index);
  void PrevEntry();
  void NextEntry();
  MenuEntry* at(const int index); 
  //MenuEntry& operator[] (const int index);

  friend class MenuButton;

private:
  std::vector<MenuEntry*>  Entries;
  int                      Index;
 

  //TTF_Font*                Font;
  int                      FontSize;
  int                      LineSpacing;
  MirageApp*               App;
  SDL_Rect                 Rect;
  long                     OldTime;   
};




#endif //MENUMANAGER_HPP
