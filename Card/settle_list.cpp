#include"card_line.h"

//����»�״̬
int dosettle(Charge* phead,List *head, const char* name)
{
	List pcur1;
	int a = 0;
	int state = 0;
	pcur1 = *head;
	float balance=getAmount(phead, name);//�������ѽ��
	float sum = 0;//����۷Ѻ����
	for (pcur1; pcur1 != NULL; pcur1 = pcur1->next)
	{	
		if (((strcmp(name, pcur1->data.name) == 0)) && (pcur1->data.nDel == 1))
			{
				a = 3;//����ͬ����ע����
			}

		if (((strcmp(name, pcur1->data.name) == 0))&&(pcur1->data.nDel==0))
		{
			
			sum = pcur1->data.fleft - balance;//���������ѽ��
			printf("�۷Ѻ����%.3f\n", sum);
			if ((pcur1->data.status) == 0)
			{
				state = 1;//����״̬δ�ϻ�
			}
			else if(((pcur1->data.fleft) <= 0)|| (sum < 0))//���С��0�򿨺�������֧������
			{
				state = 2;//��������
			}
			else
			{
				state = 4;//���»�
			}
			return state;
		}
		if ((pcur1->next == NULL) && (a == 3))//������ĩβ��û���ҵ���ؿ����Ҵ���ͬ����ע����
		{
			state = 3;
		}
			
	}

	return state;
}

//�����»�����
int Linkupdate(Charge *phead, const char *name)
{
	Charge cur;
	cur = *phead;
	float balance= getAmount(phead, name);//���ѽ��
	printf("%.2f\n", balance);

	for (cur; cur != NULL; cur = cur->next)
	{
		if ((strcmp(name, cur->data.aCardName) == 0) && (cur->data.nDel == 0) && (cur->data.nStatus == 0))//���㿨��ͬ����δע����δ����
		{
			cur->data.fAmount = balance;//���ѽ��
			cur->data.left-= balance;//���
			cur->data.tEnd = time(NULL);//�»�ʱ���Ϊ��ǰʱ��
			break;
		}
	}
	return OK;
}

void Put(Charge* phead, const char* name)
{	
	char t1[20];//�ϻ�ʱ��
	char t2[20];//�»�ʱ��
	Charge card;
	card = *phead;
	for (card; card != NULL; card = card->next)
	{
		if ((strcmp(name, card->data.aCardName) == 0)&&(card->data.nStatus==0)&&(card->data.nDel==0))
		{
			card->data.nStatus == 1;//״̬�����ѽ���
			timeToString(card->data.tStart, t1);
			timeToString(card->data.tEnd, t2);
			break;
		}
	}
	// ������ı�ͷ
	printf("\t\t\t*****�»�����Ϣ*****\n");
	printf("����\t����״̬   ���\t���ѽ��\t�ϻ�ʱ��\t\t�»�ʱ��\n");
	printf("%s\t %d\t   %0.2f  %0.2f\t  %s\t%s\n", card->data.aCardName, card->data.nStatus, card->data.left, card->data.fAmount, t1, t2);
}
