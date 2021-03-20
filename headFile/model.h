#ifndef MODEL_H
#define MODEL_H
#include<time.h>

//卡结构体
typedef struct CARD
{
	char name[18];//卡号
	char key[8];//密码
	int status;//卡状态（0-未上机，1-正在上机，2—已注销，3-已失效）
	time_t tStart;//开卡时间
	time_t tEnd;//卡截止时间
	float fAlluse;//累计金额
	time_t tLastT;//最后使用时间
	int Usecount;//使用次数
	float fleft;//卡余额
	int nDel;//删除标识（0-未删除，1-已删除）	
}CARD;

//卡节点
typedef struct CardNode
{	
	/*数据域*/
	CARD data;
	/*指针域*/
	struct CardNode* next;

}CardNode,* List;//定义List  (CardNode*)

// 上机计费信息结构体
typedef struct Bill
{
	char aCardName[18];    // 卡号
	time_t tStart;         // 上机时间
	time_t tEnd;           // 下机时间
	float fAmount;         // 消费金额
	float left;			   // 余额
	int nStatus;           // 消费状态，0-未结算，1-已经结算
	int nDel;              // 删除标识，0-未删除,1-删除
}Bill;

// 上机计费信息结点
typedef struct BillNode
{
	Bill data;
	struct BillNode* next;
}BillNode, * Charge;//定义Charge  (BillNode*)


//充值退费结构体
typedef struct Money
{
	char Name[18];			// 卡号
	time_t tTime;			// 充值退费时间 
	float fAmount;         // 充值退费金额
	float left;			   // 余额
	int nStatus;           // 状态，1-充值，0-退费
	int nDel;              // 删除标识，0-未删除,1-删除
}Money;
//充值退费信息节点
typedef struct Mnode
{
	Money data;
	struct Mnode* next;
}Mnode,* Pay;//定义Pay  (Mnode*)

//冻结激活结构体
typedef struct Frozen
{
	char coldName[8];
	time_t clod_time;//冻结时间
	time_t act_time;//解冻时间
	int coldStatus;//冻结标识（1：已冻结，0：未冻结）
}Frozen;
//冻结激活节点
typedef struct BlockNode
{
	Frozen data;
	struct BlockNode* next;
}BlockNode, * Block;//定义Block （BlockNode*)

#endif;





