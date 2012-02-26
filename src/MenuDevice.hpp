#ifndef MENUDEVICE_HPP
#define MENUDEVICE_HPP

#include "MenuOption.hpp"

#include <vector>
#include <string>
#include "GInput.hpp"

class MenuValue;


class MenuDevice : public MenuOption {
public:
  MenuDevice (std::string label);
  virtual ~MenuDevice(); 

  virtual void OnLeft();
  virtual void OnRight();
  virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode);
  // Sets one of the device pointers in response
  // to device label change
  virtual void AssignDevice();
  void AssignSym(int id, SDLKey ksym);

  virtual void AddOption(std::string option);
  virtual void AddValue(MenuValue* value);
  virtual void UpdateValues();

  virtual std::string JoyToString(JoyHandle& joy);
  
  virtual void Render(SDL_Surface* SurfDisplay);
  virtual void SetColor(SDL_Color color);
  virtual void SetPosition(float x, float y);
  virtual void SetOrigin(int origin);

  int GetWidth() const;
  int GetHeight() const;
  
  virtual void Cleanup();
  virtual void Init();

protected:
  std::vector<MenuValue*> Values;
  virtual void SetEntry(int index);

  KeyInput*           KeyInputHandle;
  JoyInput*           JoyInputHandle;
 
};
	
#endif			   
