
#include <stdio.h>
#include <ctype.h>
#include <memory.h>

char* parse_str(char *src, char *buff, char end_val)
{
	char *p_input;
	char *p_save;
	int  new_str;

	new_str = 1;
	p_input = src;
	p_save  = buff;
	while(*p_input!=end_val){
		if(new_str == 1){
			if(*p_input != ' '){
				new_str = 0;
				*p_save++ = *p_input;
			}
		}else{
			*p_save++ = *p_input;
		}
		p_input++;
	}

	return p_input;
}

int main(void)
{
    char str[1024];
	char str1[256],str2[256];
	char *pnext;
	char *pstr1, *pstr2;
	int  position;

    memset(str,  0, sizeof(str));
    memset(str1, 0, sizeof(str1));
    memset(str2, 0, sizeof(str2));
    scanf("%[^\n]", str);

	pnext = parse_str(str, str1, ',');
	pnext++;
	parse_str(pnext, str2, '\0');

	pstr1 = str1;
	pstr2 = str2;
	while(tolower(*pstr1) == tolower(*pstr2)){
		if(*pstr1++ == '\0') break;
		pstr2++;
	}

	if(tolower(*pstr1)==tolower(*pstr2)){
		position = -1;
	}else{
		position = pstr1 - str1;
	}

	printf("%d\n", position);

    return 0;
}
