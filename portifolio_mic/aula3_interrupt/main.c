/*
 * main.c
 *
 * Created: 8/27/2026 10:25:15 AM
 *  Author: kauanelb
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

//configuração da interrupção externa (INT0/INT1)

ISR(INT0_vect) { //Função de interrupção
	PORTB |= (1<<PORTB1); //Acende led em PB1
	_delay_ms(50);
	PORTB &= ~(1<<PORTB1); //Apaga led em PB1
}

ISR(INT1_vect) { //Função de interrupção
	PORTB |= (1<<PORTB1); //Acende led em PB1
	_delay_ms(100);
	PORTB &= ~(1<<PORTB1); //Apaga led em PB1
}

void INT_config(){
	EICRA = (1<<ISC11)|(1<<ISC10)//PG 54 NO DATASHEET. Configura INT1 na borda de subida
			|(1<<ISC01)|(0<<ISC00);//Configura INT0 na borda de descida
	EIMSK = (1<<INT0)|(1<<INT1); //Habilita INT0 e INT1 pra funcionar
}

void GPIO_config(){
	DDRB |= (1<<DDB0); //Pino PB0 como saída
	DDRB |= (1<<DDB1); //Pino PB1 como saída
}

int main(void) {
	INT_config();
	GPIO_config();
	sei(); // Habilita interrupções globalmente
    while(1) {
		cli();//desabilita interrupções temporariamente
		PORTB |= (1<<PORTB0); //acende led no pino PB0
		_delay_ms(100);
		sei(); //habilita novamente
		PORTB &= ~(1<<PORTB0); //apaga led no pino PB0
		_delay_ms(100);
    }
}