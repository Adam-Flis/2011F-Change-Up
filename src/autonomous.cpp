#include "main.h"
#include "define.hpp"
#include "autonomous.hpp"

void autonomous() {

  Intake_Optical.set_led_pwm(100);

  //skills();
  homeRow('B');
  //homeRow('R');

}
