#include "linear_list.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 定义顺序表基本操作
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
	// 判断插入位置 i 是否合法，插入完成后元素之间必须保持连续
	// 合法范围：0 <= i <= length，注意元素位置索引从 0 开始
	if (i < 0 || i > p_seq->length)
	{
		printf("Error: -- InsertSeqElem -- %d is an invalid index.\n", i);
		exit(EXIT_FAILURE);
	}
	
	// 判断当前顺序表是否已满，若是，则扩展顺序表所占空间
	if (p_seq->length == p_seq->list_size)
	{
		ElemType* nbase = (ElemType*)realloc(p_seq->elem, (p_seq->list_size + INCREMENT_SIZE) * sizeof(ElemType));
		if (nbase != NULL)
		{
			p_seq->elem = nbase; // 重设第一个元素地址，因扩展空间后地址可能改变
			p_seq->list_size += INCREMENT_SIZE; // 更新顺序表可容纳的元素个数
		}
		else
		{
			printf("Error: -- InsertSeqElem -- fail to alloc memory.\n");
			exit(EXIT_FAILURE);
		}
	}

	// 尾部元素至位置 i 元素依次下移，然后将新元素插入位置 i，并将 length 加 1
	for (int k = p_seq->length - 1; k >= i; k--)
	{
		p_seq->elem[k + 1] = p_seq->elem[k];
	}
	p_seq->elem[i] = elem;
	p_seq->length++;
}

void DeleteSeqElem(SeqList* p_seq, int i)
{
	// 判断删除位置是否合法
	if (i < 0 || i > p_seq->length - 1)
	{
		printf("Error: -- DeleteSeqElem -- %d is out of index.\n", i);
		exit(EXIT_FAILURE);
	}

	// 位置 i + 1 元素至尾部元素依次上移，并将 length 减 1，实现删除
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
				exit(EXIT_FAILURE); // 第一个元素没有前驱
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
				exit(EXIT_FAILURE); // 最后一个元素没有后继
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
// 定义单链表基本操作
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void InitLinkList(LinkList* p_list)
{
	// 单链表的初始化即初始化头结点和头指针
	// 注意头结点是人为附加的结点，其数据域可以不存储内容，其指针域指向首元素结点
	// 单链表初始化时，还未添加任何首元素，所以设置头结点的指针域指向 NULL
	
	// 初始化头结点
	LNode* p_head = (LNode*)malloc(sizeof(LNode)); // 此处不使用 LNode head 方式，是因为该方式定义的是局部变量，其生命周期随函数的结束而结束
	if (p_head == NULL)
	{
		printf("Error: -- InitLinkList -- fail to alloc memory.\n");
		exit(EXIT_FAILURE);
	}
	p_head->elem = -1; // 头结点数据域的存储内容不做要求
	p_head->next = NULL; // 头结点指针域指向首元素结点，因此时单链表中还没有元素，故设为 NULL

	// 将头指针指向头结点
	*p_list = p_head; // p_list 是指向头结点指针的指针，*p_list 是指向头结点的指针
}

void InsertLinkElem(LinkList* p_list, int i, ElemType elem)
{
	// 向位置 i 插入元素，关键在于找到位置 i-1 的结点
	// 然后，申请内存，定义一个新结点，并为数据域赋值
	// 接着，将新结点的指针域，指向位置 i-1 结点指针域指向的结点
	// 最后，将位置 i-1 结点指针域指向新结点，完成插入操作

	if (i < 0)
	{
		printf("Error: -- InsertLinkElem -- %d is an invalid index.\n", i);
		exit(EXIT_FAILURE);
	}

	// 存储位置 i-1 结点的变量，其初始值为头结点
	LNode* p_pre = *p_list;

	// 寻找位置 i-1 的结点
	int k = 0;
	while (k < i && p_pre != NULL) // 限制 p_pre != NULL，因为当 p_pre 为 NULL 时，则尾结点的位置是 k-1，而 k 的最大值是 i-1，则尾结点位置最大值为 i-2，从而不存在位置 i-1 的结点
	{
		p_pre = p_pre->next;
		k++;
	}

	// 未找到位置 i-1 结点，说明 i 为无效索引
	if (p_pre == NULL)
	{
		printf("Error: -- InsertLinkElem -- %d is an invalid index.\n", i);
		exit(EXIT_FAILURE);
	}

	// 定义新结点并为数据域赋值
	LNode* p_newd = (LNode*)malloc(sizeof(LNode));
	if (p_newd == NULL)
	{
		printf("Error: -- InsertLinkElem -- fail to alloc memory.\n");
		exit(EXIT_FAILURE);
	}
	p_newd->elem = elem;

	// 改变指针域指向
	p_newd->next = p_pre->next;
	p_pre->next = p_newd;
}

void DeleteLinkElem(LinkList* p_list, int i)
{
	// 删除位置 i 的元素，关键在于找到位置 i-1 的结点
	// 然后，将位置 i-1 结点的指针域，指向位置 i 结点指针域指向的结点
	// 最后，释放位置 i 结点的内存，完成删除操作

	if (i < 0)
	{
		printf("Error: -- DeleteLinkElem -- %d is out of index.\n", i);
		exit(EXIT_FAILURE);
	}

	// 存储位置 i-1 结点的变量，初始值为头结点
	LNode* p_pre = *p_list;
	
	// 空链表，无法进行删除操作
	if (p_pre->next == NULL)
	{
		printf("Error: -- DeleteLinkElem -- LinkList is empty.\n");
		exit(EXIT_FAILURE);
	}

	// 寻找位置 i-1 的结点
	int k = 0;
	while (k < i && p_pre != NULL)
	{
		p_pre = p_pre->next;
		k++;
	}

	// 未找到位置 i-1 结点，或者位置 i-1 结点是尾结点，说明 i 为无效索引
	if (p_pre == NULL || p_pre->next == NULL)
	{
		printf("Error: -- DeleteLinkElem -- %d is out of index.\n", i);
		exit(EXIT_FAILURE);
	}

	// 进行指针操作及内存释放
	LNode* p_cur = p_pre->next;
	p_pre->next = p_cur->next;
	p_cur->next = NULL;
	free(p_cur);
}

void ReverseLinkList(LinkList* p_list)
{
	// 逆置链表，先将链表头结点同第一个结点的链接断开
	// 然后从第一个结点开始，依次将结点插入链表头部，完成逆置

	// 头结点
	LNode* p_head = *p_list;
	
	// 空链表无需逆置
	if (p_head->next == NULL) return;
	
	// 初始化相关变量并断开头结点与第一个结点的链接
	LNode* p_pre = NULL;
	LNode* p_cur = p_head->next;
	p_head->next = NULL;
	LNode* p_next = p_cur->next;

	// 移动指针，始终在头部插入
	while (p_cur != NULL)
	{
		// 将头结点指针域指向当前结点，将当前结点指针域指向前一个结点，实现头部插入
		p_head->next = p_cur;
		p_cur->next = p_pre;
		// 将当前结点设为前一个结点，后一个结点设为当前结点，后后结点设为后一个结点（需判断是否存在后后结点）
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

	// 存储位置 i 结点的变量，初始位置为头结点
	LNode* p_cur = list;

	// 寻找位置 i 的结点
	int k = 0;
	while (k <= i && p_cur != NULL) // 限制 p_cur != NULL，因为当 p_cur 为 NULL 时，则尾结点的位置是 k-1，而 k 的最大值是 i，则尾结点位置最大值为 i-1，从而不存在位置 i 的结点
	{
		p_cur = p_cur->next;
		k++;
	}

	// 未找到位置 i 结点，说明 i 为无效索引
	if (p_cur == NULL)
	{
		printf("Error: -- GetLinkElem -- %d is out of index.\n", i);
		exit(EXIT_FAILURE);
	}
	
	// 返回元素
	return p_cur->elem;
}
