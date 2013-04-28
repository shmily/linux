
#include <stdio.h>
#include <memory.h>

int _test = 0;

int search(int *p, int len, int target)
{
    int low  = -1;
    int high = len;
    int probe;

    while(high-low > 1){
        probe = (low + high)>>1;
        if(*(p+probe)>target){
            high = probe;
        }else{
            low = probe;
        }

        _test++;
    }

    if((low==-1)||(*(p+low)!=target))
        return -1;
    else
        return low;
}

int main(void)
{
    int i;
    int count;
    int *p, *pboy, *pgirl;
    int *_p, *_pboy, *_pgirl;
    int position_b, _count;

while(1){

    scanf("%d", &count);

    if(count<=0) break;

    count = count*2;
    p     = (int *)malloc(sizeof(int)*count);
    pboy  = (int *)malloc(sizeof(int)*count);
    pgirl = (int *)malloc(sizeof(int)*count);

    _p = p;
    _pboy = pboy;
    _pgirl = pgirl;

    i = 0;
    while(i<count){
        scanf("%d", p+i);
        i++;
    }

    *pboy++  = *p;
    pgirl = pgirl+count-1;
    *pgirl-- = *(p+count-1);
    for(i=1; i<count; i++){
        *pboy  = *(pboy-1)  + *(p+i);
        *pgirl = *(pgirl+1) + *(p+count-1-i);
        pboy++;
        pgirl--;
    }

    pboy = _pboy;
    pgirl = _pgirl;
    for(i=0; i<count; i++){
        printf("%d ", *(pboy+i));
    }
    printf("\n");
    
    for(i=0; i<count; i++){
        printf("%d ", *(pgirl+i));
    }
    printf("\n");


    _count = count;
    count = count-1;
    for(i=1; i<_count; i++){
        position_b = search(_pboy, count, *(_pgirl+i));

        if(position_b!=-1){
            printf("G:%d, B:%d\n", i+1, position_b+1);
            count = position_b;
        }
    }

    printf("%d\n", _test);

    free(_p);
    free(_pboy);
    free(_pgirl);
}

    return 0;
}
