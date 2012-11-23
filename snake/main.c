/*=============================================================================
#
#        Author : shmily - shmily@mail.dlut.edu.cn
#            QQ : 723103903
# Last modified : 2012-11-23 17:01
#      Filename : main.c
#   Description : not thing...
#
=============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "init_Display.h"

int main(void)
{
	
	Init_Disp();            /* init and display the interface */  	
	
	getch();
	endwin();

	return 0;
}
