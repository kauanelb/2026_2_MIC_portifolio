/*
 * main.c
 *
 * Created: 9/24/2026 10:20:40 AM
 *  Author: kauanelb
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"
#include "avr/interrupt.h"
#define RX_BUFFER_SIZE 16

uint8_t gMessage[RX_BUFFER_SIZE]; //buffer global da UART, vazio
uint16_t gRxCounter = 0; //contagem de bytes recebidos
uint8_t gMessageReady = 0; 

void UART_config_rx(uint16_t pBAUD){ 
	UCSR0A = (0<<U2X0);							//Modo "double speed" desativado, tem relação com o ubrr0
	UCSR0B = (1<<RXEN0)|(0<<TXEN0)|(0<<UCSZ02) //1 - Habilita o receptor. 2 - Desabilita o transmissor UART0. 3 - pg 162, configurar o tamanho do frame, falar quantos bits vão ser enviados tabela 19.7
			|(1<<RXCIE0); 	//Habilita a interrupção de recepção da UART0 pg 160 19.10.3
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

ISR(USART_RX_vect){//Interrupção cap 11, pg 49, interrupção 19
	uint8_t tReceiveByte = UDR0; // 19.10.1 flag de I/O, leitura do buffer UART
	gMessage[gRxCounter] = tReceiveByte; //Armazena bytes recebidos no buffer
	gRxCounter++;
	if(gRxCounter == RX_BUFFER_SIZE){
		 gRxCounter = 0; //Proteção contra estouro do buffer
	}
	if(tReceiveByte == '/n'){
		gMessageReady = 1; //Flag de mensagem completa
	}
}

int main(void)
{
	GPIO_config();
	UART_config_rx(9600);
	sei();//Habilita interrupções globalmente
    while(1)
    {
		if(gMessageReady){ //Aguarda mensagem completa
			gMessageReady = 0;
			//Tratamento da mensagem recebida
			if(strcmp(gMessageReady, "Message") == 0){//string compare, compara as duas strings, se são identicas retorna 0
				PORTC |= (1<<PORTC0); //Led verde
				} else{
				PORTC |= (1<<PORTC1); //Led vermelho
			}
			_delay_ms(10);
			PORTC = 0; //Apaga todos os leds
		}
    }
}