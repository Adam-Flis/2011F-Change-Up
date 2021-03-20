#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

/**
 *
 */
void homeRow(char color) {

  char opponentColor;
  if (color == 'B') {
    opponentColor = 'R';
  } else {
    opponentColor = 'B';
  }

  intake.moveVolt(-100); // Deploy
  delay(300);
  intake.moveVolt(100);

  chassis.arcToPoint(6.0, 20, 80, 'X').withMinVel(15).withTolerance(1.5).waitUntillSettled(); // Arc towards 1st goal
  // Cycle 1st goal
  intake.moveVolt(100);
  uptake.moveVolt(100).shot(3, 1.0);
  intake.color(opponentColor, 1.0).waitForColor();
  delay(100);
  intake.stop();
  uptake.waitForShot().stop();

  // uptake.color(opponentColor, 1, 1.5).waitForColor().stop();

  chassis.driveToPoint(0, -10, 100, 'X', true).withTolerance(1).withMultiplier(1.5); // Drive away from goal
  delay(400);
  uptake.moveVolt(-100);
  intake.moveVolt(-100);
  //uptake.moveVolt(-100).color(color, 1, 1.0).waitForColor().stop().brake(); // Move alliance ball down inside robot
  chassis.waitUntillSettled();

  chassis.turnToAngle(180, 80).withTolerance(1).withMultiplier(1.2).waitUntillSettled(); // Turn down field
  intake.stop();
  uptake.stop();

  chassis.driveToPoint(-3, -25, 100, 'Y').withMinVel(20).withTolerance(1.2).waitUntillSettled(); // Drive toward mid field

  chassis.arcToPoint(6.5, 10, 60, 'X').withMinVel(15).withTolerance(1.5).waitUntillSettled(); // Arc towards 2nd goal
  // Cycle 2nd goal
  delay(200);
  uptake.moveVolt(100);
  intake.moveVolt(100).color(opponentColor, 1.0).waitForColor().stop();
  uptake.shot(1, 1.0).waitForShot().stop();

  chassis.driveToPoint(-7, -44, 100, 'X', true).withTolerance(1.5).withMultiplier(1.5); // Drive away from goal
  delay(600);
  uptake.moveVolt(-100);
  intake.moveVolt(-100);
  chassis.waitUntillSettled();

  chassis.turnToAngle(180, 80).withTolerance(1).withMultiplier(1.2).waitUntillSettled(); // Turn down field
  intake.stop();
  uptake.stop();

  chassis.driveToPoint(-5.8, -77, 80, 'Y').withMinVel(20).withTolerance(1.2).waitUntillSettled(); // Drive across the field

  chassis.arcToPoint(24, 28, 60, 'X').withMinVel(15).withTolerance(1.5).waitUntillSettled(); // Arc towards 3rd goal
}
