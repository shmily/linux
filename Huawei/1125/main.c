#include "stdio.h"
#include "string.h"

#define  M_INIT_BALANCE           3000

#define  M_INIT_POINT             150

#define  M_MAX_REC_NUM            5

#define  M_MAX_GOODS_NUM          100

#define  M_FOOD_ORIG_PRICE        10

#define  M_DRESS_ORIG_PRICE       120

#define  M_BOOK_ORIG_PRICE        30

#define  M_TOTAL_PRICES_VALUE     500

#define  M_TOTAL_PRICES_DISCOUNT  0.8

#define  M_TOTAL_PRICES_POINT     120

typedef enum tagGoodsNo
{
    Food,   
    Dress,  
    Book,   
    Goods_butt
} GoodsNo_EN;

typedef enum tagCheap
{
    Orignal_en,   
    Discount_en,   
    Depreciate_en,
    Cheap_butt
} Cheap_EN;

typedef struct tagCardInfo
{
    unsigned int nBalance;
    unsigned int nPoint;   
} CardInfo_S;

typedef struct tagBillRec
{
    unsigned int nNo;      
    unsigned int nCnt;    
    unsigned int nCheap;  
} BillRec_S;


void opInitProc();

void opOrderProc(unsigned int nNo, unsigned int nCnt);

void opCancelProc(unsigned int nNo, unsigned int nCnt);

void opBuyProc();

void opListProc(unsigned int nMethod);

int g_nExamProgramRunMode = 0;

typedef struct tagShopBag
{
    unsigned int nBillNum;               
    BillRec_S    astRec[M_MAX_REC_NUM];  
} ShopBag_S;

typedef struct tagGoodsInfo
{
    BillRec_S     stBillRec;
    unsigned int  (*pCalcFun)(unsigned int, unsigned int, unsigned int, 
    unsigned int *);
} GoodsInfo_S;

ShopBag_S  g_stShopBag;

CardInfo_S g_stCardInfo;

GoodsInfo_S  g_astGoodsRec[Goods_butt][Cheap_butt];

typedef enum tagOpStatus
{
    S001, 
    S002, 
    S003 
} opStatus_EN;

typedef enum tagErrCode
{
    E001, 
    E002,
    E003, 
    E004, 
    E005,
    E006  
} errCode_EN;

typedef enum tagRetCode
{
    RET_OK,  
    RET_ERROR 
} RetCode_EN;

void apiPrintOpStatusInfo(opStatus_EN enStatus);

void apiPrintErrInfo(errCode_EN enErrCode);

void apiPrintCartInfo(unsigned int nBalance, unsigned int nPoint);

void apiPrintShopBagInfo(unsigned int nBillNum, unsigned int nFood, 
unsigned int nDress, unsigned int nBook);

void apiPrintConsumeInfo(unsigned int nTotal, unsigned int nConsumePoint, 
unsigned int nAddPoint);


unsigned int apiCalcPrice(unsigned int nNo, unsigned int nCnt, unsigned int nCheap, unsigned int *pnPrice);


// ---- add by ZengYajian
void lowlevel_sort(unsigned int *food, unsigned int *dress, unsigned int *book);


#define SAPI_BUFFER_LEN 10240
#define DEFAULT_IO_PORT 5555
#define DEFAULT_EXAM_CENTER_PORT 6666
#define libOutputStr printf


typedef enum WORK_MODE_ENUM
{
    EN_WORK_MODE_HEX = 0,
    EN_WORK_MODE_ASCII = 1,
}WORK_MODE_EN;

void user_cmdproc(char *pszCmd, int iLen);

/* 系统框架 */
int main()
{
    char stCmnStr[100] = {0};
    char stGopStr[100] = {0};
    char stTotalCmd[100] = {0};
    opInitProc();


   while(1)
   {
       scanf("%s", stCmnStr);
        switch (stCmnStr[0])
        {
            case 'r': 
            case 'R':
            stTotalCmd[0] = 'r';
            break;
            case 'o': 
            case 'O':
            scanf("%s", stGopStr);
            memcpy(stTotalCmd,"o ",2);
            strcat(stTotalCmd,stGopStr);
            //sprintf(stTotalCmd,"%s %s", "o", stGopStr);
            break;
            case 'c':
            case 'C':
            scanf("%s", stGopStr);
            memcpy(stTotalCmd,"c ",2);
            strcat(stTotalCmd,stGopStr);
            //sprintf(stTotalCmd,"%s %s", "c", stGopStr);
            break;
            case 'b': 
            case 'B':
            stTotalCmd[0] = 'b';
            break;
            case 'l': 
            case 'L':

            scanf("%s", stGopStr);
            memcpy(stTotalCmd,"l ",2);
            strcat(stTotalCmd,stGopStr);
            //sprintf(stTotalCmd,"%s %s", "l", stGopStr);
            break;
            case 'E':
            case 'e':
            return 0;
            default:
            break;
        }

    user_cmdproc((char *)stTotalCmd, strlen(stTotalCmd));

    memset(stCmnStr, 0 , 100);
    memset(stGopStr, 0 , 100);
    memset(stTotalCmd, 0 , 100);

   }  
   
   return 0;
}

/* 系统框架,供调用 */
void apiPrintOpStatusInfo(opStatus_EN enStatus)
{
    switch (enStatus)
    {
        case S001:
            libOutputStr("S001:初始化成功\n");
            break;
        case S002:
            libOutputStr("S002:订单已经加入到购物车\n");
            break;
        case S003:
            libOutputStr("S003:订单已从购物车中删除\n");
            break;
        default:
            break;
    }
    
    return;
}

/* 系统框架,供调用 */
void apiPrintErrInfo(errCode_EN enErrCode)
{
    switch (enErrCode)
    {
        case E001:
            libOutputStr("E001:非法命令\n");
            break;
        case E002:
            libOutputStr("E002:参数错误\n");
            break;
        case E003:
            libOutputStr("E003:购物车已满\n");
            break;
        case E004:
            libOutputStr("E004:待删除的订单不存在\n");
            break;
        case E005:
            libOutputStr("E005:购物车中没有商品订单\n");
            break;
        case E006:
            libOutputStr("E006:购物卡余额或积分不足\n");
            break;
        default:
            break;
    }
    
    return;
}

/* 系统框架,供调用 */
void apiPrintCartInfo(unsigned int nBalance, unsigned int nPoint)
{
    char pszBuf[100] = {0};

    sprintf(pszBuf, "余额=%d\n积分=%d\n", nBalance, nPoint);

    libOutputStr("%s",pszBuf);

    return;
}

/* 系统框架,供调用 */
void apiPrintConsumeInfo(unsigned int nTotal, unsigned int nConsumePoint,unsigned int nAddPoint)
{
    char pszBuf[100] = {0};

    sprintf(pszBuf, "消费金额=%d\n消费积分=%d\n新增积分=%d\n", 
            nTotal, nConsumePoint, nAddPoint);

    libOutputStr("%s", pszBuf);

    return;
}

/* 系统框架,供调用 */
void apiPrintShopBagInfo(unsigned int nBillNum, unsigned int nFood, 
unsigned int nDress, unsigned int nBook)
{
    char pszBuf[200] = {0};

    sprintf(pszBuf, "订单数=%d\n食品=%d\n服装=%d\n书籍=%d\n", 
            nBillNum, nFood, nDress, nBook);

    libOutputStr("%s", pszBuf);

    return;
}

/* 系统框架,供调用 */
unsigned int apiCalcPrice(unsigned int nNo, unsigned int nCnt, unsigned int nCheap, unsigned int *pnPrice)
{
    unsigned int nRet = RET_OK;

    if (NULL == pnPrice)
    {
        return RET_ERROR;
    }
    
    switch (nNo)
    {
        case Food:
            switch (nCheap)
            {
                case Orignal_en:
                    *pnPrice = M_FOOD_ORIG_PRICE * nCnt;
                    break;
                case Discount_en:
                    *pnPrice = (unsigned int)(M_FOOD_ORIG_PRICE * nCnt * 0.9);
                    break;
                case Depreciate_en:
  *pnPrice = M_FOOD_ORIG_PRICE * nCnt - (M_FOOD_ORIG_PRICE * nCnt / 100) * 18;
                    break;
                default:
                    nRet = RET_ERROR;
                    break;
            }
            break;
        case Dress:
            switch (nCheap)
            {
                case Orignal_en:
                    *pnPrice = M_DRESS_ORIG_PRICE * nCnt;
                    break;
                case Depreciate_en:
 *pnPrice = M_DRESS_ORIG_PRICE * nCnt - (M_DRESS_ORIG_PRICE * nCnt / 200) * 40;
                    break;
                case Discount_en:
                default:
                    nRet = RET_ERROR;
                    break;
            }
            break;
        case Book:
            switch (nCheap)
            {
                case Orignal_en:
                    *pnPrice = M_BOOK_ORIG_PRICE * nCnt;
                    break;
                case Discount_en:
                    *pnPrice = (unsigned int)(M_BOOK_ORIG_PRICE * nCnt * 0.5);
                    break;
                case Depreciate_en:
                default:
                    nRet = RET_ERROR;
                    break;
            }
            break;
        default:
            nRet = RET_ERROR;
            break;
    }

    return nRet;
}

/* 系统框架 */
void user_cmdproc(char *pszCmd, int iLen)
{
    //unsigned int   nNum      = 0;
    unsigned int   nGNo      = 0;
    unsigned int   nGCnt     = 0;
    unsigned int   nMethod   = 0;
    unsigned int   nRet      = 0;
    char           buf[100]  = {0};

    switch (*pszCmd)
    {
        case 'r': 
        case 'R':
            if (iLen != 1)
            {
                apiPrintErrInfo(E001);
                return;
            }
            opInitProc();
            apiPrintOpStatusInfo(S001);
            break;
            
        case 'o': 
        case 'O':
            if (' ' == pszCmd[2])
            {
                apiPrintErrInfo(E001);
                return;
            }
            nRet = sscanf(pszCmd, "%s %d-%d", buf, &nGNo, &nGCnt);
            if (3 != nRet || (0 != strcmp(buf, "o") && 0 != strcmp(buf, "O")))
            {
                apiPrintErrInfo(E001);
                return;
            }
            opOrderProc(nGNo, nGCnt);
            break;

        case 'c':
        case 'C':
            if (' ' == pszCmd[2])
            {
                apiPrintErrInfo(E001);
                return;
            }
            nRet = sscanf(pszCmd, "%s %d-%d", buf, &nGNo, &nGCnt);
            if (3 != nRet || (0 != strcmp(buf, "c") && 0 != strcmp(buf, "C")))
            {
                apiPrintErrInfo(E001);
                return;
            }
            opCancelProc(nGNo, nGCnt);
            break;

        case 'b': 
        case 'B':
            if (iLen != 1)
            {
                apiPrintErrInfo(E001);
                return;
            }
            opBuyProc();
            break;

        case 'l': 
        case 'L':
            if (' ' == pszCmd[2])
            {
                apiPrintErrInfo(E001);
                return;
            }
            nRet = sscanf(pszCmd, "%s %d", buf, &nMethod);
            if (2 != nRet || (0 != strcmp(buf, "l") && 0 != strcmp(buf, "L")))
            {
                apiPrintErrInfo(E001);
                return;
            }
            opListProc(nMethod);
            break;

        default: 
            apiPrintErrInfo(E001);
            break;
    }

    return;
}

/* 参考函数,供调用 */
void getGoodsInfo(unsigned int nNo, unsigned int *pnCnt, unsigned int *pnCheap)
{
    unsigned int i    = 0;

    *pnCnt = 0;
    *pnCheap = Cheap_butt;
    for (i = 0; i < M_MAX_REC_NUM; i++)
    {
        if (nNo == g_stShopBag.astRec[i].nNo)
        {
            *pnCnt  += g_stShopBag.astRec[i].nCnt;
            *pnCheap = g_stShopBag.astRec[i].nCheap;
        }
    }

    return;
}

/* 初始化，参考实现 */
void opInitProc()
{
    int i, j;
    
    g_stCardInfo.nBalance = M_INIT_BALANCE;
    g_stCardInfo.nPoint   = M_INIT_POINT;

    memset(g_astGoodsRec, 0, sizeof(g_astGoodsRec));
    memset(&g_stShopBag, 0xff, sizeof(g_stShopBag));
    g_stShopBag.nBillNum = 0;

    for (i = 0; i < Goods_butt; i++)
    {
        for (j = 0; j < Cheap_butt; j++)
        {
            g_astGoodsRec[i][j].pCalcFun = apiCalcPrice;
        }
    }
    
    return;
}

/* 下订单，考生实现 */
void opOrderProc(unsigned int nNo, unsigned int nCnt)
{
	int i;

	if((nNo<Food)||(nNo>Book)||(nCnt<=0)||(nCnt>M_MAX_GOODS_NUM)){
		apiPrintErrInfo(E002);
		return;	
	}

	if(g_stShopBag.nBillNum>=M_MAX_REC_NUM){
		apiPrintErrInfo(E003);
		return;
	}

	for(i=0; i<M_MAX_REC_NUM; i++){
		if(g_stShopBag.astRec[i].nNo==-1){
			g_stShopBag.astRec[i].nNo  = nNo;
			g_stShopBag.astRec[i].nCnt = nCnt;
			g_stShopBag.nBillNum++;	
			break;
		}
	}

    apiPrintOpStatusInfo(S002);
    return;
}

/* 取消订单，考生实现 */
void opCancelProc(unsigned int nNo, unsigned int nCnt)
{	
	int i;
	int find = 0;

	if((nNo<Food)||(nNo>Book)||(nCnt<=0)||(nCnt>M_MAX_GOODS_NUM)){
		apiPrintErrInfo(E002);
		return;	
	}

	if(g_stShopBag.nBillNum==0){
		apiPrintErrInfo(E005);
		return;
	}

	for(i=0; i<M_MAX_REC_NUM; i++){
		if((g_stShopBag.astRec[i].nNo==nNo)&&(g_stShopBag.astRec[i].nCnt==nCnt)){
			find = 1;
			g_stShopBag.nBillNum--;
			g_stShopBag.astRec[i].nNo    = -1;
			g_stShopBag.astRec[i].nCnt   = -1;
			g_stShopBag.astRec[i].nCheap = -1;
			break;
		}
	}

	if(find==1)
    	apiPrintOpStatusInfo(S003);
	else
		apiPrintErrInfo(E004);
    return;
}
/* 参考函数,供调用 */
void findBestTotalMethod(unsigned int *pnSum, unsigned int *pnAvailPoint)
{
    *pnAvailPoint = 0;
    if (*pnSum >= M_TOTAL_PRICES_VALUE)
    {
        if (g_stCardInfo.nPoint >= M_TOTAL_PRICES_POINT)
        {
            *pnAvailPoint = M_TOTAL_PRICES_POINT;
        }
        else
        {
            *pnAvailPoint = g_stCardInfo.nPoint;
        }

        if (*pnSum - *pnAvailPoint >= *pnSum * M_TOTAL_PRICES_DISCOUNT)
        {
            *pnSum = (unsigned int)(*pnSum * M_TOTAL_PRICES_DISCOUNT);
            *pnAvailPoint = 0;
        }
        else
        {
            *pnSum -= *pnAvailPoint;
        }
    }
    return;
}
/* 参考函数,供调用 */
void getBestBuy(unsigned int *pnSum, unsigned int *pnPoint)
{
    unsigned int i    = 0;
    unsigned int j    = 0;
    unsigned int k    = 0;
    unsigned int nGoods;
    unsigned int anPrice[Goods_butt] = {0};
    unsigned int nAvailPoint = 0;
    unsigned int nSum = 0xffffffff;
    unsigned int nCurSum = 0;
    unsigned int anCnt[Goods_butt] = {0};
    unsigned int anCheap[Goods_butt] = {0};

    for (nGoods = Food; nGoods < Goods_butt; nGoods++)
    {
        getGoodsInfo(nGoods, &anCnt[nGoods], &anCheap[nGoods]);
    }

    for (i = 0; i < Cheap_butt; i++)
    {
        for (j = 0; j < Cheap_butt; j++)
        {
            for (k = 0; k < Cheap_butt; k++)
            {
                memset(anPrice, 0, sizeof(anPrice));
if ((g_astGoodsRec[Food][i].pCalcFun(Food, anCnt[Food], i, &anPrice[Food]))
|| (g_astGoodsRec[Dress][j].pCalcFun(Dress, anCnt[Dress], j, &anPrice[Dress]))
|| (g_astGoodsRec[Book][k].pCalcFun(Book, anCnt[Book], k, &anPrice[Book])))
                {
                    continue;
                }
                nCurSum = 0;
                for (nGoods = Food; nGoods < Goods_butt; nGoods++)
                {
                    nCurSum += anPrice[nGoods];
                }

                findBestTotalMethod(&nCurSum, &nAvailPoint);

                if (nCurSum < nSum)
                {
                    nSum = nCurSum;
                    *pnPoint = nAvailPoint;
                }
            }
        }
    }
    
    *pnSum = nSum;    
    return;
}

/* 结算，考生实现 */
void opBuyProc()
{
	unsigned int sum, point, addPoint;

	if(g_stShopBag.nBillNum<=0){
		apiPrintErrInfo(E005);
		return;	
	}

	sum   = 0;
	point = 0;
	getBestBuy(&sum, &point);

	if(sum>g_stCardInfo.nBalance){
		apiPrintErrInfo(E006);
		return;
	}else{
		addPoint = sum/10;
		apiPrintConsumeInfo(sum, point, addPoint);

		g_stCardInfo.nBalance -= sum;
		g_stCardInfo.nPoint    = g_stCardInfo.nPoint - point + addPoint;

		memset(&g_stShopBag, 0xff, sizeof(g_stShopBag));
    	g_stShopBag.nBillNum = 0;
		
		//apiPrintCartInfo(g_stCardInfo.nBalance, g_stCardInfo.nPoint);
	}

    return;
}

/* 查询，考生实现 */
void opListProc(unsigned int nMethod)
{
	unsigned int food, dress, book;

	if(nMethod==0){
		apiPrintCartInfo(g_stCardInfo.nBalance, g_stCardInfo.nPoint);
	}else if(nMethod==1){
		lowlevel_sort(&food, &dress, &book);
		apiPrintShopBagInfo(g_stShopBag.nBillNum, food, dress, book);		
	}else{
		apiPrintErrInfo(E002);
		return;
	}

    return;  
}

void lowlevel_sort(unsigned int *food, unsigned int *dress, unsigned int *book)
{
	int i = 0;

	*food  = 0;
	*dress = 0;
	*book  = 0;
	for(i=0; i<M_MAX_REC_NUM; i++){
		if     (g_stShopBag.astRec[i].nNo==Food ) *food  += g_stShopBag.astRec[i].nCnt;	
		else if(g_stShopBag.astRec[i].nNo==Dress) *dress += g_stShopBag.astRec[i].nCnt;	
		else if(g_stShopBag.astRec[i].nNo==Book ) *book  += g_stShopBag.astRec[i].nCnt;	
	}
}
