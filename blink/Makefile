blink.bin: blink.ihx
	makebin blink.ihx > blink.bin

blink.hex: blink.ihx
	packihx blink.ihx > blink.hex

blink.ihx: blink.c
	sdcc -mmcs51 blink.c
