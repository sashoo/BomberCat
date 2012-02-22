#ifndef MENUBUTTON_HPP
#define MENUBUTTON_HPP

#include "MenuEntry.hpp"

class MenuButton : public MenuEntry{
public:
  MenuButton(std::string string);
  virtual ~MenuButton();

  virtual void OnRender(SDL_Surface* SurfDisplay);
  virtual void SetColor(SDL_Color color);
  virtual void SetPosition(float x, float y);
  virtual void SetOrigin(int origin);

  int GetWidth() const;
  int GetHeight() const;

  virtual void Clean();
  virtual void Setup();  

private:
  std::string      Label;
  SDL_Surface*     Surface; 

}; // class MenuButton

#endif // MENUBUTTON_HPP
