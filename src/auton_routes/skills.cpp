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
  delay(700);
  chassis.moveVel(20);

  // Cycle 1st goal
  delay(150);
  uptake.moveVolt(100);
  delay(400);
  uptake.stop().brake();
  intake.moveVolt(-100);
  chassis.turnToAngle(-90, 100, 0.8).withMultiplier(2.0).waitUntillSettled(); // Align on goal
  chassis.driveToPoint(8, 15, 100, 'X', 0.8, -90, true).withMultiplier(1.4).waitUntillSettled(); // Drive away from 1st goal

  chassis.turnToAngle(0, 90, 1.4).waitUntillSettled(); // Turn towards ball on line
  intake.moveVolt(100);
  chassis.driveToPoint(8, 71, 100, 'Y', 1.5, 0).withMultiplier(1.15); // Drive towards ball on line
  uptake.moveVolt(100).color('R', 1, 1.5).waitForColor().stop();
  intake.stop().brake();
  chassis.waitUntillSettled();

  chassis.turnToAngle(-45, 100, 0.75).waitUntillSettled(); // Turn towards 2nd goal
  chassis.driveToPoint(-8, 84, 100, 'X', 1.0, -45).withMinVel(40).waitUntillSettled(); // Drive towards 2nd goal
  chassis.moveVel(20);

  // Cycle 2nd goal
  uptake.moveVolt(100);
  delay(500);
  uptake.stop().brake();

  chassis.turnToAngle(-45, 100, 1.2).withMultiplier(2.0).waitUntillSettled(); // Align on goal
  intake.moveVel(-100);
  chassis.driveToPoint(32, 36, 100, 'X', 2.0, -45, true).withMultiplier(1.2).waitUntillSettled();; // Drive away from 2nd goal

  chassis.turnToAngle(90, 90, 1.4).waitUntillSettled(); // Turn towards mid field
  chassis.driveToPoint(52.5, 45.5, 100, 'X', 1.0, 90).withMultiplier(1.4); // Drive towards mid field
  intake.moveVolt(100);
  uptake.moveVolt(100).color('R', 1, 1.0).waitForColor().stop();
  chassis.waitUntillSettled();

  chassis.turnToAngle(0, 100, 1.3).waitUntillSettled(); // Turn towards 3rd goal
  chassis.driveToPoint(52.5, 85, 100, 'Y', 1.0, 0).withMinVel(40).waitUntillSettled(); // Drive towards 3rd goal
  chassis.moveVel(20);

  // Cycle 3rd goal
  uptake.moveVolt(100);
  delay(150);
  intake.stop();
  delay(500);
  uptake.stop();
  intake.moveVolt(-100);

  chassis.turnToAngle(0, 100, 0.6).withMultiplier(2.0).waitUntillSettled(); // Align on goal
  chassis.driveToPoint(55.5, 55, 100, 'Y', 1.4, 0, true).withMultiplier(1.2).waitUntillSettled(); // Drive away from 3rd goal
  chassis.turnToAngle(90, 90, 1.4).waitUntillSettled(); // Turn towards far field

  intake.moveVolt(100);
  chassis.driveToPoint(125, 55, 100, 'X', 1.8, 90).withMultiplier(1.2).withMinVel(35); // Drive towards red ball
  uptake.moveVolt(100).color('R', 1, 1.8).waitForColor().stop(); // Intake red ball
  chassis.waitUntillSettled();

  chassis.driveToPoint(97, 55, 100, 'X', 1.3, 90, true).withMultiplier(1.4).waitUntillSettled(); // Drive away from wall
  chassis.turnToAngle(45, 100, 0.65).waitUntillSettled(); // Turn towards 4th goal
  chassis.driveToPoint(120, 84, 100, 'Y', 1.0, 45).withMinVel(40).waitUntillSettled(); // Drive towards 4th goal
  chassis.moveVel(20);

  // Cycle 4th goal
  intake.moveVolt(-100);
  uptake.moveVolt(100);
  delay(500);
  uptake.stop();

  chassis.turnToAngle(45, 100, 1.0).withMultiplier(2.0).waitUntillSettled(); // Align on goal
  chassis.driveToPoint(87, 80, 100, 'X', 1.2, 45, true).withMultiplier(1.4).waitUntillSettled(); // Drive away from goal
  chassis.turnToAngle(0, 100, 1.3).waitUntillSettled(); // Turn towards wall

  intake.moveVolt(100);
  chassis.driveToPoint(87, 90, 100, 'Y', 1.3, 0).withMultiplier(1.3).withMinVel(30); // Drive towards red ball on wall
  uptake.moveVolt(100).color('R', 1, 1.3).waitForColor().stop(); // Intake red ball
  chassis.waitUntillSettled();

  chassis.driveToPoint(87, 28, 100, 'Y', 2.2, 0, true).withMultiplier(1.2).waitUntillSettled(); // Drive away from wall

  chassis.turnToAngle(90, 100, 1.0).waitUntillSettled(); // Turn towards 5th goal
  chassis.driveToPoint(120, 28, 100, 'X', 1.2, -270).withMinVel(40).waitUntillSettled(); // Drive towards 5th goal
  chassis.moveVel(20);

  // Cycle 5th goal
  intake.moveVolt(-100);
  uptake.moveVolt(100);
  delay(600);
  uptake.stop();

  chassis.turnToAngle(90, 100, 0.8).withMultiplier(2.0).waitUntillSettled(); // Align on goal
  chassis.driveToPoint(110, 28, 100, 'X', 1.0, 90, true).withMultiplier(1.4).waitUntillSettled(); // Drive away from goal

  chassis.turnToAngle(180, 90, 1.4).waitUntillSettled(); // Turn towards ball on line
  intake.moveVolt(100);
  // chassis.driveToPoint(107, -20, 100, 'Y', 2.0, 0).withMultiplier(1.1); // Drive towards ball on line
  // uptake.moveVolt(100).color('R', 1, 2.0).waitForColor().stop();
  // intake.stop().brake();
  // chassis.waitUntillSettled();
  //
  // chassis.turnToAngle(-225, 100, 0.75).waitUntillSettled(); // Turn towards 6th goal
  // chassis.driveToPoint(120, -48, 100, 'X', 1.0, -225).withMinVel(40).waitUntillSettled(); // Drive towards 6th goal
  // chassis.moveVel(20);
  //
  // // Cycle 6th goal
  // uptake.moveVolt(100);
  // delay(600);
  // uptake.stop().brake();


}
