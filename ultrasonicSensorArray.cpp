/*
  ultrasonic.cpp - Library for finding the distance to an object in inches.
  */

#include "Arduino.h"
#include "ultrasonicSensorArray.h"
#include "ultrasonicSensor.h"
#include "TimerOne.h"

ultrasonicSensorArray *sensorPointer;
void ultrasonicSensorArray::sensorStaticHandler(){
  //Serial.println("ping");
  sensorPointer->ultrasonicISR();
}
void ultrasonicSensorArray::timerStaticHandler() {
	//Serial.println("ping");
	sensorPointer->pulseNext();
}
ultrasonicSensorArray::ultrasonicSensorArray(int inputPin) {
  _echoPin=inputPin;
  currentSensor=0;
  sensorsEntered=0;
  sensorPointer = this;
  pinMode(_echoPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(_echoPin),
	  ultrasonicSensorArray::sensorStaticHandler, FALLING);

}

 void ultrasonicSensorArray::addSensor(ultrasonicSensor *newSensor){
  sensors[sensorsEntered]= newSensor;
  sensorsEntered++;
}
 void ultrasonicSensorArray::begin(){
  sensors[0]->pulsePin();
  currentStartTime=micros();
  Timer1.initialize(20000); 
  Timer1.attachInterrupt(ultrasonicSensorArray::timerStaticHandler); // attach the service routine here

}

void ultrasonicSensorArray::ultrasonicISR(){	
  currentEndTime=micros();
  sensors[currentSensor]->giveValue(currentEndTime-currentStartTime);
  
  //delayMicroseconds(100000);
  //sensors[currentSensor]->pulsePin();
}

void ultrasonicSensorArray::pulseNext() {
    currentSensor++;
      if (currentSensor >= sensorsEntered) {
	    currentSensor = 0;
      }
    currentStartTime = micros();
	//Serial.println(currentSensor);

	sensors[currentSensor]->pulsePin();
}



