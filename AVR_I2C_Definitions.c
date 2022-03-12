#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "AVR_I2C_Declarations.h"

void TWI_Master_Initialize()
{
	/*
	SCL_Frequency = 400 KHz, CPU = 8 MHz
	Pre-Scalar value = 64, TWPS1 = 1, TWPS2 = 1, TWSR = 0b0000011 = 0x03
	Using Bit rate Formula, then TWBR = 0x0C;
	*/
	
	TWBR = 0x00; //Clear first
	TWBR = 0x0C; //TWI Bit Rate Register
}

void TWI_Master_Start()
{
	TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWSTA); //Enable TWI, clear interrupt flag, generate Start
	while( !(TWCR & (1<<TWINT)) ) ; //Wait until TWI finish its current Event
	//here, master has completed the Start event
	
	uint8_t status = TWSR & (0xF8); //TWI status bits (high 5-bits of TWSR)
	while( status != (0x08) ) ; //Wait until Start is transmitted
}

void TWI_Master_Write_Addr(uint8_t Addr)
{
	TWDR = Addr; //TWI Data Registers
	TWCR = (1<<TWEN) | (1<<TWINT); //Enable TWI, clear interrupt flag
	while( !(TWCR & (1<<TWINT)) ) ; //Wait until TWI finish its current Event
	//here, Master has sent SLA+W (Slave Address + Write) to Slave
	
	uint8_t status = TWSR & (0xF8); //TWI status bits (high 5-bits of TWSR)
	while( status != (0x18) ) ; //Wait until ACK is received from the Slave that has the matched Address
}

void TWI_Master_Write_Data(uint8_t Data)
{
	TWDR = Data; //TWI Data Registers
	TWCR = (1<<TWEN) | (1<<TWINT); //Enable TWI, clear interrupt flag
	while( !(TWCR & (1<<TWINT)) ) ; //Wait until TWI finish its current Event
	//here, Master has sent Data to Slave
	
	uint8_t status = TWSR & (0xF8); //TWI status bits (high 5-bits of TWSR)
	while( status != (0x28) ) ; //Wait until ACK is received from the Slave that received DATA
}

void TWI_Master_Stop()
{
	TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWSTO); //Enable TWI, clear interrupt flag, generate STOP
	while( !(TWCR & (1<<TWSTO)) ) ; //Wait until TWI finish its current Event (Stop Event)
	//here, master has completed the Stop event
}