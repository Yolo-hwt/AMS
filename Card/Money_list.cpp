#include"card_line.h"
//����ֵ
int upRechargeline(List* phead, const char* name,float money)
{
	List cur;
	cur = *phead;
	for (cur; cur != NULL; cur = cur->next)
	{
		if ((strcmp(name, cur->data.name) == 0)&&(cur->data.nDel == 0))
		{

			cur->data.fleft += money;//��ֵ
			break;
		}
	}
	return OK;
}
//���˷�
int upReturnline(List* phead, const char* name, float money)
{
	List cur;
	cur = *phead;
	for (cur; cur != NULL; cur = cur->next)
	{
		if ((strcmp(name, cur->data.name) == 0) &&(cur->data.nDel == 0))
		{
			cur->data.fleft -= money;//�˷�
			break;
		}
		else
			printf("�������ſ�%s,", cur->data.name);
	}
	return OK;
}
//ע��
int upExitline(List* phead, const char* name)
{
	List cur;
	cur = *phead;
	for (cur; cur != NULL; cur = cur->next)
	{
		if ((strcmp(name, cur->data.name) == 0) && (cur->data.nDel == 0))
		{
			cur->data.fleft = 0;//�˷Ѻ����Ϊ0
			break;
		}
		else
			printf("�������ſ�%s,", cur->data.name);
	}
	return OK;
}