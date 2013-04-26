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

int main( void )
{
	char str[100];
	int	 len;
	char *p1;
	char *p2;
	char *p1_cur;
	char *p2_cur;

	memset(str, 0, sizeof(str));
	scanf("%s", str);	

	len = strlen(str);

	if(len > 1){

		p1 = str + (len)/2 - 1;
		p2 = str + (len + 1)/2;

		p1_cur = str;
		p2_cur = p2;
		
		while(p1_cur <= p1){

			if(*p1_cur == 'a') *p1_cur = 'z';
			else               *(p1_cur) = *p1_cur - 1;
		
			if(*p2_cur == 'z') *p2_cur = 'a';
			else               *(p2_cur) = *p2_cur + 1;

			p1_cur++;
			p2_cur++;
		}
	}
	
	printf("%s\n", str);
    return 0;
}
