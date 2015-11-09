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
   for(int i=4; i>0; i--){
       recentTimeDifferences[i]=recentTimeDifferences[i-1];
   }
   recentTimeDifferences[0]=timeDifference;
}
void UltrasonicSensor::pulsePin(){
	//Serial.println("pulsing");
	digitalWrite(_pingPin, LOW);
    digitalWrite(_pingPin, HIGH);
	delayMicroseconds(250);
    digitalWrite(_pingPin, LOW);
}

float UltrasonicSensor::distance() {
  unsigned long sum = 0;

  //Average last 5 samples
  for(int i = 0; i < 5; i++) {
	sum += recentTimeDifferences[i];
  }
  //divide by 5
  sum /= 5;
  sum -= 700;
  dist = ((562.6 * (sum / 1000000.0)) * 12.0);

  //sum = recentTimeDifferences[0];

  return dist;
}
