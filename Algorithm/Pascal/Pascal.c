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

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main(int argc, char *argv[])
{
    int n; 
    int *pbuff;
    int *p;
    int tmp, tmp2;
    int i,j;

    if(argc != 2){
        printf("Tips : ./Pascal num\n");
        exit(1);
    }

    n = atoi(argv[1]);

    pbuff = malloc(sizeof(int)*n);
    memset(pbuff, 0, sizeof(int)*n);

    *(pbuff) = 1;

    for(i=0; i<n; i++){
       
        for(j=0; j<n-i-1; j++){
            printf("   ");
        }

        p = pbuff;
        tmp = *p;
        printf("%6d", *p);
        for(j=0; j<i; j++){
            tmp2 = *(p+1);
            *(p+1) = tmp + *(p+1);
            tmp = tmp2;
            p++;
            printf("%6d", *p);
        }

        printf("\n");
    }

    return 0;
}
