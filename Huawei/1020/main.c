/*
=============================================================================
#
#        Author : shmily - shmily@mail.dlut.edu.cn
#            QQ : 723103903
# Last modified : 2013-04-18 20:47
#      Filename : Pascal.c
#   Description : not thing...
#
=============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main( void )
{
	unsigned int num;
	int  tmp;

	scanf("%d", &num);

	tmp = (unsigned int)num&0x00000004;

	printf("%d\n", (tmp!=0)?1:0);
    return 0;
}
