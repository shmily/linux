/*=============================================================================
#
#        Author : shmily - shmily@mail.dlut.edu.cn
#            QQ : 723103903
# Last modified : 2012-11-24 19:32
#      Filename : snake.c
#   Description : not thing...
#
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <ncurses.h>

#include "snake.h"
#include "init_Display.h"

static struct list_head SnakeHead;	// the snake list pointer
static struct Point		food;		// the food point
static FILE *fp;

static int snake_mask[FRAME_LINES];			// mask of the snake body

int random_init(void)
{
	if ((fp = fopen("/dev/urandom", "r")) == NULL) {
		fprintf(stderr, "Error! Could not open /dev/urandom for read\n");
		return -1;
	}

	return 0;
}

void GetFood_xy( struct Point *pfood)
{
	int rand_x;
	int rand_y;

	rand_x = fgetc(fp);
	rand_y = fgetc(fp);

	pfood->x = rand_x%(FRAME_COLS/2);
	pfood->y = rand_y%FRAME_LINES;
	
	//DrawBody(pfood->x, pfood->y);
}


void DrawBody(int x, int y)
{
	DrawPoint(x*2, y, ' ');	
	DrawPoint(x*2+1, y, ' ');	
}

void ClearBody(int x, int y)
{
	ClearPoint(x*2, y);	
	ClearPoint(x*2+1, y);	
}

int CreatSnake(void)
{
	int  i;
	char *p;
	struct list_head *pList;
	struct SnakeBody *pSnakeBody;

	init_snakeMask();
	random_init();
	INIT_LIST_HEAD(&SnakeHead);

	for(i=0; i<3; i++){	
	
		p = malloc(sizeof(struct SnakeBody));
		if(p==NULL){
			return -1;	
		}
		
		pSnakeBody = (struct SnakeBody *)p;

		pSnakeBody->x = i;
		pSnakeBody->y = 4;
	
		list_add(&(pSnakeBody->list), &SnakeHead);

		set_snakeMask(i, 4);
	}

	// draw body
	//
	
	list_for_each(pList, &SnakeHead){
		pSnakeBody = list_entry(pList, struct SnakeBody, list);
		DrawBody(pSnakeBody->x, pSnakeBody->y);	
	}

	GetFood_xy(&food);
	DrawBody(food.x, food.y);	

	return 0;
}


static void Get_Next_xy(int cur_x, int cur_y, int *next_x, int *next_y, int direction)
{
	static int dir_in = KEY_RIGHT;

	if((direction==KEY_UP)||(direction==KEY_DOWN)||(direction==KEY_LEFT)||(direction==KEY_RIGHT))
	{
		dir_in = direction;
	}

	switch(dir_in){
		case KEY_UP : 
				cur_y = cur_y - 1;
				if(cur_y<0) cur_y = 0;
				break;
		
		case KEY_DOWN : 
				cur_y = cur_y + 1;
				if(cur_y>=FRAME_LINES) cur_y = FRAME_LINES - 1;
				break;
		
		case KEY_LEFT : 
				cur_x = cur_x - 1;
				if(cur_x<0) cur_x = 0;
				break;
		
		case KEY_RIGHT : 
				cur_x = cur_x + 1;
				if(cur_x>=(FRAME_COLS/2)) cur_x = (FRAME_COLS/2) - 1;
				break;
		
		default :
				break;
	}

	*next_x = cur_x;
	*next_y = cur_y;
}


int snake_Move(int direction)
{
	int    next_x, next_y;
	char   *p;
	struct SnakeBody *pNew;
	struct SnakeBody *pHead;
	struct SnakeBody *pTail;
	int	   is_cover;

	p = malloc(sizeof(struct SnakeBody));
	if(p==NULL){
		return -1;
	}
	pNew = (struct SnakeBody *)p;

	pHead = list_entry(SnakeHead.next, struct SnakeBody, list);

	Get_Next_xy(pHead->x, pHead->y, &next_x, &next_y, direction);	
	pNew->x = next_x;
	pNew->y = next_y;

	list_add(&(pNew->list), &SnakeHead);
	DrawBody(pNew->x, pNew->y);
	set_snakeMask(pNew->x, pNew->y);

	if((next_x == food.x)&&(next_y == food.y)){		// if this is a food
		
		do{
			GetFood_xy(&food);
			is_cover = is_OverSnakeBody(food.x, food.y);
		}while(is_cover!=0);

		DrawBody(food.x, food.y);

		return 0;
	}
	
	pTail = list_entry(SnakeHead.prev, struct SnakeBody, list);
	
	ClearBody(pTail->x, pTail->y);
	clear_snakeMask(pTail->x, pTail->y);
	
	list_del(SnakeHead.prev);

	free((char *)pTail);

	return 0;
}


void init_snakeMask(void)
{

	memset(snake_mask, 0, sizeof(snake_mask)*sizeof(int));
}

void set_snakeMask(int x, int y)
{
	int tmp = 0;

	tmp = (0x01<<x);
	snake_mask[y] = (snake_mask[y] | tmp);
}

void clear_snakeMask(int x, int y)
{
	int tmp = 0;

	tmp = (0x01<<x);
	tmp = ~tmp;

	snake_mask[y] = (snake_mask[y] & tmp);
}

int is_OverSnakeBody(int x, int y)
{
	int tmp = 0;

	tmp = (0x01<<x);

	return (snake_mask[y] & tmp);
}
