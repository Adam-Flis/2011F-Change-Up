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
  chassis.driveToPoint(0, 24, 90, 1.0);
  intake.waitUntillColor('R', 1.0); // Grab red ball infront of robot
  intake.move(30);
  chassis.waitUntilSettled();

  /* ********** 1st Goal ********** */
  chassis.turnToAngle(-135, 90, 1.1).waitUntilSettled(); // Turn towards 1st goal
  chassis.driveToPoint(-27, 5, 90, 1.2).waitUntilSettled(); // Drive towards 1st goal
  chassis.move(30, 'B'); // Constant pressure on 1st goal
  intake.move(-40);
  delay(100);
  uptake.move(100);
  delay(400); // Score in 1st goal
  uptake.stop();
  delay(400); // Ball settling time
  chassis.stop().brake();
  intake.stop();
  chassis.drive(-17.6, 90, 1.3); // Drive away from 1st goal
  delay(200);
  intake.move(100); // Reposition red ball
  uptake.move(-50);
  chassis.waitUntilSettled();


  /* ********** 2nd Goal ********** */
  chassis.turnToAngle(0, 90, 1.3); // Turn towards mid field
  uptake.stop();
  delay(100);
  uptake.waitUntillIndexedBottom(0.3); // Move red ball up into robot
  chassis.waitUntilSettled();
  chassis.driveToPoint(-14, 59, 90, 1.4); // Drive towards mid field
  intake.waitUntillColor('R', 1.4, false); // Grab red ball in front of 2nd goal
  chassis.waitUntilSettled();
  chassis.turnToAngle(-90, 90, 0.7); // Turn towards 2nd goal
  intake.move(100);
  uptake.waitUntillIndexedBottom(0.3); // Move red ball up into robot
  intake.stop();
  chassis.waitUntilSettled();
  chassis.driveToPoint(-25, 58.5, 90, 0.8).waitUntilSettled(); // Drive towards 2nd goal
  chassis.move(30, 'B'); // Constant pressure on 2nd goal
  delay(200);
  uptake.move(100);
  intake.move(20);
  delay(400); // Score in 2nd goal
  intake.stop();
  delay(300);
  uptake.stop();
  delay(400); // Ball settling time
  chassis.stop().brake();
  chassis.drive(-22, 85, 1.2); // Drive away from 2nd goal
  intake.move(-50);
  chassis.waitUntilSettled();
  intake.stop();

  /* ********** 3rd Goal ********** */
  chassis.turnToAngle(0, 90, 0.9).waitUntilSettled(); // Turn towards far field
  chassis.driveToPoint(0, 98, 90, 1.7); // Drive to far side of field
  intake.waitUntillColor('R', 1.5, false); // Grab red ball for 3rd goal ball
  chassis.waitUntilSettled();
  chassis.turnToAngle(-60, 90, 0.7); // Turn towards 3rd goal
  intake.move(100);
  uptake.waitUntillIndexedBottom(0.4); // Move red ball up into robot
  chassis.waitUntilSettled();
  intake.stop();
  chassis.driveToPoint(-26, 117, 90, 0.8).waitUntilSettled(); // Drive to 3rd goal
  chassis.move(30, 'B'); // Constant pressure on 3rd goal
  intake.move(-40);
  delay(100);
  uptake.move(100);
  delay(400); // Score in 3rd goal
  uptake.stop();
  delay(400); // Ball settling time
  chassis.stop().brake();
  chassis.turnToAngle(-45, 100, 1.1).waitUntilSettled(); // Align on goal
  chassis.drive(-33.5, 90, 1.2).waitUntilSettled(); // Drive away from 3rd goal

  /* ********** 4th Goal ********** */
  chassis.turnToAngle(-90, 90, 0.9).waitUntilSettled(); // Turn towards wall
  chassis.driveToPoint(-36, 92, 65, 1.4); // Drive to wall
  intake.waitUntillColor('R', 1.4, false); // Grab red wall ball
  intake.move(50);
  chassis.waitUntilSettled();
  chassis.drive(-60, 90, 1.8); // Drive across the field (backwards)
  intake.move(100);
  uptake.waitUntillIndexedBottom(0.4); // Move red ball up into robot
  intake.stop();
  chassis.waitUntilSettled();
  chassis.turnToAngle(0, 90, 0.5).waitUntilSettled(); // Turn to 4th goal
  chassis.driveToPoint(27, 115, 90, 0.8).waitUntilSettled(); // Drive to 4th goal
  chassis.move(30, 'B'); // Constant pressure on 4th goal
  uptake.move(100);
  delay(400); // Score in 4th goal
  uptake.stop();
  delay(400); // Ball settling time
  chassis.stop().brake();
  chassis.drive(-11, 90, 0.8); // Drive away from 4th goal
  intake.move(-50);
  chassis.waitUntilSettled();
  intake.stop();

  /* ********** 5th Goal ********** */
  chassis.turnToAngle(90, 90, 0.8).waitUntilSettled(); // Turn towards wall
  intake.stop();
  uptake.stop();
  chassis.driveToPoint(71, 110, 90, 1.8); // Drive across the field
  intake.waitUntillColor('R', 1.5, false); // Grab red ball
  intake.move(100);
  uptake.waitUntillIndexedBottom(0.4); // Move red ball up into robot
  intake.stop();
  chassis.waitUntilSettled();
  chassis.turnToAngle(45, 90, 0.5).waitUntilSettled(); // Turn to 5th goal
  chassis.driveToPoint(85, 117, 90, 0.8).waitUntilSettled(); // Drive to 5th goal
  chassis.move(30, 'B'); // Constant pressure on 5th goal
  intake.move(-50);
  delay(100);
  uptake.move(100);
  delay(500); // Score in 5th goal
  uptake.stop();
  delay(400); // Ball settling time
  chassis.stop().brake();
  chassis.turnToAngle(45, 100, 1.0).waitUntilSettled(); // Align on goal
  chassis.drive(-29, 85, 1.0).waitUntilSettled(); // Drive away from 5th goal

  /* ********** 6th Goal ********** */
  intake.stop();
  chassis.turnToAngle(90, 90, 0.8).waitUntilSettled(); // Turn towards wall
  chassis.driveToPoint(90, 90, 70, 1.5); // Drive to wall
  intake.waitUntillColor('R', 1.3); // Grab red wall ball
  intake.move(50);
  chassis.waitUntilSettled();
  chassis.drive(-13.5, 85, 1.0).waitUntilSettled(); // Drive away from wall
  intake.move(100);
  uptake.waitUntillIndexedBottom(0.4); // Move red ball up into robot
  intake.stop();
  chassis.waitUntilSettled();
  chassis.turnToAngle(180, 90, 0.8).waitUntilSettled(); // Turn towards mid field
  chassis.driveToPoint(80, 55, 90, 1.7); // Drive towards mid field
  intake.waitUntillColor('R', 1.4, false); // Grab red ball in front of 6th goal
  chassis.waitUntilSettled();
  chassis.turnToAngle(90, 90, 0.7); // Turn towards 6th goal
  intake.move(100);
  uptake.waitUntillIndexedBottom(0.4); // Move red ball up into robot
  intake.stop();
  chassis.waitUntilSettled();
  chassis.driveToPoint(90, 55, 90, 1.0); // Drive to 6th goal
  chassis.move(30, 'B'); // Constant pressure on 6th goal
  delay(300);
  uptake.move(100);
  intake.move(20);
  delay(400); // Score in 6th goal
  intake.stop();
  delay(300);
  uptake.stop();
  delay(400); // Ball settling time
  chassis.stop().brake();
  chassis.turnToAngle(90, 100, 1.0).waitUntilSettled(); // Align on goal
  chassis.drive(-18, 90, 0.9); // Drive away from 6th goal
  intake.move(-50);
  chassis.waitUntilSettled();
  intake.stop();

  /* ********** 7th Goal ********** */
  chassis.turnToAngle(-90, 90, 0.8).waitUntilSettled();
  chassis.driveToPoint(55, 60, 90, 1.0); // Drive towards middle goal
  intake.waitUntillColor('R', 0.6, false); // Grab red ball
  intake.move(100);
  uptake.waitUntillIndexedBottom(0.5); // Move red ball up into robot
  intake.stop();
  chassis.waitUntilSettled();
  chassis.turnToAngle(-80, 70, 0.5).waitUntilSettled();
  chassis.driveToPoint(35, 61, 90, 1.2); // Drive towards middle goal
  intake.move(-100);
  chassis.waitUntilSettled();
  chassis.move(100, 'R');
  delay(1000);
  uptake.move(100); // Score in middle 7th goal
  delay(700);
  uptake.stop();
  chassis.stop().brake();
  chassis.move(-100, 'R');
  chassis.move(-60, 'L');
  delay(1000);
  chassis.stop().brake();
}
