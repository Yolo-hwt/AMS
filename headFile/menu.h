#define _CRT_SECURE_NO_WARNINGS
#ifndef MENU_H
#define MENU_H

#include"card_service.h"
#include"card_line.h"
#include"gloabl.h"

void outputMenu();//����˵�
void query(const char *pPath);//��ѯ��
int Creat(List *phead, List *pend,const char *pPath);//��������(��ӿ�)
int Logon(List *phead, List *pend,const char *pPath);//�ϻ�
int settle(List *head, List *end, Charge *phead,Charge *pend);//�»�
int Recharge(List* phead,List *pend,Charge* head, Charge* end);//��ֵ
int Return(List* phead, List* pend, Charge* head, Charge* end);//�˷�
int ExitCard(List* phead,List *pend);//ע����
int Change(List* phead, List* pend);//�޸�����

int Admin(List* head, List* end, Charge* phead, Charge* pend, Pay* Start, Pay* Last, Block* chead, Block* cend);//����Աģʽ
void Showfile(const char*pPath);//��ʾfile�ļ������п���Ϣ
void Showbill(const char* pPath);//��ʾbill�ļ������Ѽ�¼
void Showmoney(const char* pPath);//��ʾmoney��ֵ�˷ѿ���Ϣ
void Showcold(const char* pPath);//��ʾcold����Ῠ��Ϣ

#endif;



