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

void Odom::startTask(void* param) {
  delay(300);
  isRunning = true;
  odom.reset();
  float lastTheta, lastLeft, lastRight;
  cout<<"Encoders and odometry reset"<<endl;
  cout<<"Odometry Task Started"<<endl;
  while (isRunning) {
    float currentTheta = math.angleWrap(IMU.get_rotation());
    float currentLeft = LEnc.get_value();
    float currentRight = REnc.get_value();
    float deltaLeft = currentLeft - lastLeft;
    float deltaRight = currentRight - lastRight;
    float deltaX = sin((currentTheta + lastTheta)/2) * ((deltaLeft + deltaRight)/2);
    float deltaY = cos((currentTheta + lastTheta)/2) * ((deltaLeft + deltaRight)/2);
    lastTheta = currentTheta;
    lastLeft = currentLeft;
    lastRight = currentRight;
    odom.theta = currentTheta;
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
