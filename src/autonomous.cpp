#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"
#include "functions/intake.hpp"
#include "functions/uptake.hpp"

static Chassis chassis;
static Intake intake;
static Odom odom;
static Math math;
static Uptake uptake;

void autonomous() {
  uptake.move(100);
  delay(950);
  uptake.stop();
  intake.move(100);
  chassis.drive(26, 80, 1.5);
  intake.waitUntillColor('R', 1.5);
  uptake.move(100);
  delay(150);
  uptake.stop();
  intake.move(30);
  chassis.waitUntilSettled();
  chassis.turnToAngle(-130, 80, 1.2).waitUntilSettled();
  chassis.drive(35, 85, 1.9).waitUntilSettled(); // Drive towards 1st goal
  intake.move(-30);
  uptake.move(100);
  delay(1000); // Score red ball in 1st goal
  uptake.stop();
  intake.move(100);
  chassis.drive(-14, 80, 1.0).waitUntilSettled(); // Drive away from 1st goal
  chassis.turnToAngle(0, 80, 1.5).waitUntilSettled();
  uptake.move(100);
  delay(200);
  uptake.stop();
  chassis.drive(52, 85, 2.0); // Drive towards middle of the field
  intake.waitUntillColor('R', 2);
  chassis.waitUntilSettled();
  chassis.turnToAngle(-90, 80, 1.0).waitUntilSettled();
  chassis.drive(12, 65, 1.0).waitUntilSettled(); // Drive towards 2nd goal
  intake.move(0);
  uptake.move(100);
  delay(1000); // Score red ball in 2nd goal
  intake.stop();
  uptake.stop();
  chassis.drive(-15, 60, 1.0).waitUntilSettled(); // Drive away from 2nd goal
  intake.move(100);
  intake.waitUntillColor('R', 0.5);
  uptake.move(100);
  delay(300);
  uptake.stop();
  intake.stop();
  chassis.turnToAngle(0, 80, 1.5).waitUntilSettled();
  chassis.drive(53, 85, 2.1); // Drive to far side of field
  intake.move(100);
  intake.waitUntillColor('R', 2.0);
  intake.stop();
  chassis.waitUntilSettled();
  chassis.turnToAngle(-45, 60, 1.0).waitUntilSettled(); // Turn towards 3rd goal

}

void homeRow() {
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
