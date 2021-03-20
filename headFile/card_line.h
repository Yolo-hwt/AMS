# define _CRT_SECURE_NO_WARNINGS
#ifndef CARD_LINE_H
#define CARD_LINE_H
#include"model.h"
#include"card_service.h"

//添加卡时显示子菜单
void output();

/*链表中操作函数*/
//删除链表
int aDel(List* phead);
int aDel(Charge* phead);
int aDel(Pay* phead);
int aDel(Block* phead);

//检查链表中卡号的合法性
int Check_line(List* phead, const char* card_name);
int Check_line(Charge* phead, const char* card_name);
int Check_line(Pay* phead, const char* card_name);

//计算存于链表中的卡数量
int Count_line(List* phead);
int Count_line(Charge* phead);
int Count_line(Pay* phead);
int Count_line(Block* phead);

//读取文件信息生成链表
int getLine(List *phead, List *pend,const char* pPath);//file文件中读取计费信息生成链表
int getLine(Charge* phead, Charge* pend, const char* pPath);//bill文件中读取计费信息生成链表
int getLine(Pay* phead, Pay* pend, const char* pPath);//money文件中读取费信息生成链表
int getLine(Block* phead, Block* pend, const char* pPath);//cold文件中读取费信息生成链表


/*添加卡链表*/
int Linefile(List* phead, const char* pPath);//将链表中卡信息写入文件
int Show(List p);//显示单个链表数据
int Delete(List* phead);//链表指定删除
int Find(List* phead);//查找输出指定链表数据
int showAll(List* phead);//显示所有链表数据

/*上机卡信息链表中函数*/
int dologon(List *phead,const char *name);//检测上机状态
int Linkupdate(List *phead,const char *name);//上机链表更新

/*下机卡信息链表中函数*/
int dosettle(Charge *phead,List *head, const char* name);//检测下机机状态
int Linkupdate(Charge* phead, const char* name);//更新下机链表

/*充值退费*/
int upRechargeline(List* phead, const char* name,float money);//更新充值卡链表
int upReturnline(List* phead, const char* name, float money);//更新退费链表
int upExitline(List* phead, const char* name);//更新下机链表
#endif;