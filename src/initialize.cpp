#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"

// Code that runs when you start the program
void initialize() {
<<<<<<< testing
  lcd::initialize();
  Chassis chassis;
  Odom odom;
  IMU.reset();
  delay(20);
  // while (IMU.is_calibrating()){
  //   lcd::set_text(0, "IMU Calibrating");
  //   delay(10);
  // }
  cout<<"IMU Calibrated"<<endl;
=======

  lcd::initialize();
  Chassis chassis; //Define classes
  Odom odom;

  /* ********** Calibrate IMU ********** */

  IMU.reset();
  delay(20);
  while (IMU.is_calibrating()){
    lcd::set_text(0, "IMU Calibrating");
    delay(10);
  }
  cout<<"IMU Calibrated"<<endl;

  /* ********** Initalize Chassis and Odometry Tasks ********** */

>>>>>>> master
  Task chassisTask(chassis.startTask, NULL, "Chassis Task");
  Task trackTask(odom.startTask, NULL, "Track Task");
  lcd::set_text(0, "Tasks Initalizing");
  cout<<"Tasks initializing"<<endl;
  delay(500);
<<<<<<< testing
  lcd::set_text(0, "Ready To Go!");
=======

  lcd::set_text(0, "Ready To Go!"); // Message to let user know robot is all initalized
>>>>>>> master
  cout<<"Ready"<<endl;
  delay(500);
  lcd::clear_line(0);
}

// Code that runs when the robot is in the disabled state by the competition switch or the field controller
void disabled() {

}

// Code that runs after initalize when connected to a competition switch or field controller
void competition_initialize() {

}
