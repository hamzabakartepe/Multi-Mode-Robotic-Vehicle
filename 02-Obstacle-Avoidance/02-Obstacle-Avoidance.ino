const int trigPin = 2; // Sensor trigger pin
const int echoPin = 3; // Sensor echo pin

// Motor driver pins
const int left_en = 5; 
const int left_fwd = 6; 
const int left_back = 7;
const int right_en = 10;
const int right_fwd = 11;
const int right_back = 4;

long duration = 0;
int distance = 0;
int motor_speed = 170;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(left_fwd, OUTPUT);
  pinMode(left_back, OUTPUT);
  pinMode(right_fwd, OUTPUT);
  pinMode(right_back, OUTPUT);
  pinMode(right_en, OUTPUT);
  pinMode(left_en, OUTPUT);
}

void loop() {
  // Ultrasonic distance measurement using HC-SR04
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);   
  digitalWrite(trigPin, LOW); 

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 28.5;

  Serial.println(distance);

  if (distance < 30) { // If obstacle is closer than 30cm, move back and turn
    // Move Backward
    digitalWrite(left_fwd, LOW);
    digitalWrite(left_back, HIGH);
    digitalWrite(right_fwd, LOW);
    digitalWrite(right_back, HIGH);
    analogWrite(right_en, motor_speed);
    analogWrite(left_en, motor_speed);
    delay(150);

    // Turn Left (Spin)
    digitalWrite(left_fwd, LOW);
    digitalWrite(left_back, HIGH);
    digitalWrite(right_fwd, HIGH);
    digitalWrite(right_back, LOW);
    analogWrite(right_en, motor_speed);
    analogWrite(left_en, motor_speed);
    delay(250);
  } 
  else { // Path is clear, move forward
    digitalWrite(left_fwd, HIGH);
    digitalWrite(left_back, LOW);
    digitalWrite(right_fwd, HIGH);
    digitalWrite(right_back, LOW);
    analogWrite(right_en, motor_speed);
    analogWrite(left_en, motor_speed);
  }
}