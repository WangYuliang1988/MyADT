#include <stdio.h>
#include "linear_list.h"
#include "stack.h"
#include "queue.h"
#include "ds_string.h"
#include "ds_array.h"

int main(void)
{
	printf("Hello, World!\n\n");
	
	// 顺序表
	SeqList seq_list;
	// 初始化
	InitSeqList(&seq_list);
	// 插入元素
	for (int i = 0; i < 10; i++)
	{
		InsertSeqElem(&seq_list, i, i);
	}
	// 删除元素
	DeleteSeqElem(&seq_list, 0);
	// 读取元素
	printf("SeqList: ");
	for (int i = 0; i < seq_list.length; i++)
	{
		ElemType elem;
		GetSeqElem(seq_list, i, &elem);
		printf("%d, ", elem);
	}
	printf("\b\b \n");
	// 销毁
	DestroySeqList(&seq_list);

	// 链表
	LinkList link_list;
	// 初始化
	InitLinkList(&link_list);
	// 插入元素
	for (int i = 0; i < 10; i++)
	{
		InsertLinkElem(&link_list, i, i);
	}
	// 删除元素
	DeleteLinkElem(&link_list, 0);
	// 逆置链表
	ReverseLinkList(&link_list);
	// 读取元素
	printf("LinkList: ");
	for (int i = 0; i < GetLinkLength(link_list); i++)
	{
		ElemType elem;
		GetLinkElem(link_list, i, &elem);
		printf("%d, ", elem);
	}
	printf("\b\b \n");
	// 销毁
	DestroyLinkList(&link_list);

	// 顺序栈
	SeqStack seq_stack;
	// 初始化
	InitSeqStack(&seq_stack);
	// 入栈
	for (int i = 0; i < 10; i++)
	{
		Push(&seq_stack, i);
	}
	// 出栈
	printf("Stack: ");
	for (int i = 0; i < 10; i++)
	{
		ElemType elem;
		Pop(&seq_stack, &elem);
		printf("%d, ", elem);
	}
	printf("\b\b \n");
	// 销毁
	DestroySeqStack(&seq_stack);

	// 链队列
	LinkQueue link_queue;
	// 初始化
	InitLinkQueue(&link_queue);
	// 插入
	for (int i = 0; i < 10; i++)
	{
		EnLinkQueue(&link_queue, i);
	}
	// 删除
	printf("LinkQueue: ");
	for (int i = 0; i < 10; i++)
	{
		ElemType elem;
		DeLinkQueue(&link_queue, &elem);
		printf("%d, ", elem);
	}
	printf("\b\b \n");
	// 销毁
	DestroyLinkQueue(&link_queue);

	// 顺序队列
	SeqQueue seq_queue;
	// 初始化
	InitSeqQueue(&seq_queue);
	// 插入元素
	for (int i = 0; i < 10; i++)
	{
		EnSeqQueue(&seq_queue, i);
	}
	// 获取长度
	int seq_queue_length = GetSeqQueueLength(seq_queue);
	// 删除元素
	printf("SeqQueue: ");
	for (int i = 0; i < seq_queue_length; i++)
	{
		ElemType elem;
		DeSeqQueue(&seq_queue, &elem);
		printf("%d, ", elem);
	}
	printf("\b\b \n");
	// 销毁
	DestroySeqQueue(&seq_queue);

	// 字符串模式匹配
	SString s = { 18, 'a', 'c', 'a', 'a', 'c', 'b', 'c', 'a', 'b', 'c', 'a', 'a', 'c', 'b', 'c', 'a', 'b', 'c' };
	SString p = { 6, 'c', 'a', 'a', 'c', 'b', 'c' };
	printf("Plain match index: %d\n", SStringIndex(s, p, 12));
	printf("KMP match index: %d\n", SStringIndexKMP(s, p, 12));

	// 转置矩阵
	TSMatrix tsm;
	tsm.mu = 10;
	tsm.nu = 20;
	tsm.tu = 8;
	tsm.data[1].i = 1, tsm.data[1].j = 2, tsm.data[1].e = 12;
	tsm.data[2].i = 1, tsm.data[2].j = 3, tsm.data[2].e = 9;
	tsm.data[3].i = 3, tsm.data[3].j = 1, tsm.data[3].e = -3;
	tsm.data[4].i = 3, tsm.data[4].j = 6, tsm.data[4].e = 14;
	tsm.data[5].i = 4, tsm.data[5].j = 3, tsm.data[5].e = 24;
	tsm.data[6].i = 5, tsm.data[6].j = 2, tsm.data[6].e = 18;
	tsm.data[7].i = 6, tsm.data[7].j = 1, tsm.data[7].e = 15;
	tsm.data[8].i = 6, tsm.data[8].j = 4, tsm.data[8].e = -7;
	// 按列转置
	TSMatrix tst;
	TransTSMatrix(tsm, &tst);
	printf("Transpose TSMatrix by column:\n");
	for (int i = 1; i <= tst.tu; i++)
	{
		printf("(%d, %d, %d)\n", tst.data[i].i, tst.data[i].j, tst.data[i].e);
	}
	// 快速转置
	TSMatrix tstf;
	TransTSMatrix(tsm, &tstf);
	printf("Fast transpose TSMatrix by column:\n");
	for (int i = 1; i <= tstf.tu; i++)
	{
		printf("(%d, %d, %d)\n", tstf.data[i].i, tstf.data[i].j, tstf.data[i].e);
	}
}