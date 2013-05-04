
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void avg_calcu(int *p, int N);

int main(void)
{
	int N, i;
	int *pData, *_pData;

	while( scanf("%d", &N) != EOF ){
		_pData = malloc(sizeof(int)*N);
    
		pData = _pData;
		for(i=0; i<N; i++){
			scanf("%d,", pData++);	
		}

		avg_calcu(_pData, N);
		free(_pData);
	};

	return 0;
}

void avg_calcu(int *p, int N)
{
	int sum_real, sum_imag;
	int a, b, c, d;
	int i, ret;

	short int *pshort;

	sum_real = 0;
	sum_imag = 0;
	pshort = (short int *)p;

	for(i=0; i<N; i+=2){

		b = *pshort++;
		a = *pshort++;
		d = *pshort++;
		c = *pshort++;
	
		sum_real += (a*c - b*d);
		sum_imag += (a*d + b*c);
	}

	sum_real = sum_real / N;
	sum_imag = sum_imag / N;

	if(sum_real>32767)
		sum_real = 32767;
	else if(sum_real<-32768)
		sum_real = -32768;

	if(sum_imag>32767)
		sum_imag = 32767;
	else if(sum_imag<-32768)
		sum_imag = -32768;

	ret = (sum_real<<16) | (sum_imag & 0xFFFF);

	printf("%d\n", ret);
}

