#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

/**
 * Goal: Completes 4 rows and 7 red owned goals
 * Goal: Points scored: 31 red - 14 blue + 63 = 80
 * Accomplished: Completes 2 rows and 5 red owned goals
 * Accomplished: Points scored: 17 red - 15 blue + 63 = 65
 */
void skills () {

  intake.move(-100);
  delay(500); // Deploy hood and shoot preload ball into middle goal
  chassis.driveToPoint(0, 24, 90, 1.1);
  intake.waitUntillColor('R', 1.0);
  intake.move(50);
  chassis.waitUntilSettled();
  intake.stop();

  /* ********** 1st Goal ********** */
  chassis.turnToAngle(-135, 90, 1.1).waitUntilSettled(); // Turn towards 1st goal
  chassis.driveToPoint(-27, 5, 90, 1.2).waitUntilSettled(); // Drive towards 1st goal
  intake.move(-10);
  uptake.move(100); // Score in 1st goal
  delay(400);
  intake.stop();
  uptake.stop();
  delay(400);
  chassis.drive(-17.5, 90, 1.6); // Drive away from 1st goal
  delay(100);
  intake.move(100);
  chassis.waitUntilSettled();
  uptake.move(-30);

  /* ********** 2nd Goal ********** */
  chassis.turnToAngle(0, 90, 1.3).waitUntilSettled();
  uptake.move(100);
  chassis.driveToPoint(-14, 59, 90, 1.4); // Drive towards middle of the field
  delay(200);
  uptake.stop();
  intake.waitUntillColor('R', 1.8); // Grab ball
  intake.move(100);
  chassis.waitUntilSettled();
  chassis.turnToAngle(-90, 90, 0.7).waitUntilSettled(); // Turn towards 2nd goal
  chassis.driveToPoint(-25, 59, 90, 0.8).waitUntilSettled(); // Drive towards 2nd goal
  uptake.move(100); // Score in 2nd goal
  intake.waitUntillColor('B', 0.5);
  delay(250);
  uptake.stop();
  delay(300);
  chassis.drive(-21, 90, 1.2); // Drive away from 2nd goal
  delay(100);
  uptake.move(-100);
  intake.move(-100);
  chassis.waitUntilSettled();

  /* ********** 3rd Goal ********** */
  chassis.turnToAngle(0, 90, 1.0).waitUntilSettled();
  uptake.stop();
  intake.stop();
  chassis.driveToPoint(0, 96, 90, 1.4); // Drive to far side of field
  intake.waitUntillColor('R', 1.4); // Grab ball
  intake.move(30);
  chassis.waitUntilSettled();
  chassis.turnToAngle(-55, 90, 0.4).waitUntilSettled(); // Turn towards 3rd goal
  chassis.driveToPoint(-26, 117, 90, 1.4).waitUntilSettled(); // Drive to 3rd goal
  intake.move(100);
  uptake.move(100); // Score in 3rd goal
  delay(400);
  intake.stop();
  uptake.stop();
  delay(300);
  chassis.drive(-30, 80, 0.8); // Drive away from 3rd goal
  delay(100);
  intake.move(-100);
  uptake.move(-100);
  chassis.waitUntilSettled();

  /* ********** 4th Goal ********** */
  chassis.turnToAngle(-90, 60, 0.8).waitUntilSettled();
  // chassis.drive(36, 80, 1.3); // Drive at wall
  // intake.waitUntillColor('R', 1.3); // Grab ball
  // intake.move(30);
  // chassis.waitUntilSettled();
  // chassis.drive(-55, 90, 2.3).waitUntilSettled(); // Drive across the field (backwards)
  // chassis.turnToAngle(0, 80, 1.2).waitUntilSettled(); // Turn to 4th goal
  // intake.stop();
  // chassis.drive(24, 80, 1.0).waitUntilSettled(); // Drive to 4th goal
  // uptake.move(100);
  // uptake.waitUntillShot(1, 0.7); // Score in 4th goal
  // uptake.stop();
  // chassis.drive(-12, 80, 0.7).waitUntilSettled(); // Drive away from 4th goal
  // intake.move(100);
  // uptake.move(100);
  // uptake.waitUntillIndexedBottom(0.5); // Index ball
  // uptake.stop();
  //
  // /* ********** 5th Goal ********** */
  // chassis.turnToAngle(90, 80, 1.5).waitUntilSettled();
  // chassis.drive(60, 90, 2.5).waitUntilSettled(); // Drive across the field
  // chassis.drive(-12, 80, 1.0).waitUntilSettled(); // Drive away from the wall
  // chassis.turnToAngle(50, 80, 1.3).waitUntilSettled(); // Turn to 5th goal
  // intake.stop();
  // chassis.drive(24, 80, 1.0).waitUntilSettled(); // Drive to 5th goal
  // uptake.move(100);
  // uptake.waitUntillShot(1, 0.7); // Score in 5th goal
  // uptake.stop();
  // chassis.drive(-12, 80, 0.8).waitUntilSettled(); // Drive away from 5th goal
  // intake.move(100);
  // uptake.move(100);
  // uptake.waitUntillIndexedBottom(0.5); // Index ball
  // uptake.stop();
}
