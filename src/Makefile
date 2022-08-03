# makfile configuration

COMMON_OBJECTS  = main.o p2_interrupt_handler.o switches.o lcd.o wdt_handler.o buzzer.o led.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I./h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all: lcdlab3-c.elf

#additional rules for files

lcdlab3-c.elf: ${COMMON_OBJECTS} 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load-c: lcdlab3-c.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf *~ *#

