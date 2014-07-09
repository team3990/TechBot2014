/*----------------------------------------------------------------------------*/
/* Copyright (c) TechForKid 2014. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef CONFIG_H
#define CONFIG_H

// Digital Input/Output
const int c_DeepSwtich1(1);                     // TechBot3.h
const int c_DeepSwtich2(2);                     // TechBot3.h
const int c_DeepSwtich3(3);                     // TechBot3.h
const int c_DeepSwtich4(4);                     // TechBot3.h
const int C_EncoderDrivingBaseLeft_A(5);        // IRS.h
const int C_EncoderDrivingBaseLeft_B(6);        // IRS.h
const int C_EncoderDrivingBaseRight_A(7);       // IRS.h
const int C_EncoderDrivingBaseRight_B(8);       // IRS.h
const int C_CompressorIO(9);                    // TechBot3.h
const int C_UltraSonicPing(10);                 // TechBot3.h   # SPARE
const int C_UltraSonicEcho(11);                 // TechBot3.h   # SPARE
const int C_LSwitchCatapult(12);                // Launcher.h

// Analog Input
/*
const int C_TemperatureChannel(2);              // TechBot3.h
*/
// const int C_GyroChannel(1);                     // TechBot3.h
const int C_PickerEncoderLeft(3);               // TechBot3.h
const int C_PickerEncoderRight(4);              // TechBot3.h

// Out
/*
const int C_AccelCK(1);                         // TechBot3.h
const int C_AccelDI(2);                         // TechBot3.h
const int C_AccelDO(3);                         // TechBot3.h
const int C_AccelCS(4);                         // TechBot3.h
*/

// Relay
const int C_CompressorRelay(1);                 // TechBot3.h
// const int C_LEDRelay(2);                        // TechBot3.h

// cRIO Modules
const int C_AccelModule(1);                     //DIO Module
const int C_cRIOPneumaticModuleNumber(2);       //Pneumatic Module Number

// Solenoids
const int C_SolenoidPressureSelector(1);        // Launcher.h
const int C_SolenoidCatapultElastic(2);         // Launcher.h
const int C_SolenoidSPARE3(3);                  //              # SPARE
const int C_SolenoidWings(4);                   // Launcher.h
const int C_SolenoidShifter(5);                 // DrivingBase.h
const int C_SolenoidReleaser(6);                // Launcher.h

//PWM
const int C_MotorLeftFront(1);                  // DrivingBase.h
const int C_MotorRightFront(2);                 // DrivingBase.h
const int C_MotorWinch(3);                      // Launcher.h
const int C_MotorRoller(4);                     // Picker.h
const int C_MotorLeftArmPicker(6);              // Picker.h
const int C_MotorRightArmPicker(5);             // Picker.h

// Parameters
// const int C_ArmDistanceMax(50);
// const int C_ArmDistanceMin(1);
const float C_ArmDistanceMax(140);
const float C_ArmDistanceMin(60);

const int c_IterationPerSecond(50);

const int cAutonomous0Ballon(0);
const int cAutonomous1Ballon(1);
const int cAutonomous2Ballon(2);
const int cAutonomous3Ballon(3);
const double cAutonomousSpeed(0.8);

const int cRobotLenght(37);

#endif //CONFIG_H
