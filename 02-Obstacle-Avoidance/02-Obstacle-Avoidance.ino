const int trig = 2; // Sensor pins defined
const int echo = 3;

const int left_e = 5; 
const int left_f = 6; // Motor driver pins defined
const int left_b = 7;
const int right_e = 10;
const int right_f = 11;
const int right_b = 4;

long duration = 0; // Variables for distance calculation
int distance = 0;
int motor_speed = 170;

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT); // Trigger pin set as output
  pinMode(echo, INPUT);  // Echo pin set as input
  // ... (pinMode outputs for motors)
}

void loop() {
  // Distance calculated using HC-SR04
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = (duration / 2) / 29.1;

  if (distance < 30) { // If distance is less than 30cm, move back and turn
    // ... (avoidance logic)
  } else { // If path is clear, move forward
    // ... (forward logic)
  }
}