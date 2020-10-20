#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"

float trackLength = 6; //In inches

Odom odom;
Math math;

Odom::Odom(){};
Odom::~Odom(){};

void Odom::reset() {
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

void Odom::track(void* param) {
  delay(300);
  LEnc.reset();
  REnc.reset();
  odom.reset();
  float lastTheta, lastLeft, lastRight;
  cout << "Encoders reset and odometry initalized" << endl;
  lcd::set_text(0, "Encoders reset and odometry initalized");
  while (1){
    float currentTheta = IMU.get_rotation();
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
    delay(20); // IMU refreshes at 50hz or 20ms
              // Encoders/motors refresh at 100hz or 10ms
  }
}
