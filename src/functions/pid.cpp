#include "main.h"
#include "define.hpp"

PID::PID(){}
PID::~PID(){}

float kP = 20, kI = 0.01, kD = 5;
float kP_t = 6, kI_t = 0.01, kD_t = 30;
float kP_d = 500, kD_d = 300;

float intergralActive = math.inchToTicks(3);
float intergralActive_t = 5;


void PID::drive(float distance, float maxSpeed) {


}

void PID::turn(float theta, float maxSpeed) {



}
