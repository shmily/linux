/*=============================================================================
#
#        Author : shmily - shmily@mail.dlut.edu.cn
#            QQ : 723103903
# Last modified : 2012-11-24 19:32
#      Filename : snake.h
#   Description : not thing...
#
=============================================================================*/

#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "myList.h"

struct SnakeBody{
	int 				x;
	int 				y;
	struct list_head 	list;
};

struct Point{
	int x;
	int y;
};

void GetFood_xy( struct Point *pfood);

void DrawBody(int x, int y);
void ClearBody(int x, int y);

int CreatSnake(void);
int snake_Move(int direction);

#endif
