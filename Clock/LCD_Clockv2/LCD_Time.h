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

String Time(int mode = 0) {
  if (mode == 0) {
    LCD.blink();
    LCD.setCursor(0, 0);
    LCD.print("Set: ");
    for (int i = 0; i < 3; i++) {
      int digit[2], x;
      while (x != 2) {
        LCD.setCursor(i * 2 + x, 1);
        int buttonState = readButton();
        while (buttonState == -1)buttonState = readButton();
        if (buttonState == 10)return;
        else if (buttonState == 12) {
          digit[x] = buttonState;
          x++;
        }
        LCD.print(buttonState);
      }
      time[i] = digit[0] * 10 + digit[1];
    }
  }
  else if (mode == 1) {
    String str = "Time: " + String(time[0]) + ":" + String(time[1]) + ":" + String(time[2]);
    return str;
  }
}

String Date(int mode = 0) {

}

String Alarm(int mode = 0) {
  if (mode == -1) {
    for (int a; a < alarmEn; a++) {
      if (alarm[a][0] == time[0] && alarm[a][1] == time[1]) {
        while (readButton() == -1) digitalWrite(buzzerPin, HIGH);
      }
    }
  }
  else if (mode == 0) {
    int buttonState = readButton();
    while (buttonState == -1)buttonState = readButton();
    if (buttonState == 10) alarmEn == 0;
    int alarmNo;
    alarmEn++;
    if (buttonState < alarmEn ) alarmNo = buttonState;
    else alarmNo = alarmEn;
    LCD.blink();
    LCD.setCursor(0, 0);
    LCD.print("Alarm " + String(alarmNo) + " :");
    for (int i = 0; i < 2; i++) {
      int digit[2], x;
      while (x != 2) {
        LCD.setCursor(i * 2 + x, 1);
        while (buttonState == -1)buttonState = readButton();
        if (buttonState == 10)return;
        else if (buttonState == 12) {
          digit[x] = buttonState;
          x++;
        }
        LCD.print(buttonState);
      }
      alarm[alarmNo][i] = digit[0] * 10 + digit[1];
    }
    LCD.setCursor(0, 0);
    LCD.print("Repeat ??");
    while (buttonState == -1)buttonState = readButton();
    while (true) {
      if (buttonState == 10) alarm[alarmNo][3] = 0;
      if (buttonState < 8 && buttonState != -1)
        bitWrite(alarm[alarmNo][3], buttonState - 1, buttonState);
      buttonState = readButton();
    }
  }
}
String Timer(int mode = 0) {

}

String Stopwatch(int mode = 0) {

}
