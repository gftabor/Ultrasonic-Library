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
  void addSensor(ultrasonicSensor *newSensor);
  void begin(); 

private:
  int _echoPin;
  volatile int currentSensor;
  int sensorsEntered;  
  volatile unsigned long currentStartTime;
  volatile unsigned long currentEndTime;
  void ultrasonicISR();
  void pulseNext();
  static void sensorStaticHandler();
  static void timerStaticHandler();

  
#ifndef numOfUltrasonics
    #define numOfUltrasonics 5
#endif  
  ultrasonicSensor* sensors[numOfUltrasonics];
};

#endif

