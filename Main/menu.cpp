
#include"menu.h"

//������˵�
void outputMenu()
{
	printf("_____________MENU____________\n");
	printf("1.��ӿ�\n");
	printf("2.��ѯ��\n");
	printf("3.�ϻ�\n");
	printf("4.�»�\n");
	printf("5.��ֵ\n");
	printf("6.�˷�\n");
	printf("7.ע����\n");
	printf("8.admin\n");
	printf("9.�޸�����\n");
	//printf("10.��ʾ�ļ���Ϣ\n");
	//printf("11.��ʾ���������˵�\n");
	//printf("12.��ʾ���г�ֵ�˷���Ϣ\n");
	printf("0.�˳�\n");
	printf("��ѡ���ܡ���������0~8��\n");
	
}

//��ӿ�
int Creat(List* phead, List* pend,const char*pPath) //�ȼ���CardNode **L
{
	int a = 1;
	char n[18];//����
	char k[8];//����
	struct tm* eTime;     // ��ֹʱ��
	struct tm* sTime;   // ����ʱ��	
	List pnew;

	while(a)
	{
		output();
	scanf("%d", &a);
		switch (a)
		{
			case 1:
			{
				printf("��ӿ�\n");
				if ((pnew = ((CardNode*)malloc(sizeof(CardNode)))) == NULL)//�Ӷѻ�ȡ�ڴ�
				{
					printf("���ڴ������꣡\a\n");
					exit(0);
				}
				do
				{//ѭ���õ����ȣ��Ϸ��Ծ���Ч����
					printf("�����뿨��(����<=18)��\n");
					scanf("%s", n);

					if (strlen(n) > 18)//�б𿨺źϷ���
					{
						do
						{//ѭ�����õ�������Ч����
							printf("���ų��ȣ�%d\n", strlen(n));
							printf("���ų����ѳ����ޣ�(Error input!)��>18)\n");
							memset(n, 0, sizeof(n));//��0����
							printf("���ٴ����뿨��(����<18)��\n");
							scanf_s("%s", n, sizeof(n));
							printf("���ų��ȣ�%d\n", strlen(n));
						} while (strlen(n) > 18);
					}
					else
						printf("���ų��ȣ�%d\n", strlen(n));

						if (Check_line(phead, n) || Check_user(n, pPath))//��⿨���Ƿ��Ѵ���������ļ���
							printf("ϵͳ���п��ţ����������룺����\n");
						else
						{
							strcpy(pnew->data.name, n);
							printf("�¿����ųɹ�����������ƻ�����Ϣ\n");
						}

			

				} while (Check_line(phead, n) || Check_user(n, pPath));//����,�ļ��о������ڣ��˳�ѭ��

				printf("����������(����<8)��\n");
				scanf_s("%s", k, sizeof(k));
				printf("���볤�ȣ�%d\n", strlen(k));

				if (strlen(k) > 8)//�б�����Ϸ���
				{
					do
					{
						printf("���볤���ѳ����ޣ�(Error input!)��>8)\n");
						printf("���ٴ���������(����<8)��\n");
						memset(k, 0, sizeof(k));
						scanf_s("%s", k, sizeof(k));
						printf("���볤�ȣ�%d\n", strlen(k));
					} while (strlen(k) > 8);

					strcpy(pnew->data.key, k);

				}
				else
					strcpy(pnew->data.key, k);


				printf("�����뿪����\n");
				scanf("%f", &pnew->data.fleft);
				printf("\n");
				pnew->data.fAlluse = 0;//�ۼ�ʹ�ý��
				pnew->data.nDel = 0;//ɾ����ʶ0��δɾ��
				pnew->data.Usecount = 0;//ʹ�ô���
				pnew->data.status = 0;//״̬Ϊδ�ϻ�

				// ����ʱ�䣬��ֹʱ�䣬���ʹ��ʱ�䶼Ĭ��Ϊ��ǰʱ�䡣
				pnew->data.tStart = pnew->data.tEnd = pnew->data.tLastT = time(NULL);
				//��ʱ����ֵת��Ϊ��ǰʱ��
				sTime = localtime(&pnew->data.tStart);
				eTime = localtime(&pnew->data.tEnd);
				// ���ݿ���ʱ�䣬�����ֹʱ�䣬ÿ�ſ�����Ч��Ϊһ��
				eTime->tm_year = sTime->tm_year + 1;
				pnew->data.tEnd = mktime(eTime);

				if (*phead == NULL)
				{
					*phead = pnew;
					*pend = *phead;
					(*pend)->next = NULL;
				}
				else
				{
					if (*pend != NULL)
					{
						(*pend)->next = pnew;
						*pend = pnew;
						(*pend)->next = NULL;
					}
				}
				break;
			}

			case 2: {
				if (!Find(phead))//��ѯ����ӿ�
					printf("��ѯ��ʧ�ܣ�\n");
				break;
			}
			case 3: {
				showAll(phead);//��ʾ���д���ӿ�;
				break;
			}
			case 4: {
				Delete(phead);//ɾ��ָ����
				break;
			}
			case 5: {
				if (aDel(phead))//ɾ�����п�
					printf("���д���ӿ���Ϣ��ɾ����\n");
				else
					printf("����Ϣɾ��ʧ�ܣ�\n");
				break;
			}

			case 0: {
				printf("��ӿ�����...\n");
				printf("����Ϣ����д���ļ��С���\n");
				if (Linefile(phead, pPath)) 
				{
				printf("д���ļ��ɹ���\n");
				printf("�ļ��п�����Ϊ��%d\n", CardCount(pPath));
				}
				else
					printf("д���ļ�ʧ��\n");
					
				if (aDel(phead))//��������
					printf("���������٣�\n");
				break;
			}

			default: {printf("Error choice��\a\n"); }
				   printf("\n");
		}

	}
	return OK;
}

//��ѯ��
void query(const char *pPath)
{
	char num[18];//�������ѯ����
	char find[18];//�������ļ�ȡ������
	CardNode temp;//�����ȡ���Ķ�Ӧ������Ϣ
	int ch;

	FILE* fp = NULL;  // �ļ��ṹ��ָ��

	do
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
		if (!Check_user(num, pPath))//��⿨���Ƿ���ڣ�����ֵ0���򲻴��ڴ˿�
		{
			printf("�Ƿ񴴽�������ͬ���¿���\n����1(yes��\n����0(no��\n");
			scanf_s("%d", &ch);

			if (ch == 1)
			{
				if (newadd(num,pPath))
				{
					printf("����¿��ɹ���\n");
					printf("�ļ��п�����Ϊ��%d\n", CardCount(pPath));
				}
				else
					printf("��ӿ�ʧ��\n");

			}

			else
				printf("���ѯ��������\n");
		}
	} while (!Check_user(num, pPath));//�����ѯ������Ч��ֵΪ1ʱ���˳�ѭ��
			
		// ��ֻ���ķ�ʽ���ļ�
		if ((fp = fopen(pPath, "rb")) == NULL)
		{
			printf("�޷����ļ�!\n");
			exit(0);
		}
		//��ȡ���ţ����ȽϿ����Ƿ�Ϊ��ǰ���ҵĿ���,
		while (!feof(fp))
		{
			
			if (fread(find, sizeof(num), 1, fp) != 0)
			{
				if (strcmp(find, num) == 0)
				{
					printf("���ţ�%s \n", num);
					fseek(fp, (0 - (sizeof(num))), SEEK_CUR);
					fread(&temp, sizeof(CardNode), 1, fp);
					fclose(fp);
					ShowCARD(temp);//��ʾ����Ϣ
					break;
				}
				else
				{
					// �Ƶ���һ����¼
					fseek(fp, sizeof(CardNode) - sizeof(num), SEEK_CUR);
				}
			}

		}

	}

//�ϻ�
int Logon(List* phead,List* pend,const char*pPath)
{
	char Name[18] = { 0 };
	char key[8] = { 0 };
	int result=1;//�����ϻ����
	int time = 3;//�����������
	if (getLine(phead, pend, PATH))
	{
		printf("file�ļ���ȡ�ɹ�,");
	}
	else
	{
		if (*phead == NULL)
		{
			printf("�ļ����޿���Ϣ��");
			return Error;
		}
		else
		{
			printf("file�ļ���ȡʧ��,");
			return Error;
		}
	}
	printf("�������ϻ����ţ�\n");
	scanf("%s", Name);
	if (strlen(Name) > 18)//�б𿨺źϷ���
	{
		do
		{//ѭ�����õ�������Ч����
			printf("���ų��ȣ�%d\n", strlen(Name));
			printf("���ų����ѳ����ޣ�(Error input!)��>18)\n");
			memset(Name, 0, sizeof(Name));//��0����
			printf("���ٴ����뿨��(����<18)��\n");
			scanf_s("%s", Name, sizeof(Name));
			printf("���ų��ȣ�%d\n", strlen(Name));
		} while (strlen(Name) > 18);
	}
	else
		printf("���ų��ȣ�%d\n", strlen(Name));

	if (!Check_line(phead, Name))//��⿨���Ƿ��Ѵ����ļ�������
	{
		
	printf("�޿���,��ͬ��������ע����");
	return Error;
	}

	else
	{
		if (!Check_user(Name, PATH))//�����ļ�������⿨���Ƿ񶳽�
		{
		printf("!");
		return Error;
		}
			
		while (!Check_key(phead, Name, key))
		{

		printf("�������ϻ�����(ʣ�����%d)��\n",time);
				scanf_s("%s", key, sizeof(key));
				if (strlen(key) > 8)//�б����볤�ȺϷ���
				{
					do
					{
						printf("���볤���ѳ����ޣ�(Error input!)��>8)\n");
						printf("���ٴ���������(����<8)��\n");
						memset(key, 0, sizeof(key));
						scanf_s("%s", key, sizeof(key));
						printf("���볤�ȣ�%d\n", strlen(key));
					} while (strlen(key) > 8);

				}
				else
					printf("���볤�ȣ�%d\n", strlen(key));
				if (!Check_key(phead, Name, key))//��������Ϸ���
				{
					time--;
					printf("�������");
					if (time == 0)
					{
						printf("�����������Ѵ����ޣ�\n");
						return Error;
					}
						
					printf("������������%d��\n", time);
				}
				else
				{
					printf("������ȷ��\n");
				}
		}
		
	}
		result = dologon(phead, Name);//��ȡ���ϻ�״̬
		switch (result)
		{
		case 1:
		{
			printf("����%s�����ϻ�", Name);
			return Error
			break;
		}
		case 2:
		{
			printf("�����㣡");
			return Error;
			break;
		}
		case 3:
		{
			printf("������ע����\n");
			return Error;
			break;
		}
		case 4:
		{
			printf("�����ϻ�...\n");
			break;

		}
		default:
		{
			printf("Error!");
			return Error;
			break;
		}
		}	
		//file,bill�ļ�,�������
		if (Linkupdate(phead,Name))
		{
		if(Fileupdate(phead, PATH,Name))
				{
				Savelogon(phead,BILL,Name);//д���ϻ���Ϣ����ʾ			
					return OK;
				}
		}	
		return Error;
	
}

//�»�
int settle(List *head,List *end,Charge *phead,Charge *pend)
{
	char Name[18] = { 0 };
	char key[8] = { 0 };
	int result = 1;//�����»����
	int time = 3;//�����������

	//��bill�ļ��ж�ȡ��Ϣ��������
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
	//��file�ļ��ж�ȡ��Ϣ��������
	if (getLine(head, end, PATH))
	{
		printf("file�ļ���ȡ�ɹ�,");
	}
	else
	{
		if (*head == NULL)
		{
			printf("�ļ����޿���Ϣ��");
			return Error;
		}
		else
		{
			printf("file�ļ���ȡʧ��,");
			return Error;
		}
	}

	printf("�������»����ţ�\n");
	scanf("%s", Name);
	if (strlen(Name) > 18)//�б𿨺źϷ���
	{
		do
		{//ѭ�����õ�������Ч����
			printf("���ų��ȣ�%d\n", strlen(Name));
			printf("���ų����ѳ����ޣ�(Error input!)��>18)\n");
			memset(Name, 0, sizeof(Name));//��0����
			printf("���ٴ����뿨��(����<18)��\n");
			scanf_s("%s", Name, sizeof(Name));
			printf("���ų��ȣ�%d\n", strlen(Name));
		} while (strlen(Name) > 18);
	}
	else
		printf("���ų��ȣ�%d\n", strlen(Name));

	if (Check_line(phead, Name))//��⿨���Ƿ��Ѵ���bill�ļ�������
	{
		if (Check_user(Name, PATH))//���������⿨���Ƿ���ע��
			printf("����״̬��ȷ\n");
		else
		{
			printf("�޿����ϻ���Ϣ���򿨺���ע����");
			return Error;
		}

	}
	else
	{
	printf("����δ�ϻ���");
	return Error;
	}
		
		while (!Check_key(head, Name, key))
		{

		printf("�������»�������(ʣ�����%d)��\n", time);
		scanf_s("%s", key, sizeof(key));
		if (strlen(key) > 8)//�б����볤�ȺϷ���
		{
			do
			{
				printf("���볤���ѳ����ޣ�(Error input!)��>8)\n");
				printf("���ٴ���������(����<8)��\n");
				memset(key, 0, sizeof(key));
				scanf_s("%s", key, sizeof(key));
				printf("���볤�ȣ�%d\n", strlen(key));
			} while (strlen(key) > 8);

		}
		else
			printf("���볤�ȣ�%d\n", strlen(key));

		if (!Check_key(head, Name, key))//��������Ϸ���
		{
			time--;
			printf("�������");
			if (time == 0)
			{
				printf("�����������Ѵ����ޣ�\n");
				return Error;
			}

			printf("������������%d��\n", time);
		}
		else
		{
			printf("������ȷ��\n");
		}

		}
		

		result = dosettle(phead,head, Name);//��ȡ���»�״̬
		switch (result)
		{
		case 1:
		{
			printf("����%sδ�ϻ�", Name);
			return Error
				break;
		}
		case 2:
		{
			printf("�����㣡");
			return Error;
			break;
		}
		case 3:
		{
			printf("������ע����\n");
			return Error;
			break;

		}
		case 4:
		{
			printf("�����»�...\n");
			break;

		}
		default:
		{
			printf("Error!\n");
			return Error;
			break;
		}
		}
		//file,bill�ļ�,�������
		if (Linkupdate(phead,Name))//�»��������
		{
			printf("1");
			if (upbill(phead, BILL, Name))//bill���Ѽ�¼����
			{
				printf("2");
				upfile(head, phead, PATH, Name);//file�ļ�����
				printf("3");
				Put(phead, Name);//��ʾ�»���Ϣ
				return OK;
			}
		}
		return Error;

}

//��ֵ
int Recharge(List *phead,List *pend,Charge *head,Charge *end)
{
	List pcur;
	float value1=0;//�������
	float money=0;//�����ֵ���
	int result=0;//�����ֵ�������
	char Name[18];
	char key[8];
	int time = 3;
	//��file�ļ��ж�ȡ��Ϣ��������
	if (getLine(phead, pend, PATH))
	{
			printf("file�ļ���ȡ�ɹ�,");
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
			printf("file�ļ���ȡʧ��,");
			return Error;
		}
	}
	//��bill�ļ��ж�ȡ��Ϣ��������
	if (getLine(head, end, BILL))
	{
		printf("bill�ļ���ȡ�ɹ�,");
	}
	else
	{
		if (*head == NULL)
		{
			printf("bill�ļ����޿���Ϣ��¼��");//����ʹû��Bil�ļ���¼��Ȼ��Ӱ���ֵ�˷ѣ�
		}
		else
		{
			printf("bill�ļ���ȡʧ��,");
			return Error;
		}
	}

	printf("�������ֵ���ţ�\n");
	scanf("%s", Name);
	if (strlen(Name) > 18)//�б𿨺źϷ���
	{
		do
		{//ѭ�����õ�������Ч����
			printf("���ų��ȣ�%d\n", strlen(Name));
			printf("���ų����ѳ����ޣ�(Error input!)��>18)\n");
			memset(Name, 0, sizeof(Name));//��0����
			printf("���ٴ����뿨��(����<18)��\n");
			scanf_s("%s", Name, sizeof(Name));
			printf("���ų��ȣ�%d\n", strlen(Name));
		} while (strlen(Name) > 18);
	}
	else
		printf("���ų��ȣ�%d\n", strlen(Name));

	if (!Check_line(phead, Name))//��⿨���Ƿ��Ѵ���file�ļ�������
	{
		printf("�޳�ֵ������Ϣ��");
		return Error;
	}

	else
	{
		if (!Check_user(Name, PATH))//��⿨���Ƿ��Ѷ���
		{
			printf("�޷���ֵ��");
			return Error;
		}
		while (!Check_key(phead, Name, key))
		{

			printf("�������ֵ��������(ʣ�����%d)��\n", time);
			scanf_s("%s", key, sizeof(key));
			if (strlen(key) > 8)//�б����볤�ȺϷ���
			{
				do
				{
					printf("���볤���ѳ����ޣ�(Error input!)��>8)\n");
					printf("���ٴ���������(����<8)��\n");
					memset(key, 0, sizeof(key));
					scanf_s("%s", key, sizeof(key));
					printf("���볤�ȣ�%d\n", strlen(key));
				} while (strlen(key) > 8);

			}
			else
				printf("���볤�ȣ�%d\n", strlen(key));

			if (!Check_key(phead, Name, key))//��������Ϸ���
			{
				time--;
				printf("�������");
				if (time == 0)
				{
					printf("�����������Ѵ����ޣ�\n");
					return Error;
				}

				printf("������������%d��\n", time);
			}
			else
			{
				printf("������ȷ��\n");
			}

		}


	}

	for (pcur = *phead; pcur != NULL; pcur = pcur->next)
	{
		if ((strcmp(Name, pcur->data.name) == 0))
		{
			if (pcur->data.nDel == 1)
			{
				printf("������ɾ����ע����\n");
			}
			else
			{
				result = 1;
				break;
			}
		}
			
	}
		
	switch(result)
	{
	case 1:
	{
		printf("�������ֵ���:\n");
			break;
	}
	case 0:
	{
		printf("����ʧЧ��");
		return Error;
		break;
	}
	
	default:
	{
		printf("Error!\n");
		return Error;
		break;
	}
	}
	scanf("%f", &money);//��ȡ��ֵ���
	//file,money�ļ�,�������
	if (upRechargeline(phead, Name, money))//�������
	{
		if (upChargeMoney(phead, Name,money,MONEY))//money�ļ���ֵ�˷Ѽ�¼����
		{
			value1=upMoneyfile(phead,Name,PATH);//file�ļ�����
			upChargeMoneybill(head,Name,BILL,money);//bill�ļ�����
			printf("��ֵ��Ϣ���£�\n");
			printf("����  ��ֵ���  ���\n");
			printf("%s\t%.2f\t%.2f\n", Name, money, value1);
			return OK;
		}
	}
	return Error;
}

//�˷�
int Return(List* phead, List* pend, Charge* head, Charge* end)
{
	List pcur;
	float value1;//�������
	float money = 0;//�����˷ѽ��
	
	int result = 0;//�����˷��������
	char Name[18];
	char key[8];
	int time = 3;
	//��file�ļ��ж�ȡ��Ϣ��������
	if (getLine(phead, pend, PATH))
	{

			printf("file�ļ���ȡ�ɹ�,");
	}
	else
	{
		if (*phead == NULL)
		{
			printf("�ļ����޿���Ϣ��");
			return Error;
		}
		else
		{
			printf("file�ļ���ȡʧ��,");
			return Error;
		}
	}
	//��bill�ļ��ж�ȡ��Ϣ��������
	if (getLine(head, end, BILL))
	{
		printf("bill�ļ���ȡ�ɹ�,");
	}
	else
	{
		if (*head == NULL)
		{
			printf("bill�ļ����޿���Ϣ��¼��");//����ʹû��Bil�ļ���¼��Ȼ��Ӱ���ֵ�˷ѣ�
		}
		else
		{
			printf("bill�ļ���ȡʧ��,");
			return Error;
		}
	}

	printf("�������˷ѿ��ţ�\n");
	scanf("%s", Name);
	if (strlen(Name) > 18)//�б𿨺źϷ���
	{
		do
		{//ѭ�����õ�������Ч����
			printf("���ų��ȣ�%d\n", strlen(Name));
			printf("���ų����ѳ����ޣ�(Error input!)��>18)\n");
			memset(Name, 0, sizeof(Name));//��0����
			printf("���ٴ����뿨��(����<18)��\n");
			scanf_s("%s", Name, sizeof(Name));
			printf("���ų��ȣ�%d\n", strlen(Name));
		} while (strlen(Name) > 18);
	}
	else
		printf("���ų��ȣ�%d\n", strlen(Name));

	if (!Check_line(phead, Name))//��⿨���Ƿ��Ѵ���file�ļ�������
	{
		printf("���˷ѿ�����Ϣ��");
		return Error;
	}

	else
	{
		if (!Check_user(Name, PATH))//��⿨���Ƿ��Ѷ���
		{
			printf("�޷��˷ѣ�");
			return Error;
		}
		while (!Check_key(phead, Name, key))//��⿨��������ȷ��
		{

			printf("�������˷ѿ�������(ʣ�����%d)��\n", time);
			scanf_s("%s", key, sizeof(key));
			if (strlen(key) > 8)//�б����볤�ȺϷ���
			{
				do
				{
					printf("���볤���ѳ����ޣ�(Error input!)��>8)\n");
					printf("���ٴ���������(����<8)��\n");
					memset(key, 0, sizeof(key));
					scanf_s("%s", key, sizeof(key));
					printf("���볤�ȣ�%d\n", strlen(key));
				} while (strlen(key) > 8);

			}
			else
				printf("���볤�ȣ�%d\n", strlen(key));

			if (!Check_key(phead, Name, key))//��������Ϸ���
			{
				time--;
				printf("�������");
				if (time == 0)
				{
					printf("�����������Ѵ����ޣ�\n");
					return Error;
				}

				printf("������������%d��\n", time);
			}
			else
			{
				printf("������ȷ��\n");
			}

		}


	}
	printf("�������˷ѽ��:\n");
	scanf("%f", &money);//��ȡ�˷ѽ��
	for (pcur = *phead; pcur != NULL; pcur = pcur->next)
	{
		if ((strcmp(Name, pcur->data.name) == 0))
		{
			if (pcur->data.nDel == 1)
			{
				printf("������ɾ����ע����\n");
			}
			else if((pcur->data.fleft <= 0)||(pcur->data.fleft<money))//���С��0��С���˷ѽ��
			{
				
				result = 2;
			}
			else
			{
				result = 1;//���˷�
				break;
			}
		}

	}

	switch (result)
	{
	case 1:
	{
		printf("�����˷�...\n");
		break;
	}
	case 2:
	{
		printf("�������㣡\n");
		return Error;
		break;

	}
	case 0:
	{
		printf("����ʧЧ��");
		return Error;
		break;
	}

	default:
	{
		printf("Error!\n");
		return Error;
		break;
	}
	}
	
	//file,money�ļ�,�������
	if (upReturnline(phead, Name, money))//�������
	{
		if (upReturnMoney(phead, Name, money, MONEY))//money�ļ���ֵ�˷Ѽ�¼����
		{
			value1 = upMoneyfile(phead, Name, PATH);//file�ļ�����
			upReturnMoneybill(head, Name, BILL, money);//bill�ļ�����
			printf("�˷���Ϣ���£�\n");
			printf("����  �˷ѽ��  ���\n");
			printf("%s\t%.2f\t%.2f\n", Name, money, value1);
			return OK;
		}
	}
	return Error;
}

//ע����
int ExitCard(List* phead,List *pend)
{
	int time = 3;
	char Name[18] = { 0 };
	char key[8] = { 0 };
	int result = 1;
	int get = 0;
	float money=0;//ע�����˿���
	float value1=0;//�������
	if (getLine(phead, pend, PATH))
	{
			printf("file�ļ���ȡ�ɹ�,");
	}
	else
	{
		if (*phead == NULL)
		{
			printf("�ļ����޿���Ϣ��");
			return Error;
		}
		else
		{
			printf("file�ļ���ȡʧ��,");
			return Error;
		}
	}

	printf("������ע�����ţ�\n");
	scanf("%s", Name);
	if (strlen(Name) > 18)//�б𿨺źϷ���
	{
		do
		{//ѭ�����õ�������Ч����
			printf("���ų��ȣ�%d\n", strlen(Name));
			printf("���ų����ѳ����ޣ�(Error input!)��>18)\n");
			memset(Name, 0, sizeof(Name));//��0����
			printf("���ٴ����뿨��(����<18)��\n");
			scanf_s("%s", Name, sizeof(Name));
			printf("���ų��ȣ�%d\n", strlen(Name));
		} while (strlen(Name) > 18);
	}
	else
		printf("���ų��ȣ�%d\n", strlen(Name));

	if (!Check_line(phead, Name))//��⿨���Ƿ��Ѵ���file�ļ�������
	{
		printf("��ע��������Ϣ���򿨺���ע��");
		return Error;
	}

	else
	{
		while (!Check_key(phead, Name, key))//��⿨��������ȷ��
		{

			printf("������ע����������(ʣ�����%d)��\n", time);
			scanf_s("%s", key, sizeof(key));
			if (strlen(key) > 8)//�б����볤�ȺϷ���
			{
				do
				{
					printf("���볤���ѳ����ޣ�(Error input!)��>8)\n");
					printf("���ٴ���������(����<8)��\n");
					memset(key, 0, sizeof(key));
					scanf_s("%s", key, sizeof(key));
					printf("���볤�ȣ�%d\n", strlen(key));
				} while (strlen(key) > 8);

			}
			else
				printf("���볤�ȣ�%d\n", strlen(key));

			if (!Check_key(phead, Name, key))//��������Ϸ���
			{
				time--;
				printf("�������");
				if (time == 0)
				{
					printf("�����������Ѵ����ޣ�\n");
					return Error;
				}

				printf("������������%d��\n", time);
			}
			else
			{
				printf("������ȷ��\n");
				printf("ע�����󿨺�%s��ʧЧ!�Ƿ����ע����\n",Name);
				printf("ȷ��ע����... 1\n�������� ...2\n");
				scanf("%d", &result);
			}

		}

	}

	switch (result)
	{
	case 1:
	{
		printf("����ע��...\n");
		break;
	}
	case 2:
	{
		printf("�ϻ۵���ֹͣ��ע����\n");
		return Error;
		break;

	}
	default:
	{
		printf("Error input!\n");
		return Error;
		break;
	}
	}
	
	money = Exitmoney(phead,Name);
	printf("�˷ѽ��%.2f\n", money);
	if (upExitline(phead, Name))
	{
		if (upExitMoney(Name, money, MONEY))//money�ļ�ע�����˷Ѽ�¼����
		{
			value1=upExitMoneyfile(phead, Name, PATH);//file�ļ�����
				printf("ע������Ϣ���£�\n");
				printf("����  �˷ѽ��  ���\n");
				printf("%s\t%.2f\t%.2f\n", Name, money, value1);
				return OK;
		}

	}
	
	return Error;
}

//�޸�����
int Change(List *phead,List *pend)
{
	int time = 3;
	char Name[18];
	char key[8];
	char newkey1[8];
	char newkey2[2];
	//��file�ļ��ж�ȡ��Ϣ��������
	if (getLine(phead, pend, PATH))
	{
		printf("file�ļ���ȡ�ɹ�,");
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
			printf("file�ļ���ȡʧ��,");
			return Error;
		}
	}

	printf("��������ܿ��ţ�\n");
	scanf("%s", Name);
	if (strlen(Name) > 18)//�б𿨺źϷ���
	{
		do
		{//ѭ�����õ�������Ч����
			printf("���ų��ȣ�%d\n", strlen(Name));
			printf("���ų����ѳ����ޣ�(Error input!)��>18)\n");
			memset(Name, 0, sizeof(Name));//��0����
			printf("���ٴ����뿨��(����<18)��\n");
			scanf_s("%s", Name, sizeof(Name));
			printf("���ų��ȣ�%d\n", strlen(Name));
		} while (strlen(Name) > 18);
	}
	else
		printf("���ų��ȣ�%d\n", strlen(Name));

	if (!Check_line(phead, Name))//��⿨���Ƿ��Ѵ���file�ļ�������
	{
		printf("�޸��ܿ�����Ϣ��");
		return Error;
	}

	else
	{
		while (!Check_key(phead, Name, key))
		{

			printf("�����뿨��ԭ����(ʣ�����%d)��\n", time);
			scanf_s("%s", key, sizeof(key));
			if (strlen(key) > 8)//�б����볤�ȺϷ���
			{
				do
				{
					printf("���볤���ѳ����ޣ�(Error input!)��>8)\n");
					printf("���ٴ���������(����<8)��\n");
					memset(key, 0, sizeof(key));
					scanf_s("%s", key, sizeof(key));
					printf("���볤�ȣ�%d\n", strlen(key));
				} while (strlen(key) > 8);

			}
			else
				printf("���볤�ȣ�%d\n", strlen(key));

			if (!Check_key(phead, Name, key))//��������Ϸ���
			{
				time--;
				printf("�������");
				if (time == 0)
				{
					printf("�����������Ѵ����ޣ�");
					return Error;
				}

				printf("������������%d��\n", time);
			}
			else
			{
				printf("������ȷ��\n");
			}

		}
	}

	time = 3;
	
		do
		{
		printf("�����������룺\n");
		scanf("%s", newkey1);
		if (strcmp(newkey1, key) != 0)
			printf("����������ɹ����ٴ�������ȷ��������:\n");
		else
		{
			time--;
			printf("��ԭ�����ظ���");
			if (time)
				printf("��������%d��\n",time);
			else
			{
			printf("������������Ѵ�����,\n");
			return Error;
			}
				
		}
			
		} while (strcmp(newkey1, key) == 0);

		time = 3;
		do
		{

		scanf("%s", newkey2);
		if (strcmp(newkey1, newkey2) == 0)
		{
			printf("�����������룬���Ժ�...\n");
		}
		else
		{
			time--;
			if(time)
			printf("�����������벻������������%d�Σ���������:\n",time);
			else
			{

				printf("����ȷ�ϴ����Ѵ�����!\n");
				return Error;
			}
		}
			
		} while (strcmp(newkey1, newkey2) != 0);

		if (Reset(phead, PATH, Name, newkey1))//��������
		{
			printf("����д���ļ���...\n");
			printf("������Ϊ%s\n", newkey1);
			return OK;
		}
		return Error;
}

//����Աģʽ
int Admin(List *head,List *end,Charge* phead, Charge* pend, Pay* Start, Pay* Last, Block* chead, Block* cend)
{
	int choice = 1;
	if (Getin())
		printf("����Ա�˺ŵ�¼�ɹ���\n");
	else
	{
		return Error;
	}
	
	while (choice)
	{		
		//�������
			aDel(phead);
			*phead = NULL;
			*pend = NULL;
			aDel(Start);
			*Start = NULL;
			*Last = NULL;
			aDel(head);
			*head = NULL;
			*end = NULL;
			aDel(chead);
			*chead = NULL;
			*cend = NULL;

		Outadmin();
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
		{
			printf("Start...���Ῠ\n");
			if (Frozencard())
				printf("����ɹ���\n");
			else if (Frozencard() == 2)
				printf("�����ظ�����!\n");
			else
				printf("����ʧ��!\n");
			break;
		}
		case 2: 
		{
			printf("Start...���\n");
			if (Activecard(chead, cend))
			{
				printf("����ɹ���\n");
			}
			else
				printf("����ʧ��!\n");
			break;
		}
		case 3:
		{
			printf("Start...��ѯ��������Ϣ\n");//���������˵�����ֵ�˷�
			Querycard(phead,pend,Start,Last);
			break;
		}
		case 4:
		{
			printf("Start...��ʾ���п���Ϣ\n");
			Showfile(PATH);
			break;
		}
		case 5:
		{
			printf("Start...��ʾ���������˵�\n");
			Showbill(BILL);
			break;
		}
		case 6:
		{
			printf("Start...��ʾ���г�ֵ�˷���Ϣ\n");
			Showmoney(MONEY);
			break;
		}
		case 7:
		{
			printf("Start...��ʾ���ж��Ῠ��Ϣ\n");
			Showcold(COLD);
			break;
		}
		case 0:
		{
			printf("Start...�˳��������\n");
			choice = 0;
			break;
		}
		default:
		{
			printf("Error input!\n");
			break;
		}

		}

	}
	return OK;
	
}
//��ʾ�ļ������п���Ϣ
void Showfile(const char*pPath)
{
	FILE* fp;
	CardNode temp;
	printf("�ļ������п�����Ϊ��%d\n", CardCount(pPath));
	if (exitCardCount(pPath))
		printf("����%d�ſ���ע����\n", exitCardCount(pPath));
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("�޷����ļ�!\n");
		exit(0);
	}

	if (CardCount(pPath) == 0)
		printf("�ļ���û�п���Ϣ��\n");
	else
	{
	while (!feof(fp))
		{
		if (fread(&temp, sizeof(CardNode), 1, fp))
		//��ʾ����Ϣ
		ShowCARD(temp);
		else
			break;
		}

	}
	fclose(fp);
}
void Showbill(const char* pPath) 
{
	FILE* fp;
	Charge temp;
	temp = (Charge)malloc(sizeof(BillNode));
	printf("���Ѽ�¼����%d\n", Billcount(pPath));
	if (Billcount(pPath) == 0)
		printf("�ļ�����������Ϣ��\n");

	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("�޷����ļ�!\n");
		exit(0);
	}
	fseek(fp, 0, 0);//��λ���ļ��ײ�
		while (!feof(fp))
		{
			if (fread(temp, sizeof(BillNode), 1, fp))
				//��ʾ����Ϣ
				Printbill(temp);
			else
				break;
		}

	
	fclose(fp);
	free(temp);
}
void Showmoney(const char* pPath)
{
	FILE* fp;
	Mnode temp;
	printf("��ֵ�˷Ѽ�¼����%d\n", Moneycount(pPath));
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("�޷����ļ�!\n");
		exit(0);
	}

	if (Moneycount(pPath) == 0)
		printf("�ļ���û�п���Ϣ��\n");
	else
	{
		printf("״̬1����ֵ��״̬0���˷�\n");
		while (!feof(fp))
		{
			if (fread(&temp, sizeof(Mnode), 1, fp))
				//��ʾ����Ϣ
				Putmoney(temp);
			else
				break;
		}
	}
	fclose(fp);
}
void Showcold(const char* pPath)
{
	FILE* fp;
	Block temp;
	temp = (Block)malloc(sizeof(BlockNode));
	printf("�����¼����%d\n", Coldcount(pPath));
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("�޷����ļ�!\n");
		exit(0);
	}

	if (Coldcount(pPath) == 0)
		printf("�ļ���û�п���Ϣ��\n");
	else
	{
		while (!feof(fp))
		{
			if (fread(temp, sizeof(BlockNode), 1, fp))
				//��ʾ����Ϣ
				Putcold(temp);
			else
				break;
		}
	}
	free(temp);
	fclose(fp);
}