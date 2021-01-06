#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

/**
 * Completes the home row in the autonomous
 * @param color 'B' or 'R' (Alliance color; Blue or Red)
 * Points scored: 11
 * Win points: 1
 */
void homeRow(char color) {

  // Changes color of inputted alliance to opponents alliance for waituntilColor function
  if (color == 'B') {
    color = 'R';
  } else if (color == 'R') {
    color = 'B';
  }

  /* ********** 1st Middle Goal (1st Goal) ********** */
  intake.move(-100);
  delay(500); // Deploy hood and shoot preload ball into middle goal
  intake.stop();

  /* ********** 1st Corner Goal (2nd Goal) ********** */
  chassis.driveToPoint(0, 35, 90, 1.3).waitUntilSettled();
  chassis.turnToAngle(90, 90, 0.8).waitUntilSettled(); // Turn towards goal
  intake.move(100);
  chassis.driveToPoint(35.5, 35.5, 90, 1.8); // Drive towards goal
  uptake.move(85);
  chassis.move(40, 'B'); // Constant pressure on 1st goal
  intake.waitUntilColor(color, 1.8); // Wait until middle color ball (opponents color) is inside intakes (Prevent ovvercycling of balls)
  uptake.stop();
  chassis.waitUntilSettled();
  chassis.stop().brake();
  chassis.turnToAngle(90, 100, 0.5).waitUntilSettled(); // Align on goal

  /* ********** Drive away from goal ********** */
  chassis.drive(-34, 90, 1.2); // Drive away from goal
  intake.move(-100);
  delay(100); // Outake opponents ball
  uptake.move(-100);
  chassis.waitUntilSettled();
  uptake.stop();
  intake.stop();

  /* ********** Drive across the field ********** */
  chassis.turnToAngle(-143, 90, 1.2).waitUntilSettled(); // Turn to face downfield
  chassis.drive(-30, 80, 1.3).waitUntilSettled(); // Drive into the wall
  chassis.driveToPoint(-32, -19, 90, 2.0).waitUntilSettled(); // Drive across the field

  /* ********** 2nd Corner Goal (3rd Goal) ********** */
  chassis.turnToAngle(175, 90, 1.0).waitUntilSettled(); // Turn towards goal
  chassis.driveToPoint(-38, -60, 90, 2.2); // Drive towards goal
  uptake.move(90);
  chassis.move(40, 'B'); // Constant pressure on 3rd goal
  intake.waitUntilColor(color, 2.2); // Wait until middle color ball (opponents color) is inside intakes (Prevent ovvercycling of balls)
  uptake.stop();
  chassis.waitUntilSettled();
  chassis.stop().brake();

  /* ********** Drive away from goal ********** */
  chassis.drive(-24, 100, 1.0); // Drive away from goal
  intake.move(-100);
  delay(100); // Outake opponents ball
  uptake.move(-100);
  chassis.waitUntilSettled();
  intake.stop();
  uptake.stop();
}
