/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "DrivingBase.h"

/* --------------------------------------------------------------------------- */
// Constructors 
DrivingBase::DrivingBase()
: m_Shifter(C_cRIOPneumaticModuleNumber, C_SolenoidShifter), 
  m_motorLeft(C_MotorLeftFront),
  m_motorRight(C_MotorRightFront)
{
  // Log to console
  printf("DrivingBase Constructor Started\n");

  // Properties
  m_Seuil_Rotation    = 0.0; // (0.1?)
  m_Seuil_Forward     = 0.0; // (0.3?)
  m_CompensationFriction_Forward  = 0; // (15?)
  m_CompensationFriction_Rotation = 0; // (20?)
  
  // Create a robot using standard left/right robot drive
  m_moteurs = new RobotDrive(&m_motorLeft, &m_motorRight);
  m_motorLeft.EnableDeadbandElimination(true);
  m_motorRight.EnableDeadbandElimination(true);
}
DrivingBase::~DrivingBase()
{
  
}

/* --------------------------------------------------------------------------- */
// Methods

//
// SamrtDashboard functions
//
void DrivingBase::DashboardInit()
{
  // Send default values to populate dashboard
  SmartDashboard::PutNumber("Forward compensation",       m_CompensationFriction_Forward);
  SmartDashboard::PutNumber("Rotation compensation",      m_CompensationFriction_Rotation);
  SmartDashboard::PutNumber("Max Forward compensation",   m_Seuil_Forward);
  SmartDashboard::PutNumber("Min Rotation compensation",  m_Seuil_Rotation);
}

void DrivingBase::UpdateDashboardInputs()
{
  //Send dashboard values
  m_CompensationFriction_Forward  = SmartDashboard::GetNumber("Forward compensation");
  m_CompensationFriction_Rotation = SmartDashboard::GetNumber("Rotation compensation");
  m_Seuil_Forward                 = SmartDashboard::GetNumber("Max Forward compensation");
  m_Seuil_Rotation                = SmartDashboard::GetNumber("Min Rotation compensation");
}

void DrivingBase::Drive(float iForward, float iRotation)
{
  // Pour compenser la friction quand on tourne à une petite vitesse
/*  if (iForward < m_Seuil_Forward && iForward > -m_Seuil_Forward              &&
      (iRotation > m_Seuil_Rotation || iRotation < -m_Seuil_Rotation) )
  {
    m_motorLeft.SetBounds (206, 128+m_CompensationFriction_Rotation, 128, 128-m_CompensationFriction_Rotation, 56);
    m_motorRight.SetBounds(206, 128+m_CompensationFriction_Rotation, 128, 128-m_CompensationFriction_Rotation, 56);
  }
  else
  {
    m_motorLeft.SetBounds (206, 128+m_CompensationFriction_Forward,  128, 128-m_CompensationFriction_Forward,  56);
    m_motorRight.SetBounds(206, 128+m_CompensationFriction_Forward,  128, 128-m_CompensationFriction_Forward,  56);
  }
»*/  
  m_moteurs->ArcadeDrive(-iForward, iRotation);
}

void DrivingBase::HighSpeed()
{
  m_Shifter.Set(true);
}

void DrivingBase::LowSpeed()
{
  m_Shifter.Set(false);
}

void DrivingBase::ToggleSpeed()
{
  if(m_Shifter.Get() == true)
  {
    m_Shifter.Set(false);
  }
  else
  {
    m_Shifter.Set(true);
  }
}
