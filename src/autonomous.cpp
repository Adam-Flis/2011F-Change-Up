#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

void autonomous() {

  float time = millis();

  Intake_Optical.set_led_pwm(100); // Turn on optical sensor LED
  Bottom_Uptake_Optical.set_led_pwm(100);
  Middle_Uptake_Optical.set_led_pwm(100);

  //homeRow('R');
  //rightCorner('R');
  skills();

  //chassis.driveToPoint(0, 48, 100, 'Y', 10.0, 0).waitUntillSettled();
  // chassis.turnToAngle(90, 100, 5.0).waitUntillSettled();
  //chassis.arcToPoint(24, 24, 90, 'Y').waitUntillSettled();
  //chassis.stop();

  time = (millis() - time)/1000;

  lcd::print(7, "Time: %0.01f", time);

}
