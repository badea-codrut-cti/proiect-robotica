#include <Arduino.h>
#include "pinmaps.h"

float distanceLeft, distanceRight;
volatile bool shouldPark = false;
uint32_t lastInterruptTime = 0, parkStartTime = 0;

void handleStartButton() {
  uint32_t currentTime = millis();

  if (currentTime - lastInterruptTime >= DEBOUNCE_DELAY) {
    lastInterruptTime = currentTime;
    shouldPark = !shouldPark;
    parkStartTime = millis();
  }
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
  if (millis() < 5000)
    return;
  
  if (min(distanceLeft, distanceRight) < STOPPING_DISTANCE) {
    digitalWrite(LEFT_MOTOR_POS, LOW);
    digitalWrite(RIGHT_MOTOR_POS, LOW);
    return;
  }

  if (abs(distanceLeft - distanceRight) < 0.1 * min(distanceLeft, distanceRight)) {
    digitalWrite(LEFT_MOTOR_POS, HIGH);
    digitalWrite(RIGHT_MOTOR_POS, HIGH);
    return;
  }

  bool steerLeft = distanceLeft > distanceRight;

  digitalWrite(LEFT_MOTOR_POS, steerLeft ? HIGH : LOW);
  digitalWrite(RIGHT_MOTOR_POS, steerLeft ? LOW : HIGH);
}

void loop() {
  getDistances();
  handleSteering();
  /*Serial.print(distanceLeft);
  Serial.print(", ");
  Serial.println(distanceRight);*/
  delay(20);
}
