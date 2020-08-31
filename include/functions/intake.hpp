#include "main.h"

#ifndef INTAKE_HPP
#define INTAKE_HPP

class Intake{
  public:
    Intake();
    ~Intake();

    Intake& stop();
    void brake();
    void setVelocity(int velocity_);

    class Bottom{
      public:
        void stop();
        void setVelocity(int velocity_);
    };

    class Top{
      public:
        void stop();
        void setVelocity(int velocity_);
    };
};


#endif
