#ifndef MENUOPTION_HPP
#define MENUOPTION_HPP

#include "MenuEntry.hpp"
#include "Origin.hpp"
#include <vector>
#include <string>

class MenuOption : public MenuEntry {
public:
  MenuOption (std::string label, float halfOffset);
  virtual ~MenuOption();

  virtual void OnLeft();
  virtual void OnRight();
  
  virtual void OnRender(SDL_Surface* SurfDisplay);
  virtual void SetColor(SDL_Color color);
  virtual void SetPosition(float x, float y);
  virtual void SetOrigin(int origin);

  int GetWidth() const;
  int GetHeight() const;
  
  virtual void Clean();
  virtual void Setup();

private:
  void SetEntry(int index);
  std::vector<std::string> OptionList;
  std::string  Label;
  std::string  Option;
  SDL_Surface* SurfLabel;
  SDL_Surface* SurfOption;
  int          Origin;
  int          HalfOffset;

  int Index;  
};
	
#endif			   
