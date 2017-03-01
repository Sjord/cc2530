// Source code under CC0 1.0
#include <stdbool.h>

__sfr __at(0x80) P0;        // port 0
__sfr __at(0xf3) P0SEL;     // port 0 function select (0 = GPIO)
__sfr __at(0xfd) P0DIR;     // port 0 direction (0 = output)

__sfr __at(0x90) P1;        // port 1
__sfr __at(0xf5) P1SEL;     // port 1 function select (0 = GPIO)
__sfr __at(0xfe) P1DIR;     // port 1 direction (1 = output)

__sfr __at(0xa5) P1MDOUT;
__sfr __at(0xe2) XBR1;
__sfr __at(0xd9) PCA0MD;

__sfr __at(0x88) TCON;
__sfr __at(0x89) TMOD;
__sfr __at(0x8a) TL0;
__sfr __at(0x8c) TH0;

__sfr __at(0xa8) IE;

volatile unsigned long int clocktime;
volatile _Bool clockupdate;

void clockinc(void) __interrupt(1)
{
	TH0 = (65536 - 125) / 256;
	TL0 = (65536 - 125) % 256;
	clocktime++;
	clockupdate = true;
}

unsigned long int clock(void)
{
	unsigned long int ctmp;

	do
	{
		clockupdate = false;
		ctmp = clocktime;
	} while (clockupdate);

	return(ctmp);
}

unsigned char _sdcc_external_startup(void)
{
	PCA0MD = 0; // Disable watchdog timer

    return 0; // perform normal initialization
}

void main(void)
{
    unsigned long int i;
    P0DIR = 0xff;

    while (1) {
        P0 = 1 << 2;
        for (i = 0; i < 100000; i++) ;
        P0 = 1 << 3;
        for (i = 0; i < 100000; i++) ;
    }

    return;
	// Enable port push-pull output
	XBR1 = 0x40;
	P1MDOUT = 0xff;

	// Configure timer for 1.5 Mhz default SYSCLK
	// 1000 ticks per second
	TH0 = (65536 - 125) / 256;
	TL0 = (65536 - 125) % 256;
	TMOD = 0x01;
	IE |= 0x82;
	TCON |= 0x10; // Start timer

	for(;;)
		P1 = (clock() / 1000);
}
