/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.		              */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef JOYSTICK_ATTACK3_H_
#define JOYSTICK_ATTACK3_H_

#include "Joystick.h"


/**
 * Handle input from standard Joysticks Attack3 connected to the Driver Station.
 */
class JoystickAttack3 : public Joystick
{
  
public:
	
  // Constructors
  explicit              JoystickAttack3(UINT32 port);
  virtual               ~JoystickAttack3();

  //
  // Methods
  //

  // Get the X value of the joystick in ENU - BODY format
  virtual float         GetX();    // Pour l'instant on oublie le parametre hand puisqu'il ne sert a rien dans le code de Joystick
  virtual float         GetY();
  virtual float         GetT();
  
  // Properties
  float                 m_Seuil_X;
  float                 m_Seuil_XX;
  float                 m_Seuil_Y;
  float                 m_Seuil_YY;

private:
  DISALLOW_COPY_AND_ASSIGN(JoystickAttack3);
	
};

#endif // JOYSTICK_ATTACK3_H_
