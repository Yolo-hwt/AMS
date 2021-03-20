#include"card_line.h"

/*显示添加卡子菜单*/
void output()
{
	printf("_____________MENU____________\n");
	printf("1.继续添加卡\n");
	printf("2.查询现有待添加卡\n");
	printf("3.显示所有待添加卡\n");
	printf("4.删除卡\n");
	printf("5.删除所有卡\n");
	printf("0.退出\n");
	printf("请选择功能————（0~4）\n\n");
}

/*写入链表中新卡信息至文件*/
int Linefile(List* phead, const char* pPath)
{
	FILE* fp = NULL;   // 文件结构体指针
	CardNode *pwrite=NULL;
	pwrite = *phead;
// 以追加的模式打开文件，如果打开失败，则以只写的模式打开文件
	if ((fp = fopen(pPath, "ab")) == NULL)
	{
		if ((fp = fopen(pPath, "wb")) == NULL)
		{
			printf("打开文件失败\n");
			return Error;

		}
			
	}
	if ((pwrite == NULL)||(*phead == NULL))
	{
	printf("没有卡信息可供写入\n");
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

//查找指定链表信息并输出
int Find(List* phead)
{
	List pcur1;
	pcur1 = *phead;
	char card_name[18];//存放查询卡号
	if (*phead == NULL) 
	{
	printf("无卡数据！\n");
	return Error;
	}
		
	else
	{
		printf("请输入你要查询的卡号：\n");
		scanf("%s", card_name);

		if (Check_line(phead, card_name))//返回1则链表中存在此卡号
		{
			printf("卡号%s信息如下：\n",card_name);
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
		printf("没有相关卡信息！\n");
		return Error;
		}
			
	}

	return OK;
}

//删除指定链表中卡信息
int Delete(List* phead)
{
	List pcur1 = *phead;
	List pdel = NULL;
	char card_name[18];//存放待删除卡号

	printf("请输入你要删除的卡号：\n");
	scanf_s("%s", card_name, sizeof(card_name));
	if (Check_line(phead, card_name))//返回1，则链表中卡号存在
	{
		if ((strcmp(pcur1->data.name, card_name) == 0) && (Count_line(phead) == 1))//待删除卡为第一个节点且仅有一个节点
		{
			free(pcur1);
			*phead = NULL;
			printf("卡号：%s 已删除！\n", card_name);
			return OK;

			//if (*phead == NULL) 
			//{
			//	printf("仅有一节点情况头结点删除，且头指针置空！\n");
			//}


		}
		else if ((strcmp(pcur1->data.name, card_name)) == 0 && (Count_line(phead) > 1))//若第一个节点即为待删除卡,且不止一个节点
		{
			pdel = *phead;
			*phead = pcur1->next;//头指针后移一位	
			pcur1 = *phead;
			free(pdel);//释放节点内存			
			pdel = NULL;
			printf("卡号：%s 已删除！\n", card_name);
			return OK;

			//if (*phead != NULL) {
			//	printf("多节点情况头结点删除，头指针已重定位，phead->name=%s\n", pcur1->data.name);
			//}
		}
		else
		{
			for (pcur1; pcur1 != NULL; pcur1 = pcur1->next)//非头结点删除
			{
				if ((strcmp(pcur1->next->data.name, card_name) == 0) && (pcur1 != NULL))//遍历查找卡
				{
					pdel = pcur1->next;//定位待删除节点
					pcur1->next = pdel->next;
					free(pdel);
					pdel = NULL;
					printf("卡号：%s 已删除！\n", card_name);
					return OK;

					//if (*phead != NULL) {
					//	printf("非头节点删除，删除节点后phead->name=%s\n", (*phead)->data.name);
					//}
					

				}
			}
		}
	}
	else
	{
	printf("未查询到待删除卡信息\n");
	return Error;
	}
	return OK;
}

//显示单个链表数据
int Show(List p1)
{
	char t1[20];
	char t2[20];
	//将时间转换为字符串形式
	timeToString(p1->data.tStart, t1);
	timeToString(p1->data.tLastT, t2);
	printf("\t\t\t*****查询到相关卡信息如下*****\n");
	printf("卡号\t状态\t余额  累计使用\t使用次数\t上次使用时间\t\t开卡时间\n");
	printf("%s\t%d\t%.1f\t\t%.1f\t%d\t%s\t%s\n", p1->data.name, p1->data.status, p1->data.fleft, p1->data.fAlluse, p1->data.Usecount, t2, t1);
	return OK;
}

//显示所有链表数据
int showAll(List* phead)
{
	if (*phead == NULL)
	{
		printf("无卡信息！\n");
		return Error;
	}
	else
	{
		List show = NULL;
		char t1[20];//存放开卡时间
		char t2[20];//存放上次使用时间

		printf("现有卡数量：%d\n", Count_line(phead));
		printf("\t\t\t*****所有卡信息如下*****\n");
		printf("卡号\t状态\t余额  累计使用\t使用次数\t上次使用时间\t\t开卡时间\n");
		for (show = *phead; show != NULL; show = show->next)
		{
			//将时间转换为字符串形式
			timeToString(show->data.tStart, t1);
			timeToString(show->data.tLastT, t2);

			printf("%s\t%d\t%.1f\t%.1f\t%d\t%s\t%s\n", show->data.name, show->data.status, show->data.fleft, show->data.fAlluse,show->data.Usecount,t2,t1 );
		}
	}

	return OK;
}

