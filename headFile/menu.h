#define _CRT_SECURE_NO_WARNINGS
#ifndef MENU_H
#define MENU_H

#include"card_service.h"
#include"card_line.h"
#include"gloabl.h"

void outputMenu();//输出菜单
void query(const char *pPath);//查询卡
int Creat(List *phead, List *pend,const char *pPath);//单链表建立(添加卡)
int Logon(List *phead, List *pend,const char *pPath);//上机
int settle(List *head, List *end, Charge *phead,Charge *pend);//下机
int Recharge(List* phead,List *pend,Charge* head, Charge* end);//充值
int Return(List* phead, List* pend, Charge* head, Charge* end);//退费
int ExitCard(List* phead,List *pend);//注销卡
int Change(List* phead, List* pend);//修改密码

int Admin(List* head, List* end, Charge* phead, Charge* pend, Pay* Start, Pay* Last, Block* chead, Block* cend);//管理员模式
void Showfile(const char*pPath);//显示file文件中所有卡信息
void Showbill(const char* pPath);//显示bill文件中消费记录
void Showmoney(const char* pPath);//显示money充值退费卡信息
void Showcold(const char* pPath);//显示cold激活冻结卡信息

#endif;



