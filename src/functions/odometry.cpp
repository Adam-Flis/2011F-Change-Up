#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"

float trackLength;
float wheelDiameter = 2.75;
double wheelCircumference = wheelDiameter * M_PI;
int ticksPerRev = 360;
float gearRatio = 1;

Odom odom;
Odom::Odom(){};
Odom::~Odom(){};

int Odom::inchToTicks(int ticks){
  double inches = ticks/ticksPerRev * gearRatio * wheelCircumference;
  return inches;
}

void Odom::reset(){
  odom.x = 0;
  odom.y = 0;
  odom.theta = 0;
}

int Odom::getX(){
  return odom.x;
}

int Odom::getY(){
  return odom.y;
}

int Odom::getTheta(){
  return odom.theta;
}

void Odom::track(void* param){
  //bool getIMU = true;
  LEnc.reset();
  REnc.reset();
  odom.reset();
  cout << "Encoders reset and odometry initalized";
  lcd::set_text(1, "Encoders reset and odometry initalized");
  while (1){
    double currentTheta = odom.theta;
    double currentLeft = inchToTicks(LEnc.get_value());
    double currentRight = inchToTicks(REnc.get_value());
    double alpha = (currentRight - currentLeft)/trackLength;
    double tangent = 2 * ((currentLeft/alpha) + (trackLength/2)) * sin(alpha/2);
    double deltaX = tangent * cos(currentTheta + alpha/2);
    double deltaY = tangent * sin(currentTheta + alpha/2);
    odom.theta += alpha;
    odom.x += deltaX;
    odom.y += deltaY;

    //IMU refreshes at 100hz or 20ms
    // if (getIMU == true){
    //   double currentIMUTheta = IMU.get_rotation();
    // };
    //getIMU = !getIMU;
    delay(10);
  }
}
