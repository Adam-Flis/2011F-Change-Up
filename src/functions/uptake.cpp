#include "main.h"
#include "define.hpp"
#include "functions/uptake.hpp"
#include "functions/math.hpp"

Uptake::Uptake(){}
Uptake::~Uptake(){}

static Math math; // Class definition

/**
 * Stops the uptakes
 */
Uptake& Uptake::stop() {
  BU.move_velocity(0);
  TU.move_velocity(0);
  return *this;
}

/**
 * Sets the brake mode of the uptakes to brake
 */
void Uptake::brake() {
  BU.set_brake_mode(MOTOR_BRAKE_BRAKE);
  TU.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

/**
 * Sets the speed of the uptakes
 * @param velocity -100 to 100 (In percentage of max uptakes speed)
 */
void Uptake::move(float velocity) {
  BU.move_velocity(math.percentToVelocity(velocity, 'B'));
  TU.move_velocity(math.percentToVelocity(velocity, 'B'));
}

/**
 * Waits untill a ball is indexed
 * Accurately index a ball
 * @param timeOut (In seconds)
 */
void Uptake::waitUntillIndexed(float timeOut) {
  int ballPassed = 2920;
  timeOut = math.secToMillis(timeOut) + millis();
  while (1) {
    if (Bottom_Uptake_Line.get_value() < ballPassed) {
      break;
    } else if (millis() >= timeOut) {
      break;
    }
    delay(10); // Loop speed, prevent overload
  }
}

/**
 * Waits untill ball/s are shot into the goal
 * Accurately shoot a desired number of ball/s
 * @param amount (Number of balls to shoot)
 * @param timeOut (In seconds)
 */
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
      delay(10); // Loop speed, prevent overload
    }
    if (amount > 1) {
      delay(125); // Delay before going onto next for loop if there are multiple balls queued
    }
  }
}
