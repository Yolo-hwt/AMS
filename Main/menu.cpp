
#include"menu.h"

//输出主菜单
void outputMenu()
{
	printf("_____________MENU____________\n");
	printf("1.添加卡\n");
	printf("2.查询卡\n");
	printf("3.上机\n");
	printf("4.下机\n");
	printf("5.充值\n");
	printf("6.退费\n");
	printf("7.注销卡\n");
	printf("8.admin\n");
	printf("9.修改密码\n");
	//printf("10.显示文件信息\n");
	//printf("11.显示所有消费账单\n");
	//printf("12.显示所有充值退费信息\n");
	printf("0.退出\n");
	printf("请选择功能————（0~8）\n");
	
}

//添加卡
int Creat(List* phead, List* pend,const char*pPath) //等价于CardNode **L
{
	int a = 1;
	char n[18];//卡号
	char k[8];//密码
	struct tm* eTime;     // 截止时间
	struct tm* sTime;   // 开卡时间	
	List pnew;

	while(a)
	{
		output();
	scanf("%d", &a);
		switch (a)
		{
			case 1:
			{
				printf("添加卡\n");
				if ((pnew = ((CardNode*)malloc(sizeof(CardNode)))) == NULL)//从堆获取内存
				{
					printf("堆内存已用完！\a\n");
					exit(0);
				}
				do
				{//循环得到长度，合法性均有效卡号
					printf("请输入卡号(长度<=18)：\n");
					scanf("%s", n);

					if (strlen(n) > 18)//判别卡号合法性
					{
						do
						{//循环，得到长度有效卡号
							printf("卡号长度：%d\n", strlen(n));
							printf("卡号长度已超上限！(Error input!)（>18)\n");
							memset(n, 0, sizeof(n));//置0数组
							printf("请再次输入卡号(长度<18)：\n");
							scanf_s("%s", n, sizeof(n));
							printf("卡号长度：%d\n", strlen(n));
						} while (strlen(n) > 18);
					}
					else
						printf("卡号长度：%d\n", strlen(n));

						if (Check_line(phead, n) || Check_user(n, pPath))//检测卡号是否已存在链表或文件中
							printf("系统已有卡号，请重新输入：……\n");
						else
						{
							strcpy(pnew->data.name, n);
							printf("新开卡号成功！请继续完善基本信息\n");
						}

			

				} while (Check_line(phead, n) || Check_user(n, pPath));//链表,文件中均不存在，退出循环

				printf("请输入密码(长度<8)：\n");
				scanf_s("%s", k, sizeof(k));
				printf("密码长度：%d\n", strlen(k));

				if (strlen(k) > 8)//判别密码合法性
				{
					do
					{
						printf("密码长度已超上限！(Error input!)（>8)\n");
						printf("请再次输入密码(长度<8)：\n");
						memset(k, 0, sizeof(k));
						scanf_s("%s", k, sizeof(k));
						printf("密码长度：%d\n", strlen(k));
					} while (strlen(k) > 8);

					strcpy(pnew->data.key, k);

				}
				else
					strcpy(pnew->data.key, k);


				printf("请输入开卡金额：\n");
				scanf("%f", &pnew->data.fleft);
				printf("\n");
				pnew->data.fAlluse = 0;//累计使用金额
				pnew->data.nDel = 0;//删除标识0，未删除
				pnew->data.Usecount = 0;//使用次数
				pnew->data.status = 0;//状态为未上机

				// 开卡时间，截止时间，最后使用时间都默认为当前时间。
				pnew->data.tStart = pnew->data.tEnd = pnew->data.tLastT = time(NULL);
				//将时间数值转化为当前时间
				sTime = localtime(&pnew->data.tStart);
				eTime = localtime(&pnew->data.tEnd);
				// 根据开卡时间，计算截止时间，每张卡的有效期为一年
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
				if (!Find(phead))//查询待添加卡
					printf("查询卡失败！\n");
				break;
			}
			case 3: {
				showAll(phead);//显示所有待添加卡;
				break;
			}
			case 4: {
				Delete(phead);//删除指定卡
				break;
			}
			case 5: {
				if (aDel(phead))//删除所有卡
					printf("所有待添加卡信息已删除！\n");
				else
					printf("卡信息删除失败！\n");
				break;
			}

			case 0: {
				printf("添加卡结束...\n");
				printf("卡信息正在写入文件中……\n");
				if (Linefile(phead, pPath)) 
				{
				printf("写入文件成功！\n");
				printf("文件中卡数量为：%d\n", CardCount(pPath));
				}
				else
					printf("写入文件失败\n");
					
				if (aDel(phead))//销毁链表
					printf("链表已销毁！\n");
				break;
			}

			default: {printf("Error choice！\a\n"); }
				   printf("\n");
		}

	}
	return OK;
}

//查询卡
void query(const char *pPath)
{
	char num[18];//保存待查询卡号
	char find[18];//保存由文件取出卡号
	CardNode temp;//保存读取出的对应卡号信息
	int ch;

	FILE* fp = NULL;  // 文件结构体指针

	do
	{
		printf("请输入待查询卡号(长度<18)：\n");
		scanf("%s", num);
		printf("卡号长度：%zd\n", strlen(num));
		if (strlen(num) > 18)//判别卡号长度合法性
		{

			do
			{
				printf("卡号长度已超上限！(Error input!)（>18)\n");
				memset(num, 0, sizeof(num));//置0数组
				printf("请再次输入卡号(长度<18)：\n");
				scanf("%s", num);
				printf("卡号长度：%zd\n", strlen(num));
			} while (strlen(num) > 18);

		}
		if (!Check_user(num, pPath))//检测卡号是否存在，返回值0，则不存在此卡
		{
			printf("是否创建与输入同名新卡？\n……1(yes）\n……0(no）\n");
			scanf_s("%d", &ch);

			if (ch == 1)
			{
				if (newadd(num,pPath))
				{
					printf("添加新卡成功！\n");
					printf("文件中卡数量为：%d\n", CardCount(pPath));
				}
				else
					printf("添加卡失败\n");

			}

			else
				printf("请查询其他卡：\n");
		}
	} while (!Check_user(num, pPath));//满足查询卡号有效，值为1时，退出循环
			
		// 以只读的方式打开文件
		if ((fp = fopen(pPath, "rb")) == NULL)
		{
			printf("无法打开文件!\n");
			exit(0);
		}
		//读取卡号，并比较卡号是否为当前查找的卡号,
		while (!feof(fp))
		{
			
			if (fread(find, sizeof(num), 1, fp) != 0)
			{
				if (strcmp(find, num) == 0)
				{
					printf("卡号：%s \n", num);
					fseek(fp, (0 - (sizeof(num))), SEEK_CUR);
					fread(&temp, sizeof(CardNode), 1, fp);
					fclose(fp);
					ShowCARD(temp);//显示卡信息
					break;
				}
				else
				{
					// 移到下一条记录
					fseek(fp, sizeof(CardNode) - sizeof(num), SEEK_CUR);
				}
			}

		}

	}

//上机
int Logon(List* phead,List* pend,const char*pPath)
{
	char Name[18] = { 0 };
	char key[8] = { 0 };
	int result=1;//保存上机结果
	int time = 3;//密码输入次数
	if (getLine(phead, pend, PATH))
	{
		printf("file文件读取成功,");
	}
	else
	{
		if (*phead == NULL)
		{
			printf("文件中无卡信息！");
			return Error;
		}
		else
		{
			printf("file文件读取失败,");
			return Error;
		}
	}
	printf("请输入上机卡号：\n");
	scanf("%s", Name);
	if (strlen(Name) > 18)//判别卡号合法性
	{
		do
		{//循环，得到长度有效卡号
			printf("卡号长度：%d\n", strlen(Name));
			printf("卡号长度已超上限！(Error input!)（>18)\n");
			memset(Name, 0, sizeof(Name));//置0数组
			printf("请再次输入卡号(长度<18)：\n");
			scanf_s("%s", Name, sizeof(Name));
			printf("卡号长度：%d\n", strlen(Name));
		} while (strlen(Name) > 18);
	}
	else
		printf("卡号长度：%d\n", strlen(Name));

	if (!Check_line(phead, Name))//检测卡号是否已存在文件链表中
	{
		
	printf("无卡号,或同名卡号已注销，");
	return Error;
	}

	else
	{
		if (!Check_user(Name, PATH))//存在文件链表后检测卡号是否冻结
		{
		printf("!");
		return Error;
		}
			
		while (!Check_key(phead, Name, key))
		{

		printf("请输入上机密码(剩余机会%d)：\n",time);
				scanf_s("%s", key, sizeof(key));
				if (strlen(key) > 8)//判别密码长度合法性
				{
					do
					{
						printf("密码长度已超上限！(Error input!)（>8)\n");
						printf("请再次输入密码(长度<8)：\n");
						memset(key, 0, sizeof(key));
						scanf_s("%s", key, sizeof(key));
						printf("密码长度：%d\n", strlen(key));
					} while (strlen(key) > 8);

				}
				else
					printf("密码长度：%d\n", strlen(key));
				if (!Check_key(phead, Name, key))//检验密码合法性
				{
					time--;
					printf("密码错误！");
					if (time == 0)
					{
						printf("密码错误次数已达上限！\n");
						return Error;
					}
						
					printf("还可输入密码%d次\n", time);
				}
				else
				{
					printf("密码正确！\n");
				}
		}
		
	}
		result = dologon(phead, Name);//获取卡上机状态
		switch (result)
		{
		case 1:
		{
			printf("卡号%s正在上机", Name);
			return Error
			break;
		}
		case 2:
		{
			printf("卡余额不足！");
			return Error;
			break;
		}
		case 3:
		{
			printf("卡号已注销！\n");
			return Error;
			break;
		}
		case 4:
		{
			printf("正在上机...\n");
			break;

		}
		default:
		{
			printf("Error!");
			return Error;
			break;
		}
		}	
		//file,bill文件,链表更新
		if (Linkupdate(phead,Name))
		{
		if(Fileupdate(phead, PATH,Name))
				{
				Savelogon(phead,BILL,Name);//写入上机信息并显示			
					return OK;
				}
		}	
		return Error;
	
}

//下机
int settle(List *head,List *end,Charge *phead,Charge *pend)
{
	char Name[18] = { 0 };
	char key[8] = { 0 };
	int result = 1;//保存下机结果
	int time = 3;//保存密码次数

	//从bill文件中读取信息生成链表
	if (getLine(phead, pend, BILL))
	{
		
		printf("bill文件读取成功,");
	}
	else
	{
		if (*phead == NULL)
		{
			printf("文件中无上机卡消费记录！");
			return Error;
		}
		else 
		{
		printf("bill文件读取失败,");
		return Error;
		}
		
	}
	//从file文件中读取信息生成链表
	if (getLine(head, end, PATH))
	{
		printf("file文件读取成功,");
	}
	else
	{
		if (*head == NULL)
		{
			printf("文件中无卡信息！");
			return Error;
		}
		else
		{
			printf("file文件读取失败,");
			return Error;
		}
	}

	printf("请输入下机卡号：\n");
	scanf("%s", Name);
	if (strlen(Name) > 18)//判别卡号合法性
	{
		do
		{//循环，得到长度有效卡号
			printf("卡号长度：%d\n", strlen(Name));
			printf("卡号长度已超上限！(Error input!)（>18)\n");
			memset(Name, 0, sizeof(Name));//置0数组
			printf("请再次输入卡号(长度<18)：\n");
			scanf_s("%s", Name, sizeof(Name));
			printf("卡号长度：%d\n", strlen(Name));
		} while (strlen(Name) > 18);
	}
	else
		printf("卡号长度：%d\n", strlen(Name));

	if (Check_line(phead, Name))//检测卡号是否已存在bill文件链表中
	{
		if (Check_user(Name, PATH))//若存在则检测卡号是否已注销
			printf("卡号状态正确\n");
		else
		{
			printf("无卡号上机信息，或卡号已注销，");
			return Error;
		}

	}
	else
	{
	printf("卡号未上机！");
	return Error;
	}
		
		while (!Check_key(head, Name, key))
		{

		printf("请输入下机卡密码(剩余机会%d)：\n", time);
		scanf_s("%s", key, sizeof(key));
		if (strlen(key) > 8)//判别密码长度合法性
		{
			do
			{
				printf("密码长度已超上限！(Error input!)（>8)\n");
				printf("请再次输入密码(长度<8)：\n");
				memset(key, 0, sizeof(key));
				scanf_s("%s", key, sizeof(key));
				printf("密码长度：%d\n", strlen(key));
			} while (strlen(key) > 8);

		}
		else
			printf("密码长度：%d\n", strlen(key));

		if (!Check_key(head, Name, key))//检验密码合法性
		{
			time--;
			printf("密码错误！");
			if (time == 0)
			{
				printf("密码错误次数已达上限！\n");
				return Error;
			}

			printf("还可输入密码%d次\n", time);
		}
		else
		{
			printf("密码正确！\n");
		}

		}
		

		result = dosettle(phead,head, Name);//获取卡下机状态
		switch (result)
		{
		case 1:
		{
			printf("卡号%s未上机", Name);
			return Error
				break;
		}
		case 2:
		{
			printf("卡余额不足！");
			return Error;
			break;
		}
		case 3:
		{
			printf("卡号已注销！\n");
			return Error;
			break;

		}
		case 4:
		{
			printf("正在下机...\n");
			break;

		}
		default:
		{
			printf("Error!\n");
			return Error;
			break;
		}
		}
		//file,bill文件,链表更新
		if (Linkupdate(phead,Name))//下机链表更新
		{
			printf("1");
			if (upbill(phead, BILL, Name))//bill消费记录更新
			{
				printf("2");
				upfile(head, phead, PATH, Name);//file文件更新
				printf("3");
				Put(phead, Name);//显示下机信息
				return OK;
			}
		}
		return Error;

}

//充值
int Recharge(List *phead,List *pend,Charge *head,Charge *end)
{
	List pcur;
	float value1=0;//保存余额
	float money=0;//保存充值金额
	int result=0;//保存充值条件结果
	char Name[18];
	char key[8];
	int time = 3;
	//从file文件中读取信息生成链表
	if (getLine(phead, pend, PATH))
	{
			printf("file文件读取成功,");
	}
	else
	{
		if (*phead == NULL)
		{
			printf("文件中无卡信息记录！");
			return Error;
		}
		else
		{
			printf("file文件读取失败,");
			return Error;
		}
	}
	//从bill文件中读取信息生成链表
	if (getLine(head, end, BILL))
	{
		printf("bill文件读取成功,");
	}
	else
	{
		if (*head == NULL)
		{
			printf("bill文件中无卡信息记录！");//（即使没有Bil文件记录任然不影响充值退费）
		}
		else
		{
			printf("bill文件读取失败,");
			return Error;
		}
	}

	printf("请输入充值卡号：\n");
	scanf("%s", Name);
	if (strlen(Name) > 18)//判别卡号合法性
	{
		do
		{//循环，得到长度有效卡号
			printf("卡号长度：%d\n", strlen(Name));
			printf("卡号长度已超上限！(Error input!)（>18)\n");
			memset(Name, 0, sizeof(Name));//置0数组
			printf("请再次输入卡号(长度<18)：\n");
			scanf_s("%s", Name, sizeof(Name));
			printf("卡号长度：%d\n", strlen(Name));
		} while (strlen(Name) > 18);
	}
	else
		printf("卡号长度：%d\n", strlen(Name));

	if (!Check_line(phead, Name))//检测卡号是否已存在file文件链表中
	{
		printf("无充值卡号信息，");
		return Error;
	}

	else
	{
		if (!Check_user(Name, PATH))//检测卡号是否已冻结
		{
			printf("无法充值！");
			return Error;
		}
		while (!Check_key(phead, Name, key))
		{

			printf("请输入充值卡号密码(剩余机会%d)：\n", time);
			scanf_s("%s", key, sizeof(key));
			if (strlen(key) > 8)//判别密码长度合法性
			{
				do
				{
					printf("密码长度已超上限！(Error input!)（>8)\n");
					printf("请再次输入密码(长度<8)：\n");
					memset(key, 0, sizeof(key));
					scanf_s("%s", key, sizeof(key));
					printf("密码长度：%d\n", strlen(key));
				} while (strlen(key) > 8);

			}
			else
				printf("密码长度：%d\n", strlen(key));

			if (!Check_key(phead, Name, key))//检验密码合法性
			{
				time--;
				printf("密码错误！");
				if (time == 0)
				{
					printf("密码错误次数已达上限！\n");
					return Error;
				}

				printf("还可输入密码%d次\n", time);
			}
			else
			{
				printf("密码正确！\n");
			}

		}


	}

	for (pcur = *phead; pcur != NULL; pcur = pcur->next)
	{
		if ((strcmp(Name, pcur->data.name) == 0))
		{
			if (pcur->data.nDel == 1)
			{
				printf("卡号已删除或注销！\n");
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
		printf("请输入充值金额:\n");
			break;
	}
	case 0:
	{
		printf("卡已失效！");
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
	scanf("%f", &money);//获取充值金额
	//file,money文件,链表更新
	if (upRechargeline(phead, Name, money))//链表更新
	{
		if (upChargeMoney(phead, Name,money,MONEY))//money文件充值退费记录更新
		{
			value1=upMoneyfile(phead,Name,PATH);//file文件更新
			upChargeMoneybill(head,Name,BILL,money);//bill文件更新
			printf("充值信息如下：\n");
			printf("卡号  充值金额  余额\n");
			printf("%s\t%.2f\t%.2f\n", Name, money, value1);
			return OK;
		}
	}
	return Error;
}

//退费
int Return(List* phead, List* pend, Charge* head, Charge* end)
{
	List pcur;
	float value1;//保存余额
	float money = 0;//保存退费金额
	
	int result = 0;//保存退费条件结果
	char Name[18];
	char key[8];
	int time = 3;
	//从file文件中读取信息生成链表
	if (getLine(phead, pend, PATH))
	{

			printf("file文件读取成功,");
	}
	else
	{
		if (*phead == NULL)
		{
			printf("文件中无卡信息！");
			return Error;
		}
		else
		{
			printf("file文件读取失败,");
			return Error;
		}
	}
	//从bill文件中读取信息生成链表
	if (getLine(head, end, BILL))
	{
		printf("bill文件读取成功,");
	}
	else
	{
		if (*head == NULL)
		{
			printf("bill文件中无卡信息记录！");//（即使没有Bil文件记录任然不影响充值退费）
		}
		else
		{
			printf("bill文件读取失败,");
			return Error;
		}
	}

	printf("请输入退费卡号：\n");
	scanf("%s", Name);
	if (strlen(Name) > 18)//判别卡号合法性
	{
		do
		{//循环，得到长度有效卡号
			printf("卡号长度：%d\n", strlen(Name));
			printf("卡号长度已超上限！(Error input!)（>18)\n");
			memset(Name, 0, sizeof(Name));//置0数组
			printf("请再次输入卡号(长度<18)：\n");
			scanf_s("%s", Name, sizeof(Name));
			printf("卡号长度：%d\n", strlen(Name));
		} while (strlen(Name) > 18);
	}
	else
		printf("卡号长度：%d\n", strlen(Name));

	if (!Check_line(phead, Name))//检测卡号是否已存在file文件链表中
	{
		printf("无退费卡号信息，");
		return Error;
	}

	else
	{
		if (!Check_user(Name, PATH))//检测卡号是否已冻结
		{
			printf("无法退费！");
			return Error;
		}
		while (!Check_key(phead, Name, key))//检测卡号密码正确性
		{

			printf("请输入退费卡号密码(剩余机会%d)：\n", time);
			scanf_s("%s", key, sizeof(key));
			if (strlen(key) > 8)//判别密码长度合法性
			{
				do
				{
					printf("密码长度已超上限！(Error input!)（>8)\n");
					printf("请再次输入密码(长度<8)：\n");
					memset(key, 0, sizeof(key));
					scanf_s("%s", key, sizeof(key));
					printf("密码长度：%d\n", strlen(key));
				} while (strlen(key) > 8);

			}
			else
				printf("密码长度：%d\n", strlen(key));

			if (!Check_key(phead, Name, key))//检验密码合法性
			{
				time--;
				printf("密码错误！");
				if (time == 0)
				{
					printf("密码错误次数已达上限！\n");
					return Error;
				}

				printf("还可输入密码%d次\n", time);
			}
			else
			{
				printf("密码正确！\n");
			}

		}


	}
	printf("请输入退费金额:\n");
	scanf("%f", &money);//获取退费金额
	for (pcur = *phead; pcur != NULL; pcur = pcur->next)
	{
		if ((strcmp(Name, pcur->data.name) == 0))
		{
			if (pcur->data.nDel == 1)
			{
				printf("卡号已删除或注销！\n");
			}
			else if((pcur->data.fleft <= 0)||(pcur->data.fleft<money))//余额小于0或小于退费金额
			{
				
				result = 2;
			}
			else
			{
				result = 1;//可退费
				break;
			}
		}

	}

	switch (result)
	{
	case 1:
	{
		printf("正在退费...\n");
		break;
	}
	case 2:
	{
		printf("卡号余额不足！\n");
		return Error;
		break;

	}
	case 0:
	{
		printf("卡已失效！");
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
	
	//file,money文件,链表更新
	if (upReturnline(phead, Name, money))//链表更新
	{
		if (upReturnMoney(phead, Name, money, MONEY))//money文件充值退费记录更新
		{
			value1 = upMoneyfile(phead, Name, PATH);//file文件更新
			upReturnMoneybill(head, Name, BILL, money);//bill文件更新
			printf("退费信息如下：\n");
			printf("卡号  退费金额  余额\n");
			printf("%s\t%.2f\t%.2f\n", Name, money, value1);
			return OK;
		}
	}
	return Error;
}

//注销卡
int ExitCard(List* phead,List *pend)
{
	int time = 3;
	char Name[18] = { 0 };
	char key[8] = { 0 };
	int result = 1;
	int get = 0;
	float money=0;//注销后退款金额
	float value1=0;//保存余额
	if (getLine(phead, pend, PATH))
	{
			printf("file文件读取成功,");
	}
	else
	{
		if (*phead == NULL)
		{
			printf("文件中无卡信息！");
			return Error;
		}
		else
		{
			printf("file文件读取失败,");
			return Error;
		}
	}

	printf("请输入注销卡号：\n");
	scanf("%s", Name);
	if (strlen(Name) > 18)//判别卡号合法性
	{
		do
		{//循环，得到长度有效卡号
			printf("卡号长度：%d\n", strlen(Name));
			printf("卡号长度已超上限！(Error input!)（>18)\n");
			memset(Name, 0, sizeof(Name));//置0数组
			printf("请再次输入卡号(长度<18)：\n");
			scanf_s("%s", Name, sizeof(Name));
			printf("卡号长度：%d\n", strlen(Name));
		} while (strlen(Name) > 18);
	}
	else
		printf("卡号长度：%d\n", strlen(Name));

	if (!Check_line(phead, Name))//检测卡号是否已存在file文件链表中
	{
		printf("无注销卡号信息，或卡号已注销");
		return Error;
	}

	else
	{
		while (!Check_key(phead, Name, key))//检测卡号密码正确性
		{

			printf("请输入注销卡号密码(剩余机会%d)：\n", time);
			scanf_s("%s", key, sizeof(key));
			if (strlen(key) > 8)//判别密码长度合法性
			{
				do
				{
					printf("密码长度已超上限！(Error input!)（>8)\n");
					printf("请再次输入密码(长度<8)：\n");
					memset(key, 0, sizeof(key));
					scanf_s("%s", key, sizeof(key));
					printf("密码长度：%d\n", strlen(key));
				} while (strlen(key) > 8);

			}
			else
				printf("密码长度：%d\n", strlen(key));

			if (!Check_key(phead, Name, key))//检验密码合法性
			{
				time--;
				printf("密码错误！");
				if (time == 0)
				{
					printf("密码错误次数已达上限！\n");
					return Error;
				}

				printf("还可输入密码%d次\n", time);
			}
			else
			{
				printf("密码正确！\n");
				printf("注销卡后卡号%s将失效!是否继续注销？\n",Name);
				printf("确认注销：... 1\n好像还有用 ...2\n");
				scanf("%d", &result);
			}

		}

	}

	switch (result)
	{
	case 1:
	{
		printf("正在注销...\n");
		break;
	}
	case 2:
	{
		printf("聪慧的你停止了注销！\n");
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
	printf("退费金额%.2f\n", money);
	if (upExitline(phead, Name))
	{
		if (upExitMoney(Name, money, MONEY))//money文件注销卡退费记录更新
		{
			value1=upExitMoneyfile(phead, Name, PATH);//file文件更新
				printf("注销卡信息如下：\n");
				printf("卡号  退费金额  余额\n");
				printf("%s\t%.2f\t%.2f\n", Name, money, value1);
				return OK;
		}

	}
	
	return Error;
}

//修改密码
int Change(List *phead,List *pend)
{
	int time = 3;
	char Name[18];
	char key[8];
	char newkey1[8];
	char newkey2[2];
	//从file文件中读取信息生成链表
	if (getLine(phead, pend, PATH))
	{
		printf("file文件读取成功,");
	}
	else
	{
		if (*phead == NULL)
		{
			printf("文件中无卡信息记录！");
			return Error;
		}
		else
		{
			printf("file文件读取失败,");
			return Error;
		}
	}

	printf("请输入改密卡号：\n");
	scanf("%s", Name);
	if (strlen(Name) > 18)//判别卡号合法性
	{
		do
		{//循环，得到长度有效卡号
			printf("卡号长度：%d\n", strlen(Name));
			printf("卡号长度已超上限！(Error input!)（>18)\n");
			memset(Name, 0, sizeof(Name));//置0数组
			printf("请再次输入卡号(长度<18)：\n");
			scanf_s("%s", Name, sizeof(Name));
			printf("卡号长度：%d\n", strlen(Name));
		} while (strlen(Name) > 18);
	}
	else
		printf("卡号长度：%d\n", strlen(Name));

	if (!Check_line(phead, Name))//检测卡号是否已存在file文件链表中
	{
		printf("无改密卡号信息，");
		return Error;
	}

	else
	{
		while (!Check_key(phead, Name, key))
		{

			printf("请输入卡号原密码(剩余机会%d)：\n", time);
			scanf_s("%s", key, sizeof(key));
			if (strlen(key) > 8)//判别密码长度合法性
			{
				do
				{
					printf("密码长度已超上限！(Error input!)（>8)\n");
					printf("请再次输入密码(长度<8)：\n");
					memset(key, 0, sizeof(key));
					scanf_s("%s", key, sizeof(key));
					printf("密码长度：%d\n", strlen(key));
				} while (strlen(key) > 8);

			}
			else
				printf("密码长度：%d\n", strlen(key));

			if (!Check_key(phead, Name, key))//检验密码合法性
			{
				time--;
				printf("密码错误！");
				if (time == 0)
				{
					printf("密码错误次数已达上限！");
					return Error;
				}

				printf("还可输入密码%d次\n", time);
			}
			else
			{
				printf("密码正确！\n");
			}

		}
	}

	time = 3;
	
		do
		{
		printf("请输入新密码：\n");
		scanf("%s", newkey1);
		if (strcmp(newkey1, key) != 0)
			printf("新密码输入成功，再次输入以确认新密码:\n");
		else
		{
			time--;
			printf("与原密码重复！");
			if (time)
				printf("还可输入%d次\n",time);
			else
			{
			printf("重置密码次数已达上限,\n");
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
			printf("正在重置密码，请稍后...\n");
		}
		else
		{
			time--;
			if(time)
			printf("两次输入密码不符，还可输入%d次，重新输入:\n",time);
			else
			{

				printf("密码确认次数已达上限!\n");
				return Error;
			}
		}
			
		} while (strcmp(newkey1, newkey2) != 0);

		if (Reset(phead, PATH, Name, newkey1))//重置密码
		{
			printf("密码写入文件中...\n");
			printf("新密码为%s\n", newkey1);
			return OK;
		}
		return Error;
}

//管理员模式
int Admin(List *head,List *end,Charge* phead, Charge* pend, Pay* Start, Pay* Last, Block* chead, Block* cend)
{
	int choice = 1;
	if (Getin())
		printf("管理员账号登录成功！\n");
	else
	{
		return Error;
	}
	
	while (choice)
	{		
		//清空链表
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
			printf("Start...冻结卡\n");
			if (Frozencard())
				printf("冻结成功！\n");
			else if (Frozencard() == 2)
				printf("无需重复冻结!\n");
			else
				printf("冻结失败!\n");
			break;
		}
		case 2: 
		{
			printf("Start...激活卡\n");
			if (Activecard(chead, cend))
			{
				printf("激活成功！\n");
			}
			else
				printf("激活失败!\n");
			break;
		}
		case 3:
		{
			printf("Start...查询卡消费信息\n");//包括消费账单，充值退费
			Querycard(phead,pend,Start,Last);
			break;
		}
		case 4:
		{
			printf("Start...显示所有卡信息\n");
			Showfile(PATH);
			break;
		}
		case 5:
		{
			printf("Start...显示所有消费账单\n");
			Showbill(BILL);
			break;
		}
		case 6:
		{
			printf("Start...显示所有充值退费信息\n");
			Showmoney(MONEY);
			break;
		}
		case 7:
		{
			printf("Start...显示所有冻结卡信息\n");
			Showcold(COLD);
			break;
		}
		case 0:
		{
			printf("Start...退出管理界面\n");
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
//显示文件中所有卡信息
void Showfile(const char*pPath)
{
	FILE* fp;
	CardNode temp;
	printf("文件中现有卡数量为：%d\n", CardCount(pPath));
	if (exitCardCount(pPath))
		printf("其中%d张卡已注销！\n", exitCardCount(pPath));
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("无法打开文件!\n");
		exit(0);
	}

	if (CardCount(pPath) == 0)
		printf("文件中没有卡信息！\n");
	else
	{
	while (!feof(fp))
		{
		if (fread(&temp, sizeof(CardNode), 1, fp))
		//显示卡信息
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
	printf("消费记录数：%d\n", Billcount(pPath));
	if (Billcount(pPath) == 0)
		printf("文件中无消费信息！\n");

	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("无法打开文件!\n");
		exit(0);
	}
	fseek(fp, 0, 0);//定位至文件首部
		while (!feof(fp))
		{
			if (fread(temp, sizeof(BillNode), 1, fp))
				//显示卡信息
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
	printf("充值退费记录数：%d\n", Moneycount(pPath));
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("无法打开文件!\n");
		exit(0);
	}

	if (Moneycount(pPath) == 0)
		printf("文件中没有卡信息！\n");
	else
	{
		printf("状态1：充值；状态0：退费\n");
		while (!feof(fp))
		{
			if (fread(&temp, sizeof(Mnode), 1, fp))
				//显示卡信息
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
	printf("冻结记录数：%d\n", Coldcount(pPath));
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("无法打开文件!\n");
		exit(0);
	}

	if (Coldcount(pPath) == 0)
		printf("文件中没有卡信息！\n");
	else
	{
		while (!feof(fp))
		{
			if (fread(temp, sizeof(BlockNode), 1, fp))
				//显示卡信息
				Putcold(temp);
			else
				break;
		}
	}
	free(temp);
	fclose(fp);
}