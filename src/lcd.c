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

void draw_bar(int col, int row, unsigned short color)
{
  fillRectangle(col, row, 11, 1, color);
}

short barDrawPos[2] = {screenWidth/2, screenWidth/2}; // left bar on 0, right bar on 1
short barControlPos[2] = {1+screenWidth/2, 1+screenWidth/2};
short barLim[2] = {5,screenWidth-8};  //bar is of size 5 and bar have shifts of 3

void screen_update_bar()
{
  for (char bar = 0; bar < 2; bar++) 
    if (barDrawPos[bar] != barControlPos[bar]) // position changed?
      goto redraw;
  return;			// nothing to do
 redraw:
  draw_bar(barDrawPos[0]-5, 2, COLOR_BLACK);  // erase left bar
  draw_bar(barDrawPos[1]-5, screenHeight-2, COLOR_BLACK);  // erase right bar
  for (char bar = 0; bar < 2; bar++) 
    barDrawPos[bar] = barControlPos[bar];
  draw_bar(barDrawPos[0]-5, 2, COLOR_WHITE); // draw left bar
  draw_bar(barDrawPos[1]-5, screenHeight-2, COLOR_WHITE); // draw right bar
}

void position_update_bar()
{
  if (switches & SW1 && barControlPos[1] > barLim[0]) barControlPos[1] -= 3;
  if (switches & SW2 && barControlPos[1] < barLim[1]) barControlPos[1] += 3;
  if (switches & SW3 && barControlPos[0] > barLim[0]) barControlPos[0] -= 3;
  if (switches & SW4 && barControlPos[0] < barLim[1]) barControlPos[0] += 3;
}

//----------------------------------------------------------------------------------

char blue = 31, green = 0, red = 31;
unsigned char step = 0;

short drawPos[2] = {1,50}, controlPos[2] = {2, 50};
short colVelocity = 1, colLimits[2] = {1, screenWidth};

void
draw_ball(int col, int row, unsigned short color)
{
  fillRectangle(col-1, row-1, 5, 5, color);
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
  screen_update_bar();
	//led_start();
	//draw_ptrn();
	//R_draw_ptrn();
	//clearScreen(COLOR_BLUE);
}

	
short redrawScreen = 1;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 25) {		/* 10/sec */
  	position_update_ball();
    position_update_bar();
    redrawScreen = 1;
    secCount = 0;
    }
  
  }
