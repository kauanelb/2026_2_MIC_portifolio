/*
 * main.c
 *
 * Created: 10/29/2026 8:53:58 AM
 *  Author: kauanelb
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

void PWM_config(){
	TCCR0A = (0<<COM0A0)|(1<<COM0A1)														//Saída OCR0A Não-inversora pg 84 table 14.3
			|(1<<COM0B0)|(1<<COM0B1)														//Saída OCR0B inversora
			|(1<<WGM00)|(1<<WGM01);															//modo Fast PWM
	TCCR0B = (0<<WGM02)|(0<<CS02)|(0<<CS01)|(1<<CS00);										//Habilita timer com prescaler de 1x
	OCR0A = 163;																			//Razão de ciclo de 40% da contagem de 255 em OC0A
	OCR0B = 76;																				//Razão de ciclo de 30% da contagem de 255 em OC0B
	DDRD = (1<<DDD6)|(1<<DDD5);																//Configura pino PD6 e PD5 como saída
}

void PWM_setVoltageA(uint16_t pMillivolts){
	if(pMillivolts == 0){
		//Proteção contra parâmetros fora da faixa útil
		OCR0A = 0;
	} else
	if(pMillivolts >= 5000){
		OCR0A = 0xff;
	}
	else{
		//Ver cast estático em linguagem C
		OCR0A = (uint8_t)(0x000000FF & (((uint32_t) pMillivolts * 256) / 5000));
	}
}
	

int main(void)
{
	PWM_config();
	PWM_setVoltageA(2500);
    while(1)
    {
		PWM_setVoltageA(2500); //Fase 0º
		_delay_ms(1);
		PWM_setVoltageA(3750); //Fase 30º
		_delay_ms(1);
		PWM_setVoltageA(4665); //Fase 60º
		_delay_ms(1);
		PWM_setVoltageA(5000); //Fase 90º
		_delay_ms(1);
		PWM_setVoltageA(4665); //Fase 120º
		_delay_ms(1);
		PWM_setVoltageA(3750); //Fase 150º
		_delay_ms(1);
		PWM_setVoltageA(2500); //Fase 180º
		_delay_ms(1);
		PWM_setVoltageA(1250); 
		_delay_ms(1);
		PWM_setVoltageA(335);
		_delay_ms(1);
		PWM_setVoltageA(0);
		_delay_ms(1);
		PWM_setVoltageA(335);
		_delay_ms(1);
		PWM_setVoltageA(1250);
		_delay_ms(1);
    }
}