#define _CRT_SECURE_NO_WARNINGS
#include"card_service.h"
#include"card_line.h"


//����ļ��п��źϷ��ԣ��Ƿ��Ѵ����ļ���δע����δ����)����1�������
int Check_user(const char* card_name, const char* pPath)
{
	int a = 0;
	int b = 0;
	FILE* fp=NULL;
	FILE* bp = NULL;
	List pcur;
	Block cur;
	cur = (Block)malloc(sizeof(BlockNode));
	pcur = (List)malloc(sizeof(CardNode));
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("�޷����ļ�\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);//��λ�ļ��ײ�
	while (!feof(fp))
	{ 
		// ��ȡ���ţ����ȽϿ����Ƿ�Ϊ��ǰ�Ŀ���
		if (fread(pcur, sizeof(CardNode), 1, fp) != 0)//������ȡ����
		{
			if ((strcmp(pcur->data.name, card_name) == 0)&&(pcur->data.nDel==0))
			{
				a = 1;
				break;
			}
		}
	}
	free(pcur);
	fclose(fp);

	if ((bp = fopen(COLD, "rb")) == NULL)
	{
		printf("�޷����ļ�\n");
		exit(0);
	}
	fseek(bp, 0, SEEK_SET);//��λ�ļ��ײ�
	while (!feof(bp))
	{
		// ��ȡ���ţ����ȽϿ����Ƿ�Ϊ��ǰ�Ŀ���
		if (fread(cur, sizeof(BlockNode), 1, bp) != 0)//������ȡ����
		{
			if ((strcmp(cur->data.coldName, card_name) == 0) && (cur->data.coldStatus == 1))//����ͬ�����Ѷ���
			{
				b = 1;
				break;
			}
		}
	}
	if ((a + b) == 0)//�ļ����޿���¼
	{
	free(cur);
	fclose(bp);
	return Error;
	}
	if ((a + b) == 1)//file���Ϸ���cold�п���δ����
	{
		free(cur);
		fclose(bp);
		return OK;
	}
	if ((a + b) == 2)//file���Ϸ���cold�п����Ѷ���
	{
		free(cur);
		fclose(bp);
		printf("�����Ѷ��ᣡ\n");
		return Error;
	}
	return OK;
	
}


//�����ļ��п�����
int CardCount(const char* pPath)
{
	FILE* fp = NULL;  // �ļ�ָ��
	int nIndex = 0;   // ����Ϣ����
	List pCARD;
	pCARD = (List)malloc(sizeof(CardNode));
	// ��ֻ��ģʽ���ļ�
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("���ļ�ʧ��\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);//��λ�ļ�ָ�����ļ��ײ�
	// ���ж�ȡ�ļ����ݣ���ȡ���ļ��������ǿ���Ϣ��
	while (!feof(fp))
	{
		if (fread(pCARD, sizeof(CardNode), 1, fp)!=0)
			nIndex++;
	}

	// �ر��ļ�
	fclose(fp);
	free(pCARD);
	return nIndex;
}
int Billcount(const char* pPath)
{
	FILE* fp = NULL;  // �ļ�ָ��
	int nIndex = 0;   // ����Ϣ����
	BillNode *pCARD;
	pCARD = (Charge)malloc(sizeof(BillNode));
	// ��ֻ��ģʽ���ļ�
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("���ļ�ʧ��\n");
		return Error;
	}
	fseek(fp, 0, SEEK_SET);//��λ�ļ�ָ�����ļ��ײ�
	// ���ж�ȡ�ļ����ݣ���ȡ���ļ��������ǿ���Ϣ��
	while (!feof(fp))
	{
		if (fread(pCARD, sizeof(Bill), 1, fp) != 0)
			nIndex++;
	}

	// �ر��ļ�
	fclose(fp);
	free(pCARD);
	return nIndex;
}
int Moneycount(const char* pPath)
{
	FILE* fp = NULL;  // �ļ�ָ��
	int nIndex = 0;   // ����Ϣ����
	Pay pCARD;
	pCARD = (Pay)malloc(sizeof(Mnode));
	// ��ֻ��ģʽ���ļ�
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("���ļ�ʧ��\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);//��λ�ļ�ָ�����ļ��ײ�
	// ���ж�ȡ�ļ����ݣ���ȡ���ļ��������ǿ���Ϣ��
	while (!feof(fp))
	{
		if (fread(pCARD, sizeof(Mnode), 1, fp) != 0)
			nIndex++;
	}

	// �ر��ļ�
	fclose(fp);
	free(pCARD);
	return nIndex;
}
int Coldcount(const char* pPath)
{
	FILE* fp = NULL;  // �ļ�ָ��
	int nIndex = 0;   // ����Ϣ����
	Block pCARD;
	pCARD = (Block)malloc(sizeof(BlockNode));
	// ��ֻ��ģʽ���ļ�
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("���ļ�ʧ��\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);//��λ�ļ�ָ�����ļ��ײ�
	// ���ж�ȡ�ļ����ݣ���ȡ���ļ��������ǿ���Ϣ��
	while (!feof(fp))
	{
		if (fread(pCARD, sizeof(BlockNode), 1, fp) != 0)
			nIndex++;
	}

	// �ر��ļ�
	fclose(fp);
	free(pCARD);
	return nIndex;

}

//�����ļ�����ע��������
int exitCardCount(const char* pPath)
{
	FILE* fp = NULL;  // �ļ�ָ��
	int nIndex = 0;   // ����Ϣ����
	List pCARD;
	pCARD = (List)malloc(sizeof(CardNode));
	// ��ֻ��ģʽ���ļ�
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("���ļ�ʧ��\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);//��λ�ļ�ָ�����ļ��ײ�
	// ���ж�ȡ�ļ����ݣ���ȡ���ļ��������ǿ���Ϣ��
	while (!feof(fp))
	{
		if (fread(pCARD, sizeof(CardNode), 1, fp) != 0)
		{
			if(pCARD->data.nDel==1)
			nIndex++;
		}	
	}

	// �ر��ļ�
	fclose(fp);
	free(pCARD);
	return nIndex;
}

//��ѯ���У�����¿�
int newadd(const char *num,const char *pPath)

{
	CardNode c;//���忨��Ϣ�ṹ�����
	char nkey[18] = { 0 };//����¿�����
	struct tm* eTime; // ��ֹʱ��
	struct tm* sTime; // ����ʱ��
	char name[18] = { 0 };
	char key[8] = { 0 };

	printf("�¿��˺�Ϊ%s\n", num);
	strcpy(c.data.name, num);
	printf("�¿����ųɹ�����������ƻ�����Ϣ\n");
	printf("����������(����<8)��\n");
	scanf("%s", key);
	

	if (strlen(key) > 8)//�б�����Ϸ���
	{
		do
		{
			printf("���볤�ȣ�%zd\n", strlen(nkey));
			printf("���볤���ѳ����ޣ�(Error input!)��>8)\n");
			printf("���ٴ���������(����<8)��\n");
			memset(nkey, 0, sizeof(nkey));
			scanf("%s", nkey);

		} while (strlen(nkey) > 8);

		strcpy(c.data.key, nkey);

	}
	else
		printf("���볤�ȣ�%zd\n", strlen(key));
		strcpy(c.data.key, nkey);

	printf("�����뿪����\n");
	scanf_s("%f", &c.data.fleft);
	c.data.fAlluse = c.data.fleft;//�����ۼƽ��
	c.data.nDel = 0;//ɾ����ʶ0��δɾ��
	c.data.Usecount = 0;//ʹ�ô���
	c.data.status = 0;//״̬
	c.data.tStart = c.data.tEnd = c.data.tLastT = time(NULL);


	// ����ʱ�䣬��ֹʱ�䣬���ʹ��ʱ�䶼Ĭ��Ϊ��ǰʱ�䡣
	// ���ݿ���ʱ�䣬�����ֹʱ�䣬ÿ�ſ�����Ч��Ϊһ��

	sTime = localtime(&c.data.tStart);
	eTime = localtime(&c.data.tEnd);
	eTime->tm_year = sTime->tm_year + 1;
	c.data.tEnd = mktime(eTime);

	//д���¿����ļ���
	if (!Queryfile(c, pPath))
	{
		return Error;
	}

		return OK;
	
}

//�ṹ�������ʽд���ļ�,�ɹ�����1
int Queryfile(CardNode card, const char* pPath)
{
	FILE* fp = NULL;   // �ļ��ṹ��ָ��	

	// ��׷�ӵ�ģʽ���ļ��������ʧ�ܣ�����ֻд��ģʽ���ļ�
	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
			printf("���ļ�ʧ��\n");
			return Error;
		}
	}
	
		fwrite(&card, sizeof(CardNode), 1, fp);	
		printf("д���ļ��ɹ���\n");

	// �ر��ļ�
	fclose(fp);
	return OK;
}

//�ϻ�����file
int Fileupdate(List* phead, const char* pPath, const char* name)
{
	int line = 1;//�ļ�����
	int nindex =1;//����λ��
	List pcur;//���������������Ϣ
	pcur = *phead;
	List buff;//����������ļ�
	buff = (CardNode*)malloc(sizeof(CardNode));
	
	FILE* fp;
	long IPosition = 0;//��¼�ļ�λ��

	for (pcur; pcur != NULL; pcur = pcur->next)
	{
		if (!(strcmp(name, pcur->data.name) == 0))
		{
			nindex++;//��ȡ�ϻ�����������
		}
		else
		{
			break;
		}
	}
		//�Զ�д��ʽ���ļ�
		if ((fp = fopen(pPath, "rb+")) == NULL)
		{
			printf("���ļ�ʧ��\n");
			return Error;
		}

		while (!feof(fp))//ѭ����ȡ�ļ�λ��
		{
			if (line == nindex)
			{
				IPosition = ftell(fp);//��¼�ļ�λ��
				break;
			}
			else
			{
				if (fread(buff, sizeof(CardNode), 1, fp))
				{
					line++;
				}
			}
		}
		fseek(fp, IPosition, 0);//���ļ��ײ���¼ƫ������λָ��
		fwrite(pcur, sizeof(CardNode), 1, fp);//���Ѹ��¿���Ϣд���ļ�
		fclose(fp);
		free(buff);
		return OK;
	
}
//�»�����bill�ļ�
int upbill(Charge *phead,const char*pPath,const char *name)
{
	int get = 0;//���ұ�ʶ
	int index=1;
	int line=1;

	Charge cur;
	cur = *phead;

	Charge Status;//���������к�����Ϣ//Ϊ�˲�Ӱ��������ԭ����Ϣ����Ӱ��file�ļ�����(Ԥ�ȳ�ʼ��phead)
	Status = (Charge)malloc(sizeof(BillNode));

	Charge buff;//����������ļ�
	buff = (Charge)malloc(sizeof(BillNode));

	FILE* fp;
	long IPosition = 0;//��¼�ļ�λ��

	for (cur; cur != NULL; cur = cur->next)
	{
		if ((strcmp(name, cur->data.aCardName) == 0) && (cur->data.nDel == 0) && (cur->data.nStatus == 0))//���㿨��ͬ����δע����δ����
		{
			get = 1;
			//Ϊ��ʱ������ֵ
			strcpy(Status->data.aCardName, name);
			Status->data.fAmount = cur->data.fAmount;
			Status->data.left = cur->data.left;
			Status->data.nDel = 0;
			Status->data.tEnd = cur->data.tEnd;
			Status->data.tStart = cur->data.tStart;
			Status->data.nStatus = 1;
			break;
		}
		else//�����в��ҵ���Ӧ���ź���¿���Ϣ
		{
			index++;//��ȡ�ϻ�����������
		}
	}
	printf("upbill��get��%d\n", get);
	if (get)
	{

		//�Զ�д��ʽ���ļ�
		if ((fp = fopen(pPath, "rb+")) == NULL)
		{
			printf("���ļ�ʧ��\n");
			return Error;
		}

		while (!feof(fp))//ѭ����ȡ�ļ�λ��
		{
			if (line == index)
			{
				IPosition = ftell(fp);//��¼�ļ�λ��
				break;
			}
			else
			{
				if (fread(buff, sizeof(BillNode), 1, fp))
				{
					line++;
				}
			}
		}
		fseek(fp, IPosition, 0);//���ļ��ײ���¼ƫ������λָ��
		fwrite(Status, sizeof(BillNode), 1, fp);//���Ѹ��¿���Ϣд���ļ�
		fclose(fp);
		free(buff);
		free(Status);
		return OK;

	}
	else
	free(buff);
	free(Status);
	return Error;
}
//�»�����file�ļ�
int upfile(List* phead,Charge *head, const char* pPath, const char* name)
{
	int get = 0;
	int line = 1;//�ļ�����
	int nindex = 1;//����λ��

	List pcur;//��������Ϣ�������������Ϣ
	pcur = *phead;

	Charge find;//�����»������п��ţ���ȡ�Ʒ���Ϣ
	find = *head;
	
	//Charge mark;
	//mark = (Charge)malloc(sizeof(BillNode));

	List buff;//����������ļ�
	buff = (CardNode*)malloc(sizeof(CardNode));

	FILE* fp;
	long IPosition = 0;//��¼�ļ�λ��

	for (find; find != NULL; find = find->next)//�����»������ж�Ӧ��
	{
		if ((strcmp(find->data.aCardName, name) == 0) && (find->data.nStatus == 0) && (find->data.nDel == 0))//����ͬ����״̬δ���㣬��ʶδɾ��
		{
			get = 1;
			//mark = find;
		break;
		}
			
	}
	printf("upfile��get��%d\n", get);

	for (pcur; pcur != NULL; pcur = pcur->next)
	{
		if((strcmp(pcur->data.name,name)==0)&&(pcur->data.nDel==0)&&(pcur->data.status==1))//����ͬ����δע���������ϻ�
		{
			//�����в��ҵ���Ӧ���ź���¿���Ϣ
			pcur->data.fAlluse += find->data.fAmount;//�ۼ����ѽ��
			pcur->data.fleft = find->data.left;//�����
			pcur->data.status = 0;//��״̬�����»�
			pcur->data.tLastT = find->data.tEnd;//�ϴ�ʹ��ʱ��Ϊ�»�ʱ��
			break;
		}
		else
		{
			nindex++;//��ȡ�ϻ�����������
		}
	}

	//�Զ�д��ʽ���ļ�
	if ((fp = fopen(pPath, "rb+")) == NULL)
	{
		printf("���ļ�ʧ��\n");
		return Error;
	}

	while (!feof(fp))//ѭ����ȡ�ļ�λ��
	{
		if (line == nindex)
		{
			IPosition = ftell(fp);//��¼�ļ�λ��
			break;
		}
		else
		{
			if (fread(buff, sizeof(CardNode), 1, fp))
			{
				line++;
			}
		}
	}
	fseek(fp, IPosition, 0);//���ļ��ײ���¼ƫ������λָ��
	fwrite(pcur, sizeof(CardNode), 1, fp);//���Ѹ��¿���Ϣд���ļ�
	fclose(fp);
	free(buff);
	return OK;

}

//���bill���Ѽ�¼
int addBill(BillNode card,const char* pPath)
{
	FILE* fp;
	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
	printf("�ϻ��ļ���ʧ�ܣ�\n");
		return Error;
		}
	}
	fwrite(&card, sizeof(BillNode), 1, fp);
	fclose(fp);
	return OK;
}

//�����ϻ���������Ϣ����ʾ
void Savelogon(List *phead,const char *pPath ,const char *name)
{
	char last[20];//�����ϻ�ʱ��
	BillNode save;//���ϻ�����Ϣд�����Ѽ�¼�ļ�bill
	List pcur;//�����ϻ�����
	pcur = *phead;
	
//���ϻ����ڵ�ṹ�������ֵ
			save.data.fAmount = 0;//���ѽ��
			save.data.nStatus = 0;//����״̬��δ����
			save.data.nDel = 0;//ɾ����ʶ��δɾ��
			save.data.tStart = time(NULL);//�ϻ�ʱ��Ϊ��ǰʱ��
			save.data.tEnd = time(NULL);//�»�ʱ��Ĭ��Ϊ��ǰʱ��
			strcpy(save.data.aCardName, name);//����
			for (pcur; pcur != NULL; pcur = pcur->next)
			{
				if ((strcmp(name, pcur->data.name) == 0)&&(pcur->data.nDel==0))//����ͬ����δɾ��
				{
					save.data.left = pcur->data.fleft;//�����
					timeToString(pcur->data.tLastT, last);
					break;
				}
			}
			
			if (addBill(save,pPath))
				printf("���Ѽ�¼�ѱ���!\n");

			printf("�ϻ�����Ϣ���£�\n");
			// ������ı�ͷ
			printf("����\t���\t��״̬\tʹ�ô���\t�ϻ�ʱ��\n");
			printf("%s\t%0.1f\t%d\t%d\t%s\n", pcur->data.name, save.data.left, pcur->data.status, pcur->data.Usecount, last);
			
}

//�������ѽ��
float getAmount(Charge* phead, const char* name)
{
	int unit = 1;//��С�շѵ�Ԫ1min
	int cost = 1;//ÿ��Ԫ��Ǯ1yuan
	int count = 0;//��¼��Ԫ�����������룩
	int nMinute=0;
	float Amount=0;//��ʼ������Ϊ0

	time_t nSec=0;//�����ϻ�ʱ��
	time_t tEnd=time(NULL);//���������ʱ��

	Charge pcur;
	pcur = *phead;
	for (pcur; pcur != NULL; pcur = pcur->next)
	{
		if((strcmp(name, pcur->data.aCardName) == 0)&&(pcur->data.nStatus==0))//����ƥ����δ����
		{
			nSec = pcur->data.tStart;//��ȡ�����ϻ�ʱ��
			break;
		}
	}
	nSec = tEnd-nSec;//�������ϻ�ʱ��
	nMinute = int((nSec / 60)+0.5);
	if (nMinute % unit == 0)
	{
		count = int(nMinute / unit);//�Ʒѵ�Ԫ��
	}
	else
	{
		count = int((nMinute / unit) + 0.5);
	}
	Amount = float(count * cost);
	return Amount;
}

//��֤����������ȷ��(����0������ȷ��
int Check_key(List* phead, const char* name, const char* key)
{
	List pcur;
	pcur = *phead;
	int a = 0;
	for (pcur; pcur != NULL; pcur = pcur->next)
	{
		if ((strcmp(name, pcur->data.name) == 0)&&(pcur->data.nDel==0))
		{
			if (strcmp(key, pcur->data.key) == 0)
				a = 1;//���㿨���������ȷ
			break;
		}
	}
	return a;

}

//����money�ļ�
int upChargeMoney(List* phead, const char* name, float money, const char* pPath)
{
	FILE* fp;
	List pcur;
	pcur = *phead;
	Pay up;//�����ֵ��Ϣ
	up = (Pay)malloc(sizeof(Mnode));
	
	//�Գ�ֵ��Ϣ�ṹ��up��ֵ
	up->data.fAmount = money;//��ֵ���
	up->data.nStatus = 1;//״̬1Ϊ��ֵ
	strcpy(up->data.Name, name);//����
	up->data.tTime = time(NULL);//��ֵʱ��Ϊ��ǰʱ��
	up->data.nDel = 0;//ɾ����ʶ0��δɾ����

	for (pcur; pcur != NULL; pcur = pcur->next)
	{
		if (strcmp(name, pcur->data.name) == 0)
		{
			up->data.left = pcur->data.fleft;//�����
			break;
		}
	}

	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
			printf("���ļ�ʧ��\n");
			return Error;
		}
	}
	fwrite(up, sizeof(Mnode), 1, fp);
	fclose(fp);
	free(up);
	return OK;
}
int upReturnMoney(List* phead, const char* name, float money, const char* pPath)
{
	FILE* fp;
	List pcur;
	pcur = *phead;
	Pay up;//�����˷���Ϣ
	up = (Pay)malloc(sizeof(Mnode));

	//���˷���Ϣ�ṹ��up��ֵ
	up->data.fAmount = money;//�˷ѽ��
	up->data.nStatus = 0;//״̬0Ϊ�˷�
	strcpy(up->data.Name, name);//����
	up->data.tTime = time(NULL);//�˷�ʱ��Ϊ��ǰʱ��
	up->data.nDel = 0;//ɾ����ʶ0��δɾ����

	for (pcur; pcur != NULL; pcur = pcur->next)
	{
		if (strcmp(name, pcur->data.name) == 0)
		{
			up->data.left = pcur->data.fleft;//�����
			break;
		}
	}

	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
			printf("���ļ�ʧ��\n");
			return Error;
		}
	}
	fwrite(up, sizeof(Mnode), 1, fp);
	fclose(fp);
	free(up);
	return OK;
}
int upExitMoney( const char* name, float money, const char* pPath)
{
	FILE* fp;
	Pay up;//����ע�����˷���Ϣ
	up = (Pay)malloc(sizeof(Mnode));

	//��ע�����˷���Ϣ�ṹ��up��ֵ
	up->data.fAmount = money;//�˷ѽ��
	up->data.nStatus = 0;//״̬0Ϊ�˷�
	strcpy(up->data.Name, name);//����
	up->data.tTime = time(NULL);//�˷�ʱ��Ϊ��ǰʱ��
	up->data.nDel = 1;//ɾ����ʶ1����ɾ����
	up->data.left = 0;//�����

	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
			printf("���ļ�ʧ��\n");
			return Error;
		}
	}
	fwrite(up, sizeof(Mnode), 1, fp);
	fclose(fp);
	free(up);
	return OK;
}

//��ֵ�˷�ע����file�ļ�
 float upMoneyfile(List* phead, const char* name, const char* pPath)
{
	int line = 1;//�ļ�����
	int nindex = 1;//����λ��
	FILE* fp;//�ļ�ָ��
	long IPosition = 0;//��¼�ļ�λ��
	float value = 0;//�������
	List pcur;//��������
	pcur = *phead;

	List buff;//����������ļ�
	buff = (CardNode*)malloc(sizeof(CardNode));

	for (pcur; pcur != NULL; pcur = pcur->next)
	{
		if (!(strcmp(name, pcur->data.name) == 0)||(pcur->data.nDel==1))
		{
			nindex++;//��ȡ�ϻ�����������
		}
		else//�����в��ҵ���Ӧ���ź���¿���Ϣ
		{
			value = pcur->data.fleft;
			break;
		}
	}

	if ((fp = fopen(pPath, "rb+")) == NULL)
		{
			printf("���ļ�ʧ��\n");
			exit(0);
		}

	while (!feof(fp))//ѭ����ȡ�ļ�λ��
	{
		if (line == nindex)
		{
			IPosition = ftell(fp);//��¼�ļ�λ��
			break;
		}
		else
		{
			if (fread(buff, sizeof(CardNode), 1, fp))
			{
				line++;
			}
		}
	}

	fseek(fp, IPosition, 0);//���ļ��ײ���¼ƫ������λָ��
	fwrite(pcur, sizeof(CardNode), 1, fp);
	fclose(fp);
	free(buff);
	return value;
}
 //ע����file�ļ�
 float upExitMoneyfile(List* phead, const char* name, const char* pPath)
 {
	 int line = 1;//�ļ�����
	 int nindex = 1;//����λ��
	 FILE* fp;//�ļ�ָ��
	 long IPosition = 0;//��¼�ļ�λ��
	 float value = 0;//�������
	 List pcur;//��������
	 pcur = *phead;

	 List buff;//����������ļ�
	 buff = (CardNode*)malloc(sizeof(CardNode));

	 for (pcur; pcur != NULL; pcur = pcur->next)
	 {
		 if((!(strcmp(name, pcur->data.name) == 0))||(pcur->data.nDel==1))
		 {
			 nindex++;//��ȡ�ϻ�����������
		 }
		 else//�����в��ҵ���Ӧ���ź���¿���Ϣ
		 {
			 pcur->data.nDel = 1;//��״̬����Ϊ��ɾ��
			 value = pcur->data.fleft;
			 break;
		 }
	 }

	 if ((fp = fopen(pPath, "rb+")) == NULL)
	 {
		 printf("���ļ�ʧ��\n");
		 exit(0);
	 }

	 while (!feof(fp))//ѭ����ȡ�ļ�λ��
	 {
		 if (line == nindex)
		 {
			 IPosition = ftell(fp);//��¼�ļ�λ��
			 break;
		 }
		 else
		 {
			 if (fread(buff, sizeof(CardNode), 1, fp))
			 {
				 line++;
			 }
		 }
	 }

	 fseek(fp, IPosition, 0);//���ļ��ײ���¼ƫ������λָ��
	 fwrite(pcur, sizeof(CardNode), 1, fp);
	 fclose(fp);
	 free(buff);
	 return value;
 }
 //����ע�����˷ѽ��
 float Exitmoney(List* phead, const char* name)//����ע�����˿���
 {
	 float m=0;
		List pcur;
		pcur = *phead;
		for (pcur; pcur != NULL; pcur = pcur->next)
		{
			if (strcmp(name, pcur->data.name) == 0)
			{
				if (pcur->data.nDel == 0)//����δע��
				{
					m = pcur->data.fleft;//������˷�
					break;
				}
			}
		}
		
		return m;
 }
 //��ֵ�˷Ѹ���bill�ļ�
 int upChargeMoneybill(Charge* phead, const char* name, const char* pPath,float money)
 {
	 int get = 0;//��ʶ�Ƿ��ҵ���������bill�ļ���Ϣ
	 int line = 1;//�ļ�����
	 int nindex = 1;//����λ��
	 FILE* fp;//�ļ�ָ��
	 long IPosition = 0;//��¼�ļ�λ��
	 Charge pcur;//��������
	 pcur = *phead;

	 Charge buff;//����������ļ�
	 buff = (Charge)malloc(sizeof(BillNode));

	 for (pcur; pcur != NULL; pcur = pcur->next)
	 {
		 if (!(strcmp(name, pcur->data.aCardName) == 0) || (pcur->data.nDel == 1)||(pcur->data.nStatus==1))//����ͬ����δע����δ����
		 {
			 nindex++;//��ȡ�ϻ�����������
		 }
		 else//�����в��ҵ���Ӧ���ź���¿���Ϣ
		 {
			 get = 1;
			 pcur->data.left += money;//����ֵ�˷Ѻ����
			 break;
		 }
	 }
	 if (get)//�ҵ��ɸ���bill��Ϣ
	 {
		if ((fp = fopen(pPath, "rb+")) == NULL)
		 {
			 printf("���ļ�ʧ��\n");
			 return Error;
		 }

		 while (!feof(fp))//ѭ����ȡ�ļ�λ��
		 {
			 if (line == nindex)
			 {
				 IPosition = ftell(fp);//��¼�ļ�λ��
				 break;
			 }
			 else
			 {
				 if (fread(buff, sizeof(BillNode), 1, fp))
				 {
					 line++;
				 }
			 }
		 }

		 fseek(fp, IPosition, 0);//���ļ��ײ���¼ƫ������λָ��
		 fwrite(pcur, sizeof(BillNode), 1, fp);
		 fclose(fp);
	 }
	 else//�޿ɸ�����Ϣ
	 {
		 free(buff);
		 return Error;
	 }
	 free(buff);
	 return OK;
 }
 int upReturnMoneybill(Charge* phead, const char* name, const char* pPath, float money)
 {
	 int get = 0;//��ʶ�Ƿ��ҵ���������bill�ļ���Ϣ
	 int line = 1;//�ļ�����
	 int nindex = 1;//����λ��
	 FILE* fp;//�ļ�ָ��
	 long IPosition = 0;//��¼�ļ�λ��
	 Charge pcur;//��������
	 pcur = *phead;

	 Charge buff;//����������ļ�
	 buff = (Charge)malloc(sizeof(BillNode));

	 for (pcur; pcur != NULL; pcur = pcur->next)
	 {
		 if (!(strcmp(name, pcur->data.aCardName) == 0) || (pcur->data.nDel == 1) || (pcur->data.nStatus == 1))//����ͬ����δע����δ����
		 {
			 nindex++;//��ȡ�ϻ�����������
		 }
		 else//�����в��ҵ���Ӧ���ź���¿���Ϣ
		 {
			 get = 1;
			 pcur->data.left -= money;//����ֵ�˷Ѻ����
			 break;
		 }
	 }
	 if (get)//�ҵ��ɸ���bill��Ϣ
	 {
		 if ((fp = fopen(pPath, "rb+")) == NULL)
		 {
			 printf("���ļ�ʧ��\n");
			 return Error;
		 }

		 while (!feof(fp))//ѭ����ȡ�ļ�λ��
		 {
			 if (line == nindex)
			 {
				 IPosition = ftell(fp);//��¼�ļ�λ��
				 break;
			 }
			 else
			 {
				 if (fread(buff, sizeof(BillNode), 1, fp))
				 {
					 line++;
				 }
			 }
		 }

		 fseek(fp, IPosition, 0);//���ļ��ײ���¼ƫ������λָ��
		 fwrite(pcur, sizeof(BillNode), 1, fp);
		 fclose(fp);
	 }
	 else//�޿ɸ�����Ϣ
	 {
		 free(buff);
		 return Error;
	 }
	 free(buff);
	 return OK;
 }

 //��������
 int Reset(List* phead, const char* pPath, const char *name,const char *newkey)
 {
	 int line = 1;//�ļ�����
	 int nindex = 1;//����λ��
	 FILE* fp;//�ļ�ָ��
	 long IPosition = 0;//��¼�ļ�λ��
	 List pcur;//��������
	 pcur = *phead;

	 List buff;//����������ļ�
	 buff = (CardNode*)malloc(sizeof(CardNode));

	 for (pcur; pcur != NULL; pcur = pcur->next)
	 {
		 if ((!(strcmp(name, pcur->data.name) == 0)) || (pcur->data.nDel == 1))
		 {
			 nindex++;//��ȡ�ϻ�����������
		 }
		 else//�����в��ҵ���Ӧ���ź���¿���Ϣ
		 {
			 strcpy(pcur->data.key,newkey);//���¿�����
			 break;
		 }
	 }

	 if ((fp = fopen(pPath, "rb+")) == NULL)
	 {
		 printf("���ļ�ʧ��\n");
		 exit(0);
	 }

	 while (!feof(fp))//ѭ����ȡ�ļ�λ��
	 {
		 if (line == nindex)
		 {
			 IPosition = ftell(fp);//��¼�ļ�λ��
			 break;
		 }
		 else
		 {
			 if (fread(buff, sizeof(CardNode), 1, fp))
			 {
				 line++;
			 }
		 }
	 }

	 fseek(fp, IPosition, 0);//���ļ��ײ���¼ƫ������λָ��
	 fwrite(pcur, sizeof(CardNode), 1, fp);
	 fclose(fp);
	 free(buff);
	 return OK;
 }

 //����Աģʽ�ӹ���
//��ʾ�Ӳ˵�
void Outadmin()
{
	printf("*** _Menu of Administer_ ***\n");
	printf("1.���Ῠ\n");
	printf("2.���\n");
	printf("3.��ѯ��������Ϣ\n");
	printf("4.��ʾ���п���Ϣ(file)\n");
	printf("5.��ʾ���������˵�(bill)\n");
	printf("6.��ʾ��ֵ�˷���Ϣ(money)\n");
	printf("7.��ʾ���ж��Ῠ��Ϣ(cold)\n");
	printf("0.�˳��������\n");
}
//��¼����Ա�˺�
int Getin()
{
	int a = 3;
	char key[8];
	char Name[8];
	
	
		printf("���������Ա�˺ţ�\n");
		scanf("%s", Name);
		if (strcmp(Name, ADMINISTER) == 0)
			printf("�˺���ȷ�����������룡\n");
		else
		{
			printf("�˺Ų����ڣ�\n");
			return Error;
		}
		while (Check_admin(key))
		{
			printf("���������룺\n");
		scanf("%s", key);
		a--;
		if (Check_admin(key)==0)
			printf("�ѽ������Աģʽ��\n");
		else
		{
			printf("�������\n!");
			if (a == 0)
			{
			printf("����������Ѵ����ޣ�\n");
			return Error;
			}
				
			printf("������������%d��", a);
		}	
		}
		return a;
}
//������Ա����(��ȷ����0��
int Check_admin(const char *key)
{
	int back = 1;
	if (strcmp(key, POWERWORD) == 0)
		back = 0;
	return back;
}

//���Ῠ
int Frozencard()
{
	int sta = 1;
	char t1[20];//����ʱ��
	char t2[20];//����ʱ��
	Block card;
	card = (Block)malloc(sizeof(BlockNode));
	char num[18];
	int times = 3;
	while (!Check_user(num, PATH))//��⿨���Ƿ���ڣ�����ֵ0���򲻴��ڴ˿�
	{
			printf("�����붳�Ῠ��(����<18)��");
			printf("����������%d�Σ�\n", times);
			scanf("%s", num);
			times--;
			printf("���ų��ȣ�%zd\n", strlen(num));
			if (strlen(num) > 18)//�б𿨺ų��ȺϷ���
			{

				do
				{
					printf("���ų����ѳ����ޣ�(Error input!)��>18)\n");
					memset(num, 0, sizeof(num));//��0����
					if (times)//������Ϊ0
					{
						printf("���ٴ����붳�Ῠ��(����<18)��");
						printf("����������%d�Σ�\n", times);
						scanf("%s", num);
						times--;
						printf("���ų��ȣ�%zd\n", strlen(num));
					}
					else
					{
						printf("���Ῠ����������Ѵ����ޣ�\n");
						return Error;

					}



				} while (strlen(num) > 18);

			}

			if (Check_Cold(num, COLD))//�����Ѷ���
			{
				printf("�����Ѷ��ᣬ");
				sta = 2;
				return sta;
			}
		
		if (!Check_user(num, PATH)&&(times))//����δƥ�䣬�������������
			printf("���Ῠ�Ų����ڣ����ٴ����룺\n");

		if (!Check_user(num, PATH) && (times==0))//����δƥ�䣬û���������
		{
			printf("���Ῠ����������Ѵ����ޣ�\n");
			return Error;
		}
		if(Check_user(num, PATH)&&(times==0))//ƥ����û���������
			printf("������...\n");
		
		if (Check_user(num, PATH) && (times))//ƥ���������������
			printf("������...\n");
	}
	
		
	//Ϊ���Ῠ�ṹ�������ֵ
	strcpy(card->data.coldName, num);
	card->data.coldStatus = 1;//��ʶ1���Ѷ���
	card->data.clod_time = time(NULL);//����ʱ��Ϊ��ǰʱ��
	card->data.act_time = time(NULL);//�ⶳʱ��Ĭ��Ϊ��ǰʱ��

	if (upFrozencold(card, COLD))//����cold�ļ�
	{
	timeToString(card->data.clod_time, t1);
	timeToString(card->data.act_time, t2);

	printf("����%s�Ѷ���", num);
	//��ʾ���Ῠ��Ϣ
	printf("���Ῠ��Ϣ����:\n");
	printf("����\t����ʱ��\t����ʱ��\n");
	printf("%s\t%s\t%s\n", num, t1, t2);
	free(card);
	return OK;
	}
	free(card);
	return Error;
}
//���
int Activecard(Block *phead,Block *pend)
{
	char num[18] = { 0 };
	int times = 3;
	while (!Check_Cold(num,COLD))//��⿨���Ƿ����cold�ļ����ҷ�������������ֵ0���򲻴���
	{
		printf("�����뼤���(����<18)��");
		printf("����������%d�Σ�\n", times);
		scanf("%s", num);
		times--;
		printf("���ų��ȣ�%zd\n", strlen(num));
		if (strlen(num) > 18)//�б𿨺ų��ȺϷ���
		{

			do
			{
				printf("���ų����ѳ����ޣ�(Error input!)��>18)\n");
				memset(num, 0, sizeof(num));//��0����
				if (times)//������Ϊ0
				{
					printf("���ٴ����뼤���(����<18)��");
					printf("����������%d�Σ�\n", times);
					scanf("%s", num);
					times--;
					printf("���ų��ȣ�%zd\n", strlen(num));
				}
				else
				{
					printf("�������������Ѵ����ޣ�\n");
					return Error;

				}

			} while (strlen(num) > 18);

		}

		if (!Check_Cold(num, COLD) && (times))//δƥ�䣬�������������
			printf("����Ų����ڣ����ٴ����룺\n");
		else if (!Check_Cold(num, COLD) && (times == 0))//δƥ�䣬û���������
		{
			printf("�������������Ѵ����ޣ�\n");
			return Error;
		}
		else if (Check_Cold(num, COLD) && (times == 0))//ƥ����û���������
			printf("������...\n");
		else//ƥ���������������
			printf("������...\n");
	}
	//��cold�ļ��ж�ȡ��Ϣ��������
	if (getLine(phead, pend, COLD))
	{
		printf("cold�ļ���ȡ�ɹ�,");
	}
	else
	{
		if (*phead == NULL)
		{
			printf("�ļ����޿���Ϣ��¼��");
			return Error;
		}
		else
		{
			printf("cold�ļ���ȡʧ��,");
			return Error;
		}
	}
	
	upActivecold(phead, num, COLD);//����cold�ļ�	
			return OK;
}
//���Ῠ����cold�ļ�
int upFrozencold(Block card, const char* pPath)
{
	FILE* fp;
	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
			printf("�ϻ��ļ���ʧ�ܣ�\n");
			return Error;
		}
	}
	fwrite(card, sizeof(BlockNode), 1, fp);
	fclose(fp);
	return OK;
}
//�������cold�ļ�����ʾ
int upActivecold(Block *phead, const char *name,const char* pPath)
{
	int get = 0;//���ұ�ʶ
	int index = 1;//����λ��
	int line = 1;//�ļ�λ��

	Block cur;
	cur = *phead;

	Block buff;//����������ļ�
	buff = (Block)malloc(sizeof(BlockNode));

	FILE* fp;
	long IPosition = 0;//��¼�ļ�λ��

	for (cur; cur != NULL; cur = cur->next)
	{
		if ((strcmp(name, cur->data.coldName) == 0) && (cur->data.coldStatus==1))//���㿨��ͬ�����Ѷ���
		{
			get = 1;
			cur->data.coldStatus = 0;//��ʶΪ0����
			cur->data.act_time = time(NULL);//����ʱ��Ϊ��ǰʱ��
			break;
		}
		else//�����в��ҵ���Ӧ���ź���¿���Ϣ
		{
			index++;//��ȡ�ϻ�����������
		}
	}
	//printf("upActivecold��get��%d\n", get);
	if (get)
	{

		//�Զ�д��ʽ���ļ�
		if ((fp = fopen(pPath, "rb+")) == NULL)
		{
			printf("���ļ�ʧ��\n");
			return Error;
		}

		while (!feof(fp))//ѭ����ȡ�ļ�λ��
		{
			if (line == index)
			{
				IPosition = ftell(fp);//��¼�ļ�λ��
				break;
			}
			else
			{
				if (fread(buff, sizeof(BlockNode), 1, fp))
				{
					line++;
				}
			}
		}
		fseek(fp, IPosition, 0);//���ļ��ײ���¼ƫ������λָ��
		fwrite(cur, sizeof(BlockNode), 1, fp);//���Ѹ��¿���Ϣд���ļ�
		fclose(fp);
		free(buff);
		printf("�����Ϣ���£�\n");
		Putcold(cur);
		return OK;

	}
	else
		free(buff);
	return Error;
}
//���,���Ῠʱ���cold�ļ����Ƿ���ڷ���������Ϣ(�����ҷ��Ϸ���1��
int Check_Cold(const char* name, const char* pPath)
{
	FILE* fp = NULL;  // �ļ�ָ��
	int get = 0; 
	Block pCARD;
	pCARD = (Block)malloc(sizeof(BlockNode));
	// ��ֻ��ģʽ���ļ�
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("���ļ�ʧ��\n");
		return Error;
	}
	fseek(fp, 0, SEEK_SET);//��λ�ļ�ָ�����ļ��ײ�
	// ���ж�ȡ�ļ����ݣ���ȡ���ļ��������ǿ���Ϣ��
	while (!feof(fp))
	{
		if (fread(pCARD, sizeof(BlockNode), 1, fp) != 0)
			if ((strcmp(pCARD->data.coldName, name) == 0) && (pCARD->data.coldStatus == 1))//����ͬ�����Ѷ���
				get = 1;
	}
	//printf("Check_Cold��get%d\n", get);
	// �ر��ļ�
	fclose(fp);
	free(pCARD);
	return get;
}


//���ҿ��������˵�
int Querycard(Charge *phead, Charge *pend,Pay *Start,Pay *Last)
{
	
	char num[18] = { 0 };
	while (!Check_user(num, PATH))//��⿨���Ƿ���ڣ�����ֵ0���򲻴��ڴ˿�
	{
	printf("���������ѯ����(����<18)��\n");
		scanf("%s", num);
		printf("���ų��ȣ�%zd\n", strlen(num));
		if (strlen(num) > 18)//�б𿨺ų��ȺϷ���
		{

			do
			{
				printf("���ų����ѳ����ޣ�(Error input!)��>18)\n");
				memset(num, 0, sizeof(num));//��0����
				printf("���ٴ����뿨��(����<18)��\n");
				scanf("%s", num);
				printf("���ų��ȣ�%zd\n", strlen(num));
			} while (strlen(num) > 18);

		}
		if (!Check_user(num, PATH))
			printf("���Ų����ڣ����ٴ����룺\n");
		else
			printf("��ѯ��...\n");
	}

	//��bill�ļ��ж�ȡ�Ʒ���Ϣ
	if (getLine(phead, pend, BILL))
	{

		printf("bill�ļ���ȡ�ɹ�,");
	}
	else
	{
		if (*phead == NULL)
		{
			printf("�ļ������ϻ������Ѽ�¼��");
			return Error;
		}
		else
		{
			printf("bill�ļ���ȡʧ��,");
			return Error;
		}

	}
	//��money�ļ��ж�ȡ�Ʒ���Ϣ
	if (getLine(Start, Last, MONEY))
	{

		printf("money�ļ���ȡ�ɹ�\n");
	}
	else
	{
		if (*Start == NULL)
		{
			printf("�ļ������ϻ������Ѽ�¼��");
			return Error;
		}
		else
		{
			printf("money�ļ���ȡʧ��,");
			return Error;
		}

	}

	Charge show1;
	Pay show2;
	show1 = *phead;
	show2 = *Start;

	
	printf("bill�ļ��й���%d�����Ѽ�¼\n", CheckBillnumber(phead, num));
	if (CheckBillnumber(phead, num))
	{
		printf("�����˵����£�\n");
		for (show1; show1 != NULL; show1 = show1->next)
		{
			if (strcmp(num, show1->data.aCardName)==0)
				Printbill(show1);
		}
	}

		printf("money�ļ��й���%d�����Ѽ�¼\n", CheckMoneynumber(Start, num));
	if (CheckMoneynumber(Start, num))
	{
		printf("��ֵ�˷��˵����£�\n");
		for (show2; show2 != NULL; show2 = show2->next)
		{
			if (strcmp(num, show2->data.Name)==0)
				Putmoney(*show2);
		}

	}
	return OK;
}
//���bill�ļ���ͬ��������Ϣ��
int CheckBillnumber(Charge* phead, const char* name)
{
	Charge cur;
	cur = *phead;
	int num = 0;
	for (cur; cur != NULL; cur = cur->next)
	{
		if (strcmp(cur->data.aCardName, name) == 0)//������Ϣ������ͬ
			num++;
	}
	return num;
}
//���money�ļ���ͬ��������Ϣ��
int CheckMoneynumber(Pay* Start, const char* name)
{
Pay cur;
cur = *Start;
int num = 0;
for (cur; cur != NULL; cur = cur->next)
{
	if (strcmp(cur->data.Name, name) == 0)//������Ϣ������ͬ
		num++;
}
return num;

}

// ��ʾ����Ϣ
void ShowCARD(CardNode card)
{
	
	char t1[20];
	char t3[20];
	timeToString(card.data.tStart, t1);
	timeToString(card.data.tLastT, t3);
	// ������ı�ͷ
	printf("����\t״̬\t���  �ۼ�ʹ��\tʹ�ô���    �ϴ�ʹ��ʱ��\t\t����ʱ��   ɾ����ʶ\n");
	printf("%s\t%d\t%0.1f\t%0.1f\t  %d\t  %s\t%s   %d\n", card.data.name, card.data.status, card.data.fleft,
		card.data.fAlluse, card.data.Usecount, t3,t1,card.data.nDel);
}
void Printbill(Charge card)
{

	char t1[20];//�ϻ�ʱ��
	char t2[20];//�»�ʱ��
	timeToString(card->data.tStart, t1);
	timeToString(card->data.tEnd, t2);
	// ������ı�ͷ
	printf("����\t����״̬\tɾ����ʶ\t���ѽ��\t���\t\t�ϻ�ʱ��\t\t�»�ʱ��\n");
	printf("%s\t %d\t\t %d\t\t %0.1f\t\t%0.1f\t\t   %s\t%s\n", card->data.aCardName, card->data.nStatus, card->data.nDel, card->data.fAmount,card->data.left, t1, t2);
		
}
void Putmoney(Mnode temp)
{
	char t[20];//��ֵ�˷�ʱ��
	//char *sta;//�����ֵ�˷�״̬
	//sta = new char;
	//if (temp.data.nStatus == 1)
		//strcpy(sta, "��ֵ");
	//else
		//strcpy(sta, "�˷�");
	timeToString(temp.data.tTime, t);
	// ������ı�ͷ
	
	printf("����\t״̬\tɾ����ʶ  ���  ���\t  ����ʱ��\n");
	printf("%s\t%d\t %d\t%0.2f\t%0.2f\t%s\n", temp.data.Name, temp.data.nStatus,temp.data.nDel, temp.data.fAmount, temp.data.left, t);
	//delete sta;
}
void Putcold(Block card)
{
	char t1[20];//����ʱ��
	char t2[20];//����ʱ��
	timeToString(card->data.clod_time, t1);
	timeToString(card->data.act_time, t2);
	// ������ı�ͷ
	printf("����\t�����ʶ\t����ʱ��\t\t����ʱ��\n");
	printf("%s\t %d\t %s\t\t%s\n", card->data.coldName, card->data.coldStatus, t1, t2);

}

