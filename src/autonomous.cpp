#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

void autonomous() {

  float time = millis();

  Intake_Optical.set_led_pwm(100); // Turn on optical sensor LED
  Bottom_Uptake_Optical.set_led_pwm(100);
  Middle_Uptake_Optical.set_led_pwm(100);

/* ********** Select what autonomous to run ********** */

  //homeRow('R');
  //homeRow('B');
  //rightCorner('R');
  rightCorner('B');
  //skills();

/* ************************************************** */

  //chassis.driveToPoint(0, 48, 100, 'Y', 10.0, 0).waitUntillSettled();
  //chassis.turnToAngle(90, 100, 10.0).waitUntillSettled();
  //chassis.stop();
  //intake.moveVel(100);

  time = (millis() - time)/1000;

  // Display how long autonomous period took
  lcd::print(7, "Time: %0.01f", time);

}
