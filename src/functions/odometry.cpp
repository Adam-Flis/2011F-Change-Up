#include "main.h"
#include "define.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"

Odom odom; // Class definition
static Math math;

/* ********** Define variables ********** */

bool Odom::isRunning = false;
float Sv = 7.5;
float Sh = 6.25;

/**
 * Resets the odometry variables
 */
void Odom::reset() {
  VEnc.reset();
  HEnc.reset();
  odom.x = odom.y = odom.theta = 0;
}

/**
 * Returns current x value (In inches)
 */
float Odom::getX() {
  return odom.x;
}

/**
 * Returns current y value (In inches)
 */
float Odom::getY() {
  return odom.y;
}

/**
 * Returns current theta value (In degress)
 */
float Odom::getTheta() {
  return odom.theta;
}

/**
 * Starts the odometry tracking task
 */
void Odom::startTask(void* param) {
  delay(100);
  isRunning = true;
  odom.reset();
  cout<<"Encoders and odometry reset"<<endl;
  delay(500);
  cout<<"Odometry Task Started"<<endl;

  double currentTheta = 0, currentVertical = 0, currentHorizontial = 0;
  double lastTheta = 0, lastVertical = 0, lastHorizontial = 0;
  double deltaTheta = 0, deltaVertical = 0, deltaHorizontial = 0;
  double theta = 0, averageTheta = 0;
  double verticalRadius = 0, horizontialRadius = 0;
  double verticalCord = 0, horizontialCord = 0;

  while (isRunning) {

	  // Value of the sensors
    currentTheta = math.angleWrap(IMU.get_rotation() * (7200/7181.9));
	  currentVertical = VEnc.get_value();
	  currentHorizontial = HEnc.get_value();

    // Change in sensor values since last update
    deltaTheta = math.filter(currentTheta, lastTheta);
    deltaVertical = math.filter(currentVertical, lastHorizontial);
    deltaHorizontial = math.filter(currentHorizontial, lastHorizontial);

    // Finding the average of the current and last theta
    averageTheta = (currentTheta + lastTheta)/2;

	  // Update last sensor values
    lastTheta = currentTheta;
    lastVertical = currentVertical;
    lastHorizontial = currentHorizontial;

    currentTheta = math.degToRad(currentTheta); // Convert theta from degress to radians

	  // If the robot turned
	  if (deltaTheta != 0) {

      theta = deltaTheta / 2.0;

      // Calculating the traslation of the vertical wheel
		  verticalRadius = deltaVertical / deltaTheta + Sv;
		  verticalCord = (verticalRadius * sin(theta)) * 2;

      // Calculating the translation with the horizontial wheel
		  horizontialRadius = deltaHorizontial / deltaTheta + Sh;
		  horizontialCord = (horizontialRadius * sin(theta)) * 2;

	  } else { // If the robot did not turn

      // Setting the vertical and horizontial movement to the ticks rotated
		  verticalCord = deltaVertical;
		  horizontialCord = deltaHorizontial;

      // Setting the offset to 0 because it didn't turn
		  deltaTheta = 0;

	  }

    // Adding the change in the axis to the global coordonates
    odom.x += math.ticksToInch(verticalCord * sin(averageTheta));
    odom.y += math.ticksToInch(verticalCord * cos(averageTheta));

    odom.x += math.ticksToInch(horizontialCord * -cos(averageTheta));
    odom.y += math.ticksToInch(horizontialCord * sin(averageTheta));

    // Updating the global angle
	  odom.theta += deltaTheta;

	  delay(10);
  }
}

/**
 * Ends the odometry task
 */
void Odom::endTask() {
  isRunning = false;
  odom.reset();
  cout<<"Odometry task ended"<<endl;
}
