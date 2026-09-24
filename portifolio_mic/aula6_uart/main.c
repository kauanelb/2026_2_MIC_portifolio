/*
 * main.c
 *
 * Created: 9/17/2026 10:15:14 AM
 *  Author: kauanelb
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

//tratamento de string
char gMessage[16] = "Mensagem"; // Vetor com espaço de 16 bytes alocados com a mensagem "Mensagem" null terminated strings (8 bytes + terminação nula)

void UART_config(){ //Configuração do módulo do USRT0 para modo assíncrono, frame de 8 bits, paridade par, BAUD de 9600
	UCSR0A = (0<<U2X0);							//Modo "double speed" desativado, tem relação com o ubrr0
	UCSR0B = (0<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02); //1 - Desabilita o receptor. 2 - Habilita o transmissor UART0. 3 - pg 162, configurar o tamanho do frame, falar quantos bits vão ser enviados tabela 19.7
	UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)          //Modo assíncrono pg 161 tabela 19.4
			|(1<<UPM01)|(0<<UPM00)              //Tabela 19.5 pg 162, paridade par
			|(1<<USBS0)                         //2 bits de stop
			|(1<<UCSZ01)|(1<<UCSZ00)            //3 - Ainda sobre a tabela 19.7, configura o tamanho do frame pra 8 bits  
			|(0<<UCPOL0);                       //Polaridade de clock ignorada
	UBRR0 = 103; //BAUD de 9600 seria se fosse 103,16..., sendo 103, fica 9615... erro de 0,16%
				//9600 bits por segundo, frequencia, tem 8 bits dos dados, o start, o stop, e a paridade, total de 11 bits, logo pra mandar um byte ele demora 11/9600 = 1,14ms
}

void UART_send_byte(uint8_t pByte){ //Envia um byte na USART0
	//Aguardar espaço no buffer (semáforo)
	//UDR0 = 0x5A; Envia um byte, em hexa 0x5A, em binário 01011010
	while((UCSR0A & (1<<UDRE0)) == 0); //Enquanto o bit é 0, ele espera, quando for 1 ele sai do while
	UDR0 = pByte; //Envia um byte exemplo
}

void UART_send_string(char *pString){ //passa o espaço físico que está a "Mensagem", tipo posição de memória "358"
	char *tMessagePtr = pString;
	while(*tMessagePtr != 0){ //repete enquanto o ponteiro não for 0, (8 bytes + terminação nula)
		UART_send_byte(*tMessagePtr); //desreferencia o ponteiro, lê a real mensagem "Mensagem", só o primeiro caractere, o M
		tMessagePtr++;
	//UART_send_byte(*tMessagePtr); //Desreferencia o ponteiro, após ele dar um passo, então vai aparecer o "e"
	}
}

int main(void)
{
	UART_config();
    while(1)
    {
		//Tabela aschii
        //UART_send_byte(0x4D); // M em hexa
		//UART_send_byte(0x49); // I
		//UART_send_byte(0x43); // C
		//UART_send_byte(0x0A); // Pula uma linha, line feed
		
		//UART_send_byte('M'); //Aceita, fica mais facil
		//UART_send_byte('I');
		//UART_send_byte('C');
		//UART_send_byte('\n');
		
		UART_send_string(gMessage);
		_delay_ms(5); //tempo de silêncio
    }
}