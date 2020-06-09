#include "main.h"

#ifndef INTAKE_HPP
#define INTAKE_HPP

class Intake {
  public:

    Intake& stop();
    void brake();
    void move(int velocity);

    class Bottom {
      public:
        void stop();
        void move(int velocity);
    };

    class Top {
      public:
        void stop();
        void move(int velocity);
    };
};


#endif
