#include"card_line.h"

/*��ʾ��ӿ��Ӳ˵�*/
void output()
{
	printf("_____________MENU____________\n");
	printf("1.������ӿ�\n");
	printf("2.��ѯ���д���ӿ�\n");
	printf("3.��ʾ���д���ӿ�\n");
	printf("4.ɾ����\n");
	printf("5.ɾ�����п�\n");
	printf("0.�˳�\n");
	printf("��ѡ���ܡ���������0~4��\n\n");
}

/*д���������¿���Ϣ���ļ�*/
int Linefile(List* phead, const char* pPath)
{
	FILE* fp = NULL;   // �ļ��ṹ��ָ��
	CardNode *pwrite=NULL;
	pwrite = *phead;
// ��׷�ӵ�ģʽ���ļ��������ʧ�ܣ�����ֻд��ģʽ���ļ�
	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
			printf("���ļ�ʧ��\n");
			return Error;

		}
			
	}
	if ((pwrite == NULL)||(*phead == NULL))
	{
	printf("û�п���Ϣ�ɹ�д��\n");
	return Error;
	}
	else
	{
		while (pwrite!=NULL)
		{
		fwrite(pwrite, sizeof(CardNode), 1, fp);
		pwrite = pwrite->next;
		}
	}
	
		if (pwrite == NULL)
		{
			fclose(fp);
			return OK;
		}
		else
		{
			fclose(fp);
			return Error;
		}
	return Error;
}

//����ָ��������Ϣ�����
int Find(List* phead)
{
	List pcur1;
	pcur1 = *phead;
	char card_name[18];//��Ų�ѯ����
	if (*phead == NULL) 
	{
	printf("�޿����ݣ�\n");
	return Error;
	}
		
	else
	{
		printf("��������Ҫ��ѯ�Ŀ��ţ�\n");
		scanf("%s", card_name);

		if (Check_line(phead, card_name))//����1�������д��ڴ˿���
		{
			printf("����%s��Ϣ���£�\n",card_name);
			for (pcur1; pcur1 != NULL; pcur1 = pcur1->next)
			{
				if (strcmp(card_name, pcur1->data.name) == 0)
				{
					Show(pcur1);
					break;
				}
			}
		}
		else
		{
		printf("û����ؿ���Ϣ��\n");
		return Error;
		}
			
	}

	return OK;
}

//ɾ��ָ�������п���Ϣ
int Delete(List* phead)
{
	List pcur1 = *phead;
	List pdel = NULL;
	char card_name[18];//��Ŵ�ɾ������

	printf("��������Ҫɾ���Ŀ��ţ�\n");
	scanf_s("%s", card_name, sizeof(card_name));
	if (Check_line(phead, card_name))//����1���������п��Ŵ���
	{
		if ((strcmp(pcur1->data.name, card_name) == 0) && (Count_line(phead) == 1))//��ɾ����Ϊ��һ���ڵ��ҽ���һ���ڵ�
		{
			free(pcur1);
			*phead = NULL;
			printf("���ţ�%s ��ɾ����\n", card_name);
			return OK;

			//if (*phead == NULL) 
			//{
			//	printf("����һ�ڵ����ͷ���ɾ������ͷָ���ÿգ�\n");
			//}


		}
		else if ((strcmp(pcur1->data.name, card_name)) == 0 && (Count_line(phead) > 1))//����һ���ڵ㼴Ϊ��ɾ����,�Ҳ�ֹһ���ڵ�
		{
			pdel = *phead;
			*phead = pcur1->next;//ͷָ�����һλ	
			pcur1 = *phead;
			free(pdel);//�ͷŽڵ��ڴ�			
			pdel = NULL;
			printf("���ţ�%s ��ɾ����\n", card_name);
			return OK;

			//if (*phead != NULL) {
			//	printf("��ڵ����ͷ���ɾ����ͷָ�����ض�λ��phead->name=%s\n", pcur1->data.name);
			//}
		}
		else
		{
			for (pcur1; pcur1 != NULL; pcur1 = pcur1->next)//��ͷ���ɾ��
			{
				if ((strcmp(pcur1->next->data.name, card_name) == 0) && (pcur1 != NULL))//�������ҿ�
				{
					pdel = pcur1->next;//��λ��ɾ���ڵ�
					pcur1->next = pdel->next;
					free(pdel);
					pdel = NULL;
					printf("���ţ�%s ��ɾ����\n", card_name);
					return OK;

					//if (*phead != NULL) {
					//	printf("��ͷ�ڵ�ɾ����ɾ���ڵ��phead->name=%s\n", (*phead)->data.name);
					//}
					

				}
			}
		}
	}
	else
	{
	printf("δ��ѯ����ɾ������Ϣ\n");
	return Error;
	}
	return OK;
}

//��ʾ������������
int Show(List p1)
{
	char t1[20];
	char t2[20];
	//��ʱ��ת��Ϊ�ַ�����ʽ
	timeToString(p1->data.tStart, t1);
	timeToString(p1->data.tLastT, t2);
	printf("\t\t\t*****��ѯ����ؿ���Ϣ����*****\n");
	printf("����\t״̬\t���  �ۼ�ʹ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\t\t����ʱ��\n");
	printf("%s\t%d\t%.1f\t\t%.1f\t%d\t%s\t%s\n", p1->data.name, p1->data.status, p1->data.fleft, p1->data.fAlluse, p1->data.Usecount, t2, t1);
	return OK;
}

//��ʾ������������
int showAll(List* phead)
{
	if (*phead == NULL)
	{
		printf("�޿���Ϣ��\n");
		return Error;
	}
	else
	{
		List show = NULL;
		char t1[20];//��ſ���ʱ��
		char t2[20];//����ϴ�ʹ��ʱ��

		printf("���п�������%d\n", Count_line(phead));
		printf("\t\t\t*****���п���Ϣ����*****\n");
		printf("����\t״̬\t���  �ۼ�ʹ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\t\t����ʱ��\n");
		for (show = *phead; show != NULL; show = show->next)
		{
			//��ʱ��ת��Ϊ�ַ�����ʽ
			timeToString(show->data.tStart, t1);
			timeToString(show->data.tLastT, t2);

			printf("%s\t%d\t%.1f\t%.1f\t%d\t%s\t%s\n", show->data.name, show->data.status, show->data.fleft, show->data.fAlluse,show->data.Usecount,t2,t1 );
		}
	}

	return OK;
}

