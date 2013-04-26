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

void InputParser(const char *pstr, int *parray, int *len)
{
	int new_num = 0;
	int count = 0;

	while(*pstr != '\0'){
		if( (*pstr>='0') && (*pstr <='9') ){
			if(new_num == 0) count++;
			*parray = (*parray * 10) + (*pstr - '0');
			new_num = 1;
		}else{
			if(new_num == 1){
				if(count!=0) parray++;
				new_num = 0;
			}
		}

		pstr++;
	}

	*len = count;
}

int main(void)
{
	char in_str[256];
	int  array[32];
	int  len;
	int  res;

	memset(in_str, 0, sizeof(in_str));
	memset(array,  0, sizeof(array));

	scanf("%s", in_str);
	InputParser(in_str, array, &len);

	res = GetByondAvgNumber(array, len);	

	printf("%d\n", res);
    return 0;
}
