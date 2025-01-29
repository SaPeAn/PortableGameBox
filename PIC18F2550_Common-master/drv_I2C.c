
#include "xc.h"
#include "drv_I2C.h"

void I2C_init(void)
{
   TRISB |= 0b00000011; // RB0 RB1 Inputs (for I2C)
   SSPCON1 = 0x08;
   SSPSTAT = 0x00;
   SSPADD  =  29; // 400,000 baud ----> SSPADD = (48MHz/(4*0.4 MHz) - 1
   SSPCON1bits.SSPEN = 1;
}

void I2C_Idle(void)
{
   while ((SSPCON2 & 0x1F) || (SSPSTATbits.R_W));
}


void I2C_Start(void)
{
   I2C_Idle();
   SSPCON2bits.SEN=1;
   while(SSPCON2bits.SEN);
}


void I2C_Stop(void)
{
   SSPCON2bits.PEN = 1; // initiate bus stop condition
   I2C_Idle();
}

void I2C_RepStart(void)
{
   SSPCON2bits.RSEN = 1;    // initiate bus restart condition
   while(SSPCON2bits.RSEN);
}

unsigned char I2C_WriteByte(unsigned char data_out)
{
   SSPBUF = data_out;         // write single byte to SSPBUF
   if (SSPCON1bits.WCOL)      // test if write collision occurred
      return (1);            // if WCOL bit is set return negative #
   else
   {
      if(((SSPCON1&0x0F)!= 0x08) && ((SSPCON1&0x0F)!=0x0B)) //slave mode only
      {
         SSPCON1bits.CKP = 1;      // release clock line
         while (!PIR1bits.SSPIF);  // wait until ninth clock pulse received

         // if R/W=0 and BF=0, NOT ACK was received
         if ((!SSPSTATbits.R_W) && (!SSPSTATbits.BF))
            return (2);         // Return NACK
         else
            return(0);           // Return ACK

      }
      else if(((SSPCON1&0x0F)==0x08) || ((SSPCON1&0x0F)==0x0B)) //master mode only
      {
         while(SSPSTATbits.BF);   // wait until write cycle is complete
         I2C_Idle();              // ensure module is idle
         if (SSPCON2bits.ACKSTAT) // test for ACK condition received
            return (2);          // Return NACK
         else
            return (0);           // Return ACK
      }
   }
   return 0;
}

unsigned char I2C_ReadByte(void)
{
   if(((SSPCON1&0x0F)==0x08) || ((SSPCON1&0x0F)==0x0B))  //master mode only
      SSPCON2bits.RCEN = 1;      // enable master for 1 byte reception

   while (!SSPSTATbits.BF);      // wait until byte received

   return (SSPBUF);              // return with read byte
}


void I2C_Ack(void)
{
   SSPCON2bits.ACKDT = 0;           // set acknowledge bit state for ACK
   SSPCON2bits.ACKEN = 1;           // initiate bus acknowledge sequence
   I2C_Idle();
}

void I2C_NAck(void)
{
   SSPCON2bits.ACKDT = 1;          // set acknowledge bit for not ACK
   SSPCON2bits.ACKEN = 1;          // initiate bus acknowledge sequence
   I2C_Idle();
}
