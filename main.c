#include <stdio.h>
#include "linear_list.h"

int main(void)
{
	printf("Hello, World!\n\n");
	
	// ˳���
	SeqList seq_list;
	// ��ʼ��
	InitSeqList(&seq_list);
	// ����Ԫ��
	for (int i = 0; i < 10; i++)
	{
		InsertSeqElem(&seq_list, i, i);
	}
	// ɾ��Ԫ��
	DeleteSeqElem(&seq_list, 0);
	// ��ȡԪ��
	printf("SeqList: ");
	for (int i = 0; i < seq_list.length; i++)
	{
		printf("%d, ", GetSeqElem(seq_list, i));
	}
	printf("\b\b \n");

	// ����
	LinkList link_list;
	// ��ʼ��
	InitLinkList(&link_list);
	// ����Ԫ��
	for (int i = 0; i < 10; i++)
	{
		InsertLinkElem(&link_list, i, i);
	}
	// ɾ��Ԫ��
	DeleteLinkElem(&link_list, 0);
	// ��������
	ReverseLinkList(&link_list);
	// ��ȡԪ��
	printf("LinkList: ");
	for (int i = 0; i < GetLinkLength(link_list); i++)
	{
		printf("%d, ", GetLinkElem(link_list, i));
	}
	printf("\b\b \n");
}