#include "GBomber.hpp"

Input::Input() {
  bUp = false;
  bDown = false;
  bLeft = false;
  bRight = false;
  bBomb = false;
  Bomber = NULL;
}

void Input::HandleInput() {
  if (NULL != Bomber) {
    if (Bomber->App->NetMode != GAME_CLIENT) {
      Bomber->MoveUp    = bUp;
      Bomber->MoveDown  = bDown;
      Bomber->MoveLeft  = bLeft;
      Bomber->MoveRight = bRight;
    } else {
      Bomber->ServerMove(bUp, bDown, bLeft, bRight);
    }
    if (bBomb)
      Bomber->PlaceBomb();
  }
}

void Input::Connect(GBomber* bomber) {
  if (bomber != NULL) {
    if (Bomber != NULL)
      Disconnect();
    Bomber = bomber;
    Bomber->InputHandle = this;
  }
}

void Input::Disconnect() {
  if (Bomber != NULL) {
    Bomber->InputHandle = NULL;
    Bomber->MoveUp    = false;
    Bomber->MoveDown  = false;
    Bomber->MoveRight = false;
    Bomber->MoveLeft  = false;
    bUp = false;
    bDown = false;
    bLeft = false;
    bRight = false;
    bBomb = false;
    Bomber = NULL;
  }
}

KeyInput::KeyInput() {
  // kUp = 0;
  // kDown = 0;
  // kLeft = 0;
  // kRight = 0;
  // kBomb = 0;
}

void KeyInput::OnKeyDown(SDLKey sym) {
  if (NULL != Bomber ) {
    if (sym == kUp)
      bUp = true;
    if (sym == kDown)
      bDown = true;
    if (sym == kLeft)
      bLeft = true;
    if (sym == kRight)
      bRight = true;
    if (sym == kBomb)
      bBomb = true;
  }
}

void KeyInput::OnKeyUp(SDLKey sym) {
  if (NULL != Bomber) {
    if (sym == kUp)
      bUp = false;
    if (sym == kDown)
      bDown = false;
    if (sym == kLeft)
      bLeft = false;
    if (sym == kRight)
      bRight = false;	
    if (sym == kBomb)
      bBomb = false;
  }
}

JoyInput::JoyInput() {
  Which = 0;
  jUp.jEntity = JOY_AXIS;
  jUp.Number = 1;
  jUp.Value = -1;

  jDown.jEntity = JOY_AXIS;
  jDown.Number = 1;
  jDown.Value = 1;

  jRight.jEntity = JOY_AXIS;
  jRight.Number = 0;
  jRight.Value = +1;

  jLeft.jEntity = JOY_AXIS;
  jLeft.Number = 0;
  jLeft.Value = -1;

  jBomb.jEntity = JOY_BUTTON;
  jBomb.Number = 0;
  jBomb.Value = 0;
}

void JoyInput::OnJoyAxis (Uint8 which, Uint8 axis, Sint16 value) {
  if (which == Which) {
    if(JOY_AXIS == jUp.jEntity) {     
      if (axis == jUp.Number) {
	if (abs(value) < JOYSENSE) {
	  bUp = false;
	  bDown = false;
	}
	else {
	  if ((Sint16)value/abs(value) == (Sint16)jUp.Value)
	    bUp = true;
	}	
      }
    }
    if(JOY_AXIS == jDown.jEntity) {     
      if (axis == jDown.Number) {
	if (abs(value) < JOYSENSE) {
	  bUp = false;
	  bDown = false;
	}
	else {
	  if (value/abs(value) == jDown.Value)
	    bDown = true;
	}	
      }
    }
    if(JOY_AXIS == jLeft.jEntity) {     
      if (axis == jLeft.Number) {
	if (abs(value) < JOYSENSE) {
	  bRight = false;
	  bLeft = false;
	}
	else {
	  if (value/abs(value) == jLeft.Value)
	    bLeft = true;
	}	
      }
    }
    if(JOY_AXIS == jRight.jEntity) {     
      if (axis == jRight.Number) {
	if (abs(value) < JOYSENSE) {
	  bRight = false;
	  bLeft = false;
	}
	else {
	  if (value/abs(value) == jRight.Value)
	    bRight = true;
	}	
      }
    }
  }
   
}

void JoyInput::OnJoyHat(Uint8 which, Uint8 hat, Uint8 value) {
  if (which == Which) {
    
  }
}

void JoyInput::OnJoyButtonDown(Uint8 which, Uint8 button){
  if (which == Which){
    if (button == jBomb.Number)
      bBomb = true;
  }
}  

void JoyInput::OnJoyButtonUp(Uint8 which, Uint8 button){
  if (which == Which){
    if (button == jBomb.Number)
      bBomb = false;
  }
}  

