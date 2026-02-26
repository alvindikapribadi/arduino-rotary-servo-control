/*
  ============================================================
  PROJECT  : Arduino Rotary Encoder + Servo Control
  
  DESCRIPTION:
  This project uses a rotary encoder to control
  the angle of a servo motor (0–180 degrees).

  Rotate clockwise  -> Servo angle increases
  Rotate counter    -> Servo angle decreases

  COMPONENTS:
  - Arduino Uno / Nano
  - Rotary Encoder (CLK, DT)
  - Servo Motor (SG90 / MG90S)
  - Breadboard
  - Jumper wires

  CONNECTION:
  Rotary CLK -> Pin 2
  Rotary DT  -> Pin 3
  Servo Signal -> Pin 9
  VCC -> 5V
  GND -> GND
  ============================================================
*/

#include <Servo.h>

#define CLK 2
#define DT  3
#define SERVO_PIN 9

Servo myServo;

int lastCLKState;
int currentCLKState;

int servoAngle = 90;  // start from middle position

void setup() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(servoAngle);

  lastCLKState = digitalRead(CLK);
}

void loop() {

  currentCLKState = digitalRead(CLK);

  // Detect rotation
  if (currentCLKState != lastCLKState) {

    // Check direction
    if (digitalRead(DT) == currentCLKState) {
      servoAngle += 10;   // clockwise
    } else {
      servoAngle -= 10;   // counter-clockwise
    }

    // Limit angle 0 - 180
    if (servoAngle > 180) servoAngle = 180;
    if (servoAngle < 0)   servoAngle = 0;

    myServo.write(servoAngle);
    delay(5); // small debounce delay
  }

  lastCLKState = currentCLKState;
}


