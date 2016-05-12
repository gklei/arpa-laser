/*
  Motor.cpp - A library for controlling the stepper motor
*/

#include "Motor.h"

Motor::Motor(int pin1, int pin2, int pin3, int pin4)
{
  _pin1 = pin1;
  _pin2 = pin2;
  _pin3 = pin3;
  _pin4 = pin4;

  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);
  pinMode(_pin3, OUTPUT);
  pinMode(_pin4, OUTPUT);
}
