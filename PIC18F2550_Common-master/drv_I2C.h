#ifndef DRV_I2C_H
#define	DRV_I2C_H


void I2C_init(void);
unsigned char I2C_WriteByte(unsigned char data_out);
void I2C_Idle(void);
void I2C_RepStart(void);
void I2C_Start(void);
void I2C_Stop(void);
unsigned char I2C_ReadByte(void);
void I2C_NAck(void);
void I2C_Ack(void);

#endif	