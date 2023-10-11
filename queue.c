#include "queue.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 定义链队列基本操作
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void InitLinkQueue(LinkQueue* p_queue)
{
	QNode* p_head = (QNode*)malloc(sizeof(QNode));
	if (p_head == NULL)
	{
		printf("Error: -- InitLinkQueue -- fail to malloc memory.\n");
		exit(EXIT_FAILURE);
	}
	p_head->elem = -1;
	p_head->p_next = NULL;
	p_queue->p_front = p_queue->p_rear = p_head;
}

void EnLinkQueue(LinkQueue* p_queue, ElemType elem)
{
	// 队列只能在队尾插入元素
	// 首先，为待插入的元素结点分配内存空间
	// 然后，将旧队尾结点的 p_next 指向新建结点
	// 最后，将队尾指针的指向新建结点，完成插入

	QNode* p_newd = (QNode*)malloc(sizeof(QNode));
	if (p_newd == NULL)
	{
		printf("Error: -- EnLinkQueue -- fail to malloc memory.\n");
		exit(EXIT_FAILURE);
	}
	p_newd->elem = elem;
	p_newd->p_next = NULL;

	p_queue->p_rear->p_next = p_newd;
	p_queue->p_rear = p_newd;
}

void DeLinkQueue(LinkQueue* p_queue, ElemType* p_elem)
{
	// 队列只能在队首删除元素
	// 首先，使用临时变量保存首元素结点的地址
	// 然后，将头结点的 p_next 指向首元素结点的 p_next
	// 最后，释放首元素结点占用的内存空间，完成删除
	// 注意，若删除后头结点的 p_next 变为 NULL，即成为空队列，则需将队尾指针也指向头结点

	if (p_queue->p_front == p_queue->p_rear)
	{
		printf("Error: -- DeLinkQueue -- queue is empty.\n");
		exit(EXIT_FAILURE);
	}

	QNode* p_old = p_queue->p_front->p_next;
	p_queue->p_front->p_next = p_old->p_next;
	*p_elem = p_old->elem;
	free(p_old);

	if (p_queue->p_front->p_next == NULL)
	{
		p_queue->p_rear = p_queue->p_front;
	}
}

void DestroyLinkQueue(LinkQueue* p_queue)
{
	while (p_queue->p_front)
	{
		p_queue->p_rear = p_queue->p_front->p_next;
		free(p_queue->p_front);
		p_queue->p_front = p_queue->p_rear;
	}
}

void GetLinkQueueHead(LinkQueue queue, ElemType* p_elem)
{
	if (queue.p_front == queue.p_rear)
	{
		printf("Error: -- GetLinkQueueHead -- queue is empty.\n");
		exit(EXIT_FAILURE);
	}
	*p_elem = queue.p_front->p_next->elem;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 定义顺序队列基本操作
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void InitSeqQueue(SeqQueue* p_seq_queue)
{
	p_seq_queue->p_base = (ElemType*)malloc(sizeof(ElemType) * SEQ_INIT_SIZE);
	if (p_seq_queue->p_base == NULL)
	{
		printf("Error: -- InitSeqQueue -- fail to malloc memory.\n");
		exit(EXIT_FAILURE);
	}
	p_seq_queue->front = 0;
	p_seq_queue->rear = 0;
}

void EnSeqQueue(SeqQueue* p_seq_queue, ElemType elem)
{
	// 插入元素，先判断队列是否已满，是则报错（因为顺序队列是循环结构，无法动态扩展）
	// 队列未满，则将元素放入目前队尾指针指向的位置，然后将队尾指针加 1，完成插入
	// 注意顺序队列里指针的加 1 是循环意义下的加 1，即：(指针 + 1) % 数组大小

	if ((p_seq_queue->rear + 1) % SEQ_INIT_SIZE == p_seq_queue->front)
	{
		printf("Error: -- EnSeqQueue -- the queue is already full.\n");
		exit(EXIT_FAILURE);
	}
	p_seq_queue->p_base[p_seq_queue->rear] = elem;
	p_seq_queue->rear = (p_seq_queue->rear + 1) % SEQ_INIT_SIZE;
}

void DeSeqQueue(SeqQueue* p_seq_queue, ElemType* p_elem)
{
	// 删除元素，先判断元素是否已空，是则报错
	// 队列未空，则将队首指针加 1，完成删除
	// 注意顺序队列里指针的加 1 是循环意义下的加 1，即：(指针 + 1) % 数组大小

	if (p_seq_queue->rear == p_seq_queue->front)
	{
		printf("Error: -- DeSeqQueue -- the queue is alreay empty,\n");
		exit(EXIT_FAILURE);
	}
	*p_elem = p_seq_queue->p_base[p_seq_queue->front];
	p_seq_queue->front = (p_seq_queue->front + 1) % SEQ_INIT_SIZE;
}

void DestroySeqQueue(SeqQueue* p_seq_queue)
{
	free(p_seq_queue->p_base);
	p_seq_queue->p_base = NULL;
	p_seq_queue->front = 0;
	p_seq_queue->rear = 0;
}

int GetSeqQueueLength(SeqQueue seq_queue)
{
	return (seq_queue.rear - seq_queue.front + SEQ_INIT_SIZE) % SEQ_INIT_SIZE;
}
