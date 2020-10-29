#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"


void opcontrol() {

  Chassis chassis;
  Odom odom;
  Math math;

  // chassis.turnToAngle(-45, 50, 2).waitUntilSettled();
  // delay(1000);
  chassis.brake();

  while(1) {
    lcd::print(0, "X: %f \n", odom.getX());
    lcd::print(1, "Y: %f \n", odom.getY());
    lcd::print(2, "Theta: %f degress\n", odom.getTheta());
    lcd::print(3, "Left: %f in\n", math.ticksToInch(LEnc.get_value()));
    lcd::print(4, "Right: %f in\n", math.ticksToInch(REnc.get_value()));
    lcd::print(5, "L: %d ticks\n", LEnc.get_value());
    lcd::print(6, "R: %d ticks\n", REnc.get_value());

    /* ********** Drivetrain ********** */

    LFD.move(Main.get_analog(ANALOG_LEFT_Y)); // Left joystick pushed or pulled, move left drive
    LBD.move(Main.get_analog(ANALOG_LEFT_Y));
    RFD.move(Main.get_analog(ANALOG_RIGHT_Y)); // Right joystick pushed or pulled, move right drive
    RBD.move(Main.get_analog(ANALOG_RIGHT_Y));

    /* ********** Ball Uptakes ********** */

    if (Main.get_digital(DIGITAL_L1)) { // Button L1 pressed, uptake balls
      TU.move_velocity(600);
      BU.move_velocity(600);
    } else if (Main.get_digital(DIGITAL_L2)) { // Button L2 pressed, downtake balls
      TU.move_velocity(-600);
      BU.move_velocity(-600);
    } else { // Nothing pressed, stop uptake
      TU.set_brake_mode(MOTOR_BRAKE_BRAKE);
      BU.set_brake_mode(MOTOR_BRAKE_BRAKE);
      TU.move_velocity(0);
      BU.move_velocity(0);
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
