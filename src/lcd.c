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
	
short redrawScreen = 1;
