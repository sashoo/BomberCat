#ifndef MENUOPTION_HPP
#define MENUOPTION_HPP

#include "MenuEntry.hpp"

#include <vector>
#include <string>

class MenuOption : public MenuEntry {
public:
  MenuOption (std::string label);
  virtual ~MenuOption();

  static int HalfOffset;

  virtual void OnLeft();
  virtual void OnRight();
  virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode){}
  virtual void AddOption(std::string option);
  
  virtual void Render(SDL_Surface* SurfDisplay);
  virtual void SetColor(SDL_Color color);
  virtual void SetPosition(float x, float y);
  virtual void SetOrigin(int origin);

  virtual int GetWidth() const;
  virtual int GetHeight() const;
  
  virtual void Cleanup();
  virtual void Init();

protected:
  virtual void SetEntry(int index);
  std::vector<std::string> OptionList;
  std::string  Label;
  std::string  Option;
  SDL_Surface* SurfLabel;
  SDL_Surface* SurfOption;  
  SDL_Color    OptionColor;

  int Index;  
};
	
#endif			   
