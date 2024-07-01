//Variables
int rightMotor = 9;
int leftMotor = 8;
int bumper = 7;
int rtime = 1500;  //In Microseconds
int ltime = 1500;  //In Microseconds

/*  if time < 1500 turn backwards  //Max = 2000
    if time > 1500 turn forwards   //Min = 1000
    if time = 1500 stop
*/

float timeD;  // timeD = time difference

const int frontPing =  6; //Ping sensor at the front
const int rearPing =  5;  //Ping sensor at the rear/back
const float pi = 3.141592654; //the value of pi use for calculation

int lenghtOfTheRoom = 412;  //In centimetre
int x=0;
int oldx;
int r=0;

int noOfNinetyDegree;
int noOfNinetyDegree2;  //For turn the robot
int distancePerNinetyDegree;
int diametreOfWheel = 8.5;  //Diametre = 2*Radius //In centimetre
int diametreOfRobot = 30;   //In centimetre

long fduration, fdistance, fcm;  // for calculation
long rduration, rdistance, rcm;  // for calculation

void setup() {
  pinMode(rightMotor, OUTPUT);
  pinMode(leftMotor, OUTPUT);
  pinMode(bumper, INPUT);
  distancePerNinetyDegree = (diametreOfWheel*pi)/4;
  noOfNinetyDegree = lenghtOfTheRoom / distancePerNinetyDegree;
  timeDifference();
}

void loop() {
  getDistance();
  while (fcm == 0 || fcm > 15) {
    rtime = 2000;  //Rotate the wheel by 90 degree
    ltime = 1000;  //Rotate the wheel by 90 degree
    x++;
    action(ltime, rtime);
  }
  if (fcm < 15 && digitalRead(7) == HIGH && x == noOfNinetyDegree && r != 1) {
    for (int i = 1; i < noOfNinetyDegree2; i++) { //Repeat 90 Degree
      rtime = ltime = 2000;   //Rotate 90 degree of the wheel
      action(ltime, rtime);
    }
    rtime = ltime = (1500+timeD);  //Turn the robot 90 degree
    action(ltime, rtime);
    rtime = 2000;
    ltime = 2000;
    action(ltime, rtime);
    for (int i = 1; i < noOfNinetyDegree2; i++) { //Repeat 90 Degree
      rtime = ltime = 2000;   //Rotate 90 degree of the wheel
      action(ltime, rtime);
    }
    rtime = ltime = (1500+timeD);  //Turn the robot 90 degree
    action(ltime, rtime);
    x=0;
    r++;
  }
  if (fcm < 15 && digitalRead(7) == HIGH && x == noOfNinetyDegree && r == 1){
    for (int i = 1; i < noOfNinetyDegree2; i++) { //Repeat 90 Degree
      rtime = ltime = 1000;   //Rotate 90 degree of the wheel
      action(ltime, rtime);
    }
    rtime = ltime = (1500-timeD);  //Turn the robot 90 degree
    action(ltime, rtime);
    rtime = 2000;
    ltime = 2000;
    action(ltime, rtime);
    for (int i = 1; i < noOfNinetyDegree2; i++) { //Repeat 90 Degree
      rtime = ltime = 2000;   //Rotate 90 degree of the wheel
      action(ltime, rtime);
    }
    rtime = ltime = (1500-timeD);  //Turn the robot 90 degree
    action(ltime, rtime);
    x=0;
    r--;
  }
  
  

}

void getDistance() {
  pinMode(frontPing, OUTPUT);
  digitalWrite(frontPing, LOW);
  delayMicroseconds(2);
  digitalWrite(frontPing, HIGH);
  delayMicroseconds(5);
  digitalWrite(frontPing, LOW);
  pinMode(frontPing, INPUT);
  fduration = pulseIn(frontPing, LOW);
  fdistance = 0.5 * 344 * fduration;
  fcm = fdistance * 100;

  pinMode(frontPing, OUTPUT);
  digitalWrite(frontPing, LOW);
  delayMicroseconds(2);
  digitalWrite(frontPing, HIGH);
  delayMicroseconds(5);
  digitalWrite(frontPing, LOW);
  pinMode(frontPing, INPUT);
  rduration = pulseIn(frontPing, LOW);
  rdistance = 0.5 * 344 * rduration;
  rcm = rdistance * 100;
}

void action(int ltime, int rtime) {
  digitalWrite(rightMotor, HIGH);
  delayMicroseconds(rtime);
  digitalWrite(rightMotor, LOW);
  delayMicroseconds(20000 - rtime);  //The servo needs to have a pwm signal with period = 20ms

  digitalWrite(leftMotor, HIGH);
  delayMicroseconds(ltime);
  digitalWrite(leftMotor, LOW);
  delayMicroseconds(20000 - ltime);  //The servo needs to have a pwm signal with period = 20ms

}
void timeDifference() {
  timeD = 0.25 * pi * diametreOfRobot;
  timeD = (360 * timeD) / (pi * diametreOfWheel);
  noOfNinetyDegree2 = timeD / 90;
  timeD = timeD - (noOfNinetyDegree2 * 3);
  timeD = (timeD * 50) / 9;
}



