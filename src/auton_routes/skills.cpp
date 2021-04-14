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
  chassis.moveVel(15);

  // Cycle 1st goal
  delay(150);
  uptake.moveVolt(100);
  delay(500);
  uptake.stop().brake();
  intake.moveVolt(-100);
  chassis.turnToAngle(-90, 100, 0.6).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  chassis.driveToPoint(8, 15, 100, 'X', 0.8, -90, true).withMultiplier(1.4).waitUntillSettled(); // Drive away from 1st goal

  chassis.turnToAngle(0, 100, 1.45).waitUntillSettled(); // Turn towards ball on line
  intake.moveVolt(100);
  chassis.driveToPoint(8, 71, 100, 'Y', 1.5, 0); // Drive towards ball on line
  uptake.moveVolt(75).color('R', 1, 1.5).waitForColor().stop();
  intake.stop().brake();
  chassis.waitUntillSettled();

  chassis.turnToAngle(-45, 100, 0.75).waitUntillSettled(); // Turn towards 2nd goal
  chassis.driveToPoint(-8, 78, 100, 'X', 1.1, -45).withMinVel(30).waitUntillSettled(); // Drive towards 2nd goal
  chassis.moveVel(15);

  // Cycle 2nd goal
  uptake.moveVolt(100);
  delay(500);
  uptake.stop().brake();

  chassis.turnToAngle(-45, 100, 0.8).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  intake.moveVel(-100);
  chassis.driveToPoint(28.8, 42.2, 100, 'X', 2.0, -45, true).withMultiplier(1.15).waitUntillSettled();; // Drive away from 2nd goal

  chassis.turnToAngle(90, 100, 1.35).waitUntillSettled(); // Turn towards mid field
  chassis.driveToPoint(54, 45.5, 100, 'X', 1.0, 90).withMultiplier(1.2); // Drive towards mid field
  intake.moveVolt(100);
  uptake.moveVolt(75).color('R', 1, 1.0).waitForColor().stop();
  chassis.waitUntillSettled();

  chassis.turnToAngle(0, 100, 0.6).waitUntillSettled(); // Turn towards 3rd goal
  chassis.driveToPoint(52.5, 76.6, 100, 'Y', 1.2, 0).withMinVel(30).waitUntillSettled(); // Drive towards 3rd goal
  chassis.moveVel(15);

  // Cycle 3rd goal
  uptake.moveVolt(100);
  delay(150);
  intake.stop();
  delay(550);
  uptake.stop();
  intake.moveVolt(-100);

  chassis.turnToAngle(0, 100, 0.6).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  chassis.driveToPoint(55.5, 55, 100, 'Y', 1.4, 0, true).withMultiplier(1.2).waitUntillSettled(); // Drive away from 3rd goal
  chassis.turnToAngle(90, 100, 1.3).waitUntillSettled(); // Turn towards far field

  intake.moveVolt(100);
  chassis.driveToPoint(120, 55.5, 100, 'X', 1.8, 90); // Drive towards red ball on line
  uptake.moveVolt(75).color('R', 1, 1.7).waitForColor().stop(); // Intake red ball
  chassis.waitUntillSettled();

  chassis.driveToPoint(99.5, 56, 100, 'X', 1.4, 90, true).withMultiplier(1.3).waitUntillSettled(); // Drive away from wall
  chassis.turnToAngle(45, 100, 0.6).waitUntillSettled(); // Turn towards 4th goal
  chassis.driveToPoint(118, 80, 100, 'Y', 1.2, 45).withMinVel(30).waitUntillSettled(); // Drive towards 4th goal
  chassis.moveVel(15);

  // Cycle 4th goal
  uptake.moveVolt(100);
  delay(500);
  uptake.stop();
  intake.moveVolt(-100);

  chassis.turnToAngle(45, 100, 0.6).withMultiplier(2.5).waitUntillSettled(); // Align on goal
}
