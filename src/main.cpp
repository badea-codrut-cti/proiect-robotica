#include <Arduino.h>
#include "pinmaps.h"

float distanceLeft, distanceRight;
volatile uint32_t lastInterruptTime = 0, parkStartTime = 0;

void handleStartButton() {
  uint32_t currentTime = millis();

  if (currentTime - lastInterruptTime < DEBOUNCE_DELAY) 
    return;

  lastInterruptTime = parkStartTime = currentTime;
}

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIGGER_PIN_LEFT, OUTPUT);
  pinMode(TRIGGER_PIN_RIGHT, OUTPUT);

  pinMode(ECHO_PIN_LEFT, INPUT);
  pinMode(ECHO_PIN_RIGHT, INPUT);

  pinMode(START_BTN_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(START_BTN_PIN), handleStartButton, FALLING);

  pinMode(LEFT_MOTOR_POS, OUTPUT);
  pinMode(LEFT_MOTOR_GND, OUTPUT);

  pinMode(RIGHT_MOTOR_POS, OUTPUT);
  pinMode(RIGHT_MOTOR_GND, OUTPUT);

  digitalWrite(LEFT_MOTOR_GND, LOW);
  digitalWrite(RIGHT_MOTOR_GND, LOW);
}

uint8_t coords = 0;

void getDistances() {
  digitalWrite(TRIGGER_PIN_LEFT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_LEFT, LOW);

  long duration = pulseIn(ECHO_PIN_LEFT, HIGH);
  distanceLeft = (duration * SPEED_OF_SOUND) / 2;

  digitalWrite(TRIGGER_PIN_RIGHT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_RIGHT, LOW);

  duration = pulseIn(ECHO_PIN_RIGHT, HIGH);
  distanceRight = (duration * SPEED_OF_SOUND) / 2;
}

void handleSteering() {
  if (millis() - parkStartTime < PARKING_COOLDOWN || min(distanceLeft, distanceRight) < STOPPING_DISTANCE) {
    analogWrite(LEFT_MOTOR_POS, 0);
    analogWrite(RIGHT_MOTOR_POS, 0);
    return;
  }

  if (abs(distanceLeft - distanceRight) < MAX_DISTANCE_DEVIATION * min(distanceLeft, distanceRight)) {
    analogWrite(LEFT_MOTOR_POS, 255);
    analogWrite(RIGHT_MOTOR_POS, 255);
    return;
  }

  bool steerLeft = distanceLeft > distanceRight;

  analogWrite(LEFT_MOTOR_POS, steerLeft ? 255 : 0);
  analogWrite(RIGHT_MOTOR_POS, steerLeft ? 0 : 255);
}

void loop() {
  getDistances();
  handleSteering();
  Serial.print(distanceLeft);
  Serial.print(", ");
  Serial.println(distanceRight);
  delay(20);
}
