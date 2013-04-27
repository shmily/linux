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
	int i,j;
	int input[22];
	int odd[12], even[12];
	int *p_odd;
	int *p_even;

	memset(input, 0, sizeof(input));	
	memset(odd,   0, sizeof(odd));	
	memset(even,  0, sizeof(even));	
	
	for(i=0; i<10; i++){
		scanf("%d", &input[i]);
	}

	InsertSort(input, 10);

	p_odd  = odd;
	p_even = even;
	for(i=0; i<10; i++){
		if(input[i]%2==0) *p_even++ = input[i];
		else              *p_odd++  = input[i];
	}

	memset(input, 0, sizeof(input));
	i = 0;
	j = 0;	
	do{
		input[i++] = odd[j];
		input[i++] = even[j];
		j++;
	}while((odd[j]!=0)||(even[j]!=0));

	if(input[i-1]==0) i = (i - 1);

	for(j=0; j<i-1; j++){
		printf("%d ", input[j]);
	}

	printf("%d\n", input[i-1]);

    return 0;
}
