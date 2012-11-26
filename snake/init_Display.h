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

#define FRAME_COLS	48
#define FRAME_LINES	16

#define FIX_COLS	(FRAME_COLS + 31)
#define FIX_LINES	(FRAME_LINES + 6)

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


void 	Init_Disp();           /* init and display the interface */
void 	Curs_Return(void);
int 	DrawPoint(int x, int y, char ascii);
int 	ClearPoint(int x, int y);


#endif
