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

#define _norma(_i) \
{\
	if(_i>32767) _i = 32767;\
	else if(_i<-32768) _i= -32768;\
}

int avg_calu(int *p, int n);
int main(void)
{
	int i,n;
	int *pData, *_pData;

	scanf("%d", &n);

	if(n==0){
		printf("0\n");
		return 0;
	}

	if((n<0)||(n>1000)||( (n&0x01) == 0x01)){
		exit(-1);
	}

	_pData = (int *)malloc(sizeof(int)*n);
	pData  = _pData;
	for(i=0; i<n; i++){
		scanf("	%d,", pData++);
	}
	
	printf("%d\n", avg_calu(_pData, n));

	free(_pData);

    return 0;
}

int avg_calu(int *p, int n)
{
	int sum_real, sum_imag;
	int i, a, b, c, d, ret;
	int tmp_r, tmp_i;
	short int *pdiv;

	sum_real = 0;
	sum_imag = 0;
	pdiv = (short int *)p;
	for(i=0; i<n/2; i++){

		b = *pdiv++;
		a = *pdiv++;
		d = *pdiv++;
		c = *pdiv++;
		
		tmp_r = (a*c - b*d);	
		tmp_i = (a*d + b*c);

		_norma(tmp_r);
		_norma(tmp_i);

		sum_real += tmp_r;
		sum_imag += tmp_i;

		_norma(sum_real);
		_norma(sum_imag);
	}

	sum_real = sum_real / n;
	sum_imag = sum_imag / n;

	ret = (sum_real<<16)|(sum_imag & 0xFFFF);

	return ret;
}
