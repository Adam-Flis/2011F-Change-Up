#include "main.h"

#ifndef UPTAKE_HPP
#define UPTAKE_HPP

class Uptake {
public:
  Uptake();
  ~Uptake();

  Uptake& stop();
  void brake();
  void coast();
  void hold();

  Uptake& moveVel(double velocity_);
  Uptake& moveVolt(double voltage_);

  char getColorB();
  char getColorM();
  Uptake& color(char color_, int position_, double timeOut_);
  Uptake& waitForColor();

  void resetCount();
  int getCount();
  Uptake& shot(int amount_, double timeOut_);
  Uptake& waitForShot();

  static void start();
  void end();

private:
  static bool isRunning, isShooting, hasColor;
  static char desiredColorB, currentColorB, desiredColorM, currentColorM;
  static double velocity, voltage, timeOut;
  static int position, desiredAmount, currentAmount;

};

#endif
