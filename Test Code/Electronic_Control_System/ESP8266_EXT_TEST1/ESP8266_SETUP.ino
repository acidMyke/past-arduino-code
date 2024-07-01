int ESP_Setup() {
  if (sendCheck("AT", "OK", 5000)) Serial.println("ESP CHECK OK");
  else return -1;
  if (sendCheck("AT+RST", "Ready", 7000)) Serial.println("ESP RESET OK");
  else return -2;
  if (sendCheck("AT+CWMODE=1", "OK", 1000)) Serial.println("ESP CWMODE SET");
  else return -3;
  if (sendCheck("AT+CWJAP\"" + SSID + "\",\"" + PASS + "\"", "OK", 10000)) Serial.println("ESP SSID SET OK");
  else return -4;
  if (sendCheck("AT+CIFSR\r\n", "", 10000)) Serial.println("IP Address: " + reply);
  else return -5;
  if (sendCheck("AT+CIPMUX=1", "OK", 1000)) Serial.println("ESP CIPMUX SET");
  else return -6;
  return 1;
}


boolean sendCheck(String send, String param, uint32_t timeout) {
  reply = "";
  ESP.println(send);
  int Millis = millis() + timeout; // 5 Seconds Timeout
  while (!ESP.available())
    if (Millis > millis()) delay(1); // wait for ESP to reply with 5 seconds timeout
    else return 0;
  if (ESP.available())
    if (param != NULL)
      if (ESP.readString().equalsIgnoreCase(param)) return 1;
      else return 0;
    else reply = ESP.readString();
  else return 0;
}

