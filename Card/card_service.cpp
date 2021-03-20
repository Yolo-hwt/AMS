#define _CRT_SECURE_NO_WARNINGS
#include"card_service.h"
#include"card_line.h"


//检查文件中卡号合法性（是否已存在文件中未注销且未冻结)返回1，则符合
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
		printf("无法打开文件\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);//定位文件首部
	while (!feof(fp))
	{ 
		// 读取卡号，并比较卡号是否为当前的卡号
		if (fread(pcur, sizeof(CardNode), 1, fp) != 0)//逐条读取卡号
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
		printf("无法打开文件\n");
		exit(0);
	}
	fseek(bp, 0, SEEK_SET);//定位文件首部
	while (!feof(bp))
	{
		// 读取卡号，并比较卡号是否为当前的卡号
		if (fread(cur, sizeof(BlockNode), 1, bp) != 0)//逐条读取卡号
		{
			if ((strcmp(cur->data.coldName, card_name) == 0) && (cur->data.coldStatus == 1))//卡号同名且已冻结
			{
				b = 1;
				break;
			}
		}
	}
	if ((a + b) == 0)//文件中无卡记录
	{
	free(cur);
	fclose(bp);
	return Error;
	}
	if ((a + b) == 1)//file卡合法，cold中卡号未冻结
	{
		free(cur);
		fclose(bp);
		return OK;
	}
	if ((a + b) == 2)//file卡合法，cold中卡号已冻结
	{
		free(cur);
		fclose(bp);
		printf("卡号已冻结！\n");
		return Error;
	}
	return OK;
	
}


//计算文件中卡数量
int CardCount(const char* pPath)
{
	FILE* fp = NULL;  // 文件指针
	int nIndex = 0;   // 卡信息数量
	List pCARD;
	pCARD = (List)malloc(sizeof(CardNode));
	// 以只读模式打开文件
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("打开文件失败\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);//定位文件指针至文件首部
	// 逐行读取文件内容，获取的文件行数就是卡信息数
	while (!feof(fp))
	{
		if (fread(pCARD, sizeof(CardNode), 1, fp)!=0)
			nIndex++;
	}

	// 关闭文件
	fclose(fp);
	free(pCARD);
	return nIndex;
}
int Billcount(const char* pPath)
{
	FILE* fp = NULL;  // 文件指针
	int nIndex = 0;   // 卡信息数量
	BillNode *pCARD;
	pCARD = (Charge)malloc(sizeof(BillNode));
	// 以只读模式打开文件
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("打开文件失败\n");
		return Error;
	}
	fseek(fp, 0, SEEK_SET);//定位文件指针至文件首部
	// 逐行读取文件内容，获取的文件行数就是卡信息数
	while (!feof(fp))
	{
		if (fread(pCARD, sizeof(Bill), 1, fp) != 0)
			nIndex++;
	}

	// 关闭文件
	fclose(fp);
	free(pCARD);
	return nIndex;
}
int Moneycount(const char* pPath)
{
	FILE* fp = NULL;  // 文件指针
	int nIndex = 0;   // 卡信息数量
	Pay pCARD;
	pCARD = (Pay)malloc(sizeof(Mnode));
	// 以只读模式打开文件
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("打开文件失败\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);//定位文件指针至文件首部
	// 逐行读取文件内容，获取的文件行数就是卡信息数
	while (!feof(fp))
	{
		if (fread(pCARD, sizeof(Mnode), 1, fp) != 0)
			nIndex++;
	}

	// 关闭文件
	fclose(fp);
	free(pCARD);
	return nIndex;
}
int Coldcount(const char* pPath)
{
	FILE* fp = NULL;  // 文件指针
	int nIndex = 0;   // 卡信息数量
	Block pCARD;
	pCARD = (Block)malloc(sizeof(BlockNode));
	// 以只读模式打开文件
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("打开文件失败\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);//定位文件指针至文件首部
	// 逐行读取文件内容，获取的文件行数就是卡信息数
	while (!feof(fp))
	{
		if (fread(pCARD, sizeof(BlockNode), 1, fp) != 0)
			nIndex++;
	}

	// 关闭文件
	fclose(fp);
	free(pCARD);
	return nIndex;

}

//计算文件中已注销卡数量
int exitCardCount(const char* pPath)
{
	FILE* fp = NULL;  // 文件指针
	int nIndex = 0;   // 卡信息数量
	List pCARD;
	pCARD = (List)malloc(sizeof(CardNode));
	// 以只读模式打开文件
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("打开文件失败\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);//定位文件指针至文件首部
	// 逐行读取文件内容，获取的文件行数就是卡信息数
	while (!feof(fp))
	{
		if (fread(pCARD, sizeof(CardNode), 1, fp) != 0)
		{
			if(pCARD->data.nDel==1)
			nIndex++;
		}	
	}

	// 关闭文件
	fclose(fp);
	free(pCARD);
	return nIndex;
}

//查询卡中，添加新卡
int newadd(const char *num,const char *pPath)

{
	CardNode c;//定义卡信息结构体变量
	char nkey[18] = { 0 };//存放新卡密码
	struct tm* eTime; // 截止时间
	struct tm* sTime; // 开卡时间
	char name[18] = { 0 };
	char key[8] = { 0 };

	printf("新卡账号为%s\n", num);
	strcpy(c.data.name, num);
	printf("新开卡号成功！请继续完善基本信息\n");
	printf("请输入密码(长度<8)：\n");
	scanf("%s", key);
	

	if (strlen(key) > 8)//判别密码合法性
	{
		do
		{
			printf("密码长度：%zd\n", strlen(nkey));
			printf("密码长度已超上限！(Error input!)（>8)\n");
			printf("请再次输入密码(长度<8)：\n");
			memset(nkey, 0, sizeof(nkey));
			scanf("%s", nkey);

		} while (strlen(nkey) > 8);

		strcpy(c.data.key, nkey);

	}
	else
		printf("密码长度：%zd\n", strlen(key));
		strcpy(c.data.key, nkey);

	printf("请输入开卡金额：\n");
	scanf_s("%f", &c.data.fleft);
	c.data.fAlluse = c.data.fleft;//卡余额，累计金额
	c.data.nDel = 0;//删除标识0，未删除
	c.data.Usecount = 0;//使用次数
	c.data.status = 0;//状态
	c.data.tStart = c.data.tEnd = c.data.tLastT = time(NULL);


	// 开卡时间，截止时间，最后使用时间都默认为当前时间。
	// 根据开卡时间，计算截止时间，每张卡的有效期为一年

	sTime = localtime(&c.data.tStart);
	eTime = localtime(&c.data.tEnd);
	eTime->tm_year = sTime->tm_year + 1;
	c.data.tEnd = mktime(eTime);

	//写入新卡至文件中
	if (!Queryfile(c, pPath))
	{
		return Error;
	}

		return OK;
	
}

//结构体变量形式写入文件,成功返回1
int Queryfile(CardNode card, const char* pPath)
{
	FILE* fp = NULL;   // 文件结构体指针	

	// 以追加的模式打开文件，如果打开失败，则以只写的模式打开文件
	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
			printf("打开文件失败\n");
			return Error;
		}
	}
	
		fwrite(&card, sizeof(CardNode), 1, fp);	
		printf("写入文件成功！\n");

	// 关闭文件
	fclose(fp);
	return OK;
}

//上机更新file
int Fileupdate(List* phead, const char* pPath, const char* name)
{
	int line = 1;//文件行数
	int nindex =1;//链表位置
	List pcur;//遍历并保存更新信息
	pcur = *phead;
	List buff;//保存二进制文件
	buff = (CardNode*)malloc(sizeof(CardNode));
	
	FILE* fp;
	long IPosition = 0;//记录文件位置

	for (pcur; pcur != NULL; pcur = pcur->next)
	{
		if (!(strcmp(name, pcur->data.name) == 0))
		{
			nindex++;//获取上机卡的索引号
		}
		else
		{
			break;
		}
	}
		//以读写方式打开文件
		if ((fp = fopen(pPath, "rb+")) == NULL)
		{
			printf("打开文件失败\n");
			return Error;
		}

		while (!feof(fp))//循环获取文件位置
		{
			if (line == nindex)
			{
				IPosition = ftell(fp);//记录文件位置
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
		fseek(fp, IPosition, 0);//从文件首部记录偏移量定位指针
		fwrite(pcur, sizeof(CardNode), 1, fp);//将已更新卡信息写入文件
		fclose(fp);
		free(buff);
		return OK;
	
}
//下机更新bill文件
int upbill(Charge *phead,const char*pPath,const char *name)
{
	int get = 0;//查找标识
	int index=1;
	int line=1;

	Charge cur;
	cur = *phead;

	Charge Status;//保存链表中合理信息//为了不影响链表中原本信息进而影响file文件更新(预先初始化phead)
	Status = (Charge)malloc(sizeof(BillNode));

	Charge buff;//保存二进制文件
	buff = (Charge)malloc(sizeof(BillNode));

	FILE* fp;
	long IPosition = 0;//记录文件位置

	for (cur; cur != NULL; cur = cur->next)
	{
		if ((strcmp(name, cur->data.aCardName) == 0) && (cur->data.nDel == 0) && (cur->data.nStatus == 0))//满足卡号同名，未注销，未结算
		{
			get = 1;
			//为临时变量赋值
			strcpy(Status->data.aCardName, name);
			Status->data.fAmount = cur->data.fAmount;
			Status->data.left = cur->data.left;
			Status->data.nDel = 0;
			Status->data.tEnd = cur->data.tEnd;
			Status->data.tStart = cur->data.tStart;
			Status->data.nStatus = 1;
			break;
		}
		else//链表中查找到对应卡号后更新卡信息
		{
			index++;//获取上机卡的索引号
		}
	}
	printf("upbill中get是%d\n", get);
	if (get)
	{

		//以读写方式打开文件
		if ((fp = fopen(pPath, "rb+")) == NULL)
		{
			printf("打开文件失败\n");
			return Error;
		}

		while (!feof(fp))//循环获取文件位置
		{
			if (line == index)
			{
				IPosition = ftell(fp);//记录文件位置
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
		fseek(fp, IPosition, 0);//从文件首部记录偏移量定位指针
		fwrite(Status, sizeof(BillNode), 1, fp);//将已更新卡信息写入文件
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
//下机更新file文件
int upfile(List* phead,Charge *head, const char* pPath, const char* name)
{
	int get = 0;
	int line = 1;//文件行数
	int nindex = 1;//链表位置

	List pcur;//遍历卡信息链表并保存更新信息
	pcur = *phead;

	Charge find;//查找下机链表中卡号，获取计费信息
	find = *head;
	
	//Charge mark;
	//mark = (Charge)malloc(sizeof(BillNode));

	List buff;//保存二进制文件
	buff = (CardNode*)malloc(sizeof(CardNode));

	FILE* fp;
	long IPosition = 0;//记录文件位置

	for (find; find != NULL; find = find->next)//查找下机链表中对应卡
	{
		if ((strcmp(find->data.aCardName, name) == 0) && (find->data.nStatus == 0) && (find->data.nDel == 0))//卡号同名，状态未结算，标识未删除
		{
			get = 1;
			//mark = find;
		break;
		}
			
	}
	printf("upfile中get是%d\n", get);

	for (pcur; pcur != NULL; pcur = pcur->next)
	{
		if((strcmp(pcur->data.name,name)==0)&&(pcur->data.nDel==0)&&(pcur->data.status==1))//卡号同名，未注销，正在上机
		{
			//链表中查找到对应卡号后更新卡信息
			pcur->data.fAlluse += find->data.fAmount;//累计消费金额
			pcur->data.fleft = find->data.left;//卡余额
			pcur->data.status = 0;//卡状态，已下机
			pcur->data.tLastT = find->data.tEnd;//上次使用时间为下机时间
			break;
		}
		else
		{
			nindex++;//获取上机卡的索引号
		}
	}

	//以读写方式打开文件
	if ((fp = fopen(pPath, "rb+")) == NULL)
	{
		printf("打开文件失败\n");
		return Error;
	}

	while (!feof(fp))//循环获取文件位置
	{
		if (line == nindex)
		{
			IPosition = ftell(fp);//记录文件位置
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
	fseek(fp, IPosition, 0);//从文件首部记录偏移量定位指针
	fwrite(pcur, sizeof(CardNode), 1, fp);//将已更新卡信息写入文件
	fclose(fp);
	free(buff);
	return OK;

}

//添加bill消费记录
int addBill(BillNode card,const char* pPath)
{
	FILE* fp;
	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
	printf("上机文件打开失败！\n");
		return Error;
		}
	}
	fwrite(&card, sizeof(BillNode), 1, fp);
	fclose(fp);
	return OK;
}

//保存上机卡消费信息并显示
void Savelogon(List *phead,const char *pPath ,const char *name)
{
	char last[20];//储存上机时间
	BillNode save;//将上机卡信息写入消费记录文件bill
	List pcur;//遍历上机链表
	pcur = *phead;
	
//对上机卡节点结构体变量赋值
			save.data.fAmount = 0;//消费金额
			save.data.nStatus = 0;//结算状态，未结算
			save.data.nDel = 0;//删除标识，未删除
			save.data.tStart = time(NULL);//上机时间为当前时间
			save.data.tEnd = time(NULL);//下机时间默认为当前时间
			strcpy(save.data.aCardName, name);//卡号
			for (pcur; pcur != NULL; pcur = pcur->next)
			{
				if ((strcmp(name, pcur->data.name) == 0)&&(pcur->data.nDel==0))//卡号同名，未删除
				{
					save.data.left = pcur->data.fleft;//卡余额
					timeToString(pcur->data.tLastT, last);
					break;
				}
			}
			
			if (addBill(save,pPath))
				printf("消费记录已保存!\n");

			printf("上机卡信息如下：\n");
			// 输出表格的表头
			printf("卡号\t余额\t卡状态\t使用次数\t上机时间\n");
			printf("%s\t%0.1f\t%d\t%d\t%s\n", pcur->data.name, save.data.left, pcur->data.status, pcur->data.Usecount, last);
			
}

//计算消费金额
float getAmount(Charge* phead, const char* name)
{
	int unit = 1;//最小收费单元1min
	int cost = 1;//每单元价钱1yuan
	int count = 0;//记录单元数（四舍五入）
	int nMinute=0;
	float Amount=0;//初始化消费为0

	time_t nSec=0;//保存上机时间
	time_t tEnd=time(NULL);//保存结算金额时间

	Charge pcur;
	pcur = *phead;
	for (pcur; pcur != NULL; pcur = pcur->next)
	{
		if((strcmp(name, pcur->data.aCardName) == 0)&&(pcur->data.nStatus==0))//卡号匹配且未结算
		{
			nSec = pcur->data.tStart;//获取保存上机时间
			break;
		}
	}
	nSec = tEnd-nSec;//计算总上机时常
	nMinute = int((nSec / 60)+0.5);
	if (nMinute % unit == 0)
	{
		count = int(nMinute / unit);//计费单元数
	}
	else
	{
		count = int((nMinute / unit) + 0.5);
	}
	Amount = float(count * cost);
	return Amount;
}

//验证卡号密码正确性(返回0，不正确）
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
				a = 1;//满足卡号密码均正确
			break;
		}
	}
	return a;

}

//更新money文件
int upChargeMoney(List* phead, const char* name, float money, const char* pPath)
{
	FILE* fp;
	List pcur;
	pcur = *phead;
	Pay up;//保存充值信息
	up = (Pay)malloc(sizeof(Mnode));
	
	//对充值信息结构体up赋值
	up->data.fAmount = money;//充值金额
	up->data.nStatus = 1;//状态1为充值
	strcpy(up->data.Name, name);//卡号
	up->data.tTime = time(NULL);//充值时间为当前时间
	up->data.nDel = 0;//删除标识0（未删除）

	for (pcur; pcur != NULL; pcur = pcur->next)
	{
		if (strcmp(name, pcur->data.name) == 0)
		{
			up->data.left = pcur->data.fleft;//卡余额
			break;
		}
	}

	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
			printf("打开文件失败\n");
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
	Pay up;//保存退费信息
	up = (Pay)malloc(sizeof(Mnode));

	//对退费信息结构体up赋值
	up->data.fAmount = money;//退费金额
	up->data.nStatus = 0;//状态0为退费
	strcpy(up->data.Name, name);//卡号
	up->data.tTime = time(NULL);//退费时间为当前时间
	up->data.nDel = 0;//删除标识0（未删除）

	for (pcur; pcur != NULL; pcur = pcur->next)
	{
		if (strcmp(name, pcur->data.name) == 0)
		{
			up->data.left = pcur->data.fleft;//卡余额
			break;
		}
	}

	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
			printf("打开文件失败\n");
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
	Pay up;//保存注销卡退费信息
	up = (Pay)malloc(sizeof(Mnode));

	//对注销卡退费信息结构体up赋值
	up->data.fAmount = money;//退费金额
	up->data.nStatus = 0;//状态0为退费
	strcpy(up->data.Name, name);//卡号
	up->data.tTime = time(NULL);//退费时间为当前时间
	up->data.nDel = 1;//删除标识1（已删除）
	up->data.left = 0;//卡余额

	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
			printf("打开文件失败\n");
			return Error;
		}
	}
	fwrite(up, sizeof(Mnode), 1, fp);
	fclose(fp);
	free(up);
	return OK;
}

//充值退费注销卡file文件
 float upMoneyfile(List* phead, const char* name, const char* pPath)
{
	int line = 1;//文件行数
	int nindex = 1;//链表位置
	FILE* fp;//文件指针
	long IPosition = 0;//记录文件位置
	float value = 0;//保存余额
	List pcur;//遍历卡号
	pcur = *phead;

	List buff;//保存二进制文件
	buff = (CardNode*)malloc(sizeof(CardNode));

	for (pcur; pcur != NULL; pcur = pcur->next)
	{
		if (!(strcmp(name, pcur->data.name) == 0)||(pcur->data.nDel==1))
		{
			nindex++;//获取上机卡的索引号
		}
		else//链表中查找到对应卡号后更新卡信息
		{
			value = pcur->data.fleft;
			break;
		}
	}

	if ((fp = fopen(pPath, "rb+")) == NULL)
		{
			printf("打开文件失败\n");
			exit(0);
		}

	while (!feof(fp))//循环获取文件位置
	{
		if (line == nindex)
		{
			IPosition = ftell(fp);//记录文件位置
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

	fseek(fp, IPosition, 0);//从文件首部记录偏移量定位指针
	fwrite(pcur, sizeof(CardNode), 1, fp);
	fclose(fp);
	free(buff);
	return value;
}
 //注销卡file文件
 float upExitMoneyfile(List* phead, const char* name, const char* pPath)
 {
	 int line = 1;//文件行数
	 int nindex = 1;//链表位置
	 FILE* fp;//文件指针
	 long IPosition = 0;//记录文件位置
	 float value = 0;//保存余额
	 List pcur;//遍历卡号
	 pcur = *phead;

	 List buff;//保存二进制文件
	 buff = (CardNode*)malloc(sizeof(CardNode));

	 for (pcur; pcur != NULL; pcur = pcur->next)
	 {
		 if((!(strcmp(name, pcur->data.name) == 0))||(pcur->data.nDel==1))
		 {
			 nindex++;//获取上机卡的索引号
		 }
		 else//链表中查找到对应卡号后更新卡信息
		 {
			 pcur->data.nDel = 1;//卡状态更新为已删除
			 value = pcur->data.fleft;
			 break;
		 }
	 }

	 if ((fp = fopen(pPath, "rb+")) == NULL)
	 {
		 printf("打开文件失败\n");
		 exit(0);
	 }

	 while (!feof(fp))//循环获取文件位置
	 {
		 if (line == nindex)
		 {
			 IPosition = ftell(fp);//记录文件位置
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

	 fseek(fp, IPosition, 0);//从文件首部记录偏移量定位指针
	 fwrite(pcur, sizeof(CardNode), 1, fp);
	 fclose(fp);
	 free(buff);
	 return value;
 }
 //返回注销卡退费金额
 float Exitmoney(List* phead, const char* name)//返回注销卡退款金额
 {
	 float m=0;
		List pcur;
		pcur = *phead;
		for (pcur; pcur != NULL; pcur = pcur->next)
		{
			if (strcmp(name, pcur->data.name) == 0)
			{
				if (pcur->data.nDel == 0)//卡号未注销
				{
					m = pcur->data.fleft;//将余额退费
					break;
				}
			}
		}
		
		return m;
 }
 //充值退费更新bill文件
 int upChargeMoneybill(Charge* phead, const char* name, const char* pPath,float money)
 {
	 int get = 0;//标识是否找到符合条件bill文件信息
	 int line = 1;//文件行数
	 int nindex = 1;//链表位置
	 FILE* fp;//文件指针
	 long IPosition = 0;//记录文件位置
	 Charge pcur;//遍历卡号
	 pcur = *phead;

	 Charge buff;//保存二进制文件
	 buff = (Charge)malloc(sizeof(BillNode));

	 for (pcur; pcur != NULL; pcur = pcur->next)
	 {
		 if (!(strcmp(name, pcur->data.aCardName) == 0) || (pcur->data.nDel == 1)||(pcur->data.nStatus==1))//卡号同名，未注销，未结算
		 {
			 nindex++;//获取上机卡的索引号
		 }
		 else//链表中查找到对应卡号后更新卡信息
		 {
			 get = 1;
			 pcur->data.left += money;//余额充值退费后更新
			 break;
		 }
	 }
	 if (get)//找到可更新bill信息
	 {
		if ((fp = fopen(pPath, "rb+")) == NULL)
		 {
			 printf("打开文件失败\n");
			 return Error;
		 }

		 while (!feof(fp))//循环获取文件位置
		 {
			 if (line == nindex)
			 {
				 IPosition = ftell(fp);//记录文件位置
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

		 fseek(fp, IPosition, 0);//从文件首部记录偏移量定位指针
		 fwrite(pcur, sizeof(BillNode), 1, fp);
		 fclose(fp);
	 }
	 else//无可更新信息
	 {
		 free(buff);
		 return Error;
	 }
	 free(buff);
	 return OK;
 }
 int upReturnMoneybill(Charge* phead, const char* name, const char* pPath, float money)
 {
	 int get = 0;//标识是否找到符合条件bill文件信息
	 int line = 1;//文件行数
	 int nindex = 1;//链表位置
	 FILE* fp;//文件指针
	 long IPosition = 0;//记录文件位置
	 Charge pcur;//遍历卡号
	 pcur = *phead;

	 Charge buff;//保存二进制文件
	 buff = (Charge)malloc(sizeof(BillNode));

	 for (pcur; pcur != NULL; pcur = pcur->next)
	 {
		 if (!(strcmp(name, pcur->data.aCardName) == 0) || (pcur->data.nDel == 1) || (pcur->data.nStatus == 1))//卡号同名，未注销，未结算
		 {
			 nindex++;//获取上机卡的索引号
		 }
		 else//链表中查找到对应卡号后更新卡信息
		 {
			 get = 1;
			 pcur->data.left -= money;//余额充值退费后更新
			 break;
		 }
	 }
	 if (get)//找到可更新bill信息
	 {
		 if ((fp = fopen(pPath, "rb+")) == NULL)
		 {
			 printf("打开文件失败\n");
			 return Error;
		 }

		 while (!feof(fp))//循环获取文件位置
		 {
			 if (line == nindex)
			 {
				 IPosition = ftell(fp);//记录文件位置
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

		 fseek(fp, IPosition, 0);//从文件首部记录偏移量定位指针
		 fwrite(pcur, sizeof(BillNode), 1, fp);
		 fclose(fp);
	 }
	 else//无可更新信息
	 {
		 free(buff);
		 return Error;
	 }
	 free(buff);
	 return OK;
 }

 //重置密码
 int Reset(List* phead, const char* pPath, const char *name,const char *newkey)
 {
	 int line = 1;//文件行数
	 int nindex = 1;//链表位置
	 FILE* fp;//文件指针
	 long IPosition = 0;//记录文件位置
	 List pcur;//遍历卡号
	 pcur = *phead;

	 List buff;//保存二进制文件
	 buff = (CardNode*)malloc(sizeof(CardNode));

	 for (pcur; pcur != NULL; pcur = pcur->next)
	 {
		 if ((!(strcmp(name, pcur->data.name) == 0)) || (pcur->data.nDel == 1))
		 {
			 nindex++;//获取上机卡的索引号
		 }
		 else//链表中查找到对应卡号后更新卡信息
		 {
			 strcpy(pcur->data.key,newkey);//更新卡密码
			 break;
		 }
	 }

	 if ((fp = fopen(pPath, "rb+")) == NULL)
	 {
		 printf("打开文件失败\n");
		 exit(0);
	 }

	 while (!feof(fp))//循环获取文件位置
	 {
		 if (line == nindex)
		 {
			 IPosition = ftell(fp);//记录文件位置
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

	 fseek(fp, IPosition, 0);//从文件首部记录偏移量定位指针
	 fwrite(pcur, sizeof(CardNode), 1, fp);
	 fclose(fp);
	 free(buff);
	 return OK;
 }

 //管理员模式子功能
//显示子菜单
void Outadmin()
{
	printf("*** _Menu of Administer_ ***\n");
	printf("1.冻结卡\n");
	printf("2.激活卡\n");
	printf("3.查询卡消费信息\n");
	printf("4.显示所有卡信息(file)\n");
	printf("5.显示所有消费账单(bill)\n");
	printf("6.显示充值退费信息(money)\n");
	printf("7.显示所有冻结卡信息(cold)\n");
	printf("0.退出管理界面\n");
}
//登录管理员账号
int Getin()
{
	int a = 3;
	char key[8];
	char Name[8];
	
	
		printf("请输入管理员账号：\n");
		scanf("%s", Name);
		if (strcmp(Name, ADMINISTER) == 0)
			printf("账号正确！请输入密码！\n");
		else
		{
			printf("账号不存在！\n");
			return Error;
		}
		while (Check_admin(key))
		{
			printf("请输入密码：\n");
		scanf("%s", key);
		a--;
		if (Check_admin(key)==0)
			printf("已进入管理员模式！\n");
		else
		{
			printf("密码错误\n!");
			if (a == 0)
			{
			printf("密码输次数已达上限！\n");
			return Error;
			}
				
			printf("还可输入密码%d次", a);
		}	
		}
		return a;
}
//检测管理员密码(正确返回0）
int Check_admin(const char *key)
{
	int back = 1;
	if (strcmp(key, POWERWORD) == 0)
		back = 0;
	return back;
}

//冻结卡
int Frozencard()
{
	int sta = 1;
	char t1[20];//冻结时间
	char t2[20];//激活时间
	Block card;
	card = (Block)malloc(sizeof(BlockNode));
	char num[18];
	int times = 3;
	while (!Check_user(num, PATH))//检测卡号是否存在，返回值0，则不存在此卡
	{
			printf("请输入冻结卡号(长度<18)：");
			printf("（还可输入%d次）\n", times);
			scanf("%s", num);
			times--;
			printf("卡号长度：%zd\n", strlen(num));
			if (strlen(num) > 18)//判别卡号长度合法性
			{

				do
				{
					printf("卡号长度已超上限！(Error input!)（>18)\n");
					memset(num, 0, sizeof(num));//置0数组
					if (times)//次数不为0
					{
						printf("请再次输入冻结卡号(长度<18)：");
						printf("（还可输入%d次）\n", times);
						scanf("%s", num);
						times--;
						printf("卡号长度：%zd\n", strlen(num));
					}
					else
					{
						printf("冻结卡号输入次数已达上限！\n");
						return Error;

					}



				} while (strlen(num) > 18);

			}

			if (Check_Cold(num, COLD))//卡号已冻结
			{
				printf("卡号已冻结，");
				sta = 2;
				return sta;
			}
		
		if (!Check_user(num, PATH)&&(times))//卡号未匹配，且仍有输入次数
			printf("冻结卡号不存在，请再次输入：\n");

		if (!Check_user(num, PATH) && (times==0))//卡号未匹配，没有输入次数
		{
			printf("冻结卡号输入次数已达上限！\n");
			return Error;
		}
		if(Check_user(num, PATH)&&(times==0))//匹配且没有输入次数
			printf("冻结中...\n");
		
		if (Check_user(num, PATH) && (times))//匹配且仍有输入次数
			printf("冻结中...\n");
	}
	
		
	//为冻结卡结构体变量赋值
	strcpy(card->data.coldName, num);
	card->data.coldStatus = 1;//标识1，已冻结
	card->data.clod_time = time(NULL);//冻结时间为当前时间
	card->data.act_time = time(NULL);//解冻时间默认为当前时间

	if (upFrozencold(card, COLD))//更新cold文件
	{
	timeToString(card->data.clod_time, t1);
	timeToString(card->data.act_time, t2);

	printf("卡号%s已冻结", num);
	//显示冻结卡信息
	printf("冻结卡信息如下:\n");
	printf("卡号\t冻结时间\t激活时间\n");
	printf("%s\t%s\t%s\n", num, t1, t2);
	free(card);
	return OK;
	}
	free(card);
	return Error;
}
//激活卡
int Activecard(Block *phead,Block *pend)
{
	char num[18] = { 0 };
	int times = 3;
	while (!Check_Cold(num,COLD))//检测卡号是否存在cold文件中且符合条件，返回值0，则不存在
	{
		printf("请输入激活卡号(长度<18)：");
		printf("（还可输入%d次）\n", times);
		scanf("%s", num);
		times--;
		printf("卡号长度：%zd\n", strlen(num));
		if (strlen(num) > 18)//判别卡号长度合法性
		{

			do
			{
				printf("卡号长度已超上限！(Error input!)（>18)\n");
				memset(num, 0, sizeof(num));//置0数组
				if (times)//次数不为0
				{
					printf("请再次输入激活卡号(长度<18)：");
					printf("（还可输入%d次）\n", times);
					scanf("%s", num);
					times--;
					printf("卡号长度：%zd\n", strlen(num));
				}
				else
				{
					printf("激活卡号输入次数已达上限！\n");
					return Error;

				}

			} while (strlen(num) > 18);

		}

		if (!Check_Cold(num, COLD) && (times))//未匹配，且仍有输入次数
			printf("激活卡号不存在，请再次输入：\n");
		else if (!Check_Cold(num, COLD) && (times == 0))//未匹配，没有输入次数
		{
			printf("激活卡号输入次数已达上限！\n");
			return Error;
		}
		else if (Check_Cold(num, COLD) && (times == 0))//匹配且没有输入次数
			printf("激活中...\n");
		else//匹配且仍有输入次数
			printf("激活中...\n");
	}
	//从cold文件中读取信息生成链表
	if (getLine(phead, pend, COLD))
	{
		printf("cold文件读取成功,");
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
			printf("cold文件读取失败,");
			return Error;
		}
	}
	
	upActivecold(phead, num, COLD);//更新cold文件	
			return OK;
}
//冻结卡更新cold文件
int upFrozencold(Block card, const char* pPath)
{
	FILE* fp;
	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
			printf("上机文件打开失败！\n");
			return Error;
		}
	}
	fwrite(card, sizeof(BlockNode), 1, fp);
	fclose(fp);
	return OK;
}
//激活卡更新cold文件并显示
int upActivecold(Block *phead, const char *name,const char* pPath)
{
	int get = 0;//查找标识
	int index = 1;//链表位置
	int line = 1;//文件位置

	Block cur;
	cur = *phead;

	Block buff;//保存二进制文件
	buff = (Block)malloc(sizeof(BlockNode));

	FILE* fp;
	long IPosition = 0;//记录文件位置

	for (cur; cur != NULL; cur = cur->next)
	{
		if ((strcmp(name, cur->data.coldName) == 0) && (cur->data.coldStatus==1))//满足卡号同名，已冻结
		{
			get = 1;
			cur->data.coldStatus = 0;//标识为0激活
			cur->data.act_time = time(NULL);//激活时间为当前时间
			break;
		}
		else//链表中查找到对应卡号后更新卡信息
		{
			index++;//获取上机卡的索引号
		}
	}
	//printf("upActivecold中get是%d\n", get);
	if (get)
	{

		//以读写方式打开文件
		if ((fp = fopen(pPath, "rb+")) == NULL)
		{
			printf("打开文件失败\n");
			return Error;
		}

		while (!feof(fp))//循环获取文件位置
		{
			if (line == index)
			{
				IPosition = ftell(fp);//记录文件位置
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
		fseek(fp, IPosition, 0);//从文件首部记录偏移量定位指针
		fwrite(cur, sizeof(BlockNode), 1, fp);//将已更新卡信息写入文件
		fclose(fp);
		free(buff);
		printf("激活卡信息如下：\n");
		Putcold(cur);
		return OK;

	}
	else
		free(buff);
	return Error;
}
//激活卡,冻结卡时检测cold文件中是否存在符合条件信息(存在且符合返回1）
int Check_Cold(const char* name, const char* pPath)
{
	FILE* fp = NULL;  // 文件指针
	int get = 0; 
	Block pCARD;
	pCARD = (Block)malloc(sizeof(BlockNode));
	// 以只读模式打开文件
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("打开文件失败\n");
		return Error;
	}
	fseek(fp, 0, SEEK_SET);//定位文件指针至文件首部
	// 逐行读取文件内容，获取的文件行数就是卡信息数
	while (!feof(fp))
	{
		if (fread(pCARD, sizeof(BlockNode), 1, fp) != 0)
			if ((strcmp(pCARD->data.coldName, name) == 0) && (pCARD->data.coldStatus == 1))//卡号同名且已冻结
				get = 1;
	}
	//printf("Check_Cold中get%d\n", get);
	// 关闭文件
	fclose(fp);
	free(pCARD);
	return get;
}


//查找卡号消费账单
int Querycard(Charge *phead, Charge *pend,Pay *Start,Pay *Last)
{
	
	char num[18] = { 0 };
	while (!Check_user(num, PATH))//检测卡号是否存在，返回值0，则不存在此卡
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
		if (!Check_user(num, PATH))
			printf("卡号不存在，请再次输入：\n");
		else
			printf("查询中...\n");
	}

	//从bill文件中读取计费信息
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
	//从money文件中读取计费信息
	if (getLine(Start, Last, MONEY))
	{

		printf("money文件读取成功\n");
	}
	else
	{
		if (*Start == NULL)
		{
			printf("文件中无上机卡消费记录！");
			return Error;
		}
		else
		{
			printf("money文件读取失败,");
			return Error;
		}

	}

	Charge show1;
	Pay show2;
	show1 = *phead;
	show2 = *Start;

	
	printf("bill文件中共有%d条消费记录\n", CheckBillnumber(phead, num));
	if (CheckBillnumber(phead, num))
	{
		printf("消费账单如下：\n");
		for (show1; show1 != NULL; show1 = show1->next)
		{
			if (strcmp(num, show1->data.aCardName)==0)
				Printbill(show1);
		}
	}

		printf("money文件中共有%d条消费记录\n", CheckMoneynumber(Start, num));
	if (CheckMoneynumber(Start, num))
	{
		printf("充值退费账单如下：\n");
		for (show2; show2 != NULL; show2 = show2->next)
		{
			if (strcmp(num, show2->data.Name)==0)
				Putmoney(*show2);
		}

	}
	return OK;
}
//检测bill文件中同名卡号信息数
int CheckBillnumber(Charge* phead, const char* name)
{
	Charge cur;
	cur = *phead;
	int num = 0;
	for (cur; cur != NULL; cur = cur->next)
	{
		if (strcmp(cur->data.aCardName, name) == 0)//满足信息卡号相同
			num++;
	}
	return num;
}
//检测money文件中同名卡号信息数
int CheckMoneynumber(Pay* Start, const char* name)
{
Pay cur;
cur = *Start;
int num = 0;
for (cur; cur != NULL; cur = cur->next)
{
	if (strcmp(cur->data.Name, name) == 0)//满足信息卡号相同
		num++;
}
return num;

}

// 显示卡信息
void ShowCARD(CardNode card)
{
	
	char t1[20];
	char t3[20];
	timeToString(card.data.tStart, t1);
	timeToString(card.data.tLastT, t3);
	// 输出表格的表头
	printf("卡号\t状态\t余额  累计使用\t使用次数    上次使用时间\t\t开卡时间   删除标识\n");
	printf("%s\t%d\t%0.1f\t%0.1f\t  %d\t  %s\t%s   %d\n", card.data.name, card.data.status, card.data.fleft,
		card.data.fAlluse, card.data.Usecount, t3,t1,card.data.nDel);
}
void Printbill(Charge card)
{

	char t1[20];//上机时间
	char t2[20];//下机时间
	timeToString(card->data.tStart, t1);
	timeToString(card->data.tEnd, t2);
	// 输出表格的表头
	printf("卡号\t结算状态\t删除标识\t消费金额\t余额\t\t上机时间\t\t下机时间\n");
	printf("%s\t %d\t\t %d\t\t %0.1f\t\t%0.1f\t\t   %s\t%s\n", card->data.aCardName, card->data.nStatus, card->data.nDel, card->data.fAmount,card->data.left, t1, t2);
		
}
void Putmoney(Mnode temp)
{
	char t[20];//充值退费时间
	//char *sta;//保存充值退费状态
	//sta = new char;
	//if (temp.data.nStatus == 1)
		//strcpy(sta, "充值");
	//else
		//strcpy(sta, "退费");
	timeToString(temp.data.tTime, t);
	// 输出表格的表头
	
	printf("卡号\t状态\t删除标识  金额  余额\t  操作时间\n");
	printf("%s\t%d\t %d\t%0.2f\t%0.2f\t%s\n", temp.data.Name, temp.data.nStatus,temp.data.nDel, temp.data.fAmount, temp.data.left, t);
	//delete sta;
}
void Putcold(Block card)
{
	char t1[20];//冻结时间
	char t2[20];//激活时间
	timeToString(card->data.clod_time, t1);
	timeToString(card->data.act_time, t2);
	// 输出表格的表头
	printf("卡号\t冻结标识\t冻结时间\t\t激活时间\n");
	printf("%s\t %d\t %s\t\t%s\n", card->data.coldName, card->data.coldStatus, t1, t2);

}

