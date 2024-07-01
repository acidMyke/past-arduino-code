                      /* Forward
                     Sensor front
                 Left     ____    Right
               Motor B   /    \   Motor A
  ENB <- Motor Driver   |      |   ENA <- Motor Driver
  IN3 <- Motor Driver   |      |   IN1 <- Motor Driver
  IN4 <- Motor Driver   |      |   IN2 <- Motor Driver
                         \____/
                        Backward  */

// Motor Speed
int Speed_A = 80;
int Speed_B = 80;

// Motor A pins (enableA = enable motor, pinA1 = forward, pinA2 = backward)
//To Motor Driver connections, L298N
int enableA = 3;   //ENA
int pinA1 = 6;     //IN1
int pinA2 = 7;     //IN2
//Motor B pins (enabledB = enable motor, pinB2 = forward, pinB2 = backward)
int enableB = 5;   //ENB
int pinB1 = 8;     //IN3
int pinB2 = 9;     //IN4
int sensor[5] = {0, 0, 0, 0, 0};

void setup(){
  pinMode(enableA, OUTPUT);
  pinMode(pinA1, OUTPUT);
  pinMode(pinA2, OUTPUT);
  pinMode(enableB, OUTPUT);
  pinMode(pinB1, OUTPUT);
  pinMode(pinB2, OUTPUT);
}
void loop(){
  enableMotors();
  analogWrite(enableA, Speed_A);
  analogWrite(enableB, Speed_B);
  sensor[0] = digitalRead(A1);
  sensor[1] = digitalRead(A2);
  sensor[2] = digitalRead(A3);
  sensor[3] = digitalRead(A4);
  sensor[4] = digitalRead(A5);
  //               S1                 S2                  S3                  S4                   S5
  if      ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0))
    forward(10); // Centre line
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 0))
    forward(20); // Centre line
    
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 0))
    turnRight(1); // Centre off R1
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 1))
    turnRight(1); // Centre off R1
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 0))
    turnRight(1); // Centre off R1
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))
    turnRight(1); // Centre off R1
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 1))
    turnRight(1); // Centre off far R1
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0))
    turnLeft(1); // Centre off L1
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0))
    turnLeft(1); // Centre off L1
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0))
    turnLeft(1); // Centre off L1
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0))
    turnLeft(1); // Centre off L1
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0))
    turnLeft(1); // Centre off far L1
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))
    brake(1); // All sensor detected, brake.
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0))
    brake(1); // All sensors not detected, brake.
  else
    forward(10);
}

//Define high-level H-bridge commands
void enableMotors()
{
  motorAOn();
  motorBOn();
}

void disableMotors()
{
  motorAOff();
  motorBOff();
}

void forward(int time)
{
  motorAForward();
  motorBForward();
  delay(time);
}

void backward(int time)
{
  motorABackward();
  motorBBackward();
  delay(time);
}

void turnLeft(int time)
{
  motorAForward();
  motorBBrake();
  delay(time);
}

void turnRight(int time)
{
  motorABrake();
  motorBForward();
  delay(time);
}

void coast(int time)
{
  motorACoast();
  motorBCoast();
  delay(time);
}

void brake(int time)
{
  motorABrake();
  motorBBrake();
  delay(time);
}

//Define low-level H-bridge commands
//enable motors
void motorAOn()
{
  digitalWrite(enableA, HIGH);
}

void motorBOn()
{
  digitalWrite(enableB, HIGH);
}

//disable motors
void motorAOff()
{
  digitalWrite(enableB, LOW);
}

void motorBOff()
{
  digitalWrite(enableA, LOW);
}

//motor A controls
void motorAForward()
{
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, LOW);
}

void motorABackward()
{
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, HIGH);
}

//motor B controls
void motorBForward()
{
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, LOW);
}

void motorBBackward()
{
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
}

//coasting and braking
void motorACoast()
{
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, LOW);
}

void motorABrake()
{
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, HIGH);
}

void motorBCoast()
{
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, LOW);
}

void motorBBrake()
{
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, HIGH);
}
