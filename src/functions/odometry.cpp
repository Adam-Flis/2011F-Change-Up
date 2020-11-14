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

float lastTheta = 0, lastMiddle = 0;
float currentTheta = 0, currentMiddle = 0;
float deltaMiddle = 0, deltaX = 0, deltaY = 0;

void Odom::startTask(void* param) {
  delay(300);
  isRunning = true;
  odom.reset();
  cout<<"Encoders and odometry reset"<<endl;
  cout<<"Odometry Task Started"<<endl;
  while (isRunning) {
    currentTheta = math.angleWrap(IMU.get_rotation() * (7200/7181.9)) * (M_PI/180);
    currentMiddle = math.encoderAverage();
    deltaMiddle = currentMiddle - lastMiddle;
    deltaX = deltaMiddle * sin((currentTheta + lastTheta)/2);
    deltaY = deltaMiddle * cos((currentTheta + lastTheta)/2);
    lastTheta = currentTheta;
    lastMiddle = currentMiddle;
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
