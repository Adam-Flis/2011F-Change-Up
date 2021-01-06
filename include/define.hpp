#include "main.h"

#ifndef DEFINE_HPP
#define DEFINE_HPP

/* ********** Declare Motors ********** */

extern Motor LFD, LBD , RFD, RBD; // Drive motors
extern Motor LI, RI; // Intakes
extern Motor LU, RU; // Uptakes

/* ********** Declare Sensors ********** */

extern Imu IMU; // Inertial measurement unit
extern Distance Distance_Sensor; // Distance sensor
extern Optical Middle_Optical; // Optical sensor
extern ADILineSensor Bottom_Line, Middle_Line, Top_Line; // Line sensors
extern ADIEncoder HEnc, VEnc; // Encoders

/* ********** Declare Controller ********** */

extern Controller Main; // Main controller

/* ********** Declare Tasks ********** */

extern Task *trackingTask;
extern Task *chassisTask;
extern Task *rollerTask;

#endif
