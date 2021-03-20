
#include"card_line.h"

//删除链表中所有卡信息
int aDel(List* phead)
{
	List del = *phead;//指向待删除节点	
	List p=NULL;//记录下一节点
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

	if ((!del) && (!(*phead)))//确保循环至链表末尾	
	{
		
		return OK;
	}

	else
		printf("Error!\n");

	return Error;

}
int aDel(Charge* phead)
{
	Charge del = *phead;//指向待删除节点	
	Charge p = NULL;//记录下一节点
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

	if ((!del) && (!(*phead)))//确保循环至链表末尾	
	{

		return OK;
	}

	else
		printf("Error!\n");

	return Error;

}
int aDel(Pay* phead)
{
	Pay del = *phead;//指向待删除节点	
	Pay p = NULL;//记录下一节点
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

	if ((!del) && (!(*phead)))//确保循环至链表末尾	
	{

		return OK;
	}

	else
		printf("Error!\n");

	return Error;
}
int aDel(Block* phead)
{
	Block del = *phead;//指向待删除节点	
	Block p = NULL;//记录下一节点
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

	if ((!del) && (!(*phead)))//确保循环至链表末尾	
	{

		return OK;
	}

	else
		printf("Error!\n");

	return Error;
}
//检查链表中输入合法性
int Check_line(List* phead, const char* card_name)
{
	//返回值为0则链表中没有相同卡号
	List f;
	f = *phead;
	if (*phead == NULL)
		return Error;
	while (f != NULL)
	{
		if ((strcmp(f->data.name, card_name) == 0)&&(f->data.nDel==0))//卡号匹配且未注销
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
	//返回值为0则链表中没有相同卡号
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
	//返回值为0则链表中没有相同卡号
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

//计算链表中卡数量
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

//从文件中读取计费信息生成	链表
int getLine(List *phead, List* pend,const char* pPath)
{	
	//置空链表
	aDel(phead);
	*phead = NULL;
	*pend = NULL;

	if (CardCount(pPath) == 0)
	{
		return Error;
	}
	FILE* fp = NULL;  // 文件结构体指针
	List file;//储存文件内容
	// 以只读方式打开文件，如果打开失败，则读取失败
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("文件打开失败！\n");
		return Error;
	}
	fseek(fp, 0, SEEK_SET);// 定位至文件的开头
	// 读取文件内容
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
	// 关闭文件
	fclose(fp);
	if ((*pend)->next == NULL)
	{
		return OK;
	}

return Error;		
}
int getLine(Charge* phead, Charge* pend, const char* pPath)
{
	//置空链表
		aDel(phead);
	*phead = NULL;
	*pend = NULL;

	if (Billcount(pPath)==0)
	{
		return Error;
	}

	FILE* fp = NULL;  // 文件结构体指针
	Charge file;//储存文件内容
	// 以只读方式打开文件，如果打开失败，则读取失败
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("文件打开失败！\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);// 定位至文件的开头
	// 读取文件内容
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
	// 关闭文件
	fclose(fp);
	if ((*pend)->next == NULL)
	{
		return OK;
	}

	return Error;
}
int getLine(Pay* phead, Pay* pend, const char* pPath)
{
	// 置空链表
		aDel(phead);
	*phead = NULL;
	*pend = NULL;

	if (Billcount(pPath) == 0)
	{
		return Error;
	}

	FILE* fp = NULL;  // 文件结构体指针
	Pay file;//储存文件内容
	// 以只读方式打开文件，如果打开失败，则读取失败
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("文件打开失败！\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);// 定位至文件的开头
	// 读取文件内容
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
	// 关闭文件
	fclose(fp);
	if ((*pend)->next == NULL)
	{
		return OK;
	}

	return Error;
}
int getLine(Block* phead, Block* pend, const char* pPath)
{
	// 置空链表
	aDel(phead);
	*phead = NULL;
	*pend = NULL;

	if (Coldcount(pPath) == 0)
	{
		return Error;
	}

	FILE* fp = NULL;  // 文件结构体指针
	Block file;//储存文件内容
	// 以只读方式打开文件，如果打开失败，则读取失败
	if ((fp = fopen(pPath, "rb")) == NULL)
	{
		printf("文件打开失败！\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_SET);// 定位至文件的开头
	// 读取文件内容
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
	// 关闭文件
	fclose(fp);
	if ((*pend)->next == NULL)
	{
		return OK;
	}

	return Error;
}




