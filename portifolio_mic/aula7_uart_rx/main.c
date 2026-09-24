/*
 * main.c
 *
 * Created: 9/24/2026 10:20:40 AM
 *  Author: kauanelb
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

void UART_config_rx(uint16_t pBAUD){ 
	UCSR0A = (0<<U2X0);							//Modo "double speed" desativado, tem relação com o ubrr0
	UCSR0B = (1<<RXEN0)|(0<<TXEN0)|(0<<UCSZ02); //1 - Habilita o receptor. 2 - Desabilita o transmissor UART0. 3 - pg 162, configurar o tamanho do frame, falar quantos bits vão ser enviados tabela 19.7
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)          //Modo assíncrono pg 161 tabela 19.4
			|(1<<UPM01)|(0<<UPM00)              //Tabela 19.5 pg 162, paridade par
			|(1<<USBS0)                         //2 bits de stop
			|(1<<UCSZ01)|(1<<UCSZ00)            //3 - Ainda sobre a tabela 19.7, configura o tamanho do frame pra 8 bits
			|(0<<UCPOL0);                       //Polaridade de clock ignorada
	UBRR0 = (1000000 / pBAUD) - 1; //tabela 19.1
}

void GPIO_config(){
	DDRC = (1<<DDC0)|(1<<DDC1);// Porta PC0 e PC1 como saída
}

int main(void)
{
	GPIO_config();
	UART_config_rx(9600);
    while(1)
    {
		//19.10.2 bit 7 RXCn
		while((UCSR0A & (1<<RXC0)) == 0); // Semáforo na flag de recebimento da UART, enquanto nao tiver nada pra ler ele fica esperando
		uint8_t tReceiveByte = UDR0; // 19.10.1 flag de I/O, leitura do buffer UART
		//Tratamento da mensagem recebida
		if(tReceiveByte == 'M'){
			PORTC |= (1<<PORTC0); //Led verde
		} else{
			PORTC |= (1<<PORTC1); //Led vermelho
		}
		_delay_ms(1);
		PORTC = 0; //Apaga todos os leds
    }
}