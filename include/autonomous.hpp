#include "functions/chassis.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"
#include "functions/intake.hpp"
#include "functions/uptake.hpp"

#ifndef AUTON_HPP
#define AUTON_HPP

static Chassis chassis;
static Intake intake;
static Odom odom;
static Math math;
static Uptake uptake;

void homeRow(char color);
void skills();

#endif
