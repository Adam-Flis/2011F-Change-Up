#include "main.h"
#include "functions/lift.hpp"
#include "functions/odometry.hpp"

// Code that runs when you start the program
void initialize(){
  lcd::initialize();
  Odom odom;
  // Lift lift;
  // Task liftTask(lift.startTask, NULL, "Lift Task");
  // delay(1000);
  // cout<<"Tasks initialized"<<endl;
  //Task chassisController(chassis.start, NULL, "Chassis Controller");
  Task trackingTask(odom.track, NULL, "Tracking Task");
  delay(1000);
  lcd::set_text(2, "Tasks Initalized");
  cout<<"Tasks Initialized"<<endl;
  delay(2000);
  lcd::clear();
}

// Code that runs when the robot is in the disabled state by the competition switch or the field controller
void disabled(){

}

// Code that runs after initalize when connected to a competition switch or field controller
void competition_initialize(){

}
