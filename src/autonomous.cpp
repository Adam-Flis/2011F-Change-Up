#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

void autonomous() {

  Intake_Optical.set_led_pwm(100); // Turn on optical sensor LED

  //skills();
  //homeRow('B');
  homeRow('R');

}
