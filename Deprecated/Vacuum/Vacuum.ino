// Digital //
const int FUS = 2;
const int BUS = 4;

// Servo //
const int FUSServo = 3; // Front Ultrasonic Sensor Servo
const int leftMotor = 5; // Left Wheel Servo
const int rightMotor = 6; //  Right Wheel Servo


// Long Value //
long duration; // Time taken for Ultrasound to get back to the
long frontUSensor; // Front Ultrasonic Sensor
long backUSensor; // Back Ultrasonic Sensor
long leftAUSensor; // Left Ultrasonic Sensor
long rightAUSensor; // Right Ultrasonic Sensor

// Integer //
const int pi = 3.141592654;
const int wheelRadius = 100;

/*  For Servo Time
    if time < 1500 turn Clockwise        //Max = 2000
    if time > 1500 turn Anti-Clockwise   //Min = 1000
    if time = 1500 stop
*/

void setup() {


}
void loop() {
  frontUSensor = ReadUltrasoundSensor(FUS);
  backUSensor = ReadUltrasoundSensor(BUS);

  while ( frontUSensor > 10 ) {
    runServo(1250, leftMotor);
    runServo(1750, rightMotor);
  }
  if ( frontUSensor == 10 ) {
    runServo(1500, leftMotor);
    runServo(1500, rightMotor);
  }


}
void runServo(int timeS, int ServoPin) {
  digitalWrite(ServoPin, HIGH);
  delayMicroseconds(timeS);
  digitalWrite(ServoPin, LOW);
  delay(20);
}
long ReadUltrasoundSensor(int US) {
  pinMode(US, OUTPUT);
  digitalWrite(US, LOW);
  delayMicroseconds(2);
  digitalWrite(US, HIGH);
  delayMicroseconds(5);
  digitalWrite(US, LOW);

  pinMode(US, INPUT);
  duration = pulseIn(US, HIGH);
  return duration / 29 / 2 ;
}

void PathDetection() {
  int servoTime = 0;
  int noObstacle = 0;
  frontUSensor = ReadUltrasoundSensor(FUS);
  for (int a = 0; a <= 67.5 ; a = a + 22.5) {
    servoTime = 500 / 90;
    servoTime = servoTime * a;
    runServo(1500 - servoTime, FUSServo);
    leftAUSensor = ReadUltrasoundSensor(FUS);
    runServo(1500 + servoTime, FUSServo);
    rightAUSensor = ReadUltrasoundSensor(FUS);
    noObstacle = (frontUSensor / cos(a)) + 5;
    if (leftAUSensor < noObstacle && rightAUSensor < noObstacle ) {
      continue;
    }
    else if ( leftAUSensor >= noObstacle ) {
      int b = 0;
      runServo(1000, FUSServo);
      runServo(2000, leftMotor);
      runServo(2000, rightMotor);
      frontUSensor = ReadUltrasoundSensor(FUS);
      while ( frontUSensor > 10 ) {
        frontUSensor = ReadUltrasoundSensor(FUS);
        runServo(1000, leftMotor);
        runServo(2000, rightMotor);
        b++;
      }
      runServo(1000, leftMotor);
      runServo(1000, rightMotor);
      runServo(1000, leftMotor);
      runServo(2000, rightMotor);
      while ( frontUSensor > 10 ) {
        frontUSensor = ReadUltrasoundSensor(FUS);
        runServo(1000, leftMotor);
        runServo(2000, rightMotor);
      }
      runServo(1000, leftMotor);
      runServo(1000, rightMotor);
      while ( b > 0) {
        runServo(1000, leftMotor);
        runServo(2000, rightMotor);
        b--;
      }
      runServo(2000, leftMotor);
      runServo(2000, rightMotor);
      runServo(1500, FUSServo);
      break;
    }
    else if ( rightAUSensor >= noObstacle ) {
      int b = 0;
      runServo(1000, FUSServo);
      runServo(1000, leftMotor);
      runServo(1000, rightMotor);
      frontUSensor = ReadUltrasoundSensor(FUS);
      while ( frontUSensor > 10 ) {
        frontUSensor = ReadUltrasoundSensor(FUS);
        runServo(1000, leftMotor);
        runServo(2000, rightMotor);
        b++;
      }
      runServo(2000, leftMotor);
      runServo(2000, rightMotor);
      runServo(1000, leftMotor);
      runServo(2000, rightMotor);
      while ( frontUSensor > 10 ) {
        frontUSensor = ReadUltrasoundSensor(FUS);
        runServo(1000, leftMotor);
        runServo(2000, rightMotor);
      }
      runServo(2000, leftMotor);
      runServo(2000, rightMotor);
      while ( b > 0) {
        runServo(1000, leftMotor);
        runServo(2000, rightMotor);
        b--;
      }
      runServo(1000, leftMotor);
      runServo(1000, rightMotor);
      runServo(1500, FUSServo);
      break;
    }
    if(leftAUSensor < noObstacle && rightAUSensor < noObstacle && a == 67.5){
      
    }

    }
  }


