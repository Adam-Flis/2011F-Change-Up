#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

/**
 * Completes 4 rows and 7 red owned goals
 * Descores 2 blue balls
 * Points scored: 31 red - 13 blue + 63 = 81
 */
void skills () {

  intake.brake();
  uptake.brake();

  intake.move(100);
  delay(500); // Deploy hood
  chassis.driveToPoint(0, 26, 90, 1.1);
  intake.move(100); // Grab red ball infront of robot
  chassis.waitUntilSettled();
  intake.stop();

  /* ********** 1st Goal ********** */
  chassis.turnToAngle(-135, 85, 0.9).waitUntilSettled(); // Turn towards 1st goal
  chassis.driveToPoint(-23.5, 0.5, 90, 1.3).waitUntilSettled(); // Drive towards 1st goal
  chassis.move(30, 'B'); // Constant power on 1st goal
  delay(100);
  uptake.waitUntilShot(1, 0.8); // Score in 1st goal
  chassis.stop().brake();
  chassis.turnToAngle(-135, 100, 0.6).waitUntilSettled(); // Align on 1st goal
  intake.move(-50);
  chassis.drive(-15, 95, 1.1); // Drive away from 1st goal
  delay(200);
  intake.move(100);
  uptake.waitUntilIndexedMiddle(1.2); // Reposition red ball
  intake.stop();
  chassis.waitUntilSettled();

  /* ********** 2nd Goal ********** */
  chassis.turnToAngle(0, 85, 1.2); // Turn towards mid field
  uptake.move(-50);
  intake.move(70);
  chassis.waitUntilSettled();
  uptake.stop();
  intake.move(100); // Grab red ball in front of 2nd goal
  chassis.driveToPoint(-17, 57, 90, 1.4).waitUntilSettled(); // Drive towards mid field
  chassis.turnToAngle(-90, 85, 1.0); // Turn towards 2nd goal
  uptake.waitUntilIndexedTop(1.2); // Index both red balls
  chassis.waitUntilSettled();
  intake.stop();
  chassis.driveToPoint(-26, 57, 90, 0.9).waitUntilSettled(); // Drive towards 2nd goal
  chassis.move(30, 'B'); // Constant power on 2nd goal
  delay(100);
  uptake.waitUntilShot(2, 1.3); // Score in 2nd goal
  chassis.stop().brake();
  chassis.turnToAngle(-90, 100, 0.7).waitUntilSettled(); // Align on 2nd goal
  intake.move(-100);
  chassis.drive(-22, 90, 1.2); // Drive away from 2nd goal
  chassis.waitUntilSettled();
  intake.stop();

  /* ********** 3rd Goal ********** */
  chassis.turnToAngle(0, 75, 1.2).waitUntilSettled(); // Turn towards far field
  chassis.driveToPoint(0, 108, 90, 2.0); // Drive to far side of field
  intake.move(100);
  uptake.waitUntilIndexedMiddle(1.8); // Grab red ball for 3rd goal ball
  chassis.waitUntilSettled();
  chassis.turnToAngle(-70, 85, 1.1); // Turn towards 3rd goal
  uptake.waitUntilIndexedMiddle(1.0); // Make sure red ball is inside robot
  intake.stop();
  chassis.waitUntilSettled();
  chassis.driveToPoint(-30, 118, 90, 1.0).waitUntilSettled(); // Drive to 3rd goal
  chassis.move(30, 'B'); // Constant power on 3rd goal
  delay(100);
  uptake.waitUntilShot(1, 0.9); // Score in 3rd goal
  chassis.stop().brake();
  chassis.turnToAngle(-45, 100, 1.1).waitUntilSettled(); // Align on 3rd goal
  chassis.drive(-35, 90, 1.4); // Drive away from 3rd goal
  intake.move(-100);
  chassis.waitUntilSettled();
  intake.stop();

  /* ********** 4th Goal ********** */
  chassis.turnToAngle(-90, 90, 0.8).waitUntilSettled(); // Turn towards wall
  chassis.driveToPoint(-33.5, 92, 75, 1.4); // Drive to wall
  intake.move(100);
  uptake.waitUntilIndexedMiddle(1.4); // Grab red wall ball
  intake.stop();
  chassis.waitUntilSettled();
  delay(100);
  chassis.drive(-61, 85, 1.8).waitUntilSettled(); // Drive across the field (backwards)
  chassis.turnToAngle(0, 90, 1.0).waitUntilSettled(); // Turn to 4th goal
  chassis.driveToPoint(36, 114, 90, 0.8).waitUntilSettled(); // Drive to 4th goal
  chassis.move(30, 'B'); // Constant power on 4th goal
  delay(100);
  uptake.waitUntilShot(1, 0.8); // Score in 4th goal
  chassis.stop().brake();
  chassis.turnToAngle(0, 100, 0.9).waitUntilSettled(); // Align on 4th goal
  intake.move(-100);
  chassis.drive(-11, 90, 0.8); // Drive away from 4th goal
  chassis.waitUntilSettled();
  intake.stop();

  /* ********** 5th Goal ********** */
  chassis.turnToAngle(90, 85, 1.0).waitUntilSettled(); // Turn towards wall
  intake.move(100);
  chassis.driveToPoint(73, 100, 90, 1.4).waitUntilSettled(); // Drive across the field
  uptake.waitUntilIndexedMiddle(1.3); // Index red ball
  intake.stop();
  chassis.turnToAngle(47, 85, 0.6).waitUntilSettled(); // Turn to 5th goal
  chassis.driveToPoint(93, 118, 90, 1.2).waitUntilSettled(); // Drive to 5th goal
  chassis.move(30, 'B'); // Constant power on 5th goal
  delay(100);
  uptake.waitUntilShot(1, 0.8); // Score in 5th goal
  chassis.stop().brake();
  chassis.turnToAngle(45, 100, 1.0).waitUntilSettled(); // Align on goal
  chassis.drive(-34, 90, 1.9); // Drive away from 5th goal
  intake.move(-100);
  chassis.waitUntilSettled();
  intake.stop();

  /* ********** 6th Goal ********** */
  chassis.turnToAngle(90, 90, 0.8).waitUntilSettled(); // Turn towards wall
  chassis.driveToPoint(95, 92, 75, 1.6); // Drive to wall
  intake.move(100);
  uptake.waitUntilIndexedMiddle(1.6); // Grab red wall ball
  intake.stop();
  chassis.waitUntilSettled();
  chassis.drive(-14, 85, 1.2).waitUntilSettled(); // Drive away from wall
  chassis.turnToAngle(180, 85, 0.9); // Turn towards mid field
  uptake.move(-50);
  intake.move(70);
  chassis.waitUntilSettled();
  uptake.stop();
  chassis.driveToPoint(73, 63, 90, 2.1); // Drive towards mid field
  intake.move(100); // Grab red ball in front of 6th goal
  chassis.waitUntilSettled();
  chassis.turnToAngle(90, 90, 1.0); // Turn towards 6th goal
  uptake.waitUntilIndexedTop(1.0); // Index both red balls
  chassis.waitUntilSettled();
  intake.stop();
  chassis.driveToPoint(95, 63, 90, 1.0).waitUntilSettled(); // Drive to 6th goal
  chassis.move(30, 'B'); // Constant power on 6th goal
  delay(100);
  uptake.waitUntilShot(2, 1.3); // Score in 6th goal
  chassis.stop().brake();
  chassis.turnToAngle(90, 100, 1.0).waitUntilSettled(); // Align on goal
  intake.move(-100);
  chassis.drive(-14, 85, 1.0); // Drive away from 6th goal
  chassis.waitUntilSettled();
  intake.stop();

  /* ********** 7th Goal ********** */
  chassis.turnToAngle(-90, 70, 1.4).waitUntilSettled();
  chassis.driveToPoint(50, 63, 90, 1.1); // Drive towards middle goal
  intake.move(100);
  uptake.waitUntilIndexedMiddle(1.1); // Move red ball up into robot
  chassis.waitUntilSettled();
  chassis.turnToAngle(-77, 90, 1.0); // Slight turn towards middle goal
  uptake.waitUntilIndexedMiddle(0.9); // Make sure red ball is inside robot
  intake.stop();
  chassis.waitUntilSettled();
  intake.move(-100);
  chassis.driveToPoint(42, 62.5, 95, 1.0).waitUntilSettled(); // Drive towards middle goal and poke out 1st blue ball
  chassis.drive(-6, 100, 0.5).waitUntilSettled(); // Drive away from middle to reset
  delay(100);
  chassis.drive(8, 100, 0.5).waitUntilSettled(); // Poke out 2nd blue ball
  delay(100);
  chassis.move(100, 'R'); // Constant pressure on middle goal
  delay(500);
  uptake.waitUntilShot(1, 1.0); // Score in middle 7th goal
  delay(100);
  chassis.move(-100, 'R'); // Do a curved drive away from the middle goal
  chassis.move(-60, 'L');
  delay(1000);
  chassis.stop().brake();
  intake.stop();
}
