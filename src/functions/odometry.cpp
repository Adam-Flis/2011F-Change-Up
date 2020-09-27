#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"

float trackLength;
float wheelDiameter = 2.75;
double wheelCircumference = wheelDiameter * M_PI;

Odom odom;
Odom::Odom(){};
Odom::~Odom(){};

int Odom::inchToTicks(int ticks){
  double inches = ticks * wheelCircumference;
  return inches;
}

void Odom::reset(){
  odom.x = 0;
  odom.y = 0;
  odom.theta = 0;
}

void Odom::track(){
  double lastTheta, lastIMUTheta, lastMiddle;
  LEnc.reset();
  REnc.reset();
  MEnc.reset();
  odom.reset();
  while (1){
    double currentTheta = odom.theta;
    double currentIMUTheta = IMU.get_rotation();
    int currentLeft = inchToTicks(LEnc.get_value());
    int currentRight = inchToTicks(REnc.get_value());

    //Calculate theta

    //Calculate distance left wheel traveled

    //Calculate distance right wheel traveled


  }
}
