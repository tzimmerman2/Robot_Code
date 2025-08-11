// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <string>
#include <cmath>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/motorcontrol/victorSP.h>
#include <frc/drive/MecanumDrive.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

#include <frc2/command/SubsystemBase.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc2/command/Command.h>
#include <frc2/command/CommandHelper.h>
#include <frc/XboxController.h>
#include <subsystems/DriveContinuous.h>
#include <functional>
#include <frc2/command/Command.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "Classes/InputDevice.h"
#include "studica/AHRS.h"


//#include "Robot.h"

class Drive : public frc2::CommandHelper<frc2::Command, Drive> {
 public:
  
 
  Drive(DriveContinuous*, inputDevice*, studica::AHRS*, frc::SendableChooser<double>*);
  void Execute() override;
  bool IsFinished() override;
  private:
  //Mecanum drive subsystem
  DriveContinuous* m_drive;
  //Xbox controller ignore the 1 after the name it is still the same xbox controller
  inputDevice *joystick;
  //navX gyro
  studica::AHRS *m_gyro;
  //pointer to smartdashboard robot speed selector
  frc::SendableChooser<double> *m_robotSpeed;
  //Left joystick X
  double x;
  //Left joystick Y
  double y;
  //Right joystick X
  double z;

  //static frc::SendableChooser<double>* driveSpeed;
  
};
