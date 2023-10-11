#include "queue.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// ���������л�������
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
	// ����ֻ���ڶ�β����Ԫ��
	// ���ȣ�Ϊ�������Ԫ�ؽ������ڴ�ռ�
	// Ȼ�󣬽��ɶ�β���� p_next ָ���½����
	// ��󣬽���βָ���ָ���½���㣬��ɲ���

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
	// ����ֻ���ڶ���ɾ��Ԫ��
	// ���ȣ�ʹ����ʱ����������Ԫ�ؽ��ĵ�ַ
	// Ȼ�󣬽�ͷ���� p_next ָ����Ԫ�ؽ��� p_next
	// ����ͷ���Ԫ�ؽ��ռ�õ��ڴ�ռ䣬���ɾ��
	// ע�⣬��ɾ����ͷ���� p_next ��Ϊ NULL������Ϊ�ն��У����轫��βָ��Ҳָ��ͷ���

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
// ����˳����л�������
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
	// ����Ԫ�أ����ж϶����Ƿ����������򱨴���Ϊ˳�������ѭ���ṹ���޷���̬��չ��
	// ����δ������Ԫ�ط���Ŀǰ��βָ��ָ���λ�ã�Ȼ�󽫶�βָ��� 1����ɲ���
	// ע��˳�������ָ��ļ� 1 ��ѭ�������µļ� 1������(ָ�� + 1) % �����С

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
	// ɾ��Ԫ�أ����ж�Ԫ���Ƿ��ѿգ����򱨴�
	// ����δ�գ��򽫶���ָ��� 1�����ɾ��
	// ע��˳�������ָ��ļ� 1 ��ѭ�������µļ� 1������(ָ�� + 1) % �����С

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
