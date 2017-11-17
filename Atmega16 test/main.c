#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define DF_CPU 8000000

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

volatile int outputNumber[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
volatile uint16_t counter = 5423;
void initialize(){
	DDRC = 0xFF;
	DDRD = 0xFF;
}

int main (){
	initialize();
	PORTD = 0b00000001;
	int counter2 = 0;
	while(1){
			switch(PORTD){
		case 0b00001000:
			PORTD = 0b00000001;
			PORTC = 0b11111111;
			PORTC = outputNumber[(counter/1000)%10];
			break;
		case 0b00000001:
			PORTD = 0b00000010;
			PORTC = 0b11111111;
			PORTC = outputNumber[(counter/100)%10];
			break;
		case 0b00000010:
			PORTD = 0b00000100;
			PORTC = 0b11111111;
			PORTC = outputNumber[(counter/10)%10];
			break;
		case 0b00000100:
			PORTD = 0b00001000;
			PORTC = 0b11111111;
			PORTC = outputNumber[counter%10];
			break;
		}
	_delay_ms(2);
	if (counter2 == 50){
	counter--;
	counter2 = 0;
	}
	counter2++;
	}
}