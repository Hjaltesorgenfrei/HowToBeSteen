#include "debounce.h"
#include "interfacesetting.h"
#include "adc.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#define BIT(x) (1 << (x))
#define SETBITS(x,y) ((x) |= (y))
#define CLEARBITS(x,y) ((x) &= (~(y)))
#define SETBIT(x,y) SETBITS((x), (BIT((y))))
#define CLEARBIT(x,y) CLEARBITS((x), (BIT((y))))

//a:0,b:1,c:2,d:3,e:4,f:5,g:6
#define ZERO  0b01000000
#define ONE   0b01111001
#define TWO   0b00100100
#define THREE 0b00110000
#define FOUR  0b00011001
#define FIVE  0b00010010
#define SIX   0b00000011
#define SEVEN 0b01111000
#define EIGHT 0b00000000
#define NINE  0b00011000

static volatile uint16_t counter = 0;
volatile int inc = 20;

ISR(TIMER0_OVF_vect){
	debounce();
	PORTB |= (1 << PB7);
	adcValue = (uint32_t)adc_read(0) * 100 / 1024;
	PORTB &= ~(1 << PB7);
}


void timer_init(void){
	TCCR0 = (1<<CS00)|(1<<CS02); //1024 prescaler. Overflows about 30 times a second.
	TIFR = (1<<TOV0); //clear pending interrupts
	TIMSK  = (1<<TOIE0); //Enable timer 0 overflow
	sei();
}


void initialize(){
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRB = 0xF0;
	timer_init();
	debounce_init();
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	if (read_eeprom_word(0) < 101)
		humudityValue = read_eeprom_word(0);
	else humudityValue = 0;
	if (read_eeprom_word(1) < 2)
		lightValue = read_eeprom_word(1);
	else lightValue = 0;
	PORTD = 0b00000001;
}

int main (){
	initialize();

	while(1){
		switch (interfaceSetting) {
		case HUMIDITYSENSE:
			humuditySensing();
			break;
		case HUMIDITYSET:
			humuditySet();
			break;
		case LIGHTSETTING:
			lightSet();
			break;
		}
		if (button_down(BUTTON3_MASK) && interfaceSetting < 3)
			interfaceSetting++;
		else interfaceSetting = HUMIDITYSENSE;
		if (adcValue < humudityValue)
			PORTB |= (1 << PB5);
		else PORTB &= ~(1 << PB5);
		if (!(PORTB & (1<<PB6)) && lightValue)
			PORTB |= (1 << PB6);
		else PORTB &= ~(1 << PB6);
	}
}