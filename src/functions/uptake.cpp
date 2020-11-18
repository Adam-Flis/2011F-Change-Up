#include "main.h"
#include "define.hpp"
#include "functions/uptake.hpp"
#include "functions/math.hpp"

Uptake::Uptake(){}
Uptake::~Uptake(){}

static Math math;

void Uptake::move(float velocity) {
  BU.move_velocity(math.percentToVelocity(velocity, 'B'));
  TU.move_velocity(math.percentToVelocity(velocity, 'B'));
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

void Uptake::waitUntillIndexed(float timeOut) {
  int ballPassed = 2920;
  timeOut = math.secToMillis(timeOut) + millis();
  while (1) {
    if (Bottom_Uptake_Line.get_value() < ballPassed) {
      break;
    } else if (millis() >= timeOut) {
      break;
    }
    delay(10);
  }
}

void Uptake::waitUntillShot(int amount, float timeOut) {
  int ballPassed = 2900;
  timeOut = math.secToMillis(timeOut) + millis();
  for (int lp = 0; lp <= amount; lp++) {
    while (1) {
      if (Top_Uptake_Line.get_value() < ballPassed) {
        break;
      } else if (millis() >= timeOut) {
        lp = amount;
        break;
      }
      delay(10);
    }
    delay(125);
  }
}
