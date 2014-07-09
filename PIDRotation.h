/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef PIDROTATION_H
#define PIDROTATION_H

#include "WPILib.h"
#include "Config.h"

/*
 * Class qui lit un encodeur analogique et qui prend la conversion en deg
 * Permet de le passer au PID pour du positionnement
 */

class PIDRotation: public PIDSource
{
  
public:
  
  // Constructeurs
  PIDRotation();
  virtual       ~PIDRotation();
  
  // Methods
  double        PIDGet();
  void          PutValue(float value);
  
  // Properties
  double        m_value;
  
};

#endif
