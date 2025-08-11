// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <cmath>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/XboxController.h>

#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/SubsystemBase.h>

//#include <commands/Drive.h>
#include <frc/motorcontrol/victorSP.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include "studica/AHRS.h"

//#define M_PI = 3.14159265358979323846
//#include <frc/SPI.h>




class DriveContinuous : public frc2::SubsystemBase  {
 public:
  
  
  DriveContinuous();
  void Periodic() override;
  
  static void setMecanumDrive(double translationAngle, double translationPower, double turnPower, DriveContinuous *m_drive);
  //If not supplied with a value for gyroAngle, the drive system will function without the field orientation
  static void DriveCartesian(double ySpeed, double xSpeed, double zRotation, DriveContinuous *m_drive, double gyroAngle = 0.0);
  private:
  ctre::phoenix::motorcontrol::can::VictorSPX *RIGHT_FRONT_DRIVE_MOTOR;
  ctre::phoenix::motorcontrol::can::VictorSPX *RIGHT_BACK_DRIVE_MOTOR;
  ctre::phoenix::motorcontrol::can::VictorSPX *LEFT_FRONT_DRIVE_MOTOR;
  ctre::phoenix::motorcontrol::can::VictorSPX *LEFT_BACK_DRIVE_MOTOR;
  
  

};
