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

  void waitUntilIndexedBottom(float timeOut);
  void waitUntilIndexedMiddle(float timeOut);
  void waitUntilIndexedTop(float timeOut);
  void waitUntilShot(int amount, float timeOut);

};

#endif
