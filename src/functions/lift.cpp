#include "main.h"
#include "define.hpp"
<<<<<<< Updated upstream
#include "functions/lift.hpp"

bool Lift::isRunning = false,
     Lift::isSettled = true;

int Lift::topLimit = 1200,
Lift::bottomLimit = 500,
Lift::bothIntakesLimit = 800,
Lift::hold = 1000;

int Lift::velocity,
    Lift::target,
    Lift::timeOut;

Lift lift;

Lift::Lift(){}
Lift::~Lift(){}

void Lift::startTask(void* param){
  delay(200);
  isRunning = true;
  cout<<"Lift task started"<<endl;
  while(isRunning){
    Arm.move_velocity(velocity);
    if (!isSettled){
      if (millis() >= timeOut){ // Time out stopping
        lift.reset();
      }
      else if (velocity > 0 && lift.getPot() >= target){ // Lift up stopping
        lift.reset();
      }
      else if (velocity < 0 && lift.getPot() <= target){ // Lift down stopping
        lift.reset();
      }
    }
    delay(10);
  }
}

void Lift::endTask(){
  isRunning = false;
  reset();
  cout<<"Lift task ended"<<endl;
}

Lift& Lift::move(int velocity_, int target_, int timeOut_){
  if (isRunning){
    velocity = velocity_;
    target = target_;
    timeOut = timeOut_ + millis();
    isSettled = false;
    cout<<"Lift Velocity: "<<velocity<<" Lift Target: "<<target<<" Lift Timeout: "<<timeOut<<endl;
  }
  return *this;
}

Lift& Lift::setVelocity(int velocity_){
  if (isRunning){
    velocity = velocity_;
  }
  else {
    Arm.move_velocity(velocity_);
  }
  return *this;
}

Lift& Lift::setTarget(int target_){
  target = target_;
  return *this;
}

Lift& Lift::setTimeOut(int timeOut_){
  timeOut = timeOut_;
  return *this;
}

int Lift::getVelocity(){
  return velocity;
}

int Lift::getTarget(){
  return target;
}

int Lift::getTimeOut(){
  return timeOut;
}

void Lift::reset(){
  isSettled = true;
  velocity = target = timeOut = 0;
  setBrakeMode();
  cout<<"Lift: Velocity: "<<velocity<<" Lift Target: "<<target<< " Lift Timeout: "<<timeOut<<endl;
}

void Lift::waitUntilTime(int time_){
  int time = millis() + time_;
  while(time >= millis())delay(10);
}

void Lift::waitUntilTarget(int target_){
  if(velocity > 0 && lift.getPot() < target){
    while(target_ >= lift.getPot())delay(10);
  }
  else if(velocity < 0 && lift.getPot() > target){
    while(target_ <= lift.getPot())delay(10);
  }
}

void Lift::waitUntilSettled(){
  while(!isSettled)delay(10);
}

Lift& Lift::stop(){
  Arm.move_velocity(0);
  return *this;
}

int Lift::getPot(){
  return ArmPot.get_value();
}

void Lift::setBrakeMode(){
  if (getPot() > hold && Arm.get_brake_mode() == 1){
    Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
  }
  else {
    Arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
  }
}
=======
// #include "functions/lift.hpp"
//
// bool Lift::isRunning = false,
//      Lift::isSettled = true;
//
// int Lift::topLimit = 1200,
// Lift::bottomLimit = 500,
// Lift::bothIntakesLimit = 800,
// Lift::hold = 1000;
//
// int Lift::velocity,
//     Lift::target,
//     Lift::timeOut;
//
// Lift lift;
//
// Lift::Lift() {}
// Lift::~Lift() {}
//
// void Lift::startTask(void* param){
//   delay(200);
//   isRunning = true;
//   cout<<"Lift task started"<<endl;
//   while(isRunning){
//     lift.move(velocity);
//     if (!isSettled){
//       if (millis() >= timeOut){ // Time out stopping
//         lift.reset();
//       }
//       else if (velocity > 0 && lift.getPot() > target){ // Lift up stopping
//         lift.reset();
//       }
//       else if (velocity < 0 && lift.getPot() < target){ // Lift down stopping
//         lift.reset();
//       }
//     }
//     delay(10);
//   }
// }
//
// void Lift::endTask(){
//   isRunning = false;
//   reset();
//   cout<<"Lift task ended"<<endl;
// }
//
// Lift& Lift::move(int velocity_, int target_, int timeOut_){
//   if (isRunning){
//     velocity = velocity_;
//     target = target_;
//     timeOut = timeOut_ + millis();
//     isSettled = false;
//     cout<<"Lift Velocity: "<<velocity<<" Lift Target: "<<target<<" Lift Timeout: "<<timeOut<<endl;
//   }
//   return *this;
// }
//
// void Lift::reset(){
//   isSettled = true;
//   velocity = target = timeOut = 0;
//   setBrakeMode();
//   cout<<"Lift Velocity: "<<velocity<<" Lift Target: "<<target<< " Lift Timeout: "<<timeOut<<endl;
// }
//
// void Lift::waitUntilSettled(){
//   while(!isSettled)delay(10);
// }
//
// Lift& Lift::stop(){
//   move(0);
//   return *this;
// }
// 
// void Lift::setBrakeMode() {
//   if (getPot() > hold && Arm.get_brake_mode() == 1){
//     Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
//   }
//   else {
//     Arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
//   }
// }
//
// int Lift::getPot(){
//   return ArmPot.get_value();
// }
//
// void Lift::move(int velocity){
//   Arm.move_velocity(velocity);
// }
>>>>>>> Stashed changes
