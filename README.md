# Arduino Automated Railway Gate System

## Overview
This project is an Arduino-based automated railway gate prototype developed during my undergraduate studies. The idea was inspired by a real railway crossing near my university, where an automated gate system could reduce manual operation and improve safety.

The prototype uses two IR obstacle sensors to detect train movement, a servo motor to control the gate, and a 16x2 LCD to display the system status. The project was demonstrated using a cardboard prototype enclosure with the Arduino, breadboard, sensors and display mounted inside.

## Features
- Train approach detection using IR obstacle sensor
- Train exit detection using second IR sensor
- Automatic gate opening and closing using servo motor
- 16x2 LCD display for system status
- Warning LED/buzzer logic during gate movement
- Simple embedded control logic using Arduino

## Tools and Technologies
- Arduino Uno
- Arduino IDE
- Embedded C / Arduino programming
- IR obstacle sensors
- Servo motor
- 16x2 LCD display
- Breadboard and jumper wires

## Hardware Concept

| Component | Purpose |
|---|---|
| Arduino Uno | Main controller |
| IR Sensor 1 | Detects train approaching |
| IR Sensor 2 | Detects train leaving |
| Servo Motor | Opens and closes the gate |
| 16x2 LCD | Displays system status |
| LED/Buzzer | Warning indication |

## Working Logic
1. The first IR sensor detects the train approaching the railway gate.
2. The Arduino displays a warning message on the LCD.
3. The buzzer/LED warning is triggered.
4. The servo motor closes the gate.
5. The system waits until the second IR sensor detects that the train has passed.
6. The servo motor opens the gate again.
7. The LCD displays that the track is clear.
