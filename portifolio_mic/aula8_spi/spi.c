/*
 * spi.c
 *
 * Created: 08/10/2026 10:33:26
 *  Author: kauanelb
 */ 

#include <xc.h>

void SPI_master_config(){//cap 18.5 pg 141
	SPCR = (1<<SPE) //Habilita SPI
	|(0<<DORD) //Ordem MSB primeiro (padrão)
	|(1<<MSTR) //Modo mestre, gera o clock
	|(0<<CPOL)|(0<<CPHA)//SPI no modo 0
	|(0<<SPR1)|(0<<SPR0);//Combina com o SPSR pra ver a frequência de clock, divisor fosc/2, SCK->8MHz
	SPSR = (1<<SPI2X);
	DDRB = (1<<DDB3)|(1<<DDB5);//Config dos pinos MOSI e SCK como saídas
}

uint8_t SPI_transceive(uint8_t pTxByte){
	uint8_t tReceivedByte;
	SPDR = pTxByte;//Escrita no SPDR dispara a transação
	while((SPSR & (1<<SPIF)) == 0);//Espera a flag SPIF subir
	tReceivedByte = SPDR;//Byte armazenado na variável, leitura do registrador de dados
	return tReceivedByte;
}