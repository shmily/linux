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

int mahjong[3][10]; // T,D,W

void paserInput(char *str);
void print_arry(void);

int main(void)
{
	char str[32];

	memset(mahjong, 0, sizeof(int)*2*10);
	gets(str);
	paserInput(str);

	print_arry();

	return 0;
}

void paserInput(char *str)
{
	char *p;
	int num, type;

	p = str;
	while(*p!='\0'){
		num  = (*p - '0');
		if(*(p+1)=='T')		 { type = 0; }
		else if(*(p+1)=='D') { type = 1; }
		else				 { type = 2; }
		
		mahjong[type][0]++;
		mahjong[type][num]++;
		
		p +=2;
	}
}

int isWin(void)
{
	int i, pair, nopair;
	int ret;

	if((mahjong[0][0]=!0)&&(mahjong[1][0]!=0)&&(mahjong[2][0]!=0)){
		return -2;
	}

	pair   = -1;
	nopair = -1;
	for(i=0; i<3; i++){
		if( mahjong[i][0]%3==1 ){
			return -2;
		}else if(mahjong[i][0]%3==2){	// 3n+2
			
			if(pair==-1){
				pair = i;
			}else{						// Impossible have 2 (3n+2)
				return -2;
			}
		}else{	// 3n
			nopair = i;
		}
	}

	// 3n
	if(nopair!=-1){
		ret = analyze(mahjong[nopair]);
		if(ret!=0) return -1;
	}

	if(pair!=-1){
		for(i=0; i<10; i++)
	}
}

int analyze(int *arry)
{
	int i, ret;

	if(arry[0]==0){
		return 0;
	}

	// search the first one
	for(i=1; i<10; i++){
		if(arry[i]!=0) break;
	}

	if(arry[i]>=3){
		arry[i] -= 3;
		arry[0] -= 3;
		ret = analyze(arry);
		arry[i] += 3;
		arry[0] += 3;

		return ret;
	}

	if((i<8)&&(arry[i+1]>0)&&(arry[i+2]>0)){
		arry[i]   -= 1;
		arry[i+1] -= 1;
		arry[i+2] -= 1;
		arry[0]   -= 3;
		ret = analyze(arry);
		arry[i]   += 1;
		arry[i+1] += 1;
		arry[i+2] += 1;
		arry[0]   += 3;

		return ret;
	}

	return -1;
}

void print_arry(void)
{
	int i;
	
	printf("T>");
	for(i=0; i<10; i++){
		printf("%d ", mahjong[0][i]);
	}
	printf("\n");

	printf("D>");
	for(i=0; i<10; i++){
		printf("%d ", mahjong[1][i]);
	}
	printf("\n");

	printf("W>");
	for(i=0; i<10; i++){
		printf("%d ", mahjong[2][i]);
	}
	printf("\n");
}
