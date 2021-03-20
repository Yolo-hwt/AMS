# define _CRT_SECURE_NO_WARNINGS
#ifndef CARD_LINE_H
#define CARD_LINE_H
#include"model.h"
#include"card_service.h"

//��ӿ�ʱ��ʾ�Ӳ˵�
void output();

/*�����в�������*/
//ɾ������
int aDel(List* phead);
int aDel(Charge* phead);
int aDel(Pay* phead);
int aDel(Block* phead);

//��������п��ŵĺϷ���
int Check_line(List* phead, const char* card_name);
int Check_line(Charge* phead, const char* card_name);
int Check_line(Pay* phead, const char* card_name);

//������������еĿ�����
int Count_line(List* phead);
int Count_line(Charge* phead);
int Count_line(Pay* phead);
int Count_line(Block* phead);

//��ȡ�ļ���Ϣ��������
int getLine(List *phead, List *pend,const char* pPath);//file�ļ��ж�ȡ�Ʒ���Ϣ��������
int getLine(Charge* phead, Charge* pend, const char* pPath);//bill�ļ��ж�ȡ�Ʒ���Ϣ��������
int getLine(Pay* phead, Pay* pend, const char* pPath);//money�ļ��ж�ȡ����Ϣ��������
int getLine(Block* phead, Block* pend, const char* pPath);//cold�ļ��ж�ȡ����Ϣ��������


/*��ӿ�����*/
int Linefile(List* phead, const char* pPath);//�������п���Ϣд���ļ�
int Show(List p);//��ʾ������������
int Delete(List* phead);//����ָ��ɾ��
int Find(List* phead);//�������ָ����������
int showAll(List* phead);//��ʾ������������

/*�ϻ�����Ϣ�����к���*/
int dologon(List *phead,const char *name);//����ϻ�״̬
int Linkupdate(List *phead,const char *name);//�ϻ��������

/*�»�����Ϣ�����к���*/
int dosettle(Charge *phead,List *head, const char* name);//����»���״̬
int Linkupdate(Charge* phead, const char* name);//�����»�����

/*��ֵ�˷�*/
int upRechargeline(List* phead, const char* name,float money);//���³�ֵ������
int upReturnline(List* phead, const char* name, float money);//�����˷�����
int upExitline(List* phead, const char* name);//�����»�����
#endif;