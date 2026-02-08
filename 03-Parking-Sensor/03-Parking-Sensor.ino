const int trigPin = A0;
const int echoPin = A1;
const int buzzer = 2;
const int blueLED = 3;
const int yellowLED = 4;
const int orangeLED = 5;
const int redLED = 6;

long duration;
int distance;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(orangeLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Ultrasonic pulse generation
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.println(distance);

  // Alert logic based on distance
  if(distance < 5) { // Danger zone
    allLedsOn();
    digitalWrite(buzzer, HIGH);
    delay(50);
    allLedsOff();
    digitalWrite(buzzer, LOW);
    delay(100);
  } 
  // ... (Other distance conditions follow same logic)
}

void allLedsOn() {
  digitalWrite(redLED, HIGH);
  digitalWrite(orangeLED, HIGH);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(blueLED, HIGH);
}

void allLedsOff() {
  digitalWrite(redLED, LOW);
  digitalWrite(orangeLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(blueLED, LOW);
}