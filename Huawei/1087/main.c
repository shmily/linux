
#include <stdio.h>

int main(void)
{
    char str[1024];
    char str_rev[1024];
    char *p;
    char *p_rev;

    memset(str, 0, sizeof(str));
    memset(str_rev, 0, sizeof(str));
    scanf("%[^\n]", str);

    p = str + strlen(str) - 1;
    p_rev = str_rev;
    do{
        *p_rev++ = *p--;
    }while(p>=str);

    printf("%s\n", str_rev);

    return 0;
}
