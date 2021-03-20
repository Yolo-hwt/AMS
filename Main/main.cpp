# define _CRT_SECURE_NO_WARNINGS
#include"menu.h"
//添加卡链表//file计费信息链表
List pHead = NULL;
List pend = NULL;
//下机链表//消费信息链表
Charge Head=NULL;
Charge End = NULL;
//充值退费链表
Pay Start=NULL;
Pay Last = NULL;
//激活冻结卡链表
Block chead = NULL;
Block cend = NULL;
int main()
{
	int m=1;
	printf("欢迎进入计费管理系统！！！\n");

	while(m)
	{
		//保证指针以空指针开始
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

		outputMenu();//显示菜单
		scanf_s("%d", &m);
		switch (m)
		{
		case 1: {
			printf("Start  添加卡...\n");
				Creat(&pHead,&pend,PATH);//添加卡函数
				break; 
				}
		case 2: {
			printf("Start  查询卡...\n");
				query(PATH);//查询卡函数
				break; 
				}
		case 3: {
			printf("Start  上机...\n"); 
			if (Logon(&pHead, &pend, PATH))//上机函数
			{
				printf("上机成功！\n");
			}
			else
				printf("上机失败！\n");
			
			break;
		}
		case 4: {
			printf("Start  下机...\n");
			if (settle(&pHead, &pend,&Head,&End))//下机函数
			{
				printf("下机成功！\n");
			}
			else
				printf("下机失败！\n");
			
			break;
		}
		case 5: {
			printf("Start  充值...\n");
			if(Recharge(&pHead,&pend,&Head,&End))
			{
				printf("充值成功！\n");
			}
			else
				printf("充值失败！\n");
			
			break;
		}
		case 6: {
			printf("Start  退费...\n"); 

			if (Return(&pHead, &pend,&Head,&End))
			{
				printf("退费成功！\n");
			}
			else
				printf("退费失败！\n");
			
			break;
		}
		
		case 7: { 
			printf("Start  注销卡...\n");
			if (ExitCard(&pHead, &pend))
			{
				printf("注销卡成功！\n");
			}
			else
				printf("注销卡失败！\n");
			
			break;
		}

		case 8: {
			printf("进入管理员模式\n");
			if (Admin(&pHead,&pend,&Head,&End,&Start,&Last,&chead,&cend))
				printf("已退出administer\n");
			else
				printf("登录失败!\n");
			break;
		}
		case 9:
		{
			printf("Start...修改密码\n");
			if (Change(&pHead, &pend))
			{
				printf("密码修改成功！\n");
			}
			else
				printf("修改密码失败!\n");
			
			break;
		}
		//case 10:
		//{
		//	printf("Start...显示所有卡信息\n");
		//	Showfile(PATH);
		//	break;
		//}

		//case 11:
		//{
		//	printf("Start...显示所有消费账单\n");
		//	Showbill(BILL);
		//	break;
		//}
		//case 12:
		//{
		//	printf("Start...显示所有充值退费信息\n");
		//	Showmoney(MONEY);
		//	break;
		//}
		case 0: {printf("Start  退出...\a\n"); return OK; }
		default: {printf("Error choice！\a\n");}
			printf("\n");
		}

	}
	
	return Error;
}