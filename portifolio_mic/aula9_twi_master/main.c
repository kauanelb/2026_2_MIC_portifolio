/*
 * main.c
 *
 * Created: 10/15/2026 8:59:14 AM
 *  Author: kauanelb
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

void TWI_master_config(){
	TWBR = 64;												//Divisor 64, fscl = 100KHz, TWBR x TWPS = (F_CPU/2xFSCL) - 16
	TWSR |= (0<<TWPS0)|(0<<TWPS1);							//Prescaler de 1
	TWCR |= (1<<TWEN);										//Habilita o periférico
}

int main(void)
{
	TWI_master_config();
	_delay_ms(1000);
	uint8_t tSlaveAddress = 10;
    while(1)
    {
		//Iniciar transmissão como mestre
		TWCR |= (1<<TWSTA);									//Inicia condição de start
		while((TWCR & (1<<TWINT)) == 0);					//Aguarda flag de interrupção subir		
		uint8_t tStatusCode = (TWSR & 0b11111000);
		//condição de start ok?
		
		if(tStatusCode == 0x08){							//Condição de start ok
			//Iniciar escrita no escravo 10
			TWDR = (tSlaveAddress<<1)|0;					//Endereço + flag R/W leitura/escrita, 1 leitura, 0 escrita
			TWCR = (1<<TWINT)|(1<<TWEN);					//Limpar flag de interrupção
			while((TWCR & (1<<TWINT)) == 0);				//Aguarda conclusão da transmissão
			tStatusCode = (TWSR & 0b11111000);				//Novo código de estado
			if(tStatusCode == 0x18){
				//Ack recebido
			}else
			if(tStatusCode == 0x28){			
				//nack, ack não recebido, erro
			}else{
				//algum erro
			}
		}else{
			//algum erro
		}
		_delay_ms(100);
	}
}