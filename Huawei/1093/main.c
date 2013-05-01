
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

const int mask[100] = {
0, 0, 1, 1, 0, 1, 0, 1, 0, 0,
0, 1, 0, 1, 0, 0, 0, 1, 0, 1,
0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
0, 1, 0, 1, 0, 0, 0, 1, 0, 0,
0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
0, 0, 0, 0, 0, 0, 0, 1, 0, 0
};

int main(void)
{
	int num;
	int i;
	int len;
	char *p, *sp;

	p = malloc(512);
	memset(p, 0, 512);
	scanf("%d", &num);

	sp = p;
	for(i=4;i<=num; i++){
		if(mask[i]==0){
			len = sprintf(sp, "%d ", i);
			sp += len;
		}
	}

	if(sp>p)
	 	*(sp-1) = '\0';

	printf("%s\n",p);

	free(p);
    return 0;
}
