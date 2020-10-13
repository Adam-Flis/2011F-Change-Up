#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"

float trackLength = 6; //In inches
float wheelDiameter = 2.75; //In inches
float wheelCircumference = wheelDiameter * M_PI;
float gearRatio = 1/1; //Teeth of driver/Teeth of driven (N/A because of unpowered wheels)
float ticksPerRevolution = 360; //Number of ticks in one full revolution of encoder/motor

Odom odom;
Odom::Odom(){};
Odom::~Odom(){};

float Odom::ticksToInch(float ticks) {
  float inches = ticks/ticksPerRevolution * gearRatio * wheelCircumference;
  return inches;
}

void Odom::reset() {
  odom.x = 0;
  odom.y = 0;
  odom.theta = 0;
}

float Odom::getX() {
  return odom.x;
}

float Odom::getY() {
  return odom.y;
}

float Odom::getTheta(){
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
    odom.x += ticksToInch(deltaX);
    odom.y += ticksToInch(deltaY);
    delay(20); // IMU refreshes at 50hz or 20ms
              // Encoders/motors refresh at 100hz or 10ms
  }
}
