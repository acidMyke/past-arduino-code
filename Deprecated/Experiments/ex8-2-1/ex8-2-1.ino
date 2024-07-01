//========== ex8-2-1.ino ============
// pins 2~5 connected to P19D-3~P19D-6
// pin 6 connected to P19D-1, pin 7 connected to P19D-2
// pins A0~A3 connected to P5-1~P5-4
// pin A4 connected to P5-8
//========== Global Declaration ============
const int stepPin[4] = {2, 4, 3, 5}; // step motor pins connected to digital pins 2, 3, 4, 5
const int EN12 = 6; 	       // EN12 pin connected to digital pin 6
const int EN34 = 7; 	       // EN34 pin connected to digital pin 7
const int SW5_1 = A0; 	       // DIP switch SW5-1 connected to analog pin A0
const int SW5_2 = A1; 	       // DIP switch SW5-2 connected to analog pin A1
const int SW5_3 = A2; 	       // DIP switch SW5-3 connected to analog pin A2
const int dir = A3; 	       // DIP switch SW5-4 connected to analog pin A3
const int onOff = A4; 	       // DIP switch SW5-8 connected to analog pin A4
int i; 			       // declare integer variable named i
//========== initialization ============
void setup()
{ for (int i = 0; i < 4; i++)
  { pinMode(stepPin[i], OUTPUT); // configure digital pins 2-5 as outputs
    digitalWrite(stepPin[i], 0); // stop the step motor
  }
  pinMode(EN12, OUTPUT);	 // configure digital pin 6 as an output
  pinMode(EN34, OUTPUT);	 // configure digital pin 7 as an output
  digitalWrite(EN12, 0);	 // disable drivers 1 and 2
  digitalWrite(EN34, 0);	 // disable drivers 3 and 4
  pinMode(SW5_1, INPUT);	 // configure analog pin A0 as an input
  pinMode(SW5_2, INPUT);	 // configure analog pin A1 as an input
  pinMode(SW5_3, INPUT);	 // configure analog pin A2 as an input
  pinMode(dir, INPUT);	 // configure analog pin A3 as an input
  pinMode(onOff, INPUT);	 // configure analog pin A4 as an input
}
//========== Main Code ============
void loop()
{ int ON = digitalRead(onOff); 	// read DIP switch SW5-8 (onOff)
  if (!ON) 				// if SW5-8 is ON
  { digitalWrite(EN12, 1); 		// enable drivers 1 and 2
    digitalWrite(EN34, 1); 		// enable drivers 3 and 4
    int DIR = digitalRead(dir); 	// read SW5-4 (dir) state and store it in DIR
    int SW1 = digitalRead(SW5_1); 	// read SW5-1 state and store it in SW1
    int SW2 = digitalRead(SW5_2); 	// read SW5-2 state and store it in SW2
    int SW3 = digitalRead(SW5_3); 	// read SW5-3 state and store it in SW3
    if (!DIR) 				// if SW5-4 is ON, forward (CW)
    { if (!SW1 && SW2 && SW3)		// 1-phase-on scheme
      { digitalWrite(stepPin[i], 1);	// energize a single phase
        delay(50); 			// a delay of 50ms
        digitalWrite(stepPin[i], 0);	// de-energize a single phase
        if (++i >= 4)  i = 0;
      }
      else if (SW1 && !SW2 && SW3)			// 2-phase-on scheme
      { digitalWrite(stepPin[i], 1);			// energize two phases
        digitalWrite(stepPin[(i + 1) % 4], 1);
        delay(50); 					// a delay of 50ms
        digitalWrite(stepPin[i], 0);			// de-energize two phases
        digitalWrite(stepPin[(i + 1) % 4], 0);
        if (++i >= 4)  i = 0;
      }
      else if (SW1 && SW2 && !SW3)			// 1-2-phase-on scheme
      { if (i % 2 == 0)					// 1-phase-on operation
        { digitalWrite(stepPin[i / 2], 1);		// energize a single phase
          delay(50); 				// a delay of 50 ms
          digitalWrite(stepPin[i / 2], 0);		// de-energize a single phase
        }
        else					// 2-phase-on operation
        { digitalWrite(stepPin[i / 2], 1);		// energize two phases
          digitalWrite(stepPin[(i / 2 + 1) % 4], 1);
          delay(50); 				// a delay of 50 ms
          digitalWrite(stepPin[i / 2], 0);		// de-energize two phases
          digitalWrite(stepPin[(i / 2 + 1) % 4], 0);
        }
        if (++i >= 8)  i = 0;
      }
    }
    else
    { if (!SW1 && SW2 && SW3)			 // 1-phase-on scheme
      { digitalWrite(stepPin[3 - i], 1);	 // energize a single phase
        delay(50); 				  // a delay of 50 ms
        digitalWrite(stepPin[3 - i], 0);	 // de-energize a single phase
        if (++i >= 4)  i = 0;
      }
      else if (SW1 && !SW2 && SW3)		 // 2-phase-on scheme
      { digitalWrite(stepPin[3 - i], 1);	 // energize two phases
        digitalWrite(stepPin[(3 - i + 1) % 4], 1);
        delay(50); 				  // a delay of 50 ms
        digitalWrite(stepPin[3 - i], 0);	 // de-energize two phases
        digitalWrite(stepPin[(3 - i + 1) % 4], 0);
        if (++i >= 4)  i = 0;
      }
      else if (SW1 && SW2 && !SW3)		 // 1-2-phase-on scheme
      { if (i % 2 == 0)				 // 1-phase-on operation
        { digitalWrite(stepPin[3 - i / 2], 1);	 // energize a single phase
          delay(50); 			  // a delay of 50 ms
          digitalWrite(stepPin[3 - i / 2], 0);	 // de-energize a single phase
        }
        else				  // 2-phase-on operation
        { digitalWrite(stepPin[3 - i / 2], 1);	 // energize two phases
          digitalWrite(stepPin[(3 - i / 2 + 1) % 8], 1);
          delay(50); 			  // a delay of 50 ms
          digitalWrite(stepPin[3 - i / 2], 0);	 // de-energize two phases
          digitalWrite(stepPin[(3 - i / 2 + 1) % 8], 0);
        }
        if (++i >= 8)  i = 0;
      }
    }
    digitalWrite(EN12, 0); 		// disable drivers 1 and 2
    digitalWrite(EN34, 0); 		// disable drivers 3 and 4
  }
}

