/*
+-----------------------------------------------------------------------+
| File:	usart.c															|
+-----------------------------------------------------------------------+
| Brief: Usart implementation concerning Atmega328p-pn					|
+-----------------------------------------------------------------------+
| The USART is a highly flexible serial communication device. For this	|
| project, we are mainly using it to efficiently debug our code. It is	|
| used to recieve information and display it in the terminal.			|
+-----------------------------------------------------------------------+
| Authors: Rick Kock <ritkock@student.nl>								|
+-----------------------------------------------------------------------+
*/

//-------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------
#include "usart.h"
//-------------------------------------------------------------------------

// Enable the receiver and transmitter. set frame format: 8data, 1 stop bit
void USART_Init( unsigned int ubrr) {
	setBaudRate(ubrr);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);		// Enable receiver and transmitter
	UCSR0C = (3<<UCSZ00);				//Set data format
}

void setBaudRate(unsigned int ubrr) {
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
}

// Wait for data to be received Get and return received data from buffer.
unsigned char USART_Receive(void) {
	while (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

// Wait for empty transmit buffer. Put data into buffer, sends the data
void USART_Transmit(unsigned char data) {
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}