
#ifndef AVR_I2C_DECLARATIONS_H_
#define AVR_I2C_DECLARATIONS_H_

void TWI_Master_Initialize();
void TWI_Master_Start();
void TWI_Master_Write_Addr(uint8_t Addr);
void TWI_Master_Write_Data(uint8_t Data);
void TWI_Master_Stop();

#endif /* AVR_I2C_DECLARATIONS_H_ */