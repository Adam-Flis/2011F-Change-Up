#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/intake.hpp"
#include "functions/lift.hpp"

void opcontrol() {

  Chassis chassis;
  Intake intakes;
  Lift lift;
  Intake::Bottom bottom;
  Intake::Top top;

  chassis.brake();
  intakes.brake();

  lift.move(-100, 500, 5000).waitUntilSettled();

  top.move(200);

  delay(10000);


  while(1){

    /* ********** Drivetrain ********** */

    LFD.move(Main.get_analog(ANALOG_LEFT_Y)); // Left joystick pushed or pulled, move left drive
    LBD.move(Main.get_analog(ANALOG_LEFT_Y));
    RFD.move(Main.get_analog(ANALOG_RIGHT_Y)); // Right joystick pushed or pulled, move right drive
    RBD.move(Main.get_analog(ANALOG_RIGHT_Y));

    /* ********** Lift ********** */

    if (Main.get_digital(DIGITAL_R1)) { // Button R1 pressed, lift up
      lift.move(200);
    } else if (Main.get_digital(DIGITAL_R2)) { // Button R2 pressed, lift down
      lift.move(-200);
    } else {
      lift.stop().setBrakeMode(); // Stops lift and sets brake mode
    }

    /* ********** Both Ball Intakes ********** */

    if (lift.getPot() <= lift.bothIntakesLimit) {
      if (Main.get_digital(DIGITAL_L1) || Main.get_digital(DIGITAL_A)){ // Button L1 or A pressed, intake on both intakes
        intakes.move(600);
      } else if (Main.get_digital(DIGITAL_L2) || Main.get_digital(DIGITAL_B)){ // Button L2 or B pressed, outake on both intakes
        intakes.move(-600);
      } else {
        intakes.stop(); //Stops both intakes
      }
    }

    /* ********** Bottom Ball Intake ********** */

    if (lift.getPot() > lift.bothIntakesLimit) {
      if (Main.get_digital(DIGITAL_L1)) { // Button L1 pressed, intake balls
        bottom.move(600);
      } else if (Main.get_digital(DIGITAL_L2)) { // Button L2 pressed, outtake balls
        bottom.move(-600);
      } else {
        bottom.stop(); // Stops bottom intakes
      }
    }

    /* ********** Top Ball Intake ********** */

    if (lift.getPot() > lift.bothIntakesLimit) {
      if (Main.get_digital(DIGITAL_A)) { // Button A pressed, intake balls
        top.move(600);
      } else if (Main.get_digital(DIGITAL_B)) { // Button B pressed, outake balls
        top.move(-600);
      } else {
        top.stop(); // Stops top intake
      }
    }

    delay(10); // Loop speed, prevent overload
  }
}
