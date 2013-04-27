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
#include <memory.h>

int IsPalindrome(int iNumber)
{
	char str[32];
	char str_r[32];
	char *p_head;
	char *p_tail;

	memset(str, 0, sizeof(str));
	memset(str_r, 0, sizeof(str));
	sprintf(str, "%d", iNumber);

	p_head = str + strlen(str) - 1;
	p_tail = str_r;
	do{
		*p_tail++ = *p_head--;
	}while(p_head>=str);

	return (strcmp(str, str_r)==0) ? 1:0;
}

int main(void)
{	
	int num;
	int res;

	scanf("%d", &num);

	res = IsPalindrome(num);
	printf("%d\n", res);

    return 0;
}
