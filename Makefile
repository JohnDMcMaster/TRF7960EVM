CC=msp430-gcc
CFLAGS=-DHAVE_STDINT_H -DMSPGCC -Wall

CC_SRCS = 14443.c SPI.c parallel.c anticollision.c automatic.c epc.c hardware.c host.c main.c tiris.c 
OBJECTS = $(CC_SRCS:.c=$(OBJECT_LINKAGE_SUFFIX).o) $(CXX_SRCS:.cpp=$(OBJECT_LINKAGE_SUFFIX).o)
#OBJECTS=14443.o SPI.o parallel.o anticollision.o automatic.o epc.o hardware.o host.o main.o tiris.o

all: depend reader.elf reader.hex reader_loadable.hex

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



MAKEDEPEND=makedepend
MAKEFILE_DEPEND=Makefile.depend$(OBJECT_LINKAGE_SUFFIX)
$(shell touch $(MAKEFILE_DEPEND))
include $(MAKEFILE_DEPEND)

ifdef MAKEDEPEND
# Silicenced because they started to take up a lot of screen during each build
# Ignore cannot find stdio.h stuff
depend: $(DEPEND_DEP)
#$(MAKEDEPEND) -f$(MAKEFILE_DEPEND) -Y $(CCFLAGS) $(CC_SRCS) $(CXX_SRCS)
	@($(MAKEDEPEND) -f$(MAKEFILE_DEPEND) -Y $(CCFLAGS) $(CC_SRCS) $(CXX_SRCS) 2>/dev/null >/dev/null)
#	perl -pi -e 's/[.]o/$(OBJECT_LINKAGE_SUFFIX).o/g' $(MAKEFILE_DEPEND)
#	$(MAKEDEPEND) -f$(MAKEFILE_DEPEND) -Y $(CCFLAGS) $(CC_SRCS) $(CXX_SRCS) 2>/dev/null >/dev/null
# Remove annoying backup
	@($(RM) $(MAKEFILE_DEPEND).bak)
endif

