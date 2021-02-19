#include "main.h"
#include "define.hpp"
#include "functions/chassis.hpp"
#include "functions/odometry.hpp"
#include "functions/math.hpp"

Chassis::Chassis(){}
Chassis::~Chassis(){}

Chassis chassis; // Class definition
static Math math;
static Odom odom;

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

//-Drive to Point---------------------------------------------------------------
void Chassis::driveToPoint(float targetX, float targetY, float maxVel, float pctCutoff,
                           char errorType, bool reversed, bool stop) {
  //--Variables-----------------------------------------------------------------
  float errorX, errorY, errorD, errorT,
        kP = 2.7,
        kI = 2.0,
        kD = 2.55,
        proportion,
        integral,
        integralZone = 13,
        intergralLimit = 10 * kI,
        derivative, lErrorD,
        driveVel, finalVL, finalVR,
        turnVel, drift = 0.01, dTurn, lErrorT,
        stuckTimer = 0, stuckTime = 300;
  bool enabled = true;

  maxVel = math.percentToVelocity(maxVel, 'G');

  //--Math----------------------------------------------------------------------
  while (enabled) {
    errorX = math.filter(targetX, odom.getX());

    errorY = math.filter(targetY, odom.getY());

    errorD = sqrt(errorX * errorX + errorY * errorY);

    errorT = (math.radToDeg(math.angleIn180(atan2(errorX, errorY))) -
                  math.radToDeg((math.angleIn180(odom.getTheta()))));

    proportion = errorD;

    if (fabs(errorD) < integralZone && errorD != 0){
      integral = integral + errorD;
    } else {
      integral = 0;
    }
    if (integral > intergralLimit){
      integral = intergralLimit;
    }

    derivative = errorD - lErrorD;
    lErrorD = errorD;

    if (fabs(derivative) > 0.01) {
      stuckTimer = millis() + stuckTime;
    }

    driveVel = (kP * proportion + kI * integral + kD * fabs(derivative));

    if (driveVel > maxVel) {
      driveVel = maxVel;
    }
    if (driveVel < -maxVel) {
      driveVel = -maxVel;
    }

    if (reversed) {
      driveVel = -driveVel;
    }

    dTurn = fabs(errorT) - lErrorT;
    turnVel = dTurn * drift;
    lErrorT = fabs(errorT);

    finalVL = (driveVel + turnVel);
    finalVR = (driveVel - turnVel);

    if (errorType == 'Y') {
      if (fabs(errorY) < pctCutoff) {
        enabled = false;
      }
    } else if (errorType == 'X') {
      if (fabs(errorX) < pctCutoff) {
        enabled = false;
      }
    } else if (errorType == 'D') {
      if (fabs(errorD) < pctCutoff) {
        enabled = false;
      }
    }

    if (millis() >= stuckTimer) {
      enabled = false;
    }

    // LFD.move_velocity(finalVL);
    // RFD.move_velocity(finalVR);
    // LBD.move_velocity(finalVL);
    // RBD.move_velocity(finalVR);

    chassis.move(finalVL, 'L');
    chassis.move(finalVR, 'R');

    delay(10);
  }

  if (stop) {
    chassis.stop().brake();
  }
}

//Arc-----------------------------------------------------------------
void Chassis::arcToPoint(float targetX, float targetY, float targetTheta, float timeOut,
                         float minVel, bool reversed, bool stop) {
  float errorX, errorY, errorD, errorT, errorTa,
        atan, rangle,
        kP = 0.2,
        kI = 0.001,
        kD = 0.01,
        proportion,
        integral, integralZone = 13, intergralLimit = 10 * kI,
        derivative, lErrorD, driveVel,
        kP_t = 0.15,
        kI_t = 0.001,
        kD_t = 0.01,
        proportion_t,
        integral_t, integralZone_t = 3, intergralLimit_t = 5 * kI_t,
        derivative_t, lErrorT, turnVel,
        finalVL, finalVR,
        stuckTimer = 0, stuckTime = 300;

  bool enabled = true, first = true;

  timeOut = math.secToMillis(timeOut) + millis();

  minVel = math.percentToVelocity(minVel, 'G');

  float numOfTurns = fabs(odom.getTheta() / 360);

  if (numOfTurns > 1) {
    targetTheta = targetTheta * numOfTurns;
  }

  while (enabled) {

    //Arc length and angle error calculations
    errorX = math.filter(targetX, odom.getX());

    errorY = math.filter(targetY, odom.getY());

    errorD = sqrt(errorX * errorX + errorY * errorY);

    if (first) {
      atan = 2 * math.radToDeg(math.angleIn180(atan2(errorX, errorY)));
      first = false;
    }

    rangle = math.radToDeg((math.angleIn180(odom.getTheta())));
    errorT = (atan - rangle);
    errorTa = fabs(errorT);

    //Drive PID
    proportion = errorD;

    if (fabs(errorD) < integralZone && errorD != 0) {
      integral = integral + errorD;
    } else {
      integral = 0;
    }

    if (integral > intergralLimit) {
      integral = intergralLimit;
    }

    derivative = errorD - lErrorD;
    lErrorD = errorD;

    driveVel = (kP * proportion + kI * integral + kD * fabs(derivative));

    if (driveVel < minVel) {
      driveVel = minVel;
    }

    if (reversed) {
      driveVel = -driveVel;
    }

    if (errorD < 1) {
      driveVel = 0;
    }

    //Turn PID
    proportion_t = errorT;

    if (errorTa < integralZone_t && errorTa != 0) {
      integral_t = integral_t + errorTa;
    } else {
      integral_t = 0;
    }

    if (integral_t > intergralLimit_t) {
      integral_t = intergralLimit_t;
    }

    derivative_t = errorTa - lErrorT;
    lErrorT = errorTa;

    if (fabs(derivative) > 0.01 || fabs(derivative_t) > 0.2) {
      stuckTimer = millis() + stuckTime;
    }

    turnVel = (kP_t * proportion_t + kI_t * integral_t + kD_t * fabs(derivative_t));

    if (errorT < 0) {
      turnVel = -turnVel;
    }

    if (targetTheta == math.radToDeg(odom.getTheta())) {
      turnVel = 0;
    }

    finalVL = (driveVel + turnVel);
    finalVR = (driveVel - turnVel);

    if (millis() > stuckTimer) {
      enabled = false;
    } else if (millis() >= timeOut) {
      enabled = false;
    }

    LFD.move_velocity(finalVL);
    RFD.move_velocity(finalVR);
    LBD.move_velocity(finalVL);
    RBD.move_velocity(finalVR);
    // chassis.move(finalVL, 'L');
    // chassis.move(finalVR, 'R');

    delay(10);
  }

  if (stop) {
    chassis.stop().brake();
  }
}

//-Turn to Angle---------------------------------------------------------
void Chassis::turnToAngle(float targetTheta, float maxVel, float pctCutoff, char side) {
  float errorT, errorTa,
        kP_t,
        kI_t,
        kD_t,
        proportion_t,
        integral_t, integralZone_t = 500,
        derivative_t, lErrorT,
        turnVel,
        multipler,
        stuckTimer = 0, stuckTime = 300;
  bool enabled = true, start = true;

  maxVel = math.percentToVelocity(maxVel, 'G');

  float numOfTurns = fabs(odom.getTheta() / 360);

  if (numOfTurns > 1) {
    targetTheta = targetTheta * numOfTurns;
  }

  if (side == 'B') {
    kP_t = 0.25,
    kI_t = 0.01,
    kD_t = 0.04,
    multipler = 1.02175;
  } else {
    kP_t = 2.8,
    kI_t = 0.95,
    kD_t = 2.1;
    multipler = 2.1;
  }

  float intergralLimit_t = maxVel / kI_t / 50;

  while (enabled) {
    //Angle error calculations
    errorT = math.degToRad(targetTheta) - odom.getTheta();
    errorTa = math.radToDeg(math.angleWrap(fabs(errorT)));

    //Turn PID
    proportion_t = errorTa;

    if (errorTa < integralZone_t && errorTa != 0) {
      integral_t = integral_t + errorTa;
    } else {
      integral_t = 0;
    }

    if (integral_t > intergralLimit_t) {
      integral_t = intergralLimit_t;
    }

    derivative_t = errorTa - lErrorT;
    lErrorT = lErrorT;

    if (fabs(derivative_t) > 0.2) {
      stuckTimer = millis() + stuckTime;
    }

    turnVel = (kP_t * proportion_t + kI_t * integral_t + kD_t * fabs(derivative_t)) * multipler;

    if(errorT < 0) {
      turnVel = -turnVel;
    }

    if (turnVel > maxVel) {
      turnVel =  maxVel;
    } else if (turnVel < -maxVel) {
      turnVel = -maxVel;
    }

    if (errorTa < pctCutoff) {
      turnVel = 0;
      enabled = false;
    } else if (millis() > stuckTimer) {
      turnVel = 0;
      enabled = false;
    }

    if (side == 'B') {
      chassis.move(turnVel, 'L');
      chassis.move(-turnVel, 'R');
      // LFD.move_velocity(turnVel);
      // RFD.move_velocity(-turnVel);
      // LBD.move_velocity(turnVel);
      // RBD.move_velocity(-turnVel);
    } else if (side == 'L') {
      chassis.move(turnVel, 'L');
      chassis.move(0, 'R');
      // LFD.move_velocity(turnVel);
      // RFD.move_velocity(0);
      // LBD.move_velocity(turnVel);
      // RBD.move_velocity(0);
    } else if (side == 'R') {
      chassis.move(0, 'L');
      chassis.move(turnVel, 'R');
      // LFD.move_velocity(0);
      // RFD.move_velocity(turnVel);
      // LBD.move_velocity(0);
      // RBD.move_velocity(turnVel);
    }

    pros::delay(10);
  }
}
