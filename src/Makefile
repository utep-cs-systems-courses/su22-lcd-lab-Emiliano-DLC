# makfile configuration

COMMON_OBJECTS  = main.o p2_interrupt_handler.o switches.o #led.o buzzer.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${cpu} -c

all: lcdlab3-c.elf #lcdlab-s.elf

#additional rules for files

lcdlab3-c.elf: ${COMMON_OBJECTS} 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

#lcd-s.elf: ${COMMON_OBJECTS}
#	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load-c: lcdlab3-c.elf
	msp430loader.sh $^

#load-s: load-s.elf
#	msp430loader.sh $^

clean:
	rm -f *.o *.elf *~ *#

