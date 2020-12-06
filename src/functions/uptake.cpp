#include "main.h"
#include "define.hpp"
#include "functions/uptake.hpp"
#include "functions/math.hpp"

Uptake::Uptake(){}
Uptake::~Uptake(){}

Uptake uptake; // Class definition
static Math math;

/**
 * Stops the uptakes
 */
Uptake& Uptake::stop() {
  LU.move_velocity(0);
  RU.move_velocity(0);
  return *this;
}

/**
 * Sets the brake mode of the uptakes to brake
 */
void Uptake::brake() {
  LU.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RU.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

/**
 * Sets the speed of the uptakes
 * @param velocity -100 to 100 (In percentage of max uptakes speed)
 */
void Uptake::move(float velocity) {
  LU.move_velocity(math.percentToVelocity(velocity, 'B'));
  RU.move_velocity(math.percentToVelocity(velocity, 'B'));
}

/**
 * Waits untill a ball is indexed
 * Accurately index a ball
 * @param amount (Number of balls to index 1 or 2)
 * @param timeOut (In seconds)
 */
void Uptake::waitUntillIndexed(int amount, float timeOut) {
  // int bottomLineThresh = 2900;
  // int middleLineThresh = 2800;
  // timeOut = math.secToMillis(timeOut) + millis();
  //
  // for (int lp = 0; lp <= amount; lp++) {
  //
  // uptake.stop();
}


/**
 * Waits untill ball/s are shot into the goal
 * Accurately shoot a desired number of ball/s
 * @param amount (Number of balls to shoot)
 * @param timeOut (In seconds)
 */
 void Uptake::waitUntillShot(int amount, float timeOut) {
  int lineThresh = 2900;
  timeOut = math.secToMillis(timeOut) + millis();
  for (int lp = 0; lp <= amount; lp++) {
    uptake.move(100); // Start Uptakes
    while (1) {
      if (Top_Uptake_Line.get_value() <= lineThresh) {
        break;
      } else if (millis() >= timeOut) {
        lp = amount;
        break;
      }
      delay(10); // Loop speed, prevent overload
    }
    if (amount > 1) { // If multiple balls are queued wait untill previous ball is shot to get next sensor reading
      uptake.move(70); // Slow down uptakes
      float timeOut2 = math.secToMillis(0.3) + millis();
      while (1) {
        if (Top_Uptake_Line.get_value() >= lineThresh) {
          break;
        } else if (millis() >= timeOut2) {
          break;
        }
        delay(10); // Loop speed, prevent overload
      }
    }
  }
  uptake.stop(); // Stop uptakes
}
