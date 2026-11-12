/*
 * main.c
 *
 * Created: 11/12/2026 10:16:14 AM
 *  Author: kauanelb
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"


void ADC_config(){
	ADMUX = (0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0)					//Canal de conversão: pino ADC7, tabela 23.4
			|(1<<REFS1)|(1<<REFS0);									//Referência de tensão interna tabela 23.3
	ADCSRA = (1<<ADEN)|(0<<ADATE)									//Habilita o ADC em modo "manual"
			|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);						//Fator de prescale 128 (125KHz freq do ADC)		
	DIDR0 = (1<<ADC0D);												//Desabilita porta PCO (função digital do pino ADC0) 					
}

int main(void)
{
	DDRB |= (1<<DDB0);//Pino PB0 como saida (led)
	ADC_config();
	_delay_ms(1);
    while(1)
    {
		ADCSRA |= (1<<ADSC);//Inicia uma conversão
		while((ADCSRA & (1<<ADSC)) != 0);
        uint16_t tADCData = ADC;//Acesso a ADCH e ADCL como um único registrados de 16 bits, faixa de inteiros de 0 a 1023 (ADCLAR=0)
		if(tADCData < 670){
			PORTB |= (1<<PORTB0);//Acender led abaixo de 720mV
		} else {
			PORTB &= ~(1<<PORTB0);//Apagar led caso contrário
		}
    }
}