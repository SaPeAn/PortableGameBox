
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

/*-------------------------SYSTEM VARIABLES-----------------------------------*/
typedef struct{
  uint8 sec;     // BCD  0...59            |x |SH|SH|SH|SL|SL|SL|SL|
  uint8 min;     // BCD  0...59            |x |MH|MH|MH|ML|ML|ML|ML|
  uint8 hour;    // BCD  0...23            |x |x |HH|HH|HL|HL|HL|HL|
  uint8 day;     // BCD  0...              |x |x |Dh|DH|DL|DL|DL|DL|    
  uint8 weekday; // BCD  from SUN to SAT   |x |x |x |x |x |W |W |W |
  uint8 month;   // century bit & BCD      |C |x |x |MH|ML|ML|ML|ML|
  uint8 year;    // BCD                    |YH|YH|YH|YH|YL|YL|YL|YL|
} rtc_t;

typedef union{
  rtc_t rtcpar; 
  uint8  rtcdata[7];
} rtcun_t;

typedef union{
  struct{
    unsigned MenuFl             :1;
    unsigned RunGameFl          :1;
    unsigned MenuSettingsFl     :1;  
    unsigned TestScreen         :1;  
    unsigned MMPartbit_2        :1;  
    unsigned coursorpos         :3;
  };
} flags_t;                               // System functions launch flags

flags_t CFlags = {1, 0, 0, 0, 0, 1};

uint32 timestamp = 0;    // System timer (ms), starts counting from power on or last restart
rtcun_t rtcbcd;          // structure for storaging clock/date from RTC module (BCD format))
rtcun_t rtcraw;          // structure for storaging system clock/date (uint8)
uint8 Ubat;              // ADC data from battery level measurement
uint8 batlvl;            // battery level for display (0...5)
uint8 brightlvl;         // brightness level for display (0...7)
uint8 brightPWM = 220;   // PWM duty cycle value for regulate display brightness

const uint8 str_null[] = "NULL"; //for show zero pointer
/*----------------------------------------------------------------------------*/

/*-------------------------SYSTEM FUNCTIONS-----------------------------------*/
void Interrupt_init(void);
void timersinit(void);
void commoninit(void);
void gettime(void);
uint8 getbatlvl(uint8);
void delay_ms(uint32);
uint8 getrand(uint8);
void randinit(void);
char dig_to_smb(uint8);
void u16_to_str(char*, uint16, uint8);
void BrightPWMgen(uint8);
void decbright(void);
void incbright(void);
void getbrightlvl(void);
void Sounds(uint16);
void ShutDown(void);
void ShutDownLB(void);
void batcheck(void);
void rtcbcdtoraw(void);
void rtcrawtobcd(void);
/*----------------------------------------------------------------------------*/

/*---------------------BUTTONS & JOYSTICK VARIABLES---------------------------*/
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
//buttons
typedef union{
  struct{
    uint8 up      :1;
    uint8 down    :1;
    uint8 left    :1;
    uint8 right   :1;
    uint8 joyFl   :1;
  };
}joy_t;

btn_t B1;
btn_t B2;
btn_t B3;
btn_t B4;
uint8 ox, oy; //joystick coordinates
joy_t joystick = {0};
/*----------------------------------------------------------------------------*/

/*---------------------BUTTONS & JOYSTICK FUNCTIONS---------------------------*/
btn_t CreateBtn(volatile uint8*, volatile uint8*, volatile uint8*, const uint8, const uint8, const uint32*);
void TestBtn(btn_t*);
void initbuttons(void);
uint8 adc_getval_an0(void);
uint8 adc_getval_an1(void);
uint8 adc_getval_an2(void);
void getjoypos(void);
void checkjoydir(void);
/*----------------------------------------------------------------------------*/

/*-------------------------------GAME VARIABLES-------------------------------*/
typedef struct
{
  int    health;
  int    energy;
  uint8  gasmask_fl;
  uint8  bombs;
  uint8  money;
  uint8  pg;
  uint8  cl;
}Gamer_t;

Gamer_t Gamer;

typedef struct 
{
  uint8 bombs;
  uint8 bullets;
  uint8 evilstars;
  uint8 chemists;
  uint8 gasclouds;
  uint8 coins;
}objquantity_t;

objquantity_t Dispobjects;
/*----------------------------------------------------------------------------*/

typedef enum {
  lines_first,
  columns_first
}tDirect;

typedef struct{
  uint8 pages;
  uint8 columns;
  uint8* sprite;
  tDirect direct;
}tSprite;

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

