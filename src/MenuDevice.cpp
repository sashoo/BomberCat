#include "MenuDevice.hpp"
#include "MenuManager.hpp"
#include "MenuValue.hpp"
#include "Define.hpp"
#include "GSurface.hpp"
#include "MirageApp.hpp"
#include <SDL_ttf.h>
#include <sstream>

MenuDevice::MenuDevice(std::string label) : MenuOption(label) {    
  OptionList.push_back("Key-1");
  OptionList.push_back("Key-2");
  OptionList.push_back("Key-3");
  OptionList.push_back("Key-4");
  OptionList.push_back("Joy-1");
  OptionList.push_back("Joy-2");
  OptionList.push_back("Joy-3");
  OptionList.push_back("Joy-4");  
  Option = OptionList[0].c_str();
  //AssignDevice();
  //UpdateValues();
}

MenuDevice::~MenuDevice() {
}

void MenuDevice::OnLeft() {
  MenuOption::OnLeft();
  AssignDevice();
  UpdateValues();
} 

void MenuDevice::OnRight() {
  MenuOption::OnRight();
  AssignDevice();
  UpdateValues();
}

void MenuDevice::AssignDevice() {
  if (Option == "Key-1") {
    KeyInputHandle = &App->Key1;
    JoyInputHandle = NULL;
  } else if (Option == "Key-2") {
    KeyInputHandle = &App->Key2;
    JoyInputHandle = NULL;
  } else if (Option == "Key-3") {
    KeyInputHandle = &App->Key3;
    JoyInputHandle = NULL;
  } else if (Option == "Key-4") {
    KeyInputHandle = &App->Key4;
    JoyInputHandle = NULL;
  } else if (Option == "Joy-1") {
    KeyInputHandle = NULL;
    JoyInputHandle = &App->Joy1;
  } else if (Option == "Joy-2") {
    KeyInputHandle = NULL;
    JoyInputHandle = &App->Joy2;
  } else if (Option == "Joy-3") {
    KeyInputHandle = NULL;
    JoyInputHandle = &App->Joy3;
  } else if (Option == "Joy-4") {
    KeyInputHandle = NULL;
    JoyInputHandle = &App->Joy4;
  } 
}

void MenuDevice::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 Unicode) {
  if (KeyInputHandle != NULL) {
  }
}

void MenuDevice::AssignSym(int id, SDLKey ksym) {
  if (KeyInputHandle != NULL) {    
    switch (id) {
    case 1:
      KeyInputHandle->kUp = ksym;
      break;
    case 2:
      KeyInputHandle->kDown = ksym;
      break;
    case 3:
      KeyInputHandle->kLeft = ksym;
      break;
    case 4:
      KeyInputHandle->kRight = ksym;
      break;
    case 5:
      KeyInputHandle->kBomb = ksym;
      break;
    default:
      break;
    }
    UpdateValues();
  }
}

void MenuDevice::AddOption(std::string option ) {
  MenuOption::AddOption(option);
}

void MenuDevice::AddValue(MenuValue* value) {
  value->SetOwner(this);  
  Values.push_back(value);  
}

void MenuDevice::UpdateValues() {   
  if (KeyInputHandle != NULL) {
    //App->Log << KeyInputHandle;
    // KeyInputHandle->kUp = SDLK_a;
    std::string s = "Keyboard";
    Values[0]->SetValue(s);

    s = SDL_GetKeyName(KeyInputHandle->kUp);
    Values[1]->SetValue(s);
    s = SDL_GetKeyName(KeyInputHandle->kDown);
    Values[2]->SetValue(s);
    s = SDL_GetKeyName(KeyInputHandle->kLeft);
    Values[3]->SetValue(s);
    s = SDL_GetKeyName(KeyInputHandle->kRight);
    Values[4]->SetValue(s);
    s = SDL_GetKeyName(KeyInputHandle->kBomb);
    Values[5]->SetValue(s);
  } 
  else if (JoyInputHandle != NULL) {
    std::string s = JoyToString(JoyInputHandle->jUp);
    Values[1]->SetValue(s);
    s = JoyToString(JoyInputHandle->jDown);
    Values[2]->SetValue(s);
    s = JoyToString(JoyInputHandle->jLeft);
    Values[3]->SetValue(s);
    s = JoyToString(JoyInputHandle->jRight);
    Values[4]->SetValue(s);
    s = JoyToString(JoyInputHandle->jBomb);
    Values[5]->SetValue(s);
  }
}

void MenuDevice::Render(SDL_Surface* SurfDisplay) {
  MenuOption::Render(SurfDisplay);
}

std::string MenuDevice::JoyToString(JoyHandle& joy) {
  std::string s;
  std::stringstream ss;
  if (JOY_BUTTON == joy.jEntity) {
    ss << "Button #" << (int)joy.Number;
  } 
  else if (JOY_AXIS == joy.jEntity) {
    ss << "Axis ";
    if (1 == joy.Number )
      ss << "Y";
    else if (0 == joy.Number)
      ss << "X";
    else 
      ss << "#" << joy.Number;

    if (joy.Value > 0)
      ss << "+";
    else if (joy.Value < 0)
      ss << "-";
  }
  else if (JOY_HAT == joy.jEntity) {
    ss << "Hat #" << joy.Number << " "; 
    switch (joy.Value) {
    case SDL_HAT_UP:
      ss << "Up";
      break;
    case SDL_HAT_DOWN:
      ss << "Down";
      break;
    case SDL_HAT_LEFT:
      ss << "Left";
      break;
    case SDL_HAT_RIGHT:
      ss << "Right";
      break;
    case SDL_HAT_RIGHTUP:
      ss << "Right+Up";
      break;
    case SDL_HAT_LEFTUP:
      ss << "Left+Up";
      break;
    case SDL_HAT_RIGHTDOWN:
      ss << "Right+Down";
      break;
    case SDL_HAT_LEFTDOWN:
      ss << "Left+Down";
      break;
    }    
  }
  else 
    ss << "Unknown value";
      
  return ss.str(); 
}

void MenuDevice::SetColor(SDL_Color color){
  Color = color;
  if (SurfLabel) 
    SDL_FreeSurface(SurfLabel);
  if (SurfOption)
    SDL_FreeSurface(SurfOption);
  SurfLabel  = TTF_RenderText_Solid(GSurface::FontRegular, Label.c_str(),  Color);  
  SurfOption = TTF_RenderText_Solid(GSurface::FontRegular, Option.c_str(), GSurface::ColorOption);
  Rect.w = SurfLabel->w;
  Rect.h = SurfLabel->h;
}  

void MenuDevice::SetPosition(float x, float y){
  MenuOption::SetPosition(x, y); 
}

void MenuDevice::SetOrigin(int origin) {
  MenuOption::SetOrigin(origin);
}

int MenuDevice::GetWidth() const {
  return MenuOption::GetWidth();
}

int MenuDevice::GetHeight() const {
  return Rect.h;
}

void MenuDevice::Cleanup() {
  MenuOption::Cleanup();
}


void MenuDevice::Init() {
  SurfLabel  = TTF_RenderText_Solid(GSurface::FontRegular, Label.c_str(), GSurface::ColorOption);  
  SurfOption = TTF_RenderText_Solid(GSurface::FontRegular, OptionList[Index].c_str(), GSurface::ColorOption);  
  Rect.w = SurfLabel->w;
  Rect.h = SurfLabel->h;
  App->Log << Label << std::endl;
}

void MenuDevice::SetEntry(int index) {
  MenuOption::SetEntry(index);
}
