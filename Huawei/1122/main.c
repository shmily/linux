
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

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
	int *pos_b, *pos_g, *_pos_b;
	int result;

	while(1){

    	scanf("%d", &count);
    	if(count<=0) break;

    	count = count*2;
    	p     = (int *)malloc(sizeof(int)*count);
    	pboy  = (int *)malloc(sizeof(int)*count);
    	pgirl = (int *)malloc(sizeof(int)*count);
		pos_b = (int *)malloc(sizeof(int)*count);

    	_p = p;
    	_pboy = pboy;
    	_pgirl = pgirl;
		_pos_b = pos_b;

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

		pos_g = _p;
		memset(pos_g, 0, count);
		memset(pos_b, 0, count);
		result = 1;
		*pos_g++ = 1;
		*pos_b++ = count;

    	_count = count;
    	count = count-1;
    	for(i=1; i<_count; i++){
        	position_b = search(_pboy, count, *(_pgirl+i));

        	if(position_b!=-1){
				*pos_g++ = i+1;
				*pos_b++ = position_b+1;
				result++;
            	count = position_b;
        	}
    	}

		pos_g = _p;
		pos_b = _pos_b;

		printf("共有%d种站法\n", result);
		for(i=0; i<result; i++){
			printf("第%d种站法:女方站位置%d,男方站位置%d\n", i+1, *pos_g++, *pos_b++);	
		}

    	free(_p);
    	free(_pboy);
    	free(_pgirl);
		free(_pos_b);
	}

    return 0;
}
