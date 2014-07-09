/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "WPILib.h"
#include "Config.h"

class IRS
{
    
public:

  // Constructors
  IRS();
  ~IRS();
  
  // Encoders: Methods
  void          Init();
  void          ProcessSensors();
 // void          UpdateSmartDashboard();

  int           getBaseLeft();
  int           getBaseRight();
  void          ResetEncoders();
  void          ResetVirtualEncodersDistance();
  double        GetLeftDistance();
  double        GetRightDistance();
  double        GetDistance();
  double        GetLeftVirtualEncoder();
  double        GetRightVirtualEncoder();
  double        GetVirtualDistance();
 
  // Encoders Properties
  Encoder       m_BaseLeft;
  Encoder       m_BaseRight;
  int           m_EncodeurLeftCount;
  int           m_EncodeurRightCount;
  int           m_EncodeurCount;
  double        m_LeftEncoderDifference;
  double        m_RightEncoderDifference;
  
  // Accelerometer
  ADXL345_SPI   * m_Accel;
  
  // Gyroscope: Methods
  //void          ResetVirtualGyroDifference();
  //float         GetVirtualGyroAngle();
  
  // Gyroscope: Properties
 // Gyro          * m_Gyro;
  float         GyroDifference;
  
  // Ultrasonic: Properties
  Ultrasonic    * m_Ultrasonic;
  
};
