#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "stdlib.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

//本文件中的宏、结构体、API函数供考生使用，但不需更改

#define min(a,b)    (((a) < (b)) ? (a) : (b))

//医生初始信息的记录数
#define MAX_DOCTOR_RECORD       1
//病人初始信息的记录数
#define MAX_PATIENT_RECORD      6
//医生允许排队就诊的病人最大数量
#define MAX_DOCTOR_CAPABILITY   4
//挂号费
#define REG_FEE                 10
//处方费
#define DIAG_FEE                50
//命名字符串最大长度
#define CMD_LEN                 10000
//命令分隔符
#define CMD_SEPARATRIX          ","

//操作码定义
typedef enum _OpRet
{
    E000_INITITIAL_SUCC             = 0, //E000:初始化成功
    E002_DIAGNOSE_NOT_END           = 2, //E002:本次看病未结束
    E003_QUEUE_EXCEED_OF_PER_DOCTOR = 3, //E003:医生排队人数达到上限
    E004_LACK_FEE_FOR_REGISTER      = 4, //E004:无足够挂号费用
    E005_DIAGNOSE_SUCC              = 5, //E005:诊治成功
    E006_NO_PATIENT_IN_QUEUE        = 6, //E006:无病人排队
    E007_PAY_SUCC                   = 7, //E007:缴费成功
    E008_BALANCE_NOT_ENOUGH         = 8, //E008:余额不足
    E014_PATIENT_NOT_BE_PAY_STATUS  = 14, //E014:无该病人待缴费
    E016_NO_PATIENT_IN_HOSP         = 16, //E016:本院无该病人
    E017_DCT_DIAG_NOBODY            = 17, //E017:医生尚未诊断过任何病人
}OpRet;

//病人就诊的状态
typedef enum
{
    PS_IDLE,    //未挂号
    PS_IN_QUEUE,//待就诊
    PS_WAIT_PAY,//待缴费
}PatientStatus;

//病人类型
typedef enum
{
    PM_CREDIT,  //无社保病人
    PM_INSURE,  //有社保病人
}PayMethod;

//查询方式
typedef enum
{
    Q_DOCTOR,   //按医生ID查询
    Q_PATIENT,  //按病人ID查询
}QueryType;

//单条的病人初始信息记录
struct PatientIni
{
    const char *patientId;  //病人ID
    int patientLevel;       //病人类型
    int creditBalance;      //现金金额
    int insureBalance;      //社保金额
};

//查询医生的信息结果
typedef struct
{
    int queueNum;                               //排队的病人数量
    char *pPatientIdInfo[MAX_DOCTOR_CAPABILITY];//排队的病人ID列表
}DoctorQueue;

//病人信息，测试的依据，考生不允许更改其数值
static struct PatientIni gPatientIniCfg[] =
{
    //病人ID  病人类型 现金金额 社保金额
    {"pat01", 0,       100,     0  ,},
    {"pat02", 1,       100,     100,},
    {"pat03", 0,       100,     0  ,},
    {"pat04", 1,       100,     50 ,},
    {"pat05", 1,       10 ,     10 ,},
    {"pat06", 1,       20 ,     10 ,},
};

//===========================================================================

struct PatientInfo_t
{
	int 				patid;
	struct PatientIni 	info;
	PatientStatus		status;
	int					index;;
};

// queue define
struct queue_t
{
	int nTail;
	int nHead;
	int count;
	struct PatientInfo_t *pat_queue[5];
};

void 	queue_init(void);
int 	is_queue_empty(void);
int 	is_queue_full(void);
int 	en_queue(void *p);
void 	*de_queue(void);
int 	queue_count(void);
void *	query_queue(int offset);
int 	get_queue_sequence(int index);

struct queue_t       _queue;
struct PatientInfo_t _PatientInfo[6];

//===========================================================================

/*****************************************************************************
 函 数 名  : api_print_operation_result
 功能描述  : 系统提供的函数,供考生调用,打印操作结果信息
 输入参数  : OpRet opRet 操作码定义
*****************************************************************************/
void api_print_operation_result(OpRet opRet);

/*****************************************************************************
 函 数 名  : api_print_register_succ
 功能描述  : 系统提供的函数,供考生调用,挂号成功返回的信息
*****************************************************************************/
void api_print_register_succ(void);

/*****************************************************************************
 函 数 名  : api_print_patient_query_info
 功能描述  : 系统提供的函数,供考生调用,按照病人方式查询的结果
 输入参数  : const char *pPatientId 病人ID
             PatientStatus patientStatus 病人就诊的状态
             int sequence 病人正在排队就诊时的序号,仅在patientStatus为PS_IN_QUEUE有效
                          patientStatus为其他值时sequence可以输入任意值
             int insureBalance 社保帐户余额
             int creditBalance 现金帐户余额
*****************************************************************************/
void api_print_patient_query_info(const char *pPatientId,
                                  PatientStatus patientStatus,
                                  int sequence,
                                  int insureBalance,
                                  int creditBalance);

/*****************************************************************************
 函 数 名  : api_print_doctor_query_info
 功能描述  : 系统提供的函数,供考生调用,按照医生方式查询的结果
 输入参数  : DoctorQueue *pDoctorQueue 医生名下的病人排队情况
*****************************************************************************/
void api_print_doctor_query_info(DoctorQueue *pDoctorQueue);

//需考生实现的函数声明 BEGIN
void OpInit(void);

void OpRegister(const char *pPatientId);

void OpDiag();

void OpPay(const char *pPatientId);

void OpQuery(QueryType queryType, const char *pQueryId);
//需考生实现的函数声明 END

#ifdef __cplusplus
}
#endif /* __cplusplus */


/*****************************************************************************
函 数 名  : OpInit
功能描述  : 需要考生实现的接口,系统初始化
*****************************************************************************/
void OpInit(void)
{
	int i;

	// init the patient information
	for(i=0; i<6; i++){
		_PatientInfo[i].patid  = i;
		_PatientInfo[i].status = PS_IDLE;
		_PatientInfo[i].index  = -1;
		memcpy(&_PatientInfo[i].info, &gPatientIniCfg[i], sizeof(struct PatientIni));
	}

	queue_init();

	api_print_operation_result(E000_INITITIAL_SUCC);
}

/*****************************************************************************
函 数 名  : OpRegister
功能描述  : 需要考生实现的接口,病人挂号
输入参数  : const char *pPatientId 病人ID
*****************************************************************************/
void OpRegister(const char *pPatientId)
{
	struct PatientInfo_t *pinfo;
	int reg = -1;
	int id;

	id = *(pPatientId+4)-'0' - 1;

	pinfo = &_PatientInfo[id];
	

	if(pinfo->status!=PS_IDLE){
		api_print_operation_result(E002_DIAGNOSE_NOT_END);
		return;	
	}

	if(is_queue_full()!=1){
		if((pinfo->info.patientLevel==1)&&(pinfo->info.insureBalance>=10)){
			pinfo->info.insureBalance -= 10;
			reg = 1;
		}else{
			if(pinfo->info.creditBalance>=10){
				pinfo->info.creditBalance -= 10;
				reg = 1;
			}
		}

		if(reg==1){
			pinfo->index = en_queue(pinfo);
			pinfo->status = PS_IN_QUEUE;
			api_print_register_succ();
		}else{
			api_print_operation_result(E004_LACK_FEE_FOR_REGISTER);
		}
	}else{
		api_print_operation_result(E003_QUEUE_EXCEED_OF_PER_DOCTOR);
	}

	return;
}

/*****************************************************************************
函 数 名  : OpDiag
功能描述  : 需要考生实现的接口,就诊
*****************************************************************************/
void OpDiag(void)
{
	int res;
	struct PatientInfo_t *p;	
	
	if(is_queue_empty()==1){
		res = E006_NO_PATIENT_IN_QUEUE;
	}else{
		p = de_queue();
		p->status = PS_WAIT_PAY;
		p->index = -1;
		res = E005_DIAGNOSE_SUCC;
	}
	api_print_operation_result(res);
}

/*****************************************************************************
函 数 名  : OpPay
功能描述  : 需要考生实现的接口,缴费
输入参数  : const char *pPatientId 病人ID
*****************************************************************************/
void OpPay(const char *pPatientId)
{
	int id, res, pay;
	struct PatientInfo_t *p;

	id = *(pPatientId+4) - '0' - 1;
	p = &_PatientInfo[id];

	pay = -1;
	if(p->status!=PS_WAIT_PAY){
		res = E014_PATIENT_NOT_BE_PAY_STATUS;
	}else{
		if((p->info.patientLevel==1)&&(p->info.insureBalance>=50)){
			p->info.insureBalance -= 50;
			pay = 1;
		}else{
			if(p->info.creditBalance>=50){
				p->info.creditBalance -= 50;
				pay = 1;
			}
		}

		if(pay == 1){
			res = E007_PAY_SUCC;
		}else{
			res = E008_BALANCE_NOT_ENOUGH;
		}

		p->status = PS_IDLE;
	}

	api_print_operation_result(res);

}

/*****************************************************************************
函 数 名  : OpQuery
功能描述  : 需要考生实现的接口,查询
输入参数  : QueryType queryType 查询方式
            const char *pQueryId 医生/病人ID
*****************************************************************************/
void OpQuery(QueryType queryType, const char *pQueryId)
{
	DoctorQueue q;
	struct PatientInfo_t *p;	
	int id,i,sequence;

	if(queryType == Q_DOCTOR){

		q.queueNum = queue_count();
		for(i=0; i<q.queueNum; i++){
			p = query_queue(i);
			q.pPatientIdInfo[i] = (char *)p->info.patientId;
		}
		api_print_doctor_query_info(&q);
	}else if(queryType == Q_PATIENT){
		id = *(pQueryId+4) - '0' - 1;
		p = &_PatientInfo[id];
		sequence = get_queue_sequence(p->index);	
		api_print_patient_query_info(p->info.patientId, p->status, 
						sequence, p->info.insureBalance, p->info.creditBalance);
	}
}


/*****************************************************************************
 函 数 名  : libOutputStr
 功能描述  : 内部函数: 考试系统的输出打印函数，考生无须关注
 输入参数  : pcStr  输出打印字符串
*****************************************************************************/
void libOutputStr(char* pcStr);

/*****************************************************************************
 函 数 名  : cmd_process
 功能描述  : 系统调用的函数,考生无需关注
*****************************************************************************/
void cmd_process(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    cmd_process(argc,argv);
    return 0;
}

void cmd_dispatch(char *pszCmd)
{
    char    Buff1[32];
    char    Buff2[32];
    char    Buff3[32];
    int     tmpParaA;

    int             GetParaCount;
    const char      *p = NULL;
    const char      *p1 = NULL;

    if (NULL == pszCmd)
    {
        return;
    }
    //if (0 == strlen(pszCmd))
    //{
    //    return;
    //}

    p = pszCmd;

    memset(Buff1, 0, sizeof(Buff1));
    memset(Buff2, 0, sizeof(Buff2));
    memset(Buff3, 0, sizeof(Buff3));

    if (p == strstr(p, "i"))
    {
        OpInit();
        return;
    }
    else if (p == strstr(p, "reg_"))
    {
        GetParaCount = sscanf(p, "reg_%s", Buff1);

        if (1 == GetParaCount)
        {
            OpRegister(Buff1);
            return;
        }
    }
    else if (p == strstr(p, "diag"))
    {
        OpDiag();
        return;
    }
    else if (p == strstr(p, "pay"))
    {
        GetParaCount = sscanf(p, "pay_%s", Buff1);

        if (1 == GetParaCount)
        {
            OpPay(Buff1);
            return;
        }
    }
    else if (p == strstr(p, "qu"))
    {
        GetParaCount = sscanf(p, "qu_%d-%s", &tmpParaA, Buff1);

        if (2 == GetParaCount)
        {
            OpQuery((QueryType)tmpParaA, Buff1);
            return;
        }
    }

    libOutputStr("无效命令");
    return;
}

void user_cmdproc(char *pszCmd, int iLen)
{
    if (NULL == pszCmd)
    {
        return;
    }

    cmd_dispatch(pszCmd);

    return;
}

void api_print_operation_result(OpRet opRet)
{
    switch (opRet)
    {
        case E000_INITITIAL_SUCC:
            libOutputStr("E000:初始化成功");
            break;
        case E002_DIAGNOSE_NOT_END:
            libOutputStr("E002:本次看病未结束");
            break;
        case E003_QUEUE_EXCEED_OF_PER_DOCTOR:
            libOutputStr("E003:医生排队人数达到上限");
            break;
        case E004_LACK_FEE_FOR_REGISTER:
            libOutputStr("E004:无足够挂号费用");
            break;
        case E005_DIAGNOSE_SUCC:
            libOutputStr("E005:诊治成功");
            break;
        case E006_NO_PATIENT_IN_QUEUE:
            libOutputStr("E006:无病人排队");
            break;
        case E007_PAY_SUCC:
            libOutputStr("E007:缴费成功");
            break;
        case E008_BALANCE_NOT_ENOUGH:
            libOutputStr("E008:余额不足");
            break;
        case E014_PATIENT_NOT_BE_PAY_STATUS:
            libOutputStr("E014:无该病人待缴费");
            break;

        case E016_NO_PATIENT_IN_HOSP:
            libOutputStr("E016:本院无该病人");
            break;

        case E017_DCT_DIAG_NOBODY:
            libOutputStr("E017:医生尚未诊断过任何病人");
            break;

        default:
            break;
    }

    return;
}
void api_print_register_succ(void)
{
    libOutputStr("E001:挂号成功");

    return;
}

void api_print_patient_query_info(const char *pPatientId, PatientStatus patientStatus, int sequence, int insureBalance, int creditBalance)
{
    char pBuff[512];
    if (NULL == pPatientId)
    {
        return;
    }

    memset(pBuff, 0, sizeof(pBuff));

    switch (patientStatus)
    {
        case PS_IN_QUEUE:
            sprintf(pBuff, "E012:%s 待就诊 排在第%d位,社保帐户余额:%d,现金帐户余额:%d",
                    pPatientId, sequence, insureBalance, creditBalance);
            libOutputStr(pBuff);
            break;

        case PS_IDLE:
            sprintf(pBuff, "E012:%s 未挂号 社保帐户余额:%d,现金帐户余额:%d",
                    pPatientId, insureBalance, creditBalance);
            libOutputStr(pBuff);
            break;

        case PS_WAIT_PAY:
            sprintf(pBuff, "E012:%s 待缴费 社保帐户余额:%d,现金帐户余额:%d",
                    pPatientId, insureBalance, creditBalance);
            libOutputStr(pBuff);
            break;

        default:
            break;
    }
    return;
}

void api_print_doctor_query_info(DoctorQueue *pDoctorQueue)
{
    char pBuff[512];
    if (NULL == pDoctorQueue)
    {
        return;
    }

    memset(pBuff, 0, sizeof(pBuff));

    if (0 == pDoctorQueue->queueNum)
    {
        libOutputStr("E013:dct 无人排队");
    }
    else
    {
        int i;

        sprintf(pBuff, "E013:dct 等待队列");
        for (i = 0; i < pDoctorQueue->queueNum; i++)
        {
            strcat(pBuff, " ");
            strcat(pBuff, pDoctorQueue->pPatientIdInfo[i]);
        }
        libOutputStr(pBuff);
    }

    return;
}

/*****************************************************************************
 函 数 名  : libOutputStr
 功能描述  : 内部函数: 考试系统的输出打印函数
 输入参数  : pcStr  输出打印字符串
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void libOutputStr(char* pcStr)
{
    if (NULL != pcStr )
    {
        printf("%s\n", pcStr);
    }
}


/*****************************************************************************
 函 数 名  : cmd_process
 功能描述  : 系统调用函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
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
    while (true)
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
            libOutputStr("Get command fail.");
        }
    }
    
    free(pszCmd);

    return;
}

// =============================================================

/* queue founctions */
void queue_init(void)
{
	int i;

	_queue.nTail = 0;
	_queue.nHead = 0;
	_queue.count = 0;

	for(i=0; i<5; i++){
		_queue.pat_queue[i] = NULL;
	}
}

int is_queue_empty(void)
{
	return (_queue.nTail == _queue.nHead)?1:0;
}

int is_queue_full(void)
{
	return ((_queue.nTail+1)%5 == _queue.nHead)?1:0;
}

int en_queue(void *p)
{
	int pos;

	_queue.count += 1;
	pos = _queue.nTail;
	_queue.pat_queue[_queue.nTail] = p;
	_queue.nTail = (_queue.nTail + 1)%5;
	return pos;
}

void *de_queue(void)
{
	void *p;
	
	_queue.count -= 1;
	p = _queue.pat_queue[_queue.nHead];
	_queue.pat_queue[_queue.nHead] = NULL;
	_queue.nHead = (_queue.nHead+1)%5;
	
	return p;
}

int queue_count(void)
{
	return _queue.count;
}

void *query_queue(int offset)
{
	int i;

	i = (_queue.nHead + offset)%5;
	return _queue.pat_queue[i];
}

int get_queue_sequence(int index)
{
	if(index==-1) return -1;

	return ((index+5)-_queue.nHead)%5 + 1;
}
