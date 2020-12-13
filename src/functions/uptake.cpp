#include "main.h"
#include "define.hpp"
#include "functions/uptake.hpp"
#include "functions/math.hpp"

Uptake::Uptake(){}
Uptake::~Uptake(){}

Uptake uptake; // Class definition
static Math math;

int bottomLineThresh = 2915;
int middleLineThresh = 2925;

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
 * Waits untill a ball is indexed to the bottom roller
 * Accurately index a ball to bottom roller
 * @param timeOut (In seconds)
 */
void Uptake::waitUntillIndexedBottom(float timeOut) {
  timeOut = math.secToMillis(timeOut) + millis();
  uptake.move(40); // Start Uptakes
  while (1) {
    if (Bottom_Uptake_Line.get_value() <= bottomLineThresh) {
      break;
    } else if (Middle_Uptake_Line.get_value() <= middleLineThresh) {
      break;
    } else if (millis() >= timeOut) {
      break;
    }
    delay(10); // Loop speed, prevent overload
  }
  uptake.stop(); // Stop uptakes
}

/**
 * Waits untill a ball is indexed to the middle roller
 * Accurately index a ball to middle roller
 * @param timeOut (In seconds)
 */
void Uptake::waitUntillIndexedMiddle(float timeOut) {
  timeOut = math.secToMillis(timeOut) + millis();
  uptake.move(40); // Start uptakes
  while (1) {
    if (Middle_Uptake_Line.get_value() <= middleLineThresh) {
      break;
    } else if (millis() >= timeOut) {
      break;
    }
    delay(10); // Loop speed, prevent overload
  }
  uptake.stop(); // Stop uptakes
}

/**
 * Waits untill ball/s are shot into the goal
 * Accurately shoot a desired number of ball/s
 * @param amount (Number of balls to shoot)
 * @param timeOut (In seconds)
 */
 void Uptake::waitUntillShot(int amount, float timeOut) {
  int lineThresh = 2905;
  timeOut = math.secToMillis(timeOut) + millis();
  for (int lp = 0; lp <= amount; lp++) {
    uptake.move(100); // Start uptakes
    while (1) {
      if (Top_Uptake_Line.get_value() <= lineThresh) {
        break;
      } else if (millis() >= timeOut) {
        lp = amount;
        break;
      }
      delay(10); // Loop speed, prevent overload
    }
    if (amount > 1 && amount != lp) { // If multiple balls are queued wait untill previous ball is shot to get next sensor reading
      uptake.move(0); // Slow down uptakes
      float timeOut2 = math.secToMillis(0.5) + millis();
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
