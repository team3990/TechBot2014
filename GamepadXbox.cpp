/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.			      */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "GamepadXbox.h"

/* --------------------------------------------------------------------------- */
// Constructors

/**
 * Construct an instance of a GamepadXbox.
 * The joystick index is the usb port on the drivers station.
 * 
 * @param port The port on the driver station that the joystick is plugged into.
 */
GamepadXbox::GamepadXbox(UINT32 port)
: Joystick(port)
{
}

GamepadXbox::~GamepadXbox()
{
}

/* --------------------------------------------------------------------------- */
// Methods

/**
 * Get the X value of the joystick in ENU - BODY format.
 */
float GamepadXbox::GetLeftX()
{
  return -Joystick::GetRawAxis(2);  // Pour retourner la valeur Y de la classe de base, mais de sens inverse
}

float GamepadXbox::GetLeftY()
{
  return Joystick::GetRawAxis(1);
}

float GamepadXbox::GetRightX()
{
  return -Joystick::GetRawAxis(5);
}

float GamepadXbox::GetRightY()
{
  return Joystick::GetRawAxis(4);
}

float GamepadXbox::Trigger()
{
  // Left Trigger goes from 0 to 1;
  // Right Trigger goes from -1 to 0;
  return Joystick::GetRawAxis(3);
}
