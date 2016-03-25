/*
+-----------------------------------------------------------------------+
| File:	i2c_protocol.c													|
+-----------------------------------------------------------------------+
| Brief: i2c protocol implementation concerning Atmega328p-pn			|
+-----------------------------------------------------------------------+
| The 2-wire serial interface is a simple yet powerful and flexible		|
| communication interface that only uses two bus lines that can			|
| communicate with up to 128 different devices! All you need is a		|
| single pull-up resistor for each of these lines.						|
| All devices connected to the bus have individual addresses, and		|
| mechanisms for resolving bus contention are inherent in the TWI		|
| protocol.																|
+-----------------------------------------------------------------------+
| Authors: Rick Kock <ritkock@student.nl>								|
+-----------------------------------------------------------------------+
*/

//-------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------
#include "i2c_protocol.h"
//-------------------------------------------------------------------------

void i2c_initialTest(void) {
	printf("%s\n", "I'm going here.");
	i2c_issueStartCondition();
	i2c_displayStatus();
}

//////////////////////////////////////////////////////////////////////////
//						START AND STOP CONDITIONS
//////////////////////////////////////////////////////////////////////////
//
// Master initiates a transmission by sending a start condition.
// If a REPEATED START condition is issued, it means the master
// wishes to initiate a new transfer without relinquishing
// control of the bus. Start and stop conditions are sent by
// changing the level of the SDA line when the SCL line is high.
//
// Master transmits a stop condition. When a stop condition is
// sent, it means that the master wishes to terminate the
// transmission. This may occur after a START condition or after
// a REPEATED START condition. Between the start and stop
// condition, the bus is considered busy.
//
//////////////////////////////////////////////////////////////////////////

void i2c_issueStartCondition(void) {
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
}

void i2c_issueStopCondition(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void i2c_init(void) {
	// Master sends start condition
	i2c_issueStartCondition();
	// If start condition detected
	if (i2c_getStatus() = START)
	{

	}
}

//////////////////////////////////////////////////////////////////////////
//							DATA PACKET FORMAT
//////////////////////////////////////////////////////////////////////////
//
// All data packets transmitted on the TWI bus are nine bits long, 
// consisting of one data byte and an acknowledge bit. 
// 
// During a data transfer, the Master generates the clock and the START 
// and STOP conditions, while the Receiver is responsible for 
// acknowledging the reception. 
//
// An Acknowledge (ACK) is signaled by the Receiver pulling the SDA line 
// low during the ninth SCL cycle. If the Receiver leaves the SDA line 
// high, a NACK is signaled. When the Receiver has received the last 
// byte, or for some reason cannot receive any more bytes, it should 
// inform the Transmitter by sending a NACK after the final byte. The MSB
// of the data byte is transmitted first.
//
//////////////////////////////////////////////////////////////////////////

// Wait for TWINT Flag set. Indicates START condition transmitted
void i2c_wait(void) {
	while (!(TWCR & (1 << TWINT)));
}

// Load data into TWDR register
// Clear TWINT bit in TWCR to start transmission of address
void i2c_loadValueTWI(unsigned char data) {
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
}

int i2c_getAddressBits(int word) {
	return (word & 0x7F);
}

int i2c_getAddress_R_W_Bit(int word) {
	return (GET_BIT(word, 7));
}

int i2c_getAddressAckBit(int word) {
	return (GET_BIT(word, 8));
}

//////////////////////////////////////////////////////////////////////////
//							ADDRESS PACKET FORMAT
//////////////////////////////////////////////////////////////////////////
//
// If the addressed slave is busy, or cannot service the master for some 
// reason, the SDA line must be left high in the acknowledge clock cycle, 
// in which case the master could issue a stop condition, or a repeated 
// start condition to start a new transmission.
//
//////////////////////////////////////////////////////////////////////////

bool hasAcknowledged(short word) {
	return (word & (1 << 9));
}

void i2c_commenceProtocol(void) {
	i2c_issueStartCondition();
}

bool i2c_sdaChangeDetected(void) {
}

bool i2c_sclLineIsHigh(void) {
}

short getAcknowledgeBit(short word) {
	return GET_BIT(word, 8);
}

//////////////////////////////////////////////////////////////////////////
//							CONTROL UNIT
//////////////////////////////////////////////////////////////////////////
//
// When an event  requires attention, the TWINT interrupt flag is 
// asserted. In the next clock cycle, The TWSR is updated with the status 
// code identifying the event.
//
// The Address Match unit checks if received address bytes match the 
// seven-bit address in the TWI Address Register (TWAR). If the TWI 
// General Call Recognition Enable (TWGCE) bit in the TWAR is written to 
// one, all incoming address bits will also be compared against the 
// General Call address. Upon an address match, the Control Unit is 
// informed, allowing correct action to be taken.
//
//////////////////////////////////////////////////////////////////////////

uint8_t i2c_getStatus(void) {
	uint8_t status;
	status = TWSR & 0xF8;
	return status;
}

void i2c_displayStatus() {
	uint8_t status = i2c_getStatus();
	
	switch (status) {
		
		case START:
		printf("%s\n", "A start condition has been successfully transmitted.");
		break;
		
		case REPEATED_START:
		printf("%s\n", "A repeated start condition has been transmitted.");
		break;
		
		case SLA_W:
		printf("%s\n", "SLA+W has been transmitted.");
		break;
		
		case  SLA_W_NOT_ACK:
		printf("%s\n", "SLA+W has been transmitted. Not ACK has been received.");
		break;
		
		case DATA_TRANSMIT_ACK:
		printf("%s\n", "Data has been transmitted. ACK has been received.");
		break;
		
		case DATA_TRANSMIT_NOT_ACK:
		printf("%s\n", "Data has been transmitted. Not ACK has been received.");
		break;
		
		case ARBITRATION_LOST_SLA_W_OR_DATA:
		printf("%s\n", "Arbitration has been lost in SLA+W or data bytes.");
		break;
		
		case TWINT_NOT_SET:
		printf("%s\n", "No relevant information available, because TWINT flag is not set.");
		break;
		
		default:
		printf("%s","Status: ");
		printf("%i\n",status);
		break;
	}
}

