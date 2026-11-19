/*
 * main.c
 *
 * Created: 11/19/2026 8:33:41 AM
 *  Author: kauanelb
 */ 

#include <xc.h>
#include "avr/interrupt.h"

ISR(TIMER1_COMPB_vect){
	PORTB ^= (1<<PORTB1);			//Debug: para visualizar o tempo do TMR1
}

ISR(ADC_vect){//Interrupção referente a conversão concluida
	uint16_t tADCData = ADC;//Acesso a ADCH e ADCL como um único registrados de 16 bits, faixa de inteiros de 0 a 1023 (ADCLAR=0)
	if(tADCData < 670){
		PORTB ^= (1<<PORTB0);//Acender led abaixo de 720mV
		} else {
		PORTB &= ~(1<<PORTB0);//Apagar led caso contrário
	}
}

void ADC_config(){
	ADMUX = (0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0)					//Canal de conversão: pino ADC7, tabela 23.4
			|(1<<REFS1)|(1<<REFS0);									//Referência de tensão interna tabela (1.1V)23.3
	ADCSRA = (1<<ADEN)|(1<<ADATE)									//Habilita o ADC em modo "auto trigger"
			|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)						//Fator de prescale 128 (125KHz freq do ADC) pg 208
			|(1<<ADIE);												//Habilita interrupção no AD
	DIDR0 = (1<<ADC0D);												//Desabilita porta PCO (função digital do pino ADC0)
	ADCSRB = (1<<ADTS2)|(0<<ADTS1)|(1<<ADTS0);						//Fonte do disparo: TMR1 Compare match B, Tab 23.6 pg 220
}

void TMR1_config(){//Configurar timer 1 para disparo a cada 1ms, cap 15
	TCCR1A = (0<<WGM11)|(0<<WGM10);				//tabela 15.5
	TCCR1B = (0<<WGM13)|(1<<WGM12)				//Modo 4: CTC com topo em OCR1A
			|(0<<CS12)|(0<<CS11)|(1<<CS10);		//Prescaler unitário
	OCR1A = 15999;								//Período de 1ms
	OCR1B = 0;
	TIMSK1 = (1<<OCIE1B);						//Debug: habilita interrupção compare match B
}

int main(void)
{
	DDRB = (1<<DDB0)|(1<<DDB1);		//Pinos PB0 e PB1 como saída
	TMR1_config();
	ADC_config();
	sei();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}