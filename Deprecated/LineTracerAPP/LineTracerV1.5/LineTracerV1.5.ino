// L298 Connection
#define LeftMotorF 6                                                  // Left Motor Forward Pin
#define LeftMotorR 7                                                  // Left Motor Reverse Pin
#define RightMotorF 8                                                 // Right Motor Forward Pin
#define RightMotorR 9                                                 // Right Motor Reverse Pin

enum : byte {RotateLeft, TurnLeft, Forward, TurnRight, RotateRight} direction;
//Treat it as   0         1         2         3           4

void setup() {
  pinMode(LeftMotorF, OUTPUT);                                        //Set Left Motor Forward Pin as OUTPUT
  pinMode(LeftMotorR, OUTPUT);                                        //Set Left Motor Reverse Pin as OUTPUT
  pinMode(RightMotorF, OUTPUT);                                       //Set Right Motor Forward Pin as OUTPUT
  pinMode(RightMotorR, OUTPUT);                                       //Set Right Motor Reverse Pin as OUTPUT
  pinMode(LED_BUILTIN, OUTPUT);                                       //Set Built-in LED pin as OUTPUT
}

void loop() {
  if (digitalRead(A3))        direction = Forward;                    //If A3 is HIGH, set the direction to Forward
  else if (digitalRead(A1))   direction = RotateLeft;                 //If A3 is LOW but A1 is HIGH, set the direction to RotateLeft
  else if (digitalRead(A5))   direction = RotateRight;                //If A3 and A1 are LOW but A5 is HIGH, set the direction to RotateRight
  else if (digitalRead(A2))   direction = TurnLeft;                   //If A3, A1 and A5 are LOW but A2 is HIGH, set the direction to TurnLeft
  else if (digitalRead(A4))   direction = TurnRight;                  //If A3, A1, A5 and A2 are LOW but A4 is HIGH, set the direction to TurnRight
  else return;                                                        //If A3, A1, A5, A2 and A4 are LOW, Start over

  int numRun = 0;                                                     //Start a new Counter
  byte sensorData = PINC;                                             //Copy the data from Register PINC to Variable sensorData
  while (PINC == sensorData) {                                        //While Register PINC has not changed
    if (direction <= Forward)     digitalWrite(RightMotorF, HIGH);    //If the direction is either Forward, TurnLeft or RotateLeft, set Right Motor to Forward
    if (direction >= Forward)     digitalWrite(LeftMotorF, HIGH);     //If the direction is either Forward, TurnRight or RotateRight, set Left Motor to Forward
    if (direction == RotateLeft)  digitalWrite(LeftMotorR, HIGH);     //If the direction is RotateLeft, set Left Motor to Reverse
    if (direction == RotateRight) digitalWrite(RightMotorR, HIGH);    //If the direction is RotateRight, set Right Motor to Reverse
    digitalWrite(LED_BUILTIN, HIGH);                                  //Set the Built-in LED to HIGH to indicate that the motor has been turn on

    //At this point the respective motor has been turn on
    if (numRun++ < 250) delay(10);                                    //If the increment of the counter(numRun) is less than 250, wait for 10ms
    else while (PINC == sensorData);                                  //else, wait until PINC has change
    digitalWrite(LeftMotorF, LOW);                                    //Set Left motor to stop
    digitalWrite(LeftMotorR, LOW);                                    //Set Left motor to stop
    digitalWrite(RightMotorF, LOW);                                   //Set Right motor to stop
    digitalWrite(RightMotorR, LOW);                                   //Set Right motor to stop
    digitalWrite(LED_BUILTIN, LOW);                                   //Set the Built-in LED to LOW to indicate that the motor has been turn off
    delay(10);                                                        //Wait for 10ms
  }
}

/*Hardware Connection (Data Connection)
  Arduino     L298     Sensor
     6 --------IN1        |       //Left Motor Forward Pin
     7 --------IN2        |       //Left Motor Reverse Pin
     8 --------IN3        |       //Right Motor Forward Pin
     9 --------IN4        |       //Right Motor Reverse Pin
    VCC--------ENA        |       //Left Motor Enable Pin
    VCC--------ENB        |       //Right Motor Enable Pin
    A1 ------------------S1       //Extreme Left Sensor
    A2 ------------------S2       //Centre Left Sensor
    A3 ------------------S3       //Middle Sensor
    A4 ------------------S4       //Centre Right Sensor
    A5 ------------------S5       //Extreme Right Sensor
*/
