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

int GetByondAvgNumber(int iArray[], int iLen)
{
	int sum = 0;
	int average = 0;
	int count = 0;
	int	i;
	int *p;

	p = iArray;
	i = iLen;
	while( i-- > 0 ){
		sum += *p++;
	}
	
	average = (sum + (iLen-1)) / iLen;

	p = iArray;
	i = iLen;
	while( i-- > 0){
		if(*p >= average) count++;
		p++;
	}

	return count;
}

int main(void)
{
	int array[] = {1,2,3,4,5};
	int res;

	res = GetByondAvgNumber(array, 5);	

	printf("%d\n", res);
    return 0;
}
