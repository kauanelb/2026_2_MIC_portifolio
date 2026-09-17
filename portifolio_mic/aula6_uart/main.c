/*
 * main.c
 *
 * Created: 9/17/2026 10:15:14 AM
 *  Author: kauanelb
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

void UART_config(){ //Configuração do módulo do USRT0 para modo assíncrono, frame de 8 bits, paridade par, BAUD de 9600
	UCSR0A = (0<<U2X0);							//Modo "double speed" desativado, tem relação com o ubrr0
	UCSR0B = (0<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02); //1 - Desabilita o receptor. 2 - Habilita o transmissor UART0. 3 - pg 162, configurar o tamanho do frame, falar quantos bits vão ser enviados tabela 19.7
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)          //Modo assíncrono pg 161 tabela 19.4
			|(1<<UPM01)|(0<<UPM00)              //Tabela 19.5 pg 162, paridade par
			|(0<<USBS0)                         //1 bit de stop
			|(1<<UCSZ01)|(1<<UCSZ00)            //3 - Ainda sobre a tabela 19.7, configura o tamanho do frame pra 8 bits  
			|(0<<UCPOL0);                       //Polaridade de clock ignorada
	UBRR0 = 103; //BAUD de 9600 seria se fosse 103,16..., sendo 103, fica 9615... erro de 0,16%
				//9600 bits por segundo, frequencia, tem 8 bits dos dados, o start, o stop, e a paridade, total de 11 bits, logo pra mandar um byte ele demora 11/9600 = 1,14ms
}

void UART_send(){ //Envia um byte na USART0
	//UDR0 = 0x5A; Envia um byte, em hexa 0x5A, em binário 01011010
	UDR0 = 0x53;
	_delay_ms(2); //Espera 2ms tendo em vista que pra transmtir os 11 bits demora 1,14ms
}

int main(void)
{
	UART_config();
    while(1)
    {
        UART_send();
    }
}