#include"card_line.h"

//����ϻ�״̬
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
						s = 1;//�������ϻ�
					}
					else if ((pcur1->data.fleft) <= 0)
					{
						s = 2;//��������
					}
					else if (pcur1->data.nDel == 1)
					{
						s = 3;//������ע��
					}
					else 
					{
						s = 4;//���ϻ�
					}
					break;
				}
			}
			return s;
}

//�ϻ��������
int Linkupdate(List *phead,const char *name)
{
	List cur;
	cur = *phead;
	for (cur;cur != NULL; cur = cur->next)
	{
		if ((strcmp(name, cur->data.name) == 0))
		{
		
			cur->data.status = 1;//��״̬����Ϊ�ϻ�
			cur->data.Usecount++;//ʹ�ô�����һ
			cur->data.tLastT = time(NULL);//�ϴ�ʹ��ʱ���Ϊ��ǰʱ��
				break;			
		}
	}
	return OK;
}

