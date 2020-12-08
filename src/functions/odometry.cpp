#include "main.h"
#include "define.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"

Odom odom; // Class definition
static Math math;

/* ********** Define variables ********** */

bool Odom::isRunning = false;
float lastTheta = 0, lastVertical = 0, lastHorizontial = 0;
float currentTheta = 0, currentVertical = 0, currentHorizontial = 0;
float deltaVertical = 0, deltaHorizontial = 0, deltaX = 0, deltaY = 0;
float averageTheta = 0;

/**
 * Resets the odometry variables
 */
void Odom::reset() {
  VEnc.reset();
  HEnc.reset();
  odom.x = odom.y = odom.theta = 0;
  lastTheta = 0, lastVertical = 0, lastHorizontial = 0;
  currentTheta = 0, currentVertical = 0, currentHorizontial = 0;
  deltaVertical = 0, deltaHorizontial = 0, deltaX = 0, deltaY = 0;
  averageTheta = 0;
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
 * Starts the odometry task
 */
void Odom::startTask(void* param) {
  delay(100);
  isRunning = true;
  odom.reset();
  cout<<"Encoders and odometry reset"<<endl;
  delay(500);
  cout<<"Odometry Task Started"<<endl;
  while (isRunning) {
    currentTheta = math.angleWrap(IMU.get_rotation() * (7200/7181.9)) * (M_PI/180); // Filters and then converts the IMU value to radians

    if (abs(currentTheta - lastTheta) < 0.01) { // Filter theta value
      currentTheta = 0;
    }

    currentVertical = VEnc.get_value();
    deltaVertical = currentVertical - lastVertical; // Difference between current and last vertical position

    currentHorizontial = HEnc.get_value();
    deltaHorizontial = currentHorizontial - lastHorizontial; // Difference between current and last horizontial position

    averageTheta = (currentTheta + lastTheta)/2;

    deltaX = deltaVertical * sin(averageTheta); // Calculates the distance the robot moved in the x direction
    deltaY = deltaVertical * cos(averageTheta); // Calculates the distance the robot moved in the y direction

    deltaX += deltaHorizontial * -cos(averageTheta);
    deltaY += deltaHorizontial * sin(averageTheta);

    lastTheta = currentTheta;
    lastVertical = currentVertical;
    lastHorizontial = currentHorizontial;

    odom.theta = currentTheta * (180/M_PI); // Converts currentTheta from radians back to degress
    odom.x += math.ticksToInch(deltaX); // Converts then adds deltaX to current x position
    odom.y += math.ticksToInch(deltaY); // Converts then adds deltaY to current Y position

    delay(10); // Loop speed, prevent overload
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
