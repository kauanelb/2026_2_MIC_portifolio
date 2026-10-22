/*
 * main.c
 *
 * Created: 10/22/2026 8:20:54 AM
 *  Author: kauanelb
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

ISR(TWI_vect){												//Vetor de interrupção
	//Tratar o estado atual da máquina do TWI
	PORTB |= (PORTB0);
	uint8_t tStatusCode = (TWSR & 0b11111000);

	switch(tStatusCode){
		case (0x60) : {										//Recebido SLA+W, início de escrita do mestre
			PORTB |= (PORTB1);
			TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA);					//Envio do ACK
		}break;
		
		case (0x80) : {										
			PORTB |= (PORTB2);
			uint8_t tReceivedByte = TWDR;					//Recebe o dado enviado pelo mestre
			TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA);					//Envio do ACK
		}break;
		
		case (0xA0) : {										//Final da transmissão (stop condition ou repeat start)
			PORTB |= (PORTB3);
			
		}break;
		default : {
			PORTB |= (PORTB4);
			//Algum erro ou condição não tratada
			TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT);		
		}
	}
	_delay_ms(1);
	PORTB = 0;
}

void TWI_slave_config(uint8_t pAddress){
	TWBR = 64;												//Divisor 64, fscl = 100KHz, TWBR x TWPS = (F_CPU/2xFSCL) - 16
	TWSR |= (0<<TWPS0)|(0<<TWPS1);							//Prescaler de 1
	TWCR |= (1<<TWEN)|(1<<TWIE);							//Habilita o periférico e a interrupção
	TWAR = pAddress<<1;
	TWCR = (1<<TWINT);
}



int main(void)
{
	DDRB |= (1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)|(1<<DDB4);		//leds
	TWI_slave_config(10);
	sei();
    while(1)
    {
		
		
		
    }
}