unsigned long OldTime = millis(); // store the begining clock time into OldTime

int count=0; // declare a variable named Second as zero.

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Set Serial monitor Baud rate to 9600.
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(count); // Print value of Second on monitor every new line.
  count++;  // Increase Second by 1.
  delay(100); // Delay 0.1 Second.
  if(millis() - OldTime >1000) // Check if it reached 1 second.
  {
      Serial.println("1 Second"); // Print 1 Second on monitor.
      OldTime = millis(); // Restart the timing.
      count =0;
  }
}