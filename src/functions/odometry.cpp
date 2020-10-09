#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"

float trackLength = 6; //In inches
float wheelDiameter = 2.75; //In inches
float wheelCircumference = wheelDiameter * M_PI;
float gearRatio = 1/1; //Teeth of driver/Teeth of driven (N/A for me because of unpowered wheels)
float ticksPerRevolution = 360; //Number of ticks in one full revolution of encoder/motor

Odom odom;
Odom::Odom(){};
Odom::~Odom(){};

float Odom::ticksToInch(float ticks){
  float inches = ticks/ticksPerRevolution * gearRatio * wheelCircumference;
  return inches;
}

void Odom::reset(){
  odom.x = 0;
  odom.y = 0;
  odom.theta = 0;
}

float Odom::getX(){
  return odom.x;
}

float Odom::getY(){
  return odom.y;
}

float Odom::getTheta(){
  return odom.theta;
}

float Odom::getIMURot(){
  return odom.IMURot;
}

void Odom::track(void* param){
  delay(300);
  bool getIMU = true;
  LEnc.reset();
  REnc.reset();
  odom.reset();
  cout << "Encoders reset and odometry initalized" << endl;
  lcd::set_text(0, "Encoders reset and odometry initalized");
  while (1){
    float currentTheta = odom.theta;
    float currentLeft = ticksToInch(LEnc.get_value());
    float currentRight = ticksToInch(REnc.get_value());
    float alpha = (currentRight - currentLeft)/(trackLength);
    float tangent = 2 * ((currentLeft/alpha) + (trackLength/2)) * sin(alpha/2);
    float deltaX = tangent * cos(currentTheta + alpha/2);
    float deltaY = tangent * sin(currentTheta + alpha/2);
    odom.theta += alpha;
    odom.x += deltaX;
    odom.y += deltaY;

    //IMU refreshes at 50hz or 20ms compared to encoders that refresh at 100hz or 10ms
    if (getIMU == true){
      odom.IMURot = IMU.get_rotation();
    };
    getIMU = !getIMU;
    delay(10);
  }
}
