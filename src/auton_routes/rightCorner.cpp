#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

/**
 * Partner autonomous
 * Full cycle right corner goal then defend center goal
 * Line up on right of the field facing the right wall with
 * left side of drive wheels on the white line
 */
void rightCorner() {

  intake.moveVolt(-100); // Deploy
  delay(150);
  intake.moveVolt(100);

  // Drive towards 1st goal
  chassis.stop().brake();
  chassis.move(80, 'L');
  chassis.move(20, 'R');
  delay(425);
  chassis.move(20);

  // Cycle 1st goal
  delay(50);
  chassis.stop().brake();
  uptake.resetCount();
  chassis.stop().brake();
  uptake.moveVolt(100).shot(3, 1.75).waitForShot(); // Shoot 3 balls in 1st goal
  // float time = millis() + 400;
  // bool ball = true;
  // while (uptake.getColorB() != color || uptake.getColorM() != color || millis() <= time) {
  //   uptake.moveVolt(-80);
  //   ball = false;
  // }
  // if (ball) {
  //   uptake.moveVolt(100);
  //   delay(400);
  // }
  delay(120);
  uptake.stop().brake();
  intake.moveVel(-10);
  chassis.turnToAngle(45, 100, 0.5).withMultiplier(2.5).waitUntillSettled(); // Align on goal

  chassis.driveToPoint(-18.5, -9, 100, 'X', 1.4, 45, true).waitUntillSettled(); // Drive away from first goal

  chassis.turnToAngle(27, 65, 1.8).waitUntillSettled();

  delay(1600);

  chassis.driveToPoint(-28, -44, 100, 'Y', 1.9, 27, true).waitUntillSettled();

  chassis.turnToAngle(-96, 65, 0.8).waitUntillSettled();

  intake.moveVolt(-100);
  chassis.driveToPoint(-49.2, -42.5, 100, 'X', 1.0, -96).waitUntillSettled(); // Drive towards middle goal
  chassis.driveToPoint(-41, -42.5, 100, 'X', 0.8, -96, true).waitUntillSettled(); // Drive away from middle goal

  chassis.driveToPoint(-49.2, -42.5, 100, 'X', 1.0, -96).waitUntillSettled(); // Drive towards middle goal
  chassis.driveToPoint(-41, -42.5, 100, 'X', 0.8, -96, true).waitUntillSettled(); // Drive away from middle goal

  chassis.driveToPoint(-49.2, -42.5, 100, 'X', 1.0, -96).waitUntillSettled(); // Drive towards middle goal
  chassis.driveToPoint(-41, -42.5, 100, 'X', 0.8, -96, true).waitUntillSettled(); // Drive away from middle goal

  chassis.driveToPoint(-49.2, -42.5, 100, 'X', 1.0, -96).waitUntillSettled(); // Drive towards middle goal
  chassis.driveToPoint(-41, -42.5, 100, 'X', 0.8, -96, true).waitUntillSettled(); // Drive away from middle goal

  chassis.driveToPoint(-49.2, -42.5, 100, 'X', 1.0, -96).waitUntillSettled(); // Drive towards middle goal
  chassis.driveToPoint(-41, -42.5, 100, 'X', 0.8, -96, true).waitUntillSettled(); // Drive away from middle goal

  chassis.driveToPoint(-47.2, -42.5, 100, 'X', 1.0, -96).waitUntillSettled(); // Drive towards middle goal
  chassis.driveToPoint(-39, -42.5, 100, 'X', 0.8, -96, true).waitUntillSettled(); // Drive away from middle goal

  chassis.driveToPoint(-47.2, -42.5, 100, 'X', 1.0, -96).waitUntillSettled(); // Drive towards middle goal
  chassis.driveToPoint(-39, -42.5, 100, 'X', 0.8, -96, true).waitUntillSettled(); // Drive away from middle goal

  chassis.driveToPoint(-47.2, -42.5, 100, 'X', 1.0, -96).waitUntillSettled(); // Drive towards middle goal
  chassis.driveToPoint(-39, -42.5, 100, 'X', 0.8, -96, true).waitUntillSettled(); // Drive away from middle goal

}
