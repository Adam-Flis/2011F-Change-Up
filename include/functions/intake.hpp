#include "main.h"

#ifndef INTAKE_HPP
#define INTAKE_HPP

class Intake {
public:
  Intake();
  ~Intake();

  Intake& stop();
  void brake();
  void coast();
  void hold();

  Intake& moveVel(double velocity_);
  Intake& moveVolt(double voltage_);

  char getColor();
  Intake& color(char color_, double timeOut_);
  Intake& waitForColor();

  static void start();
  void end();

private:
  static bool isRunning, hasColor, getValue;
  static char desiredColor, currentColor;
  static double velocity, voltage, timeOut;

};

#endif
