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

  chassis.arcToPoint(7.5, 18, 80, 'X').withMinVel(30).withTolerance(1).waitUntillSettled();
  // chassis.turnToAngle(45, 100).withTolerance(0.3).withMultiplier(2.5);
  uptake.moveVolt(100).shot(2, 2.0);
  intake.moveVolt(100).color(opponentColor, 2.0).waitForColor().stop().brake(); // Cycle 1st goal
  uptake.waitForShot().stop().brake();

  chassis.driveToPoint(0, 4, 100, 'Y', true).withMultiplier(2.5); // Drive away from goal
  intake.moveVolt(100);
  delay(300);
  intake.moveVolt(-100);
  uptake.moveVolt(-50).color(color, 1, 2.0).waitForColor().stop().brake();
  intake.stop().brake();
  chassis.waitUntillSettled();

  chassis.turnToAngle(180, 90).waitUntillSettled();




}
