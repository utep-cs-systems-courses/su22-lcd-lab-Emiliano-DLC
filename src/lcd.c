#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "lcd.h"
#include "buzzer.h"
#include "led.h"

void R_draw_ptrn()
{
//buzzer_set_period(5000);
	red_on = 0;
	green_on = 0;
	led_changed = 1;
	led_update();
  for (unsigned char col = screenWidth; col > 0; col--)
    {

      for(unsigned char row = screenWidth; row > 0; row--)
	{ 
	  if(col % 2 == 0)
	    {
	      fillRectangle(row, col, 5, 5, COLOR_BLUE);
		  	//buzzer_set_period(10000);
		  red_on ^= 0;
	led_changed = 1;
	led_update();
	    }
	  else
	    fillRectangle(col, row, 5, 5, COLOR_GREEN);
	      //buzzer_set_period(7500);
		green_on ^= 0;
		led_changed = 1;
		led_update();
	}
	}
	buzzer_set_period(0);
}

void draw_ptrn()
{
	buzzer_set_period(5000);
  for (unsigned char col = 0; col <= screenHeight; col++)
    {

      for(unsigned char row = 0; row <= screenWidth; row++)
	{ 
	  if(col % 2 == 0)
	    {
	      fillRectangle(row, col, 5, 5, COLOR_PINK);
		  	buzzer_set_period(10000);
	    }
	  else
	    fillRectangle(col, row, 5, 5, COLOR_BLACK);
	      buzzer_set_period(7500);
	}
	}
	buzzer_set_period(0);
}
    
void
update_shape()
{
  screen_update_ball();
	draw_ptrn();
	R_draw_ptrn();
}

	
short redrawScreen = 1;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 25) {		/* 10/sec */
   
    {				/* move ball */
      short oldCol = controlPos[0];
      short newCol = oldCol + colVelocity;
      if (newCol <= colLimits[0] || newCol >= colLimits[1])
	colVelocity = -colVelocity;
      else
	controlPos[0] = newCol;
    }

    {				/* update hourglass */
      if (switches & SW3) green = (green + 1) % 64;
      if (switches & SW2) blue = (blue + 2) % 32;
      if (switches & SW1) red = (red - 3) % 32;
      if (step <= 30)
	step ++;
      else
	step = 0;
      secCount = 0;
    }
    if (switches & SW4) return;
    redrawScreen = 1;
  }
}
