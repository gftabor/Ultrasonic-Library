/*
  ultrasonicSensor.cpp - Sensor class for ultrasonic library
  Takes 5 samples and averages them together for a better reading.
 */

#include "Arduino.h"
#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int pingPin) {
  pinMode(pingPin, OUTPUT);
  _pingPin = pingPin;
}
void UltrasonicSensor::giveValue(unsigned long timeDifference){ 
    secondRecentTimeDifference = recentTimeDifference;
	firstRecentTimeDifference =timeDifference;
}
void UltrasonicSensor::pulsePin(){
	//Serial.println("pulsing");
	digitalWrite(_pingPin, LOW);
    digitalWrite(_pingPin, HIGH);
	delayMicroseconds(250);
    digitalWrite(_pingPin, LOW);
}

float UltrasonicSensor::distance() {
  noInterrupts();
  if (secondRecentTimeDifference > firstRecentTimeDifference) //uses smaller value from last 2 pings
	  recentTimeDifference = firstRecentTimeDifference;
  else
	  recentTimeDifference = secondRecentTimeDifference;
  recentTimeDifference -= 700;
  dist = ((562.6 * (recentTimeDifference / 1000000.0)) * 12.0);
  //dist = recentTimeDifference; //error testing 

  interrupts();

  return dist;
}
