# define _CRT_SECURE_NO_WARNINGS
#ifndef CARD_SERVICE_H
#define CARD_SERVICE_H

#include "model.h"
#include<string.h>
#include<stdio.h>
#include <stdlib.h>
#include"tool.h"
#include"gloabl.h"

//文件中操作函数
int Check_user(const char* card_name, const char* pPath);////检查文件中卡号合法性（是否已存在文件中未注销且未冻结)返回1，则符合
int CardCount(const char* pPath);//计算file卡信息数量
int exitCardCount(const char* pPath);//计算file中已注销卡数量
int Billcount(const char* pPath);//计算bill消费记录数量
int Moneycount(const char* pPath);//计算money消费记录数量
int Coldcount(const char* pPath);//计算cold消费记录
int Check_key(List *phead, const char* name, const char* key);//验证卡号密码正确性

//显示文件中单个卡信息
void ShowCARD(CardNode card);
void Printbill(Charge card);
void Putmoney(Mnode temp);
void Putcold(Block card);

//查询卡中添加新卡
int newadd(const char*num,const char *pPath);//添加新卡
int Queryfile(CardNode card, const char* pPath);//查询卡中添加新卡写入file文件

//上机
int Fileupdate(List *phead, const char *pPath, const char *name);//上机file文件更新
void Savelogon(List *phead, const char *pPath, const char *name);//保存并显示上机信息
int addBill(BillNode card,const char* pPath);//添加消费记录

//下机
int upbill(Charge* phead, const char* pPath, const char* name);//下机更新bill文件
float getAmount(Charge *phead,const char*name);//计算消费金额
int upfile(List* phead, Charge* head, const char* pPath, const char* name);//下机更新file文件
void Put(Charge* phead, const char* name);//显示下机卡信息

//充值，退费
//更新money文件
int upChargeMoney(List* phead, const char* name, float money,const char *pPath);
int upReturnMoney(List* phead, const char* name, float money, const char* pPath);
int upExitMoney(const char* name, float money, const char* pPath);
float Exitmoney(List* phead, const char* name);//返回注销卡退款金额
//充值退费更新file文件
float upMoneyfile(List* phead, const char* name, const char* pPath);
float upExitMoneyfile(List* phead, const char* name, const char* pPath);
//充值退费更新bill文件
int upChargeMoneybill(Charge* phead, const char* name, const char* pPath, float money);
int upReturnMoneybill(Charge* phead, const char* name, const char* pPath, float money);

//重置密码
int Reset(List* phead, const char* pPath, const char *name,const char *newkey);

//管理员模式子功能函数
void Outadmin();//显示管理员菜单
int Getin();//登录管理员账号
int Check_admin(const char *key);//检测管理员密码



int Frozencard();//冻结卡
int Activecard(Block* phead, Block* pend);//激活卡
int upFrozencold(Block card, const char* pPath);//冻结卡更新cold文件
int upActivecold(Block* phead, const char* name, const char* pPath);//激活卡更新cold文件并显示
int Check_Cold(const char* name, const char* pPath);//激活卡冻结卡时检测cold文件中是否存在符合条件信息(存在返回1）

int Querycard(Charge* phead, Charge* pend, Pay* Start, Pay* Last);//查找卡号消费账单
int CheckBillnumber(Charge* phead, const char* name);//检测bill文件中同名卡号信息数
int CheckMoneynumber(Pay* Start, const char* name);//检测money文件中同名卡号信息数

#endif;
