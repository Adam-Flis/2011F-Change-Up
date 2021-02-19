#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

void middleGoal() {
  /* ********** Deploy hood ********** */
  intake.brake();
  uptake.brake();
  intake.move(100);
  delay(500); // Deploy hood
  intake.stop();

  /* ********** Middle goal ********** */

  chassis.driveToPoint(0, 36, 80, 2.5).waitUntilSettled();
  delay(100);
  chassis.turnToAngle(45, 80, 1.5).waitUntilSettled();
  delay(7500); // Wait to drive towards middle goal
  chassis.driveToPoint(24, 48, 70, 2.0).waitUntilSettled();
  uptake.move(100);
  delay(550); // Score in middle goal
  chassis.move(-60, 'B'); // Drive away from goal
  delay(300);
  chassis.stop();
}
