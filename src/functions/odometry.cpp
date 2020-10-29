#include "main.h"
#include "define.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"

Odom odom;
static Math math;

float trackLength = 6; //In inches
bool Odom::isRunning = false;

void Odom::reset() {
  LEnc.reset();
  REnc.reset();
  odom.x = odom.y = odom.theta = 0;
}

float Odom::getX() {
  return odom.x;
}

float Odom::getY() {
  return odom.y;
}

float Odom::getTheta() {
  return odom.theta;
}

float lastTheta = 0, lastLeft = 0, lastRight = 0;
float currentTheta = 0, currentLeft = 0, currentRight = 0;
float deltaLeft = 0, deltaRight = 0, deltaX = 0, deltaY = 0;

void Odom::startTask(void* param) {
  delay(300);
  isRunning = true;
  odom.reset();
  cout<<"Encoders and odometry reset"<<endl;
  cout<<"Odometry Task Started"<<endl;
  while (isRunning) {
    currentTheta = math.angleWrap(IMU.get_rotation()) * (M_PI/180);
    currentLeft = LEnc.get_value();
    currentRight = REnc.get_value();
    deltaLeft = currentLeft - lastLeft;
    deltaRight = currentRight - lastRight;
    deltaX = (deltaLeft + deltaRight)/2 * sin((currentTheta + lastTheta)/2);
    deltaY = (deltaLeft + deltaRight)/2 * cos((currentTheta + lastTheta)/2);
    lastTheta = currentTheta;
    lastLeft = currentLeft;
    lastRight = currentRight;
    odom.theta = currentTheta * (180/M_PI);
    odom.x += math.ticksToInch(deltaX);
    odom.y += math.ticksToInch(deltaY);
    delay(10);
  }
}

void Odom::endTask() {
  isRunning = false;
  odom.reset();
  cout<<"Odometry task ended"<<endl;
}
