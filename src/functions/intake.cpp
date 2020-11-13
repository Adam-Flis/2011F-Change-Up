#include "main.h"
#include "define.hpp"
#include "functions/intake.hpp"
#include "functions/math.hpp"

Intake::Intake(){}
Intake::~Intake(){}

static Math math;

void Intake::move(float velocity) {
  LI.move_velocity(math.percentToVelocity(velocity, 'B'));
  RI.move_velocity(math.percentToVelocity(velocity, 'B'));
}

Intake& Intake::stop() {
  LI.move_velocity(0);
  RI.move_velocity(0);
  return *this;
}

void Intake::brake() {
  LI.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RI.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

void Intake::waitUntillColor(char color, float timeOut) {
  timeOut = math.secToMillis(timeOut) + millis();
  int low_hue;
  int high_hue;
  if (color == 'B') {
    low_hue = 50;
    high_hue = 84;
  } else if (color == 'R') {
    low_hue = 50;
    high_hue = 84;
  } else {
    timeOut = millis();
  }
  while (1) {
    if (low_hue <= Intake_Optical.get_hue() <= high_hue) {
      break;
    } else if (millis() >= timeOut) {
      break;
    }
    delay(10);
  }
}
