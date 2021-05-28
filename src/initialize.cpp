#include "main.h"
#include "define.hpp"
#include "functions/odometry.hpp"
#include "functions/chassis.hpp"
#include "functions/intake.hpp"
#include "functions/uptake.hpp"

// Code that runs when you start the program
void initialize() {
  lcd::initialize();
  Odom odom;
  Intake intake;
  Uptake uptake;
  Chassis chassis;

  float timer = millis();

  // Calibrate and initalize IMUs
  LIMU.reset();
  RIMU.reset();
  delay(50);
  while (LIMU.is_calibrating() || RIMU.is_calibrating()) delay(20);

  lcd::set_text(0, "IMU Calibrated");

  // Initalize Tasks
  trackingTask = new Task(odom.start, TASK_PRIORITY_MAX, TASK_STACK_DEPTH_DEFAULT, "Tracking Task");
  delay(50);
  chassisTask = new Task(chassis.start, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Chassis Task");
  delay(50);
  uptakeTask = new Task(uptake.start, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_MIN, "Uptake Task");
  delay(300);

  lcd::set_text(1, "Tasks Initalized");
  lcd::print(2, "Initalization took: %f ms\n", millis() - timer);
  delay(1500);

}

// Code that runs when the robot is in the disabled state by the competition switch or the field controller
void disabled() {

}

// Code that runs after initalize when connected to a competition switch or field controller
void competition_initialize() {

}
