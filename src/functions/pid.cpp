#include "main.h"
#include "define.hpp"
#include "functions/pid.hpp"
#include "functions/math.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"

PID pid; // Class definition
static Math math;
static Chassis chassis;
static Odom odom;

/* ********** Define variables ********** */

float kP = 12.3, kI = 0.1, kD = 3.0;
float kP_t = 100, kI_t = 0.1, kD_t = 50;
float kP_d = 1800, kD_d = 900;

float intergralActive = math.inchToTicks(3);
float intergralActive_t = 3;
float intergralLimit;
float intergralLimit_t;

float lastIMURotation;

// Error var declarations
float error;
float error_drift;
float lastError;
float lastError_d;
float rotation;

// Calc var declarations
float proportion;
float proportion_drift;
float intergral;
float derivative;
float derivative_d;

// Motor output var declarations
float targetVoltage;
float voltage;

/**
 * Calculates the drive pid of the robot
 * Slows robot down as it approaches inputted target
 * Returns a voltage value
 * @param targetTicks_ (In ticks -backwards +forwards)
 * @param targetVoltage_ 0 to 12,000 (In volts)
 */
float PID::drive(float targetTicks_, float targetVoltage_) {
  intergralLimit = (targetVoltage_/kI)/50;

  // Error reestablished at the start of the loop
  error = targetTicks_ + VEnc.get_value();
  // Proportion stores the error until it can be multiplied by the constant
  proportion = error;
  // Intergral takes area under the error and is useful for major adjustment
  if (fabs(error) < intergralActive) {
    intergral = intergral + error;
  } else {
    intergral = 0;
  }
  // Set intergral output to limit
  if (intergral > intergralLimit) {
    intergral = intergralLimit;
  } else if (intergral < intergralLimit) {
    intergral = -intergralLimit;
  }

  // Derivative finds difference between current error and last recrded to recieve ROC, good for fine adjustment
  derivative = error - lastError;
  lastError = error;
  // Sets var equal to zero if no adjustment is needed
  if (error == 0) {
    derivative = 0;
  }

  // Final output of drive alg that applies constants to the PID factors
  voltage = kP * proportion + kI * intergral + kD * derivative;

  if (voltage > targetVoltage_) {
    voltage = targetVoltage_;
  } else if (voltage < -targetVoltage_) {
    voltage = -targetVoltage_;
  }
  return voltage;
}

/**
 * Calculates the drift of the robot
 * Returns a voltage value
 */
float PID::drift() {
  // Establishes the initial error simply as the value of the IMU since its supposed to be 0
  error_drift = odom.getTheta() - lastIMURotation;
  // Derivative finds difference between current error and last recrded to recieve ROC, good for fine adjustment
  derivative_d = error_drift - lastError_d;
  lastIMURotation = odom.getTheta();
  lastError_d = error_drift;

  return proportion_drift = error_drift * kP_d + derivative_d * kD_d;
}

/**
 * Calculates the turn pid of the robot
 * Slows robot down as it approaches inputted target
 * Returns a voltage value
 * @param targetTheta_ (In degress)
 * @param targetVoltage_ 0 to 12,000 (In volts)
 */
float PID::turn(float targetTheta_, float targetVoltage_) {
  intergralLimit_t = (targetVoltage_/kI_t)/50;

  // Error reestablished at the start of the loop
  error = math.angleWrap(targetTheta_ - odom.getTheta());
  // Proportion stores the error until it can be multiplied by the constant
  proportion = error;
  // Intergral takes area under the error and is useful for major adjustment
  if (fabs(error) < intergralActive_t) {
    intergral = intergral + error;
  } else {
    intergral = 0;
  }
  // Set intergral output to limit
  if (intergral > intergralLimit_t) {
    intergral = intergralLimit_t;
  } else if (intergral < intergralLimit_t) {
    intergral = -intergralLimit_t;
  }

  // Derivative finds difference between current error and last recrded to recieve ROC, good for fine adjustment
  derivative = error - lastError;
  lastError = error;
  // Sets var equal to zero if no adjustment is needed
  if (error == 0) {
    derivative = 0;
  }

  // Final output of drive alg that applies constants to the PID factors
  voltage = kP_t * proportion + kI_t * intergral + kD_t * derivative;

  if (voltage > targetVoltage_) {
    voltage = targetVoltage_;
  } else if (voltage < -targetVoltage_) {
    voltage = -targetVoltage_;
  }
  return voltage;
}
