int readButton() {
  int buttonValue = -1;
  for (int x = 0; x < 3; x++) {
    digitalWrite(buttonPin[x], HIGH);
    for (int y = 6; y >= 3; y--) {
      if (digitalRead(buttonPin[y]) == HIGH) {
        buttonValue = x * 4 + (4 - (y - 3)) + 1;
      }
    }
  }
  if (buttonValue == 11) return 0;
  else return buttonValue;
}

void interval() {
  if (oldMillis < millis() - 1000) {
    time[2]++;
    oldMillis = millis() - oldMillis - 1000;
  }
  if (time[2] == 60) {
    time[1]++;
    time[2] = 0;
  }
  if (time[1] == 60) {
    time[0]++;
    time[1] = 0;
  }
  if (time[0] == 24) {
    date[0]++;
    date[3]++;
    time[2] = 0;
    time[1] = 0;
    time[0] = 0;
  }
  if (date[3] == 7) {
    date[3] = 1;
    date[4]++;
  }
  if (date[0] == noOfDay[date[1]]) {
    date[1]++;
    date[0];
  }
}

void display(int* arr, int mode) {
  switch(mode){
    case 1: LCD.print("Time: " + String(arr[0]) + ":" + String(arr[1]) + ":" + String(arr[2])); break;
    case 2: LCD.print("Date: " + String(arr[0]) + nameOfMonth[arr[1]]+ String(arr[2]));
  }
}

void Time() {

}

void Date() {

}

void Alarm() {

}

void Timer() {

}

void Stopwatch() {

}

void getSerialTime() {

}

void getTemp() {

}
