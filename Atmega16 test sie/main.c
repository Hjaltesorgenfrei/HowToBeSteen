// Calculate the value needed for 
// the CTC match value in OCR1A.
#define CTC_MATCH_OVERFLOW (8000000 / 8) 
 
#include <avr/io.h>
#include <avr/interrupt.h>
ISR (TIMER1_COMPA_vect)
{
		PORTC ^= 0xFF;
}

int main(void)
{
    // CTC mode, Clock/8
    TCCR1B |= (1 << WGM12) | (1 << CS11);
    // Load the high byte, then the low byte
    // into the output compare
    OCR1A = 0xFFFF;
 
    // Enable the compare match interrupt
    TIMSK |= (1 << OCF1A);
    
	DDRC = 0xFF;
	DDRD = 0xFF;
	PORTD = 0xFF;
    // Now enable global interrupts
    sei();
	PORTC = 0xFF;
    while (1)
    {
    }
}