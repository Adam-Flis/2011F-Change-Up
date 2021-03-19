#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

void autonomous() {
  Intake_Optical.set_led_pwm(100); // Turn on optical sensor LED
  Bottom_Uptake_Optical.set_led_pwm(100); // Turn on optical sensor LED
  Middle_Uptake_Optical.set_led_pwm(100);

  homeRow('B');

  //chassis.driveToPoint(0, 48, 90, 'Y').waitUntillSettled();
  //chassis.turnToAngle(90, 90, 'B').waitUntillSettled();
  //chassis.arcToPoint(24, 24, 90, 'Y').waitUntillSettled();
  //chassis.stop();

}
