// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/motorcontrol/victorSP.h>
#include <frc/XboxController.h>
#include <frc/drive/MecanumDrive.h>
#include <commands/Drive.h>
//#include <subsystems/DriveContinuous.h>
#include <frc/RobotBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <memory.h>
#include <frc/DriverStation.h>
#include <studica/AHRS.h>
#include "Classes/InputDevice.h"


//#include <commands/Drive.h>

class Robot : public frc::TimedRobot {
 public:
  
  
  
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  void SimulationInit() override;
  void SimulationPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
  
  frc::SendableChooser<double> robotSpeed;

  static DriveContinuous *driveSub;
  static Drive *driveCommand;
  static frc2::CommandPtr commandPtr;
  inputDevice* Joystick;
  
  studica::AHRS *gyro;
};
