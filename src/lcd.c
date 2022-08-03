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
  for (unsigned char col = screenHeight; col > 0; col--)
    {
	  //led_shift();
      for(unsigned char row = screenWidth; row > 0; row--)
	{ 
	  if(col % 2 == 0)
	    {
	      fillRectangle(row, col, 5, 5, COLOR_SKY_BLUE);
		  	buzzer_set_period(0);
	    }
	  else
	    fillRectangle(col, row, 5, 5, COLOR_LIME_GREEN);
	      buzzer_set_period(0);
	}
}
	buzzer_set_period(0);
}

void draw_ptrn()
{
	red_on = 1;
	green_on = 0;
	led_changed = 1;
	led_update();
	buzzer_set_period(0);
  for (unsigned char col = 0; col <= screenHeight; col++)
    {
	red_on ^= 1;
	green_on ^= 1;
	led_changed = 1;
	led_update();
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

short drawPos[2] = {screenHeight/2 , screenWidth/2}, controlPos[2] = {(screenHeight/2)+1, screenWidth/2};
short colVelocity = 1, colLimits[2] = {1, screenWidth};
short limitW[2] = {1, screenWidth-1};
short limitH[2] = {2, screenHeight-1};

void
draw_ball(int col, int row, unsigned short color)
{
  fillRectangle(col, row, 1, 1, color);
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

void position_update_ball()
{
  if (switches & SW1 && controlPos[1] > limitW[1]){
	  controlPos[1] -= 1;
  }
  if (switches & SW2 && controlPos[1] < limitW[1]){ 
	  controlPos[1] += 1;
  }
  if (switches & SW3 && controlPos[0] > limitH[0]){ 
	  controlPos[0] -= 1;
  }
  if (switches & SW4 && controlPos[0] < limitH[0]){ 
	  controlPos[0] += 1;
  }
}


//---------------------------------------------------------------------

void
update_shape()
{
  //draw_ptrn();
  //R_draw_ptrn();
  screen_update_ball();
}

short redrawScreen = 1;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 30) {		/* 10/sec */
   position_update_ball();
   redrawScreen = 1;
    secCount = 0;
   }
	//draw_ptrn();
   }
