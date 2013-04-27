
#include <stdio.h>
#include <memory.h>

char * mis[10]={
	"wang fei",
	"zhang man yu",
	"zhang zhi yi",
	"li li",
	"li xiao man",
	"li yu cun",
	"yang ni",
	"xiao tong",
	"li lei",
	"zhang san"};

void init_mask(char *p)
{
	int  i;
	char *pname;

	memset(p, 0, 26*10);

	for(i=0; i<10; i++){
		pname = mis[i];
		while(*pname!='\0'){
			if(*pname!=' ')
				*(p+(*pname - 'a')) = 1;
			pname++;
		}

		p = p + 26;
	}
}

int main(void)
{
	int  i;
    char mr[32];
	char mask[10][26];

	int  index;
	char *p;
	int  rap[10];
	int  max;

	init_mask((char *)mask);
    scanf("%[^\n]", mr);

	memset(rap, 0, sizeof(rap));
	p = mr;
	while(*p!='\0'){
		if(*p!=' '){
			index = *p - 'a';
			for(i=0; i<10; i++){
				rap[i] = rap[i] + mask[i][index];
				mask[i][index] = 0;
			}
		}
		p++;
	}

	max = 0;
	index = 0;
	for(i=0; i<10; i++){
		if(rap[i]>max){
			max = rap[i];
			index = i;
		}
	}

	printf("%s\n", mis[index]);

    return 0;
}
