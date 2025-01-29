# 1 "common.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "common.c" 2
# 1 "./common.h" 1








typedef unsigned char uint8;
typedef char int8;
typedef unsigned int uint16;
typedef int int16;
typedef unsigned long uint32;
typedef long int32;

uint32 timestamp = 0;
void Delay_ms(uint32);
uint8 getrand(uint8);
void randinit(void);
uint8 dig_to_smb(uint8);
void u8_to_str(uint8*, uint8);
# 1 "common.c" 2

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\stdlib.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\musl_xc8.h" 1 3
# 5 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\stdlib.h" 2 3





# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\features.h" 1 3
# 11 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\stdlib.h" 2 3
# 21 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\stdlib.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 24 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long int wchar_t;
# 128 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned size_t;
# 174 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __int24 int24_t;
# 210 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\stdlib.h" 2 3

int atoi (const char *);
long atol (const char *);

long long atoll (const char *);

double atof (const char *);


float strtof (const char *restrict, char **restrict);
double strtod (const char *restrict, char **restrict);
long double strtold (const char *restrict, char **restrict);



long strtol (const char *restrict, char **restrict, int);
unsigned long strtoul (const char *restrict, char **restrict, int);

long long strtoll (const char *restrict, char **restrict, int);
unsigned long long strtoull (const char *restrict, char **restrict, int);


unsigned long __strtoxl(const char * s, char ** endptr, int base, char is_signed);

unsigned long long __strtoxll(const char * s, char ** endptr, int base, char is_signed);
# 55 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\stdlib.h" 3
int rand (void);
void srand (unsigned);

void *malloc (size_t);
void *calloc (size_t, size_t);
void *realloc (void *, size_t);
void free (void *);

          void abort (void);
int atexit (void (*) (void));
          void exit (int);
          void _Exit (int);

void *bsearch (const void *, const void *, size_t, size_t, int (*)(const void *, const void *));







__attribute__((nonreentrant)) void qsort (void *, size_t, size_t, int (*)(const void *, const void *));

int abs (int);
long labs (long);

long long llabs (long long);


typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;

typedef struct { long long quot, rem; } lldiv_t;


div_t div (int, int);
ldiv_t ldiv (long, long);

lldiv_t lldiv (long long, long long);


typedef struct { unsigned int quot, rem; } udiv_t;
typedef struct { unsigned long quot, rem; } uldiv_t;
udiv_t udiv (unsigned int, unsigned int);
uldiv_t uldiv (unsigned long, unsigned long);
# 2 "common.c" 2



void Delay_ms(uint32 ms)
{
  uint32 temp = timestamp;
  while((timestamp - temp) < ms);
}

void randinit(void)
{
  srand((uint8)timestamp);
}

uint8 getrand(uint8 N)
{
  return (rand() % (N + 1));
}

uint8 dig_to_smb(uint8 dig)
{
  switch (dig)
  {
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
  }
  return 0;
}

void u8_to_str(uint8* str, uint8 num)
{
  str[0] = num/100;
  str[1] = (num%100)/10;
  str[2] = num%10;
  if(num > 99)
  {
    for(uint8 i = 0; i < 3; i++) {
    str[i] = dig_to_smb(str[i]);
    }
    str[3] = '\0';
  }
  if((num > 9) && (num < 100))
  {
    for(uint8 i = 0; i < 2; i++) {
    str[i] = dig_to_smb(str[i+1]);
    }
    str[2] = '\0';
  }
  if(num < 10)
  {
    str[0] = dig_to_smb(str[2]);
    str[1] = '\0';
  }
}
