#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"
#include "functions/intake.hpp"
#include "functions/uptake.hpp"

void autonomous() {
  Chassis chassis;
  Intake intake;
  Odom odom;
  Math math;
  Uptake uptake;

  uptake.move(100);
  delay(950);
  uptake.stop();
  chassis.driveToPoint(0, 29.7, 85, 1.35).waitUntilSettled();
  chassis.turnToAngle(92.5, 85, 1.25).waitUntilSettled();
  intake.move(100);
  chassis.driveToPoint(34, 23, 90, 1.3); // Drive towards goal
  delay(400);
  uptake.move(100); // Sends ball infront of goal up
  delay(650);
  intake.move(40);
  intake.waitUntillColor('R', 1.0);
  delay(150);
  uptake.stop();
  chassis.waitUntilSettled();
  chassis.driveToPoint(0, 18, 85, 1.65, true); // Drive away from goal
  intake.move(-100);
  uptake.move(-100);
  chassis.waitUntilSettled();
  uptake.stop();
  intake.stop();
  chassis.turnToAngle(-135, 80, 1.2).waitUntilSettled();
  chassis.driveToPoint(-44, -16, 85, 2.1).waitUntilSettled(); // Drive across the field
  chassis.turnToAngle(170, 65, 0.4).waitUntilSettled(); // Turn towards goal
  intake.move(100);
  chassis.driveToPoint(-35, -53, 90, 1.1); // Drive towards goal
  delay(100);
  uptake.move(100); // Sends ball infront of goal up
  delay(850);
  intake.move(40);
  intake.waitUntillColor('R', 5);
  chassis.waitUntilSettled();
  delay(150);
  uptake.stop();
  chassis.drive(-24, 100, 1.0); // Drive away from goal
  intake.stop();
  chassis.waitUntilSettled();
}
