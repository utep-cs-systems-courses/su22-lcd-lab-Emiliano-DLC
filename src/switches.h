#ifndef switches_included
#define switches_included

//P2DIR
//define buttons on external board (p2)
#define SW1 1 
#define SW2 2 
#define SW3 4 
#define SW4 8 
#define SWITCHES 15 //Switches for external board (p2)

//P1DIR
//#define SW0 BIT4		/* switch1 is p1.3 */
//#define P1SWITCHES(SW0)		/* only 1 switch on this board */

void switch_init();
void switch_interrupt_handler();
void wtd_c_handler();

int switches;

#endif
