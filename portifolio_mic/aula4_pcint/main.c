/*
 * main.c
 *
 * Created: 9/3/2026 8:56:32 AM
 *  Author: kauanelb
 */ 

#include <xc.h>
#include "avr/interrupt.h"

ISR(PCINT0_vect){
	
}

void GPIO_config(){
	DDRB &= ~((1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)); //zera o valor dos pinos com shift a esquerda fica: b7 b6 b5 b4 0 0 0 0, ele mantem os valores dos 4 primeiros bits e zera os bits que vamos usar, PB0, PB1, PB2, PB3 como entrada
	DDRD = 0xff; //seta todo mundo como saída, 0b11111111, PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7 como saídas
	// DDRD |= (1<<DDD0)|(1<<DDD1)|(1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7); faz a mesma coisa, seta todo mundo como saída.
}

void PCINT_config(){
	
}

int main(void){
    while(1){

    }
}