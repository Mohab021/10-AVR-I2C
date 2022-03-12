
// This program for Master

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "AVR_Ports.h"
#include "AVR_LCD_Declarations.h"
#include "AVR_I2C_Declarations.h"

int main(void)
{
	uint8_t cnt = 0;
	char * x  = "MOHAB";
	
	LCD_Initialize();
	TWI_Master_Initialize();
	
	_delay_ms(10);
	LCD_Print("MASTER: ");
	_delay_ms(10);
	
	while(x[cnt] != 0)
	{
		TWI_Master_Start();
		_delay_ms(10);
		TWI_Master_Write_Addr(0x20);
		_delay_ms(10);
		TWI_Master_Write_Data(x[cnt]);
		LCD_Out(TWDR); //Print the transmitted data
		_delay_ms(10);
		TWI_Master_Stop();
		_delay_ms(10);
		
		cnt++;
	}
}
