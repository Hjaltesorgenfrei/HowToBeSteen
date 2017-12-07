#ifndef INTERFACESETTING_H
#define INTERFACESETTING_H
#include <avr/eeprom.h>
#include <avr/io.h>
#define read_eeprom_word(address) eeprom_read_word ((const uint16_t*)address)
#define write_eeprom_word(address,value) eeprom_write_word ((uint16_t*)address,(uint16_t)value)
#define update_eeprom_word(address,value) eeprom_update_word ((uint16_t*)address,(uint16_t)value)

//Fugt måling, fugt sæt, tænd lys
#define HUMIDITYSENSE 0
#define HUMIDITYSET   1
#define LIGHTSETTING  2

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

#define H	  0b00001001
#define L	  0b01000111

volatile int outputNumber[10];
volatile uint16_t humudityValue;
volatile uint16_t lightValue;
volatile int interfaceSetting;
void humuditySensing();

void humuditySet();

void lightSet();

#endif