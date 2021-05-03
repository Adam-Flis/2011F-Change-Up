#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

/**
 *
 */
void skills () {

  intake.moveVolt(-100); // Deploy

  chassis.driveToPoint(21, 45, 90, 'Y', 1.2, 25); // Drive at wall
  delay(100);
  intake.moveVolt(100);
  uptake.moveVolt(65).color('R', 1, 0.7).waitForColor().stop(); // Grab line ball
  chassis.waitUntillSettled();
  delay(100);

  chassis.driveToPoint(20, 32.5, 100, 'Y', 0.85, 25, true); // Drive away from wall
  uptake.moveVolt(60).color('R', 2, 0.3).waitForColor().stop(); // Index balls
  intake.stop();
  chassis.waitUntillSettled();

  chassis.turnToAngle(-45, 100, 0.4).waitUntillSettled(); // Turn towards 1st goal
  chassis.driveToPoint(-5, 46, 100, 'X', 0.8, -45).waitUntillSettled(); // Drive at 1st goal
  chassis.move(20);

  // Cycle 1st goal
  uptake.resetCount();
  intake.moveVolt(100);
  uptake.moveVolt(85).color('B', 2, 1.7).waitForColor().stop();
  delay(70);

  intake.moveVolt(-50);
  uptake.moveVolt(-45);
  chassis.driveToPoint(38.5, 12.5, 70, 'X', 1.2, -45, true).waitUntillSettled(); // Drive away from 1st goal
  intake.stop();
  uptake.stop();

  chassis.turnToAngle(-180, 100, 1.0).waitUntillSettled(); // Turn downfield
  chassis.driveToPoint(36, -10, 100, 'Y', 0.85, -180); // Drive across the field
  intake.moveVolt(100);
  uptake.moveVolt(65).color('R', 1, 0.85).waitForColor().stop(); // Index ball
  chassis.waitUntillSettled();
  chassis.turnToAngle(-90, 100, 0.65).waitUntillSettled(); // Turn at 2nd goal
  chassis.driveToPoint(-1, -10, 100, 'X', 0.8, -90).waitUntillSettled(); // Drive at 2nd goal
  chassis.move(20);

  // Cycle 2nd goal
  uptake.resetCount();
  intake.moveVolt(100);
  uptake.moveVolt(75).color('B', 2, 1.2).waitForColor().stop();
  intake.moveVolt(-50);
  delay(60);

  chassis.driveToPoint(18, -10.5, 100, 'X', 1.0, -90, true).waitUntillSettled(); // Drive away from 2nd goal
  intake.moveVolt(-100);
  uptake.moveVolt(-100); // Discard blue ball
  chassis.turnToAngle(-45, 100, 0.35).waitUntillSettled();

  chassis.turnToAngle(-175, 100, 0.8).waitUntillSettled(); // Turn at line ball
  chassis.driveToPoint(14.3, -46, 100, 'Y', 1.0, -175); // Drive at line ball
  intake.moveVolt(100);
  uptake.moveVolt(65).color('R', 1, 1.0).waitForColor().stop(); // Index ball
  chassis.waitUntillSettled();

  chassis.turnToAngle(-200, 100, 0.3).waitUntillSettled(); // Turn at wall ball
  intake.moveVolt(100);
  chassis.driveToPoint(21, -72, 90, 'Y', 1.2, -200).waitUntillSettled(); // Drive at wall
  delay(100);

  chassis.driveToPoint(16.5, -60, 100, 'Y', 0.85, -200, true); // Drive away from wall
  uptake.moveVolt(65).color('R', 2, 0.85).waitForColor().stop(); // Index balls
  intake.stop();
  chassis.waitUntillSettled();

  chassis.turnToAngle(-135, 100, 0.5).waitUntillSettled(); // Turn towards 3rd goal
  chassis.driveToPoint(-5, -72, 100, 'X', 1.0, -135).waitUntillSettled(); // Drive at 3rd goal
  chassis.move(20);

  // Cycle 3rd goal
  uptake.resetCount();
  intake.moveVolt(100);
  uptake.moveVolt(85).color('B', 2, 1.2).waitForColor().stop();
  delay(70);

  intake.moveVolt(-50);
  uptake.moveVolt(-45);
  chassis.driveToPoint(37, -36, 70, 'Y', 1.2, -135, true).waitUntillSettled(); // Drive away from 3rd goal
  intake.stop();
  uptake.stop();

  chassis.turnToAngle(-270, 100, 1.0).waitUntillSettled(); // Turn downfield
  chassis.driveToPoint(56.5, -36, 100, 'X', 0.9, -270); // Drive across the field
  intake.moveVolt(100);
  uptake.moveVolt(65).color('R', 1, 0.9).waitForColor().stop(); // Index balls
  chassis.waitUntillSettled();
  chassis.turnToAngle(-180, 100, 0.65).waitUntillSettled(); // Turn at 4th goal
  chassis.driveToPoint(56.5, -74, 100, 'Y', 0.9, -180).waitUntillSettled(); // Drive at 4th goal
  chassis.move(20);

  // Cycle 4th goal
  uptake.resetCount();
  intake.moveVolt(100);
  uptake.moveVolt(75).color('B', 2, 1.4).waitForColor().stop();
  intake.moveVolt(-50);
  delay(60);

  chassis.driveToPoint(56.5, -52.8, 100, 'Y', 1.2, -180, true).waitUntillSettled(); // Drive away from 4th goal
  intake.moveVolt(-100);
  uptake.moveVolt(-100); // Discard blue ball
  chassis.turnToAngle(-135, 100, 0.35).waitUntillSettled();

  chassis.turnToAngle(-270, 100, 0.9).waitUntillSettled(); // Turn at line ball
  chassis.driveToPoint(105.5, -52.8, 100, 'X', 1.15, -270); // Drive at line ball
  intake.moveVolt(100);
  uptake.moveVolt(65).color('R', 1, 1.2).waitForColor().stop(); // Index ball
  chassis.waitUntillSettled();

  chassis.turnToAngle(-155, 100, 0.7).waitUntillSettled(); // Turn at wall ball
  intake.moveVolt(100);
  chassis.driveToPoint(102, -72, 90, 'Y', 1.2, -155).waitUntillSettled(); // Drive at wall
  delay(100);

  chassis.driveToPoint(101, -60.5, 100, 'Y', 0.85, -155, true); // Drive away from wall
  uptake.moveVolt(65).color('R', 2, 0.4).waitForColor().stop(); // Index balls
  intake.stop();
  chassis.waitUntillSettled();

  chassis.turnToAngle(-225, 100, 0.4).waitUntillSettled(); // Turn towards 5th goal
  chassis.driveToPoint(125, -72, 100, 'X', 0.9, -225).waitUntillSettled(); // Drive at 5th goal
  chassis.move(20);

  // Cycle 5th goal
  uptake.resetCount();
  intake.moveVolt(100);
  uptake.moveVolt(85).color('B', 2, 1.4).waitForColor().stop();
  intake.moveVolt(-50);
  delay(70);

  intake.moveVolt(-50);
  uptake.moveVolt(-45);
  chassis.driveToPoint(85, -36.5, 70, 'Y', 1.3, -225, true).waitUntillSettled(); // Drive away from 5th goal
  intake.stop();
  uptake.stop();

  chassis.turnToAngle(-360, 100, 1.2).waitUntillSettled(); // Turn downfield
  chassis.driveToPoint(85, -18.5, 100, 'Y', 1.0, -360); // Drive across the field
  intake.moveVolt(100);
  uptake.moveVolt(65).color('R', 1, 1.0).waitForColor().stop(); // Index ball
  chassis.waitUntillSettled();
  chassis.turnToAngle(-270, 100, 0.6).waitUntillSettled(); // Turn at 6th goal
  chassis.driveToPoint(117, -18.5, 100, 'X', 0.9, -270).waitUntillSettled(); // Drive at 6th goal
  chassis.move(20);

  // Cycle 6th goal
  uptake.resetCount();
  intake.moveVolt(100);
  uptake.moveVolt(70).color('B', 2, 1.2).waitForColor().stop();
  intake.moveVolt(-50);
  delay(50);

  chassis.driveToPoint(101.5, -18.5, 100, 'X', 1.3, -270, true).waitUntillSettled(); // Drive away from 6th goal
  intake.moveVolt(-100);
  uptake.moveVolt(-100); // Discard blue ball
  chassis.turnToAngle(-225, 100, 0.35).waitUntillSettled();

  chassis.turnToAngle(-350, 100, 0.85).waitUntillSettled(); // Turn at line ball
  chassis.driveToPoint(107, 20, 100, 'Y', 1.0, -350); // Drive at line ball
  intake.moveVolt(100);
  uptake.moveVolt(65).color('R', 1, 1.0).waitForColor().stop(); // Index ball
  chassis.waitUntillSettled();

  chassis.turnToAngle(-380, 100, 0.45).waitUntillSettled(); // Turn at wall ball
  intake.moveVolt(100);
  chassis.driveToPoint(101, 45, 90, 'Y', 1.2, -380).waitUntillSettled(); // Drive at wall
  delay(100);

  chassis.driveToPoint(104, 33, 100, 'Y', 0.85, -380, true); // Drive away from wall
  uptake.moveVolt(65).color('R', 2, 0.85).waitForColor().stop(); // Index balls
  intake.stop();
  chassis.waitUntillSettled();

  chassis.turnToAngle(-315, 100, 0.4).waitUntillSettled(); // Turn towards 7th goal
  chassis.driveToPoint(125, 46, 100, 'X', 0.9, -315).waitUntillSettled(); // Drive at 7th goal
  chassis.move(20);

  // Cycle 7th goal
  uptake.resetCount();
  intake.moveVolt(100);
  uptake.moveVolt(85).color('B', 2, 1.4).waitForColor().stop();
  intake.moveVolt(-50);
  delay(70);

  intake.moveVolt(-50);
  uptake.moveVolt(-45);
  chassis.driveToPoint(85.5, 12, 70, 'Y', 1.2, -315, true).waitUntillSettled(); // Drive away from 7th goal
  intake.stop();
  uptake.stop();

  chassis.turnToAngle(-450, 100, 1.1).waitUntillSettled(); // Turn upfield
  chassis.driveToPoint(59.5, 12, 100, 'X', 0.9, -450); // Drive across the field
  intake.moveVolt(100);
  uptake.moveVolt(65).color('R', 1, 0.9).waitForColor().stop(); // Index ball
  chassis.waitUntillSettled();
  chassis.turnToAngle(-355, 100, 0.7).waitUntillSettled(); // Turn at 8th goal
  chassis.driveToPoint(61, 47, 100, 'Y', 0.9, -355).waitUntillSettled(); // Drive at 8th goal
  chassis.move(20);

  // Cycle 8th goal
  uptake.resetCount();
  intake.moveVolt(100);
  uptake.moveVolt(100);
  delay(300);
  uptake.moveVolt(65).color('R', 2, 0.8).waitForColor().stop();
  intake.moveVolt(100);
  delay(200);

  chassis.driveToPoint(61, 18, 100, 'Y', 1.0, -360, true).waitUntillSettled(); // Drive away from 8th goal
  intake.moveVolt(-100);
  chassis.turnToAngle(-190, 100, 1.0).waitUntillSettled(); // Turn at 9th goal

  chassis.driveToPoint(63, -9.5, 100, 'Y', 0.9, -190).waitUntillSettled(); // Drive to 9th goal
  chassis.driveToPoint(56, 5, 100, 'Y', 0.5, -190, true).waitUntillSettled(); // Drive away from 9th goal

  chassis.driveToPoint(63, -9.5, 100, 'Y', 0.5, -180).waitUntillSettled(); // Drive to 9th goal
  chassis.driveToPoint(56, 5, 100, 'Y', 0.45, -180, true).waitUntillSettled(); // Drive away from 9th goal

  chassis.driveToPoint(63, -9.5, 100, 'Y', 0.5, -180).waitUntillSettled(); // Drive to 9th goal
  chassis.driveToPoint(56, 5, 100, 'Y', 0.45, -180, true).waitUntillSettled(); // Drive away from 9th goal

  chassis.driveToPoint(63, -9.5, 100, 'Y', 0.5, -180).waitUntillSettled(); // Drive to 9th goal

  chassis.move(100, 'L');
  uptake.moveVel(-100);
  delay(100);
  uptake.stop().brake();
  delay(200);
  uptake.moveVolt(100);
  delay(400); // Score in 9th goal
  chassis.move(-100);
  delay(400);
  chassis.stop().coast();

}
