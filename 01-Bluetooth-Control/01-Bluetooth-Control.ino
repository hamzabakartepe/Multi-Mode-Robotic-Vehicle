#include <SoftwareSerial.h>

// Software serial port for Bluetooth module (RX, TX)
SoftwareSerial btCommunication(3, 4);

// --------- PIN DEFINITIONS ---------
// Left motor (Motor A)
#define left_enable 5  // ENA - Speed control with PWM
#define left_in1 6     // IN1 - direction control
#define left_in2 7     // IN2 - direction control

// Right motor (Motor B)
#define right_enable 11 // ENB - Speed control with PWM
#define right_in3 9     // IN3 - direction control
#define right_in4 10    // IN4 - direction control

// Motor speed value (between 0-255)
int motorSpeed = 255;

// Last operation performed (forward, backward, right, left)
byte lastOperation;

void setup() {
  // Set motor pins as output
  pinMode(left_enable, OUTPUT);
  pinMode(left_in1, OUTPUT);
  pinMode(left_in2, OUTPUT);

  pinMode(right_enable, OUTPUT);
  pinMode(right_in3, OUTPUT);
  pinMode(right_in4, OUTPUT);

  // Initialize serial communication
  Serial.begin(9600);
  btCommunication.begin(9600);
}

void loop() {
  // Read data if available from Bluetooth
  while (btCommunication.available()) {
    char data = btCommunication.read();
    Serial.println(data);

    if (data == '1') { // Forward
      stop();
      delay(50);
      forward();
      lastOperation = 1;
    }
    // ... (rest of the logic stays same, only comments updated)
  }
}

// ----------- MOTOR CONTROL FUNCTIONS -----------
void forward() {
  digitalWrite(left_in1, HIGH);
  digitalWrite(left_in2, LOW);
  digitalWrite(right_in3, HIGH);
  digitalWrite(right_in4, LOW);
  analogWrite(left_enable, motorSpeed);
  analogWrite(right_enable, motorSpeed);
}
// ... (stop, turn functions follow same pattern)