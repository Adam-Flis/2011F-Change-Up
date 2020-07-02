#include "main.h"
#include "define.hpp"
#include "functions/lift.hpp"

int Lift::top = 1200,
Lift::bottom = 500,
Lift::bothIntakes = 800,
Lift::hold = 1000;

int Lift::target, Lift::velocity;
float Lift::timeOut;

bool Lift::isRunning = false,
Lift::isSettled = true;

Lift::Lift() { }

Lift::~Lift() { }

Lift& Lift::stop() {
  Arm.move_velocity(0);
  return *this;
}

void Lift::setBrakeMode() {
  if (getPot() > hold && Arm.get_brake_mode() == 1){
    Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
  }
  else {
    Arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
  }
}

int Lift::getPot(){
  return ArmPot.get_value();
}

void Lift::move(int velocity) {
  Arm.move_velocity(velocity);
}

Lift& Lift::move(int target_, int velocity_, float timeOut_) {
  target = target_;
  velocity = velocity_;
  timeOut = timeOut_;
  stop();
  isSettled = false;
  return *this;
}

void Lift::start(void *ignore) {
  if(!isRunning) {
    delay(500);
    Lift *that = static_cast<Lift*>(ignore);
    that -> run();
  }
}

void Lift::run() {
  isRunning = true;
  while(isRunning) {
    if (target == getPot()+5 || target == getPot()-5 || timeOut == millis()+timeOut){
      isSettled = true;
      break;
    }
    move(velocity);
    delay(10);
  }
  setBrakeMode();
}

void Lift::waitUntillSettled() {
  while(!isSettled) delay(20);
}
