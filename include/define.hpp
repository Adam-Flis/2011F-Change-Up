#include "main.h"

#ifndef DEFINE_HPP
#define DEFINE_HPP

/* ********** Declare Motors ********** */

extern Motor LFD, LBD , RFD, RBD; // Drive motors
extern Motor LI, RI; // Intakes
extern Motor TU, BU; // Uptake

/* ********** Declare Sensors ********** */

extern Imu IMU; // Inertial measurement unit
extern Optical Intake_Optical;
extern ADILineSensor Bottom_Uptake_Line, Top_Uptake_Line;
extern ADIEncoder LEnc, REnc; // Encoders
extern ADIPotentiometer ArmPot; // Arm potentiometer

/* ********** Declare Controller ********** */

extern Controller Main; // Main controller

#endif
