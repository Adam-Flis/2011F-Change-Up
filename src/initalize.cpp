#include "main.h"
#include "functions/lift.hpp"

// Code that runs when you start the program
void initialize(){
  lcd::initialize();
<<<<<<< Updated upstream
  Lift lift;
  Task liftTask(lift.startTask, NULL, "Lift Task");
  delay(1000);
  cout<<"Tasks initialized"<<endl;
=======
  // Lift lift;
  // Task liftTask(lift.startTask, NULL, "Lift Task");
  // delay(1000);
  // cout<<"Tasks initialized"<<endl;
  //Task chassisController(chassis.start, NULL, "Chassis Controller");
>>>>>>> Stashed changes
}

// Code that runs when the robot is in the disabled state by the competition switch or the field controller
void disabled(){

}

// Code that runs after initalize when connected to a competition switch or field controller
void competition_initialize(){

}
