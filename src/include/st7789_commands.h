#ifndef _ST7789_COMMAND_H_
#define _ST7789_COMMAND_H_

#include "types.h"

#define SWRESET 0x01
#define DISPOFF 0x28
#define DISPON 0x29
#define SLPIN 0x10
#define SLPOUT 0x11
#define CASET 0x2A
#define RASET 0x2B
#define RAMWR 0x2C
#define IDMOFF 0x38
#define IDMON 0x39

#define DATA(x) (u8) x | (1 << 7)
#define COLOR(x) DATA(x << 2)

#define SWRESET_DELAY_MSEC 120

#endif
