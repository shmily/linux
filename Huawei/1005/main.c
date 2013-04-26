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

int IsPalindrome(int iNumber)
{
	char str[1024];
	int	 len;
	char *p_head;
	char *p_tail;

	memset(str, 0, sizeof(str));
	sprintf(str, "%d", iNumber);

	len = strlen(str);
	p_head = str;
	p_tail = str + len - 1;

	while(p_head <= p_tail){
		if(*p_head == *p_tail){
			p_head++;
			p_tail--;
		}else{
			break;
		}
	}
	
	return ((p_head<p_tail) ? 0:1);
}

int main(int argc, char *argv[])
{	
	int num;
	int res;

	scanf("%d", &num);

	res = IsPalindrome(num);
	printf("%d\n", res);

    return 0;
}
