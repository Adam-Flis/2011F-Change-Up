#include "main.h"
#include "define.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"

Odom odom; // Class definition
static Math math;

/* ********** Define variables ********** */

bool Odom::isRunning = false;
float Sv = 2.8;
float Sh = 7.5;

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
  return math.angleWrap(odom.theta);
}

/**
 * Starts the odometry tracking task
 */
void Odom::startTask() {
  isRunning = true;
  odom.reset();
  cout<<"Encoders and odometry reset"<<endl;
  cout<<"Odometry Task Started"<<endl;

  // Define variables
  float currentTheta = 0, currentVertical = 0, currentHorizontial = 0;
  float lastTheta = 0, lastVertical = 0, lastHorizontial = 0;
  float deltaTheta = 0, deltaVertical = 0, deltaHorizontial = 0, deltaX = 0, deltaY = 0;
  float alpha = 0, averageTheta = 0, angle = 0, inertialValue = 0, thetaFiltered = 0;
  float verticalRadius = 0, horizontialRadius = 0;
  float verticalCord = 0, horizontialCord = 0;

  while (isRunning) {

	  // Value of the sensors
    currentTheta = LIMU.get_rotation() * (7200/7181.9);
    thetaFiltered += math.filter(currentTheta, lastTheta);
    lastTheta = currentTheta;

    // Calculating the change in the angle using the inertial sensor
    deltaTheta = math.degToRad(thetaFiltered - odom.theta);

    // Inches the encoders have moved
	  currentVertical = math.ticksToInch(VEnc.get_value());
	  currentHorizontial = math.ticksToInch(HEnc.get_value());

    // Change in sensor values since last update
    //deltaTheta = currentTheta - math.degToRad(odom.getTheta());
    deltaVertical = currentVertical - lastVertical;
    deltaHorizontial = currentHorizontial - lastHorizontial;

    lastVertical = currentVertical;
    lastHorizontial = currentHorizontial;

	  // If the robot turned
	  if (deltaTheta != 0) {

      alpha = deltaTheta / 2;

      // Calculating the traslation of the vertical wheel
		  verticalRadius = deltaVertical / deltaTheta + Sv;
		  verticalCord = (verticalRadius * sin(alpha)) * 2;

      // Calculating the translation with the horizontial wheel
		  horizontialRadius = deltaHorizontial / deltaTheta + Sh;
		  horizontialCord = (horizontialRadius * sin(alpha)) * 2;

	  } else { // If the robot did not turn

      // Setting the vertical and horizontial movement to the inches rotated
		  verticalCord = deltaVertical;
		  horizontialCord = deltaHorizontial;

      // Setting the offset to 0 because it didn't turn
		  alpha = 0;

	  }

    // Finding the average of the current and last theta
    averageTheta = math.degToRad(odom.theta) + alpha;

    // Adding the change in the axis to the global coordonates
    odom.x += verticalCord * sin(averageTheta);
    odom.y += verticalCord * cos(averageTheta);

    odom.x += horizontialCord * cos(averageTheta);
    odom.y += horizontialCord * -sin(averageTheta);

    // Updating the global positions
    odom.theta += math.radToDeg(deltaTheta);

    // Display sensor values to LCD display
    lcd::print(0, "X: %f \n", odom.getX());
    lcd::print(1, "Y: %f \n", odom.getY());
    lcd::print(2, "Theta: %f degress\n", odom.getTheta());
    lcd::print(3, "Left IMU: %f degress\n", LIMU.get_rotation());
    lcd::print(4, "Right IMU: %f degress\n", RIMU.get_rotation());

	  delay(10);
  }
}

/**
 * Ends the odometry task
 */
void Odom::endTask() {
  //isRunning = false;
  trackingTask->remove();
  delete trackingTask; // Deletes the task from memory
  trackingTask = nullptr;
  odom.reset();
  cout<<"Odometry task ended"<<endl;
}
