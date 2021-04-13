#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

void middleGoal() {
  /* ********** Deploy hood ********** */
  intake.brake();
  uptake.brake();
  intake.move(-100);
  delay(500); // Deploy hood
  intake.stop();
  delay(8000); // Wait to drive towards middle goal

  /* ********** Middle goal ********** */

  chassis.driveToPoint(0, 36, 80, 2.5).waitUntilSettled();
  delay(100);
  chassis.turnToAngle(45, 80, 1.5).waitUntilSettled();
  delay(100);
  chassis.driveToPoint(24, 48, 70, 2.0).waitUntilSettled();
  uptake.waitUntilShot(1, 500);
  chassis.move(-60, 'B'); // Drive away from goal
  delay(300);
  chassis.stop();
}

void u() {

  /* ********** Deploy hood ********** */
  intake.brake();
  uptake.brake();
  intake.move(-100);
  delay(500); // Deploy hood
  intake.stop();

  delay(11000);

  chassis.drive(24, 85, 0.75).waitUntilSettled();

  chassis.turnToAngle(120, 85, 0.75).waitUntilSettled();

  chassis.drive(24, 85, 0.7).waitUntilSettled();

  chassis.move(35, 'B');
  intake.move(100);
  uptake.move(100);
  intake.waitUntilColor('R', 0.5);
  intake.stop();
  uptake.waitUntilColor('B', 0.5);
  uptake.stop();
  chassis.stop();
  intake.move(-100);

  chassis.drive(-12, 100, 0.5).waitUntilSettled();
  intake.stop();

  chassis.turnToAngle(0, 80, 1.0).waitUntilSettled();

}
