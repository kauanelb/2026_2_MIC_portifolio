/*
 * main.c
 *
 * Created: 10/22/2026 10:51:01 AM
 *  Author: kauanelb
 */ 

#include <xc.h>
#include "avr/interrupt.h"

//Obter uma interruoção com período de 10ms
ISR(TIMER0_COMPA_vect){															//Interrupção de comparação A do timer 0, toda vez que der 155 ele interrompe
	PORTB ^= (1<<PORTB0);														//Alterna PB0
}


void TMR0_config(){																//PG 86 configuração no modo CTC
	TCCR0A = (0<<WGM00)|(1<<WGM01);												//Definem modo de operação do timer
	TCCR0B = (0<<WGM02)|(1<<CS02)|(0<<CS01)|(1<<CS00);
	OCR0A = 155;																//Corresponde a 9,984ms
	TIMSK0 = (1<<OCIE0A);														//Habilita interrupção COMPA
}

int main(void)
{
	DDRB |= (1<<DDB0);															//PB0 como saída
	TMR0_config();
	sei();
    while(1)
    {
		
        //
    }
}