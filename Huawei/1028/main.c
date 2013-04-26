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

void InsertSort ( char arr[],int count)
{
	int  i,j;
	char temp;
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
	char str[100] = {0};
	
	scanf("%s", str);

	InsertSort(str, strlen(str));

	printf("%s",str);
    return 0;
}
