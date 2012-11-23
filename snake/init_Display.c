
#include <ncurses.h>
#include "init_Display.h"

int Line_offset;
int Col_offset;

static int Check_TermialSize(void);

/* Function: Init_Disp()
 * Usage: init and display the interface
 * Return: none
 */
void Init_Disp()
{
	char wall = ' ';
	int i, j;
	initscr();

	if(Check_TermialSize()!=0){
		return;
	}

	cbreak();				/* put termial to CBREAK mode */
	noecho();
	curs_set(0);			/* set cursor invisible */

	start_color();			/* init color */
	init_pair(1, COLOR_RED, COLOR_BLACK);

	/* display some message about title and wall */
	attrset(A_NORMAL);		/* set NORMAL first */
	attron(A_REVERSE);		/* turn off REVERSE */
	
	for(i = 0; i < FIX_LINES; i++)
	{
		mvaddch(i+Line_offset, LEFT_EDGE+Col_offset, wall);
		mvaddch(i+Line_offset, RIGHT_EDGE+Col_offset, wall);
	}
	for(j = 0; j < FIX_COLS; j++)
	{
		mvaddch(Line_offset-1, j+Col_offset, '=');
		mvaddch(TOP_ROW+Line_offset, j+Col_offset, wall);
		mvaddch(BOT_ROW+Line_offset, j+Col_offset, wall);
	}
	attroff(A_REVERSE);		/* turn off REVERSE */
	mvaddstr(1, 2, "Game: snake    version: 1.0    date: 2011/08/22");
	mvaddstr(2, 2, "Author: Dream Fly	Blog: blog.csdn.net/jjzhoujun2010");
	mvaddstr(3, 2, "Usage: Press 'f' to speed up, 's' to speed down,'q' to quit.");
    mvaddstr(4, 2, "       Nagivation key controls snake moving.");
	refresh();
}

static int Check_TermialSize(void)
{
	if((LINES<FIX_LINES+8)||(COLS<FIX_COLS+8)){
		mvaddstr(4, 4, "ERROR : Termial Size is too small!");
		mvaddstr(5, 4, "        Please resize it, and try again...");
		return -1;
	}
	
	Line_offset = (LINES - FIX_LINES)/2;
	Col_offset = (COLS - FIX_COLS)/2;

	return 0;	
}
