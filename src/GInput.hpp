#ifndef GINPUT_HPP
#define GINPUT_HPP

//#include "GBomber.hpp"
const int JOYSENSE = 8000;

class GBomber;

enum JoyEntity {
  JOY_BUTTON = 0,
  JOY_AXIS = 1,
  JOY_HAT = 2   
};

// represents basic game input
// perfectly suitable for keyboard
struct Input {  
  Input();
  bool bUp;
  bool bDown;
  bool bLeft;
  bool bRight;
  bool bBomb; 
  
  GBomber* Bomber; // Bomber to be controlled
  
  // Moves player according to the flags.
  // StateGame::OnLoop() calls this function for each
  // Input struct before entity update routines take place
  void HandleInput();
};

struct KeyInput : Input {
  KeyInput();
  SDLKey kUp;
  SDLKey kDown;
  SDLKey kLeft;
  SDLKey kRight;
  SDLKey kBomb;   

  // Two functions below set flags according
  // to the keys (un)pressed
  // StateGame::OnEvent() calls them
  void OnKeyDown(SDLKey sym);
  void OnKeyUp(SDLKey sym);
};

// represents any "entity" of joystick:
// axis, hat or button, and stores its value
struct JoyHandle {  
  // Type of Entity: axis, hat or button
  int jEntity;

  // axis, hat or button number
  Uint8 Number;

  // value of axis or hat; has no meaning for buttons
  // since axis values are Sint16, hat values are Uint8,
  // Uint32 is used to hold all kinds of data (FIXME?)
  Uint32 Value;
};

// Represents joystick controller
struct JoyInput : Input {  
  JoyInput();
  Uint8 Which; // joystick identifier
  JoyHandle jUp;
  JoyHandle jDown;
  JoyHandle jLeft;
  JoyHandle jRight;
  JoyHandle jBomb;

  void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value); 
  void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value); 
  void OnJoyButtonDown(Uint8 which, Uint8 button);    
  void OnJoyButtonUp(Uint8 which, Uint8 button);   
};

#endif
