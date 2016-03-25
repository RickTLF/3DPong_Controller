/*
+-----------------------------------------------------------------------+
| File:	atmega328BatjesController.c										|
+-----------------------------------------------------------------------+
| Brief: Implementation concerning project Pong							|
+-----------------------------------------------------------------------+
| This is the implementation concerning the wireless controllers for	|
| our console game 3D-Pong which consists of multiple variation, such	|
| as hockey, tennis, handball and a demo of tennis game play.			|
|																		|
| The chosen micro controller for the wireless motion enabled remote,	|
| is the popular ATMEGA328P-PN. The remote will communicate with		|
| other components with the use of protocols, such as: 2-wire serial	| 
| interface, usart (for debugging purposes), and am- or					|
| fm-transmission.														|
|																		|
+-----------------------------------------------------------------------+
| IMPORTANT																|
+-----------------------------------------------------------------------+
|						|												|
| External oscillator	|	8Mhz										|
| Fuses set				|	lfuse:0xe6, hfuse:0xd9						|
| Baud rate				|	b19200										|
| Programmer used		|	Arduino (with ArduinoISP example programmed)|
|																		|
+-----------------------------------------------------------------------+
| Authors: Rick Kock <ritkock@student.nl>								|
+-----------------------------------------------------------------------+
*/

//-------------------------------------------------------------------------
// Definitions
//-------------------------------------------------------------------------
#define F_CPU	8000000UL
#define BAUD	19200
#define MYUBRR	F_CPU/16/BAUD-1
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------
#include "usart.h"
//-------------------------------------------------------------------------

int main(void)
{
	USART_Init(MYUBRR); 
    while(1)
    {
		//TODO:: Please write your application code
		USART_Transmit(USART_Receive());
    }
}