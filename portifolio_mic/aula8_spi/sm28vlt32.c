/*
 * sm28vlt32.c
 *
 * Created: 08/10/2026 10:34:46
 *  Author: kauanelb
 */ 

#include <xc.h>
#include "spi.h"

void SM28VLT32_config(){
		DDRC = (1<<DDC0);//Usando PCO como Slave Select (saída)
		PORTC |= (1<<PORTC0);//Slave select em nível alto
}

uint16_t SM28VLT32_readWord(uint32_t pAddress){
	uint8_t tAddressByte2 = (pAddress & 0x00FF0000) >> 16;
	uint8_t tAddressByte1 = (pAddress & 0x0000FF00) >> 8;
	uint8_t tAddressByte0 = (pAddress & 0x000000FF) >> 0;
	uint8_t tDataByte1;
	uint8_t tDataByte0;
	uint16_t tDataWord;

	PORTC &= ~(1<<PORTC0);//Slave select em nível baixo
	SPI_transceive(0x15); //Comando 'Read Word'
	SPI_transceive(tAddressByte2);
	SPI_transceive(tAddressByte1);
	SPI_transceive(tAddressByte0);
	tDataByte1 = SPI_transceive(0x00);
	tDataByte0 = SPI_transceive(0x00);
	SPI_transceive(0x00); //Dummy
	PORTC |= (1<<PORTC0);//Slave select em nível alto
	
	tDataWord = ((uint16_t) tDataByte1) << 8 // 0xAB
						|((uint16_t) tDataByte0) << 0; // 0xCD

	return tDataWord;
}