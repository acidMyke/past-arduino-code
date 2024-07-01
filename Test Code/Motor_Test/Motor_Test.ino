#define Left 0
#define Right 1

void motorRun(int motor, int speed);  // Declare

const int motorPin[2][2] = {{13, 15},{14, 12}};
//const int motorPin[2][2] = {{12, 14},{15, 13}};

int rightSpeed, leftSpeed;

void setup(){
  Serial.begin(115200);
  for (int i = 0; i < 4; i++) {
    pinMode(motorPin[0][i], OUTPUT);
    digitalWrite(motorPin[0][i], LOW);
  }
  while(digitalRead(0) == LOW)delay(500);
}

void loop() {
  rightSpeed = 255;
  Serial.println("Change pin of left motor");
  for (leftSpeed = 255 ; leftSpeed >= -255; leftSpeed = leftSpeed - 10 ) {
    if(leftSpeed < 120 && leftSpeed > 0) leftSpeed = -120;
    int returnLeftSpeed = -leftSpeed, returnRightSpeed = -rightSpeed;
    motorRun(Left, leftSpeed);
    motorRun(Right, rightSpeed);
    delay(1000);
    motorRun(Left, 0);
    motorRun(Right, 0);
    motorRun(Left, returnLeftSpeed);
    motorRun(Right, returnLeftSpeed);
    delay(1000);
    motorRun(Left, 0);
    motorRun(Right, 0);
  }
  leftSpeed = 255;
  for (rightSpeed = 255 ; rightSpeed >= -255; rightSpeed-- ) {
    int returnLeftSpeed = -leftSpeed, returnRightSpeed = -rightSpeed;
    motorRun(Left, leftSpeed);
    motorRun(Right, rightSpeed);
    delay(500);
    motorRun(Left, 0);
    motorRun(Right, 0);
    motorRun(Left, returnLeftSpeed);
    motorRun(Right, returnLeftSpeed);
    delay(500);
    motorRun(Left, 0);
    motorRun(Right, 0);
  }
  //digitalWrite(14, HIGH);
}

void motorRun(int motor, int speed) {
  Serial.println(String(motor) + "Motor speed" + String(speed));
  if (speed > 0) {
    digitalWrite(motorPin[motor][0], 0);  // Forward
    analogWrite(motorPin[motor][1], speed); // at this speed
  }
  else if (speed < 0) {
    speed = -speed;
    digitalWrite(motorPin[motor][0], 1);  // Reverse
    analogWrite(motorPin[motor][1], speed); // at this speed
  }
  if (speed == 0){
    digitalWrite(motorPin[motor][0], 0);  // Forward
    digitalWrite(motorPin[motor][1], 0); // at this speed
  }
}

/*
  void motorRun(int speed, int motor) {
  if (speed > 0) {
    digitalWrite(motorPin[motor][0], 0);  // Forward
    analogWrite(motorPin[motor][1], speed); // at this speed
    delay(timing); // for this amount of time
    digitalWrite(motorPin[motor][1], 0); // than stop
    digitalWrite(motorPin[motor][0], 1); // Reverse
    analogWrite(motorPin[motor][1], speed); // at the same speed
    delay(timing); // for the same amount of time
    digitalWrite(motorPin[motor][1], 0); // then stop
    digitalWrite(motorPin[motor][0], 0); // change back to forward
  }
  else if (speed < 0) {
    speed = -speed;
    digitalWrite(motorPin[motor][0], 1);  // Reverse
    analogWrite(motorPin[motor][1], speed); // at this speed
    delay(timing); // for this amount of time
    digitalWrite(motorPin[motor][1], 0); // than stop
    digitalWrite(motorPin[motor][0], 0); // Forword
    analogWrite(motorPin[motor][1], speed); // at the same speed
    delay(timing); // for the same amount of time
    digitalWrite(motorPin[motor][1], 0); // then stop
    digitalWrite(motorPin[motor][0], 0); // change back to forward
  }
  }
*/
