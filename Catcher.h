/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef CATCHER_H
#define CATCHER_H

#include "WPILib.h"
#include "Config.h"


class Catcher
{

public:
  
  // Constructors
  Catcher();
  ~Catcher();
  
  // Methods
  void          GestionWings();
  bool          GetWingsState();
  void          OpenWings();
  void          CloseWings();
  void          ToggleWings();
    
  // Solenoids
  Solenoid      m_SolenoidCatcher;
  
  // Properties
  bool          m_StateWings;
  bool          m_ModeShoot;
  
};

#endif // CATCHER_H
