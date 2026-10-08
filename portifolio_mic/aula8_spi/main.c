/*
 * main.c
 *
 * Created: 10/8/2026 8:49:57 AM
 *  Author: kauanelb
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

void SPI_master_config(){//cap 18.5 pg 141
	SPCR = (1<<SPE) //Habilita SPI
		  |(0<<DORD) //Ordem MSB primeiro (padrão)
		  |(1<<MSTR) //Modo mestre, gera o clock
		  |(0<<CPOL)|(0<<CPHA)//SPI no modo 0
		  |(0<<SPR1)|(0<<SPR0);//Combina com o SPSR pra ver a frequência de clock, divisor fosc/2, SCK->8MHz
	SPSR = (1<<SPI2X);
	DDRB = (1<<DDB3)|(1<<DDB5);
}

int main(void)
{
	SPI_master_config();
    while(1)
    {
		SPDR = 0xC7;
		_delay_ms(1);
    }
}