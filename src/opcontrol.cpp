#include "main.h"
#include "define.hpp"
#include "functions/odometry.hpp"
#include "functions/chassis.hpp"
#include "functions/intake.hpp"
#include "functions/uptake.hpp"


void opcontrol() {

  Odom odom;
  Intake intake;
  Uptake uptake;
  Chassis chassis;

  // LFD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  // LBD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  // RFD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  // RBD.set_brake_mode(MOTOR_BRAKE_BRAKE);

  odom.end();
  chassis.end();
  intake.end();
  uptake.end();
  lcd::clear();
  lcd::shutdown();
  chassis.brake();

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

    if (Main.get_digital(DIGITAL_R1)) { // Button R1 pressed, intake balls
      LI.move_voltage(12000);
      RI.move_voltage(12000);
    } else if (Main.get_digital(DIGITAL_R2)) { // Button R2 pressed, outtake balls
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
