// AutomatSys.cpp : 定义控制台应用程序的入口点。
//



#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "stdlib.h"

//命名字符串最大长度
#define CMD_LEN                 4096
//命令分隔符
#define CMD_SEPARATRIX          ";"

/* 最大商品名称 */
#define MAX_GOODS_NAME_LEN 2

/* 最大商品个数 */
#define MAX_GOODS_NUM 6

#define min(a,b)    (((a) < (b)) ? (a) : (b))

/* 操作状态码 */
typedef enum tagOpStatus
{
    S001, /* S001:初始化成功 */
    S002, /* S002:投币成功,投币余额=X */
    S003, /* S003:购买成功,投币余额=X */
} opStatus_EN;

//操作错误码定义
typedef enum tagErrCode
{
    E001, //非法命令
    E002, //钱币面额错误
    E003, //零钱不足,投币失败
    E004, //投币余额超出最大范围
    E005, //所有商品售罄
    E006, //商品不存在
    E007, //该商品售罄
    E008, //余额不足
    E009, //退币失败
    E010  //参数错误
}errCode_EN;

/* 函数返回码 */
typedef enum tagRetCode
{
    RET_OK,   /* 成功 */
    RET_ERROR /* 错误 */
} RetCode_EN;

/* 商品定义 */
typedef struct tagGoods
{
    char szName[MAX_GOODS_NAME_LEN + 1]; /* 商品名称 */
    unsigned int nPrice; /* 商品价格 */
    unsigned int nNumber;/* 商品数量 */
}Goods_STRU;

/* 钱币定义 */
typedef struct tagMoney
{
    unsigned int nOneYuanCnt;  /* 1元钱币个数 */
    unsigned int nTwoYuanCnt;  /* 2元钱币个数 */
    unsigned int nFiveYuanCnt; /* 5元钱币个数 */
    unsigned int nTenYuanCnt;  /* 10元钱币个数 */    
}Money_STRU;

/* 商品信息，测试的依据，考生不允许更改商品名称和单价，商品数量在初始化命令中进行设置*/
Goods_STRU g_astGoods[MAX_GOODS_NUM] = 
{  
    //商品名称  价格       数量
    {"A1",       2,        0},
    {"A2",       3,        0},
    {"A3",       4,        0},
    {"A4",       5,        0},
    {"A5",       8,        0},
    {"A6",       6,        0}
};

/* 存钱盒信息，钱币数量在初始化命令中进行设置 */
Money_STRU g_stSaveBox = 
{
    0,   /* 1元钱币个数 */
    0,   /* 2元钱币个数 */
    0,   /* 5元钱币个数 */
    0    /* 10元钱币个数 */  
};

typedef enum tagMoneyType
{
    ONE_YUAN = 1,
	TWO_YUAN = 2,
	FIVE_YUAN = 5,
	TEN_YUAN  = 10
}Money_Type_EN;

/* 
    投币余额：指当前自动售货机中剩余的可购买商品的钱币总额；例如：投入2元面额的
    钱币，钱币余额增加2元；购买一件价格2元的商品，投币余额减少2元；            
*/

unsigned int g_nPayBalance = 0;

/* 考试需要实现的函数 Begin */
void OpReset(Goods_STRU *pstGoods,Money_STRU *pstSaveBox);
void OpPay(unsigned int nMoney);
void OpBuy(char *pszGoodsName);
void OpChange(void);
void OpQuery(unsigned int nMethod);
/* 考试需要实现的函数 End */

/*****************************************************************************
 函 数 名  : libOutputStr
 功能描述  : 内部函数: 考试系统的输出打印函数
 输入参数  : pcStr  输出打印字符串
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void libOutputStr(char* pcStr)
{
	printf("%s\n",pcStr);
}
void cmd_dispatch(char *pszCmd);
/*****************************************************************************
 函 数 名  : cmd_process
 功能描述  : 系统调用的函数,考生无需关注
*****************************************************************************/
void cmd_process(int argc, char* argv[])
{
	unsigned char ucRecvCmdBuff[CMD_LEN]  = {0};
	unsigned char ucSingleCmdBuff[CMD_LEN]= {0};
	unsigned char *pucStartPos = NULL;
	unsigned char *pucEndPos   = NULL;

	/* 
	   所有的命令以;分割，例如：r 1-1-1-1-1-1 10-5-2-1;p 1;q 1; 共三条命令，一条
	   初始化命令，一条付款命令，最后一天为查询命令。
	*/
	gets((char *)ucRecvCmdBuff);

	pucStartPos = ucRecvCmdBuff;
	pucEndPos = (unsigned char *)strstr((char *)pucStartPos,CMD_SEPARATRIX);

	while(NULL != pucEndPos)
	{
		memset(ucSingleCmdBuff,0,sizeof(ucSingleCmdBuff));
		memcpy(ucSingleCmdBuff,pucStartPos,(pucEndPos-pucStartPos));

		cmd_dispatch((char *)ucSingleCmdBuff);
		
		pucStartPos = pucEndPos + 1;
		pucEndPos = (unsigned char *)strstr((char *)pucStartPos,CMD_SEPARATRIX);
	}


	return;
}


/*****************************************************************************
 函 数 名  : apiPrintErrInfo
 功能描述  : 提供给考生的API函数:输出错误信息函数
 输入参数  : enErrCode 错误码枚举值
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void apiPrintErrInfo(errCode_EN enErrCode)
{
    switch (enErrCode)
    {
    	case E001:
    		libOutputStr("E001:非法命令");
    		break;
    	case E002:
            libOutputStr("E002:钱币面额错误");
    		break;
    	case E003:
            libOutputStr("E003:零钱不足,投币失败");
    		break;
    	case E004:
            libOutputStr("E004:投币余额超出最大范围");
    		break;
    	case E005:
            libOutputStr("E005:所有商品售罄");
    		break;
        case E006:
            libOutputStr("E006:商品不存在");
            break;
        case E007:
            libOutputStr("E007:该商品售罄");
        	break;
    	case E008:
            libOutputStr("E008:余额不足");
        	break;
    	case E009:
            libOutputStr("E009:退币失败");
        	break;
    	case E010:
            libOutputStr("E010:参数错误");
            break;
    	default:
    		break;
    }
    
    return;
}

/*****************************************************************************
 函 数 名  : apiPrintPayBalance
 功能描述  : 提供给考生的API函数:输出投币余额
 输入参数  : 
            opStatus_EN enStatus   操作状态
			unsigned int nBalance  投币余额
 输出参数  : 无
 返 回 值  : 无
 输出示例  : S001:投币成功，投币余额=5
*****************************************************************************/
void apiPrintBalance(opStatus_EN enStatus,unsigned int nBalance)
{
	char pszBuf[100] = {0};
    
	switch (enStatus)
    {
		 case S001:
			sprintf(pszBuf,"S001:初始化成功,投币余额=%d",nBalance);
			break;
		 case S002:
			sprintf(pszBuf,"S002:投币成功,投币余额=%d",nBalance);
			break;
		 case S003:
			sprintf(pszBuf,"S003:购买成功,投币余额=%d",nBalance);
			break;
		 default:
			break;
	}

	libOutputStr(pszBuf);	
}
/*****************************************************************************
 函 数 名  : apiPrintGoods
 功能描述  : 提供给考生的API函数:输出商品信息
 输入参数  : Goods_STRU *pstGoods 指向商品信息，本函数不会释放其所指向的内存。 
             unsigned int nCount 打印输出的商品信息个数
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void apiPrintGoods(Goods_STRU *pstGoods,unsigned int nCount)
{
    char pszBuf[1024] = {0};
	
	if(nCount > MAX_GOODS_NUM)
	{
		return;	
	}
    
    for (unsigned int i = 0; i < nCount; i++)
    {
        sprintf(pszBuf + strlen(pszBuf), "%s %d %d\n", pstGoods->szName,pstGoods->nPrice,pstGoods->nNumber);
		pstGoods++;
    }
    
    libOutputStr(pszBuf);
}

/*****************************************************************************
 函 数 名  : apiPrintMoney
 功能描述  : 提供给考生的API函数:输出钱币信息
 输入参数  : Money_STRU stMoney 钱币信息结构，本函数输出不同面额的钱币张数
 输出参数  : 无
 返 回 值  : 无
  输出示例  : 
				1元钱币张数=0
				2元钱币张数=0
				5元钱币张数=1
				10元钱币张数=0
*****************************************************************************/
void apiPrintMoney(Money_STRU stMoney)
{
    char pszBuf[256] = {0};

    sprintf(pszBuf + strlen(pszBuf), "1元钱币张数=%d\n",stMoney.nOneYuanCnt);  
    sprintf(pszBuf + strlen(pszBuf), "2元钱币张数=%d\n",stMoney.nTwoYuanCnt);   
    sprintf(pszBuf + strlen(pszBuf), "5元钱币张数=%d\n",stMoney.nFiveYuanCnt);  
    sprintf(pszBuf + strlen(pszBuf), "10元钱币张数=%d",stMoney.nTenYuanCnt);
    libOutputStr(pszBuf);    
}

void user_cmdproc(char *pszCmd, int iLen)
{
    if (NULL == pszCmd)
    {
        apiPrintErrInfo(E001);
        return;
    }

    cmd_dispatch(pszCmd);

    return;
}

int main(int argc, char* argv[])
{
    cmd_process(argc,argv);
    return 0;
}

void cmd_dispatch(char *pszCmd)
{
    unsigned int nMoney;
    int GetParaCount = 0; //参数个数
    char szGoods[1024]; //商品名称
    unsigned int nMethod;
    char buf[100]  = {0};

    Goods_STRU stGoods[MAX_GOODS_NUM] = 
    {  
        //商品名称  价格       数量
        {"A1",       2,        0},
        {"A2",       3,        0},
        {"A3",       4,        0},
        {"A4",       5,        0},
        {"A5",       8,        0},
        {"A6",       6,        0}
    };
    
    Money_STRU stSaveBox = 
    {
        0, /* 1元钱币个数 */
        0,   /* 2元钱币个数 */
        0,   /* 5元钱币个数 */
        0    /* 10元钱币个数 */  
    };

	switch (*pszCmd)
    {
        case 'r':
        case 'R':
            GetParaCount = sscanf(pszCmd, "%s %u-%u-%u-%u-%u-%u %u-%u-%u-%u",buf,
                &stGoods[0].nNumber,&stGoods[1].nNumber,&stGoods[2].nNumber,&stGoods[3].nNumber,
                &stGoods[4].nNumber,&stGoods[5].nNumber,
                &stSaveBox.nOneYuanCnt,&stSaveBox.nTwoYuanCnt,
                &stSaveBox.nFiveYuanCnt,&stSaveBox.nTenYuanCnt);
            
            if (GetParaCount != 11 || (0 != strcmp(buf, "r") && 0 != strcmp(buf, "R"))
				|| (stGoods[0].nNumber > 10 )
				|| (stGoods[1].nNumber > 10 )
				|| (stGoods[2].nNumber > 10 )
				|| (stGoods[3].nNumber > 10 )
				|| (stGoods[4].nNumber > 10 )
				|| (stGoods[5].nNumber > 10 )
				|| (stSaveBox.nOneYuanCnt > 10 )
				|| (stSaveBox.nTwoYuanCnt > 10 )
				|| (stSaveBox.nFiveYuanCnt > 10 )
				|| (stSaveBox.nTenYuanCnt > 10 ))
            {
                libOutputStr("E001:非法命令");
                break;
            }

            OpReset(stGoods,&stSaveBox);
            libOutputStr("S001:初始化成功");
            break;
            
        case 'p':
        case 'P':
            GetParaCount = sscanf(pszCmd, "%s %u", buf,&nMoney);

            if (2 != GetParaCount || (0 != strcmp(buf, "p") && 0 != strcmp(buf, "P")))
            {
                libOutputStr("E001:非法命令");
                break;
            }
            
            OpPay(nMoney);
            break;

        case 'b':
        case 'B':
            GetParaCount = sscanf(pszCmd, "%s %256s",buf,szGoods);
            if (2 != GetParaCount || (0 != strcmp(buf, "b") && 0 != strcmp(buf, "B")))
            {
                libOutputStr("E001:非法命令");
                break;
            }
            OpBuy(szGoods);
            break;
            
        case 'c':
        case 'C':     
			GetParaCount = sscanf(pszCmd, "%s",buf);
			if (1 != GetParaCount || (0 != strcmp(buf, "c") && 0 != strcmp(buf, "C")))
            {
                libOutputStr("E001:非法命令");
                break;
            }
            OpChange();
            break;
            
        case 'q':
        case 'Q':     
            GetParaCount = sscanf(pszCmd, "%s %u", buf,&nMethod);
            if (2 != GetParaCount || (0 != strcmp(buf, "q") && 0 != strcmp(buf, "Q")) )
            {
                libOutputStr("E001:非法命令");
                break;
            }
            
            OpQuery(nMethod);
            break;  
            
        default:
           apiPrintErrInfo(E001);
            break;
    }
}

/*****************************************************************************
 函 数 名  : OpReset
 功能描述  : 考生需要实现的接口
             完成初始化操作
 输入参数  : Goods_STRU *pstGoods 商品信息
             Money_STRU *pstSaveBox 存钱盒信息
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void OpReset(Goods_STRU *pstGoods,Money_STRU *pstSaveBox)
{
	memcpy(&g_astGoods,  pstGoods,   sizeof(g_astGoods));
	memcpy(&g_stSaveBox, pstSaveBox, sizeof(g_stSaveBox));

	g_nPayBalance = 0;
}


/*****************************************************************************
 函 数 名  : OpPay
 功能描述  : 考生需要实现的接口
             完成投币操作
 输入参数  : unsigned int nMoney 钱币面额
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/

int get_changeSum(void)
{
	return g_stSaveBox.nOneYuanCnt + g_stSaveBox.nTwoYuanCnt * 2;
}

int get_goodsSum(void)
{
	return 	g_astGoods[0].nNumber + g_astGoods[1].nNumber +
			g_astGoods[2].nNumber + g_astGoods[3].nNumber +
			g_astGoods[4].nNumber + g_astGoods[5].nNumber;	
}

void add_money(int money)
{
	switch(money){
		case 1:
			g_stSaveBox.nOneYuanCnt++;
			break;
		case 2:
			g_stSaveBox.nTwoYuanCnt++;
			break;
		case 5:
			g_stSaveBox.nFiveYuanCnt++;
			break;
		case 10:	
			g_stSaveBox.nTenYuanCnt++;
			break;
		default:
			break;
	}
}

void OpPay(unsigned int nMoney)
{
	if((nMoney==1)||(nMoney==2)||(nMoney==5)||(nMoney==10)){

		if((nMoney==5)||(nMoney==10)){	
			if( nMoney>get_changeSum() ){
				apiPrintErrInfo(E003);
				return;
			}
		}

		if( (g_nPayBalance+nMoney)>10 ){
			apiPrintErrInfo(E004);
		}else if( get_goodsSum()==0 ){
			apiPrintErrInfo(E005);
		}else{
			g_nPayBalance += nMoney;
			add_money(nMoney);
			apiPrintBalance(S002, g_nPayBalance);
		}
	}else{
		apiPrintErrInfo(E002);
	}
}


/*****************************************************************************
 函 数 名  : OpBuy
 功能描述  : 考生需要实现的接口
             完成购买商品操作
 输入参数  : char *pszGoodsName 商品名称
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void OpBuy(char *pszGoodsName)
{
	unsigned int id;

	id = *(pszGoodsName+1) - '0';

	if((id>=1)&&(id<=MAX_GOODS_NUM)){
		id = id - 1;
		if(g_astGoods[id].nNumber==0){
			apiPrintErrInfo(E007);
		}else if(g_nPayBalance<g_astGoods[id].nPrice){
			apiPrintErrInfo(E008);
		}else{
			g_astGoods[id].nNumber--;
			g_nPayBalance -= g_astGoods[id].nPrice;
			apiPrintBalance(S003, g_nPayBalance);
		}
	}else{
		apiPrintErrInfo(E006);	
	}
}

/*****************************************************************************
 函 数 名  : OpChange
 功能描述  : 考生需要实现的接口
             完成退币操作
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/

void get_changes(Money_STRU *pchange)
{
	const int money[4] = {1,2,5,10};
	
	unsigned int changes[4];
	unsigned int savebox[4];
	unsigned int tmp;
	int i;

	savebox[0] = g_stSaveBox.nOneYuanCnt;
	savebox[1] = g_stSaveBox.nTwoYuanCnt;
	savebox[2] = g_stSaveBox.nFiveYuanCnt;
	savebox[3] = g_stSaveBox.nTenYuanCnt;
	
	for(i=3; i>=0; i--){
		tmp = g_nPayBalance/money[i];
		if(tmp > savebox[i]){
			tmp = savebox[i];
		}

		changes[i] = tmp;
		g_nPayBalance = g_nPayBalance - tmp * money[i];
	}

	if((g_nPayBalance==1)&&(changes[2]>0)&&(g_stSaveBox.nTwoYuanCnt-changes[1]>=3)){
		changes[2] -= 1;
		changes[1] += 3;
		g_nPayBalance = 0;
	}
	
	if((g_nPayBalance==3)&&(changes[2]>0)&&(g_stSaveBox.nTwoYuanCnt-changes[1]>=4)){
		changes[2] -= 1;
		changes[1] += 4;
		g_nPayBalance = 0;
	}

	g_stSaveBox.nOneYuanCnt  -= changes[0];
	g_stSaveBox.nTwoYuanCnt  -= changes[1];
	g_stSaveBox.nFiveYuanCnt -= changes[2];
	g_stSaveBox.nTenYuanCnt  -= changes[3];

	pchange->nOneYuanCnt  = changes[0];
	pchange->nTwoYuanCnt  = changes[1];
	pchange->nFiveYuanCnt = changes[2];
	pchange->nTenYuanCnt  = changes[3];
}

void OpChange(void)
{
	Money_STRU change;

	if(g_nPayBalance==0){
		apiPrintErrInfo(E009);
	}else{
		get_changes(&change);
		apiPrintMoney(change);	
		g_nPayBalance = 0;
	}
}


/*****************************************************************************
 函 数 名  : OpQuery
 功能描述  : 考生需要实现的接口
             完成系统的查询操作
 输入参数  : unsigned int nMethod
             0、查询自动售货机中商品信息
             1、查询存钱盒信息
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/

void GoodsSort(Goods_STRU **p, int count)
{
	int  i,j;
	Goods_STRU  *pbuff;
	for(i=1; i<count; i++){
		if(p[i]->nNumber > p[i-1]->nNumber){
			pbuff = p[i];

			for(j=i-1; j>=0 && p[j]->nNumber < pbuff->nNumber; j--){
				p[j+1] = p[j];
			}
			p[j+1] = pbuff;
		}
	}
}

void __PrintGoods(Goods_STRU **p, unsigned int nCount)
{
    char pszBuf[1024] = {0};
	
	if(nCount > MAX_GOODS_NUM)
	{
		return;	
	}
    
    for (unsigned int i = 0; i < nCount; i++)
    {
        sprintf(pszBuf + strlen(pszBuf), "%s %d %d\n", p[i]->szName,p[i]->nPrice,p[i]->nNumber);
    }
    
    libOutputStr(pszBuf);
}

void OpQuery(unsigned int nMethod)
{
	Goods_STRU *p[MAX_GOODS_NUM];

	if(nMethod == 0){
	
		p[0] = &g_astGoods[0];
		p[1] = &g_astGoods[1];
		p[2] = &g_astGoods[2];
		p[3] = &g_astGoods[3];
		p[4] = &g_astGoods[4];
		p[5] = &g_astGoods[5];

		GoodsSort((Goods_STRU **)&p, MAX_GOODS_NUM);
		__PrintGoods((Goods_STRU **)&p, MAX_GOODS_NUM);

	}else if(nMethod == 1){
		apiPrintMoney(g_stSaveBox);	
	}else{
		apiPrintErrInfo(E010);
	}
}

