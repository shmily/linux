#include <stdio.h> 
  
int main(void) 
{ 
    int t1_s,t1_x,t2_s,t2_x; 
    int sum_s,sum_x,mul_s,mul_x; 
    short temp_s,temp_x; 
    int temp,input,T,i; 
    int *ptemp; 
    scanf("%d",&T); 
    if(T==0) 
    { 
        printf("0"); 
        return 0; 
    } 
    if(T%2==1||T>1000) 
        return 0; 
    sum_s = 0;sum_x = 0; 
    for(i=0;i<T/2;i++) 
    { 
        if(i!=0) 
            scanf(","); 
        scanf("%d,",&input);         
        temp = input; 
        //temp_s = (temp & 0xffff0000) >> 16; 
        //temp_x = input & 0x0000ffff; 
        temp_s = 32767; 
        temp_x = 4; 
        t1_s = temp_s;t1_x = temp_x; 
        scanf("%d",&input); 
        temp = input; 
        //temp_s = (temp & 0xffff0000) >> 16; 
        //temp_x = input & 0x0000ffff; 
        temp_s = 4; 
        temp_x = -32767; 
        t2_s = temp_s;t2_x = temp_x; 
        mul_s = t1_s*t2_s - t1_x*t2_x; 
        mul_x = t1_s*t2_x + t1_x*t2_s; 
        if(mul_s > 32767) 
            mul_s = 32767; 
        else if(mul_s < -32768) 
            mul_s = -32768; 
        if(mul_x > 32767) 
            mul_x = 32767; 
        else if(mul_x < -32768) 
            mul_x = -32768; 
        sum_s += mul_s; 
        sum_x += mul_x; 
        if(sum_s > 32767) 
            sum_s = 32767; 
        else if(sum_s < -32768) 
            sum_s = -32768; 
        if(sum_x > 32767) 
            sum_x = 32767; 
        else if(sum_x < -32768) 
            sum_x = -32768; 
    } 
    sum_s = sum_s/T; 
    sum_x = sum_x/T; 
    if(sum_s > 32767) 
        sum_s = 32767; 
    else if(sum_s < -32768) 
        sum_s = -32768; 
    if(sum_x > 32767) 
        sum_x = 32767; 
    else if(sum_x < -32768) 
        sum_x = -32768; 
    temp_s = sum_s; 
    temp_x = sum_x; 
    ptemp = &temp; 
    *(short *)ptemp = temp_x; 
    *((short *)ptemp + 1) = temp_s; 
    printf("%d",temp); 
    return 0; 
}
