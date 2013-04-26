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

int main(int argc, char *argv[])
{
	char str[5] = {0};
	int  i;
	int  num1, sum;
	char *p;

	sum = 0;
	for(i=0; i<2; i++){
		scanf("%s", str);
		p = str + strlen(str) - 1;
		num1 = 0;
		while(p>=str){
			num1 = num1*10 + (*p-- - '0');
		}
		sum += num1;
	}

	printf("%d\n", sum);
    return 0;
}
