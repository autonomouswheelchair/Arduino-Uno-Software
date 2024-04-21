#include <Arduino.h>

// Define pins for L293D Motor Controller
const int inputPin1 = 10;  // Pin 15 of L293D IC
const int inputPin2 = 11;  // Pin 10 of L293D IC
const int inputPin3 = 9;   // Pin 7 of L293D IC
const int inputPin4 = 8;   // Pin 2 of L293D IC
int ENA = 6; // L293D Enable Pin for motor A
int ENB = 5; // L293D Enable Pin for motor B
int defaultSpeed = 60;

// Define pins for HC-SR04 Ultrasonic Sensor
const int trigPin = 12;
const int echoPin = 13;

// Global variables
long duration;
int distance;
int stop = 0;
int incomingSpeedA = 0;    // for incoming speed data of motor A
int incomingSpeedB = 0;    // for incoming speed data of motor B

void setup() {
  Serial.begin(9600);
  pinMode(inputPin1, OUTPUT);
  pinMode(inputPin2, OUTPUT);
  pinMode(inputPin3, OUTPUT);
  pinMode(inputPin4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    if (command == "TEST_MOTOR_CONTROLLER") {
      testMotorController();
    } else if (command == "TEST_ULTRASONIC_SENSOR") {
      testUltrasonicSensor();
    }
  }

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (digitalRead(2) == 1 && distance > 10) {
    if (stop == 1) {
      //jumpstart
      digitalWrite(inputPin1, HIGH);
      digitalWrite(inputPin2, LOW);
      digitalWrite(inputPin3, HIGH);
      digitalWrite(inputPin4, LOW);
      analogWrite(ENA, 120);
      analogWrite(ENB, 2 * 120);
      delay(1000); // waits for a second
      stop = 0;
    }

    if (Serial.available() > 0) {
      String input = Serial.readStringUntil(',');
      incomingSpeedA = input.toInt();
      input = Serial.readStringUntil('\n');
      incomingSpeedB = input.toInt();

      // set motor A speed
      Serial.print("Setting motor A speed to: ");
      Serial.println(incomingSpeedA);
      analogWrite(ENA, incomingSpeedA);

      // set motor B speed
      Serial.print("Setting motor B speed to: ");
      Serial.println(incomingSpeedB);
      analogWrite(ENB, 2 * incomingSpeedB);
    }
  } else {
    //turn off motor
    digitalWrite(inputPin1, LOW);
    digitalWrite(inputPin2, LOW);
    digitalWrite(inputPin3, LOW);
    digitalWrite(inputPin4, LOW);
    stop = 1;
  }
}

void testMotorController() {
  // Test Motor Controller
  digitalWrite(inputPin1, HIGH);
  digitalWrite(inputPin2, LOW);
  digitalWrite(inputPin3, HIGH);
  digitalWrite(inputPin4, LOW);
  analogWrite(ENA, 120);
  analogWrite(ENB, 2 * 120);
  delay(1000);
  digitalWrite(inputPin1, LOW);
  digitalWrite(inputPin2, LOW);
  digitalWrite(inputPin3, LOW);
  digitalWrite(inputPin4, LOW);
  
  // Check if motor is running
  if !(digitalRead(inputPin1) == HIGH && digitalRead(inputPin2) == LOW &&
      digitalRead(inputPin3) == HIGH && digitalRead(inputPin4) == LOW &&
      analogRead(ENA) == 120 && analogRead(ENB) == 2 * 120) {
    Serial.println("Motor Controller Test Failed");
  } else {
    Serial.println("Motor Controller Test Successful");
  }
}

void testUltrasonicSensor() {
  // Test Ultrasonic Sensor
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  
  // Check if distance is valid
  if !(distance > 0) {
    Serial.println("Ultrasonic Sensor Test Failed");
  } else {
    Serial.print("Ultrasonic Sensor Distance: ");
    Serial.println(distance);
    Serial.println("Ultrasonic Sensor Test Successful");
  }
}
