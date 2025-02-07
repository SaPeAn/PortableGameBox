#ifndef __DISP_DAT_H__
#define __DISP_DAT_H__

// ASCII � ��������� 5�8 ��������
#define CHAR_W	5
#define CHAR_NUM	256
const unsigned char char_8x5[CHAR_NUM][CHAR_W]={
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
const unsigned char  battary_2[6][20] =
{
    0xFF, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0xC3, 0x3C, 0x00, // 0
    0xFF, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0x81, 0x81, 0x81, 0xC3, 0x3C, 0x00, // 1 
    0xFF, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xC3, 0x3C, 0x00, // 2
    0xFF, 0x81, 0xBD, 0xBD, 0x81, 0xBD, 0xBD, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xC3, 0x3C, 0x00, // 3 
    0xFF, 0x81, 0xBD, 0xBD, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xC3, 0x3C, 0x00, // 4 
    0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xC3, 0x3C, 0x00  // 5 
};


const unsigned char  tarelka[2][27] =
{
    0x00, 0x00, 0x80, 0x80, 0xE0, 0x98, 0x84, 0x82, 0x82, 0x91, 0xA5, 0xA1, 0xA1, 0xA5, 0x91, 0x82, 0x82, 0x84, 0x98, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ������ 32  < > 
    0x3E, 0x41, 0x88, 0x80, 0x88, 0x80, 0x88, 0x80, 0x88, 0x80, 0x88, 0x80, 0x88, 0x80, 0x88, 0x80, 0x88, 0x80, 0x88, 0x80, 0x88, 0x41, 0x3E, 0x14, 0x14, 0x14, 0x1C  // ������ 33  <!>  
};

const unsigned char  tar_bullet[8] =
{
    0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00  
};

const unsigned char  cometa[2][28] =
{
   0xC0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x30, 0x0C, 0x62, 0x01, 0x62, 0x0C, 0x30, 0x40, 0x40, 0x40, 0x40, 0x40, 0xC0, 0x10, 0x90, 0x88, 0x88, 0x48, 0x48, 0x48, 0x24, 0x24,
   0x00, 0x01, 0xC2, 0xA4, 0x98, 0x86, 0x49, 0x2D, 0x29, 0x2B, 0x29, 0x2D, 0x49, 0x86, 0x98, 0xA4, 0xC2, 0x01, 0x04, 0x04, 0x04, 0x08, 0x08, 0x08, 0x12, 0x12, 0x12, 0x12
};

const unsigned char  distr_cometa[2][28] =
{
    0xC0, 0x41, 0x46, 0x44, 0x44, 0x00, 0x00, 0x0C, 0x02, 0x01, 0x02, 0x0C, 0x00, 0x00, 0x00, 0x40, 0x46, 0x40, 0xC0, 0x00, 0x00, 0x00, 0x08, 0x08, 0x12, 0x08, 0x04, 0x04,  // ������ 33  <!> 
    0x00, 0x09, 0xCC, 0xA0, 0x80, 0x84, 0x00, 0x05, 0x01, 0x08, 0x08, 0x05, 0x49, 0x86, 0x80, 0xA0, 0xC2, 0x01, 0x04, 0x34, 0x20, 0x00, 0x00, 0x08, 0x08, 0x12, 0x12, 0x12 
};

const unsigned char  bright_icon[8] =
{ 0x1F, 0x18, 0x36, 0xF3, 0xC8, 0xA4, 0xB2, 0x91}; // brightness icon

const unsigned char  bright_lvl[8][15] =
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


const unsigned char  menu_pointer[2][11] =
{
    0xFF, 0xFF, 0xFE, 0xFE, 0x7C, 0x7C, 0x38, 0x38, 0x10, 0x10, 0x00,   
    0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char  but_sel_hint[4][128] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA0, 0x0B, 0xD0, 0x05, 0x50, 0x14, 0x28, 0x0A, 0x50, 0x14, 0x28, 0x0A, 0x50, 0x14, 0x28, 0x0A, 0xA0, 0x0B, 0xD0, 0x05, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA0, 0x8B, 0xD0, 0x85, 0x50, 0x94, 0xE9, 0xCB, 0x50, 0x94, 0xEB, 0xEB, 0x50, 0x94, 0xE9, 0xCB, 0xA0, 0x8B, 0xD0, 0x85, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xE0, 0x03, // ������ 32  < > 
    0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA0, 0x8B, 0xD0, 0x85, 0x50, 0x94, 0xE9, 0xCB, 0x50, 0x94, 0xEB, 0xEB, 0x50, 0x94, 0xE9, 0xCB, 0xA0, 0x8B, 0xD0, 0x85, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA0, 0x0B, 0xD0, 0x05, 0x50, 0x14, 0x28, 0x0A, 0x50, 0x14, 0x28, 0x0A, 0x50, 0x14, 0x28, 0x0A, 0xA0, 0x0B, 0xD0, 0x05, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ������ 33  <!> 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA0, 0x0B, 0xD0, 0x05, 0x50, 0x14, 0x28, 0x0A, 0x50, 0x14, 0x28, 0x0A, 0x50, 0x14, 0x28, 0x0A, 0xA0, 0x0B, 0xD0, 0x05, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x07, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA1, 0x0B, 0xD1, 0x05, 0xD3, 0x97, 0x29, 0x0A, 0xD7, 0xD7, 0x29, 0x0A, 0xD3, 0x97, 0x29, 0x0A, 0xA1, 0x0B, 0xD1, 0x05, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0xC0, 0x07, 0x00, 0x00, // ������ 34  <"> 
    0xC0, 0x07, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA1, 0x0B, 0xD1, 0x05, 0xD3, 0x97, 0x29, 0x0A, 0xD7, 0xD7, 0x29, 0x0A, 0xD3, 0x97, 0x29, 0x0A, 0xA1, 0x0B, 0xD1, 0x05, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0xC0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xC0, 0x01, 0x60, 0x0C, 0x30, 0x06, 0xA0, 0x0B, 0xD0, 0x05, 0x50, 0x14, 0x28, 0x0A, 0x50, 0x14, 0x28, 0x0A, 0x50, 0x14, 0x28, 0x0A, 0xA0, 0x0B, 0xD0, 0x05, 0x60, 0x0C, 0x30, 0x06, 0x80, 0x03, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // ������ 35  <#> 
};

#endif