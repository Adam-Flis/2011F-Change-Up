#include "main.h"

#ifndef UPTAKE_HPP
#define UPTAKE_HPP

class Uptake {
  public:
    Uptake();
    ~Uptake();

    void move(int velocity);
    Uptake& stop();
    void brake();
};

#endif
