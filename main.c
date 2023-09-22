#include <stdio.h>
#include "linear_list.h"

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
}