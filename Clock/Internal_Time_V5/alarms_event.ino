void alarmEvent(){
  while(true){
    if(Serial.available()){
      String str = Serial.readString();
      str.toLowerCase();
      if(str == "snooze"){
        Serial.println("Snooze for 1.5 minutes");
        Alarm.timerOnce(90, alarmEvent);
        return;
      }
      if(str == "stop"){
        Serial.println("Alarm Stopped");
        return;
      }
    }
    Serial.println("Ringing!!!");
    delay(100);
  }
}

