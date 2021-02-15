#include "main.h"
#include "define.hpp"
#include "functions/odometry.hpp"

// Code that runs when you start the program
void initialize() {
  lcd::initialize();
  Odom odom;

  /* ********** Calibrate IMU ********** */

  LIMU.reset();
  RIMU.reset();
  delay(20);
  while (LIMU.is_calibrating() || RIMU.is_calibrating()){
    lcd::set_text(0, "IMU Calibrating");
    delay(10);
  }
  cout<<"IMU Calibrated"<<endl;

  /* ********** Initalize Chassis and Odometry Tasks ********** */

  trackingTask = new Task(odom.startTask, TASK_PRIORITY_MAX, TASK_STACK_DEPTH_DEFAULT, "Track Task");
  lcd::set_text(0, "Tasks Initalizing");
  cout<<"Tasks Initializing"<<endl;
  delay(1500);
  cout<<trackingTask<<endl; // Print to console task information
  cout<<"Tasks Done Initializing"<<endl;
}

// Code that runs when the robot is in the disabled state by the competition switch or the field controller
void disabled() {

}

// Code that runs after initalize when connected to a competition switch or field controller
void competition_initialize() {

}
