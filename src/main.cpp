#include <Arduino.h>
#include <Servo.h>

// Define pins for HC-SR04
//const int trigPin = 9;
//const int echoPin = 10;

const int motorPinPos = 10, motorPinNeg = 9;

// Variable for storing the duration and calculated distance
long duration;
float distance;

Servo servo;

void setup() {
  // Set up serial communication
  //Serial.begin(9600);
  servo.attach(6);
  
  // Set trigPin as output and echoPin as input
  //pinMode(trigPin, OUTPUT);
  //pinMode(echoPin, INPUT);
  pinMode(motorPinNeg, OUTPUT);
  pinMode(motorPinPos, OUTPUT);
}

uint8_t coords = 0;

void loop() {
  // Ensure the trigPin is LOW initially
  /*digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10-microsecond HIGH pulse to the trigPin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin and calculate the duration of the pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm
  // Speed of sound in air is 343 m/s or 0.0343 cm/us
  // Divide by 2 because the sound travels to the object and back
  distance = (duration * 0.0343) / 2;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");*/

  coords = (coords + 10) % 180;
  servo.write(coords);
  
  // Short delay before the next measurement
  analogWrite(motorPinPos, 255);
  analogWrite(motorPinNeg, 0);
}
