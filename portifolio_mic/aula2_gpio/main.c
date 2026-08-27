/*
 * main.c
 *
 * Created: 8/27/2026 8:25:00 AM
 *  Author: kauanelb
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

#define BIT0_MASK 0b00000001
#define BIT1_MASK 0b00000010
#define BIT2_MASK 0b00000100
#define BIT5_MASK 0b00100000


int main(void) {
	DDRB = (1<<DDB5); // VIRA 100000 ADICIONA 5 ZEROS A ESQUERDA
	// DDRB = 0b00100000; da na mesma
	DDRB = 0b00100000 | 0b00000100; // deixa os dois bits setados no final = 0b00100100
	// DDRB = BIT5_MASK | BIT2_MASK; da na mesma
	
    while(1) {
        //TODO:: Please write your application code 
    }
}