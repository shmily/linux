/*=============================================================================
#
#        Author : shmily - shmily@mail.dlut.edu.cn
#            QQ : 723103903
# Last modified : 2012-11-24 15:43
#      Filename : init_Display.c
#   Description : not thing...
#
=============================================================================*/

#include <ncurses.h>
#include "init_Display.h"

static struct WindowParameter g_window;

static int Check_TermialSize(void);

/* Function: Init_Disp()
 * Usage: init and display the interface
 * Return: none
 */
void Init_Disp()
{
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
	init_pair(2, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(3, COLOR_BLACK, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, COLOR_GREEN);

	/* display some message about title and wall */
	attrset(A_NORMAL);		/* set NORMAL first */
	attron(A_REVERSE);		/* turn on REVERSE */
	attron(COLOR_PAIR(1));

	for(i = 0; i < FIX_LINES; i++)
	{
		mvaddch( i+g_window.TopLeft_y, g_window.TopLeft_x, ' ');
		mvaddch( i+g_window.TopLeft_y, g_window.BottomRight_x, ' ');
	}
	for(j = 0; j < FIX_COLS; j++)
	{
		mvaddch(g_window.TopLeft_y, j+g_window.TopLeft_x, '+');
		mvaddch(g_window.BottomRight_y, j+g_window.TopLeft_x, ' ');
	}
	
	for(i = 0; i < FRAME_LINES + 2; i++)
	{
		mvaddch( i+g_window.G_TopLeft_y, g_window.G_TopLeft_x, ' ');
		mvaddch( i+g_window.G_TopLeft_y, g_window.G_BottomRight_x, ' ');
	}
	for(j = 0; j < FRAME_COLS +2; j++)
	{
		mvaddch(g_window.G_TopLeft_y, j+g_window.G_TopLeft_x, '+');
		mvaddch(g_window.G_BottomRight_y, j+g_window.G_TopLeft_x, ' ');
	}

	attroff(COLOR_PAIR(1));
	//attroff(A_REVERSE);		/* turn off REVERSE */
	curs_set(0);			/* set cursor invisible */
	
	attron(COLOR_PAIR(4));
	mvaddstr(g_window.TopLeft_y+2,  g_window.TopLeft_x+2, "   Game : snake");
	mvaddstr(g_window.TopLeft_y+3,  g_window.TopLeft_x+2, "Version : 0.01");
	mvaddstr(g_window.TopLeft_y+4,  g_window.TopLeft_x+2, " Author : shmily");
	mvaddstr(g_window.TopLeft_y+7,  g_window.TopLeft_x+2, "Usage :");
	mvaddstr(g_window.TopLeft_y+9,  g_window.TopLeft_x+2, "F for speed up");
	mvaddstr(g_window.TopLeft_y+10, g_window.TopLeft_x+2, "S for speed down");
	mvaddstr(g_window.TopLeft_y+11, g_window.TopLeft_x+2, "Q for quit");
	mvaddstr(g_window.TopLeft_y+13, g_window.TopLeft_x+2, "Nagivation key to moving.");
	
	attroff(COLOR_PAIR(4));
	refresh();
}

static int Check_TermialSize(void)
{
	if((LINES<FIX_LINES+4)||(COLS<FIX_COLS+4)){
		mvaddstr(4, 4, "ERROR : Termial Size is too small!");
		mvaddstr(5, 4, "        Please resize it, and try again...");
		return -1;
	}
	
	g_window.Line_offset = (LINES - FIX_LINES)/2;
	g_window.Col_offset = (COLS - FIX_COLS)/2;
	
	g_window.TopLeft_x = g_window.Col_offset;
	g_window.TopLeft_y = g_window.Line_offset;

	g_window.BottomRight_x = FIX_COLS + g_window.Col_offset - 1;
	g_window.BottomRight_y = FIX_LINES + g_window.Line_offset - 1;
	
	g_window.G_TopLeft_x = g_window.TopLeft_x + 27;
	g_window.G_TopLeft_y = g_window.TopLeft_y + 2;

	g_window.G_BottomRight_x = g_window.G_TopLeft_x + FRAME_COLS + 1;
	g_window.G_BottomRight_y = g_window.G_TopLeft_y + FRAME_LINES + 1;
	
	return 0;	
}

int DrawPoint(int x, int y, char ascii)
{
	int phy_x;
	int phy_y;

	if((x<0)||(x>=FRAME_COLS)||(y<0)||(y>=FRAME_LINES)){
		return -1;
	}
	
	phy_x = g_window.G_TopLeft_x + x + 1;			
	phy_y = g_window.G_TopLeft_y + y + 1;			
	
	attron(COLOR_PAIR(2));
	mvaddch(phy_y, phy_x, ascii);	
	attron(COLOR_PAIR(2));
	Curs_Return();	

	return 0;
}

int ClearPoint(int x, int y)
{
	int phy_x;
	int phy_y;

	if((x<0)||(x>=FRAME_COLS)||(y<0)||(y>=FRAME_LINES)){
		return -1;
	}
	
	phy_x = g_window.G_TopLeft_x + x + 1;			
	phy_y = g_window.G_TopLeft_y + y + 1;			
	
	attron(COLOR_PAIR(3));
	mvaddch(phy_y, phy_x, ' ');	
	attroff(COLOR_PAIR(3));
	Curs_Return();	

	return 0;
}

void Curs_Return(void)
{
	mvaddch(0, 0, ' ');
}
