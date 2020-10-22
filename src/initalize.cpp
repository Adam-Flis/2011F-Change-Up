#include "main.h"
#include "define.hpp"

// Code that runs when you start the program
void initialize() {
  lcd::initialize();
  // Lift lift;
  // Task liftTask(lift.startTask, NULL, "Lift Task");
  // delay(1000);
  // cout<<"Tasks initialized"<<endl;
  //Task chassisController(chassis.start, NULL, "Chassis Controller");
  IMU.reset();
  //Task trackTask(odom.track, NULL, "Track Task");
  while (IMU.is_calibrating()){}
  //lcd::set_text(1, "Tasks and IMU Initalized");
  //cout << "Tasks and IMU Initialized" << endl;
  delay(1000);
}

// Code that runs when the robot is in the disabled state by the competition switch or the field controller
void disabled() {

}

// Code that runs after initalize when connected to a competition switch or field controller
void competition_initialize() {

}
