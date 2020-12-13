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

  // Changes color of inputted alliance to opponents alliance for waitUntillColor function
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
  chassis.driveToPoint(0, 33.5, 85, 1.4).waitUntilSettled();
  chassis.turnToAngle(90, 85, 1.1).waitUntilSettled(); // Turn towards goal
  intake.move(100);
  chassis.driveToPoint(35, 35, 85, 1.9); // Drive towards goal
  uptake.move(100);
  delay(400);
  chassis.move(30, 'B'); // Constant pressure on 1st goal
  intake.waitUntillColor(color, 0.9); // Wait untill middle color ball (opponents color) is inside intakes (Prevent ovvercycling of balls)
  delay(125); // Ball settling time
  uptake.stop();
  chassis.waitUntilSettled();

  /* ********** Drive away from goal ********** */
  chassis.drive(-36, 90, 1.7); // Drive away from goal
  intake.move(-100);
  delay(300); // Outake blue balls
  uptake.move(-100);
  chassis.waitUntilSettled(); // Outake middle color ball while driving backwards
  uptake.stop();
  intake.stop();

  /* ********** Drive across the field ********** */
  chassis.turnToAngle(-140, 85, 1.2).waitUntilSettled(); // Turn to drive across the field
  chassis.driveToPoint(-40, -13, 85, 1.9).waitUntilSettled(); // Drive across the field

  /* ********** 2nd Corner Goal (3rd Goal) ********** */
  chassis.turn(-48, 85, 1.0).waitUntilSettled(); // Turn towards goal
  chassis.driveToPoint(-50, -60, 90, 2.3); // Drive towards goal
  uptake.move(100);
  delay(400);
  chassis.move(30, 'B'); // Constant pressure on 3rd goal
  intake.waitUntillColor(color, 1.05); // Wait untill middle color ball (opponents color) is inside intakes (Prevent ovvercycling of balls)
  delay(125); // Ball settling time
  uptake.stop();
  chassis.waitUntilSettled();

  /* ********** Drive away from goal ********** */
  chassis.drive(-24, 100, 1.0); // Drive away from goal
  intake.move(-100);
  delay(300); // Outake blue balls
  uptake.move(-100);
  chassis.waitUntilSettled();
  intake.stop();
  uptake.stop();
}
