#include "main.h"
#include "define.hpp"
#include "functions/intake.hpp"
#include "functions/math.hpp"

Intake::Intake(){}
Intake::~Intake(){}

Intake intake;
static Math math;

// Define variables
bool Intake::isRunning = false,
     Intake::hasColor = false;

char Intake::desiredColor, Intake::currentColor;

double Intake::velocity, Intake::voltage, Intake::timeOut;

/**
 * Stops the intakes
 */
Intake& Intake::stop() {
  velocity = 0;
  voltage = 0;
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
 * Sets the brake mode of the intakes to coast
 */
void Intake::coast() {
  LI.set_brake_mode(MOTOR_BRAKE_COAST);
  RI.set_brake_mode(MOTOR_BRAKE_COAST);
}

/**
 * Sets the brake mode of the intakes to hold
 */
void Intake::hold() {
  LI.set_brake_mode(MOTOR_BRAKE_HOLD);
  RI.set_brake_mode(MOTOR_BRAKE_HOLD);
}

/**
 * Sets the voltage of the intakes
 * @param voltage -100 to 100 (In percentage of max intake speed)
 */
Intake& Intake::moveVolt(double voltage_) {
  velocity = 0;
  voltage = math.percentToVoltage(voltage_);
  return *this;
}

/**
 * Sets the velocity of the intakes
 * @param velocity -100 to 100 (In percentage of max intake speed)
 */
Intake& Intake::moveVel(double velocity_) {
  voltage = 0;
  velocity = math.percentToVelocity(velocity_, 'B');
  return *this;
}

/**
 * Returns current ball color ('R', 'B', 'N')
 */
char Intake::getColor() {
  return intake.currentColor;
}

/**
 * Waits until a certain ball color is detected in the intakes
 * Pervents overcycling of balls in autonomous
 * @param color 'B' or 'R' (Ball color; Blue or Red)
 * @param timeOut (In seconds)
 */
Intake& Intake::color(char color_, double timeOut_) {
  desiredColor = color_;
  timeOut = math.secToMillis(timeOut_) + millis();
  hasColor = false;
  return *this;
}

/**
 * Waits until the intake has desired color
 */
Intake& Intake::waitForColor() {
  while (!hasColor) delay(20);
  return *this;
}

/**
 * Starts the intake task
 */
void Intake::start() {
  isRunning = true;
  hasColor = true;
  Intake_Optical.set_led_pwm(0);
  string printColor;
  double hue, prox;

  while (isRunning) {

    hue = Intake_Optical.get_hue();
    prox = Intake_Optical.get_proximity();

    if (voltage != 0) {
      LI.move_voltage(voltage);
      RI.move_voltage(voltage);
    } else if (velocity != 0) {
      LI.move_velocity(velocity);
      RI.move_velocity(velocity);
    }

    if (hue <= redThresh && prox >= 245) {
      currentColor = 'R';
      printColor = "Red";
    } else if (hue >= blueThresh && prox >= 245) {
      currentColor = 'B';
      printColor = "Blue";
    } else {
      currentColor = 'N';
      printColor = "Not Blue/Red";
    }

    if (!hasColor) {
      if (millis() >= timeOut) {
        hasColor = true;
      } else if (desiredColor == currentColor) {
        hasColor = true;
      }
    }

    //lcd::print(6, "Inatke Color: %s \n", printColor);
    delay(20);
  }
}

/**
 * Ends the intake task
 */
void Intake::end() {
  if (intakeTask != nullptr) {
    intake.stop().brake(); // Stops intakes
    isRunning = false;
    intakeTask->remove(); // Removes memory stack task is occupying
    delete intakeTask; // Deletes the task from memory
    intakeTask = nullptr;
    Intake_Optical.set_led_pwm(0); // Turn off optical sensor LED
  }
}
