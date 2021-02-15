#include "main.h"
#include "define.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"

Odom odom; // Class definition
static Math math;

/**
 * Resets the odometry variables
 */
void Odom::reset() {
  VEnc.reset();
  HEnc.reset();
  odom.x = odom.y = 0;
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
 * Returns current theta value (In radians)
 */
float Odom::getTheta() {
  return odom.theta;
}

/**
 * Starts the odometry tracking task
 */
void Odom::startTask() {
  isRunning = true;
  odom.reset();
  odom.theta = 0;
  cout<<"Encoders and odometry reset"<<endl;
  cout<<"Odometry Task Started"<<endl;

  // Define variables
  // Constants
  float Sv = 2.8, // Distance from tracking center to middle of vertical wheel
        Sh = 7.5, // Distance from tracking center to middle of horizontial wheel
        verticalSF = 1.028, // Slop adjustment for vertical tracking wheel
        horizontialSF = 1.028,  // Slop adjustment for horizontial trackinng wheel

  // Theta
        deltaTheta = 0, // Change in theta between refresh cycles
        alpha = 0, // Average theta robot took over interval
        theta = 0, // Average theta between average angle and final
        radius = 0, // Radius of arc traveled by robot
        thetaFiltered = 0, // Filtered theta value
        thetaNew = 0, // Theta returned by filter
        thetaAverage = 0, // Average theta of refresh
        currentRotation = 0, // Current raw theta
        lastRotation = 0, // Previous measurement of raw theta

  // Encoder
        currentVertical = 0, // Current rotations of vertical wheel
        currentHorizontial = 0, // Current rotations of horizontial wheel
        lastVertical = 0, // Previous rotation measurement of vertical wheel
        lastHorizontial = 0, // Previous rotation measurement of horizontial wheel
        deltaVertical = 0, // Distance traveled by vertical wheel over interval in inches
        deltaHorizontial = 0, // Distance traveled by horizontial wheel over interval in inches
        verticalRadius = 0, // Radius vertical wheel traveled
        horizontialRadius = 0, // Radius horizontial wheel traveled
        verticalCord = 0, // Traslation of vertical wheel
        horizontialCord = 0, // Traslation of horizontial wheel

  // IMU
        iL, // Left IMU sensor
        iR, // Right IMU sensor
        sL = 7200/7181.9, // Scale factor of left IMU
        sR = 7200/7181.9, // Scale factor of right IMU
        Li = LIMU.get_rotation(), // Initial value of left IMU
        Ri = RIMU.get_rotation(); // Initial value of right IMU

  while (isRunning) {

    // Establishing IMU to use
    iL = (LIMU.get_rotation() - Li) * sL;
    iR = (RIMU.get_rotation() - Ri) * sR;
    currentRotation = iR;
    if (iL > iR) {
      currentRotation = iL;
    }

	  // Calculate theta value
    thetaFiltered += math.filter(currentRotation, lastRotation);
    lastRotation = currentRotation;
    thetaNew = math.degToRad(thetaFiltered);
    deltaTheta = thetaNew - odom.theta;

    // Inches the encoders have traveled
    // VerticaL wheel
	  currentVertical = math.ticksToInch(VEnc.get_value()) * verticalSF;
    deltaVertical = currentVertical - lastVertical;
    lastVertical = currentVertical;
    // Horizontial wheel
	  currentHorizontial = math.ticksToInch(HEnc.get_value()) * horizontialSF;
    deltaHorizontial = currentHorizontial - lastHorizontial;
    lastHorizontial = currentHorizontial;

    // Calculate wheel traslations if the robot has turned
    if (deltaTheta != 0) {

      // Calculating the traslation of the vertical wheel
		  verticalRadius = deltaVertical / deltaTheta + Sv;
		  verticalCord = (2*sin(deltaTheta/2)) * verticalRadius;

      // Calculating the translation with the horizontial wheel
		  horizontialRadius = deltaHorizontial / deltaTheta + Sh;
		  horizontialCord = (2*sin(deltaTheta/2)) * horizontialRadius;

    } else { // If the robot did not turn

      // Setting the vertical and horizontial movement to the inches rotated
		  verticalCord = deltaVertical;
		  horizontialCord = deltaHorizontial;

      // Setting the offset to 0 because it didn't turn
		  alpha = 0;

	  }

    // Finding the average of the current and last theta
    alpha = deltaTheta/2;
    thetaAverage = odom.theta + alpha;

    // Adding the change in the axis to the global coordonates
    odom.x += verticalCord * sin(thetaAverage);
    odom.y += verticalCord * cos(thetaAverage);

    odom.x += horizontialCord * cos(thetaAverage);
    odom.y += horizontialCord * -sin(thetaAverage);

    // Updating the global theta
    odom.theta += deltaTheta;

    // Display sensor values to LCD display
    lcd::print(0, "X: %f \n", odom.x);
    lcd::print(1, "Y: %f \n", odom.y);
    lcd::print(2, "Theta: %f degress\n", math.radToDeg(odom.theta));
    lcd::print(3, "Left IMU: %f degress\n", iL);
    lcd::print(4, "Right IMU: %f degress\n", iR);

	  delay(10); // Loop speed
  }
}

/**
 * Ends the odometry task
 */
void Odom::endTask() {
  if (trackingTask != nullptr) {
    trackingTask->remove(); // Removes memory stack task is occupying
    delete trackingTask; // Deletes the task from memory
    trackingTask = nullptr;
    cout<<"Odometry task ended"<<endl;
  }
}
