
#include <stdio.h>

char encode[52] = 
{'c', 'g', 'm', 'u', 'E', 'Q', 'e', 'u',
 'M', 'g', 'C', 'a', 'A', 'c', 'G', 'm',
 'U', 'E', 'q', 'e', 'U', 'M', 'G', 'C',
 'A', 'A', 'C', 'G', 'M', 'U', 'e', 'q',
 'E', 'U', 'm', 'G', 'c', 'A', 'a', 'C',
 'g', 'M', 'u', 'e', 'Q', 'E', 'u', 'm',
 'g', 'c', 'a', 'a'};

int main(void)
{

	char *pstr;
	char str[1024];

	scanf("%s", str);

	pstr = str;
	while(*pstr!='\0'){
		if(*pstr<'a'){
			*pstr = encode[(*pstr - 'A')+26];
		}else{
			*pstr = encode[(*pstr - 'a')];	
		}

		pstr++;
	}
	printf("%s\n", str);
    return 0;
}
