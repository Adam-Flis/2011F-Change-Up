#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

/**
 * Cycle 2 balls into the center
 */
void center() {
  float time = millis();

  intake.moveVolt(-100); // Deploy
  delay(150);
  intake.moveVolt(100);

  chassis.driveToPoint(0, 44, 100, 'Y', 1.3, 0).waitUntillSettled(); // Drive towards center field
  delay(200);

  chassis.driveToPoint(0, 18, 80, 'Y', 1.4, 0, true).waitUntillSettled(); // Drive away from center field
  chassis.stop();

  chassis.turnToAngle(47, 90, 1.0).waitUntillSettled();

  chassis.driveToPoint(28, 44, 100, 'X', 1.5, 47).waitUntillSettled(); // Drive towards center goal
  chassis.move(40);
  delay(300);
  chassis.stop();

  intake.moveVolt(100);
  uptake.moveVolt(100);
  delay(2500);
  intake.stop().brake();
  uptake.moveVolt(-100);
  delay(500);
  uptake.moveVolt(100);
  delay(1000);
  intake.stop().brake();
  uptake.stop().brake();
  while (time + 14700 > millis()) delay(10);

  intake.moveVolt(-100);
  chassis.move(-80);
  delay(50);
  intake.stop();
  delay(250);
  uptake.stop();
  chassis.stop().coast();

}
