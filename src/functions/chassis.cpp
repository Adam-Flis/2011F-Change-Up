#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"
#include "functions/pid.hpp"
#include "functions/math.hpp"


Chassis::Chassis(){}
Chassis::~Chassis(){}

Chassis chassis; // Class definition
static Math math;
static PID pid;
static Odom odom;

/* ********** Define variables ********** */

float kP_D = 0,
      kI_D = 0,
      kD_D = 0,

      kP_T = 0,
      kI_T = 0,
      kD_T = 0,

      kP_DA = 0,
      kI_DA = 0,
      kD_DA = 0,

      kP_TA = 0,
      kI_TA = 0,
      kD_TA = 0;


float errorX,
      errorY,
      errorTheta,
      errorTicks,
      lastErrorTicks,
      errorRotation,
      targetVelocity,
      targetX,
      targetY,
      targetTheta,
      driveVelocity,
      turnVelocity,
      velocityL,
      velocityR,
      drift,
      timeOut,

      proportionD,
      integralD,
      integralZoneD = 10,
      integralLimitD = 10 * kI_D,
      derivativeD,
      turnD = 0.1, dTurn, lastErrorR;

bool reversed;

char side;

/**
 * Stops the chassis
 */
Chassis& Chassis::stop() {
  LFD.move_velocity(0);
  LBD.move_velocity(0);
  RFD.move_velocity(0);
  RBD.move_velocity(0);
  return *this;
}

/**
 * Sets the brake mode of the chassis to brake
 */
void Chassis::brake() {
  LFD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  LBD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RFD.set_brake_mode(MOTOR_BRAKE_BRAKE);
  RBD.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

/**
 * Sets the brake mode of the chassis to hold
 */
void Chassis::hold() {
  LFD.set_brake_mode(MOTOR_BRAKE_HOLD);
  LBD.set_brake_mode(MOTOR_BRAKE_HOLD);
  RFD.set_brake_mode(MOTOR_BRAKE_HOLD);
  RBD.set_brake_mode(MOTOR_BRAKE_HOLD);
}

/**
 * Sets the brake mode of the chassis to coast
 */
void Chassis::coast() {
  LFD.set_brake_mode(MOTOR_BRAKE_COAST);
  LBD.set_brake_mode(MOTOR_BRAKE_COAST);
  RFD.set_brake_mode(MOTOR_BRAKE_COAST);
  RBD.set_brake_mode(MOTOR_BRAKE_COAST);
}

/**
 * Sets velocity of chassis side/s
 * @param velocity -100 to 100 (In percentage of drive max speed)
 * @param side 'L', 'R', or 'B' (Side of drive that will move; Left, Right, or Both)
 */
void Chassis::move(float velocity, char side) {
  if (side == 'L') {
    LFD.move_velocity(math.percentToVelocity(velocity, 'G'));
    LBD.move_velocity(math.percentToVelocity(velocity, 'G'));
  } else if (side == 'R') {
    RFD.move_velocity(math.percentToVelocity(velocity, 'G'));
    RBD.move_velocity(math.percentToVelocity(velocity, 'G'));
  } else if (side == 'B') {
    LFD.move_velocity(math.percentToVelocity(velocity, 'G'));
    RFD.move_velocity(math.percentToVelocity(velocity, 'G'));
    LBD.move_velocity(math.percentToVelocity(velocity, 'G'));
    RBD.move_velocity(math.percentToVelocity(velocity, 'G'));
  }
}

/**
 * Resets the chassis variables
 */
void Chassis::reset() {
  isSettled = true;
  chassis.stop().brake();
}

/**
 * Starts the chassis drive task
 */
void Chassis::startTask() {
  isRunning = true;
  isSettled = false;
  isTurning = false;
  isDriving = false;
  isArcing = false;

  chassis.reset();
  cout<<"Chassis Task Started"<<endl;
  while(isRunning) {
    if (!isSettled) {
      if (isTurning) {
        // velocity = pid.turn(errorTheta, targetVelocity);
        // if (side == 'B') {
        //   velocityL = velocity;
        //   velocityR = -velocity;
        // } else if (side == 'L') {
        //   velocityL = velocity;
        //   velocityR = 0;
        // } else if (side == 'R') {
        //   velocityL = 0;
        //   velocityR = -velocity;
        // }
      } else if (isDriving) {

        errorX = math.filter(targetX, odom.getX());
        errorY = math.filter(targetY, odom.getY());

        errorTicks = sqrt(errorX * errorX + errorY * errorY);

        errorRotation = (math.angleIn180(math.radToDeg(atan2(errorX, errorY))) -
                        math.angleIn180(math.radToDeg(odom.getTheta())));

        proportionD = errorTicks;

        if(fabs(errorTicks) < integralZoneD && errorTicks != 0){
            integralD = integralD + errorTicks;
        } else {
            integralD = 0;
        }
        if(integralD > integralLimitD){
            integralD = integralLimitD;
        }

    derivativeD = errorTicks - lastErrorTicks;
    lastErrorTicks = errorTicks;

    driveVelocity = (kP_D * proportionD + kI_D * integralD + kD_D * derivativeD);
    if(driveVelocity > targetVelocity){
      driveVelocity = targetVelocity;
    }
    if(driveVelocity < -targetVelocity){
      driveVelocity = -targetVelocity;
    }
    if (reversed) {
      driveVelocity = -driveVelocity;
    }

    dTurn = fabs(errorR) - lastErrorR;
    turnVelocity = dTurn * turnD;
    lastErrorR = fabs(errorR);

    finalVL = (driveVelocity + turnVelocity);
    finalVR = (driveVelocity - turnVelocity);
    if(errorType == "y"){
      if(fabs(errorY) < pctCutoff){
        enabled = false;
      }
    }
    else if(errorType == "x"){
      if(fabs(errorX) < pctCutoff){
        enabled = false;
      }
    }
    else if(errorType == "d"){
      if(fabs(errorD) < pctCutoff){
        enabled = false;
      }

    }
    lDrive_V(finalVL * 2);
    rDrive_V(finalVR * 2);
  }
}
      } else if (isArcing) {
        velocityArr = pid.arc(errorX, errorY, targetVelocity);
        velocityL = velocityArr[0];
        velocityR = velocityArr[1];
      }

      if (timeOut <= millis()) {
        chassis.reset();
      } else if (targetX <= odom.getX()) {
        chassis.reset();
      } else if (targetY <= odom.getY()) {
        chassis.reset();
      } else if (targetTheta <= math.radToDeg(odom.getTheta())) {
        chassis.reset();
      }

      LFD.move_velocity(velocityL);
      RFD.move_velocity(velocityR);
      LBD.move_velocity(velocityL);
      RBD.move_velocity(velocityR);
    }
    delay(10); // Loop speed, prevent overload
  }
}

Chassis& Chassis::driveToPoint(float targetX_, float targetY_, float targetVelocity_, float timeOut_, bool reversed_) {
  if (isRunning) {
    targetX = targetX_;
    targetY = targetY_;
    reversed = reversed_;
    targetVelocity = math.percentToVelocity(targetVelocity_, 'G');
    timeOut = math.secToMillis(timeOut_) + millis();
    isDriving = true;
    isTurning = false;
    isArcing = false;
    isSettled = false;
  }
  return *this;
}




/**
 * Moves the chassis a certain distance using a PID loop
 * @param distance (In inches -backwards +forwards)
 * @param targetVelocity_ 0 to 100 (In percentage of drive max speed)
 * @param timeOut_ (In seconds)
 */
Chassis& Chassis::drive(float distance, float targetVelocity_, float timeOut_) {
  if (isRunning) {
    errorTicks = math.inchToTicks(distance);
    targetVelocity = math.percentToVelocity(targetVelocity_, 'G');
    timeOut = math.secToMillis(timeOut_) + millis();
    isDriving = true;
    isTurning = false;
    isArcing = false;
    isSettled = false;
  }
  return *this;
}

/**
 * Truns the chassis a certain degress using a PID loop
 * @param theta_ (In degress -180 to 180)
 * @param targetVoltage_ 0 to 100 (In percentage of drive max speed)
 * @param timeOut_ (In seconds)
 */
Chassis& Chassis::turn(float theta, float targetVelocity_, float timeOut_) {
  if (isRunning) {
    errorTheta = theta;
    targetVelocity = math.percentToVelocity(targetVelocity_, 'G');
    timeOut = math.secToMillis(timeOut_) + millis();
    isDriving = false;
    isTurning = true;
    isArcing = false;
    isSettled = false;
  }
  return *this;
}

/**
 * Ends the chassis drive task
 */
void Chassis::endTask() {
  if (chassisTask != nullptr) {
    chassisTask->remove(); // Removes memory stack task is occupying
    delete chassisTask; // Deletes the task from memory
    chassisTask = nullptr;
    cout<<"Chassis task ended"<<endl;
  }
}

/**
 * Waits until the chassis has settled
 */
void Chassis::waitUntilSettled() {
  while(!isSettled) {
    delay(10); // Loop speed, prevent overload
  }
}
