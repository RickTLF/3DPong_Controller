#ifndef I2C_H_
#define I2C_H_

//-------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// Definitions
//-------------------------------------------------------------------------
#define F_CPU 8000000
#define GET_BIT(data, bit)	((data &(1 << bit)) >> bit)
#define ADDRESS_PACKET_SIZE 9
#define ADDRESS_BITS_SIZE 7
#define DATA_PACKET_SIZE 9
#define DATA_BYTE_SIZE 8
#define bool int
#define READ 0
#define WRITE 1
#define TRUE 1
#define FALSE 0
//-------------------------------------------------------------------------
// Definitions for i2c status
//-------------------------------------------------------------------------
#define START								0x08
#define REPEATED_START						0x10
#define SLA_W								0x18
#define SLA_W_NOT_ACK						0x20
#define DATA_TRANSMIT_ACK					0x28
#define DATA_TRANSMIT_NOT_ACK				0x30
#define ARBITRATION_LOST_SLA_W_OR_DATA		0x38
#define TWINT_NOT_SET						0xF8
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------
void i2c_initialTest(void);
void i2c_issueStartCondition(void);
void i2c_issueStopCondition(void);
void i2c_init(void)
void i2c_wait(void);
void i2c_loadValueTWI(unsigned char data);
int i2c_getAddressBits(int word);
int i2c_getAddress_R_W_Bit(int word);
int i2c_getAddressAckBit(int word);
bool hasAcknowledged(short word);
void i2c_commenceProtocol(void);
bool i2c_sdaChangeDetected(void)
bool i2c_sclLineIsHigh(void);
short getAcknowledgeBit(short word);
uint8_t i2c_getStatus(void);
void i2c_displayStatus(void);
//-------------------------------------------------------------------------

#endif /* I2C_H_ */