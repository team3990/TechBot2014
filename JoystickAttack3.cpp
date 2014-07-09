/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.			      */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "JoystickAttack3.h"

/**
 * Construct an instance of a tfkJoystickAttack3.
 * The joystick index is the usb port on the drivers station.
 * 
 * @param port The port on the driver station that the joystick is plugged into.
 */

/* --------------------------------------------------------------------------- */
// Constructors 

JoystickAttack3::JoystickAttack3(UINT32 port)
: Joystick(port),
  m_Seuil_X(0.1),
  m_Seuil_XX(-0.1),
  m_Seuil_Y(0.1),
  m_Seuil_YY(-0.1)
{
}

JoystickAttack3::~JoystickAttack3()
{
}

/* --------------------------------------------------------------------------- */
// Methods
/* --------------------------------------------------------------------------- */


/**
 * Get the X value of the joystick in ENU - BODY format.
 */
float JoystickAttack3::GetX()
{
  float v = -Joystick::GetY(); // Pour retourner la valeur Y de la classe de base, mais de sens inverse

  if (v < m_Seuil_X && v > m_Seuil_XX)
  {
    v = 0;
  }
  return v;
}

float JoystickAttack3::GetY()
{
  float v1 = Joystick::GetX();

  if ( v1 < m_Seuil_X && v1 > m_Seuil_XX)
  {
    v1 = 0;
  }
  return v1;
}

float JoystickAttack3::GetT()
{
  return 0.5 * Joystick::GetZ() + 0.5;
}
