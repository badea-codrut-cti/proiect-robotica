# Self Parking Toy Car

## Introduction

The project consists of a toy car that, when placed in the general direction of a a parking space, it will try to steer itself into said parking space. A parking space is determined by three obstacles and an opening, i.e two parked cars and a wall. The car will use two ultrasonic sensors to measure the distance on its front left and front right and determine whether it is approaching an obstacle and in which direction. With that information, it will try to steer itself away from said obstacle. It will consider the parking maneuver finished once it gets close enough to the wall (which is determined by both sensors reporting similar distances).

## General Description

![general description](./images/general-description.svg)

## Hardware Design

![schematic](./images/schematic.png)

Element|Quantity|Source
---|---|---
DC Motor|2|Faculty
SR90 Servo|1|Bought
L298N|1|Bought
HC-SR04|2|Faculty
Arduino Uno|1|Faculty
1.5V Battery Driver|1|Faculty
1.5V Battery|4|Bought
9V Battery|1|Bought

Roluri Pini:
- D0: Este conectat la push button-ul care comuta masina intre modul parcare si modul standby.
- D1: Este conectat la senzorul ultrasonic din dreapta.
- D4: Este conectat la senzorul ultrasonic din stanga.
- D6: Comunica prin PWM sa controleze unghiul servomotorului care vireaza axul frontal.
- D10-D11: Pinii analogici controleaza viteza motoarelor, conectate la puntea H dubla pentru ambele servo-motoare.
- A0: Primeste semnalul de echo de la senzorul ultrasonic din stanga.
- A1: Primeste semnalul de echo de la senzorul ultrasonic din dreapta.

![design-front](./images/design-front.jpeg)
![design-back](./images/design-back.jpeg)
![design-top](./images/design-top.jpeg)

## Software Design

Whether parking should start is dictated by a push button whose pin is configured with an interrupt on the falling edge. Debouncing is handled using a variable that keeps track of the last time the button was pressed as a timestamp in milliseconds since the microcontroller has been powered on. If the difference between the current timestamp and the timestamp stored in the variable is below the pre-defined threshold, the button press would be ignored. 

Subsequent button presses would delay when parking initiates, as once the button is pressed, a two second countdown will start before the car begins to park itself.

The source code contains a function for measuring the distance between the frontal sensors and potential obstacles. The function works by sending an input to the `HC-SR04` sensors and waiting for an echo using `pulseIn`. 

Those results are stored in two global variables and are later processed in a function that handles steering. The function first checks if it should proceed with parking (if it is in park mode and if the time between being put in park mode and the current timestamp is greater than two seconds), then it checks if either of the sensors is closer to an obstacle than the stopping threshold, in which case it will end the parking maneuver. If that is not the case, it then checks if the deviation between the distances reported by the two frontal sensors are less than a pre-defined percentage, which would make the car go forward. If the distance is skewed to either direction, the car will steer in the opposite direction to avoid the obstacle.

## Documented Results

The car is able to steer itself into the parking space, but in a situation where the car is surrounded by three obstacles and an entrance, it might misidentify which one of the three obstacles is the wall and which ones are the adjacent cars if the steering angle is heavily skewed towards one of the parked cars. This can cause a situation where the car is parked sideways on its lot.

https://github.com/user-attachments/assets/35ce2e0a-f27a-4493-b056-790f85273674

## Conclusion

The project offered me the opportunity to apply my 3D modeling knowledge in order to create the designs for the steering system, chassis and back axle. It also served as an opportunity to use programming as a means to solving a real world issue.

## Biography

- [HC-SR04 Datasheet](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)
- [L298N Datasheet](https://www.st.com/resource/en/datasheet/l298.pdf)
- [Arduino Technical Details](https://www.oreilly.com/library/view/arduino-a-technical/9781491934319/ch04.html)
