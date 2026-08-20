/*
 * main.c
 *
 * Created: 8/20/2026 8:58:55 AM
 *  Author: kauanelb
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

int main(void){
	DDRB |= 0b00100000; //define pino PB5 como saída
    while(1){
		PORTB |= 0b00100000; //Atribui nível lógico alto ao pino PB5
        _delay_ms(100);
		PORTB &= 0b11011111; //Atribui nível lógico baixo ao pino PB5
		_delay_ms(900);
    }
}