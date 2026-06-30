/*
  Arduino Automated Railway Gate System

  The system uses two IR sensors to detect train approach and train exit,
  controls a servo motor for gate movement, and shows status on a 16x2 LCD.

  Hardware:
  - Arduino Uno
  - 2 IR obstacle sensors
  - Servo motor
  - 16x2 LCD
  - Warning LED / buzzer
*/

#include <Servo.h>
#include <LiquidCrystal.h>

// LCD pin connections: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, A1, A2);

Servo gateServo;

// Pin configuration
const int approachSensorPin = 2;
const int exitSensorPin = 3;
const int servoPin = 9;
const int buzzerPin = 8;
const int redLedPin = 12;
const int greenLedPin = 13;

// Servo angles
const int gateOpenAngle = 90;
const int gateClosedAngle = 0;

// IR sensor output is usually LOW when object is detected
const int objectDetected = LOW;

bool gateClosed = false;

void setup() {
  pinMode(approachSensorPin, INPUT);
  pinMode(exitSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  gateServo.attach(servoPin);
  openGate();

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Railway Gate");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");

  delay(2000);
  showGateOpen();
}

void loop() {
  int approachSensor = digitalRead(approachSensorPin);
  int exitSensor = digitalRead(exitSensorPin);

  // Train approaching
  if (approachSensor == objectDetected && !gateClosed) {
    showTrainDetected();
    warningSignal();
    closeGate();
  }

  // Train passed
  if (exitSensor == objectDetected && gateClosed) {
    showTrainPassed();
    delay(1000);
    openGate();
  }

  delay(100);
}

void closeGate() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Closing Gate");
  lcd.setCursor(0, 1);
  lcd.print("Please Wait");

  for (int pos = gateOpenAngle; pos >= gateClosedAngle; pos--) {
    gateServo.write(pos);
    delay(20);
  }

  gateClosed = true;
  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gate Closed");
  lcd.setCursor(0, 1);
  lcd.print("Train Passing");
}

void openGate() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Opening Gate");
  lcd.setCursor(0, 1);
  lcd.print("Safe Soon");

  for (int pos = gateClosedAngle; pos <= gateOpenAngle; pos++) {
    gateServo.write(pos);
    delay(20);
  }

  gateClosed = false;
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(buzzerPin, LOW);

  showGateOpen();
}

void warningSignal() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(redLedPin, HIGH);
    delay(250);

    digitalWrite(buzzerPin, LOW);
    digitalWrite(redLedPin, LOW);
    delay(250);
  }
}

void showTrainDetected() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Train Detected");
  lcd.setCursor(0, 1);
  lcd.print("Gate Closing");
}

void showTrainPassed() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Train Passed");
  lcd.setCursor(0, 1);
  lcd.print("Gate Opening");
}

void showGateOpen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gate Open");
  lcd.setCursor(0, 1);
  lcd.print("Track Clear");
}
