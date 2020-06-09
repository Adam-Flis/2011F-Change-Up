#include "main.h"

#ifndef DEFINE_HPP
#define DEFINE_HPP

/* ********** Declare Motors ********** */

extern Motor LFD, LBD , RFD, RBD; //Drive motors
extern Motor BLI, BRI; //Bottom intakes
extern Motor Arm;
extern Motor TI;

/* ********** Declare Sensors ********** */

extern Imu IMU;
extern ADIEncoder LEnc, REnc, MEnc; //Encoders
extern ADIPotentiometer ArmPot;

/* ********** Declare Controller ********** */

extern Controller Master;

/* ********** Declare Global Variables ********** */


#endif
