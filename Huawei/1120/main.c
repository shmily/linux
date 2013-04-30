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
#include <ctype.h>
#include <memory.h>

int main( void )
{
	const int changes[7] = {50, 20, 10, 5,   1,   5,   1  };
	const int max[7] =     {10, 20, 50, 100, 100, 200, 500};
	int counts[7];
	float money;
	int high,low, tmp;;
	int i;

	scanf("%f", &money);

	high = (int)money;
	money = money * 10;
	low = ((int)money)%10;

	if((high<2150)||((high==2150)&&(low==0))){

		for(i=0; i<5; i++){
			tmp = high/changes[i];
			if(tmp>max[i]){
				counts[i] = max[i];
				high = high - max[i]*changes[i];
			}else{
				counts[i] = tmp;
				high = high%changes[i];
			}
		}
		low = low + high*10;
		counts[5] = low/5;
		if(counts[5]>max[5]){
			counts[5] = max[5];
			low = low - max[5]*5;		
		}else{
			low = low%5;
		}
		counts[6] = low;

		printf("the results are num_50=%d num_20=%d num_10=%d num_5=%d num_1=%d num_0.5=%d num_0.1=%d\n",
		   counts[0],counts[1],counts[2],counts[3],counts[4],counts[5],counts[6]);
	}else{
		printf("the operate is fail\n");
	}

    return 0;
}
