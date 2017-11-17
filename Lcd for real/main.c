#include "hd44780.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void initialize(){
	DDRC = 0xFF;
	sei();
	//starts the timer.
	OCR1A = 62500; //should be 5 miliseconds
	TCCR1B |= (1 << WGM12);
    // Mode 4, CTC on OCR1A
    TIMSK |= (1 << OCIE1A);//Set interrupt on compare match
    TCCR1B |= (1 << CS11) | (1 << CS10);
    // set prescaler to 64 and start the timer
	hd44780_clear_screen(); 
}

ISR (TIMER1_COMPA_vect)
{
	hd44780_timer_isr();
}

int main (){
	initialize();
	while(1){
		hd44780_write_string("Hello World!", 1, 1, NO_CR_LF);
	}
}