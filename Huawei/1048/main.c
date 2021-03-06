
#include <stdio.h>
#include <memory.h>

int main(void)
{
    char str[258];
    char *p;
    int  tmp, s, i;
    int  max, max_count;
    int  min, min_index;
    int  count[10], index[10], rap[10];

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
		if((s>=0)&&(s<=9)){
        	count[s] = count[s] + 1;
        	if(index[s]==-1) index[s] = p - str;
		}
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

    printf("%d,%d\n", min_index, count[min_index]);
    return 0;
}
