#ifndef MENUBOOLOPTION_HPP
#define MENUBOOLOPTION_HPP

#include "MenuEntry.hpp"
#include <string>

class MenuBoolOption : public MenuEntry {
public:
  MenuBoolOption (std::string label, std::string on = "On", std::string off = "Off");
  virtual ~MenuBoolOption();

  static int HalfOffset;

  virtual void OnLeft();
  virtual void OnRight();
    
  virtual void OnRender(SDL_Surface* SurfDisplay);
  virtual void SetColor(SDL_Color color);
  virtual void SetPosition(float x, float y);
  virtual void SetOrigin(int origin);

  void SetChoice (bool choice);

  int GetWidth() const;
  int GetHeight() const;
  
  virtual void Clean();
  virtual void Setup();

private:

  std::string  Label;
  std::string  Option;
  std::string  On;
  std::string  Off;
  SDL_Surface* SurfLabel;
  SDL_Surface* SurfOption;  
  bool         Choice;
};
	
#endif			   
