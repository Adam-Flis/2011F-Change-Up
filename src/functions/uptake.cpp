#include "main.h"
#include "define.hpp"
#include "functions/uptake.hpp"
#include "functions/math.hpp"

Uptake::Uptake(){}
Uptake::~Uptake(){}

Uptake uptake; // Class definition
static Math math;

int bottomThresh = 2918;
int middleThresh = 2933;
int topThresh = 2907;

int distanceThresh = 230;

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
 * Waits until a ball is indexed to the bottom roller
 * Accurately index a ball to bottom roller
 * @param timeOut (In seconds)
 */
void Uptake::waitUntilIndexedBottom(float timeOut) {
  timeOut = math.secToMillis(timeOut) + millis();
  //uptake.move(100); // Start Uptakes
  while (1) {
    if (Bottom_Line.get_value() <= bottomThresh) {
      break;
    } else if (Middle_Line.get_value() <= middleThresh) {
      break;
    } else if (millis() >= timeOut) {
      break;
    }
    delay(10); // Loop speed, prevent overload
  }
  uptake.stop().brake(); // Stop uptakes
}

/**
 * Waits until a ball is indexed to the middle roller
 * Accurately index a ball to middle roller
 * @param timeOut (In seconds)
 */
void Uptake::waitUntilIndexedMiddle(float timeOut) {
  timeOut = math.secToMillis(timeOut) + millis();
  uptake.move(65); // Start uptakes
  while (1) {
    if (Middle_Line.get_value() <= middleThresh) {
      break;
    } else if (millis() >= timeOut) {
      break;
    }
    delay(10); // Loop speed, prevent overload
  }
  uptake.stop().brake(); // Stop uptakes
}

/**
 * Waits until a ball is indexed to the top roller
 * Accurately index a ball to top roller
 * @param timeOut (In seconds)
 */
void Uptake::waitUntilIndexedTop(float timeOut) {
  timeOut = math.secToMillis(timeOut) + millis();
  uptake.move(50); // Start uptakes
  while (1) {
    if (Top_Line.get_value() <= topThresh) {
      break;
    } else if (millis() >= timeOut) {
      break;
    }
    delay(10); // Loop speed, prevent overload
  }
  uptake.stop().brake(); // Stop uptakes
}

/**
 * Waits until ball/s are shot into the goal
 * Accurately shoot a desired number of ball/s
 * @param amount (Number of balls to shoot)
 * @param timeOut (In seconds)
 */
 void Uptake::waitUntilShot(int amount, float timeOut) {
  timeOut = math.secToMillis(timeOut) + millis();
  int lp = 0;
  bool passed = false;
  while (lp != amount) {
    if (!passed) {
      uptake.move(100); // Start uptakes
    }
    if (Distance_Sensor.get() <= distanceThresh && !passed) {
      lp++;
      passed = true;
      if (amount > 1) { // If the amount is greater than one bring queued ball down
                        // to wait for previous ball to be fully in goal
        uptake.move(-100); // Reverse uptakes
        delay(200);
      }
    } else if (amount > 1 && passed && Distance_Sensor.get() >= distanceThresh) { // If multiple balls are queued wait until previous ball
                                                                                 // is fully inside the goal to get next sensor reading
        passed = false;
    } else if (millis() >= timeOut) {
        lp = amount;
    }
    delay(20); // Loop speed, prevent overload
  }
  uptake.stop().brake(); // Stop uptakes
}
