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

void skills () {
  uptake.move(100);
  delay(950);
  uptake.stop();
  intake.move(100);
  intake.waitUntillColor('R', 0.5);
  uptake.move(50);
  uptake.waitUntillIndexed(0.5); // Index ball
  uptake.stop();
  chassis.drive(26, 80, 1.5).waitUntilSettled();
  intake.stop();
  chassis.turnToAngle(-130, 80, 1.2).waitUntilSettled(); // Turn towards 1st goal
  chassis.drive(33, 85, 2.0).waitUntilSettled(); // Drive towards 1st goal
  uptake.move(100);
  uptake.waitUntillShot(1, 0.5); // Score in 1st goal
  uptake.stop();
  chassis.drive(-14, 80, 1.5).waitUntilSettled(); // Drive away from 1st goal
  uptake.move(50);
  intake.move(100);
  uptake.waitUntillIndexed(0.5); // Index ball
  uptake.stop();
  chassis.turnToAngle(0, 85, 1.5).waitUntilSettled();
  chassis.drive(48, 90, 2.0); // Drive towards middle of the field
  intake.waitUntillColor('R', 1.5); // Grab ball
  chassis.waitUntilSettled();
  intake.stop();
  chassis.turnToAngle(-90, 80, 1.5).waitUntilSettled(); // Turn towards 2nd goal
  chassis.drive(12, 80, 1.0).waitUntilSettled(); // Drive towards 2nd goal
  uptake.move(100);
  uptake.waitUntillShot(1, 0.7); // Score in 2nd goal
  uptake.stop();
  chassis.drive(-18, 90, 1.3).waitUntilSettled(); // Drive away from 2nd goal
  uptake.move(50);
  intake.move(100);
  uptake.waitUntillIndexed(0.5); // Index ball
  uptake.stop();
  intake.stop();
  chassis.turnToAngle(2.5, 80, 2.0).waitUntilSettled();
  chassis.drive(56, 90, 2.05); // Drive to far side of field
  intake.move(100);
  intake.waitUntillColor('R', 1.5); // Grab ball
  intake.move(20);
  chassis.waitUntilSettled();
  chassis.drive(-18, 80, 1.0).waitUntilSettled(); // Drive away from wall
  chassis.turnToAngle(-55, 80, 1.2).waitUntilSettled(); // Turn towards 3rd goal
  chassis.drive(36, 80, 1.5).waitUntilSettled(); // Drive to 3rd goal
  uptake.move(100);
  uptake.waitUntillShot(1, 0.7); // Score in 3rd goal
  uptake.stop();
  chassis.drive(-36, 80, 0.8).waitUntilSettled(); // Drive away from 3rd goal
  intake.move(100);
  uptake.move(100);
  uptake.waitUntillIndexed(0.5); // Index ball
  uptake.stop();
  chassis.turnToAngle(-90, 60, 0.8).waitUntilSettled();
  chassis.drive(36, 80, 1.3); // Drive at wall
  intake.waitUntillColor('R', 1.3); // Grab ball
  intake.move(30);
  chassis.waitUntilSettled();
  chassis.drive(-55, 90, 2.3).waitUntilSettled(); // Drive across the field (backwards)
  chassis.turnToAngle(0, 80, 1.2).waitUntilSettled(); // Turn to 4th goal
  intake.stop();
  chassis.drive(24, 80, 1.0).waitUntilSettled(); // Drive to 4th goal
  uptake.move(100);
  uptake.waitUntillShot(1, 0.7); // Score in 4th goal
  uptake.stop();
  chassis.drive(-12, 80, 0.7).waitUntilSettled(); // Drive away from 4th goal
  intake.move(100);
  uptake.move(100);
  uptake.waitUntillIndexed(0.5); // Index ball
  uptake.stop();
  chassis.turnToAngle(90, 80, 1.5).waitUntilSettled();
  chassis.drive(60, 90, 2.5).waitUntilSettled(); // Drive across the field
  chassis.drive(-12, 80, 1.0).waitUntilSettled(); // Drive away from the wall
  chassis.turnToAngle(50, 80, 1.3).waitUntilSettled(); // Turn to 5th goal
  intake.stop();
  chassis.drive(24, 80, 1.0).waitUntilSettled(); // Drive to 5th goal
  uptake.move(100);
  uptake.waitUntillShot(1, 0.7); // Score in 5th goal
  uptake.stop();
  chassis.drive(-12, 80, 0.8).waitUntilSettled(); // Drive away from 5th goal
  intake.move(100);
  uptake.move(100);
  uptake.waitUntillIndexed(0.5); // Index ball
  uptake.stop();

}

void homeRow(char color) {
  if (color == 'B') {
    color = 'R';
  } else if (color == 'R') {
    color = 'B';
  }
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
  intake.waitUntillColor(color, 1.0);
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
  intake.waitUntillColor(color, 5);
  chassis.waitUntilSettled();
  delay(200);
  uptake.stop();
  chassis.drive(-24, 100, 1.0); // Drive away from goal
  intake.stop();
  chassis.waitUntilSettled();
}

void autonomous() {

  //skills();
  homeRow('B');


}
