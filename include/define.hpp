#include "main.h"

#ifndef DEFINE_HPP
#define DEFINE_HPP

/* ********** Declare Motors ********** */

extern Motor LFD, LBD , RFD, RBD; // Drive motors
extern Motor BLI, BRI; // Bottom intakes
extern Motor Arm; // Arm motor
extern Motor TI; // Top intake

/* ********** Declare Sensors ********** */

extern Imu IMU; // Inertial measurement unit
extern ADIEncoder LEnc, REnc, MEnc; // Encoders
extern ADIPotentiometer ArmPot; // Arm potentiometer

/* ********** Declare Controller ********** */

extern Controller Main; // Main controller

#endif
