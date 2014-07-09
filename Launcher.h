/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "WPILib.h"
#include "Catcher.h"
#include "Picker.h"
#include "Config.h"

class Launcher
{ 
	  
public:
  
  // Constructors
  Launcher();
  ~Launcher();
  
  // Motors
  Victor        m_MotorWinchCatapult;
  
  // Solenoids
  Solenoid      m_SolenoidCatapultElastic;
  Solenoid      m_SolenoidPressureSelector;
  Solenoid      m_SolenoidReleaser;
  
  // Limit Switches
  DigitalInput  m_LSwitchCatapult;       // To detect if the catapult has cranked enough
  
  // Catcher to handle for shooting sequences
//  Catcher       m_Catcher;
  
  // Prepare la catapule
  bool          m_PrepareCatapulte;            // Flag pour démarrer la preparation
  bool          m_OldPrepareCatapulte;         // Pour detecter la transition
  bool          m_CatapulteReady;              // Flag pour indiquer que la catapule est prete
  int           m_EtapePrepareCatapulte;       // Etape de preparation de l'enroulement
  float         m_SpeedForward;                // Vitesse d'enroulement
  float         m_SpeedReverse;                // Vitesse pour derouler
  int           m_WaitReverse;                 // Temps de maintien pour le derouler le fils
  bool          m_ManuelWinchOut;              // Envoye un signal pour derouler
  
  // Delai de shoot
  int           m_DelaiShoot;                 // Activation du shoot
  int           m_DelaiPostShoot;             // Délai après le shoot avant de recrinquer
  
  // Controle des pressions
  bool          m_PressureSelector;
  bool          m_OldStatePressureSelector;
  bool          m_CatapultElastic;
  bool          m_OldStateCatapultElastic;
  int           m_EtapeSequenceChangement;
  int           m_waitPressure_1;
  int           m_waitPressure_2;
  bool          m_PressureReady;
  
  // Methods
  void          LauncherInit();
  void          GestionLauncher();
  void          PrepareCatapule(void);
  void          LauncherShoot();
  void          LauncherPower(bool PressureSelector, bool CatapultElastic);
  void          SetLauncherInitialisation(bool catapulteReady);
  bool          IsCatapulteReady();
  bool          IsPressureReady();
  void          PrepareLowGoal();
  void          PrepareHighGoal();
  void          PrepareTruss();
  void          ReverseWinchManuel(bool State);
  
};

#endif //LAUNCHER_H
