
#ifndef COMMON_H
#define	COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

#define     ENABLE     1
#define     DISABLE    0    

    
typedef unsigned char    uint8;
typedef char             int8; 
typedef unsigned int     uint16;
typedef int              int16;
typedef unsigned long    uint32;
typedef long             int32;  

/*-------------------------GLOBAL VARIABLES-----------------------------------*/
typedef struct{
  uint8   sec;
  uint8   min;
  uint8   hour;
} systime_t;

uint32 timestamp = 0; //System timer (ms) from power on or last restart
systime_t Time;
uint8 Ubat;
uint8 batlvl;
/*----------------------------------------------------------------------------*/
typedef struct{
  volatile uint8*  Port;
  volatile uint8*  Lat;
  uint8            inputmask;
  uint8            outputmask;
  const uint32*    timecounter;
  uint32           btnTimer;
  uint8            BtnFl;
  uint8            BtnON;
  uint8            Toggle;
  uint8            HoldON;
  uint8            StuckON;
}btn_t;

btn_t CreateBtn(volatile uint8*, volatile uint8*, volatile uint8*, const uint8, const uint8, const uint32*);
void TestBtn(btn_t*);

btn_t B1;
btn_t B2;
btn_t B3;
btn_t B4;

uint8 ox, oy; //joystick coordinates
uint8 bright = 200;
    
void initbuttons(void);    
void Interrupt_init(void);
void timersinit(void);
uint8 adc_getval_an0(void);
uint8 adc_getval_an1(void);
uint8 adc_getval_an2(void);
void testbuttons(void);
void initbuttons(void);
  
/*-------------------------SYSTEM FUNCTIONS-----------------------------------*/
void commoninit(void);
void gettime(systime_t*);
uint8 getbatlvl(uint8);
void delay_ms(uint32);
uint8 getrand(uint8);
void randinit(void);
uint8 dig_to_smb(uint8);
void  u16_to_str(uint8*, uint16, uint8);
void BrightPWM(uint8);
void Sounds(uint16);
void ShutDown(void);
void batcheck(void);

/*----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

