# define _CRT_SECURE_NO_WARNINGS
#include"menu.h"
//��ӿ�����//file�Ʒ���Ϣ����
List pHead = NULL;
List pend = NULL;
//�»�����//������Ϣ����
Charge Head=NULL;
Charge End = NULL;
//��ֵ�˷�����
Pay Start=NULL;
Pay Last = NULL;
//����Ῠ����
Block chead = NULL;
Block cend = NULL;
int main()
{
	int m=1;
	printf("��ӭ����Ʒѹ���ϵͳ������\n");

	while(m)
	{
		//��ָ֤���Կ�ָ�뿪ʼ
		aDel(&pHead);
		pHead = NULL;
		pend = NULL;
		aDel(&Head);
		Head = NULL;
		End = NULL;
		aDel(&Start);
		Start = NULL;
		Last = NULL;
		aDel(&chead);
		chead = NULL;
		cend = NULL;

		outputMenu();//��ʾ�˵�
		scanf_s("%d", &m);
		switch (m)
		{
		case 1: {
			printf("Start  ��ӿ�...\n");
				Creat(&pHead,&pend,PATH);//��ӿ�����
				break; 
				}
		case 2: {
			printf("Start  ��ѯ��...\n");
				query(PATH);//��ѯ������
				break; 
				}
		case 3: {
			printf("Start  �ϻ�...\n"); 
			if (Logon(&pHead, &pend, PATH))//�ϻ�����
			{
				printf("�ϻ��ɹ���\n");
			}
			else
				printf("�ϻ�ʧ�ܣ�\n");
			
			break;
		}
		case 4: {
			printf("Start  �»�...\n");
			if (settle(&pHead, &pend,&Head,&End))//�»�����
			{
				printf("�»��ɹ���\n");
			}
			else
				printf("�»�ʧ�ܣ�\n");
			
			break;
		}
		case 5: {
			printf("Start  ��ֵ...\n");
			if(Recharge(&pHead,&pend,&Head,&End))
			{
				printf("��ֵ�ɹ���\n");
			}
			else
				printf("��ֵʧ�ܣ�\n");
			
			break;
		}
		case 6: {
			printf("Start  �˷�...\n"); 

			if (Return(&pHead, &pend,&Head,&End))
			{
				printf("�˷ѳɹ���\n");
			}
			else
				printf("�˷�ʧ�ܣ�\n");
			
			break;
		}
		
		case 7: { 
			printf("Start  ע����...\n");
			if (ExitCard(&pHead, &pend))
			{
				printf("ע�����ɹ���\n");
			}
			else
				printf("ע����ʧ�ܣ�\n");
			
			break;
		}

		case 8: {
			printf("�������Աģʽ\n");
			if (Admin(&pHead,&pend,&Head,&End,&Start,&Last,&chead,&cend))
				printf("���˳�administer\n");
			else
				printf("��¼ʧ��!\n");
			break;
		}
		case 9:
		{
			printf("Start...�޸�����\n");
			if (Change(&pHead, &pend))
			{
				printf("�����޸ĳɹ���\n");
			}
			else
				printf("�޸�����ʧ��!\n");
			
			break;
		}
		//case 10:
		//{
		//	printf("Start...��ʾ���п���Ϣ\n");
		//	Showfile(PATH);
		//	break;
		//}

		//case 11:
		//{
		//	printf("Start...��ʾ���������˵�\n");
		//	Showbill(BILL);
		//	break;
		//}
		//case 12:
		//{
		//	printf("Start...��ʾ���г�ֵ�˷���Ϣ\n");
		//	Showmoney(MONEY);
		//	break;
		//}
		case 0: {printf("Start  �˳�...\a\n"); return OK; }
		default: {printf("Error choice��\a\n");}
			printf("\n");
		}

	}
	
	return Error;
}