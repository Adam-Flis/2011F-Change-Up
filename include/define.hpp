#include "main.h"

#ifndef DEFINE_HPP
#define DEFINE_HPP

/* ********** Declare Motors ********** */

extern Motor LFD, LBD , RFD, RBD; // Drive motors
extern Motor LI, RI; // Intakes
extern Motor LU, RU; // Uptakes

/* ********** Declare Sensors ********** */

extern Imu LIMU, RIMU; // Inertial measurement units
extern Distance Distance_Sensor; // Distance sensor
extern Optical Intake_Optical, Bottom_Uptake_Optical, Middle_Uptake_Optical; // Optical sensors
extern ADIEncoder HEnc, VEnc; // Encoders

/* ********** Declare Controller ********** */

extern Controller Main; // Main controller

/* ********** Declare Variables ********** */

// Optical
extern double blueThresh, redThresh;

// Distance
extern double distanceThresh;

/* ********** Declare Tasks ********** */

extern Task *trackingTask;
extern Task *chassisTask;
extern Task *intakeTask;
extern Task *uptakeTask;

#endif
