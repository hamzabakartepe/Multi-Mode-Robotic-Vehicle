#include <SoftwareSerial.h>

// Software Serial port for Bluetooth module (RX, TX)
SoftwareSerial btSerial(3, 4);

// --------- PIN DEFINITIONS ---------
const int triggerLeft = 13;
const int triggerRight = A0;
const int echoLeft = 12;
const int echoRight = 8;
const int buzzerPin = 2;

// Left Motor (Motor A)
const int leftEnable = 5; // ENA - Speed control via PWM
const int leftIn1 = 6;    // IN1 - Direction control
const int leftIn2 = 7;    // IN2 - Direction control

// Right Motor (Motor B)
const int rightEnable = 11; // ENB - Speed control via PWM
const int rightIn3 = 10;    // IN3 - Direction control
const int rightIn4 = 9;     // IN4 - Direction control

// Sensor variables
int duration1;
int distance1;
int duration2;
int distance2;

// Motor speed (0-255)
int motorSpeed = 200;

// Stores the last action taken (forward, backward, left, right, etc.)
byte lastAction;

// Function to measure distance using ultrasonic sensor
int measureDistance(int trigger, int echo) {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  long duration = pulseIn(echo, HIGH);
  return duration * 0.034 / 2;
}

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(leftEnable, OUTPUT);
  pinMode(leftIn1, OUTPUT);
  pinMode(leftIn2, OUTPUT);
  pinMode(rightEnable, OUTPUT);
  pinMode(rightIn3, OUTPUT);
  pinMode(rightIn4, OUTPUT);
  pinMode(triggerLeft, OUTPUT);
  pinMode(triggerRight, OUTPUT);
  pinMode(echoLeft, INPUT);
  pinMode(echoRight, INPUT);

  // Initialize serial communication
  Serial.begin(9600);
  btSerial.begin(9600);
}

void loop() {
  // Sensor 1 (Left)
  distance1 = measureDistance(triggerLeft, echoLeft);
  delay(10); // Short delay to prevent echo interference

  // Sensor 2 (Right)
  distance2 = measureDistance(triggerRight, echoRight);

  Serial.print("Left Distance = ");
  Serial.println(distance1);
  Serial.print("Right Distance = ");
  Serial.println(distance2);

  // Read data if available from Bluetooth
  while (btSerial.available()) {
    char data = btSerial.read();
    Serial.println(data);

    if (data == '1') { // Move Forward
      stopMotors();
      delay(50);
      moveForward();
      lastAction = 1;
    } 
    else if (data == '2') { // Move Backward
      stopMotors();
      delay(50);
      moveBackward();
      lastAction = 2;
    } 
    else if (data == '3') { // Turn Left
      stopMotors();
      delay(50);
      turnLeft();
      lastAction = 3;
    } 
    else if (data == '4') { // Turn Right
      stopMotors();
      delay(50);
      turnRight();
      lastAction = 4;
    } 
    else if (data == '6') { // Stop
      stopMotors();
      delay(50);
      lastAction = 6;
    } 
    else if (data == '0') { // Obstacle Avoidance Mode
      stopMotors();
      delay(50);
      obstacleAvoidance();
      resumeLastAction();
    } 
    else if (data == '5') { // Parking Sensor Mode
      parkingSensor();
      resumeLastAction();
    }
  }
  delay(10);
}

// ----------- MOTOR CONTROL FUNCTIONS -----------

void moveForward() {
  // Left motor forward
  digitalWrite(leftIn1, HIGH);
  digitalWrite(leftIn2, LOW);
  // Right motor forward
  digitalWrite(rightIn3, HIGH);
  digitalWrite(rightIn4, LOW);

  analogWrite(leftEnable, motorSpeed);
  analogWrite(rightEnable, motorSpeed);
}

void moveBackward() {
  digitalWrite(leftIn1, LOW);
  digitalWrite(leftIn2, HIGH);
  digitalWrite(rightIn3, LOW);
  digitalWrite(rightIn4, HIGH);

  analogWrite(leftEnable, motorSpeed);
  analogWrite(rightEnable, motorSpeed);
}

void turnLeft() {
  // Rotate on axis: left motor back, right motor forward
  digitalWrite(leftIn1, LOW);
  digitalWrite(leftIn2, HIGH);
  digitalWrite(rightIn3, HIGH);
  digitalWrite(rightIn4, LOW);

  analogWrite(leftEnable, motorSpeed);
  analogWrite(rightEnable, motorSpeed);
}

void turnRight() {
  // Rotate on axis: left motor forward, right motor back
  digitalWrite(leftIn1, HIGH);
  digitalWrite(leftIn2, LOW);
  digitalWrite(rightIn3, LOW);
  digitalWrite(rightIn4, HIGH);

  analogWrite(leftEnable, motorSpeed);
  analogWrite(rightEnable, motorSpeed);
}

void stopMotors() {
  digitalWrite(leftIn1, LOW);
  digitalWrite(leftIn2, LOW);
  digitalWrite(rightIn3, LOW);
  digitalWrite(rightIn4, LOW);
  
  analogWrite(leftEnable, 0);
  analogWrite(rightEnable, 0);
  
  lastAction = 6;
}

// Resumes the last requested action after a mode finish
void resumeLastAction() {
  if (lastAction == 1) moveForward();
  else if (lastAction == 2) moveBackward();
  else if (lastAction == 3) turnLeft();
  else if (lastAction == 4) turnRight();
  else if (lastAction == 6) stopMotors();
  else if (lastAction == 0) obstacleAvoidance();
}

// Obstacle Avoidance Logic
void obstacleAvoidance() {
  analogWrite(leftEnable, motorSpeed);
  analogWrite(rightEnable, motorSpeed);
  
  if (distance1 < 30 && distance2 < 30) {
    moveBackward();
    delay(250);
  } 
  else if (distance1 < 30) { // Obstacle on the left, turn right
    moveBackward();
    delay(150);
    turnRight();
    delay(250);
  } 
  else if (distance2 < 30) { // Obstacle on the right, turn left
    moveBackward();
    delay(150);
    turnLeft();
    delay(250);
  } 
  else { // Path is clear, move forward
    moveForward();
  }
}

// Parking Sensor Feedback
void parkingSensor() {
  if (distance1 < 5 || distance2 < 5) {
    digitalWrite(buzzerPin, HIGH);
    delay(50);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  } 
  else if (distance1 < 15 || distance2 < 15) {
    digitalWrite(buzzerPin, HIGH);
    delay(50);
    digitalWrite(buzzerPin, LOW);
    delay(250);
  } 
  else if (distance1 < 25 || distance2 < 25) {
    digitalWrite(buzzerPin, HIGH);
    delay(50);
    digitalWrite(buzzerPin, LOW);
    delay(500);
  } 
  else {
    digitalWrite(buzzerPin, LOW);
  }
}