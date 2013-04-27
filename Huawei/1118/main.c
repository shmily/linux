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
	char str[128];
	char *p_head, *p_tail;

	while(1){
		memset(str,    0, sizeof(str));
		scanf("%s", str);

		if(strcmp(str, "0")==0) break;

		p_head = str;
		p_tail = str + strlen(str) - 1;

		while(p_head < p_tail){
			if(tolower(*p_head)!=tolower(*p_tail)){
				break;			
			}

			p_head++;
			p_tail--;
		}

		if(p_head<p_tail) printf("No\n");
		else printf("Yes\n");
	}

    return 0;
}
