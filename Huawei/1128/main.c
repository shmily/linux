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

typedef enum tag_E_OPERATOR
{
	E_OPER_NULL, 	/* N */
	E_OPER_ADD, 	/* + */
	E_OPER_SUB, 	/* - */
	E_OPER_MUL, 	/* X */
	E_OPER_DIV 		/* / */
}E_OPERATOR;

int main()
{
	char str[512];

	fgets(str, 512, stdin);

	printf("%s", str);

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
	if(NULL == pThis){
		return -1;
	}
	
	if(IsFull(pThis)!=0){
		return -1;
	}
	
	pThis->pNStackBuf[++(pThis->nStackTop)] = nValue; 
	
	return 0;
}

int Pop(STACK_STRU *pThis)
{
	if(NULL == pThis){
		return -1;
	}

	if(IsEmpty(pThis)!=0){
		return -1;
	}
	
	return pThis->pNStackBuf[pThis->nStackTop--];
}

int IsFull(STACK_STRU *pThis)
{
	if(NULL == pThis){
		return -1;
	}

	return (pThis->nMaxStackTop == pThis->nStackTop)?1:0;
}

int IsEmpty(STACK_STRU *pThis)
{
	if(NULL == pThis){
		return -1;
	}

	return (pThis->nStackTop == -1)?1:0; 
}

int Destory(STACK_STRU *pThis)
{
	if (NULL == pThis){
		return -1;
	}
	
	free(pThis->pNStackBuf);
	return 0;
}
