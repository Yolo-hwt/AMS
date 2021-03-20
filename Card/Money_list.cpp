#include"card_line.h"
//卡充值
int upRechargeline(List* phead, const char* name,float money)
{
	List cur;
	cur = *phead;
	for (cur; cur != NULL; cur = cur->next)
	{
		if ((strcmp(name, cur->data.name) == 0)&&(cur->data.nDel == 0))
		{

			cur->data.fleft += money;//充值
			break;
		}
	}
	return OK;
}
//卡退费
int upReturnline(List* phead, const char* name, float money)
{
	List cur;
	cur = *phead;
	for (cur; cur != NULL; cur = cur->next)
	{
		if ((strcmp(name, cur->data.name) == 0) &&(cur->data.nDel == 0))
		{
			cur->data.fleft -= money;//退费
			break;
		}
		else
			printf("不是这张卡%s,", cur->data.name);
	}
	return OK;
}
//注销
int upExitline(List* phead, const char* name)
{
	List cur;
	cur = *phead;
	for (cur; cur != NULL; cur = cur->next)
	{
		if ((strcmp(name, cur->data.name) == 0) && (cur->data.nDel == 0))
		{
			cur->data.fleft = 0;//退费后余额为0
			break;
		}
		else
			printf("不是这张卡%s,", cur->data.name);
	}
	return OK;
}