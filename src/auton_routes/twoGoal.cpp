#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

/**
 * Cycle corner and wall goal
 * Line up on right of the field facing the right wall with
 * left side of drive wheels on the white line
 */
void twoGoal(char color){

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
  chassis.move(100, 'L');
  chassis.move(40, 'R');
  delay(425);
  chassis.move(-10);

  // Cycle 1st goal
  delay(10);
  chassis.move(15);
  delay(20);
  uptake.resetCount();
  uptake.moveVolt(95).shot(2, 1.3).waitForShot(); // Shoot 2 balls in 1st goal
  delay(20);
  uptake.stop().brake();
  delay(80);
  intake.moveVolt(-50);

  chassis.driveToPoint(-13, -1.5, 100, 'X', 1.1, 45, true).waitUntillSettled(); // Drive away from first goal
  intake.stop();
  chassis.turnToAngle(0, 100, 0.7).waitUntillSettled(); // Turn to face wall

  intake.moveVolt(-100); // Discard opponent ball
  uptake.moveVolt(-70);
  delay(190);
  uptake.stop().brake();

  chassis.driveToPoint(-13, -42.5, 100, 'Y', 1.45, 0, true).waitUntillSettled(); // Drive towards mid field
  chassis.stop();
  intake.stop().brake();

  chassis.turnToAngle(90, 100, 0.7).waitUntillSettled(); // Turn to face 2nd goal

  intake.moveVolt(100);
  chassis.driveToPoint(3.7, -42.5, 100, 'X', 0.95, 90).waitUntillSettled(); // Drive at 2nd goal
  chassis.move(-10);

  // Cycle 2nd goal
  delay(10);
  chassis.move(15);
  delay(20);
  uptake.resetCount();
  uptake.moveVolt(100).color(opponentColor, 1, 1.4).waitForColor(); // Cycle until opponent color is detected inside robot, prevents overcycling
  intake.moveVolt(-50);
  delay(100);
  uptake.stop().brake();
  delay(80);
  intake.stop().brake();
  delay(6000); // Wait to drive away from goal

  intake.moveVolt(-50); // Discard opponent ball
  uptake.moveVolt(-100);
  chassis.driveToPoint(-20, -42.5, 100, 'X', 1.1, 90, true).waitUntillSettled(); // Drive away from 2nd goal
  intake.stop().brake();
  uptake.stop().brake();

}
