#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"
#include "functions/intake.hpp"
#include "functions/uptake.hpp"


void opcontrol() {

  Chassis chassis; // Defines classes
  Odom odom;
  Math math;
  Intake intake;
  Uptake uptake;

  Intake_Optical.set_led_pwm(0); // Turn off optical sensor LED
  odom.endTask(); // End tasks to prevent brain overload
  chassis.endTask();
  chassis.brake();
  lcd::clear();
  lcd::shutdown();

  while(1) {

    /* ********** Testing of sensors ********** */
    // Commented out for match to prevent brain overload

    // lcd::print(0, "X: %f \n", odom.getX());
    // lcd::print(1, "Y: %f \n", odom.getY());
    // lcd::print(2, "Theta: %f degress\n", odom.getTheta());
    //lcd::print(3, "Theta: %f radians\n", odom.getRadians());
    // lcd::print(4, "Vertical: %f in\n", math.ticksToInch(VEnc.get_value()));
    // lcd::print(5, "Horizontial: %f in\n", math.ticksToInch(HEnc.get_value()));
    // /lcd::print(6, "L: %d ticks\n", LEnc.get_value());
    // lcd::print(6, "Avg Wrap: %f ticks\n", math.encoderAverage());
    // lcd::print(7, "Avg Raw: %f ticks\n", math.encoderAverage());
    // lcd::print(7, "R: %d ticks\n", REnc.get_value());

    /* ********** Drivetrain ********** */

    LFD.move(Main.get_analog(ANALOG_LEFT_Y)); // Left joystick pushed or pulled, move left drive
    LBD.move(Main.get_analog(ANALOG_LEFT_Y));
    RFD.move(Main.get_analog(ANALOG_RIGHT_Y)); // Right joystick pushed or pulled, move right drive
    RBD.move(Main.get_analog(ANALOG_RIGHT_Y));

    /* ********** Ball Uptakes ********** */

    if (Main.get_digital(DIGITAL_L1)) { // Button L1 pressed, uptake balls
      LU.move_velocity(600);
      RU.move_velocity(600);
    } else if (Main.get_digital(DIGITAL_L2)) { // Button L2 pressed, downtake balls
      LU.move_velocity(-600);
      RU.move_velocity(-600);
    } else { // Nothing pressed, stop uptake
      LU.set_brake_mode(MOTOR_BRAKE_BRAKE);
      RU.set_brake_mode(MOTOR_BRAKE_BRAKE);
      LU.move_velocity(0);
      RU.move_velocity(0);
    }

    /* ********** Ball Intakes ********** */

    if (Main.get_digital(DIGITAL_R1)) { // Button L1 pressed, intake balls
      LI.move_velocity(600);
      RI.move_velocity(600);
    } else if (Main.get_digital(DIGITAL_R2)) { // Button L2 pressed, outtake balls
      LI.move_velocity(-600);
      RI.move_velocity(-600);
    } else { //Nothing pressed, stop intake
      LI.set_brake_mode(MOTOR_BRAKE_BRAKE);
      RI.set_brake_mode(MOTOR_BRAKE_BRAKE);
      LI.move_velocity(0);
      RI.move_velocity(0);
    }

    delay(10); // Loop speed, prevent overload
  }
}
