#include "main.h"
#include "define.hpp"

// Code that runs when you start the program
void initialize() {
  lcd::initialize();
  Task chassisTask(chassis.startTask, NULL, "Chassis Task");
  Task trackTask(odom.startTask, NULL, "Track Task");
  cout<<"Tasks initialized"<<endl;
  IMU.reset();
  while (IMU.is_calibrating()){}
  cout << "IMU Initialized" << endl;
  lcd::set_text(0, "Tasks and IMU Initalized");
  delay(1000);
  lcd::clear_line(0);
}

// Code that runs when the robot is in the disabled state by the competition switch or the field controller
void disabled() {

}

// Code that runs after initalize when connected to a competition switch or field controller
void competition_initialize() {

}
