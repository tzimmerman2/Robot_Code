// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/motorcontrol/victorSP.h>
#include <frc/XboxController.h>
#include <frc/drive/MecanumDrive.h>


//frc::XboxController *controller(0);
//frc::VictorSP *MotorRight;
//frc::VictorSP *MotorLeft;
//frc::VictorSP *MotorRight2; 
//frc::VictorSP *MotorLeft2;

//static class Drive driveSystem = *new Drive();
#include "Classes/InputDevice.h"


DriveContinuous* Robot::driveSub = nullptr;
Drive* Robot::driveCommand = nullptr;

void Robot::RobotInit() {
  
  frc::SmartDashboard::PutNumber("Robot Speed", 0.5);
  
  frc::SmartDashboard::PutData("Robot Speed", &robotSpeed);
  //initialize navX as gyro
  gyro = new studica::AHRS(studica::AHRS::NavXComType::kMXP_SPI); 
  //initialize xbox controller
  Joystick = new inputDevice(0.25);
  //initialize mecanum drive subsystem
  driveSub = new DriveContinuous();
  //initialize the command system that runs the mecanum drive subsystem
  driveCommand = new Drive(driveSub, Joystick, gyro, (&robotSpeed));
  
  //make the mecanum drive subsystem always scheduled to the command so nothing else can drive
  driveSub->SetDefaultCommand(std::move(*driveCommand));

  //smart dashboard auto
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  gyro->ZeroYaw();
  
  gyro->Reset();
  
  
}
/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  //Run the Command Scheduler. Very importent!
  frc2::CommandScheduler::GetInstance().Run();
  frc::SmartDashboard::GetNumber("controller deadzone", .15);
  
}


/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
/*
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  fmt::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
*/
}

void Robot::AutonomousPeriodic() {
  //Start auto
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {
  //DriveContinuous();
}

void Robot::TeleopPeriodic() {

  //drive system should start automaticly when teleop starts
  (*Joystick).UpdateDevice();
  if(Joystick->GetRawButtonPressed(1)){
    Joystick->ActiveDeviceHasSpeedAxis();
    gyro->ZeroYaw();
  }

  //frc::SmartDashboard::PutNumber("navX", gyro->GetYaw());
}
  
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
