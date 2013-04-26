
#include <stdio.h>

int main(void)
{
    char str[1024];
    char ch;
    char *p;

    memset(str, 0, sizeof(str));
    scanf("%[^\n]", str);

    p = str;
    do{
        ch = *p;
        if((ch>='A')&&(ch<='Z')){
            if(ch>='V'){
                *p = (ch - 'A' + 'a' - 21);    
            }else{ 
                *p = (ch - 'A' + 'a' + 5);    
            }
        }
        p++;
    }while(*p!='\0');

    printf("%s\n", str);

    return 0;
}
