/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "Launcher.h"

/* --------------------------------------------------------------------------- */
// Constructors 

Launcher::Launcher() :  m_MotorWinchCatapult(C_MotorWinch),
                        m_SolenoidCatapultElastic(C_cRIOPneumaticModuleNumber, C_SolenoidCatapultElastic),
                        m_SolenoidPressureSelector(C_cRIOPneumaticModuleNumber, C_SolenoidPressureSelector), 
                        m_SolenoidReleaser(C_cRIOPneumaticModuleNumber, C_SolenoidReleaser), 
                        m_LSwitchCatapult(C_LSwitchCatapult)
//                        m_Catcher()
{
  m_PrepareCatapulte = false;
  m_CatapulteReady = false;
  m_SpeedForward = -1.0;
  m_SpeedReverse = 1.0;
  m_WaitReverse = 0;
  
  m_DelaiShoot = 0;
  m_DelaiPostShoot = 0;
  m_PressureSelector = false;
  m_OldStatePressureSelector = false;
  m_CatapultElastic = false;
  m_OldStateCatapultElastic = false;
  m_ManuelWinchOut = false;
  m_EtapeSequenceChangement = 0;
  m_waitPressure_1 = 10;              // 10 ms de temps d'attente
  m_waitPressure_2 = 0;
  m_PressureReady = false;
}

Launcher::~Launcher()
{
}

/* --------------------------------------------------------------------------- */
// Methods 

void Launcher::GestionLauncher()
{
  // -----------------------------------------------------------------
  // Prepare la catapule
  
  // Winch Control
  float motorWinchOutput = 0.0;
  
  if(m_PrepareCatapulte == true  && m_CatapulteReady == false)
  {
    switch(m_EtapePrepareCatapulte)
    {
      case 0 :
        motorWinchOutput = m_SpeedForward;      // Enroule la courroie
        
        if(m_LSwitchCatapult.Get() == false)     // Quand on recoit la limite switch
        {
          motorWinchOutput = 0.0;               // Arret du moteur
          m_EtapePrepareCatapulte = 1;          // Vas a l'etape suivante
          m_WaitReverse = 60;                  // Set le temps de deroulage de la courroie
          //printf("Recu Switch \n");  Enleve le print pour laisser toute la place a ceux de la vision

        }
        
        break;
        
      case 1 :
        motorWinchOutput = m_SpeedReverse;      // Deroule la courroie
        //printf("Recu Reverse \n");  Enleve le print pour laisser toute la place a ceux de la vision
        
        if( (m_WaitReverse > 0)  && ((m_WaitReverse - 1) == 0)) // Detecte qu'on est a la fin
        {
          //printf("Recu Fin Reverse \n");  Enleve le print pour laisser toute la place a ceux de la vision
          motorWinchOutput = 0.0;               // Arret du moteur
          m_CatapulteReady = true;              // Catapule est prete
          m_PrepareCatapulte = false;           // preparation terminé on reset le flag
          m_EtapePrepareCatapulte = 0;          // Remet l'etape a zére
        }
        
        if (m_WaitReverse)
        {
          --m_WaitReverse;                      // Decremente le compteur
        }
        
        break;
        
      default:
        motorWinchOutput = 0.0;                 // Arret du moteur
        m_EtapePrepareCatapulte = 0; 
        m_CatapulteReady = false;               // Flag a false car ne doit pas etre a cette etape
        m_PrepareCatapulte = false;             // Flag a false car ne doit pas etre a cette etape
        break;
    }
  }
  
  // Decrement counter after shoot has occurred
  if (m_DelaiPostShoot > 1)
  {
    m_DelaiPostShoot--;
  }
  
  // Condition manuel pour la winch inverse pour depanner seulement
  if(m_ManuelWinchOut == true)
  {
      motorWinchOutput = m_SpeedReverse;
      m_PrepareCatapulte = false;           // Arret de la sequence
      m_CatapulteReady = false;             // Catapulte non prete
  }
  
  m_MotorWinchCatapult.Set(motorWinchOutput);   // Moteur pour enrouler
  SmartDashboard::PutNumber("Moteur Winch", m_MotorWinchCatapult.Get());
  SmartDashboard::PutBoolean("Switch Winch", m_LSwitchCatapult.Get());
 
  // Gestion des pression 
  // -------------------------------------------------------
  
  // si on detecte un changement dans la pression la commande de pression 
  if((m_PressureSelector != m_OldStatePressureSelector || m_CatapultElastic != m_OldStateCatapultElastic) 
  || (m_PrepareCatapulte == false && m_OldPrepareCatapulte == true))
  {
    // Initialise la sequence de changement de pression
    m_EtapeSequenceChangement = 0;   // Reset la sequence
    m_waitPressure_1 = 10;           // 10 ms d'attente
    m_PressureReady = false;         // Flag des pression qui ne sont pas prete

    //printf("Ajustement des pressions"); Enleve le print pour laisser toute la place a ceux de la vision
  }
  
  m_OldStatePressureSelector = m_PressureSelector;
  m_OldStateCatapultElastic = m_CatapultElastic;
  m_OldPrepareCatapulte = m_PrepareCatapulte;
  
  bool StatSelector = m_PressureSelector;
  bool StatElastic  = m_CatapultElastic;
  if(m_PressureReady == false)
  {
    switch (m_EtapeSequenceChangement)
    {
      case 0:                                   // Active seulement la selection
        StatElastic = false;                    // Desactive l'etat de l'elastic pendant 0.1 sec
        if(m_waitPressure_1 > 0)
        {
          m_waitPressure_1--;                   // Decremante le compteur
        }
        else
        {
          m_EtapeSequenceChangement = 1;        // si delai ecouler passe a l'etape suivante
          m_waitPressure_2 = 25;                // Set le delai de l'etape 2 a 0.25 sec
        }
        break;
        
      case 1:
        if(m_waitPressure_2 > 0)
        {
          m_waitPressure_2--;                   // Decremante le compteur
        }
        else
        {
          m_EtapeSequenceChangement = 0;        // Reinitialse l'etape
          m_PressureReady = true;               // Indique la pression est prete
        }
        break;
        
      default:
        m_EtapeSequenceChangement = 0;          // Reset la sequence
        m_waitPressure_1 = 10;                  // 10 ms d'attente
        m_PressureReady = false;                // Flag des pression qui ne sont pas prete
        break;
    }
  }
  
  // Gestion de préparation de la catapulte 
  // -------------------------------------------------------
  if(m_PrepareCatapulte == true)                // Si on prepare la catapule on doit desaciver les cylindres
  {
    m_SolenoidPressureSelector.Set(false);
    m_SolenoidCatapultElastic.Set(false);
  }
  else                                          // Sinon on applique la valeur controler avec la sequence
  {
    m_SolenoidPressureSelector.Set(StatSelector);
    m_SolenoidCatapultElastic.Set(StatElastic);
  }
  
  // Shoot 
  // -------------------------------------------------------
  if( m_DelaiShoot > 0 )
  {
    --m_DelaiShoot;                             // Decremante le temps de shooting
 //   m_Catcher.OpenWings();
    m_CatapulteReady = false;
    m_SolenoidReleaser.Set(true);               // Active la valve
  }
  else
  {
//    m_Catcher.CloseWings();
    m_SolenoidReleaser.Set(false);              // Desactive la valve
//    PrepareCatapule();
  }

}

void Launcher::PrepareCatapule(void)
{
  m_DelaiPostShoot = 1 * c_IterationPerSecond;
  m_PrepareCatapulte = true;
}

// Permet de partir en mode autonome preloader
void Launcher::SetLauncherInitialisation(bool catapulteReady)
{
  m_CatapulteReady = catapulteReady;
}

bool Launcher::IsCatapulteReady()
{
  return m_CatapulteReady;
}
bool Launcher::IsPressureReady()
{
  return m_PressureReady;
}

void Launcher::LauncherShoot()
{
  m_DelaiShoot = 50;            // Set le délai de maintien de la valve
}

void Launcher::LauncherPower(bool PressureSelector, bool CatapultElastic)
{
  m_PressureSelector = PressureSelector;
  m_CatapultElastic = CatapultElastic;
}

void Launcher::PrepareHighGoal()
{
  LauncherPower(true,true);     // Selector = true ,  Elastic = True
}

void Launcher::PrepareLowGoal() 
{
  LauncherPower(false,false);   // Selector = false ,  Elastic = false
}

void Launcher::PrepareTruss()
{
  LauncherPower(false,true);    // Selector = false ,  Elastic = True
}
void Launcher::ReverseWinchManuel(bool State)
{
  m_ManuelWinchOut = State;    // Selector = false ,  Elastic = True
}
