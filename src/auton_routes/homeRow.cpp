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

  if (intake.getColor() == opponentColor) {
    intake.moveVolt(100);
  } else {
    intake.moveVel(-10);
  }
  chassis.driveToPoint(-13, -9, 100, 'X', 1.0, 45, true).withMultiplier(1.4).waitUntillSettled(); // Drive away from first goal

  intake.stop();
  chassis.turnToAngle(0, 100, 1.35); // Turn to face wall
  if (intake.getColor() == color && uptake.getColorM() == 'N') {
    intake.moveVolt(100);
    uptake.moveVolt(100);
    delay(150);
  } else if (uptake.getColorM() == color || uptake.getColorB() == color) {
    uptake.moveVolt(-100);
    intake.moveVolt(-100);
    delay(25);
  } else {
    intake.moveVolt(-100);
    uptake.moveVolt(-100);
    delay(200);
  }
  uptake.stop();
  chassis.waitUntillSettled();
  intake.stop().brake();

  chassis.driveToPoint(-13, -50, 100, 'Y', 1.25, 0, true).withMultiplier(1.4).waitUntillSettled(); // Drive towards mid field

  chassis.turnToAngle(90, 100, 0.9).waitUntillSettled(); // Turn to face 2nd goal

  intake.moveVolt(100);
  chassis.driveToPoint(17, -48, 100, 'X', 0.4, 90).withMinVel(25).waitUntillSettled(); // Drive at 2nd goal
  chassis.moveVel(15);

  // Cycle 2nd goal
  uptake.resetCount();
  uptake.moveVolt(100).color(opponentColor, 1, 0.8).waitForColor();
  intake.moveVolt(-100);
  delay(125);
  uptake.stop().brake();
  delay(80);

  chassis.driveToPoint(-21, -48, 100, 'X', 0.8, 90, true).withMultiplier(1.4); // Drive away from 2nd goal
  delay(200);
  uptake.moveVolt(-100);
  chassis.waitUntillSettled();

  delay(10);

  chassis.turnToAngle(180, 100, 1.35).waitUntillSettled(); // Turn downfield
  uptake.stop().brake();
  intake.stop().brake();

  chassis.driveToPoint(-21, -87.5, 100, 'Y', 2.1, 180).waitUntillSettled(); // Drive across the field

  delay(10);

  chassis.turnToAngle(135, 100, 0.6).waitUntillSettled(); // Turn to face 3rd goal

  intake.moveVolt(100);
  chassis.driveToPoint(16, -113, 100, 'X', 1.1, 135).withMinVel(30).waitUntillSettled(); // Drive towards 3rd goal
  chassis.moveVel(20);

  // Cycle 3rd goal
  chassis.turnToAngle(135, 100, 0.2).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  uptake.resetCount();
  uptake.moveVolt(100).color(opponentColor, 1, 0.8).waitForColor();
  intake.moveVolt(-100);
  delay(125);
  uptake.stop().brake();
  chassis.stop().brake();
  delay(80);

  chassis.moveVel(-100, 'B'); // Drive away from 3rd goal
  delay(200);
  uptake.moveVel(-100);
  delay(150);
  // delay(100);
  // chassis.moveVel(-15, 'L');
  // chassis.moveVel(-100, 'R');
  // delay(300);
  chassis.stop().coast();
  delay(200);
  intake.stop().coast();
  uptake.stop().coast();

}
