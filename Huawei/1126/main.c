#include "stdio.h"
#include "string.h"
#include "stdlib.h"


//命名字符串最大长度
#define CMD_LEN                 10000
//命令分隔符
#define CMD_SEPARATRIX          ","
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#define MAX_MODULE_NUM          11


// 返回码枚举。考生不得修改，但应该使用此枚举。
typedef enum ReturnCode1 {
    E000,   // 操作成功
    E010,   // 软件模块已经启动
    E021,   // 软件模块已经停止
    E998,   // 一般错误
    E999    // 程序异常造成错误，考生无需使用此错误码
}ReturnCode;

typedef enum STATUS
{
   STOP= 0,
   RUNNING  = 1,
   INVALID_STATUS
}STATUS_ENUM;

//==== start >>  add by ZengYajian 2013.4.30

struct Module_t
{
	int 			moduleNum;
	STATUS_ENUM 	moduleStatus;
	struct Module_t *dependOn[MAX_MODULE_NUM];
	struct Module_t *dependBy[MAX_MODULE_NUM];
};

struct Soft_t
{
	int 			moduleSum;
	struct Module_t modules[MAX_MODULE_NUM];
};

struct Soft_t _SoftInfo;

//==== end <<  add by ZengYajian 2013.4.30


ReturnCode SetModuleNumber(int iNumber);
ReturnCode SetDependency(int iModule1, int iModule2);
ReturnCode Start(int iModuleId,int outPut[], int* pStartMouduleNum);
ReturnCode SetStatus(int iModule1,STATUS_ENUM status);
ReturnCode QueryOneModuleStatus(int iModuleId,int outPutStatus[]);
ReturnCode QueryAllModuleStatus(int outPutStatus[], int* pMouduleTotalNum);
ReturnCode Stop(int iModuleId,int outPut[],int* pStopMouduleNum);


/*****************************************************************************
 函 数 名  : cmd_dispatch
 功能描述  : 命令分发函数，此函数不得修改
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
/* 此函数不得修改 */
void cmd_dispatch(char *pszCmd)
{
    int             GetParaCount;
    const char      *p = NULL;

    int moduleNo1=0, moduleNo2= 0;
	STATUS_ENUM status = INVALID_STATUS;  //设置软件模块状态为无效值
	
	int i = 0;

    int       outPut[MAX_MODULE_NUM] = {0};
    int       moduleTotalNum = 0;
    ReturnCode err = E000;
    
    if (NULL == pszCmd)
    {
        return;
    }

    p = pszCmd;

    if (p == strstr(p, "SetNum"))//设置软件总模块数目 SetNum(N)
    {
   	    GetParaCount = sscanf(p, "SetNum(%d)", &moduleNo1);
        if (1 == GetParaCount)
        {
            err = SetModuleNumber(moduleNo1);
            
            if (E000 == err)
            {
                printf("E000:Success;\n");
                return;
            }
            return;
        }

    }
    else if (p == strstr(p, "SetDpd"))//设置模块之间依赖关系 SetRelation (n2->n1)
    {
        GetParaCount = sscanf(p, "SetDpd(%d->%d)",&moduleNo1,&moduleNo2);

        if (2 == GetParaCount)
        {
            SetDependency(moduleNo1,moduleNo2);
            return;
        }
    }
    else if (p == strstr(p, "SetSts"))//设置模块状态 SetStatus(n1->p1)
    {
    	GetParaCount = sscanf(p, "SetSts(%d->%d)",&moduleNo1,(int *)&status);
        if (2 == GetParaCount)
        {
            SetStatus(moduleNo1,status);
            return;
        }

    }
    else if (p == strstr(p, "Start"))//启动模块 StartModule(n1)
    {
        GetParaCount = sscanf(p, "Start(%d)", &moduleNo1);

        if (1 == GetParaCount)
        {
            err = Start(moduleNo1,outPut,&moduleTotalNum);
            if (E010 == err)
            {
                printf("E010:Module already running;\n");
                return;
            }

            printf("start module:");
            for ( i = 1; i <=  moduleTotalNum; i++ )
			{			 
			    printf("%d",outPut[i]);
			}
            printf("\n");
            return;
        }
    }
	else if (p == strstr(p, "Stop"))//停止模块 StopModule(n1)
    {
        GetParaCount = sscanf(p, "Stop(%d)", &moduleNo1);

        if (1 == GetParaCount)
        {
            err = Stop(moduleNo1,outPut,&moduleTotalNum);
            
            if (E021 == err)
            {
                printf("E021:Module already stopped;\n");
                return;
            }

            printf("stop module:");
            for ( i = 1; i <= moduleTotalNum; i++ )
			{
			    printf("%d",outPut[i]);
			}
            printf("\n");
            return;
        }
    }
    else if (p == strstr(p, "Query"))//查询模块状态 Query([n1])
    {
        GetParaCount = sscanf(p, "Query(%d)", &moduleNo1);

        if (1 == GetParaCount)
        {
            QueryOneModuleStatus(moduleNo1,outPut);
            
            printf("search result:");
		    if(0 == outPut[1])
	    	{
	    	    printf("(module NO=%d state=stop)",moduleNo1);
	    	}
			else
			{
		        printf("(module NO=%d state=running)",moduleNo1);
			}
            printf("\n");
            return;
        }		
		else if (0 == GetParaCount)
        {
            QueryAllModuleStatus(outPut,&moduleTotalNum);
            printf("search result:");
			for ( i = 1; i <=  moduleTotalNum; i++ )
			{
			    if(0 == outPut[i])
		    	{
		    	    printf("(module NO=%d state=stop)",i);
		    	}
				else
				{
			        printf("(module NO=%d state=running)",i);
				}
			}
            printf("\n");
            return;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : cmd_process
 功能描述  : 系统调用函数，此函数不得修改
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
/* 此函数不得修改 */
void cmd_process(int argc, char* argv[])
{

    char *pszCmd = NULL;
    int iCmdNum =0;

    pszCmd = (char*)malloc(CMD_LEN);
    if (NULL == pszCmd)
    {
        return;
    }
#ifdef _WIN32
    while (1)
#endif
    {
        iCmdNum =0;
        memset(pszCmd, 0, CMD_LEN);
        iCmdNum = scanf("%s", pszCmd);
        pszCmd[CMD_LEN-1] = 0;

        if (1 == iCmdNum)
        {
            char *pComma = pszCmd;
            char *pCmdStartPos = pszCmd;
            char pszCmdBuffer[512];

            // 多命令以逗号分割
            pComma = strstr(pCmdStartPos, CMD_SEPARATRIX);
            while (NULL != pComma)
            {
                size_t uiCpyLen = 0;

                if (pComma == pCmdStartPos)
                {
                    pCmdStartPos = pComma+1;
                    pComma = strstr(pCmdStartPos, CMD_SEPARATRIX);
                    continue;
                }

                memset(pszCmdBuffer, 0, sizeof(pszCmdBuffer));

                uiCpyLen = min(sizeof(pszCmdBuffer), (size_t)(pComma - pCmdStartPos));
                strncpy(pszCmdBuffer, pCmdStartPos, uiCpyLen);

                cmd_dispatch(pszCmdBuffer);

                pCmdStartPos = pComma+1;
                while(' ' == *pCmdStartPos)
                {
                    pCmdStartPos ++;
                }
                pComma = strstr(pCmdStartPos, CMD_SEPARATRIX);
            }
            cmd_dispatch(pCmdStartPos);
        }
        else
        {
            //libOutputStr("Get command fail.");
        }
    }
    
    free(pszCmd);

    return;
}


/*****************************************************************************
 函 数 名  : main
 功能描述  : 程序主函数，此函数不得修改
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
/* 此函数不得修改 */
int main(int argc, char* argv[])
{
    cmd_process(argc,argv);
    return 0;
}



// 注意：以下全部函数都需要考生实现。

/*****************************************************************************
 函 数 名  : SetModuleNumber
 功能描述  : 考生需要实现的接口。
             设置软件模块的总数量。
             在遇到SetModuleNum命令时，系统会调用此函数。
 输入参数  : iNumber 取值只能是1-10。考生无需检查此参数的合法性。
 输出参数  : 无
 返 回 值  : ReturnCode：返回码，成功返回E000。
 调用函数  : 
 被调函数  : 
*****************************************************************************/
/* 此函数需要考试实现*/
ReturnCode SetModuleNumber(int iNumber)
{
	int i,j;
	
	_SoftInfo.moduleSum = iNumber;

	for(i=0; i<MAX_MODULE_NUM; i++){
		_SoftInfo.modules[i].moduleNum = i;
		_SoftInfo.modules[i].moduleStatus = STOP;
		
		for(j=0; j<MAX_MODULE_NUM; j++){
			_SoftInfo.modules[i].dependOn[j] = NULL;
			_SoftInfo.modules[i].dependBy[j] = NULL;
		}
	}

    return E000;
}
/*****************************************************************************
 函 数 名  : SetStatus
 功能描述  : 考生需要实现的接口。
             设置软件模块的状态。
             在遇到SetStatus命令时，系统会调用此函数。
 输入参数  : moduleNo1 需要设置的模块号。status需要设置的状态
 输出参数  : 无
 返 回 值  : ReturnCode：返回码，成功返回E000。
 调用函数  : 
 被调函数  : 
*****************************************************************************/
/* 此函数需要考试实现*/
ReturnCode SetStatus(int iModule1,STATUS_ENUM status)
{
	_SoftInfo.modules[iModule1].moduleStatus = status;
    
    return E998;
}

/*****************************************************************************
 函 数 名  : SetDependency
 功能描述  : 考生需要实现的接口。
             设置软件模块之间的依赖关系。入参iModule1，iModule2，说明iModule1依赖于iModule2
             在遇到SetRelation命令时，系统会调用此函数。
 输入参数  : iModule1，iModule2
 输出参数  : 无
 返 回 值  : ReturnCode：返回码，成功返回E000。
 调用函数  : 
 被调函数  : 
*****************************************************************************/
/* 此函数需要考试实现*/
ReturnCode SetDependency(int iModule1, int iModule2)
{
	_SoftInfo.modules[iModule1].dependOn[iModule2] = &_SoftInfo.modules[iModule2];	
	_SoftInfo.modules[iModule2].dependBy[iModule1] = &_SoftInfo.modules[iModule1];	
    
	return E998;
}


/*****************************************************************************
 函 数 名  : Start
 功能描述  : 考生需要实现的接口。
             启动一个指定模块。
			 在遇到StartModule命令时，系统会调用此函数。
 输入参数  : iModuleId 模块标识只能是1-N。其中N为模块个数。考生无需检查此参数的合法性。
 输出参数  : outPut[]: 填入StartModule命令执行启动的所有软件模块号，模块号由小到大排序
             stopMouduleNum:填入本次启动的模块总数。
             例如: 启动的模块是7、5、6，则outPut[1]=5,outPut[2]=6,outPut[3]=7,*pStartMouduleNum=3
 返 回 值  : ReturnCode：成功时返回E000; 失败时返回对应错误码。
 调用函数  : 
 被调函数  : 
*****************************************************************************/
/* 此函数需要考试实现*/


void lowlevel_startModule(int id, int *pout, int *psum);
void _startModule(int id);
ReturnCode Start(int iModuleId,int outPut[], int* pStartMouduleNum)
{
	
	if(_SoftInfo.modules[iModuleId].moduleStatus == RUNNING){
		return E010;
	}else{
		lowlevel_startModule(iModuleId, outPut, pStartMouduleNum);
	}

    return E000;
}

int _startMask[MAX_MODULE_NUM], _startSum;
void lowlevel_startModule(int id, int *pout, int *psum)
{
	int i;
	
	_startSum = 0;
	for(i=0; i<MAX_MODULE_NUM; i++){
		_startMask[i] = INVALID_STATUS;
	}

	_startModule(id);

	pout++;
	*psum = _startSum;
	for(i=1; i<=_SoftInfo.moduleSum; i++){
		if(_startMask[i]==RUNNING){
			*pout++ = i;
		}
	}
}

void _startModule(int id)
{
	int i;

	if(_SoftInfo.modules[id].moduleStatus==STOP){	
		_startSum++;
		_startMask[id] = RUNNING;
		_SoftInfo.modules[id].moduleStatus = RUNNING;
	
		for(i=1; i<=_SoftInfo.moduleSum; i++){
			if(_SoftInfo.modules[id].dependOn[i]!=NULL){
				_startModule(_SoftInfo.modules[id].dependOn[i]->moduleNum);
			}
		}
	}
}

/*****************************************************************************
 函 数 名  : Stop
 功能描述  : 考生需要实现的接口。
             强制停止一个指定模块。
			 在遇到StopModule命令时，系统会调用此函数。
 输入参数  : iModuleId 模块标识只能是1-N。其中N为模块个数。考生无需检查此参数的合法性。
 输出参数  : outPut[]: 填入执行StopModule命令停止所有软件模块号，模块号由大到小排序
             stopMouduleNum:填入停止模块的总数。
             例如: 停止的模块是3、5、6，则outPut[1]=6,outPut[2]=5,outPut[3]=3,pStopMouduleNum=3
 返 回 值  : ReturnCode：成功时返回E000; 失败时返回对应错误码。
 调用函数  : 
 被调函数  : 
*****************************************************************************/
/* 此函数需要考试实现*/

void lowlevel_stopModule(int id, int *pout, int *psum);
void _stopModule(int id);
ReturnCode Stop(int iModuleId,int outPut[],int* pStopMouduleNum)
{
 	if(_SoftInfo.modules[iModuleId].moduleStatus == STOP){
		return E021;
	}else{
		lowlevel_stopModule(iModuleId, outPut, pStopMouduleNum);
	}

    return E000;
}

int _stopMask[MAX_MODULE_NUM], _stopSum;
void lowlevel_stopModule(int id, int *pout, int *psum)
{
	int i;
	
	_stopSum = 0;
	for(i=0; i<MAX_MODULE_NUM; i++){
		_stopMask[i] = INVALID_STATUS;
	}

	_stopModule(id);

	pout++;
	*psum = _stopSum;
	for(i=_SoftInfo.moduleSum; i>=1; i--){
		if(_stopMask[i]==STOP){
			*pout++ = i;
		}
	}
}

void _stopModule(int id)
{
	int i;

	if(_SoftInfo.modules[id].moduleStatus==RUNNING){	
		_stopSum++;
		_stopMask[id] = STOP;
		_SoftInfo.modules[id].moduleStatus = STOP;
	
		for(i=1; i<=_SoftInfo.moduleSum; i++){
			if(_SoftInfo.modules[id].dependBy[i]!=NULL){
				_stopModule(_SoftInfo.modules[id].dependBy[i]->moduleNum);
			}
		}
	}
}

/*****************************************************************************
 函 数 名  : QueryOneModuleStatus
 功能描述  : 考生需要实现的接口。
             查询一个指定模块的状态。设置完初始数据后，此函数可被多次调用。
             在遇到Query命令时，系统会调用此函数。
 输入参数  : iModuleId: 模块标识只能是1-N。其中N为模块个数。考生无需检查此参数的合法性。
 输出参数  : outPutStatus[1]填写为查询模块的状态。
 返 回 值  : ReturnCode：成功时返回E000，失败时返回对应错误码。
 调用函数  : 
 被调函数  : 
*****************************************************************************/
/* 此函数需要考试实现*/
ReturnCode QueryOneModuleStatus(int iModuleId,int outPutStatus[])
{
	outPutStatus[1] = _SoftInfo.modules[iModuleId].moduleStatus;
    return E998;
}

/*****************************************************************************
 函 数 名  : QueryAllModuleStatus
 功能描述  : 考生需要实现的接口。
             查询所有模块的状态。设置完初始数据后，此函数可被多次调用。
             在遇到Query命令时，系统会调用此函数。
 输入参数  : 无
 输出参数  : outPutStatus[]: 填入所有的模块号状态,outPutStatus[1]存在模块号1的状态，
             outPutStatus[1]存在模块号2的状态，。。。。，outPutStatus[n]存放模块号n的状态
             运行状态值1，停止状态值为0
             pMouduleTotalNum:填入模块的总数。

 返 回 值  : ReturnCode：成功时返回E000，失败时返回对应错误码。
 调用函数  : 
 被调函数  : 
*****************************************************************************/
/* 此函数需要考试实现*/
ReturnCode QueryAllModuleStatus(int outPutStatus[], int* pMouduleTotalNum)
{
	int i;

	*pMouduleTotalNum = _SoftInfo.moduleSum;
	for(i=1; i<=*pMouduleTotalNum; i++){
		outPutStatus[i] = _SoftInfo.modules[i].moduleStatus;
	}

    return E998;
}

