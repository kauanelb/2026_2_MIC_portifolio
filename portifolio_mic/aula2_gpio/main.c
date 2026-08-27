/*
 * main.c
 *
 * Created: 8/27/2026 8:25:00 AM
 *  Author: kauanelb
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "stdint.h"
#include "util/delay.h"

//controle de leds com a operação shift 

void GPIO_config(){
		DDRB = (1<<DDB6)|(1<<DDB4)|(1<<DDB2)|(1<<DDB0); //bits pares são configurados
}

int main(void) {
	GPIO_config();
	uint8_t tData = 0x03;  // 0b0000 0011
    while(1) {
		PORTB = tData;
		_delay_ms(1000);
		tData = tData << 1; // 0b0000 0110, 0b0000 1100; infinitamente pq ta dentro do while
		if(tData == 0){
			tData = 0x03;
		}
	}
}