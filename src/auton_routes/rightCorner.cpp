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
  chassis.moveVel(15);

  // Cycle 1st goal
  uptake.resetCount();
  uptake.moveVolt(100).shot(2, 1.1).waitForShot();
  delay(50);
  uptake.stop().brake();
  intake.stop().brake();
  chassis.turnToAngle(45, 100, 0.2).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  intake.moveVel(-10);

  chassis.driveToPoint(-8, -6, 75, 'X', 1.4, 45, true).waitUntillSettled(); // Drive away from first goal

  chassis.turnToAngle(-58, 70, 2.5); // Turn to mid wall goal
  intake.stop();
  if (intake.getColor() == color){
    intake.moveVel(100);
    uptake.moveVel(100);
    delay(150);
  } else {
    intake.moveVolt(-100);
    uptake.moveVolt(-100);
    delay(200);
  }
  uptake.stop();
  chassis.waitUntillSettled();
  intake.moveVolt(-100);

  delay(2000);

  chassis.driveToPoint(-45.5, 14, 70, 'X', 2.0, -58).waitUntillSettled(); // Drive towards wall goal
  chassis.turnToAngle(-65, 55, 1.0).waitUntillSettled(); // Turn to mid wall goal
  chassis.driveToPoint(-51, 15.2, 70, 'X', 2.0, -65).waitUntillSettled(); // Drive towards wall goal
  chassis.turnToAngle(-77, 55, 1.0).waitUntillSettled(); // Turn to mid wall goal

  uptake.moveVel(100);

  delay(1500);

  chassis.moveVel(-100, 'B'); // Drive away from 3rd goal
  delay(300);
  chassis.stop().coast();
  intake.stop().coast();
  uptake.stop().coast();


}
