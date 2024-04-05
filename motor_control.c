// Codeed with help from RoboIndia on Motor Control

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
int defaultSpeed = 120;

void setup()
{
  pinMode(inputPin1, OUTPUT);
  pinMode(inputPin2, OUTPUT);
  pinMode(inputPin3, OUTPUT);
  pinMode(inputPin4, OUTPUT);
  pinMode(ENA, OUTPUT); // Set ENA as OUTPUT
  pinMode(ENB, OUTPUT); // Set ENB as OUTPUT
  Serial.begin(9600);   // opens serial port, sets data rate to 9600 bps

  analogWrite(ENA, defaultSpeed);
  analogWrite(ENB, defaultSpeed);
}

void loop()
{
  // turn on motors
  digitalWrite(inputPin1, HIGH);
  digitalWrite(inputPin2, LOW);
  digitalWrite(inputPin3, HIGH);
  digitalWrite(inputPin4, LOW);

  if (Serial.available() > 0)
  {
    // read the incoming byte:
    String input = Serial.readStringUntil(',');
    incomingSpeedA = input.toInt();
    input = Serial.readStringUntil('\n');
    incomingSpeedB = input.toInt();

    if (incomingSpeedA > defaultSpeed)
    {
      // set motor A speed
      Serial.print("Setting motor A speed to: ");
      Serial.println(incomingSpeedA);
      analogWrite(ENA, incomingSpeedA);
    }

    if (incomingSpeedB > defaultSpeed)
    {
      // set motor B speed
      Serial.print("Setting motor B speed to: ");
      Serial.println(incomingSpeedB);
      analogWrite(ENB, incomingSpeedB);
    }
  }
}
