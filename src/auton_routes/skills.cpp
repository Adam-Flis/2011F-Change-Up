#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

/**
 *
 */
void skills () {

  intake.moveVolt(-100); // Deploy
  delay(150);
  intake.stop().brake();

  chassis.moveVel(40);
  delay(125);
  chassis.moveVel(40, 'R');
  chassis.moveVel(15, 'L');
  delay(650);
  chassis.moveVel(20);

  // Cycle 1st goal
  delay(150);
  uptake.moveVolt(100);
  delay(400);
  uptake.stop().brake();
  intake.moveVolt(-100);
  chassis.turnToAngle(-90, 100, 0.75).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  chassis.driveToPoint(11, 20, 100, 'X', 0.9, -90, true).withMultiplier(1.4).waitUntillSettled(); // Drive away from 1st goal

  chassis.turnToAngle(0, 90, 1.2).waitUntillSettled(); // Turn towards ball on line
  intake.moveVolt(100);
  chassis.driveToPoint(11, 76, 100, 'Y', 1.4, 0).withMultiplier(1.1); // Drive towards ball on line
  uptake.moveVolt(100).color('R', 1, 1.4).waitForColor().stop();
  intake.stop().brake();
  chassis.waitUntillSettled();

  chassis.turnToAngle(-45, 100, 0.6).waitUntillSettled(); // Turn towards 2nd goal
  chassis.driveToPoint(-8, 84, 100, 'X', 0.9, -45).withMinVel(35).waitUntillSettled(); // Drive towards 2nd goal
  chassis.moveVel(20);

  // Cycle 2nd goal
  uptake.moveVolt(100);
  delay(400);
  uptake.stop().brake();

  chassis.turnToAngle(-45, 100, 1.2).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  intake.moveVel(-100);
  chassis.driveToPoint(33.5, 36, 100, 'X', 1.8, -45, true).withMultiplier(1.15).waitUntillSettled();; // Drive away from 2nd goal

  chassis.turnToAngle(90, 90, 1.2).waitUntillSettled(); // Turn towards mid field
  chassis.driveToPoint(60, 36, 100, 'X', 1.0, 90).withMultiplier(1.15); // Drive towards mid field
  intake.moveVolt(100);
  uptake.moveVolt(80).color('R', 1, 1.0).waitForColor().stop();
  chassis.waitUntillSettled();

  chassis.turnToAngle(0, 100, 0.8).waitUntillSettled(); // Turn towards 3rd goal
  chassis.driveToPoint(60, 85, 100, 'Y', 1.0, 0).withMinVel(35).waitUntillSettled(); // Drive towards 3rd goal
  chassis.moveVel(20);

  // Cycle 3rd goal
  uptake.moveVolt(100);
  delay(150);
  intake.stop();
  delay(450);
  uptake.stop();
  intake.moveVolt(-100);

  chassis.turnToAngle(0, 100, 0.6).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  chassis.driveToPoint(60, 54, 100, 'Y', 1.4, 0, true).withMultiplier(1.2).waitUntillSettled(); // Drive away from 3rd goal
  chassis.turnToAngle(90, 90, 1.2).waitUntillSettled(); // Turn towards far field

  intake.moveVolt(100);
  chassis.driveToPoint(130, 56, 100, 'X', 1.7, 90).withMultiplier(1.15).withMinVel(40); // Drive towards red ball
  uptake.moveVolt(80).color('R', 1, 1.7).waitForColor().stop(); // Intake red ball
  chassis.waitUntillSettled();

  chassis.driveToPoint(90, 55, 100, 'X', 1.0, 90, true).withMultiplier(1.4).withMinVel(30).waitUntillSettled(); // Drive away from wall
  chassis.turnToAngle(45, 100, 0.65).waitUntillSettled(); // Turn towards 4th goal
  chassis.driveToPoint(130, 84, 100, 'Y', 1.0, 45).withMinVel(40).waitUntillSettled(); // Drive towards 4th goal
  chassis.moveVel(20);

  // Cycle 4th goal
  intake.moveVolt(-100);
  uptake.moveVolt(100);
  delay(400);
  uptake.stop();

  chassis.turnToAngle(45, 100, 1.0).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  chassis.driveToPoint(90, 55, 100, 'X', 1.0, 45, true).withMultiplier(1.4).withMinVel(30).waitUntillSettled(); // Drive away from goal
  chassis.turnToAngle(0, 100, 0.8).waitUntillSettled(); // Turn towards wall

  intake.moveVolt(100);
  chassis.driveToPoint(87, 90, 100, 'Y', 1.15, 0).withMultiplier(1.15).withMinVel(40); // Drive towards red ball on wall
  uptake.moveVolt(100).color('R', 1, 1.2).waitForColor().stop(); // Intake red ball
  chassis.waitUntillSettled();

  chassis.driveToPoint(87, 26.5, 100, 'Y', 1.8, 0, true).withMultiplier(1.3).withMinVel(30).waitUntillSettled(); // Drive away from wall

  chassis.turnToAngle(90, 100, 0.9).waitUntillSettled(); // Turn towards 5th goal
  chassis.driveToPoint(130, 26.5, 100, 'X', 0.7, 90).withMinVel(40).waitUntillSettled(); // Drive towards 5th goal
  chassis.moveVel(20);

  // Cycle 5th goal
  intake.moveVolt(-100);
  uptake.moveVolt(100);
  delay(500);
  uptake.stop();

  chassis.turnToAngle(90, 100, 0.8).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  chassis.driveToPoint(104, 27.5, 100, 'X', 0.9, 90, true).withMultiplier(1.4).waitUntillSettled(); // Drive away from goal

  chassis.turnToAngle(180, 90, 1.3).waitUntillSettled(); // Turn towards ball on line
  intake.moveVolt(100);
  chassis.driveToPoint(104, -24, 100, 'Y', 1.25, 180).withMultiplier(1.2).withMinVel(30); // Drive towards ball on line
  uptake.moveVolt(80).color('R', 1, 1.25).waitForColor().stop();
  intake.stop().brake();
  chassis.waitUntillSettled();

  chassis.turnToAngle(135, 100, 0.65).waitUntillSettled(); // Turn towards 6th goal
  chassis.driveToPoint(130, -55, 100, 'X', 0.9, 135).withMinVel(40).waitUntillSettled(); // Drive towards 6th goal
  chassis.moveVel(20);

  // Cycle 6th goal
  uptake.moveVolt(100);
  delay(400);
  uptake.stop().brake();

  chassis.turnToAngle(135, 100, 1.2).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  intake.moveVel(-100);
  chassis.driveToPoint(77, -3.5, 100, 'X', 1.8, 135, true).withMultiplier(1.15).waitUntillSettled(); // Drive away from 6th goal

  chassis.turnToAngle(270, 90, 1.3).waitUntillSettled(); // Turn towards mid field
  chassis.driveToPoint(60, -3.5, 100, 'X', 0.9, 270).withMultiplier(1.15); // Drive towards mid field
  intake.moveVolt(100);
  uptake.moveVolt(100).color('R', 1, 0.9).waitForColor().stop();
  chassis.waitUntillSettled();

  chassis.turnToAngle(180, 100, 0.75).waitUntillSettled(); // Turn towards 7th goal
  chassis.driveToPoint(60, -40, 100, 'Y', 0.9, 180).withMinVel(40).waitUntillSettled(); // Drive towards 7th goal
  chassis.moveVel(20);

  // Cycle 7th goal
  uptake.moveVolt(100);
  delay(150);
  intake.stop();
  delay(450);
  uptake.stop();
  intake.moveVolt(-100);

  chassis.turnToAngle(180, 100, 0.6).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  chassis.driveToPoint(60, -15, 100, 'Y', 1.4, 180, true).withMultiplier(1.2).waitUntillSettled(); // Drive away from 7th goal
  chassis.turnToAngle(270, 90, 1.4).waitUntillSettled(); // Turn towards far field

  intake.moveVolt(100);
  chassis.driveToPoint(-5, -20, 100, 'X', 1.6, 270).withMultiplier(1.15).withMinVel(40); // Drive towards red ball
  uptake.moveVolt(80).color('R', 1, 1.75).waitForColor().stop(); // Intake red ball
  chassis.waitUntillSettled();

  chassis.driveToPoint(22, -20, 100, 'X', 1.0, 270, true).withMultiplier(1.35).withMinVel(30).waitUntillSettled(); // Drive away from wall
  chassis.turnToAngle(225, 100, 0.65).waitUntillSettled(); // Turn towards 8th goal
  chassis.driveToPoint(0, -42, 100, 'Y', 1.0, 225).withMinVel(40).waitUntillSettled(); // Drive towards 8th goal
  chassis.moveVel(20);

  // Cycle 8th goal
  intake.moveVolt(-100);
  uptake.moveVolt(100);
  delay(400);
  uptake.stop();

  chassis.turnToAngle(225, 100, 1.0).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  chassis.driveToPoint(22, -22, 100, 'X', 1.1, 225, true).withMultiplier(1.4).waitUntillSettled(); // Drive away from goal
  chassis.turnToAngle(180, 100, 0.85).waitUntillSettled(); // Turn towards wall

  intake.moveVolt(100);
  chassis.driveToPoint(22, -44, 100, 'Y', 1.0, 180).withMultiplier(1.15).withMinVel(40); // Drive towards red ball on wall
  uptake.moveVolt(100).color('R', 1, 1.0).waitForColor().stop(); // Intake red ball
  chassis.waitUntillSettled();

  chassis.driveToPoint(15, -7, 100, 'X', 1.3, 180, true).withMultiplier(1.4).waitUntillSettled(); // Drive away from wall
  chassis.turnToAngle(75, 100, 1.0).waitUntillSettled(); // Turn towards middle goal
  chassis.driveToPoint(40, 16, 100, 'X', 1.0, 75).withMultiplier(1.4).waitUntillSettled(); // Drive towards middle goal

  intake.moveVolt(-100);
  chassis.turnToAngle(60, 100, 0.6).withMultiplier(2.0).waitUntillSettled(); // Turn towards middle goal
  uptake.moveVolt(100);
}
