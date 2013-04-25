
#include <stdio.h>

int inside(int num)
{
    do{
        if( num%10 == 7 ) return 1;
        else num = num / 10;
    }while(num!=0);

    return 0;
}

int main(void)
{
    int limit;
    int i;
    int count = 0;

    scanf("%d", &limit);

    for(i=7; i<=limit; i++){
        if( ((i%7)==0) || (inside(i)==1) ){
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}
