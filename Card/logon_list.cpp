#include"card_line.h"

//检测上机状态
int dologon(List*phead,const char *name)
{
	List pcur1;
	int s=0;
	pcur1 = *phead;
			for (pcur1; pcur1 != NULL; pcur1 = pcur1->next)
			{
				if((strcmp(name, pcur1->data.name) == 0 ))
				{
					if ((pcur1->data.status )!= 0)
					{
						s = 1;//卡号已上机
					}
					else if ((pcur1->data.fleft) <= 0)
					{
						s = 2;//卡号余额不足
					}
					else if (pcur1->data.nDel == 1)
					{
						s = 3;//卡号已注销
					}
					else 
					{
						s = 4;//可上机
					}
					break;
				}
			}
			return s;
}

//上机链表更新
int Linkupdate(List *phead,const char *name)
{
	List cur;
	cur = *phead;
	for (cur;cur != NULL; cur = cur->next)
	{
		if ((strcmp(name, cur->data.name) == 0))
		{
		
			cur->data.status = 1;//卡状态更新为上机
			cur->data.Usecount++;//使用次数加一
			cur->data.tLastT = time(NULL);//上次使用时间改为当前时间
				break;			
		}
	}
	return OK;
}

