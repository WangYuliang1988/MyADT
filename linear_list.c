#include "linear_list.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// ����˳����������
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void InitSeqList(SeqList* p_seq)
{
	p_seq->elem = (ElemType*)malloc(INIT_SIZE * sizeof(ElemType));
	if (p_seq == NULL)
	{
		printf("Error: -- InitSeqList -- fail to alloc memory.\n");
		exit(EXIT_FAILURE);
	}
	p_seq->length = 0;
	p_seq->list_size = INIT_SIZE;
}

void InsertSeqElem(SeqList* p_seq, int i, ElemType elem)
{
	// �жϲ���λ�� i �Ƿ�Ϸ���������ɺ�Ԫ��֮����뱣������
	// �Ϸ���Χ��0 <= i <= length��ע��Ԫ��λ�������� 0 ��ʼ
	if (i < 0 || i > p_seq->length)
	{
		printf("Error: -- InsertSeqElem -- %d is an invalid index.\n", i);
		exit(EXIT_FAILURE);
	}
	
	// �жϵ�ǰ˳����Ƿ����������ǣ�����չ˳�����ռ�ռ�
	if (p_seq->length == p_seq->list_size)
	{
		ElemType* nbase = (ElemType*)realloc(p_seq->elem, (p_seq->list_size + INCREMENT_SIZE) * sizeof(ElemType));
		if (nbase != NULL)
		{
			p_seq->elem = nbase; // �����һ��Ԫ�ص�ַ������չ�ռ���ַ���ܸı�
			p_seq->list_size += INCREMENT_SIZE; // ����˳�������ɵ�Ԫ�ظ���
		}
		else
		{
			printf("Error: -- InsertSeqElem -- fail to alloc memory.\n");
			exit(EXIT_FAILURE);
		}
	}

	// β��Ԫ����λ�� i Ԫ���������ƣ�Ȼ����Ԫ�ز���λ�� i������ length �� 1
	for (int k = p_seq->length - 1; k >= i; k--)
	{
		p_seq->elem[k + 1] = p_seq->elem[k];
	}
	p_seq->elem[i] = elem;
	p_seq->length++;
}

void DeleteSeqElem(SeqList* p_seq, int i)
{
	// �ж�ɾ��λ���Ƿ�Ϸ�
	if (i < 0 || i > p_seq->length - 1)
	{
		printf("Error: -- DeleteSeqElem -- %d is out of index.\n", i);
		exit(EXIT_FAILURE);
	}

	// λ�� i + 1 Ԫ����β��Ԫ���������ƣ����� length �� 1��ʵ��ɾ��
	for (int k = i + 1; k < p_seq->length; k++)
	{
		p_seq->elem[k - 1] = p_seq->elem[k];
	}
	p_seq->length--;
}

ElemType GetSeqElem(SeqList seq, int i)
{
	if (i < 0 || i >= seq.length)
	{
		printf("Error: -- GetSeqElem -- %d is out of index.\n", i);
		exit(EXIT_FAILURE);
	}
	return seq.elem[i];
}

ElemType GetSeqElemPre(SeqList seq, ElemType cur_e)
{
	for (int i = 0; i < seq.length; i++)
	{
		if (seq.elem[i] == cur_e)
		{
			if (i == 0)
			{
				printf("Error: -- GetSeqElemPre -- %d is already the first element.\n", cur_e);
				exit(EXIT_FAILURE); // ��һ��Ԫ��û��ǰ��
			}
			else
			{
				return seq.elem[i - 1];
			}
		}
	}
	printf("Error: -- GetSeqElemPre -- %d is not in the list.\n", cur_e);
	exit(EXIT_FAILURE);
}

ElemType GetSeqElemNext(SeqList seq, ElemType cur_e)
{
	for (int i = 0; i < seq.length; i++)
	{
		if (seq.elem[i] == cur_e)
		{
			if (i == seq.length - 1)
			{
				printf("Error: -- GetSeqElemNext -- %d is already the last element.\n", cur_e);
				exit(EXIT_FAILURE); // ���һ��Ԫ��û�к��
			}
			else
			{
				return seq.elem[i + 1];
			}
		}
	}
	printf("Error: -- GetSeqElemNext -- %d is not in the list.\n", cur_e);
	exit(EXIT_FAILURE);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// ���嵥�����������
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void InitLinkList(LinkList* p_list)
{
	// ������ĳ�ʼ������ʼ��ͷ����ͷָ��
	// ע��ͷ�������Ϊ���ӵĽ�㣬����������Բ��洢���ݣ���ָ����ָ����Ԫ�ؽ��
	// �������ʼ��ʱ����δ����κ���Ԫ�أ���������ͷ����ָ����ָ�� NULL
	
	// ��ʼ��ͷ���
	LNode* p_head = (LNode*)malloc(sizeof(LNode)); // �˴���ʹ�� LNode head ��ʽ������Ϊ�÷�ʽ������Ǿֲ������������������溯���Ľ���������
	if (p_head == NULL)
	{
		printf("Error: -- InitLinkList -- fail to alloc memory.\n");
		exit(EXIT_FAILURE);
	}
	p_head->elem = -1; // ͷ���������Ĵ洢���ݲ���Ҫ��
	p_head->next = NULL; // ͷ���ָ����ָ����Ԫ�ؽ�㣬���ʱ�������л�û��Ԫ�أ�����Ϊ NULL

	// ��ͷָ��ָ��ͷ���
	*p_list = p_head; // p_list ��ָ��ͷ���ָ���ָ�룬*p_list ��ָ��ͷ����ָ��
}

void InsertLinkElem(LinkList* p_list, int i, ElemType elem)
{
	// ��λ�� i ����Ԫ�أ��ؼ������ҵ�λ�� i-1 �Ľ��
	// Ȼ�������ڴ棬����һ���½�㣬��Ϊ������ֵ
	// ���ţ����½���ָ����ָ��λ�� i-1 ���ָ����ָ��Ľ��
	// ��󣬽�λ�� i-1 ���ָ����ָ���½�㣬��ɲ������

	if (i < 0)
	{
		printf("Error: -- InsertLinkElem -- %d is an invalid index.\n", i);
		exit(EXIT_FAILURE);
	}

	// �洢λ�� i-1 ���ı��������ʼֵΪͷ���
	LNode* p_pre = *p_list;

	// Ѱ��λ�� i-1 �Ľ��
	int k = 0;
	while (k < i && p_pre != NULL) // ���� p_pre != NULL����Ϊ�� p_pre Ϊ NULL ʱ����β����λ���� k-1���� k �����ֵ�� i-1����β���λ�����ֵΪ i-2���Ӷ�������λ�� i-1 �Ľ��
	{
		p_pre = p_pre->next;
		k++;
	}

	// δ�ҵ�λ�� i-1 ��㣬˵�� i Ϊ��Ч����
	if (p_pre == NULL)
	{
		printf("Error: -- InsertLinkElem -- %d is an invalid index.\n", i);
		exit(EXIT_FAILURE);
	}

	// �����½�㲢Ϊ������ֵ
	LNode* p_newd = (LNode*)malloc(sizeof(LNode));
	if (p_newd == NULL)
	{
		printf("Error: -- InsertLinkElem -- fail to alloc memory.\n");
		exit(EXIT_FAILURE);
	}
	p_newd->elem = elem;

	// �ı�ָ����ָ��
	p_newd->next = p_pre->next;
	p_pre->next = p_newd;
}

void DeleteLinkElem(LinkList* p_list, int i)
{
	// ɾ��λ�� i ��Ԫ�أ��ؼ������ҵ�λ�� i-1 �Ľ��
	// Ȼ�󣬽�λ�� i-1 ����ָ����ָ��λ�� i ���ָ����ָ��Ľ��
	// ����ͷ�λ�� i �����ڴ棬���ɾ������

	if (i < 0)
	{
		printf("Error: -- DeleteLinkElem -- %d is out of index.\n", i);
		exit(EXIT_FAILURE);
	}

	// �洢λ�� i-1 ���ı�������ʼֵΪͷ���
	LNode* p_pre = *p_list;
	
	// �������޷�����ɾ������
	if (p_pre->next == NULL)
	{
		printf("Error: -- DeleteLinkElem -- LinkList is empty.\n");
		exit(EXIT_FAILURE);
	}

	// Ѱ��λ�� i-1 �Ľ��
	int k = 0;
	while (k < i && p_pre != NULL)
	{
		p_pre = p_pre->next;
		k++;
	}

	// δ�ҵ�λ�� i-1 ��㣬����λ�� i-1 �����β��㣬˵�� i Ϊ��Ч����
	if (p_pre == NULL || p_pre->next == NULL)
	{
		printf("Error: -- DeleteLinkElem -- %d is out of index.\n", i);
		exit(EXIT_FAILURE);
	}

	// ����ָ��������ڴ��ͷ�
	LNode* p_cur = p_pre->next;
	p_pre->next = p_cur->next;
	p_cur->next = NULL;
	free(p_cur);
}

void ReverseLinkList(LinkList* p_list)
{
	// ���������Ƚ�����ͷ���ͬ��һ���������ӶϿ�
	// Ȼ��ӵ�һ����㿪ʼ�����ν�����������ͷ�����������

	// ͷ���
	LNode* p_head = *p_list;
	
	// ��������������
	if (p_head->next == NULL) return;
	
	// ��ʼ����ر������Ͽ�ͷ������һ����������
	LNode* p_pre = NULL;
	LNode* p_cur = p_head->next;
	p_head->next = NULL;
	LNode* p_next = p_cur->next;

	// �ƶ�ָ�룬ʼ����ͷ������
	while (p_cur != NULL)
	{
		// ��ͷ���ָ����ָ��ǰ��㣬����ǰ���ָ����ָ��ǰһ����㣬ʵ��ͷ������
		p_head->next = p_cur;
		p_cur->next = p_pre;
		// ����ǰ�����Ϊǰһ����㣬��һ�������Ϊ��ǰ��㣬�������Ϊ��һ����㣨���ж��Ƿ���ں���㣩
		p_pre = p_cur;
		p_cur = p_next;
		if (p_next != NULL)
		{
			p_next = p_next->next;
		}
	}
}

int GetLinkLength(LinkList list)
{
	int len = 0;
	while (list->next != NULL)
	{
		list = list->next;
		len++;
	}
	return len;
}

ElemType GetLinkElem(LinkList list, int i)
{
	if (i < 0)
	{
		printf("Error: -- GetLinkElem -- %d is out of index.\n", i);
		exit(EXIT_FAILURE);
	}

	// �洢λ�� i ���ı�������ʼλ��Ϊͷ���
	LNode* p_cur = list;

	// Ѱ��λ�� i �Ľ��
	int k = 0;
	while (k <= i && p_cur != NULL) // ���� p_cur != NULL����Ϊ�� p_cur Ϊ NULL ʱ����β����λ���� k-1���� k �����ֵ�� i����β���λ�����ֵΪ i-1���Ӷ�������λ�� i �Ľ��
	{
		p_cur = p_cur->next;
		k++;
	}

	// δ�ҵ�λ�� i ��㣬˵�� i Ϊ��Ч����
	if (p_cur == NULL)
	{
		printf("Error: -- GetLinkElem -- %d is out of index.\n", i);
		exit(EXIT_FAILURE);
	}
	
	// ����Ԫ��
	return p_cur->elem;
}
