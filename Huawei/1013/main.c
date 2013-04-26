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
	char str[100];
	char *p;

	memset(str, 0, sizeof(str));
	scanf("%s", str);	

	p = str + strlen(str) - 1;
	while(p >= str){
		printf("%c", *p--);
	}

	printf("\n");
    return 0;
}
