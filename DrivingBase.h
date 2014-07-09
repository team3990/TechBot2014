/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "WPILib.h"
#include "Config.h"

class DrivingBase
{

public:
  
  // Constructor
  DrivingBase();
  ~DrivingBase();
  
  // Solenoids
  Solenoid      m_Shifter; 
  
  // Methods
  void          DashboardInit();
  void          UpdateDashboardInputs();
  void          Drive(float iForward, float iRotation);
  void          HighSpeed();
  void          LowSpeed();
  void          ToggleSpeed();
  
  // Instances
  Victor        m_motorLeft;
  Victor        m_motorRight;
  RobotDrive *  m_moteurs;
  
  // Properties
  float         m_Seuil_Rotation;
  float         m_Seuil_Forward;
  float         m_CompensationFriction_Forward;
  float         m_CompensationFriction_Rotation;
  
};
