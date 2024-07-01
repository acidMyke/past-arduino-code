void setup() {
	DDRB |= 1 << PB6;
	ADMUX = 3 << ADLAR; // Reference voltage as AVcc //Left Adjust Data // ADC0 = A0
	ADCSRA &= ~(1 << ADEN); //Enable ADC
}

void loop() {
	ADCSRA &= ~(1 << ADSC);
	while ((ADCSRA & 1 << ADSC) > 0);
	if (ADCH > 128) PORTB |= 1 << PB6; // 
	else PORTB &= ~(1 << PB6);
}
