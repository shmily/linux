
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main(void)
{
	char *str, *_str, *out, *p;

	str = malloc(1024);
	out = malloc(512);
	memset(str, 0, 1024);
	memset(out, 0, 512);

	scanf("%s", str);

	_str = str;
	p = out;
	while(*str!='\0'){

		switch(*str){
			case 'y':
				*p++ = '1';
				str += 2;
				break;
			case 'e':
				*p++ = '2';
				str += 2;
				break;
			case 's':
				if(*(str+1)=='a'){
					*p++ = '3';
					str += 3;
				}else{
					*p++ = '4';
					str += 2;
				}
				break;
			case 'w':
				*p++ = '5';
				str += 2;
				break;
			case 'l':
				*p++ = '6';
				str += 3;
				break;
			case 'q':
				*p++ = '7';
				str += 2;
				break;
			case 'b':
				*p++ = '8';
				str +=2;
				break;
			case 'j':
				*p++ = '9';
				str +=3;
				break;
			default:
				str++;
				break;
		}
	}

	printf("%s\n", out);

	free(_str);
	free(out);
    return 0;
}
