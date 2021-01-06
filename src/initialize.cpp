#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"

// Code that runs when you start the program
void initialize() {
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

  trackingTask = new Task(odom.startTask, TASK_PRIORITY_MAX, TASK_STACK_DEPTH_DEFAULT, "Track Task");
  chassisTask = new Task(chassis.startTask, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_MIN, "Chassis Task");
  lcd::set_text(0, "Tasks Initalizing");
  cout<<"Tasks Initializing"<<endl;
  delay(1000);
  cout<<trackingTask<<endl; // Print to console task information
  cout<<chassisTask<<endl;
  cout<<"Tasks Done Initializing"<<endl;

  lcd::set_text(0, "Ready To Go!"); // Message to let user know robot is all initalized
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
