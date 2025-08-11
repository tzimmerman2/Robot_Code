// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.


#include <commands/Drive.h>


Drive::Drive(DriveContinuous *subsystem, inputDevice *joystick, studica::AHRS *gyro, frc::SendableChooser<double> *robotSpeed) : m_drive{subsystem}, joystick{joystick}, m_gyro{gyro}, m_robotSpeed{robotSpeed}, x{0}, y{0}, z{0}
 {
    
    //driveSpeed = new frc::SendableChooser<double>;
    //double speed = driveSpeed->GetSelected();
    AddRequirements(m_drive);

 
 }
void Drive::Execute() {

    
    double speed = frc::SmartDashboard::GetNumber("Robot Speed", 0.5);
    
    double y = -(joystick->GetX() * speed);
    double x = (joystick->GetY() * speed);
    double z = (joystick->GetZ() * speed);

    // Get the current yaw angle in degrees
    double yaw_angle = m_gyro->GetYaw();
    // Convert yaw angle to radians
    double gyro_radians = (yaw_angle * 3.14159265358979323846) / 180.0;
    
// REMBER TO FACTORY CALABRATE NAVX
// ALSO TO REFLASH IT WIHT THE NAVx APP

    // Log information to SmartDashboard
    frc::SmartDashboard::PutNumber("raw_raw_gyro_z", m_gyro->GetWorldLinearAccelZ());
    frc::SmartDashboard::PutNumber("navx_raw", yaw_angle);
    frc::SmartDashboard::PutNumber("navx1", gyro_radians);
    frc::SmartDashboard::PutNumber("x", x);
    frc::SmartDashboard::PutNumber("y", y);
    frc::SmartDashboard::PutNumber("X", x);
    frc::SmartDashboard::PutNumber("Y", y);

    // Use the new DriveCartesian function 
    DriveContinuous::DriveCartesian(x, y, z, m_drive, gyro_radians);
    
















/*   
    x = joystick->GetX() * speed;
    y = joystick->GetY() * speed;
    z = joystick->GetZ() * speed;

    
    // Get the current yaw angle in radians
    //double gyro_radians = (m_gyro->GetYaw() * (M_PI / 180.0));
    //chatgpt
    
    
    double gyro_radians = std::fmod((m_gyro->GetYaw() * M_PI / 180.0), 2 * M_PI);
    if (gyro_radians < 0) {
        gyro_radians += 2 * M_PI;
    }
    
    
    // Convert joystick input to field-centric coordinates
    
    //double tempX = x * std::cos(gyro_radians) - y * std::sin(gyro_radians);
    //double tempY = x * std::sin(gyro_radians) + y * std::cos(gyro_radians);
    

    
    //chatgpt try if not work
    double tempX = x * std::cos(gyro_radians) + y * std::sin(gyro_radians); // Invert the Y term
    double tempY = -x * std::sin(gyro_radians) + y * std::cos(gyro_radians); // Invert the X term
    
    
    double angle = std::atan2(tempY,tempX);
    double magnitude = std::hypot(tempX,tempY);
    double twist = z;
     
    
    frc::SmartDashboard::PutNumber("navx1", gyro_radians);
    frc::SmartDashboard::PutNumber("x", x);
    frc::SmartDashboard::PutNumber("y", y);
    frc::SmartDashboard::PutNumber("X", tempX);
    frc::SmartDashboard::PutNumber("Y", tempY);


    
    DriveContinuous::setMecanumDrive(angle, magnitude, twist, m_drive);
    */
}



bool Drive::IsFinished(){
    return false;
}

