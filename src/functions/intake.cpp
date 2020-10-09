#include "main.h"
#include "define.hpp"
#include "functions/intake.hpp"

Intake intake;
Intake::Intake(){}
Intake::~Intake(){}

void Intake::move(int velocity){
  LI.move_velocity(velocity);
  RI.move_velocity(velocity);
}

Intake& Intake::stop(){
  LI.move_velocity(0);
  RI.move_velocity(0);
  return *this;
}

void Intake::brake(){
  LI.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RI.set_brake_mode(MOTOR_BRAKE_BRAKE);
}
