#include "interfacesetting.h"
#include "adc.h"
#include "debounce.h"



volatile int outputNumber[10] = { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE };

volatile int interfaceSetting = 0;

void humuditySensing()
{
	switch (PORTD) {
	case 0b00001000:
		PORTD = 0b00000001;
		PORTC = 0b11111111;
		PORTC = H;
		break;
	case 0b00000001:
		PORTD = 0b00000010;
		PORTC = 0b11111111;
		PORTC = outputNumber[1];
		break;
	case 0b00000010:
		PORTD = 0b00000100;
		PORTC = 0b11111111;
		PORTC = outputNumber[(adcValue / 10) % 10];
		break;
	case 0b00000100:
		PORTD = 0b00001000;
		PORTC = 0b11111111;
		PORTC = outputNumber[adcValue % 10];
		break;
	}
	if (button_down(BUTTON1_MASK)) {
		interfaceSetting = HUMIDITYSET;
	}
	if (button_down(BUTTON2_MASK)) {
		interfaceSetting = HUMIDITYSET;
	}
}

void humuditySet()
{
	switch (PORTD) {
	case 0b00001000:
		PORTD = 0b00000001;
		PORTC = 0b11111111;
		PORTC = H;
		break;
	case 0b00000001:
		PORTD = 0b00000010;
		PORTC = 0b11111111;
		PORTC = outputNumber[2];
		break;
	case 0b00000010:
		PORTD = 0b00000100;
		PORTC = 0b11111111;
		PORTC = outputNumber[(humudityValue / 10) % 10];
		break;
	case 0b00000100:
		PORTD = 0b00001000;
		PORTC = 0b11111111;
		PORTC = outputNumber[humudityValue % 10];
		break;
	}
	if (button_down(BUTTON1_MASK)) {
		humudityValue++;
		write_eeprom_word(humudityValue, 0);
	}
	if (button_down(BUTTON2_MASK) && humudityValue > 0) {
		humudityValue--;
		write_eeprom_word(humudityValue, 0);
	}
}

void lightSet()
{
	switch (PORTD) {
	case 0b00001000:
		PORTD = 0b00000001;
		PORTC = 0b11111111;
		PORTC = L;
		break;
	case 0b00000001:
		PORTD = 0b00000010;
		PORTC = 0b11111111;
		PORTC = outputNumber[1];
		break;
	case 0b00000010:
		PORTD = 0b00000100;
		PORTC = 0b11111111;
		PORTC = outputNumber[0];
		break;
	case 0b00000100:
		PORTD = 0b00001000;
		PORTC = 0b11111111;
		PORTC = outputNumber[lightValue % 10];
		break;
	}
	if (button_down(BUTTON1_MASK) && lightValue == 0) {
		lightValue = 1;
		write_eeprom_word(lightValue, 1);
	}
	if (button_down(BUTTON2_MASK) && lightValue == 1) {
		lightValue = 0;
		write_eeprom_word(lightValue, 1);
	}
}
