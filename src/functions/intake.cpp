#include "main.h"
#include "define.hpp"
#include "functions/intake.hpp"

/* ********** Both Ball Intakes ********** */

/**
 * Stops both the bottom and top ball intakes
 */
Intake& Intake::stop() {
  BLI.move_velocity(0);
  BRI.move_velocity(0);
  TI.move_velocity(0);
  return *this;
};

/**
 * Set velocity of both the bottom and top ball intakes
 * @param velocity = +- 600
 */
void Intake::move(int velocity) {
  BLI.move_velocity(velocity);
  BRI.move_velocity(velocity);
  TI.move_velocity(velocity);
}

/**
 * Sets the brake mode of both the bottom and top ball intakes to brake
 */
void Intake::brake() {
  BLI.set_brake_mode(MOTOR_BRAKE_BRAKE);
  BRI.set_brake_mode(MOTOR_BRAKE_BRAKE);
  TI.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

/* ********** Bottom Ball Intakes ********** */

/**
 * Stops the bottom ball intakes
 */
void Intake::Bottom::stop() {
  BLI.move_velocity(0);
  BRI.move_velocity(0);
}

/**
 * Sets velocity of the bottom ball inatkes
 * @param velocity = +- 600
 */
void Intake::Bottom::move(int velocity) {
  BLI.move_velocity(velocity);
  BRI.move_velocity(velocity);
}

/* ********** Top Ball Intake ********** */

/**
 * Stops the top ball inatke
 */
void Intake::Top::stop() {
  TI.move_velocity(0);
}

/**
 * Sets velocity of the top ball inatke
 * @param velocity = +- 600
 */
void Intake::Top::move(int velocity) {
  TI.move_velocity(velocity);
}
