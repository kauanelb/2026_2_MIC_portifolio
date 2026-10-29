/*
 * main.c
 *
 * Created: 10/29/2026 8:53:58 AM
 *  Author: kauanelb
 */ 

#include <xc.h>

void PWM_config(){
	TCCR0A = (0<<COM0A0)|(1<<COM0A1)														//Saída OCR0A Não-inversora pg 84 table 14.3
			|(1<<COM0B0)|(1<<COM0B1)														//Saída OCR0B inversora
			|(1<<WGM00)|(1<<WGM01);															//modo Fast PWM
	TCCR0B = (0<<WGM02)|(0<<CS02)|(0<<CS01)|(1<<CS00);										//Habilita timer com prescaler de 1x
	OCR0A = 101;																			//Razão de ciclo de 40% da contagem de 255 em OC0A
	OCR0B = 76;																				//Razão de ciclo de 30% da contagem de 255 em OC0B

	DDRD = (1<<DDD6)|(1<<DDD5);																//Configura pino PD6 e PD5 como saída
}

int main(void)
{
	PWM_config();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}