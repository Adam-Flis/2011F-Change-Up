#include "functions/chassis.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"
#include "functions/intake.hpp"
#include "functions/uptake.hpp"
#include "functions/chassis.hpp"

#ifndef AUTON_HPP
#define AUTON_HPP

static Intake intake;
static Odom odom;
static Math math;
static Uptake uptake;
static Chassis chassis;

void homeRow(char color);
void center();
void rightCorner();
void skills();

#endif
