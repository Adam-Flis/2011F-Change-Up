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

  /* ********** Middle Goal (1st Ball) ********** */
  uptake.move(100);
  delay(950); // Deploy hood and shoot preload ball into middle goal
  uptake.stop();

  /* ********** 1st Corner Goal (2nd Ball) ********** */
  chassis.driveToPoint(0, 29.7, 85, 1.35).waitUntilSettled();
  chassis.turnToAngle(92.5, 85, 1.25).waitUntilSettled(); // Turn towards goal
  intake.move(100);
  chassis.driveToPoint(34.5, 24.5, 90, 1.4); // Drive towards goal
  delay(500);
  uptake.move(100);
  uptake.waitUntillShot(2, 1.0); // Shoots 2 balls into the goal
  uptake.move(70);
  intake.move(70);
  intake.waitUntillColor(color, 1.0); // Wait untill middle color ball (opponents color) is inside intakes (Prevent ovvercycling of balls)
  uptake.waitUntillIndexed(0.2); // Index ball
  uptake.stop();
  chassis.waitUntilSettled();

  // Old stuff //
  /*
  delay(400);
  uptake.move(100); // Sends ball infront of goal up
  delay(650);
  intake.move(40);
  intake.waitUntillColor(color, 1.0);
  delay(150);
  uptake.stop();
  chassis.waitUntilSettled();
  */

  /* ********** Drive across the field ********** */
  chassis.driveToPoint(0, 18, 85, 1.65, true); // Drive away from goal
  delay(100);
  intake.move(-100);
  uptake.move(-100);
  chassis.waitUntilSettled(); // Outake middle color ball while driving backwards
  uptake.stop();
  intake.stop();

  /* ********** 2nd Corner Goal (3rd Ball) ********** */
  chassis.turnToAngle(-135, 80, 1.2).waitUntilSettled(); // Turn to drive across the field
  chassis.driveToPoint(-44, -16, 85, 2.1).waitUntilSettled(); // Drive across the field
  chassis.turnToAngle(170, 65, 0.4).waitUntilSettled(); // Turn towards goal
  intake.move(100);
  chassis.driveToPoint(-35, -53, 90, 1.1); // Drive towards goal
  uptake.move(100);
  uptake.waitUntillShot(2, 1.2); // Shoots 2 balls into the goal
  uptake.move(100);
  intake.move(100);
  intake.waitUntillColor(color, 1.0); // Wait untill middle color ball (opponents color) is inside intakes (Prevent overshooting of balls)
  uptake.waitUntillIndexed(0.2); // Index ball
  uptake.stop();
  chassis.waitUntilSettled();

  // Old stuff //
  /*
  delay(100);
  uptake.move(100); // Sends ball infront of goal up
  delay(850);
  intake.move(40);
  intake.waitUntillColor(color, 5);
  chassis.waitUntilSettled();
  delay(200);
  uptake.stop();
  */

  chassis.drive(-24, 100, 1.0); // Drive away from goal
  intake.stop();
  chassis.waitUntilSettled();
}
