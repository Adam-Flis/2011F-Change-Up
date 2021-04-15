#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

/**
 * Full cycle home row
 * Line up on right of the field facing the right wall with
 * left side of drive wheels on the white line
 */
void homeRow(char color) {

  // Figure out what color is the opponent is, used with optical sensors
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
  uptake.moveVolt(100).shot(2, 1.4).waitForShot(); // Shoot 2 balls in 1st goal
  delay(50);
  uptake.stop().brake();
  intake.stop().brake();
  chassis.turnToAngle(45, 100, 0.4).withMultiplier(2.5).waitUntillSettled(); // Align on goal

  // Logic to detect if blue ball is still inside goal
  if (intake.getColor() == opponentColor) { // Intake if blue ball is still in goal
    intake.moveVolt(100);
    delay(50);
  } else { // Outake if blue ball is inside robot
    intake.moveVel(-20);
  }

  chassis.driveToPoint(-16.5, -4.5, 100, 'X', 0.9, 45, true).withMultiplier(1.4).waitUntillSettled(); // Drive away from first goal

  intake.stop();
  chassis.turnToAngle(0, 90, 1.35); // Turn to face wall

  // Logic to determine what color ball is where and what direction and for how long to run the intakes/uptakes
  if (intake.getColor() == color && uptake.getColorM() == 'N') { // Intake and uptakes if color ball is inside intakes
    intake.moveVolt(100);
    uptake.moveVolt(100);
    delay(150);
  } else if (uptake.getColorM() == color || uptake.getColorB() == color) { // Move balls down if color is further up inside robot
    uptake.moveVolt(-100);
    intake.moveVolt(-50);
    delay(40);
  } else if (uptake.getColorB() == opponentColor) { // Discard of opponent color ball
    intake.moveVolt(-100);
    uptake.moveVolt(-100);
    delay(200);
  } else { // Outtake if anything else
    intake.moveVolt(-100);
    uptake.moveVolt(-100);
    delay(150);
  }
  uptake.stop();
  chassis.waitUntillSettled();
  intake.stop().brake();

  chassis.driveToPoint(-16, -45, 100, 'Y', 1.5, 0, true).withMultiplier(1.35).waitUntillSettled(); // Drive towards mid field

  chassis.turnToAngle(90, 100, 0.85).waitUntillSettled(); // Turn to face 2nd goal

  intake.moveVolt(100);
  chassis.driveToPoint(14, -45, 100, 'X', 0.3, 90).withMultiplier(1.3).withMinVel(40).waitUntillSettled(); // Drive at 2nd goal
  chassis.moveVel(20);

  // Cycle 2nd goal
  uptake.resetCount();
  uptake.moveVolt(100).color(opponentColor, 1, 1.2).waitForColor(); // Cycle until opponent color is detected inside robot, prevents overcycling
  intake.moveVolt(-100);
  delay(130);
  uptake.stop().brake();
  delay(60);

  chassis.driveToPoint(-22, -45, 100, 'X', 1.0, 90, true).withMultiplier(1.4); // Drive away from 2nd goal
  delay(200);
  uptake.moveVolt(-100);
  chassis.waitUntillSettled();

  delay(10);

  chassis.turnToAngle(180, 100, 1.35).waitUntillSettled(); // Turn downfield
  uptake.stop().brake();
  intake.stop().brake();

  chassis.driveToPoint(-22, -84, 100, 'Y', 1.9, 180).withMultiplier(1.2).waitUntillSettled(); // Drive across the field

  delay(10);

  chassis.turnToAngle(135, 100, 0.4).waitUntillSettled(); // Turn to face 3rd goal

  intake.moveVolt(100);
  chassis.driveToPoint(14, -90, 100, 'X', 0.9, 135).withMultiplier(1.3).withMinVel(40).waitUntillSettled(); // Drive towards 3rd goal
  chassis.moveVel(20);

  // Cycle 3rd goal
  //chassis.turnToAngle(135, 100, 0.3).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  uptake.resetCount();
  uptake.moveVolt(100).color(opponentColor, 1, 1.2).waitForColor(); // Cycle until opponent color is detected inside robot, prevents overcycling
  intake.moveVolt(-100);
  delay(130);
  uptake.stop().brake();
  chassis.stop().brake();
  delay(60);

  chassis.moveVel(-100, 'B'); // Drive away from 3rd goal
  delay(400);
  chassis.stop().coast();
  delay(250);
  intake.stop().coast();
  uptake.stop().coast();

}
