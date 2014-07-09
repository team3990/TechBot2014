/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "WPILib.h"
#include "Config.h"
#include "GamepadXbox.h"
#include "DrivingBase.h"
#include "IRS.h"
#include "Launcher.h"
#include "Picker.h"
#include "Catcher.h"
#include "VisualTracking.h"

class TechBot3 : public IterativeRobot
{
  
  // Declare a variable to use to access the driver station object
  DriverStation         * m_ds;                         // driver station object
  DriverStationLCD      * m_dslcd;
  SmartDashboard        * m_dashboard;
  
  // Declare variables for the two joysticks being used
  GamepadXbox           m_RightStick;                   // Joystick 1 (arcade stick or right tank stick)
  GamepadXbox           m_LeftStick;                    // Joystick 2 (tank left stick)
  
  //Dipswitch
  DigitalInput          m_Dipswitch1;
  DigitalInput          m_Dipswitch2;
  DigitalInput          m_Dipswitch3;
  DigitalInput          m_Dipswitch4;
  
  // Driving Base
  DrivingBase           m_BaseMobile;
  float                 m_DriveForward;
  float                 m_DriveRotation;
  bool                  m_ToggleShifterPrevious;
  
  // IRS
  IRS                   m_IRS;
  
  // Encoder
  double                encoderDistance;
  
  // Compressor
  Compressor            m_Compressor;
  
  // Sensors
//  Ultrasonic            * m_Ultrasonic;
//  ADXL345_SPI           * m_Accel;
  double                m_RobotAngle;
  //  Ultrasonic *m_Ultrasonic;
  
  // Launcher
  Launcher              m_Launcher;
  int                   m_StartCrincage;
  int                   m_StartShoot;
    
  // Catcher
  Catcher               m_Catcher;
  bool                  m_ToggleWingsPrevious;
  bool                  m_ToogleWings;
  
  // Picker
  Picker                m_Picker;
  int                   m_OldButtonCalibratePicker;
  bool                  m_OldPositionPick;
  int                   m_OldPositionRetract;
  
  // Vision  
//  VisualTracking        m_Vision;

  // Autonomous
  int                   m_AutonomousChoice;
  int                   m_AutonomousStep;
  int                   m_NextAutonomousFunction;
  int                   m_AutonomousIteration;
  double                m_GoalieDistance;
  double                m_FinalDistance;
  int                   m_WaitTimerHotGoalSwitch;
  int                   m_WaitTimer1sec;
  int                   m_TimerAutonome;
  
  bool                  m_LeftGoalDetected;
  bool                  m_IsLeftHotGoal;
  bool                  m_RightGoalDetected;
  bool                  m_IsRightHotGoal;
  bool                  m_LineCrossing;           // Indique detection de la ligne
  bool                  m_NewZoneDetection;       // Indique passage a la zone de couleur
  
  int                   m_HotGoalSwitchFirstPass;
  int                   m_FirstPass_0Ball_5;      //Recommencer le gyro pour la rotation
  int                   m_FirstPass_1Ball_2;
  int                   m_FirstPass_1Ball_8;      //Attente de 1 seconde après le Shoot
  int                   m_FirstPass_1Ball_9;      //Recommencer le gyro pour la rotation
  int                   m_FirstPass_1Ball_10;
  int                   m_FirstPass_2Ball_9;      //Attente de 1 seconde après le 1e Shoot
  int                   m_FirstPass_2Ball_13;     //Attente de 1 seconde après le 2e Shoot
  int                   m_FirstPass_2Ball_14;     //Recommencer le gyro pour la rotation

  
public:

  TechBot3();

  /********************************** Init Routines *************************************/

  virtual void          RobotInit();
  virtual void          DisabledInit();
  virtual void          AutonomousInit();
  virtual void          TeleopInit();
  
  virtual void          UpdateDashboardInputs();
  virtual void          DipSwitchChoice(int& o_Choice);
  virtual bool          AreGoalsDetected();
  virtual bool          HotGoalOnSameSide();
  
  /********************************** Periodic Routines *************************************/
  
  virtual void          DisabledPeriodic();
  virtual void          AutonomousPeriodic();
  virtual void          TeleopPeriodic();

  virtual void          RobotPeriodic();
 // virtual void          UpdateSmartDashboard();
  

  /********************************** Autonomous Modes *************************************/
  
  int                   DipSwitchChoice();
  
  double                AutonomousForwardAdjustment();
  void                  AutonomousGoReturn();
  void                  AutonomousGoShootReturnOneBall();
  void                  AutonomousGoShootReturnTwoBalls();
  void                  AutonomousShootInHotGoal();
  void                  AutonomousTakeThirdBall();
  
};

// START_ROBOT_CLASS(TechBot3);
