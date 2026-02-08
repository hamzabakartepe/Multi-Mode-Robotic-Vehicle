#include <SoftwareSerial.h>

// Software serial for Bluetooth (RX, TX)
SoftwareSerial btSerial(3, 4);

// --------- PIN DEFINITIONS ---------
const int trigLeft = 13;
const int trigRight = A0;
const int echoLeft = 12;
const int echoRight = 8;
const int buzzer = 2;

// Motor Driver Pins (L298N)
const int leftEnable = 5;
const int leftIn1 = 6;
const int leftIn2 = 7;
const int rightEnable = 11;
const int rightIn3 = 10;
const int rightIn4 = 9;

int distLeft, distRight;
int motorSpeed = 200;
byte lastOperation;

void setup() {
  // Pin modes and Serial initialization
  // ... (Pins initialized as in previous steps)
  btSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // Dual-sensor distance measurement
  distLeft = measureDistance(trigLeft, echoLeft);
  delay(10); // Prevent echo interference
  distRight = measureDistance(trigRight, echoRight);

  // Bluetooth command processing
  if (btSerial.available()) {
    char command = btSerial.read();
    executeCommand(command);
  }
}

// Function to handle specific modes
void executeCommand(char cmd) {
  if (cmd == '0') {
    obstacleAvoidanceMode();
  } else if (cmd == '5') {
    parkingMode();
  }
  // ... (Movement commands)
}

// Otonom navigation logic
void obstacleAvoidanceMode() {
  if(distLeft < 30 && distRight < 30) {
    moveBackward();
    delay(250);
  } else if (distLeft < 30) {
    moveBackward(); delay(150);
    turnRight(); delay(250);
  }
  // ... (Logic continues)
}