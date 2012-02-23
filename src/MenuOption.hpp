#ifndef MENUOPTION_HPP
#define MENUOPTION_HPP

#include "MenuEntry.hpp"

#include <vector>
#include <string>

class MenuOption : public MenuEntry {
public:
  MenuOption (std::string label, std::vector<std::string>& list);
  virtual ~MenuOption();

  static int HalfOffset;

  virtual void OnLeft();
  virtual void OnRight();
  virtual void AddOption(std::string option);
  
  virtual void Render(SDL_Surface* SurfDisplay);
  virtual void SetColor(SDL_Color color);
  virtual void SetPosition(float x, float y);
  virtual void SetOrigin(int origin);

  int GetWidth() const;
  int GetHeight() const;
  
  virtual void Cleanup();
  virtual void Init();

private:
  void SetEntry(int index);
  std::vector<std::string> OptionList;
  std::string  Label;
  std::string  Option;
  SDL_Surface* SurfLabel;
  SDL_Surface* SurfOption;  
  SDL_Color    OptionColor;


  int Index;  
};
	
#endif			   
