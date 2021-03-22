#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"


  void homeRow2(char color) {
    // Changes color of inputted alliance to opponents alliance for waituntilColor function
    char opponentColor;
    if (color == 'B') {
      opponentColor = 'R';
    } else if (color == 'R') {
      opponentColor = 'B';
    }

    chassis.move(75, 'L');
    chassis.move(20, 'R');
    delay(800);
    chassis.stop();
    chassis.turnToAngle(45, 100, 1.3);
    uptake.move(100);
    intake.move(100);
    uptake.waitUntilColor(opponentColor, 1.2); // Cycle 1st goal
    delay(50);
    uptake.stop();
    intake.move(-50);
    chassis.waitUntilSettled();
    uptake.stop();

    chassis.driveToPoint(-14, -4, 80, 1.1, true); // Drive away from goal
    delay(400);
    intake.move(-100);
    uptake.move(-40);
    uptake.waitUntilColor(color, 1.0);
    uptake.stop();
    intake.stop();
    chassis.waitUntilSettled();

    chassis.turnToAngle(180, 85, 1.1).waitUntilSettled(); // Turn to face down field

    chassis.driveToPoint(-14, -41, 80, 1.45).waitUntilSettled(); // Drive across field

    chassis.turnToAngle(90, 85, 1.0).waitUntilSettled(); // Turn to face 2nd goal

    chassis.driveToPoint(12, -41, 100, 1.0).waitUntilSettled(); // Drive towards 2nd goal

    intake.move(100);
    uptake.move(100);
    chassis.turnToAngle(90, 100, 1.3);
    uptake.waitUntilColor(opponentColor, 1.7); // Cycle 2nd goal
    intake.stop();
    delay(50);
    uptake.stop();
    delay(200);
    chassis.waitUntilSettled();

    chassis.driveToPoint(-14, -42, 100, 1.1, true); // Drive away from 2nd goal
    delay(200);
    intake.move(-100);
    uptake.move(-100);
    delay(500);
    intake.stop();
    uptake.stop();
    chassis.waitUntilSettled();

    chassis.turnToAngle(-35, 85, 1.0).waitUntilSettled(); // Turn to face down field

    chassis.turnToAngle(180, 85, 1.0).waitUntilSettled(); // Turn to face down field

    chassis.driveToPoint(-14, -82.5, 85, 1.4).waitUntilSettled(); // Drive across the field

    chassis.turnToAngle(135, 85, 1.0).waitUntilSettled(); // Turn to face 3rd goal

    chassis.driveToPoint(12, -112, 100, 1.1); // Drive towards 3rd goal
    intake.move(50);
    chassis.waitUntilSettled();
    intake.move(100);
    chassis.turnToAngle(135, 100, 1.2);
    uptake.move(100);
    uptake.waitUntilColor(opponentColor, 1.2);
    uptake.stop();
    intake.move(-100);
    chassis.waitUntilSettled();
    delay(100);

    intake.move(-100);
    chassis.driveToPoint(-14, -83, 100, 1.2, true).waitUntilSettled();

  }
