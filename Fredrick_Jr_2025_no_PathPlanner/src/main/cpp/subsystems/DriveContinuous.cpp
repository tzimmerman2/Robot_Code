// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.


#include "subsystems\DriveContinuous.h"

//frc::XboxController *controller1(0);
DriveContinuous::DriveContinuous() :
  RIGHT_FRONT_DRIVE_MOTOR(new ctre::phoenix::motorcontrol::can::VictorSPX(3)), //3
  RIGHT_BACK_DRIVE_MOTOR(new ctre::phoenix::motorcontrol::can::VictorSPX(1)), //1
  LEFT_FRONT_DRIVE_MOTOR(new ctre::phoenix::motorcontrol::can::VictorSPX(2)), //2
  LEFT_BACK_DRIVE_MOTOR(new ctre::phoenix::motorcontrol::can::VictorSPX(4)) //4
  
  
  
  {
    RIGHT_FRONT_DRIVE_MOTOR->SetInverted(true);
    RIGHT_BACK_DRIVE_MOTOR->SetInverted(true);
}

void DriveContinuous::Periodic(){
  
}
/*
void DriveContinuous::setMecanumDrive(double direction, double magnitude, double zRotation, DriveContinuous *m_drive)
{
  double frontLeftSpeed = (magnitude * std::sin(direction + 3.14159265358979323846 / 4) + zRotation);
  double frontRightSpeed = (magnitude * std::cos(direction + 3.14159265358979323846 / 4) - zRotation);
  double backLeftSpeed = (magnitude * std::cos(direction + 3.14159265358979323846 / 4) + zRotation);
  double backRightSpeed = (magnitude * std::sin(direction + 3.14159265358979323846 / 4) - zRotation);

  // Normalize speeds if any speed is greater than 1.0
  double maxMagnitude = std::max({std::abs(frontLeftSpeed), std::abs(frontRightSpeed), std::abs(backLeftSpeed), std::abs(backRightSpeed)});
  if (maxMagnitude > 1.0) {
    frontLeftSpeed /= maxMagnitude;
    frontRightSpeed /= maxMagnitude;
    backLeftSpeed /= maxMagnitude;
    backRightSpeed /= maxMagnitude;
  }

  
  // Set motor speeds

  (*m_drive).LEFT_FRONT_DRIVE_MOTOR->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, frontRightSpeed); //frontLeftSpeed
  (*m_drive).RIGHT_FRONT_DRIVE_MOTOR->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, frontLeftSpeed); //frontRightSpeed
  (*m_drive).LEFT_BACK_DRIVE_MOTOR->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, backLeftSpeed); //backLeftSpeed
  (*m_drive).RIGHT_BACK_DRIVE_MOTOR->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, backRightSpeed);//backRightSpeed

}
*/
//Thanks copilot
void DriveContinuous::DriveCartesian(double ySpeed, double xSpeed, double zRotation, DriveContinuous *m_drive, double gyroAngle) {
    // If gyro angle is provided, rotate the inputs based on the gyro angle
    if (gyroAngle != 0.0) {
        double cosA = std::cos(gyroAngle);
        double sinA = std::sin(gyroAngle);

        double xSpeed_rotated = xSpeed * cosA - ySpeed * sinA;
        double ySpeed_rotated = xSpeed * sinA + ySpeed * cosA;

        xSpeed = xSpeed_rotated;
        ySpeed = ySpeed_rotated;
    }

    // Calculate motor speeds
    double frontLeftSpeed = xSpeed + ySpeed + zRotation;
    double frontRightSpeed = -xSpeed + ySpeed - zRotation;
    double backLeftSpeed = -xSpeed + ySpeed + zRotation;
    double backRightSpeed = xSpeed + ySpeed - zRotation;

    // Normalize speeds if necessary
    double maxSpeed = std::max({std::abs(frontLeftSpeed), std::abs(frontRightSpeed), std::abs(backLeftSpeed), std::abs(backRightSpeed)});
    if (maxSpeed > 1.0) {
        frontLeftSpeed /= maxSpeed;
        frontRightSpeed /= maxSpeed;
        backLeftSpeed /= maxSpeed;
        backRightSpeed /= maxSpeed;
    }
    
    // Set motor speeds
    (*m_drive).LEFT_FRONT_DRIVE_MOTOR->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, frontLeftSpeed);//frontLeftSpeed
    (*m_drive).RIGHT_FRONT_DRIVE_MOTOR->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, frontRightSpeed); //frontRightSpeed
    (*m_drive).LEFT_BACK_DRIVE_MOTOR->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, backLeftSpeed); //backLeftSpeed
    (*m_drive).RIGHT_BACK_DRIVE_MOTOR->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, backRightSpeed); //backRightSpeed
}
