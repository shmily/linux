
#include <stdio.h>
#include <memory.h>

int main(void)
{
    char str[258];

    char *p;
    int  tmp;
    int  s;
    int  i;
    int  count[10];
    int  index[10];

    int  max;
    int  max_count;
    int  rap[10];

    int  min;
    int  min_index;

    memset(str, 0, sizeof(str));

    for(i=0; i<10; i++){
        count[i] = 0;
        index[i] = -1;
    }

    scanf("%s", str);

    p   = str;
    tmp = *p++;
    while(tmp!=0){
        s = tmp - '0';
        count[s] = count[s] + 1;
        if(index[s]==-1) index[s] = p - str;
        tmp = *p++;
    }

    max = 0;
    for(i=0; i<10; i++){
        if(count[i]>max) max = count[i];
    }

    max_count = 0;
    memset(rap, 0, sizeof(rap));
    for(i=0; i<10; i++){
        if(count[i] == max){
            rap[max_count] = i;
            max_count++;
        }
    }

    min = 257;
    min_index = 0;
    for(i=0; i<max_count; i++){
        if(index[rap[i]]<min){
            min = index[rap[i]];
            min_index = rap[i];
        }
    }

    for(i=0; i<10; i++){
        printf("%d ", i);
    }
    printf("\n");
    
    for(i=0; i<10; i++){
        printf("%d ", count[i]);
    }
    printf("\n");
    
    for(i=0; i<10; i++){
        printf("%d ", index[i]);
    }

    printf("\n");

    printf("max = %d\n", max);

    for(i=0; i<max_count; i++){ 
        printf("%d ", rap[i]);
    }
    printf("\n");

    printf("min = %d, min_index = %d\n", min, min_index);


    printf("count num = %d, count = %d\n", min_index, count[min_index]);
    return 0;
}
