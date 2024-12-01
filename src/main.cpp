#include <Arduino.h>

// Define pins for HC-SR04
const int trigPin = 9;
const int echoPin = 10;

// Variable for storing the duration and calculated distance
long duration;
float distance;

void setup() {
  // Set up serial communication
  Serial.begin(9600);
  
  // Set trigPin as output and echoPin as input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Ensure the trigPin is LOW initially
  digitalWrite(trigPin, LOW);
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
  Serial.println(" cm");

  // Short delay before the next measurement
  delay(200);
}
