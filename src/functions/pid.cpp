#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"
#include "functions/pid.hpp"


Odom odom;
Math math;

PID::PID(){}
PID::~PID(){}

float kP = 20, kI = 0.01, kD = 5;
float kP_t = 6, kI_t = 0.01, kD_t = 30;
float kP_d = 500, kD_d = 300;


void PID::drivePID(float x, float y, float maxSpeed) {
  float currentX = odom.getX();
  float currentY = odom.getY();
  float currentTheta = odom.getTheta();

}

void PID::turnPID(float theta, float maxSpeed) {
  float currentTheta = odom.getTheta();


}
