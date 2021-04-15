#include "main.h"
#include "define.hpp"
#include "functions/math.hpp"

// Define variables
double Math::intergral;
double wheelDiameter = 2.75; //In inches
double wheelCircumference = wheelDiameter * M_PI;
double ticksPerRevolution = 360; //Number of ticks in one full revolution of encoder/motor
double driven = 1;
double driver = 1;

/**
 * Converts ticks to inches, then returns
 * @param ticks
 */
double Math::ticksToInch(double ticks) {
  double wheelRevolutions = ticks / ticksPerRevolution * driven / driver;
  double inches = wheelRevolutions * wheelCircumference;
  return inches;
}

/**
 * Converts inches to ticks, then returns
 * @param inches
 */
double Math::inchToTicks(double inches) {
  double motorRevolutions = inches / wheelCircumference * driver / driven;
  double ticks = motorRevolutions * ticksPerRevolution;
  return ticks;
}

/**
 * Filters variable values
 * @param current (Current variable value)
 * @param last (Last variable value)
 */
double Math::filter(double current, double last) {
  double filteredVal = current - last;
  if (fabs(filteredVal) < 0.01) {
    filteredVal = 0;
  }
  return filteredVal;
}

/**
 * Converts percent value to velocity value, then returns
 * @param percent -100 to 100 (In percentage of max speed)
 * @param cartColor 'R', 'G', 'B' (Color cart of motor insert; Red, Green, Blue)
 */
double Math::percentToVelocity(double percent, char cartColor) {
  double multiplier;
  if (cartColor == 'R') {
    multiplier = 1;
  }
  else if (cartColor == 'G') {
    multiplier = 2;
  }
  else if (cartColor == 'B') {
    multiplier = 6;
  }
  return (percent * multiplier);
}

/**
 * Converts percent to voltage, then returns
 */
double Math::percentToVoltage(double percent) {
  return percent * 120;
}

/**
 * Returns an angle between 0 and 2pi radians
 * @param angle (In radians)
 */
double Math::angleWrap(double rad) {
  rad = fmod(rad, 2 * M_PI);
    if (rad < 0) {
        rad += 2 * M_PI;
    }
  return rad;
}

/**
 * Makes sure angle is between 0 and pi radians
 * @param angle (In radians)
 */
double Math::angleIn180(double rad) {
  rad = angleWrap(rad);
  if (rad >= M_PI) {
    rad -= (2 * M_PI);
  }
  return rad;
}

/**
 * Converts degress to radians, then returns
 * @param angle (In degress)
 */
double Math::degToRad(double deg) {
  return deg * M_PI / 180.0;
}

/**
 * Converts radians to degress, then returns
 * @param angle (In radians)
 */
double Math::radToDeg(double rad) {
  return rad / M_PI * 180.0;
}

/**
 * Converts seconds to milliseconds, then returns
 * @param seconds (In seconds)
 */
double Math::secToMillis(double seconds) {
  return seconds * 1000;
}

/**
 * Accelerate the drivetrain based on difference between velocity and last velocity
 * @param velocity
 * @param lastVelocity
 */
double Math::slew(double velocity, double lastVelocity) {
  double vOut;
  double vDeriv = velocity - lastVelocity;
  if (fabs(vDeriv) > 13.5) {
    vOut = lastVelocity + 13.5;
  } else {
    vOut = velocity;
  }
  return vOut;
}

/**
 * Calulates velocity based on distance away from target, the returns
 * @param error (Distance from target)
 * @param lastError (Last distance from target)
 * @param kP (Proportion constant)
 * @param kI (Intergral constant)
 * @param kD (Derivative constant)
 * @param intergralActive (Zone intergral is utalized)
 * @param movement "Drive" or "Turn" (Drive for linear movements or turn for turns)
 */
double Math::pid(double error, double lastError, double kP, double kI,
                 double kD, double intergralActive, string movement) {

  // Define variables
  double velocity, proportion, derivative, intergralLimit;

  // Determine intergralLimit based on type of movement
  if (movement == "Drive") {
    intergralLimit = 1000;
  } else if (movement == "Turn") {
    intergralLimit = 600;
  }

  // Set proportion to distance from target or error
  proportion = error;

  // Intergral takes area under the error and is useful for major adjustment
  if (fabs(error) < intergralActive && error != 0) {
      intergral = intergral + error;
    } else {
      intergral = 0;
    }

    //Set intergral output to limit
    if (intergral > intergralLimit) {
      intergral = intergralLimit;
    } else if (intergral < intergralLimit) {
      intergral = -intergralLimit;
    }

    // Derivative finds difference between current error and last recrded to recieve ROC, good for fine adjustment
    if (movement == "Turn") {
      if (lastError != 0 || error != 0) {
        derivative = proportion - lastError;
      } else { // Sets var equal to zero if no adjustment is needed
        derivative = 0;
      }
    } else if (movement == "Drive") {
      if (lastError != 0) {
        derivative = proportion - lastError;
      } else { // Sets var equal to zero if no adjustment is needed
        derivative = 0;
      }
    }

    // Returns velocity of drive after it applies the PID constant
    return velocity = kP * proportion + kI * intergral + kD * derivative;
  }
