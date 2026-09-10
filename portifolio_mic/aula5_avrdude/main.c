/*
 * main.c
 *
 * Created: 9/10/2026 8:18:46 AM
 *  Author: kauanelb
 */ 

# define F_CPU 16000000
# include <xc.h>
# include "util/delay.h"

void GPIO_incBar () {
	PORTD = PORTD >> 1;
	PORTD |= 0b10000000 ;
}

void GPIO_decBar () {
	PORTD = PORTD << 1;
}

void GPIO_config () {
	DDRD = 0xFF ; // pinos usados pelos LEDs como saida
	PORTD = 0x00 ; // parte com a barra apagada
}

int main ( void ) {
	GPIO_config () ;
	while (1) {
		for ( uint8_t i = 0; i < 8; i ++) { GPIO_incBar () ; _delay_ms (200) ; }
		for ( uint8_t i = 0; i < 8; i ++) { GPIO_decBar () ; _delay_ms (200) ; }
	}
}