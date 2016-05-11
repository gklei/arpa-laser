/*
  Motor.h - A library for controlling the Stepper motor
*/

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor
{
  public:
    Motor(int pin1, int pin2, int pin3, int pin4);
  private:
    int _pin1, _pin2, _pin3, _pin4;
};

#endif
