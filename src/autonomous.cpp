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
  delay(700);
  uptake.stop();
  chassis.driveToPoint(0, 30, 85, 1.35).waitUntilSettled();
  chassis.turnToAngle(92.5, 85, 1.2).waitUntilSettled();
  intake.move(100);
  chassis.driveToPoint(39, 29, 90, 1.3); // Drive towards goal
  delay(500);
  uptake.move(100); // Sends ball infront of goal up
  delay(600);
  intake.move(40);
  delay(800);
  uptake.stop();
  chassis.waitUntilSettled();
  chassis.driveToPoint(0, 18, 85, 1.5, true); // Drive away from goal
  intake.move(-100);
  uptake.move(-100);
  chassis.waitUntilSettled();
  uptake.stop();
  intake.stop();
  chassis.turnToAngle(-135, 80, 1.1).waitUntilSettled();
  chassis.driveToPoint(-45, -17, 85, 2.0).waitUntilSettled(); // Drive across the field
  chassis.turnToAngle(170, 60, 0.5).waitUntilSettled(); // Turn towards goal
  intake.move(100);
  chassis.driveToPoint(-35, -53, 85, 1.2); // Drive towards goal
  delay(100);
  uptake.move(100); // Sends ball infront of goal up
  delay(700);
  intake.move(40);
  delay(900);
  chassis.waitUntilSettled();
  uptake.stop();
  chassis.drive(-24, 90, 1.5); // Drive away from goal
  intake.stop();
  chassis.waitUntilSettled();
}
