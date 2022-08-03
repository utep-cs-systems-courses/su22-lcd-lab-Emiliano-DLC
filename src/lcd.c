#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "lcd.h"


void draw_SQ()
{
  for (unsigned char col = 0; col < screenWidth; col++)
    {
      for(unsigned char row = 0; row < screenHeight; row++)
	{
	  if(col % 2 == 0)
	    {
	      fillRectangle(col, row, 1, 1, COLOR_PINK);
	    }
	  else
	    fillRectangle(col, row, 1, 1, COLOR_BLUE);
	}
	}
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
screen_update_hourglass()
{
  static unsigned char row = screenHeight / 2, col = screenWidth / 2;
  static char lastStep = 0;
  
  if (step == 0 || (lastStep > step)) {
    clearScreen(COLOR_BLUE);
    lastStep = 0;
  } else {
    for (; lastStep <= step; lastStep++) {
      int startCol = col - lastStep;
      int endCol = col + lastStep;
      int width = 1 + endCol - startCol;
      
      // a color in this BGR encoding is BBBB BGGG GGGR RRRR
      unsigned int color = (blue << 11) | (green << 5) | red;
      
      fillRectangle(startCol, row+lastStep, width, 1, color);
      fillRectangle(startCol, row-lastStep, width, 1, color);
    }
  }
}  


    
void
update_shape()
{
  screen_update_ball();
  screen_update_hourglass();
}

	
short redrawScreen = 1;

void wdt_c_handler()
{
  static int secCount = 0;
  if (++secCount >= 20) {		// 12.5/sec
    position_update_ball();
    redrawScreen = 1;
    secCount = 0;
  }
}
