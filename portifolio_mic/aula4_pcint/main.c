/*
 * main.c
 *
 * Created: 9/3/2026 8:56:32 AM
 *  Author: kauanelb
 */ 

#define F_CPU 16000000
#include <xc.h>
#include <stdint.h>
#include "avr/interrupt.h"
#include "util/delay.h"

#define KEY_RELEASED 0
#define KEY_PRESSED 1

uint8_t gKeyState_w = 0;
uint8_t gKeyState_a = 0;
uint8_t gKeyState_s = 0;
uint8_t gKeyState_d = 0;

void GPIO_config(){
	DDRB &= ~((1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)); //zera o valor dos pinos com shift a esquerda fica: b7 b6 b5 b4 0 0 0 0, ele mantem os valores dos 4 primeiros bits e zera os bits que vamos usar, PB0, PB1, PB2, PB3 como entrada
	PORTB |= (1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3); //Habilita pull up nos pinos PB0, PB1, PB2, PB3
	//DDRD = 0xff; //seta todo mundo como saída na porta D, 0b11111111, PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7 como saídas
	DDRD |= (1<<DDD0)|(1<<DDD1)|(1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7); //faz a mesma coisa, seta todo mundo na porta D como saída.
	DDRC |= (1<<DDC0); //Pino PC0 como saída
}

void GPIO_incBar(){
	PORTD = PORTD >> 1; //Escorrega pra baixo e insere 1 
	PORTD |= 0b10000000; // Aciona bit mais significativo
}

void PCINT_config(){
	PCICR |= (1<<PCIE0); // Habilita grupo PCINT0 a PCINT7, pg 56 do datasheet
	PCMSK0 |= (1<<PCINT0)|(1<<PCINT1)|(1<<PCINT2)|(1<<PCINT3); // Habilita interrupção PCINT0 a PCINT3
}

ISR(PCINT0_vect){
	uint8_t tCurrentKeyState_w = 0;
	if((PINB & (1<<PINB0)) != 0){ //PORT é para escrita, PIN é para leitura. Testa pino PB0,
		tCurrentKeyState_w = KEY_RELEASED; //PB0 = 1, chave/tecla w aberta
	} else {
		tCurrentKeyState_w = KEY_PRESSED; //PB0 = 0, chave/tecla w pressionada
	}
	
	if(tCurrentKeyState_w == KEY_PRESSED && gKeyState_w == KEY_RELEASED){
		//Tecla w acabou de ser pressionada
		//gKeyState_w = KEY_PRESSED; // Agora coloca a tecla como pressionada
		GPIO_incBar(); // Cada vez que o evento disparar vai incrementar a barra
	} else
	if(tCurrentKeyState_w == KEY_RELEASED && gKeyState_w == KEY_PRESSED){
		//Tecla w acabou de ser solta
		//gKeyState_w = KEY_RELEASED; // Agora coloca a tecla como solta/aberta
	}
	gKeyState_w = tCurrentKeyState_w;
	
	PORTC ^= (1<<PORTC0); //Seta pino PC0
	//_delay_ms(100);
	//PORTC &= ~(1<<PORTC0); //Zera pino PC0
}

int main(void){
	GPIO_config();
	PCINT_config();
	sei();
    while(1){

    }
}