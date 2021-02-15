#include "main.h"

#ifndef DEFINE_HPP
#define DEFINE_HPP

/* ********** Declare Motors ********** */

extern Motor LFD, LBD , RFD, RBD; // Drive motors
extern Motor LI, RI; // Intakes
extern Motor LU, RU; // Uptakes

/* ********** Declare Sensors ********** */

extern Imu LIMU, RIMU; // Inertial measurement unit sensors
extern Distance Distance_Sensor; // Distance sensor
extern Optical Intake_Optical, Uptake_Optical; // Optical sensors
extern ADILineSensor Bottom_Line, Middle_Line, Top_Line; // Line sensors
extern ADIEncoder HEnc, VEnc; // Encoders

/* ********** Declare Controller ********** */

extern Controller Main; // Main controller

/* ********** Declare Tasks ********** */

extern Task *trackingTask;

#endif
