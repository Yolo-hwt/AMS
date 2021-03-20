#ifndef MODEL_H
#define MODEL_H
#include<time.h>

//���ṹ��
typedef struct CARD
{
	char name[18];//����
	char key[8];//����
	int status;//��״̬��0-δ�ϻ���1-�����ϻ���2����ע����3-��ʧЧ��
	time_t tStart;//����ʱ��
	time_t tEnd;//����ֹʱ��
	float fAlluse;//�ۼƽ��
	time_t tLastT;//���ʹ��ʱ��
	int Usecount;//ʹ�ô���
	float fleft;//�����
	int nDel;//ɾ����ʶ��0-δɾ����1-��ɾ����	
}CARD;

//���ڵ�
typedef struct CardNode
{	
	/*������*/
	CARD data;
	/*ָ����*/
	struct CardNode* next;

}CardNode,* List;//����List  (CardNode*)

// �ϻ��Ʒ���Ϣ�ṹ��
typedef struct Bill
{
	char aCardName[18];    // ����
	time_t tStart;         // �ϻ�ʱ��
	time_t tEnd;           // �»�ʱ��
	float fAmount;         // ���ѽ��
	float left;			   // ���
	int nStatus;           // ����״̬��0-δ���㣬1-�Ѿ�����
	int nDel;              // ɾ����ʶ��0-δɾ��,1-ɾ��
}Bill;

// �ϻ��Ʒ���Ϣ���
typedef struct BillNode
{
	Bill data;
	struct BillNode* next;
}BillNode, * Charge;//����Charge  (BillNode*)


//��ֵ�˷ѽṹ��
typedef struct Money
{
	char Name[18];			// ����
	time_t tTime;			// ��ֵ�˷�ʱ�� 
	float fAmount;         // ��ֵ�˷ѽ��
	float left;			   // ���
	int nStatus;           // ״̬��1-��ֵ��0-�˷�
	int nDel;              // ɾ����ʶ��0-δɾ��,1-ɾ��
}Money;
//��ֵ�˷���Ϣ�ڵ�
typedef struct Mnode
{
	Money data;
	struct Mnode* next;
}Mnode,* Pay;//����Pay  (Mnode*)

//���ἤ��ṹ��
typedef struct Frozen
{
	char coldName[8];
	time_t clod_time;//����ʱ��
	time_t act_time;//�ⶳʱ��
	int coldStatus;//�����ʶ��1���Ѷ��ᣬ0��δ���ᣩ
}Frozen;
//���ἤ��ڵ�
typedef struct BlockNode
{
	Frozen data;
	struct BlockNode* next;
}BlockNode, * Block;//����Block ��BlockNode*)

#endif;





