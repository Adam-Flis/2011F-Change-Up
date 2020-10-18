#include "main.h"
#include "define.hpp"
#include "functions/uptake.hpp"

Uptake::Uptake(){}
Uptake::~Uptake(){}

void Uptake::move(int velocity) {
  BU.move_velocity(velocity);
  TU.move_velocity(velocity);
}

Uptake& Uptake::stop() {
  BU.move_velocity(0);
  TU.move_velocity(0);
  return *this;
}

void Uptake::brake() {
  BU.set_brake_mode(MOTOR_BRAKE_BRAKE);
  TU.set_brake_mode(MOTOR_BRAKE_BRAKE);
}
