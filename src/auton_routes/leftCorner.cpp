#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

void leftCorner(char color) {

  // char opponentColor;
  // if (color == 'B') {
  //   opponentColor = 'R';
  // } else {
  //   opponentColor = 'B';
  // }
  //
  // intake.moveVolt(-100); // Deploy
  // delay(300);
  // intake.moveVolt(100);
  //
  // chassis.arcToPoint(-6.0, 20, 65, 'X').withMinVel(20).withTolerance(1.5).waitUntillSettled(); // Arc towards 1st goal
  // // Cycle 1st goal
  // chassis.moveVel(20);
  // uptake.resetCount();
  // intake.moveVolt(100);
  // uptake.moveVolt(90);
  // while (uptake.getCount() != 2);
  // intake.color(color, 4.0).waitForColor();
  // intake.moveVolt(-100);
  // while (uptake.getCount() != 3);
  // chassis.stop().brake();
  // uptake.stop().brake();
  //
  // chassis.driveToPoint(20, -9, 50, 'Y', true).withTolerance(1.0).withMinVel(15).waitUntillSettled();
  //
  // intake.stop();
  // chassis.turnToAngle(90, 90).withMinVel(10).withTolerance(0.5).waitUntillSettled();
}
