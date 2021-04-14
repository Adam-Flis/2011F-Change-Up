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
  delay(425);
  chassis.moveVel(20);

  // Cycle 1st goal
  uptake.resetCount();
  uptake.moveVolt(100).shot(2, 1.4).waitForShot();
  delay(50);
  uptake.stop().brake();
  intake.stop().brake();
  chassis.turnToAngle(45, 100, 0.3).withMultiplier(2.5).waitUntillSettled(); // Align on goal

  if (intake.getColor() == opponentColor) {
    intake.moveVolt(100);
    delay(80);
  } else {
    intake.moveVel(-30);
  }
  chassis.driveToPoint(-16, -4, 100, 'X', 1.0, 45, true).withMultiplier(1.35).waitUntillSettled(); // Drive away from first goal

  intake.stop();
  chassis.turnToAngle(0, 100, 1.4); // Turn to face wall
  if (intake.getColor() == color && uptake.getColorM() == 'N') {
    intake.moveVolt(100);
    uptake.moveVolt(100);
    delay(150);
  } else if (uptake.getColorM() == color || uptake.getColorB() == color) {
    uptake.moveVolt(-100);
    intake.moveVolt(-50);
    delay(20);
  } else if (uptake.getColorB() == opponentColor) {
    intake.moveVolt(-100);
    uptake.moveVolt(-100);
    delay(150);
  } else {
    intake.moveVolt(-100);
    uptake.moveVolt(-100);
    delay(200);
  }
  uptake.stop();
  chassis.waitUntillSettled();
  intake.stop().brake();

  chassis.driveToPoint(-16, -44, 100, 'Y', 1.25, 0, true).withMultiplier(1.35).waitUntillSettled(); // Drive towards mid field

  chassis.turnToAngle(90, 100, 1.0).waitUntillSettled(); // Turn to face 2nd goal

  intake.moveVolt(100);
  chassis.driveToPoint(8, -44, 100, 'X', 0.4, 90).withMinVel(30).waitUntillSettled(); // Drive at 2nd goal
  chassis.moveVel(15);

  // Cycle 2nd goal
  uptake.resetCount();
  uptake.moveVolt(100).color(opponentColor, 1, 1.2).waitForColor();
  intake.moveVolt(-100);
  delay(130);
  uptake.stop().brake();
  delay(110);

  chassis.driveToPoint(-22, -44, 100, 'X', 0.8, 90, true).withMultiplier(1.35); // Drive away from 2nd goal
  delay(200);
  uptake.moveVolt(-100);
  chassis.waitUntillSettled();

  delay(10);

  chassis.turnToAngle(180, 100, 1.35).waitUntillSettled(); // Turn downfield
  uptake.stop().brake();
  intake.stop().brake();

  chassis.driveToPoint(-22, -86, 100, 'Y', 2.1, 180).waitUntillSettled(); // Drive across the field

  delay(10);

  chassis.turnToAngle(135, 100, 0.65).waitUntillSettled(); // Turn to face 3rd goal

  intake.moveVolt(100);
  chassis.driveToPoint(8, -103, 100, 'X', 1.1, 135).withMinVel(30).waitUntillSettled(); // Drive towards 3rd goal
  chassis.moveVel(20);

  // Cycle 3rd goal
  chassis.turnToAngle(135, 100, 0.3).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  uptake.resetCount();
  uptake.moveVolt(100).color(opponentColor, 1, 1.2).waitForColor();
  intake.moveVolt(-100);
  delay(130);
  uptake.stop().brake();
  chassis.stop().brake();
  delay(110);

  chassis.moveVel(-100, 'B'); // Drive away from 3rd goal
  delay(200);
  uptake.moveVel(-100);
  delay(150);
  // delay(100);
  // chassis.moveVel(-15, 'L');
  // chassis.moveVel(-100, 'R');
  // delay(300);
  chassis.stop().coast();
  delay(250);
  intake.stop().coast();
  uptake.stop().coast();

}
