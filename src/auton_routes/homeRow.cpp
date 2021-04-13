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
  intake.brake();
  uptake.brake();
  intake.move(-100);
  delay(500); // Deploy hood and shoot preload ball into middle goal
  intake.stop();

  /* ********** 1st Corner Goal (2nd Goal) ********** */
  chassis.driveToPoint(0, 34, 80, 1.25).waitUntilSettled();
  chassis.turnToAngle(90, 85, 0.8).waitUntilSettled(); // Turn towards goal
  intake.move(100);
  chassis.driveToPoint(35, 35, 75, 1.8); // Drive towards goal
  intake.move(100);
  //chassis.move(40, 'B'); // Constant pressure on 1st goal
  uptake.move(100);
  uptake.waitUntilColor(color, 1.8); // Wait until middle color ball (opponents color) is inside intakes (Prevent ovvercycling of balls)
  intake.stop();
  delay(50);
  uptake.stop();
  chassis.waitUntilSettled();
  chassis.stop().brake();
  chassis.turnToAngle(90, 100, 1.3).waitUntilSettled(); // Align on goal

  /* ********** Drive away from goal ********** */
  chassis.drive(-34, 85, 1.2); // Drive away from goal
  intake.move(-100);
  delay(100); // Outake opponents ball
  uptake.move(-100);
  chassis.waitUntilSettled();
  uptake.stop();
  intake.stop();

  /* ********** Drive across the field ********** */
  chassis.turnToAngle(-140, 85, 1.25).waitUntilSettled(); // Turn to face downfield
  delay(50);
  chassis.drive(66, 65, 2.0).waitUntilSettled(); // Drive across the field

  /* ********** 2nd Corner Goal (3rd Goal) ********** */
  chassis.turnToAngle(175, 90, 0.9).waitUntilSettled(); // Turn towards goal
  chassis.driveToPoint(-42, -64, 75, 2.5); // Drive towards goal
  intake.move(100);
  //chassis.move(40, 'B'); // Constant pressure on 3rd goal
  uptake.move(100);
  uptake.waitUntilColor(color, 2.5); // Wait until middle color ball (opponents color) is inside intakes (Prevent ovvercycling of balls)
  intake.stop();
  delay(50);
  uptake.stop();
  chassis.waitUntilSettled();
  chassis.stop().brake();

  /* ********** Drive away from goal ********** */
  chassis.drive(-18, 100, 0.8); // Drive away from goal
  delay(100);
  intake.move(-100);
  delay(100); // Outake opponents ball
  uptake.move(-100);
  chassis.waitUntilSettled();
  intake.stop();
  uptake.stop();
  chassis.turnToAngle(-45, 90, 2.0);
}
