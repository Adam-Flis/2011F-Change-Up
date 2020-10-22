#include "main.h"
#include "define.hpp"

PID::PID(){}
PID::~PID(){}

float kP = 20, kI = 0.01, kD = 5;
float kP_t = 6, kI_t = 0.01, kD_t = 30;
float kP_d = 500, kD_d = 300;


void PID::drive(float distance, float maxSpeed) {
  float currentX = odom.getX();
  float currentY = odom.getY();
  float currentTheta = odom.getTheta();

}

void PID::turn(float theta, float maxSpeed) {
  float currentTheta = odom.getTheta();


}
