#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

void autonomous() {
  // Intake_Optical.set_led_pwm(100); // Turn on optical sensor LED
  // Bottom_Uptake_Optical.set_led_pwm(100); // Turn on optical sensor LED
  // Middle_Uptake_Optical.set_led_pwm(100);

  //chassis.driveToPoint(0, 48, 90, 'Y').waitUntillSettled();
  chassis.turnToAngle(90, 80, 'B', true).waitUntillSettled();
  chassis.stop();

}
