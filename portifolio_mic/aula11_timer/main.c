/*
 * main.c
 *
 * Created: 10/22/2026 10:51:01 AM
 *  Author: kauanelb
 */ 

#include <xc.h>
#include "avr/interrupt.h"

uint16_t gMilliSeconds = 0;
uint8_t gClockSeconds = 0;
uint8_t gClockMinutes = 0;
uint8_t gClockHours = 0;

//Obter uma interruoção com período de 10ms
ISR(TIMER0_COMPA_vect){															//Interrupção de comparação A do timer 0, toda vez que der 155 ele interrompe
	gMilliSeconds += 10;
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
		//Led blinck não bloqueante
		if(gMilliSeconds < 100){
			PORTB |= (1<<PORTB0);												//Seta PB0 por 100ms
		}else{
			PORTB &= ~(1<<PORTB0);												//zera PB0 por 900ms
		}
		
		//Lógica do RTC (Real Time Clock)
        if(gMilliSeconds >= 1000){
	        gMilliSeconds -= 1000;
	        gClockSeconds++;
	        if(gClockSeconds >= 60){
		        gClockSeconds = 0;
		        gClockMinutes++;
		        if(gClockMinutes >= 60){
			        gClockMinutes = 0;
			        gClockHours++;
			        if(gClockHours >= 24){
				        gClockHours = 0;
			        }
		        }
	        }
        }
    }
}