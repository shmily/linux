/*=============================================================================
#
#        Author : shmily - shmily@mail.dlut.edu.cn
#            QQ : 723103903
# Last modified : 2012-11-23 17:25
#      Filename : init_Display.h
#   Description : not thing...
#
=============================================================================*/

#ifndef _Init_Display_H_
#define _Init_Display_H_

#define FIX_LINES	20
#define FIX_COLS	80

#define TOP_ROW     5           /* top_row */  
#define BOT_ROW     FIX_LINES - 1  
#define LEFT_EDGE   0  
#define RIGHT_EDGE  FIX_COLS - 1

#define FRAME_WIDE	64
#define FRAME_HIGHT	16

struct WindowParameter
{
	int TopLeft_x;
	int TopLeft_y;

	int BottomRight_x;
	int BottomRight_y;

	int G_TopLeft_x;
	int G_TopLeft_y;

	int G_BottomRight_x;
	int G_BottomRight_y;

	int Line_offset;
	int Col_offset;
};


void Init_Disp();           /* init and display the interface */


#endif
