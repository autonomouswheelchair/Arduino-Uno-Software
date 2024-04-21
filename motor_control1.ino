// Tutorial by RoboIndia on Motor Control
// Hardware Required: Motor Driver (By RoboIndia) & Arduino

// Motor A
const int inputPin1 = 10;  // Pin 15 of L293D IC
const int inputPin2 = 11;  // Pin 10 of L293D IC
// Motor B
const int inputPin3 = 9;   // Pin 7 of L293D IC
const int inputPin4 = 8;   // Pin 2 of L293D IC
int incomingSpeedA = 0;    // for incoming speed data of motor A
int incomingSpeedB = 0;    // for incoming speed data of motor B

int ENA = 6; // L293D Enable Pin for motor A
int ENB = 5; // L293D Enable Pin for motor B
int defaultSpeed = 60;
// defines pins numbers
const int trigPin = 12;
const int echoPin = 13;
// defines variables
long duration;
int distance;
int stop = 0;
 

void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(inputPin1, OUTPUT);
  pinMode(inputPin2, OUTPUT);
  pinMode(inputPin3, OUTPUT);
  pinMode(inputPin4, OUTPUT);
  pinMode(ENA, OUTPUT); // Set ENA as OUTPUT
  pinMode(ENB, OUTPUT); // Set ENB as OUTPUT
  Serial.begin(9600);   // opens serial port, sets data rate to 9600 bps
// turn on motors
  digitalWrite(inputPin1, HIGH);
  digitalWrite(inputPin2, LOW);
  digitalWrite(inputPin3, HIGH);
  digitalWrite(inputPin4, LOW);
  analogWrite(ENA, 120);
  analogWrite(ENB, 2*120);
   delay(2000); // waits for a second

}

void loop()
{

   // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  


  if(digitalRead(2)==1 && distance > 10){
    if(stop == 1){
    //jumpstart

  digitalWrite(inputPin1, HIGH);
  digitalWrite(inputPin2, LOW);
  digitalWrite(inputPin3, HIGH);
  digitalWrite(inputPin4, LOW);
  analogWrite(ENA, 120);
  analogWrite(ENB, 2*120);
  delay(1000); // waits for a second
  stop = 0;
  }
   
  
  if (Serial.available() > 0)
  {
    // read the incoming byte:
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
      analogWrite(ENB, 2*incomingSpeedB);
    
  }
  }
  else{
    //turn off motor
  digitalWrite(inputPin1, LOW);
  digitalWrite(inputPin2, LOW);
  digitalWrite(inputPin3, LOW);
  digitalWrite(inputPin4, LOW);
  stop = 1;

  }
}
