#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

void rightCorner(char color) {

  char opponentColor;
  if (color == 'B') {
    opponentColor = 'R';
  } else {
    opponentColor = 'B';
  }

  intake.moveVolt(-100); // Deploy
  delay(150);
  intake.moveVolt(100);

  // Drive towards 1st goal
  chassis.stop().brake();
  chassis.moveVel(80, 'L');
  chassis.moveVel(20, 'R');
  delay(450);
  chassis.moveVel(20);

  // Cycle 1st goal
  uptake.resetCount();
  uptake.moveVolt(90).shot(3, 1.2).waitForShot();
  delay(30);
  uptake.stop().brake();
  intake.moveVolt(-100);
  chassis.turnToAngle(45, 100, 0.5).withMultiplier(2.5).waitUntillSettled(); // Align on goal

  chassis.driveToPoint(-18.5, -9, 100, 'X', 1.2, 45, true).withMultiplier(1.35).waitUntillSettled(); // Drive away from first goal

  chassis.turnToAngle(226, 65, 2.0).waitUntillSettled(); // Turn towards middle goal

  chassis.driveToPoint(-50.7, -42, 90, 'X', 2.7, 226).waitUntillSettled(); // Drive towards middle goal

  intake.stop();
  chassis.moveVel(10);

}
