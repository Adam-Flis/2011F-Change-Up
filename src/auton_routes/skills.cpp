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
  delay(500); // Deploy hood
  chassis.driveToPoint(0, 26, 90, 1.1);
  intake.move(100); // Grab red ball infront of robot
  chassis.waitUntilSettled();
  intake.stop();

  /* ********** 1st Goal ********** */
  chassis.turnToAngle(-135, 85, 1.0).waitUntilSettled(); // Turn towards 1st goal
  chassis.driveToPoint(-23.5, 0.5, 90, 1.4).waitUntilSettled(); // Drive towards 1st goal
  chassis.move('B', 40); // Constant power on 1st goal
  delay(200);
  uptake.waitUntilShot(1, 0.8); // Score in 1st goal
  chassis.turnToAngle(-135, 100, 1.2).waitUntilSettled(); // Align on 1st goal
  intake.stop();
  chassis.drive(-12, 80, 1.2); // Drive away from 1st goal
  delay(100);
  intake.move(100);
  uptake.waitUntilIndexedMiddle(1.2); // Reposition red ball
  intake.stop();
  chassis.waitUntilSettled();

  /* ********** 2nd Goal ********** */
  chassis.turnToAngle(0, 80, 1.2); // Turn towards mid field
  uptake.move(-50);
  intake.move(50);
  chassis.waitUntilSettled();
  uptake.stop();
  chassis.driveToPoint(-14.5, 58, 90, 1.4); // Drive towards mid field
  intake.move(100); // Grab red ball in front of 2nd goal
  chassis.waitUntilSettled();
  chassis.turnToAngle(-90, 85, 1.0); // Turn towards 2nd goal
  uptake.waitUntilIndexedTop(1.2); // Index both red balls
  chassis.waitUntilSettled();
  intake.stop();
  chassis.driveToPoint(-27, 58, 90, 1.0).waitUntilSettled(); // Drive towards 2nd goal
  chassis.move('B', 40); // Constant power on 2nd goal
  uptake.waitUntilShot(2, 1.3); // Score in 2nd goal
  chassis.turnToAngle(-90, 100, 1.2).waitUntilSettled(); // Align on 2nd goal
  chassis.drive(-17, 85, 1.2); // Drive away from 2nd goal
  intake.move(-100);
  chassis.waitUntilSettled();
  intake.stop();

  /* ********** 3rd Goal ********** */
  chassis.turnToAngle(0, 85, 1.0).waitUntilSettled(); // Turn towards far field
  chassis.driveToPoint(0, 100, 90, 1.7); // Drive to far side of field
  intake.move(100);
  uptake.waitUntilIndexedMiddle(1.7); // Grab red ball for 3rd goal ball
  intake.stop();
  chassis.waitUntilSettled();
  chassis.turnToAngle(-60, 80, 0.8).waitUntilSettled(); // Turn towards 3rd goal
  chassis.driveToPoint(-30, 115, 90, 1.0).waitUntilSettled(); // Drive to 3rd goal
  chassis.move('B', 40); // Constant power on 3rd goal
  delay(200);
  uptake.waitUntilShot(1, 0.8); // Score in 3rd goal
  chassis.turnToAngle(-45, 100, 1.2).waitUntilSettled(); // Align on 3rd goal
  chassis.drive(-31, 90, 1.2); // Drive away from 3rd goal
  intake.move(-100);
  chassis.waitUntilSettled();
  intake.stop();

  /* ********** 4th Goal ********** */
  chassis.turnToAngle(-90, 85, 1.0).waitUntilSettled(); // Turn towards wall
  chassis.driveToPoint(-32.5, 92, 65, 1.4); // Drive to wall
  intake.move(100);
  uptake.waitUntilIndexedMiddle(1.4); // Grab red wall ball
  intake.stop();
  chassis.waitUntilSettled();
  chassis.drive(-58, 85, 1.8).waitUntilSettled(); // Drive across the field (backwards)
  chassis.turnToAngle(0, 90, 1.0).waitUntilSettled(); // Turn to 4th goal
  chassis.driveToPoint(36, 115, 80, 1.0).waitUntilSettled(); // Drive to 4th goal
  chassis.move('B', 40); // Constant power on 4th goal
  delay(200);
  uptake.waitUntilShot(1, 0.8); // Score in 4th goal
  chassis.turnToAngle(0, 100, 1.2).waitUntilSettled(); // Align on 4th goal
  chassis.drive(-11, 90, 0.8); // Drive away from 4th goal
  intake.move(-100);
  chassis.waitUntilSettled();
  intake.stop();

  /* ********** 5th Goal ********** */
  chassis.turnToAngle(90, 90, 0.8).waitUntilSettled(); // Turn towards wall
  intake.move(100);
  chassis.driveToPoint(67, 100, 90, 1.8).waitUntilSettled(); // Drive across the field
  uptake.waitUntilIndexedMiddle(1.0); // Index red ball
  intake.stop();
  chassis.turnToAngle(45, 85, 0.5).waitUntilSettled(); // Turn to 5th goal
  chassis.driveToPoint(82, 120, 90, 0.9).waitUntilSettled(); // Drive to 5th goal
  chassis.move('B', 40); // Constant power on 5th goal
  delay(200);
  uptake.waitUntilShot(1, 0.8); // Score in 5th goal
  chassis.turnToAngle(45, 100, 1.2).waitUntilSettled(); // Align on goal
  chassis.drive(-26, 85, 1.3); // Drive away from 5th goal
  intake.move(-100);
  chassis.waitUntilSettled();
  intake.stop();

  /* ********** 6th Goal ********** */
  chassis.turnToAngle(90, 90, 0.8).waitUntilSettled(); // Turn towards wall
  chassis.driveToPoint(84.5, 100, 65, 1.4); // Drive to wall
  intake.move(100);
  uptake.waitUntilIndexedMiddle(1.4); // Grab red wall ball
  intake.stop();
  chassis.waitUntilSettled();
  chassis.drive(-13.5, 85, 1.0).waitUntilSettled(); // Drive away from wall
  chassis.turnToAngle(180, 90, 0.8); // Turn towards mid field
  uptake.move(-50);
  intake.move(50);
  chassis.waitUntilSettled();
  uptake.stop();
  chassis.driveToPoint(71, 71, 90, 2.0); // Drive towards mid field
  intake.move(100); // Grab red ball in front of 6th goal
  chassis.waitUntilSettled();
  chassis.turnToAngle(90, 90, 1.0); // Turn towards 6th
  uptake.waitUntilIndexedTop(1.2); // Index both red balls
  chassis.waitUntilSettled();
  intake.stop();
  chassis.driveToPoint(80, 71, 90, 1.0).waitUntilSettled(); // Drive to 6th goal
  chassis.move('B', 40); // Constant power on 6th goal
  delay(200);
  uptake.waitUntilShot(2, 1.3); // Score in 6th goal
  chassis.turnToAngle(90, 100, 1.2).waitUntilSettled(); // Align on goal
  chassis.drive(-15, 80, 0.9); // Drive away from 6th goal
  intake.move(-100);
  chassis.waitUntilSettled();
  intake.stop();

  /* ********** 7th Goal ********** */
  chassis.turnToAngle(-90, 90, 0.8).waitUntilSettled();
  // chassis.driveToPoint(55, 60, 90, 1.0); // Drive towards middle goal
  // intake.waitUntilColor('R', 0.6); // Grab red ball
  // intake.move(100);
  // uptake.waitUntilIndexedBottom(0.5); // Move red ball up into robot
  // intake.stop();
  // chassis.waitUntilSettled();
  // chassis.turnToAngle(-80, 70, 0.5).waitUntilSettled();
  // chassis.driveToPoint(35, 61, 90, 1.2); // Drive towards middle goal
  // intake.move(-100);
  // chassis.waitUntilSettled();
  // chassis.move(100, 'R');
  // delay(1000);
  // uptake.move(100); // Score in middle 7th goal
  // delay(700);
  // uptake.stop();
  // chassis.stop().brake();
  // chassis.move(-100, 'R');
  // chassis.move(-60, 'L');
  // delay(1000);
  // chassis.stop().brake();
}
