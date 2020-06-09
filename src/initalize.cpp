#include "main.h"
#include "functions/lift.hpp"

// Code that runs when you start the program
void initialize(){
  Lift lift;
  Task liftController(lift.start, NULL, "Lift Controller");
}

// Code that runs when the robot is in the disabled state by the competition switch or the field controller
void disabled(){

}

// Code that runs after initalize when connected to a competition switch or field controller
void competition_initialize(){

}
