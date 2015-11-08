/*
  ultrasonic.cpp - Library for finding the distance to an object in inches.
  */

#include "Arduino.h"
#include "ultrasonicSensorArray.h"
#include "ultrasonicSensor.h"
ultrasonicSensorArray *sensorPointer;
void ultrasonicSensorArray::staticHandler(){
  //Serial.println("ping");
  sensorPointer->ultrasonicISR();
}
ultrasonicSensorArray::ultrasonicSensorArray(int inputPin) {
  _echoPin=inputPin;
  currentSensor=0;
  sensorsEntered=0;
  sensorPointer = this;
  pinMode(_echoPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(_echoPin),
	  ultrasonicSensorArray::staticHandler, FALLING);
}

 void ultrasonicSensorArray::addSensor(ultrasonicSensor *newSensor){
  sensors[sensorsEntered]= newSensor;
  sensorsEntered++;
}
 void ultrasonicSensorArray::begin(){
  sensors[0]->pulsePin();
  currentStartTime=micros();
}

void ultrasonicSensorArray::ultrasonicISR(){	
  currentEndTime=micros();
  sensors[currentSensor]->giveValue(currentEndTime-currentStartTime);
  currentSensor++;
  if (currentSensor >= sensorsEntered) {
	  currentSensor = 0;
  }
  delayMicroseconds(100000);
  sensors[currentSensor]->pulsePin();
}

void ultrasonicSensorArray::pulseNext() {
	currentStartTime = micros();
	sensors[0]->pulsePin();
}



