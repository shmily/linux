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

void InsertSort ( int arr[],int count)
{
	int  i,j;
	int temp;
	for(i=1; i<count; i++){
		if(arr[i]<arr[i-1]){
			temp = arr[i];
			for(j=i-1; j>=0 && arr[j]>temp; j--){
				arr[j+1] = arr[j];
			}
			arr[j+1] = temp;
		}
	}
}

int main( void )
{
	int num[10] = {0};
	int out[10] = {0};
	int *p;
	int i;

	p = num;
	for(i=0; i<10; i++){
		scanf("%d", p++);
	}

	InsertSort(num, 10);

	p = num;
	for(i=0; i<5; i++){
		out[i]   = *p++;
		out[9-i] = *p++;
	}

	p = out;
	for(i=0; i<9; i++){
		printf("%d ", *p++);	
	}
	printf("%d\n", *p);	

    return 0;
}
