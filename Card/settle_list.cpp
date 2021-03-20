#include"card_line.h"

//检测下机状态
int dosettle(Charge* phead,List *head, const char* name)
{
	List pcur1;
	int a = 0;
	int state = 0;
	pcur1 = *head;
	float balance=getAmount(phead, name);//保存消费金额
	float sum = 0;//保存扣费后卡余额
	for (pcur1; pcur1 != NULL; pcur1 = pcur1->next)
	{	
		if (((strcmp(name, pcur1->data.name) == 0)) && (pcur1->data.nDel == 1))
			{
				a = 3;//存在同名已注销卡
			}

		if (((strcmp(name, pcur1->data.name) == 0))&&(pcur1->data.nDel==0))
		{
			
			sum = pcur1->data.fleft - balance;//卡余额减消费金额
			printf("扣费后卡余额%.3f\n", sum);
			if ((pcur1->data.status) == 0)
			{
				state = 1;//卡号状态未上机
			}
			else if(((pcur1->data.fleft) <= 0)|| (sum < 0))//余额小于0或卡号余额不足以支付消费
			{
				state = 2;//卡号余额不足
			}
			else
			{
				state = 4;//可下机
			}
			return state;
		}
		if ((pcur1->next == NULL) && (a == 3))//遍历到末尾仍没有找到相关卡号且存在同名已注销卡
		{
			state = 3;
		}
			
	}

	return state;
}

//更新下机链表
int Linkupdate(Charge *phead, const char *name)
{
	Charge cur;
	cur = *phead;
	float balance= getAmount(phead, name);//消费金额
	printf("%.2f\n", balance);

	for (cur; cur != NULL; cur = cur->next)
	{
		if ((strcmp(name, cur->data.aCardName) == 0) && (cur->data.nDel == 0) && (cur->data.nStatus == 0))//满足卡号同名，未注销，未结算
		{
			cur->data.fAmount = balance;//消费金额
			cur->data.left-= balance;//余额
			cur->data.tEnd = time(NULL);//下机时间改为当前时间
			break;
		}
	}
	return OK;
}

void Put(Charge* phead, const char* name)
{	
	char t1[20];//上机时间
	char t2[20];//下机时间
	Charge card;
	card = *phead;
	for (card; card != NULL; card = card->next)
	{
		if ((strcmp(name, card->data.aCardName) == 0)&&(card->data.nStatus==0)&&(card->data.nDel==0))
		{
			card->data.nStatus == 1;//状态更新已结算
			timeToString(card->data.tStart, t1);
			timeToString(card->data.tEnd, t2);
			break;
		}
	}
	// 输出表格的表头
	printf("\t\t\t*****下机卡信息*****\n");
	printf("卡号\t结算状态   余额\t消费金额\t上机时间\t\t下机时间\n");
	printf("%s\t %d\t   %0.2f  %0.2f\t  %s\t%s\n", card->data.aCardName, card->data.nStatus, card->data.left, card->data.fAmount, t1, t2);
}
