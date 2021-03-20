
#include"card_line.h"

//ɾ�����������п���Ϣ
int aDel(List* phead)
{
	List del = *phead;//ָ���ɾ���ڵ�	
	List p=NULL;//��¼��һ�ڵ�
	if (*phead == NULL)
	{
		
		return Error;
	}
		
	else
	{
		while (del)
		{
			p = del->next;
			free(del);
			del = p;
		}
		*phead = NULL;
	}

	if ((!del) && (!(*phead)))//ȷ��ѭ��������ĩβ	
	{
		
		return OK;
	}

	else
		printf("Error!\n");

	return Error;

}
int aDel(Charge* phead)
{
	Charge del = *phead;//ָ���ɾ���ڵ�	
	Charge p = NULL;//��¼��һ�ڵ�
	if (*phead == NULL)
	{
		return Error;
	}

	else
	{
		while (del)
		{
			p = del->next;
			free(del);
			del = p;
		}
		*phead = NULL;
	}

	if ((!del) && (!(*phead)))//ȷ��ѭ��������ĩβ	
	{

		return OK;
	}

	else
		printf("Error!\n");

	return Error;

}
int aDel(Pay* phead)
{
	Pay del = *phead;//ָ���ɾ���ڵ�	
	Pay p = NULL;//��¼��һ�ڵ�
	if (*phead == NULL)
	{
		return Error;
	}

	else
	{
		while (del)
		{
			p = del->next;
			free(del);
			del = p;
		}
		*phead = NULL;
	}

	if ((!del) && (!(*phead)))//ȷ��ѭ��������ĩβ	
	{

		return OK;
	}

	else
		printf("Error!\n");

	return Error;
}
int aDel(Block* phead)
{
	Block del = *phead;//ָ���ɾ���ڵ�	
	Block p = NULL;//��¼��һ�ڵ�
	if (*phead == NULL)
	{
		return Error;
	}

	else
	{
		while (del)
		{
			p = del->next;
			free(del);
			del = p;
		}
		*phead = NULL;
	}

	if ((!del) && (!(*phead)))//ȷ��ѭ��������ĩβ	
	{

		return OK;
	}

	else
		printf("Error!\n");

	return Error;
}
//�������������Ϸ���
int Check_line(List* phead, const char* card_name)
{
	//����ֵΪ0��������û����ͬ����
	List f;
	f = *phead;
	if (*phead == NULL)
		return Error;
	while (f != NULL)
	{
		if ((strcmp(f->data.name, card_name) == 0)&&(f->data.nDel==0))//����ƥ����δע��
		{
			return OK;
			break;
		}
		f = f->next;
	}
	return Error;
}
int Check_line(Charge* phead, const char* card_name)
{
	//����ֵΪ0��������û����ͬ����
	Charge f;
	f = *phead;
	if (*phead == NULL)
		return Error;
	while (f != NULL)
	{
		if ((strcmp(f->data.aCardName, card_name) == 0) && (f->data.nDel == 0)&&(f->data.nStatus==0))
		{
			return OK;
			break;
		}
		f = f->next;
	}
	return Error;
}
int Check_line(Pay* phead, const char* card_name)
{
	//����ֵΪ0��������û����ͬ����
	Pay f;
	f = *phead;
	if (*phead == NULL)
		return Error;
	while (f != NULL)
	{
		if ((strcmp(f->data.Name, card_name) == 0))
		{
			return OK;
			break;
		}
		f = f->next;
	}
	return Error;
}

//���������п�����
int Count_line(List* phead)
{
	int c = 0;
	List p;
	p = *phead;
	if (*phead == NULL)
		return c;
	for (p; p != NULL; p = p->next)
	{
		if (p != NULL)
			c++;
	}
	return c;
}
int Count_line(Charge* phead)
{
	int c = 0;
	Charge p;
	p = *phead;
	if (*phead == NULL)
		return c;
	for (p; p != NULL; p = p->next)
	{
		if (p != NULL)
			c++;
	}
	return c;
}
int Count_line(Pay* phead)
{
	int c = 0;
	Pay p;
	p = *phead;
	if (*phead == NULL)
		return c;
	for (p; p != NULL; p = p->next)
	{
		if (p != NULL)
			c++;
	}
	return c;
}
int Count_line(Block* phead)
{
	int c = 0;
	Block p;
	p = *phead;
	if (*phead == NULL)
		return c;
	for (p; p != NULL; p = p->next)
	{
		if (p != NULL)
			c++;
	}
	return c;
}

//���ļ��ж�ȡ�Ʒ���Ϣ����	����
int getLine(List *phead, List* pend,const char* pPath)
{	
	//�ÿ�����
	aDel(phead);
	*phead = NULL;
	*pend = NULL;

	if (CardCount(pPath) == 0)
	{
		return Error;
	}
	FILE* fp = NULL;  // �ļ��ṹ��ָ��
	List file;//�����ļ�����
	// ��ֻ����ʽ���ļ��������ʧ�ܣ����ȡʧ��
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return Error;
	}
	fseek(fp, 0, SEEK_SET);// ��λ���ļ��Ŀ�ͷ
	// ��ȡ�ļ�����
	while (!feof(fp))
	{
		file = (CardNode*)malloc(sizeof(CardNode));
		if (fread(file, sizeof(CardNode), 1, fp) != 0)
		{
			if (*phead == NULL)
			{
				*phead = file;
				*pend = *phead;
				(*pend)->next = NULL;
			}
			else
			{
				if (*pend != NULL)
				{
					(*pend)->next = file;
					*pend = file;
					(*pend)->next = NULL;
				}
			}
		}
		else
			break;
		
	}
	// �ر��ļ�
	fclose(fp);
	if ((*pend)->next == NULL)
	{
		return OK;
	}

return Error;		
}
int getLine(Charge* phead, Charge* pend, const char* pPath)
{
	//�ÿ�����
		aDel(phead);
	*phead = NULL;
	*pend = NULL;

	if (Billcount(pPath)==0)
	{
		return Error;
	}

	FILE* fp = NULL;  // �ļ��ṹ��ָ��
	Charge file;//�����ļ�����
	// ��ֻ����ʽ���ļ��������ʧ�ܣ����ȡʧ��
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);// ��λ���ļ��Ŀ�ͷ
	// ��ȡ�ļ�����
	while (!feof(fp))
	{
		file = (Charge)malloc(sizeof(BillNode));
		if (fread(file, sizeof(BillNode), 1, fp)!=0)
		{
				if (*phead == NULL)
				{
					*phead = file;
					*pend = *phead;
					(*pend)->next = NULL;
				}
				else
				{
					if (*pend != NULL)
					{
						(*pend)->next = file;
						*pend = file;
						(*pend)->next = NULL;
					}
				}
		}
		else
			break;

	}
	// �ر��ļ�
	fclose(fp);
	if ((*pend)->next == NULL)
	{
		return OK;
	}

	return Error;
}
int getLine(Pay* phead, Pay* pend, const char* pPath)
{
	// �ÿ�����
		aDel(phead);
	*phead = NULL;
	*pend = NULL;

	if (Billcount(pPath) == 0)
	{
		return Error;
	}

	FILE* fp = NULL;  // �ļ��ṹ��ָ��
	Pay file;//�����ļ�����
	// ��ֻ����ʽ���ļ��������ʧ�ܣ����ȡʧ��
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);// ��λ���ļ��Ŀ�ͷ
	// ��ȡ�ļ�����
	while (!feof(fp))
	{
		file = (Pay)malloc(sizeof(Mnode));
		if (fread(file, sizeof(Mnode), 1, fp) != 0)
		{
			if (*phead == NULL)
			{
				*phead = file;
				*pend = *phead;
				(*pend)->next = NULL;
			}
			else
			{
				if (*pend != NULL)
				{
					(*pend)->next = file;
					*pend = file;
					(*pend)->next = NULL;
				}
			}
		}
		else
			break;

	}
	// �ر��ļ�
	fclose(fp);
	if ((*pend)->next == NULL)
	{
		return OK;
	}

	return Error;
}
int getLine(Block* phead, Block* pend, const char* pPath)
{
	// �ÿ�����
	aDel(phead);
	*phead = NULL;
	*pend = NULL;

	if (Coldcount(pPath) == 0)
	{
		return Error;
	}

	FILE* fp = NULL;  // �ļ��ṹ��ָ��
	Block file;//�����ļ�����
	// ��ֻ����ʽ���ļ��������ʧ�ܣ����ȡʧ��
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);// ��λ���ļ��Ŀ�ͷ
	// ��ȡ�ļ�����
	while (!feof(fp))
	{
		file = (Block)malloc(sizeof(BlockNode));
		if (fread(file, sizeof(BlockNode), 1, fp) != 0)
		{
			if (*phead == NULL)
			{
				*phead = file;
				*pend = *phead;
				(*pend)->next = NULL;
			}
			else
			{
				if (*pend != NULL)
				{
					(*pend)->next = file;
					*pend = file;
					(*pend)->next = NULL;
				}
			}
		}
		else
			break;

	}
	// �ر��ļ�
	fclose(fp);
	if ((*pend)->next == NULL)
	{
		return OK;
	}

	return Error;
}




