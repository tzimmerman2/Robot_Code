// Thank you Chat Gpt

#include "Classes/InputDevice.h"


inputDevice::inputDevice(double deadzone): deadZone{deadzone}{

    if (!(frc::DriverStation::IsJoystickConnected(0))){
       frc::SmartDashboard::PutString("Controller Status", "No input device. Input device may not be recognized until the robot is re-enabled");
    }
    //frc::SmartDashboard::PutData("Input Device", &inputDeviceChooser);
    UpdateDevice();
}

void inputDevice::UpdateDevice(){
    if (frc::DriverStation::IsJoystickConnected(0)){
        if (frc::DriverStation::GetJoystickIsXbox(0)){
            activeDevice = std::make_unique<frc::XboxController>(0);
            inputName = 0;
            frc::SmartDashboard::PutString("Controller Status", "Xbox Controller connected");
        }
        else if (frc::DriverStation::GetJoystickType(0) == 20){
            activeDevice = std::make_unique<frc::Joystick>(0);
            inputName = 1;
            frc::SmartDashboard::PutString("Controller Status", "Joystick connected");
        }
        else if (frc::DriverStation::GetJoystickType(0) == 21){
            activeDevice = std::make_unique<frc::Joystick>(0);
            inputName = 2;
            frc::SmartDashboard::PutString("Controller Status", "Gamepad connected - switch pro controller");
        }
        else {
            frc::SmartDashboard::PutString("Controller Status", "No supported input device. Plug in a supported device");
            activeDevice = std::make_unique<frc::XboxController>(0);
            inputName = 0;
        } 
        frc::DriverStation::SilenceJoystickConnectionWarning(true);
    }
}

void inputDevice::updateDeadZone(double deadzone, inputDevice *joystick){
    if (deadzone<1 && deadzone>=0){
        joystick->deadZone = deadzone;
    }
}

bool inputDevice::buttonExist(int button) const{
    if (frc::DriverStation::GetStickButtonCount(0) < button || 0 > button){ // checks if button exists
        return false;
    }
    return true;
}

bool inputDevice::axisExist(int axis) const{
    if (frc::DriverStation::GetStickAxisCount(0) < axis || 0 > axis){ // checks if axis exists
        return false;
    }
    return true;
}

double inputDevice::deadzone(double input) const{
    if (inputName == gamepad){
        input = input * 1.33333;
    }

    if (input > 1) {
        return 1;
    } 
    else if (input < -1) {
        return -1;
    } 
    else if (std::abs(input) > deadZone) {
        return input;
    } 
    else {
        return 0;
    }
}

double inputDevice::GetX() const{
    if(activeDevice->IsConnected() && axisExist(0)){
        return deadzone(activeDevice->GetRawAxis(0));
        
    }
    return 0.0;
}

double inputDevice::GetY() const{
    if(activeDevice->IsConnected() && axisExist(1)){
        return deadzone(activeDevice->GetRawAxis(1));
    }
    return 0.0;
}

double inputDevice::GetZ() const{
    int axis{-1};
    if(activeDevice->IsConnected()){
        if (inputName == controller) {
            axis=controllerZ;
        }else if(inputName == joystick){
            axis=joystickZ;
        }else if (inputName == gamepad){
            axis=gamepadZ;
        }
        if (axisExist(axis)){
            return deadzone(activeDevice->GetRawAxis(axis));
        } else {
            frc::SmartDashboard::PutString("WARNING AXIS", "WARNING: Axis " + std::to_string(axis) + " does not exist on this controller");
        }
    }
    return 0.0;
}

bool inputDevice::ActiveDeviceHasSpeedAxis(){
    std::string a ="";
    for(int i{0}; i <= activeDevice->GetAxisCount(); i++){
        a+=", axis ";
        a+=i;
        a+=" ";
        a+=activeDevice->GetAxisType(i);
    }
    frc::SmartDashboard::PutString("axis type", a);
    return false;
    
}

bool inputDevice::GetRawButton(int button) const{
    if(activeDevice->IsConnected() && buttonExist(button)){
        return activeDevice->GetRawButton(button);
    }
    else {
        frc::SmartDashboard::PutString(("WARNING BUTTON " + std::to_string(button)), "WARNING: Button " + std::to_string(button) + " does not exist on this controller");
    }
    return false;
}

bool inputDevice::GetRawButtonPressed(int button) const{
    if(activeDevice->IsConnected() && buttonExist(button)){
        return activeDevice->GetRawButtonPressed(button);
    }
    else {
        frc::SmartDashboard::PutString(("WARNING BUTTON " + std::to_string(button)), "WARNING: Button " + std::to_string(button) + " does not exist on this controller");
    }
    return false;
}

bool inputDevice::GetRawButtonReleased(int button) const{
    if(activeDevice->IsConnected() && buttonExist(button)){
        return activeDevice->GetRawButtonReleased(button);
    }
    else {
        frc::SmartDashboard::PutString(("WARNING BUTTON " + std::to_string(button)), "WARNING: Button " + std::to_string(button) + " does not exist on this controller");
    }
    return false;
}

frc::BooleanEvent inputDevice::Button(int button, frc::EventLoop* loop) const {
    if(activeDevice->IsConnected() && buttonExist(button)){
        return activeDevice->Button(button, loop);
    }
    
    frc::SmartDashboard::PutString(("WARNING BUTTON " + std::to_string(button)), "WARNING: Button " + std::to_string(button) + " does not exist on this controller");
    return activeDevice->Button(button, loop); //this will call an error and return false
}

int inputDevice::GetButtonCount() const{
    if(activeDevice->IsConnected()){
        return activeDevice->GetButtonCount();
    }
    return 0;
}

double inputDevice::GetRawAxis(int axis) const{
    if(activeDevice->IsConnected()&& axisExist(axis)){
        return deadzone(activeDevice->GetRawAxis(axis));
    }
    frc::SmartDashboard::PutString("WARNING AXIS", "WARNING: Axis " + std::to_string(axis) + " does not exist on this controller");
    return 0.0;
}

int inputDevice::GetAxisType(int axis) const{
    if(activeDevice->IsConnected() && axisExist(axis)){
        return activeDevice->GetAxisType(axis);
    }
    frc::SmartDashboard::PutString(("axis " + std::to_string(axis)) + " warning", "WARNING: Axis " + std::to_string(axis) + " does not exist on this controller");
    return 0.0;
}

int inputDevice::GetAxisCount() const{
    if(activeDevice->IsConnected()){
        return activeDevice->GetAxisCount();
    }
    return 0;
}

frc::BooleanEvent inputDevice::AxisLessThan(int axis, double threshold,frc::EventLoop* loop) const{
    if(activeDevice->IsConnected() && axisExist(axis)){
        return activeDevice->AxisLessThan(axis, threshold,loop);
    }
    frc::SmartDashboard::PutString(("axis " + std::to_string(axis)) + " warning", "WARNING: Axis " + std::to_string(axis) + " does not exist on this controller");
    return activeDevice->AxisLessThan(axis, threshold,loop); //this will call an error and return false
}

frc::BooleanEvent inputDevice::AxisGreaterThan(int axis, double threshold,frc::EventLoop* loop) const{
    if(activeDevice->IsConnected() && axisExist(axis)){
        return activeDevice->AxisGreaterThan(axis, threshold,loop);
    }
    frc::SmartDashboard::PutString(("axis " + std::to_string(axis)) + " warning", "WARNING: Axis " + std::to_string(axis) + " does not exist on this controller");
    return activeDevice->AxisGreaterThan(axis, threshold,loop); //this will call an error and return false
}

int inputDevice::GetPOVCount() const{
    if(activeDevice->IsConnected()){
        return activeDevice->GetPOVCount();
    }
    return 0;
}

int inputDevice::GetPOV(int pov) const{
    if(activeDevice->IsConnected()){
        return activeDevice->GetPOV();
    }
    return 0;
}

frc::BooleanEvent inputDevice::POV(int pov, int angle, frc::EventLoop* loop) const{
    if(activeDevice->IsConnected()){
        return activeDevice->POV(pov,angle,loop);
    }
    return activeDevice->POV(pov,angle,loop); //calls an error and may cause program to crash
}


frc::BooleanEvent inputDevice::POV(int angle, frc::EventLoop *loop) const{
    if(activeDevice->IsConnected()){
        return activeDevice->POV(angle,loop);
    }
    return activeDevice->POV(angle,loop); //calls an error and may cause program to crash
}

frc::BooleanEvent inputDevice::POVUp(frc::EventLoop *loop) const{
    if(activeDevice->IsConnected()){
        return activeDevice->POVUp(loop);
    }
    return activeDevice->POVUp(loop); //calls an error and may cause program to crash
}

frc::BooleanEvent inputDevice::POVUpRight(frc::EventLoop *loop) const{
    if(activeDevice->IsConnected()){
        return activeDevice->POVUpRight(loop);
    }
    return activeDevice->POVUpRight(loop); //calls an error and may cause program to crash
}

frc::BooleanEvent inputDevice::POVRight(frc::EventLoop *loop) const{
    if(activeDevice->IsConnected()){
        return activeDevice->POVRight(loop);
    }
    return activeDevice->POVRight(loop); //calls an error and may cause program to crash
}

frc::BooleanEvent inputDevice::POVDownRight(frc::EventLoop *loop) const{
    if(activeDevice->IsConnected()){
        return activeDevice->POVDownRight(loop);
    }
    return activeDevice->POVDownRight(loop); //calls an error and may cause program to crash
}

frc::BooleanEvent inputDevice::POVDown(frc::EventLoop *loop) const{
    if(activeDevice->IsConnected()){
        return activeDevice->POVDown(loop);
    }
    return activeDevice->POVDown(loop); //calls an error and may cause program to crash
}

frc::BooleanEvent inputDevice::POVDownLeft(frc::EventLoop *loop) const{
    if(activeDevice->IsConnected()){
        return activeDevice->POVDownLeft(loop);
    }
    return activeDevice->POVDownLeft(loop); //calls an error and may cause program to crash
}

frc::BooleanEvent inputDevice::POVLeft(frc::EventLoop *loop) const{
    if(activeDevice->IsConnected()){
        return activeDevice->POVLeft(loop);
    }
    return activeDevice->POVLeft(loop); //calls an error and may cause program to crash
}

frc::BooleanEvent inputDevice::POVUpLeft(frc::EventLoop *loop) const{
    if(activeDevice->IsConnected()){
        return activeDevice->POVUpLeft(loop);
    }
    return activeDevice->POVUpLeft(loop); //calls an error and may cause program to crash
}

frc::BooleanEvent inputDevice::POVCenter(frc::EventLoop *loop) const{
    if(activeDevice->IsConnected()){
        return activeDevice->POVCenter(loop);
    }
    return activeDevice->POVCenter(loop); //calls an error and may cause program to crash
}

bool inputDevice::IsConnected() const{
    return activeDevice->IsConnected();
}

frc::GenericHID::HIDType inputDevice::GetType() const{
    if(activeDevice->IsConnected()){
        return activeDevice->GetType();
    }
    return activeDevice->GetType(); //should call an error and may cause program to crash
}

std::string inputDevice::GetName() const{
    if(activeDevice->IsConnected()){
        return activeDevice->GetName();
    }
    return "NULL_not_conneted";
}

int inputDevice::GetPort() const{
    if(activeDevice->IsConnected()){
        return activeDevice->GetPort();
    }
    return -1;
}

void inputDevice::SetOutput(int outputNumber, bool value){
    if(activeDevice->IsConnected()){
        activeDevice->SetOutput(outputNumber, value);
    }
}

void inputDevice::SetOutputs(int value){
    if(activeDevice->IsConnected()){
        activeDevice->SetOutputs(value);
    }
}

void inputDevice::SetRumble(frc::GenericHID::RumbleType type, double value){
    if(activeDevice->IsConnected()){
        activeDevice->SetRumble(type, value); 
    }
}
