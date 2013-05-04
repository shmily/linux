
#include <stdio.h>

int main(void)
{
	char str[32];

	scanf("%s", str);

	if(str[0]=='1')      str[0] = 'a';
	else if(str[0]=='2') str[0] = 'c';
	else                 str[0] = 'e';

	printf("%s\n", str);
    return 0;
}
