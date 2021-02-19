#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"


void opcontrol() {

  Chassis chassis; // Defines classes
  Odom odom;

  Intake_Optical.set_led_pwm(0); // Turn off optical sensor LED
  Uptake_Optical.set_led_pwm(0);
  //odom.endTask(); // End tasks to prevent brain overload
  chassis.brake();
  //lcd::clear();
  //lcd::shutdown(); // Turns off LCD display

  while(1) {

    /* ********** Drivetrain ********** */

    LFD.move(Main.get_analog(ANALOG_LEFT_Y)); // Left joystick pushed or pulled, move left drive
    LBD.move(Main.get_analog(ANALOG_LEFT_Y));
    RFD.move(Main.get_analog(ANALOG_RIGHT_Y)); // Right joystick pushed or pulled, move right drive
    RBD.move(Main.get_analog(ANALOG_RIGHT_Y));

    /* ********** Ball Uptakes ********** */

    if (Main.get_digital(DIGITAL_L1)) { // Button L1 pressed, uptake balls
      LU.move_voltage(12000);
      RU.move_voltage(12000);
    } else if (Main.get_digital(DIGITAL_L2)) { // Button L2 pressed, downtake balls
      LU.move_voltage(-12000);
      RU.move_voltage(-12000);
    } else { // Nothing pressed, stop uptake
      LU.set_brake_mode(MOTOR_BRAKE_BRAKE);
      RU.set_brake_mode(MOTOR_BRAKE_BRAKE);
      LU.move_velocity(0);
      RU.move_velocity(0);
    }

    /* ********** Ball Intakes ********** */

    if (Main.get_digital(DIGITAL_R1)) { // Button L1 pressed, intake balls
      LI.move_voltage(12000);
      RI.move_voltage(12000);
    } else if (Main.get_digital(DIGITAL_R2)) { // Button L2 pressed, outtake balls
      LI.move_voltage(-12000);
      RI.move_voltage(-12000);
    } else { //Nothing pressed, stop intake
      LI.set_brake_mode(MOTOR_BRAKE_BRAKE);
      RI.set_brake_mode(MOTOR_BRAKE_BRAKE);
      LI.move_velocity(0);
      RI.move_velocity(0);
    }

    delay(10); // Loop speed, prevent overload
  }
}
