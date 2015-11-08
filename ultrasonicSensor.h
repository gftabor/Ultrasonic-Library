/*
  ultrasonicSensor.h - Sensor class for ultrasonic library
*/

#ifndef ultrasonicSensor_h
#define ultrasonicSensor_h

#include "Arduino.h"

class ultrasonicSensor {
public:
  ultrasonicSensor(int pingPin);
  void giveValue(long unsigned timeDifference);
  void pulsePin();
  float distance();

private:
  volatile unsigned long recentTimeDifferences[5];
  int _pingPin;
};

#endif

