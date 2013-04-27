
#include <stdio.h>
#include <memory.h>

int main(void)
{
    char str[258];
    char *p;
    char ch;
    char new_word;

    memset(str, 0, sizeof(str));
    scanf("%[^\n]", str);

    p = str;
    new_word = 1;
    do{
        ch = *p;
        if((ch==' ')||(ch==',')||(ch=='.')){
            new_word = 1;
        } else {
            if(new_word == 1){
                new_word = 0;
                if(ch>'Z') *p = (ch - 'a' + 'A');
            }
        }
        p++;
    }while(*p!='\0');

    printf("%s\n", str);

    return 0;
}
