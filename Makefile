CC=msp430-gcc
CFLAGS=-DHAVE_STDINT_H -DMSPGCC -Wall

OBJECTS=14443.o SPI.o parallel.o anticollision.o automatic.o epc.o hardware.o host.o main.o tiris.o

all: reader.elf reader.hex reader_loadable.hex

clean:
	rm -f $(OBJECTS) reader.elf reader.hex reader_loadable.elf reader_loadable.hex

download: reader.elf
	msp430-jtag -e -l com5 reader.elf

%.o: %.c
	$(CC) $(CFLAGS) -Os -c -DDCOR=1 -mmcu=msp430x2370 -o $@ $<

%.hex: %.elf
	msp430-objcopy -O ihex $< $@

reader.elf: $(OBJECTS)
	$(CC) -mmcu=msp430x2370 -o $@ $^

reader_loadable.elf: $(OBJECTS)
	$(CC) -mmcu=msp430x2370 -T loadable.x -o $@ $^

#	msp430-gcc -I/usr/msp430/include main.c

