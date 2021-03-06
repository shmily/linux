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
#include <string.h>

#define _err 0
#define _spe 1
#define _num 2
#define _top 3
#define _low 4

int _count[5];

const int _mask[] = {
_err, _err, _err, _err, _err, _err, _err, _err,
_err, _err, _err, _err, _err, _err, _err, _err,
_err, _err, _err, _err, _err, _err, _err, _err,
_err, _err, _err, _err, _err, _err, _err, _err,
_err, _spe, _err, _spe, _spe, _spe, _spe, _err,
_spe, _spe, _spe, _spe, _err, _spe, _err, _spe,
_num, _num, _num, _num, _num, _num, _num, _num,
_num, _num, _err, _err, _err, _spe, _err, _spe,
_spe, _top, _top, _top, _top, _top, _top, _top,
_top, _top, _top, _top, _top, _top, _top, _top,
_top, _top, _top, _top, _top, _top, _top, _top,
_top, _top, _top, _err, _err, _err, _spe, _spe,
_err, _low, _low, _low, _low, _low, _low, _low,
_low, _low, _low, _low, _low, _low, _low, _low,
_low, _low, _low, _low, _low, _low, _low, _low,
_low, _low, _low, _err, _err, _err, _err, _err
};

int isValidPassword(char *p);

int main(void)
{
	char str[1000];
	int  ret;

	while(gets(str)){

		ret = isValidPassword(str);

		if(ret==0) printf("true\n");
		else printf("false\n");
	}

    return 0;
}

int isValidPassword(char *p)
{
	int i, len, typeCount;

	// len err
	len = strlen(p);
	if( len<8||len>20 ) return -1;

	_count[0] = 0;
	_count[1] = 0;
	_count[2] = 0;
	_count[3] = 0;
	_count[4] = 0;

	while(*p!='\0'){
		i = (int)*p;
		_count[_mask[i]] = 1;
		p++;
	}

	// wrong input
	if(_count[0]>0) return -1;

	typeCount = 0;
	for(i=1; i<5; i++){
		if(_count[i]>0) typeCount++;
	}

	if(typeCount<3) return -1;

	return 0;
}
