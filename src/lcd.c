#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "lcd.h"
#include "buzzer.h"
#include "led.h"

void led_start()
{
	red_on = 1;
	green_on = 0;
	led_changed = 1;
	led_update();	
}

void led_shift()
{
	red_on ^= 1;
	green_on ^= 1;
	led_changed = 1;
	led_update();	
}

void R_draw_ptrn()
{
//buzzer_set_period(5000);
  for (unsigned char col = screenHeight; col > 0; col--)
    {
	  led_shift();
      for(unsigned char row = screenWidth; row > 0; row--)
	{ 
	  if(col % 2 == 0)
	    {
	      fillRectangle(row, col, 5, 5, COLOR_BLACK);
		  	buzzer_set_period(0);
	    }
	  else
	    fillRectangle(col, row, 5, 5, COLOR_PINK);
	      buzzer_set_period(0);
	}
}
	buzzer_set_period(0);
}

void draw_ptrn()
{
	//red_on = 1;
	//green_on = 0;
	//led_changed = 1;
	//led_update();
	buzzer_set_period(0);
  for (unsigned char col = 0; col <= screenHeight; col++)
    {
	//red_on ^= 1;
	//green_on ^= 1;
	//led_changed = 1;
	//led_update();
      for(unsigned char row = 0; row <= screenWidth; row++)
	{ 
	  if(col % 2 == 0)
	    {
	      fillRectangle(row, col, 5, 5, COLOR_BLACK);
		  	buzzer_set_period(10000);
	    }
	  else
	    fillRectangle(col, row, 5, 5, COLOR_PINK);
	      buzzer_set_period(7500);
	}
	}
	buzzer_set_period(5000);
}



char blue = 31, green = 0, red = 31;
unsigned char step = 0;

short drawPos[2] = {1,10}, controlPos[2] = {2, 10};
short colVelocity = 1, colLimits[2] = {1, screenWidth/2};

void
draw_ball(int col, int row, unsigned short color)
{
  fillRectangle(col-1, row-1, 3, 3, color);
}

void
screen_update_ball()
{
  for (char axis = 0; axis < 2; axis ++) 
    if (drawPos[axis] != controlPos[axis]) /* position changed? */
      goto redraw;
  return;			/* nothing to do */
 redraw:
  draw_ball(drawPos[0], drawPos[1], COLOR_BLUE); /* erase */
  for (char axis = 0; axis < 2; axis ++) 
    drawPos[axis] = controlPos[axis];
  draw_ball(drawPos[0], drawPos[1], COLOR_WHITE); /* draw */
}
    
void
update_shape()
{
  screen_update_ball();
	led_start();
	draw_ptrn();
	R_draw_ptrn();
	//clearScreen(COLOR_BLUE);
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
