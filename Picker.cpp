/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "Picker.h"

//
//  Fonctionnement de la classe picker
//
//  Entrees:  Encodeur Analogique (droite et gauche)
//            La valeur est de 0 a 5 volts
//            La lecture du coté gauche est inversé.  On obtient un
//            voltage qui augmente quand les bras vont vers l'exterieur du robot
//
//  Sorties:  Moteur (droite et gauche)
//            Branché de facon a ce quand on donne une valeur positive les bras 
//            vont vers l'extérieur du robots
//
//  Calibration :  Nous avons calibré l'ange a 90 degré.  Le picker est donc a son
//                 point le plus haut
//   


/* --------------------------------------------------------------------------- */
// Constructors 

Picker::Picker():       m_MotorLeftArmPicker(C_MotorLeftArmPicker), 
                        m_MotorRightArmPicker(C_MotorRightArmPicker), 
                        m_MotorRoller(C_MotorRoller),
                        m_PIDRotationLeft(),
                        m_PIDRotationRight(),
                        m_PIDLeftPickerPosition((float)1.0, (float)1.0, (float)1.0, &m_PIDRotationLeft, &m_MotorLeftArmPicker, (float)0.1), 
                        m_PIDRightPickerPosition((float)1.0, (float)1.0, (float)1.0, &m_PIDRotationRight, &m_MotorRightArmPicker, (float)0.1), 
                        m_AnalogEncoderLeft(C_AccelModule, C_PickerEncoderLeft), 
                        m_AnalogEncoderRight(C_AccelModule, C_PickerEncoderRight)
{
  // Logging to NetConsole
  printf("Constructor Picker started\n");
  
  m_VoltageMax = 5.0;
  m_CalibrationValue = 2.5;
  m_OffsetLeft = 1;   // 1.512;
  m_OffsetRight = 1.0; //-2.308;
  m_RatioEncoder = 0.44444;           // 0.44444444 pour le robot de competition, 0.5 pour le robot test
  m_AngleCalibration = 90.0;          // 90 degre
  m_DegreRotation = 360.0;            // un tour est 360 degre
  m_SetPointRamasse = 137.0;          // Position pour ramasser les ballons
  m_SetPointDeplace = 70.0;           // Position pour les déplacements
  m_SetSetPoint = m_AngleCalibration; // Initialise le positionnement a la valeur de calibration
  m_SetTolerence = 1.75;               // Tolerence du positionnement
  
  
  m_Mode = Picker::kDisable;
  m_speedLeft = 0.6;
  m_speedRight = 0.5;
  
  m_cylinderSpeed = 0.2;
  
  // Logging to NetConsole
  printf("Constructor Picker completed\n");
  
}

Picker::~Picker()
{ 
}

/* --------------------------------------------------------------------------- */
// Methods 

void Picker::GestionPicker()
{
  float motorLeftOutput;
  float motorRightOutput;
  float cylinderOutput;
  
  Picker::PickerMode mode;
  
  // Entre l'angle pour l'encodeur virtuel
  m_PIDRotationLeft.PutValue(Picker::GetDegreLeft());
  m_PIDRotationRight.PutValue(Picker::GetDegreRight());
  
  mode = m_Mode;
  
  switch (mode)
  {
  
    case Picker::kDisable :
      //Disabled mode, we give a speed of 0.0 to both motors
      motorLeftOutput = 0.0;
      motorRightOutput = 0.0;
      cylinderOutput = 0.0;
      
      Picker::PIDLeftDisable();
      Picker::PIDRightDisable();
      
      m_MotorLeftArmPicker.Set(0.0);
      m_MotorRightArmPicker.Set(0.0);
//      m_MotorRoller.Set(0.0);
      break;
      
    case Picker::kJugForward :
      //Jug mode, we directly give the wanted speed to both motors
      Picker::PIDLeftDisable();
      Picker::PIDRightDisable();
      
      m_MotorLeftArmPicker.Set(m_speedLeft);
      m_MotorRightArmPicker.Set(m_speedRight);
//      m_MotorRoller.Set(m_cylinderSpeed);
      break;
      
    case Picker::kJugReverse :
      //Jug mode, we directly give the wanted speed to both motors
      Picker::PIDLeftDisable();
      Picker::PIDRightDisable();
      
     m_MotorLeftArmPicker.Set(-m_speedLeft);
     m_MotorRightArmPicker.Set(-m_speedRight);
//      m_MotorRoller.Set(m_cylinderSpeed);
      break;
        
    // Positionne ave un PID chacun des bras
    // utilise la classe PID
    case Picker::kAngle :
      Picker::PIDLeftEnable();
      Picker::PIDRightEnable();
      
      Picker::SetPIDLeft(0.03,0.001,0.002);
      Picker::SetPIDRight(0.03,0.001,0.002);
      
      
      break;
      
    // Déplace le picker en jog pour atteindre la position demande 
    // similaire au un PID mais a une vitesse fixe et tolerence
    // Reproduit ce qu'un operateur ferait manuellement
    case Picker::kJogAngle :
      Picker::PIDLeftDisable();
      Picker::PIDRightDisable();
      
      float diff;
      float ValeurAngle;
      
      // Gestion a gauche
      ValeurAngle = GetDegreLeft();
      diff = m_SetSetPoint - ValeurAngle;
      if ( diff > -m_SetTolerence && diff < m_SetTolerence )
        {
          m_MotorLeftArmPicker.Set(0.0);          // Dans la tolerence on ne bouge plus
        }
      else if ( diff > 0 )
        {
          m_MotorLeftArmPicker.Set(m_speedLeft);  // Deplace vers l'exterieur du robot
        }
      else if ( diff < 0 )
        {
          m_MotorLeftArmPicker.Set(-m_speedLeft);  // Deplace vers l'interieur du robot
        }
        
      // Gestion a droite
      ValeurAngle = GetDegreRight();
      diff = m_SetSetPoint - ValeurAngle;
      if ( diff > -m_SetTolerence && diff < m_SetTolerence )
        {
          m_MotorRightArmPicker.Set(0.0);         // Dans la tolerence on ne bouge plus
        }
      else if ( diff > 0 )
        {
          m_MotorRightArmPicker.Set(m_speedRight);// Deplace vers l'exterieur du robot
        }
      else if ( diff < 0 )
        {
          m_MotorRightArmPicker.Set(-m_speedRight);// Deplace vers l'interieur du robot
        }
      
      break;
      
    default :
      //By default, we pass 0.0 to both motors, to be sure not to move unwillingly
      Picker::PIDLeftDisable();
      Picker::PIDRightDisable();
      
      m_MotorLeftArmPicker.Set(0.0);
      m_MotorRightArmPicker.Set(0.0);
  }
  
}

void Picker::PIDLeftReset()
{
  m_PIDLeftPickerPosition.Reset();
}

void Picker::PIDLeftEnable()
{
  m_PIDLeftPickerPosition.Enable();
  // m_PIDLeftPickerPosition.SetSetpoint(90);
}

void Picker::PIDLeftDisable()
{
  m_PIDLeftPickerPosition.Disable();
}

void Picker::SetPIDLeft(float p,float i,float d)
{
  m_PIDLeftPickerPosition.SetPID(p, i, d);
}

void Picker::PIDRightReset()
{
  m_PIDRightPickerPosition.Reset();
}

void Picker::PIDRightEnable()
{
  m_PIDRightPickerPosition.Enable();
  // m_PIDRightPickerPosition.SetSetpoint(90);
}

void Picker::PIDRightDisable()
{
  m_PIDRightPickerPosition.Disable();
}

void Picker::SetPIDRight(float p,float i,float d)
{
  m_PIDRightPickerPosition.SetPID(p, i, d);
}

// Retire la valeur de l'encodeur
// Verifie si on inverse
float Picker::GetVoltageLeft()
{
  float value = m_AnalogEncoderLeft.GetVoltage();
  bool inverse = true;
  
  // Permet d'inverser selon le montage mecanique
  if (inverse == true)
    {
      value = m_VoltageMax - value;
    }
  return value;
}

//  Retire la valeur de l'encodeur
//  Verifie si on inverse
float Picker::GetVoltageRight()
{
  float value = m_AnalogEncoderRight.GetVoltage();
  bool inverse = false;
  
  
  // Permet d'inverser selon le montage mecanique
  if (inverse == true)
    {
      value = m_VoltageMax - value;
    }
  return value;
}

//
//  Retire la valeur de l'encodeur
//  Applique la calibration position de référence
//  Retourne la valeur
//
float Picker::GetEncoderLeft()
{
  float value = Picker::GetVoltageLeft();
  
 
  // Utilise la valeur de calibration (offset) pour retourner une valeur calibré
  value += m_OffsetLeft;
  if(value < 0)
    {
      value += m_VoltageMax; // S'assure d'eliminer les valeurs negative
    }
  else if (value > m_VoltageMax)
    {
      value -= m_VoltageMax; // Modulo le Voltage max pour ne pas depasser 5
    }
  
  
  return (value);
}

//
//  Retire la valeur de l'encodeur
//  Verifie si on inverse
//  Applique la calibration position de référence
//  Retourne la valeur
//
float Picker::GetEncoderRight()
{
  float value = Picker::GetVoltageRight();
  
  // Utilise la valeur de calibration (offset) pour retourner une valeur calibré
  value += m_OffsetRight;
  if(value < 0)
    {
      value += m_VoltageMax; // S'assure d'eliminer les valeurs negative
    }
  else if (value > m_VoltageMax)
    {
      value -= m_VoltageMax; // Modulo le Voltage max pour ne pas depasser 5
    }
  
  return (value);
}
//
//  convertie la valeur de voltage en degre
//
float Picker::GetDegreRight()
{
  float value = 0;
  
  // Convertie en degre en sachant qu'a 90 angle droit on est a 2.5 volts
  value = m_AngleCalibration + ((Picker::GetEncoderRight() - m_CalibrationValue ) * 
         (m_DegreRotation * m_RatioEncoder / 5));
      
  if(value < 0)
    {
      value += m_DegreRotation; // S'assure d'eliminer les valeurs negative
    }
  else if (value > m_DegreRotation)
    {
      value -= m_DegreRotation; // Modulo le Voltage max pour ne pas depasser 5
    }
  return value;
}
//
//  convertie la valeur de voltage en degre
//
float Picker::GetDegreLeft()
{
  float value = 0;
  
  // Convertie en degre en sachant qu'a 90 angle droit on est a 2.5 volts
  value = m_AngleCalibration + ((Picker::GetEncoderLeft() - m_CalibrationValue ) * 
         (m_DegreRotation * m_RatioEncoder / 5));
  
  if(value < 0)
    {
      value += m_DegreRotation; // S'assure d'eliminer les valeurs negative
    }
  else if (value > m_DegreRotation)
    {
      value -= m_DegreRotation; // Modulo le Voltage max pour ne pas depasser 5
    }
      
  return value;
}

void Picker::SetEncoderCalibration()
{
  float RightValue = Picker::GetVoltageRight();
  float LeftValue = Picker::GetVoltageLeft();

  
  m_OffsetRight = m_CalibrationValue - RightValue;
  m_OffsetLeft = m_CalibrationValue - LeftValue;
  
}

bool Picker::SetPickerPosition(double angle)
{
  if ((angle > C_ArmDistanceMin) || (angle < C_ArmDistanceMax))
  {
    m_PIDLeftPickerPosition.SetSetpoint(angle);
    m_PIDRightPickerPosition.SetSetpoint(angle);
    m_SetSetPoint = angle;
  }
  return Picker::OnTarget();
}


void Picker::SetMode(Picker::PickerMode mode)
{
  m_Mode = mode;
}

void Picker::SetAngle(float angle)
{
  if ((angle > C_ArmDistanceMin) && (angle < C_ArmDistanceMax))
  {
      m_SetSetPoint = angle;
  }
}

void Picker::SetSpeed(float speed)
{
  m_speedLeft = speed;
  m_speedRight = speed;
}

void Picker::SetSpeed(float speedLeft, float speedRight)
{
  m_speedLeft = speedLeft;
  m_speedRight = speedRight;
}

void Picker::SetCylinderSpeed(float speed)
{
  m_cylinderSpeed = speed;
}

bool Picker::OnTarget()
{
//  return (m_EncoderLeftPickerPosition.GetDistance() - m_angle) > -1 && (m_EncoderLeftPickerPosition.GetDistance() - m_angle) < 1;
   return true;
}

void Picker::ActivateRoller(float speed)
{
  m_MotorRoller.Set(speed);
}
