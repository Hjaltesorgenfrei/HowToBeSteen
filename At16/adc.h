#ifndef ADC_H
#define ADC_H
#include <avr/io.h>

//Fugt måling, fugt sæt, tænd lys
volatile int adcValue;
uint16_t adc_read(uint8_t ch);

#endif