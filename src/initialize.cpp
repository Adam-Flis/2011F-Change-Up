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

  // Calibrate IMUs
  LIMU.reset();
  RIMU.reset();
  delay(50);
  while (LIMU.is_calibrating() || RIMU.is_calibrating()) delay(20);

  lcd::set_text(0, "IMU Calibrated");

  // Initalize Tasks
  trackingTask = new Task(odom.start, TASK_PRIORITY_MAX, TASK_STACK_DEPTH_DEFAULT, "Tracking Task");
  delay(300);
  chassisTask = new Task(chassis.start, TASK_PRIORITY_MAX, TASK_STACK_DEPTH_DEFAULT, "Chassis Task");
  delay(300);
  intakeTask = new Task(intake.start, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Intake Task");
  delay(300);
  uptakeTask = new Task(uptake.start, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Uptake Task");
  delay(300);

  lcd::set_text(1, "Tasks Initalized");
  lcd::print(2, "Initalization took: %f ms\n", millis() - timer);
  delay(1000);

}

// Code that runs when the robot is in the disabled state by the competition switch or the field controller
void disabled() {

}

// Code that runs after initalize when connected to a competition switch or field controller
void competition_initialize() {

}
