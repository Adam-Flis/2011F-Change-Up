#include "main.h"
#include "define.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"

Odom odom; // Class definition
static Math math;

/* ********** Define variables ********** */

bool Odom::isRunning = false;
float lastTheta = 0, lastMiddle = 0;
float currentTheta = 0, currentMiddle = 0;
float deltaMiddle = 0, deltaX = 0, deltaY = 0;

/**
 * Resets the odometry variables
 */
void Odom::reset() {
  LEnc.reset();
  REnc.reset();
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
 * Starts the odometry task
 */
void Odom::startTask(void* param) {
  delay(300);
  isRunning = true;
  odom.reset();
  cout<<"Encoders and odometry reset"<<endl;
  cout<<"Odometry Task Started"<<endl;
  while (isRunning) {
    currentTheta = math.angleWrap(IMU.get_rotation() * (7200/7181.9)) * (M_PI/180); // Filters and then converts the IMU value to radians

    currentMiddle = math.encoderAverage();
    deltaMiddle = currentMiddle - lastMiddle; // Difference between current and last position

    deltaX = deltaMiddle * sin((currentTheta + lastTheta)/2); // Calculates the distance the robot moved in the x direction
    deltaY = deltaMiddle * cos((currentTheta + lastTheta)/2); // Calculates the distance the robot moved in the y direction

    lastTheta = currentTheta;
    lastMiddle = currentMiddle;

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
