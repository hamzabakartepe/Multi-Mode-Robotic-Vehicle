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
      continue_with_the_final_process = 1;
    }
    else if (data == '2') // Backward
    {
      stop();
      delay(50);
      backward();
      continue_with_the_final_process = 2;
    }
    else if (data == '3') // Left
    {
      stop();
      delay(50);
      left();
      continue_with_the_final_process = 3;
    }
    else if (data == '4') // Right
    {
      stop();
      delay(50);
      right();
      continue_with_the_final_process = 4;
    }
    else if (data == '6') // Stop
    {
      stop();
      delay(50);
      continue_with_the_final_process = 6;
    }
    else if (data == '0') // Speed up
    {
      motorSpeed += 25;
      if (motorSpeed > 255) motorSpeed = 255;

      Serial.print("Motor speed = ");
      Serial.println(motorSpeed);
      continue_with_the_final_process();
    }
    else if (data == '5') // Speed Down
    {
      motorSpeed -= 25;
      if (motorSpeed < 0) motorSpeed = 0;

      Serial.print("Motor speed = ");
      Serial.println(motorSpeed);
      continue_with_the_final_process();
    }
  }
  delay(10);
}

// ----------- MOTOR CONTROL FUNCTIONS -----------
void forward() 
{
  // Left motor Foward
  digitalWrite(left_in1, HIGH);
  digitalWrite(left_in2, LOW);
  // Right motor Foward
  digitalWrite(right_in3, HIGH);
  digitalWrite(right_in4, LOW);
  // Speed controller
  analogWrite(left_enable, motorSpeed);
  analogWrite(right_enable, motorSpeed);
}

void backward()
{
  // Left motor Backward
  digitalWrite(left_in1, LOW);
  digitalWrite(left_in2, HIGH);
  // Right motor Backward
  digitalWrite(right_in3, LOW);
  digitalWrite(right_in4, HIGH);
  // Speed controller
  analogWrite(left_enable, motorSpeed);
  analogWrite(right_enable, motorSpeed);
}

// Turn Left (Left motor backward, Right motor Foward)
void left()
{
  // Left motor Backward
  digitalWrite(sol_in1, LOW);
  digitalWrite(sol_in2, HIGH);
  // Right motor Foward
  digitalWrite(sag_in3, HIGH);
  digitalWrite(sag_in4, LOW);
  // Speed controller
  analogWrite(left_enable, motorSpeed);
  analogWrite(right_enable, motorSpeed);
}

// Turn Right (Left motor foward, Right motor backward)
void right()
{
  // Right motor Foward
  digitalWrite(sol_in1, HIGH);
  digitalWrite(sol_in2, LOW);
// Right motor Backward
  digitalWrite(sag_in3, LOW);
  digitalWrite(sag_in4, HIGH);
  // Speed controller
  analogWrite(left_enable, motorSpeed);
  analogWrite(right_enable, motorSpeed);
}

void stop()
{
  // All motors backward
  digitalWrite(sol_in1, LOW);
  digitalWrite(sol_in2, LOW);
  digitalWrite(sag_in3, LOW);
  digitalWrite(sag_in4, LOW);
  
  //Stop the motors by setting the Enable pins to 0.
  analogWrite(sol_enable, 0);
  analogWrite(sag_enable, 0);

  son_islem = 6;
}


// After changing speed, continue the last movement.
void continue_with_the_final_process()
{
  if (lastOperation == 1) foward();
  else if (lastOperation == 2) backward();
  else if (lastOperation == 3) left();
  else if (lastOperation == 4) right();
  else if (lastOperation == 6) stop();
}
