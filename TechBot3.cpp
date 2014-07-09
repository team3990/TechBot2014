/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

//#include "WPILib.h"

#include "TechBot3.h"

// Numéro de version unique
char Version[100] = "FBot v2.03 (Mar. 20)";

TechBot3::TechBot3()
: m_RightStick(1),
  m_LeftStick(2),
  m_Dipswitch1(c_DeepSwtich1),
  m_Dipswitch2(c_DeepSwtich2),
  m_Dipswitch3(c_DeepSwtich3),
  m_Dipswitch4(c_DeepSwtich4),
  m_DriveForward(0),
  m_DriveRotation(0),
  m_ToggleShifterPrevious(false),
  m_Compressor(C_CompressorIO, C_CompressorRelay),
//  m_Ultrasonic(NULL),
  m_Launcher(),
  m_Catcher(),
  m_ToggleWingsPrevious(false),
  m_Picker(),
//  m_Vision(),

  m_AutonomousChoice(0),
  m_AutonomousStep(0),
  m_NextAutonomousFunction(0),
  m_AutonomousIteration(0),
  m_GoalieDistance(0),
  m_FinalDistance(0),
  m_WaitTimerHotGoalSwitch(0),
  m_WaitTimer1sec(0),
  m_LeftGoalDetected(false),
  m_IsLeftHotGoal(false),
  m_RightGoalDetected(false),
  m_IsRightHotGoal(false),
  m_LineCrossing(false),
  m_NewZoneDetection(0),
  m_HotGoalSwitchFirstPass(0),
  m_FirstPass_0Ball_5(0),
  m_FirstPass_1Ball_2(0),
  m_FirstPass_1Ball_8(0),
  m_FirstPass_1Ball_9(0),
  m_FirstPass_1Ball_10(0),
  m_FirstPass_2Ball_9(0),
  m_FirstPass_2Ball_13(0),
  m_FirstPass_2Ball_14(0)
{
  printf("TechBot3 Constructor Started\n");
  
  // Acquire the Driver Station object
  m_ds          = DriverStation::GetInstance();
  m_dslcd       = DriverStationLCD::GetInstance();
  
  // Autonomous Mode
  m_TimerAutonome = 0;
  
  // Debug Logging
  printf("TechBot3 Constructor Completed\n");
}
  /**************************************************************************************/
  /********************************** Init Routines *************************************/
  /**************************************************************************************/

void TechBot3::RobotInit()
{
  // Debug Logging
  printf("RobotInit() started.\n");
  
  // Start
  m_IRS.Init();
  m_Compressor.Start();
  m_BaseMobile.DashboardInit();
  UpdateDashboardInputs();
  
  // Debug Logging
  printf("RobotInit() completed.\n");
}

void TechBot3::DisabledInit()
{
}

void TechBot3::AutonomousInit()
{
  // Debug Logging
  printf("AutonomousInit() started.\n");
  
  UpdateDashboardInputs();

  // DriverStation LCD Display
  m_dslcd->PrintfLine(DriverStationLCD::kUser_Line5, "AU");
  m_dslcd->PrintfLine(DriverStationLCD::kUser_Line6, Version);
  m_dslcd->UpdateLCD();

  // Hot Goal Timer (On shoot apres 6 secondes)
  m_WaitTimerHotGoalSwitch = (5+1) * c_IterationPerSecond;
  m_WaitTimer1sec          = 0;
  
  // Choix du mode autonomous
  // Récupérer la valeur de la décision prise à l'aide de la fonction DipSwitch
  DipSwitchChoice(m_AutonomousChoice);
  SmartDashboard::PutNumber("Auto Choice", m_AutonomousChoice);
  
  // (Pour le moment, on force cette variable à utiliser le script #0)
  //m_AutonomousChoice = 0;

  // Prochaine fonction à exécuter dans les modes autonomous
  m_NextAutonomousFunction      = 1;
  m_AutonomousStep              = 1;
  m_TimerAutonome               = 0;
  m_LineCrossing                = false;
  m_NewZoneDetection            = false;
  m_LeftGoalDetected            = false;
  m_IsLeftHotGoal               = false;
  m_RightGoalDetected           = false;
  m_IsRightHotGoal              = false;
  
  m_FinalDistance = 0; //Pour l'instant, la Final Distance a une valeur nulle.
                       //Sa valeur sera déterminée par la distance entre la position initiale
                       //et la ligne entre les deux zones. Cela va permettre au robot à retourner
                       //exactement à la position initiale. La distance sera en pouces.
  
  // First Passes
  m_HotGoalSwitchFirstPass = 1;
  m_FirstPass_0Ball_5  = 1;     //Recommencer le gyro pour la rotation
  m_FirstPass_1Ball_2  = 1;
  m_FirstPass_1Ball_9  = 1;     //Attente de 1 seconde après le Shoot
  m_FirstPass_1Ball_10 = 1;     //Recommencer le gyro pour la rotation
  m_FirstPass_2Ball_9  = 1;     //Attente de 1 seconde après le 1e Shoot
  m_FirstPass_2Ball_13 = 1;     //Attente de 1 seconde après le 2e Shoot
  m_FirstPass_2Ball_14 = 1;
  
  // Mise en place de la camera
//  m_Vision.ActivateTracking(true);
//  m_Vision.SelectTarget(VisualTracking::c_VisTarget_HotGoal);
  
  m_Picker.SetEncoderCalibration();

  
  // Debug Logging
  printf("AutonomousInit() Completed.\n");
}

void TechBot3::TeleopInit()
{
  // Debug Logging
  printf("TeleopInit() started.\n");
  
  UpdateDashboardInputs();

  // DriverStation LCD Display
  m_dslcd->PrintfLine(DriverStationLCD::kUser_Line6, "TELEOP");
  m_dslcd->PrintfLine(DriverStationLCD::kUser_Line6, Version);
  m_dslcd->UpdateLCD();
  
  // DEBUG: Pour tester live la vision dans la détection du HotGoal
//  m_Vision.SelectTarget(VisualTracking::c_VisTarget_HotGoal);
//  m_Vision.ActivateTracking(true);
  
  // Debug Logging
  printf("TeleopInit() completed.\n");
}

/**************************************************************************************/
/******************************** Periodic Routines ***********************************/
/**************************************************************************************/

void TechBot3::DisabledPeriodic()
{
}

void TechBot3::AutonomousPeriodic()
{
  //printf("AU Periodic Start \n");  Enleve le print pour laisser toute la place a ceux de la vision

  // Donne le temps total dans le mode autonome
  ++m_TimerAutonome;
  
  /* --------------------------------------------------------------------------- */
  // Handlers
  m_Picker.GestionPicker();
  m_Launcher.GestionLauncher();
  m_Catcher.GestionWings();

  /* --------------------------------------------------------------------------- */
  // Controle automatique des wings
  if (m_Launcher.m_DelaiShoot > 0)
  {
    m_Catcher.OpenWings();
  }
  else
  {
    m_Catcher.CloseWings();
  }
  
  /*----------------------------------------------------------*/
  // Calculs de l'IRS
   
  m_IRS.ProcessSensors();
  
  // Calcule le moment de changement de HotGoal
  if (m_WaitTimerHotGoalSwitch > 0)
  {
      m_WaitTimerHotGoalSwitch--;
  }
  else if (m_HotGoalSwitchFirstPass == 1)
  {
    //
    // Inverse le type "HotGoal" des cibles détectées
    //
    if (m_LeftGoalDetected == true)
    {
      m_IsLeftHotGoal  = 1-m_IsLeftHotGoal;
    }
    if (m_RightGoalDetected == true)
    {
      m_IsRightHotGoal = 1-m_IsRightHotGoal;
    }

    m_HotGoalSwitchFirstPass = 0;
  }
  
  // m_AutonomousIteration++;
  
  // Execute selected autonomous script according to the Dip Switches
  switch (m_AutonomousChoice)
  {
    case cAutonomous0Ballon :
      AutonomousGoReturn();
      break;
    case cAutonomous1Ballon :
      AutonomousGoShootReturnOneBall();
      break;
    case cAutonomous2Ballon :
      AutonomousGoShootReturnTwoBalls();
      break;
      
    /*
    case cAutonomous3Ballon :
      if (m_NextAutonomousFunction == 1)
      {
        AutonomousGoShootReturnTwoBalls();
      }
      else if (m_NextAutonomousFunction == 2)
      { 
        AutonomousTakeThirdBall();
      }
      else if (m_NextAutonomousFunction == 3)
      {
        AutonomousGoShootReturnOneBall();
      }
      break;
    */
    default:
      AutonomousGoReturn();
      break;
  }

  /*----------------------------------------------------------*/
  // SmartDashboard

  // SmartDashboard::PutNumber     ("V Forward", m_DriveForward);
  // SmartDashboard::PutNumber     ("V Rotation", m_DriveRotation);
  SmartDashboard::PutNumber     ("Distance Gauche", m_IRS.GetLeftDistance());
  SmartDashboard::PutNumber     ("Distance Droite", m_IRS.GetRightDistance());
  // SmartDashboard::PutNumber     ("Angle", m_IRS.m_Gyro->GetAngle());
  SmartDashboard::PutBoolean    ("Selecteur de pression", m_Launcher.m_PressureSelector);
  SmartDashboard::PutBoolean    ("Elastique", m_Launcher.m_CatapultElastic);
  SmartDashboard::PutBoolean    ("Prepare Catapulte", m_Launcher.m_PrepareCatapulte);
  SmartDashboard::PutBoolean    ("Catapulte est prete", m_Launcher.m_CatapulteReady);
  SmartDashboard::PutBoolean    ("Pression est prete", m_Launcher.m_PressureReady);
  
  /*----------------------------------------------------------*/
  // Execute robot
  RobotPeriodic();  
}

void TechBot3::TeleopPeriodic()
{
  //// DEBUG: Pour tester live la vision dans la détection du HotGoal
  //m_Vision.FindTarget(m_LeftGoalDetected, m_IsLeftHotGoal, m_RightGoalDetected, m_IsRightHotGoal);
  //printf("Left Detected=%d, Left Hot=%d | Right Detected=%d, Right Hot=%d\n",
  //       m_LeftGoalDetected, m_IsLeftHotGoal, m_RightGoalDetected, m_IsRightHotGoal);
  
  UpdateDashboardInputs();

  /* --------------------------------------------------------------------------- */
  // Handlers
  //("Handlers \n");   Enleve le print pour laisser toute la place a ceux de la vision
  m_Picker.GestionPicker();
  m_Launcher.GestionLauncher();
  m_Catcher.GestionWings();

  /*----------------------------------------------------------*/
  // Calculs de l'IRS
  m_IRS.ProcessSensors();
  //printf("IRS \n");    Enleve le print pour laisser toute la place a ceux de la vision

  /* --------------------------------------------------------------------------- */
  // Mapping Joysticks
  
  // Left Joystick - Driving + Calibration
  int ButtonShifter             =  m_LeftStick.GetRawButton(9)
                                || m_LeftStick.GetRawButton(10)
                                || (m_LeftStick.Trigger() >= 0.7)
                                || (m_LeftStick.Trigger() <= -0.7);
  
  // Right Joystick - Mechanisms
  int ButtonPrepareHighGoal     = m_RightStick.GetRawButton(4);
  int ButtonPrepareTruss        = m_RightStick.GetRawButton(3);
  int ButtonPrepareLowGoal      = m_RightStick.GetRawButton(1);
  int ButtonShoot               = m_RightStick.GetRawButton(5) || m_RightStick.GetRawButton(6);
  int ButtonRollerIn            = (m_RightStick.GetRightX() >= 0.5);
  int ButtonRollerOut           = (m_RightStick.GetRightX() <= -0.5);
  int ButtonPickerDown          = (m_RightStick.GetLeftX() >=  0.5);
  int ButtonPickerUp            = (m_RightStick.GetLeftX() <= -0.5);
  int ButtonPositionPick        = (m_RightStick.GetRawButton(2));
  int ButtonPositionRetract     = (m_RightStick.GetLeftX() <= -0.5);
  int ButtonWingsOpen           = (m_RightStick.Trigger() >= 0.7) || (m_RightStick.Trigger() <= -0.7);
  int ButtonPosition            = false; // m_RightStick.GetRawButton(7);
  int ButtonCalibratePicker     = m_RightStick.GetRawButton(8);
  bool ButtonReverseWinch        = m_RightStick.GetRawButton(7);
  
  /* --------------------------------------------------------------------------- */
  // Driving controls
  //printf("Joystick \n");    Enleve le print pour laisser toute la place a ceux de la vision
  // Driving Axis
  m_DriveForward      = m_LeftStick.GetLeftX();
  m_DriveRotation     = m_LeftStick.GetLeftY();

  /* --------------------------------------------------------------------------- */
  // Picker
  
  // If ButtonCalibratePicker is pressed, we calibrate the picker.
  // Picker must be at 90 degrees before executing this action.
  if(ButtonCalibratePicker == true && m_OldButtonCalibratePicker == 0)
  {
    m_Picker.SetEncoderCalibration();
  }
  m_OldButtonCalibratePicker = ButtonCalibratePicker;
  
  // Place picker in picking mode
  if(ButtonPositionPick == true && m_OldPositionPick == false)
  {
    m_Picker.SetAngle(137.0);
//    m_Launcher.PrepareCatapule();
    //printf("PrepareCatapulte");    Enleve le print pour laisser toute la place a ceux de la vision
  }
  m_OldPositionPick = ButtonPositionPick;

  if( ButtonPositionRetract == 1 && m_OldPositionRetract == 0) // One shot transition montante
  {
    m_Picker.SetAngle(70.0);
  }
  m_OldPositionRetract = ButtonPositionRetract;
  
  if (ButtonPickerDown == 1)
  {
    m_Picker.m_Mode = m_Picker.kJugForward;
  }
  else if (ButtonPickerUp == 1)
  {
    m_Picker.m_Mode = m_Picker.kJugReverse;
  }
  else if (ButtonPosition == 1)
  {
    m_Picker.m_Mode = m_Picker.kJogAngle;
  }
  else
  {
    m_Picker.m_Mode = m_Picker.kDisable;
  }
  //printf("Picker \n");    Enleve le print pour laisser toute la place a ceux de la vision

  /* --------------------------------------------------------------------------- */
  // Roller
  
  if (ButtonRollerIn)
  {
    if (m_Launcher.m_CatapulteReady == true)
    {
      m_Picker.ActivateRoller(-1.0);
      
      // Debug Logging
      //printf("Roller In activated.\n");    Enleve le print pour laisser toute la place a ceux de la vision
    }
  } 
  else if (ButtonRollerOut)
  {
    if (m_Launcher.m_CatapulteReady == true)
    {
      m_Picker.ActivateRoller(1.0);

      // Debug Logging
      //printf("Roller Out activated.\n");    Enleve le print pour laisser toute la place a ceux de la vision
    }
  }  
  else
  {
    m_Picker.ActivateRoller(0.0);
  }
  //printf("Roller \n");    Enleve le print pour laisser toute la place a ceux de la vision

  /* --------------------------------------------------------------------------- */
  // Shifter
  if (ButtonShifter == true ) //&& m_ToggleShifterPrevious == false)
  {
    m_BaseMobile.HighSpeed();
    
    // Debug Logging
    //printf("Shifter to low speed.\n");    Enleve le print pour laisser toute la place a ceux de la vision
  }
  else
    {
      m_BaseMobile.LowSpeed();
    }
//  m_ToggleShifterPrevious = ButtonShifter;
  
  /* --------------------------------------------------------------------------- */
  // Controle catapulte en automatique
  if(m_Launcher.m_CatapulteReady==false && m_Launcher.m_PrepareCatapulte == false && 
     m_Launcher.m_DelaiShoot == 0)
    {
      m_Launcher.PrepareCatapule();
    }
  
  
  
  /* --------------------------------------------------------------------------- */
  // Ailes
  //printf("Shifter \n");    Enleve le print pour laisser toute la place a ceux de la vision
  if (ButtonWingsOpen == true || m_Launcher.m_DelaiShoot > 0)
  {
    m_Catcher.OpenWings();
    
    // Debug Logging
    //printf("Wings opened.\n");    Enleve le print pour laisser toute la place a ceux de la vision
  }
  else
  {
    m_Catcher.CloseWings();
  }
  //printf("Wings \n");    Enleve le print pour laisser toute la place a ceux de la vision

  /* --------------------------------------------------------------------------- */
  // Shooting Sequences
  
  // Select the pressure before shooting. It does not shoot the ball, it only prepare
  // the elastic and the pressure selector.
  if(ButtonPrepareHighGoal)
  {
    m_Launcher.PrepareHighGoal();
    
    // Debug Logging
    //printf("Shot in High Goal.\n");    Enleve le print pour laisser toute la place a ceux de la vision
  }
  
  if(ButtonPrepareLowGoal)
  {
    m_Launcher.PrepareLowGoal();

    // Debug Logging
    //printf("Shot in Low Goal.\n");    Enleve le print pour laisser toute la place a ceux de la vision
  }
  if(ButtonPrepareTruss)
  {
    m_Launcher.PrepareTruss();
    
    // Debug Logging
    //printf("Shot over the truss.\n");    Enleve le print pour laisser toute la place a ceux de la vision
  }
  
  // If catapult is ready to shoot, shoot the ball if the shoot button is pressed
  if(m_Launcher.IsCatapulteReady()==true && m_Launcher.IsPressureReady()==true)
//    && (m_Picker.GetDegreLeft() > 120 || m_Picker.GetDegreRigth() > 120))
  {
    if(ButtonShoot == true)
    {
      // If we have the conditions, we shoot
      m_Launcher.LauncherShoot();
    }
  }
  
  // Bouton manuel reverse winch
  if(ButtonReverseWinch == true)
  {
     m_Launcher.ReverseWinchManuel(true); 
  }
  else
  {
     m_Launcher.ReverseWinchManuel(false); 
  }
  
  /* --------------------------------------------------------------------------- */
  // SmartDashboard
  SmartDashboard::PutBoolean    ("Compressor", m_Compressor.Enabled());
  SmartDashboard::PutNumber     ("VOL", m_Picker.m_AnalogEncoderLeft.GetVoltage());
  SmartDashboard::PutNumber     ("VOR", m_Picker.m_AnalogEncoderRight.GetVoltage());
  SmartDashboard::PutNumber     ("VaL", m_Picker.m_AnalogEncoderLeft.GetValue());
  SmartDashboard::PutNumber     ("VaR", m_Picker.m_AnalogEncoderRight.GetValue());
  SmartDashboard::PutNumber     ("CaL", m_Picker.m_OffsetLeft);
  SmartDashboard::PutNumber     ("CaR", m_Picker.m_OffsetRight);
  SmartDashboard::PutNumber     ("AngleL", m_Picker.GetDegreLeft());
  SmartDashboard::PutNumber     ("AngleR", m_Picker.GetDegreRight());
  SmartDashboard::PutBoolean    ("Preparing Catapult",m_Launcher.m_PrepareCatapulte);
  SmartDashboard::PutBoolean    ("Catapulte Ready",m_Launcher.m_CatapulteReady);
  SmartDashboard::PutBoolean    ("Pression Ready",m_Launcher.m_PressureReady);
  SmartDashboard::PutNumber     ("Axis X", m_DriveForward);
  SmartDashboard::PutNumber     ("Axis Y", m_DriveRotation);
  SmartDashboard::PutNumber     ("distanceG", m_IRS.GetLeftDistance());
  SmartDashboard::PutNumber     ("distanced", m_IRS.GetRightDistance());
  SmartDashboard::PutNumber     ("EncoderG", m_IRS.m_BaseLeft.GetRaw());
  SmartDashboard::PutNumber     ("Encoderd", m_IRS.m_BaseRight.GetRaw());
  //SmartDashboard::PutNumber     ("Angle",   m_IRS.m_Gyro->GetAngle());
  SmartDashboard::PutBoolean    ("Pression Selector (True = 60 psi, False = 40 psi)", m_Launcher.m_PressureSelector);
  SmartDashboard::PutBoolean    ("Catapult Elastic (True = stretched, False = not stretched)", m_Launcher.m_CatapultElastic);
  // UpdateSmartDashboard();
  
  /*----------------------------------------------------------*/
  // Mise en marche des actions moteurs
  RobotPeriodic();
    
  /* --------------------------------------------------------------------------- */
  // DriverStation LCD display
  char buf[100];
  m_dslcd->PrintfLine(DriverStationLCD::kUser_Line6, Version);
  sprintf(buf, "X:%f, Y:%f", m_DriveForward, m_DriveRotation);
  m_dslcd->PrintfLine(DriverStationLCD::kUser_Line1, buf);
  m_dslcd->UpdateLCD();
}

void TechBot3::RobotPeriodic()
{
  // Commandes moteurs de la base mobile 
  m_BaseMobile.Drive(m_DriveForward, m_DriveRotation);
  //printf("Drive \n");    Enleve le print pour laisser toute la place a ceux de la vision
}

void TechBot3::UpdateDashboardInputs()
{
  m_BaseMobile.UpdateDashboardInputs();
}

/* 
void TechBot3::UpdateSmartDashboard()
{
  // Mise-à-jour les membres du robot
  SmartDashboard::PutBoolean    ("Compressor",  m_Compressor.Enabled());
  SmartDashboard::PutBoolean    ("SwitchWinch", false);
  SmartDashboard::PutNumber     ("VOL",         m_Picker.m_AnalogEncoderLeft.GetVoltage());
  SmartDashboard::PutNumber     ("VOR",         m_Picker.m_AnalogEncoderRight.GetVoltage());
  SmartDashboard::PutNumber     ("VaL",         m_Picker.m_AnalogEncoderLeft.GetValue());
  SmartDashboard::PutNumber     ("VaR",         m_Picker.m_AnalogEncoderRight.GetValue());
  
  // Et ceux de ses sous-systèmes
  m_IRS.UpdateSmartDashboard();
}
*/

bool TechBot3::AreGoalsDetected()
{
  return m_LeftGoalDetected  == false &&
         m_RightGoalDetected == false;
}

bool TechBot3::HotGoalOnSameSide()
{
  // Si une seule target est détectée, on prend celle-la
  return ( (m_LeftGoalDetected == false && m_RightGoalDetected == true  && m_IsRightHotGoal == true) ||
           (m_LeftGoalDetected == true  && m_RightGoalDetected == false && m_IsLeftHotGoal  == true)  );
}

/************************************************************************************************/
/********************************** Autonomous Modes ********************************************/
/************************************************************************************************/

void TechBot3::DipSwitchChoice(int& o_Choice)
{
  // Assume que tous les dipswitch sont assignes au choix de mode autonome
  int DipswitchTotal = 0;
  DipswitchTotal += ((m_Dipswitch1.Get() == true)? 1 : 0);
  DipswitchTotal += ((m_Dipswitch2.Get() == true)? 2 : 0);
  DipswitchTotal += ((m_Dipswitch3.Get() == true)? 4 : 0);
  DipswitchTotal += ((m_Dipswitch4.Get() == true)? 8 : 0);
  
  o_Choice = DipswitchTotal;
}

double TechBot3::AutonomousForwardAdjustment()
{
  double correction = m_IRS.GetRightDistance() - m_IRS.GetLeftDistance();
  
  // Scale la correction a 1 pouce de difference ce qui correspond
  // au un drive maximum de 100% (Gauche et droite)
  if(correction > 1.0)          // Si le robot a tendance à aller à gauche
  {
    correction = 1.0;           //Ajuster en allant à droite
  }
  else if (correction < -1.0)   // Si le robot a tendance à aller à droite
  {
    correction = -1.0;          //Ajuster en allant à gauche
  }
  // Limite l'ajustement rotation a 25% de la drive
  return (correction / 4);
}

// Mode à 0 ballon
void TechBot3::AutonomousGoReturn()
{
  switch(m_AutonomousStep)
  {
    // Step 1 - Initialise le lanceur et les autres données
    case 1 :       
      // Debug Logging
      printf("AutonomousStep 1\n");
      
      m_GoalieDistance = 72;       // Il faut déterminer la distance de la position à lancer le but
                                      // jusqu'à la line entre les zones. La distance sera en pouces.
      
      // Prepare shooter
      m_Launcher.SetLauncherInitialisation(true);
      m_Launcher.PrepareHighGoal();
      
      // Prepare wings
      m_Catcher.CloseWings();
      
      // Prepare picker for camera height
      // To be completed
      
      // Vision
//      m_Vision.SelectTarget(VisualTracking::c_VisTarget_HotGoal);
      
      if (m_LeftGoalDetected  == false &&
          m_RightGoalDetected == false  )
      {
        //DEBUG: Pour tester verifier la vision dans la détection du HotGoal
        //printf("AutonomousStep 1: Cherche hotgoal\n");
//        m_Vision.FindTarget(m_LeftGoalDetected, m_IsLeftHotGoal, m_RightGoalDetected, m_IsRightHotGoal);
      }
      //DEBUG: Pour tester verifier la vision dans la détection du HotGoal
//      printf("Left Detected=%d, Left Hot=%d | Right Detected=%d, Right Hot=%d\n",
//             m_LeftGoalDetected, m_IsLeftHotGoal, m_RightGoalDetected, m_IsRightHotGoal);
      
      //Reset encoders et gyro
      m_IRS.ResetVirtualEncodersDistance();
      //m_IRS.m_Gyro->Reset();
      
      //Action: Enregistrer la distance parcourue pour la Final Distance
      m_FinalDistance = m_IRS.GetDistance() + cRobotLenght;

      // Mettre le picker en mode controler et positionner a plus de 120 degre
      m_Picker.m_Mode = m_Picker.kJogAngle;
      m_Picker.SetAngle(137.0);
      
      // Va a la prochaine etape
      m_AutonomousStep = 2;
      
      break;
    
    // Step 2 - Avancer de la goalie distance
    case 2 :
      // Debug Logging
      printf("AutonomousStep 2\n");
       
      // Vision
      if (m_LeftGoalDetected  == false &&
          m_RightGoalDetected == false  )
      {
        //DEBUG: Pour tester verifier la vision dans la détection du HotGoal
        //printf("AutonomousStep 2: Cherche hotgoal\n");
//        m_Vision.FindTarget(m_LeftGoalDetected, m_IsLeftHotGoal, m_RightGoalDetected, m_IsRightHotGoal);
      }
      //DEBUG: Pour tester verifier la vision dans la détection du HotGoal
//      printf("Left Detected=%d, Left Hot=%d | Right Detected=%d, Right Hot=%d\n",
 //            m_LeftGoalDetected, m_IsLeftHotGoal, m_RightGoalDetected, m_IsRightHotGoal);
      
      // Action: avancer en ligne droite
      m_DriveForward  = cAutonomousSpeed;
      m_DriveRotation = 0;//AutonomousForwardAdjustment();
        
      double VirtualDistance = m_IRS.GetVirtualDistance();
      int    VirtualTicks    = m_IRS.getBaseLeft();
      
      // DriverStation LCD Display
      char buf[100];
      sprintf(buf, "Dist:%.2f Ticks:%d", VirtualDistance, VirtualTicks);
      m_dslcd->PrintfLine(DriverStationLCD::kUser_Line1, buf);
      m_dslcd->UpdateLCD();
      
      // If catapult is ready to shoot, shoot the ball if the shoot button is pressed
      if (VirtualDistance >= 62)
      {
        m_Launcher.LauncherShoot();       // On a les conditions on shoot
        printf("Shoot \n");
      }
      
      // Critère fin: la goalie distance est parcourue
      if ( VirtualDistance >= m_GoalieDistance)
      {
        m_AutonomousStep = 3;
        printf("ShootStop \n");
      }
      
      break;
    
    // Step 3 - Stopper le robot
    case 3 :
      // Debug Logging
      printf("AutonomousStep 3\n"); 
      
      //Action: Stopper le robot
      m_DriveForward = 0.0;
      m_DriveRotation = 0.0;  // AutonomousForwardAdjustment();  // Voir si on continue pour laisser droit
      
      // Va a la prochaine etape
      m_AutonomousStep = 100;
      
      break;
    
    default:
      break;
  }
}

void TechBot3::AutonomousGoShootReturnOneBall()
{
  // Call same steps from autonomous with 0 balls
  AutonomousGoReturn();
  
  // Start steps
  switch(m_AutonomousStep)
  {
    // Step 100 - Prepare conditions for shoot
    case 100 :
      // If catapult is ready to shoot, shoot the ball if the shoot button is pressed
      if(m_Launcher.IsCatapulteReady() == true && m_Launcher.IsPressureReady() == true
        && (m_Picker.GetDegreLeft() > 120 || m_Picker.GetDegreRight() > 120))
      {
        m_AutonomousStep = 102;
      }
      printf("Step 100");
      break;
    
    // Step 101 - Wait hot goal before shoot, or shoot after 6 seconds anyway
    case 101 :
      if (AreGoalsDetected()  == false ||
          HotGoalOnSameSide() == true   )
      {
        m_AutonomousStep = 102;
      }
      printf("step 101");
      break;
    
    // Step 102 - All conditions met, let's shoot
    case 102 :
//      m_Launcher.LauncherShoot();       // On a les conditions on shoot
      m_AutonomousStep = 103;
      break;
      
    // Step 103- Stopper le robot
    case 103 :
      // Debug Logging
      printf("AutonomousStep 6\n");
      
      // Action: Stopper le robot
      m_DriveForward = 0.0;
      m_DriveRotation = 0.0;
      
      // Critère de fin: Rien
      m_AutonomousStep = 200;

      break;
          
    default:
      // Don't put anything in default to preserve index logic
      break;
  }
}

void TechBot3::AutonomousGoShootReturnTwoBalls()
{
  // Call same steps from previous autonomous modes
  //AutonomousGoReturn();
  /*
    // Step 100 - We don't wait for hot goal; we shoot as soon as we can
    case 100 :
      // If catapult is ready to shoot, shoot the ball if the shoot button is pressed
      if(m_Launcher.IsCatapulteReady() == true && m_Launcher.IsPressureReady() == true)
      {
        m_Launcher.LauncherShoot();       // On a les conditions on shoot
        m_AutonomousStep = 101;
      }
      break;
    
    // Step 101 - Start picker and prepare catapult before shooting again
    case 101 :
      m_Launcher.PrepareCatapule();
      m_Launcher.PrepareHighGoal();
      if(m_Launcher.IsCatapulteReady() == true && m_Launcher.IsPressureReady() == true
          && m_Picker.GetDegreLeft() > 120)
      {
        m_Launcher.LauncherShoot();       // On a les conditions on shoot
        m_AutonomousStep = 102;
      */

  switch(m_AutonomousStep)
    {
      // Step 1 - Initialise le lanceur et les autres données
      case 1 :       
        // Debug Logging
        printf("AutonomousStep 1\n");
        
        // Prepare shooter
        m_Launcher.SetLauncherInitialisation(true);
        m_Launcher.PrepareHighGoal();
        
        // Prepare wings
        m_Catcher.CloseWings();
        
        //// Vision
        //m_Vision.SelectTarget(VisualTracking::c_VisTarget_HotGoal);
        //
        //if (m_LeftGoalDetected  == false &&
        //    m_RightGoalDetected == false  )
        //{
        //  //DEBUG: Pour tester verifier la vision dans la détection du HotGoal
        //  //printf("AutonomousStep 1: Cherche hotgoal\n");
        //  m_Vision.FindTarget(m_LeftGoalDetected, m_IsLeftHotGoal, m_RightGoalDetected, m_IsRightHotGoal);
        //}
        ////DEBUG: Pour tester verifier la vision dans la détection du HotGoal
        //printf("Left Detected=%d, Left Hot=%d | Right Detected=%d, Right Hot=%d\n",
        //       m_LeftGoalDetected, m_IsLeftHotGoal, m_RightGoalDetected, m_IsRightHotGoal);
      
        m_GoalieDistance = 107;       // Il faut déterminer la distance de la position à lancer le but
                                      // jusqu'à la line entre les zones. La distance sera en pouces.
        
        //Reset encoders et gyro
        m_IRS.ResetVirtualEncodersDistance();
        //m_IRS.m_Gyro->Reset();
        
        //Action: Enregistrer la distance parcourue pour la Final Distance
        m_FinalDistance = m_IRS.GetDistance() + cRobotLenght;

        // Mettre le picker en mode controler et positionner a plus de 120 degre
        m_Picker.m_Mode = m_Picker.kJogAngle;
        m_Picker.SetAngle(137.0);
        
        // Va a la prochaine etape
        if(m_Picker.GetDegreLeft() > 135.0)
        {
          m_AutonomousStep = 2;
        }
        break;
        
      // Step 2 - Roule un peu le roller pour monter le ballon     
      case 2 :
        printf("AutonomousStep 2\n");
        
        //// Vision
        //if (m_LeftGoalDetected  == false &&
        //    m_RightGoalDetected == false  )
        //{
        //  //DEBUG: Pour tester verifier la vision dans la détection du HotGoal
        //  //printf("AutonomousStep 2: Cherche hotgoal\n");
        //  m_Vision.FindTarget(m_LeftGoalDetected, m_IsLeftHotGoal, m_RightGoalDetected, m_IsRightHotGoal);
        //}
        ////DEBUG: Pour tester verifier la vision dans la détection du HotGoal
        //printf("Left Detected=%d, Left Hot=%d | Right Detected=%d, Right Hot=%d\n",
        //       m_LeftGoalDetected, m_IsLeftHotGoal, m_RightGoalDetected, m_IsRightHotGoal);
        
        m_AutonomousIteration++;
        //Active le roller pendant 500 ms
        if(m_AutonomousIteration <= 20)
        {
            m_Picker.ActivateRoller(-1.0);
        }
        else
        {
            m_Picker.ActivateRoller(0.0);
            m_AutonomousStep = 3;
            m_AutonomousIteration = 0;
        }
        break;
        
      // Step 3 - Avancer de la goalie distance
      case 3 :
        // Debug Logging
        printf("AutonomousStep 3\n"); 
         
        //// Vision 
        //if (m_LeftGoalDetected  == false &&
        //    m_RightGoalDetected == false  )
        //{
        //  //DEBUG: Pour tester verifier la vision dans la détection du HotGoal
        //  //printf("AutonomousStep 3: Cherche hotgoal\n");
        //  m_Vision.FindTarget(m_LeftGoalDetected, m_IsLeftHotGoal, m_RightGoalDetected, m_IsRightHotGoal);
        //}
        ////DEBUG: Pour tester verifier la vision dans la détection du HotGoal
        //printf("Left Detected=%d, Left Hot=%d | Right Detected=%d, Right Hot=%d\n",
        //       m_LeftGoalDetected, m_IsLeftHotGoal, m_RightGoalDetected, m_IsRightHotGoal);
        
        // Action: avancer en ligne droite
        m_DriveForward  = cAutonomousSpeed;
        m_DriveRotation = 0;//AutonomousForwardAdjustment();
          
        double VirtualDistance = m_IRS.GetVirtualDistance();
        int    VirtualTicks    = m_IRS.getBaseLeft();
        
        // DriverStation LCD Display
        char buf[100];
        sprintf(buf, "Dist:%.2f Ticks:%d", VirtualDistance, VirtualTicks);
        m_dslcd->PrintfLine(DriverStationLCD::kUser_Line1, buf);
        m_dslcd->UpdateLCD();
        // If catapult is ready to shoot, shoot the ball if the shoot button is pressed
        if(VirtualDistance >= 80)
        {
          m_Launcher.LauncherShoot();       // On a les conditions on shoot
          printf("Shoot \n");
        }
        
        // Critère fin: la goalie distance est parcourue
        if ( VirtualDistance >= m_GoalieDistance)
        {
          m_AutonomousStep = 4;
          printf("ShootStop \n");
        }
        
        break;
      
      // Step 4 - Ramène la catapulte et arrete
      case 4 :
        // Debug Logging
        printf("AutonomousStep 4\n"); 
        
        m_Catcher.OpenWings();
        
        m_DriveForward  = 0;
        m_DriveRotation = 0;//AutonomousForwardAdjustment();
        
        if (m_Launcher.m_CatapulteReady == false && m_Launcher.m_PrepareCatapulte == false && 
            m_Launcher.m_DelaiShoot == 0)
        {
            m_Launcher.PrepareCatapule();
            m_Picker.ActivateRoller(-1.0);
            m_Picker.SetPickerPosition(80.0);
        }
        else if (m_Launcher.m_CatapulteReady == true)
        {
            m_Picker.ActivateRoller(0.0);
            m_AutonomousStep = 5;
            m_AutonomousIteration = 0;
        }
        
        break;
        
      // Step 5 - Met le ballon dans la catapulte
      case 5 :
        //Debug Logging
        printf("AutonomousStep 5\n");
        
        m_DriveForward  = 0;
        m_DriveRotation = 0;//AutonomousForwardAdjustment();
        
        m_Catcher.OpenWings();
        
        m_IRS.ResetVirtualEncodersDistance();
        
        m_AutonomousIteration++;
        //Active le roller pendant 1000 ms
        if(m_AutonomousIteration <= 75)
        {
            m_Picker.SetPickerPosition(137.0);
            m_Catcher.CloseWings();
        }
        else
        {
            m_Catcher.OpenWings();
            m_AutonomousStep = 6;
            m_AutonomousIteration = 0;
        }
        
      break;
        
      // Step 6 - Avance un peu et tire le second ballon
      case 6 :
        //Debug Logging
        printf("AutonomousStep 6\n");
        /*
        m_DriveForward  = cAutonomousSpeed;
        m_DriveRotation = 0;//AutonomousForwardAdjustment();
        
        VirtualDistance = m_IRS.GetVirtualDistance();
        VirtualTicks    = m_IRS.getBaseLeft();
        
        // DriverStation LCD Display
        sprintf(buf, "Dist:%.2f Ticks:%d", VirtualDistance, VirtualTicks);
        m_dslcd->PrintfLine(DriverStationLCD::kUser_Line1, buf);
        m_dslcd->UpdateLCD();
        // If catapult is ready to shoot, shoot the ball if the shoot button is pressed
        if (VirtualDistance >= 20)
        {
            m_Launcher.LauncherShoot();       // On a les conditions on shoot
            printf("Shoot \n");
        }
        
        // Critère fin: la goalie distance est parcourue
        if (VirtualDistance >= 30)
        {
            m_AutonomousStep = 7;
            printf("ShootStop \n");
        }
        */
        if(m_Picker.GetDegreLeft() > 135.0);
        {
            printf("Lance \n");
            m_Launcher.LauncherShoot();
            m_AutonomousStep = 7;
        }
        
        break;
    
      // Step 7 : Désactive tout
      case 7 :
        //Debug Logging
        printf("AutonomousStep 7\n");
        
        //Action: Stopper le robot
        m_DriveForward = 0.0;
        m_DriveRotation = 0.0;
        
        break;
        
    default:
      // Don't put anything in default to preserve index logic
      break;
  }
}
/********************************** Miscellaneous Routines *************************************/

START_ROBOT_CLASS(TechBot3);
