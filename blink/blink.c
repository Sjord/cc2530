// Source code under CC0 1.0
#include <stdbool.h>

__sfr __at(0x80) P0;        // port 0
__sfr __at(0xf3) P0SEL;     // port 0 function select (0 = GPIO)
__sfr __at(0xfd) P0DIR;     // port 0 direction (0 = output)

__sfr __at(0x90) P1;        // port 1
__sfr __at(0xf5) P1SEL;     // port 1 function select (0 = GPIO)
__sfr __at(0xfe) P1DIR;     // port 1 direction (1 = output)

void main(void)
{
    unsigned long int i;
    P0DIR = 0xff;

    while (1) {
        P0 = 1 << 2;
        for (i = 0; i < 100000; i++) __asm__("NOP");
        P0 = 1 << 3;
        for (i = 0; i < 100000; i++) __asm__("NOP");
    }
}
