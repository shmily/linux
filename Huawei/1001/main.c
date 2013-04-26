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

int Parser(const char *pstr)
{
	int num[30];
	int op[30];
	int	sum;

	int	*p_num;
	int *p_op;

	memset(num, 0, sizeof(num));
	memset(op,  0, sizeof(op));

	// parser the num and oper
	p_num = num;
	p_op  = op;
	while(*pstr!='\0'){

		if(*pstr<'0'){
			*p_op = *pstr;
			p_op++;
			p_num++;
		}else{
			*p_num = (*p_num * 10) + (*pstr - '0');
		}

		pstr++;
	}

	// calculate
	p_num = num;
	p_op  = op;
	sum   = *p_num++;
	while(*p_op != '0'){
		switch(*p_op){
			case '+':
				sum = sum + (*p_num++);
				break;
			case '-':
				sum = sum - (*p_num++);
				break;
			case '*':
				sum = sum * (*p_num++);
				break;
			case '/':
				if(*p_num!=0){
					sum = sum / (*p_num++);
				}else{
					goto _return;
				}
				break;
			default:
				goto _return;
				break;
		}

		p_op++;
	}

_return:
	return sum;
}

int main(int argc, char *argv[])
{
	char str[256];
	int	 res;

	memset(str, 0, sizeof(str));
	scanf("%s", str);

	res = Parser(str);
	printf("%d", res);

    return 0;
}
