#include "main.h"
#include "define.hpp"
#include "functions/intake.hpp"

Intake::Intake(){}
Intake::~Intake(){}

/* ********** Both Ball Intakes ********** */

/**
 * Stops both the bottom and top ball intakes
 */
Intake& Intake::stop(){
  BLI.move_velocity(0);
  BRI.move_velocity(0);
  TI.move_velocity(0);
  return *this;
};

/**
 * Set velocity of both the bottom and top ball intakes
 * @param velocity_ = +- 600
 */
void Intake::setVelocity(int velocity_){
  BLI.move_velocity(velocity_);
  BRI.move_velocity(velocity_);
  TI.move_velocity(velocity_);
}

/**
 * Sets the brake mode of both the bottom and top ball intakes to brake
 */
void Intake::brake(){
  BLI.set_brake_mode(MOTOR_BRAKE_BRAKE);
  BRI.set_brake_mode(MOTOR_BRAKE_BRAKE);
  TI.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

/* ********** Bottom Ball Intakes ********** */

/**
 * Stops the bottom ball intakes
 */
void Intake::Bottom::stop(){
  BLI.move_velocity(0);
  BRI.move_velocity(0);
}

/**
 * Sets velocity of the bottom ball inatkes
 * @param velocity_ = +- 600
 */
void Intake::Bottom::setVelocity(int velocity_){
  BLI.move_velocity(velocity_);
  BRI.move_velocity(velocity_);
}

/* ********** Top Ball Intake ********** */

/**
 * Stops the top ball inatke
 */
void Intake::Top::stop(){
  TI.move_velocity(0);
}

/**
 * Sets velocity of the top ball inatke
 * @param velocity_ = +- 600
 */
void Intake::Top::setVelocity(int velocity_){
  TI.move_velocity(velocity_);
}
