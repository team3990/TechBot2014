/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef GAMEPAD_XBOX_H_
#define GAMEPAD_XBOX_H_

#include "WPILib.h"

/**
 * Handle input from standard Joysticks Attack3 connected to the Driver Station.
 */
class GamepadXbox : public Joystick
{
  
public:
	
  // Constructors
  explicit              GamepadXbox(UINT32 port);
  virtual               ~GamepadXbox();

  // Methods

  // Get the X value of the joystick in ENU - BODY format
  virtual float         GetLeftX();
  virtual float         GetLeftY();
  
  virtual float         GetRightX();
  virtual float         GetRightY();
  
  virtual float         Trigger();

private:
  DISALLOW_COPY_AND_ASSIGN(GamepadXbox);
	
};

#endif // GAMEPAD_XBOX_H_
