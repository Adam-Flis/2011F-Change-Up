#include "main.h"
#include "define.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"

Odom odom;
static Math math;

// Define variables
bool Odom::isRunning = false;

double Odom::x, Odom::y, Odom::thetaRad, Odom::thetaDeg;

/**
 * Returns current x value (In inches)
 */
double Odom::getX() {
  return odom.x;
}

/**
 * Returns current y value (In inches)
 */
double Odom::getY() {
  return odom.y;
}

/**
 * Returns current theta value (In radians)
 */
double Odom::getThetaRad() {
  return odom.thetaRad;
}

/**
 * Returns current theta value (In degress)
 */
double Odom::getThetaDeg() {
  return odom.thetaDeg;
}

/**
 * Resets x & y odom
 */
void Odom::reset() {
  VEnc.reset();
  HEnc.reset();
  odom.x = odom.y = 0;
}

/**
 * Starts the odometry task
 */
void Odom::start() {
  isRunning = true;
  LIMU.tare_rotation();
  RIMU.tare_rotation();
  odom.reset();
  odom.thetaRad = odom.thetaDeg = 0;

  // Define variables
  double Tv = 3.0, // Distance from tracking center to middle of vertical wheel
         Th = 9.5, // Distance from tracking center to middle of horizontial wheel
         Sv = 1.0, // Slop adjustment for vertical tracking wheel
         Sh = 1.0,  // Slop adjustment for horizontial trackinng wheel
         Sl = 7200/7181.9, // Scale factor of left IMU
         Sr = 7200/7181.9, // Scale factor of right IMU

   // Theta
         deltaT = 0, // Change in theta between refresh cycles
         alpha = 0, // Average theta robot took over interval
         theta = 0, // Average theta between average angle and final
         radius = 0, // Radius of arc traveled by robot
         filteredT = 0, // Filtered theta value
         newT = 0, // Theta returned by filter
         averageT = 0, // Average theta of refresh
         currentR = 0, // Current raw theta
         lastR = 0, // Previous measurement of raw theta

   // Encoder
         currentV = 0, // Current rotations of vertical wheel
         currentH = 0, // Current rotations of horizontial wheel
         lastV = 0, // Previous rotation measurement of vertical wheel
         lastH = 0, // Previous rotation measurement of horizontial wheel
         deltaV = 0, // Distance traveled by vertical wheel over interval in inches
         deltaH = 0, // Distance traveled by horizontial wheel over interval in inches
         radiusV = 0, // Radius vertical wheel traveled
         radiusH = 0, // Radius horizontial wheel traveled
         cordV = 0, // Traslation of vertical wheel
         cordH = 0, // Traslation of horizontial wheel

   // IMU
         Li, // Left IMU sensor
         Ri; // Right IMU sensor

  while (isRunning) {

    // Estabblishing which IMU to use to minimize drift
    Li = LIMU.get_rotation() * Sl;
    Ri = RIMU.get_rotation() * Sr;
    currentR = Ri;
    if (Li > Ri) {
      currentR = Li;
    }

    // Calculate theta
    filteredT += math.filter(currentR, lastR);
    lastR = currentR;
    newT = math.degToRad(filteredT);
    deltaT = newT - odom.thetaRad;

    // Claculate inches
    // VerticaL wheel
	  currentV = math.ticksToInch(VEnc.get_value()) * Sv;
    deltaV = currentV - lastV;
    lastV = currentV;

    // Horizontial wheel
	  currentH = math.ticksToInch(HEnc.get_value()) * Sh;
    deltaH = currentH - lastH;
    lastH = currentH;

    // Calculate wheel traslations if the robot has turned
    if (deltaT != 0) {

      // Calculating the traslation of the vertical wheel
		  radiusV = deltaV / deltaT + Tv;
		  cordV = (2 * sin(deltaT / 2)) * radiusV;

      // Calculating the translation with the horizontial wheel
		  radiusH = deltaH / deltaT + Th;
		  cordH = (2 * sin(deltaT / 2)) * radiusH;

    }

    // If the robot did not turn
    else {

      // Setting the vertical and horizontial movement to the inches rotated
		  cordV = deltaV;
      cordH = deltaH;

      // Setting the offset to 0 because it didn't turn
		  alpha = 0;

	  }

    // Finding the average of the current and last theta
    alpha = deltaT / 2;
    averageT = odom.thetaRad + alpha;

    // Adding the change in the axis to the global coordonates
    odom.x += cordV * sin(averageT);
    odom.y += cordV * cos(averageT);

    odom.x += cordH * cos(averageT);
    odom.y += cordH * -sin(averageT);

    // Updating the global theta
    odom.thetaRad += deltaT;
    odom.thetaDeg = math.radToDeg(odom.thetaRad);

    // Display sensor values to LCD display
    lcd::print(0, "X: %f \n", odom.x);
    lcd::print(1, "Y: %f \n", odom.y);
    lcd::print(2, "Theta: %f radians\n", odom.thetaRad);
    lcd::print(3, "Theta: %f degress\n", odom.thetaDeg);
    lcd::print(4, "Left IMU: %f degress\n", Li);
    lcd::print(5, "Right IMU: %f degress\n", Ri);

    delay(10);
  }
}

/**
 * Ends the odometry task
 */
void Odom::end() {
  if (trackingTask != nullptr) {
    isRunning = false;
    trackingTask->remove(); // Removes memory stack task is occupying
    delete trackingTask; // Deletes the task from memory
    trackingTask = nullptr;
  }
}
