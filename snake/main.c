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
#include <unistd.h>
#include <ncurses.h>
#include <sys/time.h>  
#include <signal.h>

#include "init_Display.h"
#include "snake.h"
#include "Timer.h"

int prv_x, prv_y;
int cur_x, cur_y;
int Game_over = 0;

int G_key;

void Game_loop(int mod);
void Key_loop(void);

int main(void)
{

	Init_Disp();            /* init and display the interface */  	
	
	CreatSnake();

	signal(SIGALRM, Game_loop);
	set_ticker(400);

	while(Game_over==0){
		Key_loop();
	}

	endwin();

	return 0;
}

void Game_loop(int mod)
{
	snake_Move(G_key);
	refresh();
}

void Key_loop(void)
{
	keypad(stdscr, true);
	G_key = getch();
}
