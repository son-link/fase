#include "defs.h"
#define INIT __asm__ ("call 0xfffc")
#define FRAME \
    __asm               \
        push    ix      \
        call    0xfff1  \
        pop     ix      \
    __endasm;
#define dzx7b(src, dst) \
    __asm               \
        ld      hl, src \
        ld      de, dst \
        call    0xfe80-smooth*0x25f \
    __endasm;
#define tilepaint(from_x, from_y, to_x, to_y) repaint= from_x|from_y<<4|to_x<<8|to_y<<12
unsigned char __at (0x5b00) sprites[12][4];
unsigned char __at (0x5b30) bullets[8][2];
unsigned char __at (0x5b40) tiles[150];
unsigned char __at (0x5c00) screen;
unsigned char __at (0x5c01) shadow;
unsigned int __at (0x5c02) repaint;
__sfr __banked __at 0xf7fe Keyb54321;
__sfr __banked __at 0xfbfe KeybTREWQ;
__sfr __banked __at 0xfdfe KeybGFDSA;
__sfr __banked __at 0xfefe KeybVCXZc;
__sfr __banked __at 0xeffe Keyb67890;
__sfr __banked __at 0xdffe KeybYUIOP;
__sfr __banked __at 0xbffe KeybHJKLe;
__sfr __banked __at 0x7ffe KeybBNMs_;
