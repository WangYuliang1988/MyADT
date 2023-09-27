#include <stdio.h>
#include "linear_list.h"
#include "stack.h"

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
		printf("%d, ", GetSeqElem(seq_list, i));
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
		printf("%d, ", GetLinkElem(link_list, i));
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
	Pop(&seq_stack);
	// 读取栈顶元素
	printf("Stack top: %d\n", GetTop(seq_stack));
	// 销毁
	DestroySeqStack(&seq_stack);
}