// L298 Connection
#define RightMotorEN 9
#define LeftMotorEN 3
#define LeftMotorC 4
#define LeftMotorD 5
#define RightMotorC 6
#define RightMotorD 7

typedef enum {NotRun, RotateLeft, TurnLeft, Forward, TurnRight, RotateRight} State;

State curRun = NotRun;
State prevRun = NotRun;

int numRun = 0;
byte prevData = 0;

void setup() {
  pinMode(LeftMotorEN, OUTPUT);
  pinMode(RightMotorEN, OUTPUT);
  pinMode(LeftMotorC, OUTPUT);
  pinMode(LeftMotorD, OUTPUT);
  pinMode(RightMotorC, OUTPUT);
  pinMode(RightMotorD, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
  delay(100);
  digitalWrite(LeftMotorEN, HIGH);
  digitalWrite(RightMotorEN, HIGH);
  digitalWrite(LeftMotorC, LOW);
  digitalWrite(LeftMotorD, LOW);
  digitalWrite(RightMotorC, LOW);
  digitalWrite(RightMotorD, LOW);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  prevData = PINC;
  if (digitalRead(A3)) forward();
  else if (digitalRead(A1)) rotateLeft();
  else if (digitalRead(A5)) rotateRight();
  else if (digitalRead(A2)) turnLeft();
  else if (digitalRead(A4)) turnRight();
  else curRun = NotRun;

  if (curRun != NotRun)
    if (curRun == prevRun)
      if (numRun < 250) numRun++;
      else while (PINC == prevData);
    else {
      prevRun = curRun;
      numRun = 0;
    }
  delay(10);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(12, LOW);
  digitalWrite(LeftMotorC, LOW);
  digitalWrite(LeftMotorD, LOW);
  digitalWrite(RightMotorC, LOW);
  digitalWrite(RightMotorD, LOW);
  delay(20);
}

void rotateLeft() {
  digitalWrite(LeftMotorD, HIGH);
  digitalWrite(RightMotorC, HIGH);
  curRun = RotateLeft;
}

void turnLeft() {
  digitalWrite(RightMotorC, HIGH);
  digitalWrite(12, HIGH);
  curRun = TurnLeft;
}

void forward() {
  digitalWrite(LeftMotorC, HIGH);
  digitalWrite(RightMotorC, HIGH);
  curRun = Forward;
}

void turnRight() {
  digitalWrite(LeftMotorC, HIGH);
  digitalWrite(12, HIGH);
  curRun = TurnRight;
}

void rotateRight() {
  digitalWrite(LeftMotorC, HIGH);
  digitalWrite(RightMotorD, HIGH);
  curRun = RotateRight;
}

