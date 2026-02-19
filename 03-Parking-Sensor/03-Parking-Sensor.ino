// Pin Definitions
const int triggerPin = A0;
const int echoPin = A1;
const int buzzerPin = 2;
const int blueLed = 3;   
const int greenLed = 4;  
const int yellowLed = 5; 
const int redLed = 6;    

// Variables
long duration;
int distance;

void setup() {
  // Initialize pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Start Serial Communication
  Serial.begin(9600);
}

void loop() {
  // Trigger the ultrasonic pulse
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Measure the duration of the incoming pulse
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in cm
  distance = (duration / 2) / 28.5;
  
  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  // Alert Logic
  if (distance < 5) {
    // Critical Danger: All LEDs and Buzzer on
    digitalWrite(redLed, HIGH);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(greenLed, HIGH);
    digitalWrite(blueLed, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(50);
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  } 
  else if (distance < 10) {
    // Red Alert
    digitalWrite(redLed, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(50);
    digitalWrite(redLed, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(250);
  } 
  else if (distance < 25) {
    // Yellow Warning
    digitalWrite(yellowLed, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(50);
    digitalWrite(yellowLed, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(500);
  } 
  else if (distance < 50) {
    // Green Info
    digitalWrite(greenLed, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(50);
    digitalWrite(greenLed, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(750);
  } 
  else {
    // Safe: Only Blue LED blinks slowly
    digitalWrite(blueLed, HIGH);
    digitalWrite(buzzerPin, LOW);
    delay(1000);
    digitalWrite(blueLed, LOW);
    delay(500);
  }
}