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
  delay(200);
  intake.moveVolt(100);

  chassis.moveVel(75, 'L');
  chassis.moveVel(20, 'R');
  delay(300);
  chassis.moveVel(35, 'L');
  chassis.moveVel(35, 'R');
  delay(350);
  chassis.stop();
  chassis.turnToAngle(45, 100, 1.3).withMultiplier(2.5); // Align on goal

  //chassis.arcToPoint(-6.0, 20, 65, 'X').withMinVel(20).withTolerance(1.5).waitUntillSettled(); // Arc towards 1st goal
  // Cycle 1st goal
  uptake.resetCount();
  uptake.moveVolt(100).shot(2, 1.3).waitForShot();
  //uptake.moveVolt(100).color(opponentColor, 1, 1.3).waitForColor();
  intake.stop().hold();
  uptake.stop().brake();
  chassis.waitUntillSettled();

  chassis.driveToPoint(-12, -2, 90, 'X', 1.1, 45, true).waitUntillSettled(); // Drive away from first goal

  intake.moveVolt(-100);
  uptake.moveVolt(-100);
  chassis.turnToAngle(0, 100, 1.0); // Turn to face wall
  delay(200);
  uptake.stop();
  chassis.waitUntillSettled();
  intake.stop().brake();

  chassis.driveToPoint(-10, -28, 90, 'Y', 1.6, 0, true).waitUntillSettled(); // Drive towards mid field

  delay(20);

  chassis.turnToAngle(90, 100, 1.3).waitUntillSettled(); // Turn to face 2nd goal

  intake.moveVolt(100);
  chassis.driveToPoint(15, -34.5, 80, 'X', 0.6, 90).withMinVel(25).waitUntillSettled(); // Drive at 2nd goal

  //chassis.turnToAngle(90, 100, 1.3).withMultiplier(3.0).withTolerance(0.2); // Align on goal

  // Cycle 2nd goal
  uptake.resetCount();
  uptake.moveVolt(100).color(opponentColor, 1, 1.3).waitForColor();
  delay(200);
  // uptake.moveVolt(90).shot(2, 1.3).waitForShot();
  intake.moveVolt(-100);
  uptake.stop().brake();
  chassis.waitUntillSettled();

  chassis.driveToPoint(-7, -32, 100, 'X', 1.2, 90, true); // Drive away from 2nd goal
  delay(300);
  uptake.moveVolt(-100);
  chassis.waitUntillSettled();

  chassis.turnToAngle(180, 95, 1.3).waitUntillSettled(); // Turn downfield
  uptake.stop();
  intake.stop().brake();

  chassis.driveToPoint(-7, -76, 75, 'Y', 2.0, 180).waitUntillSettled(); // Drive across the field

  chassis.turnToAngle(135, 100, 0.8).waitUntillSettled(); // Turn to face 3rd goal

  intake.moveVolt(100);
  chassis.driveToPoint(25, -105, 95, 'X', 0.9, 135).withMinVel(40).waitUntillSettled(); // Drive towards 3rd goal

  // Cycle 3rd goal
  uptake.resetCount();
  uptake.moveVolt(100).color(opponentColor, 1, 1.3).waitForColor();
  // uptake.moveVolt(100).shot(2, 1.3).waitForShot();
  intake.moveVolt(-100);
  delay(100);
  uptake.stop().brake();
  chassis.stop().brake();

  chassis.moveVel(-100, 'B'); // Drive away from 3rd goal
  delay(500);
  chassis.stop();
  intake.stop().brake();


}
