// L298 Connection
#define LeftMotorF 6  // Left Motor Forward Pin
#define LeftMotorR 7  // Left Motor Reverse Pin
#define RightMotorF 8 // Right Motor Forward Pin
#define RightMotorR 9 // Right Motor Reverse Pin

void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(LeftMotorF, OUTPUT);  //Set Left Motor Forward Pin as OUTPUT
  pinMode(LeftMotorR, OUTPUT);  //Set Left Motor Reverse Pin as OUTPUT
  pinMode(RightMotorF, OUTPUT); //Set Right Motor Forward Pin as OUTPUT
  pinMode(RightMotorR, OUTPUT); //Set Right Motor Reverse Pin as OUTPUT
  pinMode(LED_BUILTIN, OUTPUT); //Set Built-in LED pin as OUTPUT
  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
}

void loop() {
  if (PINC == 0x00) return;
  
  int numRun = 0;                                                                               //Start a new Counter
  byte prevData = PINC;                                                                         //Copy the data from Register PINC to Variable prevData
  while (PINC == prevData) {                                                                      //While Register PINC has not changed
    if (digitalRead(A1) || digitalRead(A2) || digitalRead(A3)) digitalWrite(RightMotorF, HIGH);   //If A1, A2 or A3 is HIGH, set Right Motor to Forward 
    if (digitalRead(A3) || digitalRead(A4) || digitalRead(A5)) digitalWrite(LeftMotorF, HIGH);    //If A3, A4 or A5 is HIGH, set Left Motor to Forward
    if (digitalRead(A1))                                       digitalWrite(LeftMotorR, HIGH);    //If A1 is HIGH, set Left Motor to Backward
    if (digitalRead(A5))                                       digitalWrite(RightMotorR, HIGH);   //If A5 is HIGH, set Right Motor to Backward
    digitalWrite(LED_BUILTIN, HIGH);                                                              //Set the Built-in LED to HIGH to indicate that the motor has been turn on

    //At this point the respective motor has been turn on
    if (numRun++ < 250) delay(10);                                                                //If the increment of the counter(numRun) is less than 250, wait for 10ms
    else while (PINC == prevData);                                                                //else, wait until PINC has change
    digitalWrite(LeftMotorF, LOW);                                                                //Set Left motor to stop
    digitalWrite(LeftMotorR, LOW);                                                                //Set Left motor to stop
    digitalWrite(RightMotorF, LOW);                                                               //Set Right motor to stop
    digitalWrite(RightMotorR, LOW);                                                               //Set Right motor to stop
    digitalWrite(LED_BUILTIN, LOW);                                                               //Set the Built-in LED to LOW to indicate that the motor has been turn off
    delay(10);                                                                                    //Wait for 10ms
  }
}

/*Hardware Connection (Data Connection)
  Arduino     L298     Sensor
     4 --------IN1        |       //Left Motor Forward Pin
     5 --------IN2        |       //Left Motor Reverse Pin
     6 --------IN3        |       //Right Motor Forward Pin
     7 --------IN4        |       //Right Motor Reverse Pin
    VCC--------ENA        |       //Left Motor Enable Pin
    VCC--------ENB        |       //Right Motor Enable Pin
    A1 ------------------S1       //Extreme Left Sensor
    A2 ------------------S2       //Centre Left Sensor
    A3 ------------------S3       //Middle Sensor
    A4 ------------------S4       //Centre Right Sensor
    A5 ------------------S5       //Extreme Right Sensor
*/
