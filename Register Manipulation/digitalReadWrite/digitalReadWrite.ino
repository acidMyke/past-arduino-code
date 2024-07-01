void setup() {
	DDRB |= 1 << PB6; // Set LED at pin 13 as Output
	DDRD &= ~(1 << PD2); //Set Swicth at pin 2 as Input
	PORTD |= 1 << PD2; //Set Switch at pin 2 with pull-up
}

void loop() {
	PORTB &= ~(1 << PB6); //Clear PB6
	PORTB |= (PIND & (1 << PD2)) << (PB6 - PD2); // Set PB6 to be the value of PD2
	PORTB = ((PORTB & ~(1 << PB6)) | (((PIND & (1 << PD2)) >> PD2) << PB6)); 
}