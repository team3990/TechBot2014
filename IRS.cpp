/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "IRS.h"

/* --------------------------------------------------------------------------- */
// Constructors 

IRS::IRS() :    m_BaseLeft(C_EncoderDrivingBaseLeft_A, C_EncoderDrivingBaseLeft_B, false, CounterBase::k4X),
                m_BaseRight(C_EncoderDrivingBaseRight_A, C_EncoderDrivingBaseRight_B, true, CounterBase::k4X), m_EncodeurLeftCount(0),
                m_EncodeurRightCount(0), m_EncodeurCount(0), 
                m_Accel(NULL), 
               // m_Gyro(NULL), 
                m_Ultrasonic(NULL)
{
  printf("IRS Constructor Started\n");

  m_BaseLeft.SetDistancePerPulse(0.0490625); // 0.0061347 //0.0502655
  m_BaseRight.SetDistancePerPulse(0.0490625);
  m_BaseLeft.Start();
  m_BaseRight.Start();
  
  /*
  m_Accel       = new ADXL345_SPI(C_AccelModule, C_AccelCK, C_AccelDI, C_AccelDO, C_AccelCS);
  m_Ultrasonic  = new Ultrasonic(C_UltraSonicPing, C_UltraSonicEcho, Ultrasonic::kInches);
  
  m_Ultrasonic->SetEnabled(true);
  m_Ultrasonic->SetAutomaticMode(true);
  */
  //m_Gyro   = new Gyro(C_GyroChannel);
 
  printf("IRS Constructor Completed\n");
}

IRS::~IRS()
{
  
}

/* --------------------------------------------------------------------------- */
// Methods

void IRS::Init()
{
  ResetEncoders();
}

void IRS::ProcessSensors()
{
  m_EncodeurLeftCount = m_BaseLeft.Get();
  m_EncodeurRightCount = m_BaseRight.Get();
  m_EncodeurCount = (m_EncodeurLeftCount + m_EncodeurRightCount) / 2;
} 

int IRS::getBaseLeft()
{
  return m_EncodeurLeftCount;
}

int IRS::getBaseRight()
{
  return m_EncodeurRightCount;
}

double IRS::GetLeftDistance()
{
  return m_BaseLeft.GetDistance();
}

double IRS::GetRightDistance()
{
  return m_BaseRight.GetDistance();
}

double IRS::GetDistance()
{
  return (m_BaseLeft.GetDistance() + m_BaseRight.GetDistance()) / 2;
}

void IRS::ResetEncoders()
{
  m_BaseLeft.Reset();
  m_BaseRight.Reset();
}

void IRS::ResetVirtualEncodersDistance()
{
  m_LeftEncoderDifference = m_BaseLeft.GetDistance();
  m_RightEncoderDifference = m_BaseRight.GetDistance();
}

double IRS::GetLeftVirtualEncoder()
{
  return m_BaseLeft.GetDistance() - m_LeftEncoderDifference;
}

double IRS::GetRightVirtualEncoder()
{
  return m_BaseRight.GetDistance() - m_RightEncoderDifference;
}

double IRS::GetVirtualDistance()
{
  return ( m_BaseLeft.GetDistance() - m_LeftEncoderDifference + m_BaseRight.GetDistance() - m_RightEncoderDifference ) / 2;
}
/*       
void IRS::ResetVirtualGyroDifference()
{
  GyroDifference = m_Gyro->GetAngle();
}

float IRS::GetVirtualGyroAngle()
{
  float VirtualAngle = m_Gyro->GetAngle() - GyroDifference;
  
  // Si le robot tourne ￠ gauche, l'angle virtuel ( VirtualAngle ) sera n￩gatif.
  // cette condition permet de donner ￠ l'angle virtuelle une valeur toujours positive
  if ( VirtualAngle < 0 )
  {
    VirtualAngle = VirtualAngle + 360;
  }
  
  return VirtualAngle;
}
*/
//void IRS::UpdateSmartDashboard()
//{
  //Accelerometer Output
  /*
  SmartDashboard::PutNumber("Accel X", m_Accel->GetAcceleration(ADXL345_SPI::kAxis_X));
  SmartDashboard::PutNumber("Accel Y", m_Accel->GetAcceleration(ADXL345_SPI::kAxis_Y));
  SmartDashboard::PutNumber("Accel Z", m_Accel->GetAcceleration(ADXL345_SPI::kAxis_Z));
  */
  
  // Gyro Output
  /*
  SmartDashboard::PutNumber("Gyro Angle", m_Gyro->GetAngle());
  SmartDashboard::PutNumber("Gyro Rate", m_Gyro->GetRate());
  */
  
  // Ultrasonic
  /*
  SmartDashboard::PutNumber("US Distance", m_Ultrasonic->GetRangeInches());
  */
//}
