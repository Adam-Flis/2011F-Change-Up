#include "main.h"

#ifndef UPTAKE_HPP
#define UPTAKE_HPP

class Uptake {
public:
  Uptake();
  ~Uptake();

  Uptake& stop();
  void brake();

  void move(float velocity);

  void waitUntillIndexed(int amount, float timeOut);
  void waitUntillShot(int amount, float timeOut);

};

#endif
