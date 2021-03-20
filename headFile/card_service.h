# define _CRT_SECURE_NO_WARNINGS
#ifndef CARD_SERVICE_H
#define CARD_SERVICE_H

#include "model.h"
#include<string.h>
#include<stdio.h>
#include <stdlib.h>
#include"tool.h"
#include"gloabl.h"

//�ļ��в�������
int Check_user(const char* card_name, const char* pPath);////����ļ��п��źϷ��ԣ��Ƿ��Ѵ����ļ���δע����δ����)����1�������
int CardCount(const char* pPath);//����file����Ϣ����
int exitCardCount(const char* pPath);//����file����ע��������
int Billcount(const char* pPath);//����bill���Ѽ�¼����
int Moneycount(const char* pPath);//����money���Ѽ�¼����
int Coldcount(const char* pPath);//����cold���Ѽ�¼
int Check_key(List *phead, const char* name, const char* key);//��֤����������ȷ��

//��ʾ�ļ��е�������Ϣ
void ShowCARD(CardNode card);
void Printbill(Charge card);
void Putmoney(Mnode temp);
void Putcold(Block card);

//��ѯ��������¿�
int newadd(const char*num,const char *pPath);//����¿�
int Queryfile(CardNode card, const char* pPath);//��ѯ��������¿�д��file�ļ�

//�ϻ�
int Fileupdate(List *phead, const char *pPath, const char *name);//�ϻ�file�ļ�����
void Savelogon(List *phead, const char *pPath, const char *name);//���沢��ʾ�ϻ���Ϣ
int addBill(BillNode card,const char* pPath);//������Ѽ�¼

//�»�
int upbill(Charge* phead, const char* pPath, const char* name);//�»�����bill�ļ�
float getAmount(Charge *phead,const char*name);//�������ѽ��
int upfile(List* phead, Charge* head, const char* pPath, const char* name);//�»�����file�ļ�
void Put(Charge* phead, const char* name);//��ʾ�»�����Ϣ

//��ֵ���˷�
//����money�ļ�
int upChargeMoney(List* phead, const char* name, float money,const char *pPath);
int upReturnMoney(List* phead, const char* name, float money, const char* pPath);
int upExitMoney(const char* name, float money, const char* pPath);
float Exitmoney(List* phead, const char* name);//����ע�����˿���
//��ֵ�˷Ѹ���file�ļ�
float upMoneyfile(List* phead, const char* name, const char* pPath);
float upExitMoneyfile(List* phead, const char* name, const char* pPath);
//��ֵ�˷Ѹ���bill�ļ�
int upChargeMoneybill(Charge* phead, const char* name, const char* pPath, float money);
int upReturnMoneybill(Charge* phead, const char* name, const char* pPath, float money);

//��������
int Reset(List* phead, const char* pPath, const char *name,const char *newkey);

//����Աģʽ�ӹ��ܺ���
void Outadmin();//��ʾ����Ա�˵�
int Getin();//��¼����Ա�˺�
int Check_admin(const char *key);//������Ա����



int Frozencard();//���Ῠ
int Activecard(Block* phead, Block* pend);//���
int upFrozencold(Block card, const char* pPath);//���Ῠ����cold�ļ�
int upActivecold(Block* phead, const char* name, const char* pPath);//�������cold�ļ�����ʾ
int Check_Cold(const char* name, const char* pPath);//������Ῠʱ���cold�ļ����Ƿ���ڷ���������Ϣ(���ڷ���1��

int Querycard(Charge* phead, Charge* pend, Pay* Start, Pay* Last);//���ҿ��������˵�
int CheckBillnumber(Charge* phead, const char* name);//���bill�ļ���ͬ��������Ϣ��
int CheckMoneynumber(Pay* Start, const char* name);//���money�ļ���ͬ��������Ϣ��

#endif;
