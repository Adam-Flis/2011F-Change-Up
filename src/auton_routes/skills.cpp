#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

void skills () {
  uptake.move(100);
  delay(950); // Deploy hood
  uptake.stop();
  intake.move(100);
  intake.waitUntillColor('R', 0.5);
  uptake.move(50);
  uptake.waitUntillIndexed(0.5); // Index ball
  uptake.stop();
  chassis.drive(26, 80, 1.5).waitUntilSettled();
  intake.stop();

  /* ********** 1st Goal ********** */
  chassis.turnToAngle(-130, 80, 1.2).waitUntilSettled(); // Turn towards 1st goal
  chassis.drive(33, 85, 2.0).waitUntilSettled(); // Drive towards 1st goal
  uptake.move(100);
  uptake.waitUntillShot(1, 0.5); // Score in 1st goal
  uptake.stop();
  chassis.drive(-14, 80, 1.5).waitUntilSettled(); // Drive away from 1st goal
  uptake.move(50);
  intake.move(100);
  uptake.waitUntillIndexed(0.5); // Index ball
  uptake.stop();

  /* ********** 2nd Goal ********** */
  chassis.turnToAngle(0, 85, 1.5).waitUntilSettled();
  chassis.drive(47, 90, 2.0); // Drive towards middle of the field
  intake.waitUntillColor('R', 1.5); // Grab ball
  chassis.waitUntilSettled();
  intake.stop();
  chassis.turnToAngle(-90, 80, 1.5).waitUntilSettled(); // Turn towards 2nd goal
  chassis.drive(12, 80, 1.0).waitUntilSettled(); // Drive towards 2nd goal
  uptake.move(100);
  uptake.waitUntillShot(1, 0.7); // Score in 2nd goal
  uptake.stop();
  chassis.drive(-18, 90, 1.3).waitUntilSettled(); // Drive away from 2nd goal
  uptake.move(50);
  intake.move(100);
  uptake.waitUntillIndexed(0.5); // Index ball
  uptake.stop();
  intake.stop();

  /* ********** 3rd Goal ********** */
  chassis.turnToAngle(2.5, 80, 2.0).waitUntilSettled();
  chassis.drive(54, 85, 2.0); // Drive to far side of field
  intake.move(100);
  intake.waitUntillColor('R', 1.5); // Grab ball
  intake.move(20);
  chassis.waitUntilSettled();
  chassis.drive(-18, 80, 1.0).waitUntilSettled(); // Drive away from wall
  chassis.turnToAngle(-55, 80, 1.2).waitUntilSettled(); // Turn towards 3rd goal
  chassis.drive(36, 80, 1.5).waitUntilSettled(); // Drive to 3rd goal
  uptake.move(100);
  uptake.waitUntillShot(1, 0.7); // Score in 3rd goal
  uptake.stop();
  chassis.drive(-36, 80, 0.8).waitUntilSettled(); // Drive away from 3rd goal
  intake.move(100);
  uptake.move(100);
  uptake.waitUntillIndexed(0.5); // Index ball
  uptake.stop();

  /* ********** 4th Goal ********** */
  chassis.turnToAngle(-90, 60, 0.8).waitUntilSettled();
  chassis.drive(36, 80, 1.3); // Drive at wall
  intake.waitUntillColor('R', 1.3); // Grab ball
  intake.move(30);
  chassis.waitUntilSettled();
  chassis.drive(-55, 90, 2.3).waitUntilSettled(); // Drive across the field (backwards)
  chassis.turnToAngle(0, 80, 1.2).waitUntilSettled(); // Turn to 4th goal
  intake.stop();
  chassis.drive(24, 80, 1.0).waitUntilSettled(); // Drive to 4th goal
  uptake.move(100);
  uptake.waitUntillShot(1, 0.7); // Score in 4th goal
  uptake.stop();
  chassis.drive(-12, 80, 0.7).waitUntilSettled(); // Drive away from 4th goal
  intake.move(100);
  uptake.move(100);
  uptake.waitUntillIndexed(0.5); // Index ball
  uptake.stop();

  /* ********** 5th Goal ********** */
  chassis.turnToAngle(90, 80, 1.5).waitUntilSettled();
  chassis.drive(60, 90, 2.5).waitUntilSettled(); // Drive across the field
  chassis.drive(-12, 80, 1.0).waitUntilSettled(); // Drive away from the wall
  chassis.turnToAngle(50, 80, 1.3).waitUntilSettled(); // Turn to 5th goal
  intake.stop();
  chassis.drive(24, 80, 1.0).waitUntilSettled(); // Drive to 5th goal
  uptake.move(100);
  uptake.waitUntillShot(1, 0.7); // Score in 5th goal
  uptake.stop();
  chassis.drive(-12, 80, 0.8).waitUntilSettled(); // Drive away from 5th goal
  intake.move(100);
  uptake.move(100);
  uptake.waitUntillIndexed(0.5); // Index ball
  uptake.stop();

}
