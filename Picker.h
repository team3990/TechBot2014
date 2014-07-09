/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef PICKER_H
#define PICKER_H

#include "WPILib.h"
#include "Config.h"
#include "PIDRotation.h"

class Picker
{
  
public:
  
  // Constructors
  Picker();
  ~Picker();

  // Absolute Encoders
  
  // Motors
  Victor                m_MotorLeftArmPicker;
  Victor                m_MotorRightArmPicker;
  Victor                m_MotorRoller;
  
  // Encoders & PID
  PIDRotation           m_PIDRotationLeft;       // Donne la valeur en degre reconnue par le PID
  PIDRotation           m_PIDRotationRight;      // Donne la valeur en degre reconnue par le PID
  PIDController         m_PIDLeftPickerPosition;
  PIDController         m_PIDRightPickerPosition;
  AnalogChannel         m_AnalogEncoderLeft;
  AnalogChannel         m_AnalogEncoderRight;
  
  // Properties
  enum                  PickerMode
  {
    kDisable = 0, 
    kAngle = 1,         // Set l'angle avec un PID 
    kJogAngle = 2,      // Set l'angle avec un controle a vitesse fixe
    kJugForward = 3,    // Active les moteurs manuellement foward 
    kJugReverse = 4     // Active les moteurs manuellement reverse
  };
  
  float                 m_VoltageMax;        // Voltage maximum 5 volts
  float                 m_CalibrationValue;  // Voltage a 90 degré
  float                 m_OffsetLeft;        // offset de voltage a gauche
  float                 m_OffsetRight;       // offset de voltage a droite
  float                 m_RatioEncoder;      // Ration de l'encodeur
  float                 m_DegreRotation;     // Valeur pour 360 degre
  float                 m_AngleCalibration;  // La calibration doit se faire a 90 degre
  float                 m_SetPointRamasse;   // Valeur en degre pour ramasser le ballon
  float                 m_SetPointDeplace;   // Valeur en degre pour les deplacement
  float                 m_SetSetPoint;       // Position a atteindre positionnement jog controler
  float                 m_SetTolerence;      // Tolerence du positionnement en jog de l'angle
  
  Picker::PickerMode    m_Mode;              // Mode de positionnement
  float                 m_speedRight;        // Vitesse moteur gauche
  float                 m_speedLeft;         // Vitesse moteur droite
  
  float                 m_cylinderSpeed;     // Vitesse de rouleau
  
  // Methods 
  
  // Section PID
  bool                  SetPickerPosition(double angle);
  void                  PIDLeftReset();
  void                  PIDLeftEnable();
  void                  PIDLeftDisable();
  void                  SetPIDLeft(float p,float i,float d);
  
  void                  PIDRightReset();
  void                  PIDRightEnable();
  void                  PIDRightDisable();
  void                  SetPIDRight(float p,float i,float d);
  
  // Gestion des encodeurs
  float                 GetVoltageLeft();       // Retourne la valeur de l'encodeur (0-5 volts)
  float                 GetVoltageRight();      // Retourne la valeur de l'encodeur (0-5 volts)
  float                 GetEncoderLeft();       // Retourne la valeur de l'encodeur en voltage calibré
  float                 GetEncoderRight();      // Retourne la valeur de l'encodeur en voltage calibré
  void                  SetEncoderCalibration();// Calibre les offsets pour la position 90 degré  
  float                 GetDegreLeft();         // Retourne la position en degré de l'encodeur
  float                 GetDegreRight();        // Retourne la position en degré de l'encodeur
  
  // Type de positionnement
  void                  SetMode(Picker::PickerMode mode);
  void                  SetSpeed(float speed);
  void                  SetSpeed(float speedLeft, float speedRight);
  void                  SetAngle(float angle);
  void                  SetCylinderSpeed(float speed);
  void                  ActivateRoller(float speed);
  
  void                  GestionPicker();
  bool                  OnTarget();
  
};

#endif // PICKER_H

