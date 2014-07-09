/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "Catcher.h"

/* --------------------------------------------------------------------------- */
// Constructors 
Catcher::Catcher() : m_SolenoidCatcher(C_cRIOPneumaticModuleNumber, C_SolenoidWings)
{
  m_SolenoidCatcher.Set(false);
  m_StateWings = false;
}

Catcher::~Catcher()
{
  
}

/* --------------------------------------------------------------------------- */
// Methods

void Catcher::GestionWings()
{
   m_SolenoidCatcher.Set(m_StateWings);
}


bool Catcher::GetWingsState()
{
    return m_SolenoidCatcher.Get();
}

void Catcher::OpenWings()
{
  m_StateWings = true;
  
}

void Catcher::CloseWings()
{
  m_StateWings = false;
}

void Catcher::ToggleWings()
{
  m_StateWings ^= 1;
}
