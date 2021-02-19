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

  char opponentColor;
  if (color == 'B') {
    opponentColor = 'R';
  } else {
    opponentColor = 'B';
  }

  // Deploy
  intake.move(100);
  delay(300);

  chassis.driveToPoint(0, 57, 80, 0.5, 'Y'); // Drive towards mid field
  delay(250);
  uptake.move(100);
  delay(150);
  uptake.stop();

  chassis.driveToPoint(0, 30, 22.5, 0.5, 'Y', true); // Drive away from mid field
  delay(50);

  chassis.turnToAngle(-135, 90); // Turn towards corner goal
  delay(50);

  chassis.driveToPoint(-22, 8, 90, 1, 'Y', false, false); // Drive towards corner goal

  // Cycle corner goal
  uptake.move(100);
  intake.move(100);
  delay(100);
  uptake.waitUntilColor(opponentColor, 1.5);
  intake.move(-100);
  delay(80);
  uptake.move(-30);

  chassis.driveToPoint(-4, 26, 20, 1, 'Y', true); // Drive away from goal
  uptake.stop();
  delay(50);

  chassis.turnToAngle(-270, 85); // Turn towards far wall
  delay(50);
  intake.stop();

  chassis.arcToPoint(34, 0, 180, 1.4, 50, false, false); // Arc to middle wall goal

  // Cycle middle wall goal
  uptake.move(100);
  intake.move(100);
  delay(100);
  uptake.waitUntilColor(opponentColor, 1.5);
  intake.move(-100);
  delay(140);
  uptake.move(-50);

  chassis.driveToPoint(34, 12, 30, 1, 'Y', true); // Drive away from goal
  uptake.stop();
  delay(50);

  chassis.turnToAngle(-270, 85); // Turn towards far wall
  delay(50);
  intake.stop();
}
