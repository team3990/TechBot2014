/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "PIDRotation.h"

/* --------------------------------------------------------------------------- */
// Constructors

PIDRotation::PIDRotation()
{
  m_value = 0;
}
PIDRotation::~PIDRotation()
{
}

/* --------------------------------------------------------------------------- */
// Methods 

// Erire la valeur dans le membre
void PIDRotation::PutValue(float value)
{
  m_value = value;
}

// Lit la valeur
double PIDRotation::PIDGet()
{
  return m_value;
}
