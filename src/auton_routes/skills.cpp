#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

/**
 *
 */
void skills () {

  intake.moveVolt(-100); // Deploy
  delay(150);
  intake.stop().brake();

  chassis.moveVel(40);
  delay(125);
  chassis.moveVel(40, 'R');
  chassis.moveVel(15, 'L');
  delay(750);

  // Cycle 1st goal
  intake.moveVolt(100);
  uptake.moveVolt(100).color('B', 1, 0.6).waitForColor();
  intake.moveVolt(-100);
  uptake.stop().brake();
  chassis.turnToAngle(-90, 100, 0.5).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  chassis.driveToPoint(5.5, 12, 100, 'X', 1.0, -90, true).withMultiplier(1.4).waitUntillSettled(); // Drive away from 1st goal
  chassis.turnToAngle(-135, 100, 0.4).waitUntillSettled();
  intake.moveVel(-100); // Discard of blue ball
  uptake.moveVolt(-100);
  delay(100);

  chassis.turnToAngle(0, 80, 1.4); // Turn towards ball on line
  chassis.waitUntillSettled();
  uptake.stop();
  intake.moveVolt(100);
  chassis.driveToPoint(5, 53, 100, 'Y', 1.4, 0); // Drive towards ball on line
  uptake.moveVolt(70).color('R', 1, 1.4).waitForColor().stop();
  chassis.waitUntillSettled();

  chassis.turnToAngle(20, 100, 0.8).waitUntillSettled(); // Turn towards wall ball
  chassis.driveToPoint(14.5, 77, 100, 'Y', 1.65, 20); // Drive towards wall ball
  intake.moveVolt(100).color('R', 1.65).waitForColor();
  chassis.waitUntillSettled();

  chassis.driveToPoint(5, 55, 100, 'Y', 1.1, 20, true).withMultiplier(1.4); // Drive away from wall
  uptake.moveVolt(50).color('R', 2, 0.5).waitForColor().stop(); // Index red balls
  intake.stop();
  chassis.waitUntillSettled();
  chassis.turnToAngle(-45, 100, 0.8).waitUntillSettled(); // Turn towards 2nd goal
  chassis.driveToPoint(-9, 80, 100, 'Y', 1.1, -45).withMinVel(40).waitUntillSettled(); // Drive towards 2nd goal
  chassis.moveVel(15);

  // Cycle 2nd goal
  intake.moveVolt(100);
  uptake.moveVolt(90).color('B', 2, 1.2).waitForColor().stop();
  intake.stop();
  //chassis.turnToAngle(-45, 100, 1.0).withMultiplier(2.5).waitUntillSettled(); // Align on goal
  if (intake.getColor() == 'B') {
    intake.moveVolt(100);
  } else {
    intake.moveVel(-10);
  }

  chassis.driveToPoint(26, 35, 100, 'X', 2.0, -45, true).withMultiplier(1.25); // Drive away from 2nd goal
  delay(600);
  uptake.moveVolt(100); // Discard blue balls
  delay(1000);
  intake.stop();
  uptake.stop();
  chassis.waitUntillSettled();

  chassis.turnToAngle(90, 75, 1.4).waitUntillSettled(); // Turn towards mid field
  intake.moveVolt(100);
  chassis.driveToPoint(47, 37, 100, 'X', 1.2, 90);
  uptake.moveVolt(80).color('R', 1, 1.4).waitForColor().stop();
  chassis.waitUntillSettled(); // Drive towards mid field
  chassis.turnToAngle(0, 85, 1.0).waitUntillSettled();

  chassis.driveToPoint(50, 75, 100, 'Y', 1.3, 0).withMinVel(40).waitUntillSettled(); // Drive towards 3rd goal
  chassis.moveVel(15);

  // Cycle 3rd goal
  uptake.moveVolt(100).color('B', 1, 1.0).waitForColor();
  delay(150);
  uptake.stop();
  intake.moveVel(-100);
  chassis.turnToAngle(0, 100, 0.5).withMultiplier(2.5).waitUntillSettled(); // Align on goal

  chassis.driveToPoint(50, 48, 100, 'Y', 1.4, 0, true).withMultiplier(1.4); // Drive away from 3rd goal

}
