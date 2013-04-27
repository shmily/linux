
#include <stdio.h>
#include <memory.h>

int main(void)
{
    char str[1024];
	char *p;
    char *p_head, *p_tail;
	int  i;

	for(i=0; i<3; i++){
    scanf("%s", str);

	p_head = strstr(str, "/*");

	if(p_head!=NULL){

		p_tail = str + strlen(str) - 1;
		while(p_tail>=p_head+4){
			if( *p_tail=='/' && *(p_tail-1)=='*' ){
				break;
			}
			p_tail--;
		}

		if(p_tail>=p_head+4){
			
			p_head = p_head+2;
			p_tail = p_tail-2;

			p = p_head;

			while(p_head<p_tail){
				if( ((*p_head=='/')&&(*(p_head+1)=='*')) || ((*p_head=='*')&&(*(p_head+1)=='/')) ){
					p_head = p_head+2;
				}else{
					*p++ = *p_head++;
				}
			}

			if(p_head==p_tail) *p++ = *p_head;

			strcpy(p, p_tail+1);
		}
	}

	printf("%s\n", str);
}

    return 0;
}
