void alarmEvent() {
  while (true) {
    if (Serial.available()) {
      String str = Serial.readString();
      str.toLowerCase();
      if (str == "snooze") {
        display("Snooze for 5 minutes");
        Alarm.timerOnce(300, alarmEvent);
        return;
      }
      if (str == "stop") {
        display("Alarm Stopped");
        return;
      }
    }
    if (readKeypad() > -1 && readKeypad(2) != 10) {
      display("Snooze for 5 minutes");
      Alarm.timerOnce(300, alarmEvent);
      break;
    }
    if (readKeypad(2) == 10) {
      display("Alarm Stopped");
    }
    display("Ringing!!!");
    delay(100);
  }
}

void alarm() {
  time_t newAlarm = compileTimeDate(1);
  byte repeat = 0x00;
  display("Rep(#)/Once(*)");
  if (readKeypad(1) == 12) repeat = 0x01;
  while (true) {
    if (readKeypad(1) == 10 || readKeypad(2) == 12) break;
    if (0 < readKeypad(2) < 8) bitWrite(repeat, readKeypad(2), !bitRead(repeat, readKeypad(2)));
    display("Rep/Once:\n" + String(repeat, BIN));
  }
  if (repeat == 0x00) Alarm.alarmOnce(newAlarm, alarmEvent);
  else if (repeat == 0xFF) Alarm.alarmRepeat(newAlarm, alarmEvent);
  else {
    for (int i = 1; i < 8; i++) {
      if (bitRead(repeat, i)) {
        int x = 0;
        if (i == 7) x = 0;
        else x = i + 1;
        if (bitRead(repeat, 0)) Alarm.alarmOnce(x, newAlarm, alarmEvent);
        else Alarm.alarmRepeat(x, newAlarm, alarmEvent);
      }
    }
  }
}
