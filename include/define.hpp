#include "main.h"
#include "functions/chassis.hpp"
#include "functions/intake.hpp"
#include "functions/uptake.hpp"
#include "functions/odometry.hpp"
#include "functions/pid.hpp"
#include "functions/math.hpp"

#ifndef DEFINE_HPP
#define DEFINE_HPP

/* ********** Declare Motors ********** */

extern Motor LFD, LBD , RFD, RBD; // Drive motors
extern Motor LI, RI; // Intakes
extern Motor TU, BU; // Uptake

/* ********** Declare Sensors ********** */

extern Imu IMU; // Inertial measurement unit
extern ADIEncoder LEnc, REnc, MEnc; // Encoders
extern ADIPotentiometer ArmPot; // Arm potentiometer

/* ********** Declare Controller ********** */

extern Controller Main; // Main controller

extern Math math;
extern Odom odom;
extern Chassis chassis;
extern PID pid;
extern Uptake uptake;
extern Intake intake;

#endif
