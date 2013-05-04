/*
=============================================================================
#
#        Author : shmily - shmily@mail.dlut.edu.cn
#            QQ : 723103903
# Last modified : 2013-04-18 20:47
#      Filename : Pascal.c
#   Description : not thing...
#
=============================================================================
*/

#include "stdio.h"
int main(void)
{
    int in, sum;
    sum = 0;
    while(scanf("%d",&in)!=EOF){
        if(in>0)
            if( ((in)&(in-1))==0 ) sum++;

        if(getchar()=='\n') break;
    }
    printf("%d\n", sum);
    return 0;
}

