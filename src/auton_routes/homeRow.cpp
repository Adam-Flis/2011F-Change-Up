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
  delay(30);
  uptake.resetCount();
  uptake.moveVolt(100).shot(2, 1.2).waitForShot(); // Shoot 2 balls in 1st goal
  delay(100);
  uptake.stop().brake();
  intake.moveVel(-15);
  chassis.turnToAngle(45, 100, 0.4).withMultiplier(2.5).waitUntillSettled(); // Align on goal

  // Logic to detect if blue ball is still inside goal
  if (intake.getColor() == opponentColor) { // Intake if blue ball is still in goal
    intake.moveVolt(100);
    delay(80);
  } else { // Outake if blue ball is inside robot
    intake.moveVel(-20);
  }

  chassis.driveToPoint(-16, -4.5, 100, 'X', 0.9, 45, true).withMultiplier(1.4).withMinVel(20).waitUntillSettled(); // Drive away from first goal

  intake.stop();
  chassis.turnToAngle(0, 100, 1.0); // Turn to face wall

  // Logic to determine what color ball is where and what direction and for how long to run the intakes/uptakes
  if (intake.getColor() == color && uptake.getColorM() == 'N') { // Intake and uptakes if color ball is inside intakes
    intake.moveVolt(100);
    uptake.moveVolt(100);
    delay(150);
  } else if (uptake.getColorM() == color || uptake.getColorB() == color) { // Move balls down if color is further up inside robot
    uptake.moveVolt(-100);
    intake.moveVolt(100);
    delay(150);
    intake.moveVel(-100);
    delay(50);
    intake.stop().coast();
  } else { // Outtake if anything else
    intake.moveVolt(-100);
    uptake.moveVolt(-80);
    delay(240);
  }
  uptake.stop().brake();
  chassis.waitUntillSettled();
  intake.stop().brake();

  chassis.driveToPoint(-16, -52, 100, 'Y', 1.4, 0, true).withMultiplier(1.35).waitUntillSettled(); // Drive towards mid field

  chassis.turnToAngle(90, 100, 1.0).waitUntillSettled(); // Turn to face 2nd goal

  intake.moveVolt(100);
  chassis.driveToPoint(16, -47, 100, 'X', 0.4, 90).withMultiplier(1.35).withMinVel(40).waitUntillSettled(); // Drive at 2nd goal
  chassis.moveVel(20);

  // Cycle 2nd goal
  delay(30);
  uptake.resetCount();
  uptake.moveVolt(100).color(opponentColor, 1, 1.2).waitForColor(); // Cycle until opponent color is detected inside robot, prevents overcycling
  intake.moveVolt(-50);
  delay(130);
  uptake.stop().brake();
  delay(60);

  chassis.driveToPoint(-22, -45, 100, 'X', 0.9, 90, true).withMultiplier(1.4).waitUntillSettled(); // Drive away from 2nd goal

  chassis.turnToAngle(0, 100, 1.0); // Turn backfield
  delay(300);
  intake.moveVolt(-100);
  uptake.moveVolt(-100);
  chassis.waitUntillSettled();
  intake.stop().brake();
  uptake.stop().brake();

  chassis.driveToPoint(-22, -88, 100, 'Y', 1.7, 0, true).withMultiplier(1.4).waitUntillSettled(); // Drive across the field

  chassis.turnToAngle(135, 100, 1.0).waitUntillSettled(); // Turn to face 3rd goal

  intake.moveVolt(100);
  chassis.driveToPoint(14, -90, 100, 'X', 0.8, 135).withMultiplier(1.35).withMinVel(40).waitUntillSettled(); // Drive towards 3rd goal
  chassis.moveVel(-20);

  // Cycle 3rd goal
  //chassis.turnToAngle(135, 100, 0.3).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  delay(30);
  chassis.stop();
  uptake.resetCount();
  uptake.moveVolt(100).color(opponentColor, 1, 1.2).waitForColor(); // Cycle until opponent color is detected inside robot, prevents overcycling
  intake.moveVolt(-50);
  delay(120);
  uptake.stop().brake();
  delay(60);

  chassis.moveVel(-100, 'B'); // Drive away from 3rd goal
  delay(300);
  chassis.stop().coast();
  intake.stop().coast();
  uptake.stop().coast();

}
