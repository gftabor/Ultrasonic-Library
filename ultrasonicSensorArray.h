/*
  ultrasonicSensor.h - Sensor class for ultrasonic library
*/

#ifndef ultrasonicSensorArray_h
#define ultrasonicSensorArray_h

#include "Arduino.h"
#include "ultrasonicSensor.h"


class ultrasonicSensorArray {
public:
  ultrasonicSensorArray(int echoPin);
  static void staticHandler();
  void addSensor(ultrasonicSensor *newSensor);
  void begin();
  void ultrasonicISR();
  void pulseNext();

private:
  int _echoPin;
  volatile int currentSensor;
  int sensorsEntered;  
  volatile unsigned long currentStartTime;
  volatile unsigned long currentEndTime; 

  
#ifndef numOfUltrasonics
    #define numOfUltrasonics 5
#endif  
  ultrasonicSensor* sensors[numOfUltrasonics];
};

#endif

