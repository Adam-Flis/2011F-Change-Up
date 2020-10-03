#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"

float trackLength = 6;
float wheelDiameter = 2.75;
double wheelCircumference = wheelDiameter * M_PI;

Odom odom;
Odom::Odom(){};
Odom::~Odom(){};

double Odom::ticksToInch(int ticks){
  double inches = ticks/360 * wheelCircumference;
  return inches;
}

void Odom::reset(){
  odom.x = 0;
  odom.y = 0;
  odom.theta = 0;
}

double Odom::getX(){
  return odom.x;
}

double Odom::getY(){
  return odom.y;
}

double Odom::getTheta(){
  return odom.theta;
}

void Odom::track(void* param){
  delay(300);
  //bool getIMU = true;
  LEnc.reset();
  REnc.reset();
  odom.reset();
  cout << "Encoders reset and odometry initalized" << endl;
  lcd::set_text(1, "Encoders reset and odometry initalized");
  while (1){
    double currentTheta = odom.theta;
    double currentLeft = ticksToInch(LEnc.get_value());
    double currentRight = ticksToInch(REnc.get_value());
    lcd::print(6, "Left: %lf in\n", currentLeft);
    double alpha = (currentRight - currentLeft)/(trackLength);
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
