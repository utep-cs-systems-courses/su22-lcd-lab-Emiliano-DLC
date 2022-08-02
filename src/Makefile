# makfile configuration

COMMON_OBJECTS  = main.o led.o buzzer.o p2_interrupt_handler.o switches.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: lcd-c.elf lcd-s.elf

#additional rules for files

lcd-c.elf: ${COMMON_OBJECTS} 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

lcd-s.elf: ${COMMON_OBJECTS}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load-c: lcd-c.elf
	msp430loader.sh $^

load-s: load-s.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf *~ *#

