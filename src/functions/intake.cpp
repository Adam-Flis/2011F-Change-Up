 #include "main.h"
#include "define.hpp"
#include "functions/intake.hpp"
#include "functions/math.hpp"

Intake::Intake(){}
Intake::~Intake(){}

Intake intake; // Class definition
static Math math;


/**
 * Stops the intakes
 */
Intake& Intake::stop() {
  LI.move_velocity(0);
  RI.move_velocity(0);
  return *this;
}

/**
 * Sets the brake mode of the intakes to brake
 */
void Intake::brake() {
  LI.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RI.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

/**
 * Sets the speed of the intakes
 * @param velocity -100 to 100 (In percentage of max intake speed)
 */
void Intake::move(float velocity) {
  LI.move_velocity(math.percentToVelocity(velocity, 'B'));
  RI.move_velocity(math.percentToVelocity(velocity, 'B'));
}

/**
 * Waits untill a certain ball color is detected in the intakes
 * Pervents overcycling of balls in autonomous
 * @param color 'B', or 'R' (Ball color; Blue or Red)
 * @param timeOut (In seconds)
 * @param reverse True or False (Whether or not at goal to run intakes slower; true by default)
 */
void Intake::waitUntillColor(char color, float timeOut, bool atGoal) {
  Intake_Optical.set_led_pwm(100); // Turn on optical sensor LED
  timeOut = math.secToMillis(timeOut) + millis();
  double low_hue;
  double high_hue;

  // Sets low and high hue variables
  if (color == 'B') {
    low_hue = 220;
    high_hue = 280;
  } else if (color == 'R') {
    low_hue = 005;
    high_hue = 020;
  } else { // Ends function if a char that is not 'B' or 'R' is inputted
    timeOut = millis();
  }
  if (atGoal) {
    intake.move(70); // Start intakes
  } else if (!atGoal) {
    intake.move(90); // Start intakes
  }

  while (1) {
    if (low_hue <= Intake_Optical.get_hue() && Intake_Optical.get_hue() <= high_hue) { // Breaks loop when ball hue is in range
      break;
    }
    else if (millis() >= timeOut) { // Breaks loop when timeout is reached
      break;
    }
    delay(20); // Loop speed, prevent overload
  }
  intake.stop(); // Stop intakes
  Intake_Optical.set_led_pwm(0); // Turn off optical sensor LED
}
