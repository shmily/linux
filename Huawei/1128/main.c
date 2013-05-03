#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 10
#define MAX_FAMULA_SIZE 1024

typedef struct tag_STACK_STRU
{ 	int nStackTop;
	int nMaxStackTop;
	int *pNStackBuf;
}STACK_STRU;

int Init	(STACK_STRU *pThis, int nMaxSize);
int Destory	(STACK_STRU *pThis);
int Push	(STACK_STRU *pThis, int nValue);
int Pop		(STACK_STRU *pThis);
int IsFull	(STACK_STRU *pThis);
int IsEmpty	(STACK_STRU *pThis);

STACK_STRU g_stOperator;
STACK_STRU g_stOperand;

//------------------------------------------------

// mask : 0 for operator, 1 for operand
int infix_init(char *pstr, int *postfix, int *mask)
{
    int count;
    int sign = 1;
    int tmp;
    int *psave;

    // skip the begin spaces.
    while(*pstr==' '){
        pstr++;
    }

    // incase the first operand's sign.
    if(*pstr=='-'){
        sign = -1;
        pstr++;
    }

    psave = postfix;
    count = 0;
    tmp   = 0;
    while(*pstr!='\0'){

        if((*pstr>='0')&&(*pstr<='9')){
            tmp = tmp*10 + (*pstr - '0');
            pstr++;
        }else if((*pstr=='+')||(*pstr=='-')||(*pstr=='*')||(*pstr=='/')){
            *psave++ = tmp;
            *mask++ = 1;
            *psave++ = *pstr;
            *mask++ = 0;
            count += 2;
            tmp = 0;
            pstr++;
        }else{
            pstr++;
        }
    }
   
	*psave++ = tmp;
	*mask++ = 1;
	count += 1;
	pstr++;

    *postfix = *postfix * sign;
    return count;
}

void infix2posfix(int *postfix, int *mask, int count)
{
    int buff[32];
    int flag[32];

    int i, tmp;
    int *psave, *psource, *pmask;

    memset(buff, 0, sizeof(int)*32);
    memset(flag, 0, sizeof(int)*32);

    Init(&g_stOperator, MAX_STACK_SIZE);

    psave   = buff;
    pmask   = flag;
    psource = postfix;
    for(i=0; i<count; i++){
        if(mask[i]==1){
            *psave++ = *psource;
            *pmask++ = 1;
        }else{
            if((*psource=='+')||(*psource=='-')){
                while(IsEmpty(&g_stOperator)!=1){
                    *psave++ = Pop(&g_stOperator);
                    *pmask++ = 0;
                }
                Push(&g_stOperator, *psource);
            }else{
                while(IsEmpty(&g_stOperator)!=1){
                    tmp = Pop(&g_stOperator);
                    if((tmp=='+')||(tmp=='-')){
                        Push(&g_stOperator, tmp);
                        Push(&g_stOperator, *psource);
                        break;
                    }else{
                        *psave++ = tmp;
                        *pmask++ = 0;
                    }
                }

                if(IsEmpty(&g_stOperator)==1){
					Push(&g_stOperator, *psource);
				}
            }
        }

        psource++;
    }

    while(IsEmpty(&g_stOperator)!=1){
        *psave++ = Pop(&g_stOperator);
        *pmask++ = 0;
    }

    memcpy(postfix, buff, sizeof(int)*32);
    memcpy(mask,    flag, sizeof(int)*32);
}

int postfix_calu(int *postfix, int *mask, int count)
{
    int a1, a2, tmp;
    int i;

    Init(&g_stOperand, MAX_STACK_SIZE);

    for(i=0; i<count; i++){
        if(*mask==1){
            Push(&g_stOperand, *postfix);
        }else{
            tmp = 0;
            a2 = Pop(&g_stOperand);
            a1 = Pop(&g_stOperand);
            switch(*postfix){
                case '+': tmp = a1 + a2;
                          break;
                case '-': tmp = a1 - a2;
                          break;
                case '*': tmp = a1 * a2;
                          break;
                case '/': tmp = a1 / a2;
                          break;
                default:  break;
            }

            Push(&g_stOperand, tmp);
        }
        mask++;
        postfix++;
    }

    return Pop(&g_stOperand);
}

int main()
{
	char 	str[512];
    int 	postfix[32];
    int 	mask[32];
    int		count, i;

	gets(str);
    count = infix_init(str, postfix, mask);
    infix2posfix(postfix, mask, count);
	
	i = postfix_calu(postfix, mask, count);

	printf("%d\n", i);

	Destory(&g_stOperand);
	Destory(&g_stOperator);
	return 0;
}

int Init(STACK_STRU *pThis,int nMaxSize)
{
	if (NULL == pThis){
		return -1;
	}
	
	pThis->nMaxStackTop = nMaxSize - 1;
	pThis->nStackTop = -1;
	pThis->pNStackBuf = (int *)malloc(sizeof(int) * nMaxSize);
	
	if (NULL == pThis->pNStackBuf){ 
		return -1;
	}
	
	return 0;
}

int Push(STACK_STRU *pThis,int nValue)
{
	pThis->pNStackBuf[++(pThis->nStackTop)] = nValue; 
	return 0;
}

int Pop(STACK_STRU *pThis)
{
	return pThis->pNStackBuf[pThis->nStackTop--];
}

int IsFull(STACK_STRU *pThis)
{
	return (pThis->nMaxStackTop == pThis->nStackTop)?1:0;
}

int IsEmpty(STACK_STRU *pThis)
{
	return (pThis->nStackTop == -1)?1:0; 
}

int Destory(STACK_STRU *pThis)
{
	free(pThis->pNStackBuf);
	return 0;
}
