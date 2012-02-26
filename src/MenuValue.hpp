#ifndef MENUVALUE_HPP
#define MENUVALUE_HPP

#include "MenuEntry.hpp"

#include <vector>
#include <string>

class MenuDevice;

class MenuValue : public MenuEntry {
public:
  MenuValue (std::string label, std::string value);
  virtual ~MenuValue();

  static int HalfOffset;

  virtual void OnLeft();
  virtual void OnRight(); 
  virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode);
  
  virtual void Render(SDL_Surface* SurfDisplay);
  virtual void SetColor(SDL_Color color);
  virtual void SetPosition(float x, float y);
  virtual void SetOrigin(int origin);
  virtual void SetValue(std::string value);
  virtual void SetID(int id) {ID = id;}
  void SetOwner(MenuDevice* device) {Parent = device;}

  virtual int GetWidth() const;
  virtual int GetHeight() const;
  
  virtual void Cleanup();
  virtual void Init();

protected: 
  std::string  Label;
  std::string  Value;
  SDL_Surface* SurfLabel;
  SDL_Surface* SurfValue;  
  MenuDevice*  Parent;
  SDL_Color    ValueColor;

  int Index;  
  int ID;
};
	
#endif			   
