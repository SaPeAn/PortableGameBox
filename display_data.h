#ifndef __DISP_DAT_H__
#define __DISP_DAT_H__

#include "common.h"

// ASCII � ��������� 5�8 ��������
#define CHAR_W	5
#define CHAR_NUM	256
const uint8 char_8x5[CHAR_NUM][CHAR_W]={
{0x7F,0x7F,0x7F,0x7F,0x7F},//[
{0x7F,0x7F,0x7F,0x7F,0x7F},//[]=(1)
{0x08,0x08,0x78,0x00,0x00},//[]=(2)
{0x00,0x00,0x0F,0x08,0x08},//[]=(3)
{0x08,0x08,0x0F,0x00,0x00},//[]=(4)
{0x00,0x00,0x7F,0x00,0x00},//[]=(5)
{0x08,0x08,0x08,0x08,0x08},//[]=(6)
{0x00,0x1C,0x3E,0x1C,0x00},//[]=(7)
{0x00,0x1C,0x36,0x1C,0x00},//[]=(8)
{0x00,0x00,0x00,0x00,0x00},//[	]=(9)
{0x00,0x00,0x00,0x00,0x00},//[?]=(10)
{0x00,0x00,0x00,0x00,0x00},//[]=(11)
{0x00,0x00,0x3E,0x3E,0x00},//[]=(12)
{0x00,0x00,0x00,0x00,0x00},//[?]=(13)
{0x00,0x00,0x00,0x00,0x00},//[]=(14)
{0x00,0x00,0x00,0x00,0x00},//[]=(15)
{0x08,0x08,0x7F,0x08,0x08},//[]=(16)
{0x00,0x08,0x1C,0x3E,0x00},//[]=(17)
{0x14,0x36,0x7F,0x36,0x14},//[]=(18)
{0x00,0x5F,0x00,0x5F,0x00},//[]=(19)
{0x0E,0x11,0x7F,0x01,0x7F},//[]=(20)
{0x08,0x08,0x0F,0x08,0x08},//[]=(21)
{0x08,0x08,0x78,0x08,0x08},//[]=(22)
{0x08,0x08,0x7F,0x00,0x00},//[]=(23)
{0x04,0x02,0x7F,0x02,0x04},//[]=(24)
{0x00,0x00,0x7F,0x08,0x08},//[]=(25)
{0x08,0x08,0x3E,0x1C,0x08},//[]=(26)
{0x08,0x1C,0x3E,0x08,0x08},//[]=(27)
{0x00,0x00,0x00,0x00,0x00},//[]=(28)
{0x00,0x00,0x00,0x00,0x00},//[]=(29)
{0x00,0x00,0x00,0x00,0x00},//[]=(30)
{0x00,0x00,0x00,0x00,0x00},//[]=(31)
{0x00,0x00,0x00,0x00,0x00},//[ ]=(32)
{0x00,0x06,0x5F,0x06,0x00},//[!]=(33)
{0x00,0x07,0x00,0x07,0x00},//["]=(34)
{0x14,0x7F,0x14,0x7F,0x14},//[#]=(35)
{0x06,0x49,0x7F,0x49,0x30},//[$]=(36)
{0x43,0x33,0x08,0x66,0x61},//[%]=(37)
{0x36,0x49,0x55,0x22,0x50},//[&]=(38)
{0x00,0x00,0x07,0x00,0x00},//[']=(39)
{0x00,0x00,0x3E,0x41,0x00},//[(]=(40)
{0x00,0x41,0x3E,0x00,0x00},//[)]=(41)
{0x00,0x05,0x02,0x05,0x00},//[*]=(42)
{0x08,0x08,0x3E,0x08,0x08},//[+]=(43)
{0x00,0x40,0x30,0x00,0x00},//[,]=(44)
{0x00,0x08,0x08,0x08,0x00},//[-]=(45)
{0x00,0x00,0x20,0x00,0x00},//[.]=(46)
{0x00,0x60,0x18,0x06,0x00},//[/]=(47)
{0x3E,0x51,0x49,0x45,0x3E},//[0]=(48)
{0x00,0x42,0x7F,0x40,0x00},//[1]=(49)
{0x00,0x62,0x51,0x49,0x46},//[2]=(50)
{0x00,0x22,0x41,0x49,0x36},//[3]=(51)
{0x18,0x14,0x12,0x7F,0x00},//[4]=(52)
{0x00,0x27,0x49,0x49,0x31},//[5]=(53)
{0x3E,0x49,0x49,0x49,0x32},//[6]=(54)
{0x00,0x01,0x71,0x0D,0x03},//[7]=(55)
{0x36,0x49,0x49,0x49,0x36},//[8]=(56)
{0x26,0x49,0x49,0x49,0x3E},//[9]=(57)
{0x00,0x00,0x12,0x00,0x00},//[:]=(58)
{0x00,0x40,0x32,0x00,0x00},//[;]=(59)
{0x08,0x14,0x22,0x41,0x00},//[<]=(60)
{0x24,0x24,0x24,0x24,0x24},//[=]=(61)
{0x00,0x41,0x22,0x14,0x08},//[>]=(62)
{0x00,0x02,0x51,0x09,0x06},//[?]=(63)
{0x32,0x49,0x79,0x41,0x3E},//[@]=(64)
{0x7E,0x11,0x11,0x11,0x7E},//[A]=(65)
{0x7F,0x49,0x49,0x49,0x36},//[B]=(66)
{0x3E,0x41,0x41,0x41,0x22},//[C]=(67)
{0x7F,0x41,0x41,0x22,0x1C},//[D]=(68)
{0x7F,0x49,0x49,0x49,0x00},//[E]=(69)
{0x7F,0x09,0x09,0x01,0x00},//[F]=(70)
{0x3E,0x41,0x51,0x31,0x72},//[G]=(71)
{0x7F,0x08,0x08,0x08,0x7F},//[H]=(72)
{0x00,0x41,0x7F,0x41,0x00},//[I]=(73)
{0x00,0x20,0x41,0x3F,0x01},//[J]=(74)
{0x7F,0x08,0x14,0x22,0x41},//[K]=(75)
{0x00,0x7F,0x40,0x40,0x40},//[L]=(76)
{0x7F,0x02,0x0C,0x02,0x7F},//[M]=(77)
{0x7F,0x04,0x08,0x10,0x7F},//[N]=(78)
{0x3E,0x41,0x41,0x41,0x3E},//[O]=(79)
{0x7F,0x09,0x09,0x06,0x00},//[P]=(80)
{0x3E,0x41,0x51,0x21,0x5E},//[Q]=(81)
{0x7F,0x09,0x19,0x29,0x46},//[R]=(82)
{0x26,0x49,0x49,0x49,0x32},//[S]=(83)
{0x01,0x01,0x7F,0x01,0x01},//[T]=(84)
{0x3F,0x40,0x40,0x40,0x3F},//[U]=(85)
{0x1F,0x20,0x40,0x20,0x1F},//[V]=(86)
{0x3F,0x40,0x30,0x40,0x3F},//[W]=(87)
{0x63,0x14,0x08,0x14,0x63},//[X]=(88)
{0x07,0x08,0x70,0x08,0x07},//[Y]=(89)
{0x61,0x51,0x49,0x45,0x43},//[Z]=(90)
{0x00,0x7F,0x41,0x41,0x00},//[[]=(91)
{0x00,0x06,0x18,0x60,0x00},//[\]=(92)
{0x00,0x41,0x41,0x7F,0x00},//[]]=(93)
{0x04,0x02,0x01,0x02,0x04},//[^]=(94)
{0x40,0x40,0x40,0x40,0x40},//[_]=(95)
{0x00,0x00,0x01,0x06,0x00},//[`]=(96)
{0x00,0x20,0x54,0x54,0x78},//[a]=(97)
{0x7F,0x44,0x44,0x38,0x00},//[b]=(98)
{0x38,0x44,0x44,0x44,0x00},//[c]=(99)
{0x38,0x44,0x44,0x7F,0x00},//[d]=(100)
{0x38,0x54,0x54,0x18,0x00},//[e]=(101)
{0x10,0x7E,0x11,0x02,0x00},//[f]=(102)
{0x08,0x54,0x54,0x3C,0x00},//[g]=(103)
{0x7F,0x04,0x04,0x78,0x00},//[h]=(104)
{0x00,0x00,0x7D,0x00,0x00},//[i]=(105)
{0x20,0x40,0x3D,0x00,0x00},//[j]=(106)
{0x7F,0x10,0x28,0x44,0x00},//[k]=(107)
{0x00,0x41,0x7F,0x40,0x00},//[l]=(108)
{0x7C,0x04,0x78,0x04,0x78},//[m]=(109)
{0x7C,0x04,0x04,0x78,0x00},//[n]=(110)
{0x38,0x44,0x44,0x44,0x38},//[o]=(111)
{0x7C,0x24,0x24,0x18,0x00},//[p]=(112)
{0x18,0x24,0x24,0x7C,0x00},//[q]=(113)
{0x00,0x7C,0x08,0x04,0x04},//[r]=(114)
{0x08,0x54,0x54,0x20,0x00},//[s]=(115)
{0x04,0x3F,0x44,0x20,0x00},//[t]=(116)
{0x3C,0x40,0x40,0x20,0x7C},//[u]=(117)
{0x1C,0x20,0x40,0x20,0x1C},//[v]=(118)
{0x3C,0x40,0x30,0x40,0x3C},//[w]=(119)
{0x44,0x28,0x10,0x28,0x44},//[x]=(120)
{0x00,0x4C,0x50,0x3C,0x00},//[y]=(121)
{0x44,0x64,0x54,0x4C,0x44},//[z]=(122)
{0x00,0x08,0x36,0x41,0x00},//[{]=(123)
{0x00,0x00,0x7F,0x00,0x00},//[|]=(124)
{0x00,0x41,0x36,0x08,0x00},//[}]=(125)
{0x02,0x01,0x02,0x04,0x02},//[~]=(126)
{0x00,0x00,0x00,0x00,0x00},//[]=(127)
{0x00,0x00,0x00,0x00,0x00},//[�]=(128)
{0x00,0x00,0x00,0x00,0x00},//[�]=(129)
{0x00,0x00,0x00,0x00,0x00},//[�]=(130)
{0x00,0x00,0x00,0x00,0x00},//[�]=(131)
{0x00,0x00,0x00,0x00,0x00},//[�]=(132)
{0x00,0x00,0x00,0x00,0x00},//[�]=(133)
{0x00,0x00,0x00,0x00,0x00},//[�]=(134)
{0x00,0x00,0x00,0x00,0x00},//[�]=(135)
{0x00,0x00,0x00,0x00,0x00},//[�]=(136)
{0x00,0x00,0x00,0x00,0x00},//[�]=(137)
{0x00,0x00,0x00,0x00,0x00},//[�]=(138)
{0x00,0x00,0x00,0x00,0x00},//[�]=(139)
{0x00,0x00,0x00,0x00,0x00},//[�]=(140)
{0x00,0x00,0x00,0x00,0x00},//[�]=(141)
{0x00,0x00,0x00,0x00,0x00},//[�]=(142)
{0x00,0x00,0x00,0x00,0x00},//[�]=(143)
{0x00,0x00,0x00,0x00,0x00},//[�]=(144)
{0x00,0x00,0x00,0x00,0x00},//[�]=(145)
{0x00,0x00,0x00,0x00,0x00},//[�]=(146)
{0x00,0x00,0x00,0x00,0x00},//[�]=(147)
{0x00,0x00,0x00,0x00,0x00},//[�]=(148)
{0x00,0x00,0x00,0x00,0x00},//[�]=(149)
{0x00,0x00,0x00,0x00,0x00},//[�]=(150)
{0x00,0x00,0x00,0x00,0x00},//[�]=(151)
{0x00,0x00,0x00,0x00,0x00},//[?]=(152)
{0x00,0x00,0x00,0x00,0x00},//[�]=(153)
{0x00,0x00,0x00,0x00,0x00},//[�]=(154)
{0x00,0x00,0x00,0x00,0x00},//[�]=(155)
{0x00,0x00,0x00,0x00,0x00},//[�]=(156)
{0x00,0x00,0x00,0x00,0x00},//[�]=(157)
{0x00,0x00,0x00,0x00,0x00},//[�]=(158)
{0x00,0x00,0x00,0x00,0x00},//[�]=(159)
{0x00,0x00,0x00,0x00,0x00},//[�]=(160)
{0x00,0x00,0x00,0x00,0x00},//[�]=(161)
{0x00,0x00,0x00,0x00,0x00},//[�]=(162)
{0x00,0x00,0x00,0x00,0x00},//[�]=(163)
{0x00,0x00,0x00,0x00,0x00},//[�]=(164)
{0x00,0x00,0x00,0x00,0x00},//[�]=(165)
{0x00,0x00,0x00,0x00,0x00},//[�]=(166)
{0x00,0x4A,0x55,0x29,0x00},//[�]=(167)
{0x7C,0x55,0x54,0x55,0x54},//[�]=(168)
{0x00,0x00,0x00,0x00,0x00},//[�]=(169)
{0x3E,0x49,0x49,0x49,0x22},//[�]=(170)
{0x08,0x14,0x22,0x08,0x14},//[�]=(171)
{0x04,0x04,0x04,0x04,0x0C},//[�]=(172)
{0x00,0x08,0x08,0x08,0x00},//[�]=(173)
{0x00,0x00,0x00,0x00,0x00},//[�]=(174)
{0x00,0x01,0x7C,0x01,0x00},//[�]=(175)
{0x00,0x02,0x05,0x02,0x00},//[�]=(176)
{0x00,0x24,0x2E,0x24,0x00},//[�]=(177)
{0x00,0x00,0x7F,0x00,0x00},//[�]=(178)
{0x00,0x00,0x00,0x00,0x00},//[�]=(179)
{0x00,0x00,0x00,0x00,0x00},//[�]=(180)
{0x00,0x00,0x00,0x00,0x00},//[�]=(181)
{0x06,0x0F,0x7F,0x01,0x7F},//[�]=(182)
{0x00,0x00,0x02,0x00,0x00},//[�]=(183)
{0x38,0x55,0x54,0x19,0x00},//[�]=(184)
{0x00,0x00,0x00,0x00,0x00},//[�]=(185)
{0x38,0x54,0x54,0x44,0x00},//[�]=(186)
{0x14,0x08,0x22,0x14,0x08},//[�]=(187)
{0x00,0x00,0x7A,0x00,0x00},//[�]=(188)
{0x26,0x49,0x49,0x49,0x32},//[�]=(189)
{0x00,0x08,0x54,0x54,0x20},//[�]=(190)
{0x00,0x00,0x74,0x00,0x00},//[�]=(191)
{0x7E,0x11,0x11,0x11,0x7E},//[�]=(192)
{0x7F,0x49,0x49,0x49,0x31},//[�]=(193)
{0x7F,0x49,0x49,0x49,0x36},//[�]=(194)
{0x7F,0x01,0x01,0x01,0x03},//[�]=(195)
{0x60,0x3E,0x21,0x21,0x7F},//[�]=(196)
{0x7F,0x49,0x49,0x49,0x49},//[�]=(197)
{0x77,0x08,0x7F,0x08,0x77},//[�]=(198)
{0x22,0x41,0x49,0x49,0x36},//[�]=(199)
{0x7F,0x10,0x08,0x04,0x7F},//[�]=(200)
{0x7F,0x10,0x09,0x04,0x7F},//[�]=(201)
{0x7F,0x08,0x14,0x22,0x41},//[�]=(202)
{0x20,0x40,0x3F,0x01,0x7F},//[�]=(203)
{0x7F,0x02,0x0C,0x02,0x7F},//[�]=(204)
{0x7F,0x08,0x08,0x08,0x7F},//[�]=(205)
{0x3E,0x41,0x41,0x41,0x3E},//[�]=(206)
{0x7F,0x01,0x01,0x01,0x7F},//[�]=(207)
{0x7F,0x09,0x09,0x09,0x06},//[�]=(208)
{0x3E,0x41,0x41,0x41,0x22},//[�]=(209)
{0x01,0x01,0x7F,0x01,0x01},//[�]=(210)
{0x27,0x48,0x48,0x3F,0x00},//[�]=(211)
{0x0E,0x11,0x7F,0x11,0x0E},//[�]=(212)
{0x63,0x14,0x08,0x14,0x63},//[�]=(213)
{0x3F,0x20,0x20,0x3F,0x60},//[�]=(214)
{0x0F,0x08,0x08,0x7F,0x00},//[�]=(215)
{0x7F,0x40,0x7F,0x40,0x7F},//[�]=(216)
{0x3F,0x20,0x3F,0x20,0x7F},//[�]=(217)
{0x01,0x7F,0x48,0x48,0x30},//[�]=(218)
{0x7F,0x48,0x30,0x00,0x7F},//[�]=(219)
{0x7F,0x48,0x48,0x30,0x00},//[�]=(220)
{0x22,0x41,0x49,0x49,0x3E},//[�]=(221)
{0x7F,0x08,0x3E,0x41,0x3E},//[�]=(222)
{0x46,0x29,0x19,0x09,0x7F},//[�]=(223)
{0x00,0x20,0x54,0x54,0x78},//[�]=(224)
{0x3C,0x4A,0x49,0x30,0x00},//[�]=(225)
{0x7C,0x54,0x54,0x28,0x00},//[�]=(226)
{0x00,0x7C,0x04,0x04,0x00},//[�]=(227)
{0x60,0x38,0x24,0x24,0x7C},//[�]=(228)
{0x38,0x54,0x54,0x18,0x00},//[�]=(229)
{0x6C,0x10,0x7C,0x10,0x6C},//[�]=(230)
{0x00,0x44,0x54,0x28,0x00},//[�]=(231)
{0x7C,0x20,0x10,0x08,0x7C},//[�]=(232)
{0x7C,0x21,0x11,0x09,0x7C},//[�]=(233)
{0x7C,0x10,0x28,0x44,0x00},//[�]=(234)
{0x40,0x3C,0x04,0x7C,0x00},//[�]=(235)
{0x7C,0x08,0x10,0x08,0x7C},//[�]=(236)
{0x7C,0x10,0x10,0x7C,0x00},//[�]=(237)
{0x38,0x44,0x44,0x38,0x00},//[�]=(238)
{0x7C,0x04,0x04,0x7C,0x00},//[�]=(239)
{0x7C,0x24,0x24,0x18,0x00},//[�]=(240)
{0x00,0x38,0x44,0x44,0x00},//[�]=(241)
{0x04,0x04,0x7C,0x04,0x04},//[�]=(242)
{0x00,0x4C,0x50,0x3C,0x00},//[�]=(243)
{0x18,0x24,0x7C,0x24,0x18},//[�]=(244)
{0x44,0x28,0x10,0x28,0x44},//[�]=(245)
{0x3C,0x20,0x20,0x3C,0x60},//[�]=(246)
{0x00,0x1C,0x10,0x7C,0x00},//[�]=(247)
{0x7C,0x40,0x7C,0x40,0x7C},//[�]=(248)
{0x3C,0x20,0x3C,0x20,0x7C},//[�]=(249)
{0x04,0x7C,0x50,0x70,0x00},//[�]=(250)
{0x7C,0x50,0x70,0x00,0x7C},//[�]=(251)
{0x00,0x7C,0x50,0x70,0x00},//[�]=(252)
{0x00,0x54,0x54,0x38,0x00},//[�]=(253)
{0x7C,0x10,0x7C,0x44,0x7C},//[�]=(254)
{0x48,0x34,0x14,0x7C,0x00} //[�]=(255)
};
// ��������� ������ ������� 1
const uint8  battary_2[6][20] =
{
    0xFF, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0xC3, 0x3C, 0x00, // 0
    0xFF, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0x81, 0x81, 0x81, 0xC3, 0x3C, 0x00, // 1 
    0xFF, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xC3, 0x3C, 0x00, // 2
    0xFF, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xC3, 0x3C, 0x00, // 3 
    0xFF, 0x81, 0xBD, 0xBD, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xC3, 0x3C, 0x00, // 4 
    0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xC3, 0x3C, 0x00  // 5 
};
const unsigned char  gamer[66] =
{
    0x00, 0x0C, 0x00, 0x12, 0x00, 0x22, 0x00, 0x21, 0x80, 0x41, 0x80, 0x5C, 0x40, 0x54, 0x40, 0x5C, 0xE0, 0x40, 0x18, 0x81, 
    0x04, 0xB9, 0x02, 0xA9, 0x02, 0xB9, 0x49, 0x82, 0x8D, 0x82, 0xA1, 0xBA, 0xB1, 0xAA, 0xA1, 0xBA, 0x8D, 0x82, 0x49, 0x82, 
    0x02, 0xB9, 0x02, 0xA9, 0x04, 0xB9, 0x18, 0x81, 0xE0, 0x40, 0x40, 0x5C, 0x40, 0x54, 0x80, 0x5C, 0xC0, 0x41, 0x40, 0x21, 
    0x40, 0x22, 0xE0, 0x12, 0xA0, 0x0C
};
const tSprite gamer_sprite = {2, 33, gamer, COLUMNS_FIRST};

const unsigned char  gamer_gasmask[66] =
{
    0x00, 0x0C, 0x00, 0x12, 0x00, 0x22, 0x00, 0x21, 0x80, 0x41, 0x80, 0x5C, 0x40, 0x54, 0x40, 0x5C, 0xE0, 0x40, 0xF8, 0x81, 
    0xFC, 0xBB, 0x3E, 0xAA, 0xFE, 0xBB, 0x33, 0x82, 0xFB, 0x83, 0xDF, 0xB9, 0xCF, 0xA9, 0xDF, 0xB9, 0xF3, 0x83, 0x3B, 0x82, 
    0xFE, 0xBB, 0x3E, 0xAA, 0xFC, 0xBB, 0xF8, 0x81, 0xE0, 0x40, 0x40, 0x5C, 0x40, 0x54, 0x80, 0x5C, 0xC0, 0x41, 0x40, 0x21, 
    0x40, 0x22, 0xE0, 0x12, 0xA0, 0x0C
};
const tSprite gamer_gas_sprite = {2, 33, gamer_gasmask, COLUMNS_FIRST};

const unsigned char gamer_dead_0[66] =
{
    0x00, 0x0F, 0x02, 0x70, 0x06, 0x00, 0x40, 0x10, 0x40, 0x32, 0x80, 0xC2, 0x10, 0x09, 0x32, 0x15, 0x22, 0x49, 0x06, 0x81,
    0x04, 0xB0, 0xC2, 0x28, 0x01, 0x19, 0x15, 0x83, 0x09, 0x82, 0x95, 0xB2, 0x81, 0xAA, 0x95, 0x9A, 0x89, 0x82, 0x15, 0x82,
    0x01, 0x13, 0x02, 0x29, 0xC2, 0x38, 0x02, 0x01, 0x02, 0x01, 0x11, 0x89, 0x60, 0x54, 0x80, 0x0C, 0x88, 0x01, 0x04, 0x21,
    0x83, 0x60, 0x84, 0x80, 0x02, 0x00
};
const tSprite gamer_dead_0_sprite = {2, 33, gamer_dead_0, COLUMNS_FIRST};

const unsigned char gamer_dead_1[66] =
{
    0x06, 0x0F, 0x03, 0x70, 0x61, 0x00, 0x40, 0x10, 0x00, 0x10, 0x00, 0x46, 0x10, 0x04, 0x32, 0x01, 0x20, 0x48, 0x00, 0x80,
    0x00, 0xB0, 0x00, 0x20, 0x01, 0x10, 0x15, 0x81, 0x00, 0x81, 0x04, 0xB0, 0x00, 0xA0, 0x04, 0x90, 0x40, 0x80, 0x05, 0x81,
    0x01, 0x00, 0x02, 0x28, 0x40, 0x20, 0x00, 0x00, 0x02, 0x00, 0x01, 0x81, 0x00, 0x40, 0x00, 0x02, 0x80, 0x00, 0x00, 0x20,
    0x03, 0x20, 0x04, 0x80, 0x82, 0x99
};    
const tSprite gamer_dead_1_sprite = {2, 33, gamer_dead_1, COLUMNS_FIRST};

const uint8  gamer_bullet[4] =
{
    0x40, 0x40, 0x40, 0x40  
};
const tSprite bullet_sprite = {1, 4, gamer_bullet, COLUMNS_FIRST};

const uint8  evilstar[56] =
{
   0xC0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x30, 0x0C, 0x62, 0x01, 0x62, 0x0C, 0x30, 0x40, 0x40, 0x40, 0x40, 0x40, 0xC0, 0x10, 
   0x90, 0x88, 0x88, 0x48, 0x48, 0x48, 0x24, 0x24, 0x00, 0x01, 0xC2, 0xA4, 0x98, 0x86, 0x49, 0x2D, 0x29, 0x2B, 0x29, 0x2D, 
   0x49, 0x86, 0x98, 0xA4, 0xC2, 0x01, 0x04, 0x04, 0x04, 0x08, 0x08, 0x08, 0x12, 0x12, 0x12, 0x12
};
const tSprite evilstar_sprite = {2, 28, evilstar, LINES_FIRST};

const uint8  distr_evilstar[56] =
{
    0xC0, 0x41, 0x46, 0x44, 0x44, 0x00, 0x00, 0x0C, 0x02, 0x01, 0x02, 0x0C, 0x00, 0x00, 0x00, 0x40, 0x46, 0x40, 0xC0, 0x00, 
    0x00, 0x00, 0x08, 0x08, 0x12, 0x08, 0x04, 0x04, 0x00, 0x09, 0xCC, 0xA0, 0x80, 0x84, 0x00, 0x05, 0x01, 0x08, 0x08, 0x05, 
    0x49, 0x86, 0x80, 0xA0, 0xC2, 0x01, 0x04, 0x34, 0x20, 0x00, 0x00, 0x08, 0x08, 0x12, 0x12, 0x12 
};
const tSprite distr_evilstar_sprite = {2, 28, distr_evilstar, LINES_FIRST};

// 64x56(7 pages)
const unsigned char Magazin[448] = {
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X01,0X08,0X00,0X00,0X40,0X00,0X80,0X01,0X10,
0X00,0X00,0X40,0X00,0X80,0X01,0X10,0X00,0X00,0X40,0X00,0X80,0X01,0X10,0X00,0X00,
0X40,0XC1,0X81,0X01,0X10,0X80,0X00,0X40,0XF2,0X87,0X01,0X08,0X80,0X00,0X40,0X32,
0X86,0X01,0X06,0X80,0X00,0X40,0X5A,0X8D,0X01,0X06,0XE0,0X7F,0X40,0X9C,0X8C,0X01,
0X88,0XFF,0X80,0X40,0X58,0X8D,0X01,0XD0,0XFF,0X0C,0X41,0X30,0X86,0X01,0XD0,0XFF,
0X12,0X7E,0XF0,0X87,0X01,0XD0,0XFF,0X9A,0X44,0XC0,0X81,0X01,0XD0,0XED,0X0C,0X49,
0X00,0X80,0X01,0XC8,0XE0,0X00,0X49,0X00,0X80,0X01,0XC6,0XFF,0X0C,0X49,0X00,0X80,
0X01,0XC6,0XFF,0X92,0X44,0X00,0X83,0X01,0XC8,0XFF,0X1A,0X42,0XBC,0X87,0X01,0XD0,
0XFF,0X0C,0X7F,0XFE,0X8C,0X01,0X90,0XFF,0X80,0X40,0XF3,0X8F,0X01,0X10,0XE0,0X7F,
0X40,0XE1,0X8C,0X01,0X10,0X80,0X00,0X40,0XE1,0X87,0X01,0X08,0X80,0X00,0X40,0XF3,
0X83,0X01,0X06,0X80,0X10,0X40,0XFF,0X83,0X01,0X06,0X00,0X28,0X40,0XF3,0X83,0X01,
0X08,0X00,0X44,0X40,0XE1,0X87,0X01,0X10,0X00,0X82,0X40,0XE1,0X8C,0X01,0X10,0X00,
0X01,0X41,0XF3,0X8F,0X01,0X90,0XFF,0X00,0X42,0XFE,0X8C,0X01,0X50,0X00,0X00,0X42,
0XBC,0X87,0X01,0X48,0X00,0X00,0X42,0X00,0X83,0X01,0X46,0X00,0X00,0X42,0X00,0X80,
0X01,0X46,0X00,0X00,0X42,0X00,0X80,0X01,0X48,0X00,0X00,0X42,0X00,0X80,0X01,0X50,
0X00,0X00,0X42,0X00,0X80,0X01,0X50,0X00,0X00,0X42,0XFF,0X8F,0X01,0X50,0X00,0X00,
0X42,0XFF,0X8F,0X01,0X50,0X00,0X00,0X42,0X03,0X88,0X01,0X48,0X00,0X00,0X42,0XF9,
0X8B,0X01,0X46,0X00,0X00,0X42,0X8D,0X8B,0X01,0X46,0X00,0X00,0X42,0XC5,0X8B,0X01,
0X48,0X00,0X00,0X42,0XED,0X8B,0X01,0X50,0X00,0X00,0X42,0XF9,0X8B,0X01,0X50,0X00,
0X00,0X42,0X03,0X88,0X01,0X50,0X00,0X00,0X42,0XFF,0X8F,0X01,0X50,0X00,0X00,0X42,
0XFF,0X8F,0X01,0X48,0X00,0X00,0X42,0X00,0X80,0X01,0X46,0X00,0X00,0X42,0X00,0X80,
0X01,0X46,0X00,0X00,0X42,0X00,0X80,0X01,0X48,0X00,0X00,0X42,0XFF,0X8F,0X01,0X50,
0X00,0X00,0X42,0XFB,0X8B,0X01,0X50,0X00,0X00,0X42,0X1F,0X8F,0X01,0X50,0X00,0X00,
0X42,0X1F,0X8F,0X01,0X50,0X00,0X00,0X42,0X07,0X8C,0X01,0X48,0X00,0X00,0X42,0X07,
0X8C,0X01,0X46,0X00,0X00,0X42,0X07,0X8C,0X01,0X46,0X00,0X00,0X42,0X1F,0X8F,0X01,
0X48,0X00,0X00,0X42,0X1F,0X8F,0X01,0X50,0X00,0X00,0X42,0XFB,0X8B,0X01,0X90,0XFF,
0XFF,0X41,0XFF,0X8F,0X01,0X10,0X00,0X00,0X40,0X00,0X80,0X01,0X10,0X00,0X00,0X40,
0X00,0X80,0X01,0X08,0X00,0X00,0X40,0X00,0X80,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};
const tSprite magazin_sprite = {7, 64, Magazin, COLUMNS_FIRST};

//minimagazin 34x28
const unsigned char minimag[160] = {
0X1E,0X00,0X00,0X00,0XF1,0XFF,0XFF,0X0F,0X11,0X00,0X04,0X08,0X19,0X3E,0X04,0X08,
0X09,0X04,0X04,0X08,0X09,0X08,0XCC,0X09,0X11,0X04,0X2C,0X0A,0X11,0X3E,0X34,0X0A,
0X11,0X00,0X24,0X0A,0X09,0X3C,0XC4,0X09,0X09,0X12,0X04,0X08,0X09,0X12,0X04,0X08,
0X11,0X3C,0XE4,0X09,0X11,0X00,0XD4,0X0B,0X11,0X3E,0XC4,0X09,0X09,0X02,0XF4,0X09,
0X09,0X02,0XC4,0X09,0X09,0X02,0XD4,0X0B,0X11,0X00,0XE4,0X09,0X11,0X3C,0X04,0X08,
0X11,0X12,0X04,0X08,0X09,0X12,0XF4,0X0B,0X09,0X3C,0X14,0X0A,0X09,0X00,0XBC,0X0B,
0X11,0X2A,0XFC,0X0B,0X11,0X2A,0X14,0X0A,0X11,0X36,0XF4,0X0B,0X09,0X00,0X04,0X08,
0X09,0X3E,0XF4,0X0B,0X09,0X10,0X34,0X0B,0X11,0X08,0X14,0X0A,0X11,0X3E,0X14,0X0A,
0X11,0X00,0X34,0X0B,0X09,0X3E,0XF4,0X0B,0X09,0X08,0X04,0X08,0X09,0X08,0X04,0X08,
0X11,0X3E,0X04,0X08,0X11,0X00,0X04,0X08,0XF1,0XFF,0XFF,0X0F,0X1E,0X00,0X00,0X00,
};
const tSprite minimag_sprite = {4, 40, minimag, COLUMNS_FIRST};

const unsigned char GameStatusBar[128] = { /* 0X21,0X01,0X80,0X00,0X08,0X00, */
0XFF,0XE7,0XE7,0X81,0X81,0XE7,0XE7,0XFF,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,
0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,
0X81,0X81,0XFF,0X00,0X00,0X00,0X00,0X00,0X3C,0X42,0X81,0XA5,0XBF,0X81,0X42,0X3C,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X71,0XD9,0XAE,0XD8,0X70,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0XC1,
0XD5,0XD5,0XDD,0XFF,0XFF,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,
0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0X81,0XFF,
};
const tSprite gamestatbar_sprite = {1, 128, GameStatusBar, COLUMNS_FIRST};

const unsigned char bomb[4][8] = {
0X00,0X00,0X71,0XD9,0XAE,0XD8,0X70,0X00,
0X38,0X6C,0X54,0X6C,0X38,0X10,0X10,0X0C,
0X00,0X0E,0X1B,0X75,0X9B,0X8E,0X00,0X00,
0X30,0X08,0X08,0X1C,0X36,0X2A,0X36,0X1C,
};
const tSprite bomb_sprite[4] = {1, 8, bomb[0], COLUMNS_FIRST,
                                1, 8, bomb[1], COLUMNS_FIRST,
                                1, 8, bomb[2], COLUMNS_FIRST,
                                1, 8, bomb[3], COLUMNS_FIRST,
};

const unsigned char BombShards[3][200] = {
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1C,0X00,0X00,0X00,
0X00,0X36,0X00,0X00,0X00,0X00,0X2A,0X00,0X00,0X00,0X00,0X36,0X00,0X00,0X00,0X00,
0X1C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X20,0X00,0X01,0X00,0X00,0X30,0X08,0X03,
0X00,0X00,0X60,0X18,0X06,0X00,0X00,0X80,0X18,0X04,0X00,0X00,0X00,0X18,0X00,0X00,
0X00,0X00,0X3C,0X00,0X00,0X00,0X00,0X3C,0X00,0X00,0X00,0X00,0XFF,0X00,0X00,0X00,
0XF0,0XFF,0X0F,0X00,0X00,0XE0,0XFF,0X07,0X00,0X00,0X00,0XFF,0X00,0X00,0X00,0X00,
0X3C,0X00,0X00,0X00,0X00,0X3C,0X00,0X00,0X00,0X00,0X18,0X01,0X00,0X00,0X10,0X18,
0X03,0X00,0X00,0X18,0X18,0X06,0X00,0X00,0X30,0X08,0X04,0X00,0X00,0X40,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X04,0X00,0X01,0X00,0X03,0X04,0XC0,0X00,0X00,0X06,0X04,0XF0,0X00,0X08,
0X0A,0X0E,0X70,0X00,0X10,0X00,0X0E,0X30,0X00,0X30,0X00,0X0F,0X00,0X08,0X30,0X00,
0X07,0X00,0X08,0X60,0X00,0X0B,0X00,0X04,0XE0,0X00,0X09,0X00,0X07,0XE0,0X41,0X1C,
0X82,0X07,0XE0,0XC1,0X9D,0X83,0X03,0XC0,0XC0,0XFF,0X83,0X03,0X40,0XC0,0XFF,0X83,
0X01,0X00,0XC0,0XFF,0X83,0X01,0X00,0XC0,0XFF,0X03,0X00,0X00,0XC0,0XFF,0X03,0X00,
0X04,0XF0,0XFF,0X0F,0X00,0X07,0XFC,0XFF,0X3F,0X00,0X8F,0XFF,0XFF,0XFF,0X20,0X18,
0XFF,0XFF,0X7F,0X60,0X00,0XFC,0XFF,0X3F,0X70,0X00,0XF0,0XFF,0X0F,0XE0,0X00,0XC0,
0XFF,0X03,0X80,0X00,0XC0,0XFF,0X03,0X00,0X00,0XC0,0XFF,0X83,0X00,0X00,0XC1,0XFF,
0X83,0X01,0X80,0XC3,0XFF,0XC3,0X03,0X80,0XC7,0X9D,0XC3,0X03,0XC0,0X4F,0X1C,0X82,
0X07,0XC0,0X03,0X08,0X00,0X0E,0XE0,0X01,0X08,0X00,0X18,0X60,0X00,0X1C,0X00,0X00,
0X20,0X00,0X1C,0X00,0X00,0X10,0X00,0X1E,0X00,0X00,0X10,0X00,0X1F,0X80,0X00,0X08,
0X02,0X1E,0XC0,0X01,0X00,0X02,0X0C,0XE0,0X01,0X00,0X03,0X0C,0X00,0X03,0X00,0X03,
0X08,0X00,0X04,0X80,0X01,0X08,0X00,0X00,
};
const tSprite bombshards_sprite[3] = {5, 40, BombShards[0], COLUMNS_FIRST,
                                      5, 40, BombShards[1], COLUMNS_FIRST,
                                      5, 40, BombShards[2], COLUMNS_FIRST,
};

const unsigned char coin[8] = {
0X3C,0X42,0X81,0XA5,0XBF,0X81,0X42,0X3C,};
const tSprite coin_sprite = {1, 8, coin, COLUMNS_FIRST};

const uint8  bright_icon[8] =
{ 0x1F, 0x18, 0x36, 0xF3, 0xC8, 0xA4, 0xB2, 0x91}; // brightness icon
const tSprite bright_icon_sprite = {1, 8, bright_icon, COLUMNS_FIRST};

const unsigned char smallstar[6][8] = {
0X00,0X00,0X00,0X08,0X00,0X00,0X00,0X00,
0X00,0X00,0X08,0X1C,0X08,0X00,0X00,0X00,
0X00,0X08,0X1C,0X3E,0X1C,0X08,0X00,0X00,
0X00,0X2A,0X1C,0X3E,0X1C,0X2A,0X00,0X00,
0X08,0X2A,0X1C,0X7F,0X1C,0X2A,0X08,0X00,
0X08,0X2A,0X1C,0XFF,0X1C,0X2A,0X08,0X08,};

const tSprite smallstar_sprite[6] = {1, 8, smallstar[0], COLUMNS_FIRST,
                                     1, 8, smallstar[1], COLUMNS_FIRST,
                                     1, 8, smallstar[2], COLUMNS_FIRST,
                                     1, 8, smallstar[3], COLUMNS_FIRST,
                                     1, 8, smallstar[4], COLUMNS_FIRST,
                                     1, 8, smallstar[5], COLUMNS_FIRST};




const uint8  bright_lvl[8][15] =
{
    0xBD, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, // 
    0xBD, 0x81, 0xBD, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, // 
    0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, // 
    0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, // 
    0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, //  
    0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0x81, 0x81, 0x81, //  
    0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0x81, //  
    0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0xBD, 0x81, 0xBD  //  
};

const uint8  menu_pointer[8] =
{
    0xFF, 0xFF, 0x7E, 0x7E, 0x3C, 0x3C, 0x18, 0x18
};
const tSprite menu_pointer_sprite = {8, 1, menu_pointer, COLUMNS_FIRST};

const uint8  but_sel_hint[8][128] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA0, 0x0B, 0xD0, 0x05, 0x50, 0x14, 0x28, 0x0A, 0x50, 0x14, 0x28, 0x0A, 0x50, 0x14, 0x28, 0x0A, 0xA0, 0x0B, 0xD0, 0x05, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA0, 0x0B, 0xD0, 0x85, 0x50, 0x14, 0xE8, 0xCB, 0x50, 0x14, 0xE8, 0xEB, 0x50, 0x14, 0xE8, 0xCB, 0xA0, 0x0B, 0xD0, 0x85, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA0, 0x0B, 0xD0, 0x85, 0x50, 0x14, 0xE8, 0xCB, 0x50, 0x14, 0xE8, 0xEB, 0x50, 0x14, 0xE8, 0xCB, 0xA0, 0x0B, 0xD0, 0x85, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA0, 0x0B, 0xD0, 0x05, 0x50, 0x14, 0x28, 0x0A, 0x50, 0x14, 0x28, 0x0A, 0x50, 0x14, 0x28, 0x0A, 0xA0, 0x0B, 0xD0, 0x05, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA0, 0x0B, 0xD0, 0x05, 0x50, 0x14, 0x28, 0x0A, 0x50, 0x14, 0x28, 0x0A, 0x50, 0x14, 0x28, 0x0A, 0xA0, 0x0B, 0xD0, 0x05, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA1, 0x0B, 0xD0, 0x05, 0xD3, 0x17, 0x28, 0x0A, 0xD7, 0x17, 0x28, 0x0A, 0xD3, 0x17, 0x28, 0x0A, 0xA1, 0x0B, 0xD0, 0x05, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA1, 0x0B, 0xD0, 0x05, 0xD3, 0x17, 0x28, 0x0A, 0xD7, 0x17, 0x28, 0x0A, 0xD3, 0x17, 0x28, 0x0A, 0xA1, 0x0B, 0xD0, 0x05, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA0, 0x0B, 0xD0, 0x05, 0x50, 0x14, 0x28, 0x0A, 0x50, 0x14, 0x28, 0x0A, 0x50, 0x14, 0x28, 0x0A, 0xA0, 0x0B, 0xD0, 0x05, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA1, 0x0B, 0xD0, 0x85, 0xD3, 0x17, 0xE8, 0xCB, 0xD7, 0x17, 0xE8, 0xEB, 0xD3, 0x17, 0xE8, 0xCB, 0xA1, 0x0B, 0xD0, 0x85, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA1, 0x0B, 0xD0, 0x05, 0xD3, 0x17, 0x28, 0x0A, 0xD7, 0x17, 0x28, 0x0A, 0xD3, 0x17, 0x28, 0x0A, 0xA1, 0x0B, 0xD0, 0x05, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA0, 0x0B, 0xD0, 0x85, 0x50, 0x14, 0xE8, 0xCB, 0x50, 0x14, 0xE8, 0xEB, 0x50, 0x14, 0xE8, 0xCB, 0xA0, 0x0B, 0xD0, 0x85, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA0, 0x0B, 0xD0, 0x85, 0x50, 0x14, 0xE8, 0xCB, 0x50, 0x14, 0xE8, 0xEB, 0x50, 0x14, 0xE8, 0xCB, 0xA0, 0x0B, 0xD0, 0x85, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA1, 0x0B, 0xD0, 0x85, 0xD3, 0x17, 0xE8, 0xCB, 0xD7, 0x17, 0xE8, 0xEB, 0xD3, 0x17, 0xE8, 0xCB, 0xA1, 0x0B, 0xD0, 0x85, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA1, 0x0B, 0xD0, 0x85, 0xD3, 0x17, 0xE8, 0xCB, 0xD7, 0x17, 0xE8, 0xEB, 0xD3, 0x17, 0xE8, 0xCB, 0xA1, 0x0B, 0xD0, 0x85, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x03, 0x00, 0x00, 0x8F, 0x03, 0x00, 0x00, 0xCF, 0x02, 0x00, 0x80, 0x4D, 0x02, 0x00, 0x80, 0x7D, 0x03, 0x00, 0x80, 0x7D, 0x03, 0x00, 0x80, 0x7D, 0x03, 0x00, 0x80, 0x7D, 0x03, 0x00, 0x80, 0x4D, 0x02, 0x00, 0x00, 0xCF, 0x02, 0x00, 0x00, 0x8F, 0x03, 0x00, 0x00, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8  weekday[7][3] = 
{
  "��", "��", "��", "��", "��", "��", "��"
};

const uint8  month[12][4] = 
{
  "���", "���", "���", "���", "���", "���", "���", "���", "���", "���", "���", "���"
};

const uint8 gamestory_string[12][150] =  
{
  "\n\n    ������-�����\n  � �������-�������\n     ���������...",
  "������, ������������\n�������������� ��\n���� ������ ��������,\n� ��� ��� ���������\n���� ������. �����\n������, ��� ������.\n� ����� ���������.",
  "� ������\n��������������\n�������� �� ��� ��\n�� �� ����� ��������\n���� ���� �����,\n����� �� ��� ��������\n��������...",
  "\n\n\n������������� �������",
  "����������������\n�� ���� ����������\n������-�������� �\n���������� �����.",
  "",
  "",
  "",
  "",
  "",
  "",
  ""
};
#endif