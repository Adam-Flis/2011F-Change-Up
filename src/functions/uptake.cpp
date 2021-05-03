#include "main.h"
#include "define.hpp"
#include "functions/uptake.hpp"
#include "functions/math.hpp"

Uptake::Uptake(){}
Uptake::~Uptake(){}

Uptake uptake;
static Math math;

// Define variables
bool Uptake::isRunning = false,
     Uptake::isShooting = false,
     Uptake::hasColor = false,
     Uptake::getValue = false;

char Uptake::desiredColorB, Uptake::currentColorB, Uptake::desiredColorM, Uptake::currentColorM;

double Uptake::velocity, Uptake::voltage, Uptake::timeOut;

int Uptake::position, Uptake::desiredAmount, Uptake::currentAmount;

/**
 * Stops the uptakes
 */
Uptake& Uptake::stop() {
  velocity = 0;
  voltage = 0;
  LU.move_velocity(0);
  RU.move_velocity(0);
  return *this;
}

/**
 * Sets the brake mode of the uptakes to brake
 */
void Uptake::brake() {
  LU.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RU.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

/**
 * Sets the brake mode of the uptakes to coast
 */
void Uptake::coast() {
  LU.set_brake_mode(MOTOR_BRAKE_COAST);
  RU.set_brake_mode(MOTOR_BRAKE_COAST);
}

/**
 * Sets the brake mode of the uptakes to hold
 */
void Uptake::hold() {
  LU.set_brake_mode(MOTOR_BRAKE_HOLD);
  RU.set_brake_mode(MOTOR_BRAKE_HOLD);
}

/**
 * Sets the voltage of the uptakes
 * @param voltage -100 to 100 (In percentage of max uptake speed)
 */
Uptake& Uptake::moveVolt(double voltage_) {
  velocity = 0;
  voltage = math.percentToVoltage(voltage_);
  LU.move_voltage(voltage);
  RU.move_voltage(voltage);
  return *this;
}

/**
 * Sets the velocity of the uptakes
 * @param velocity -100 to 100 (In percentage of max uptake speed)
 */
Uptake& Uptake::moveVel(double velocity_) {
  voltage = 0;
  velocity = math.percentToVelocity(velocity_, 'B');
  LU.move_velocity(velocity);
  RU.move_velocity(velocity);
  return *this;
}

/**
 * Returns current ball color at bottom position ('R', 'B', 'N')
 */
char Uptake::getColorB() {
  getValue = true;
  delay(20);
  return uptake.currentColorB;
  getValue = false;
}

/**
 * Returns current ball color at middle position ('R', 'B', 'N')
 */
char Uptake::getColorM() {
  getValue = true;
  delay(20);
  return uptake.currentColorM;
  getValue = false;
}

/**
 * Waits until a certain ball color is detected in the uptakes
 * Pervents overcycling of balls in autonomous
 * @param color 'B' or 'R' (Ball color; Blue or Red)
 * @param position 1 or 2 (Uptake position; Bottom or Middle)
 * @param timeOut (In seconds)
 */
Uptake& Uptake::color(char color_, int position_, double timeOut_) {
  position = position_;
  if (position == 1) {
    desiredColorB = color_;
    desiredColorM = 'O';
  } else if (position == 2) {
    desiredColorM = color_;
    desiredColorB = 'O';
  }
  timeOut = math.secToMillis(timeOut_) + millis();
  isShooting = false;
  hasColor = false;
  getValue = true;
  return *this;
}

/**
 * Waits until the uptake has desired color
 */
Uptake& Uptake::waitForColor() {
  while (!hasColor) delay(20);
  return *this;
}

/**
 * Resets the shot counter value
 */
void Uptake::resetCount() {
  currentAmount = 0;
}

/**
 * Return the shot counter value
 */
int Uptake::getCount() {
  getValue = true;
  delay(20);
  return uptake.currentAmount;
  getValue = false;
}

/**
 * Waits until ball/s are shot into the goal
 * Accurately shoot a desired number of ball/s
 * @param amount (Number of balls to shoot)
 * @param timeOut (In seconds)
 */
 Uptake& Uptake::shot(int amount_, double timeOut_) {
   desiredAmount = amount_ + currentAmount;
   timeOut = math.secToMillis(timeOut_) + millis();
   hasColor = true;
   isShooting = true;
   getValue = true;
   return *this;
}

/**
 * Waits until the uptake has has shot desired amount
 */
Uptake& Uptake::waitForShot() {
  while (isShooting) delay(20);
  return *this;
}


/**
 * Starts the uptake task
 */
void Uptake::start() {
  isRunning = true;
  isShooting = false;
  hasColor = true;
  getValue = false;
  uptake.resetCount();
  Bottom_Uptake_Optical.set_led_pwm(0);
  Middle_Uptake_Optical.set_led_pwm(0);
  string printColorB, printColorM;
  double hueB, proxB,
         hueM, proxM;
  bool passed = true;
  delay(300);

  while (isRunning) {

    if (getValue) {

      // Bottom optical sensor
      hueB = Bottom_Uptake_Optical.get_hue();
      proxB = Bottom_Uptake_Optical.get_proximity();

      if (hueB <= redThresh && proxB >= 220) {
        currentColorB = 'R';
        //printColorB = "Red";
      } else if (hueB >= blueThresh && proxB >= 220) {
        currentColorB = 'B';
        //printColorB = "Blue";
      } else {
        currentColorB = 'N';
        //printColorB = "Not Blue/Red";
      }

      // Middle optical sensor
      hueM = Middle_Uptake_Optical.get_hue();
      proxM = Middle_Uptake_Optical.get_proximity();

      if (hueM <= redThresh && proxM >= 220) {
        currentColorM = 'R';
        //printColorM = "Red";
      } else if (hueM >= blueThresh && proxM >= 220) {
        currentColorM = 'B';
        //printColorM = "Blue";
      } else {
        currentColorM = 'N';
        //printColorM = "Not Blue/Red";
      }

      // Distance sensor counting logic
      if (Distance_Sensor.get() <= distanceThresh && passed) {
        passed = false;
        currentAmount ++;
      } else if (Distance_Sensor.get() > distanceThresh && !passed) {
        passed = true;
      }

      // // Sets voltage or velocity of uptakes
      // if (voltage != 0) {
      //   LU.move_voltage(voltage);
      //   RU.move_voltage(voltage);
      // } else if (velocity != 0) {
      //   LU.move_velocity(velocity);
      //   RU.move_velocity(velocity);
      // }

      // Detection logic for cycling functions
      if (!hasColor && !isShooting) { // Color
        if (millis() >= timeOut) {
          hasColor = true;
          getValue = false;
        } else if (desiredColorB == currentColorB) {
          hasColor = true;
          getValue = false;
        } else if (desiredColorM == currentColorM) {
          hasColor = true;
          getValue = false;
        }
      } else if (hasColor && isShooting) { // Shooting
        if (millis() >= timeOut) {
          isShooting = false;
          getValue = false;
        } else if (desiredAmount == currentAmount) {
          isShooting = false;
          getValue = false;
        }
      }

      // Display variables to LCD display
      // Useful for debugging
      // lcd::print(6, "Bottom Uptake Color: %s \n", printColorB);
      // lcd::print(6, "Middle Uptake Color: %s \n", printColorM);
      // lcd::print(7, "Count: %i \n", currentAmount);
    }
    delay(20);
  }
}

/**
 * Ends the uptake task
 */
void Uptake::end() {
  if (uptakeTask != nullptr) {
    uptake.stop().brake(); // Stops uptake
    isRunning = false;
    uptakeTask->remove(); // Removes memory stack task is occupying
    delete uptakeTask; // Deletes the task from memory
    uptakeTask = nullptr;
    Bottom_Uptake_Optical.set_led_pwm(0); // Turn off optical sensor LED
    Middle_Uptake_Optical.set_led_pwm(0);
  }
}
