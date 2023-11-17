#include <stdio.h>
#include "linear_list.h"
#include "stack.h"
#include "queue.h"
#include "ds_string.h"
#include "ds_array.h"
#include "tree.h"
#include "graph.h"

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
		ElemType elem;
		GetSeqElem(seq_list, i, &elem);
		printf("%lld, ", elem);
	}
	printf("\b\b \n");
	// ����
	DestroySeqList(&seq_list);

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
		ElemType elem;
		GetLinkElem(link_list, i, &elem);
		printf("%lld, ", elem);
	}
	printf("\b\b \n");
	// ����
	DestroyLinkList(&link_list);

	// ˳��ջ
	SeqStack seq_stack;
	// ��ʼ��
	InitSeqStack(&seq_stack);
	// ��ջ
	for (int i = 0; i < 10; i++)
	{
		Push(&seq_stack, i);
	}
	// ��ջ
	printf("Stack: ");
	for (int i = 0; i < 10; i++)
	{
		ElemType elem;
		Pop(&seq_stack, &elem);
		printf("%lld, ", elem);
	}
	printf("\b\b \n");
	// ����
	DestroySeqStack(&seq_stack);

	// ������
	LinkQueue link_queue;
	// ��ʼ��
	InitLinkQueue(&link_queue);
	// ����
	for (int i = 0; i < 10; i++)
	{
		EnLinkQueue(&link_queue, i);
	}
	// ɾ��
	printf("LinkQueue: ");
	for (int i = 0; i < 10; i++)
	{
		ElemType elem;
		DeLinkQueue(&link_queue, &elem);
		printf("%lld, ", elem);
	}
	printf("\b\b \n");
	// ����
	DestroyLinkQueue(&link_queue);

	// ˳�����
	SeqQueue seq_queue;
	// ��ʼ��
	InitSeqQueue(&seq_queue);
	// ����Ԫ��
	for (int i = 0; i < 10; i++)
	{
		EnSeqQueue(&seq_queue, i);
	}
	// ��ȡ����
	int seq_queue_length = GetSeqQueueLength(seq_queue);
	// ɾ��Ԫ��
	printf("SeqQueue: ");
	for (int i = 0; i < seq_queue_length; i++)
	{
		ElemType elem;
		DeSeqQueue(&seq_queue, &elem);
		printf("%lld, ", elem);
	}
	printf("\b\b \n");
	// ����
	DestroySeqQueue(&seq_queue);

	// �ַ���ģʽƥ��
	SString s = { 18, 'a', 'c', 'a', 'a', 'c', 'b', 'c', 'a', 'b', 'c', 'a', 'a', 'c', 'b', 'c', 'a', 'b', 'c' };
	SString p = { 6, 'c', 'a', 'a', 'c', 'b', 'c' };
	printf("Plain match index: %d\n", SStringIndex(s, p, 12));
	printf("KMP match index: %d\n", SStringIndexKMP(s, p, 12));

	// ת�þ���
	TSMatrix tsm;
	tsm.mu = 10;
	tsm.nu = 10;
	tsm.tu = 8;
	tsm.data[1].i = 1, tsm.data[1].j = 2, tsm.data[1].e = 12;
	tsm.data[2].i = 1, tsm.data[2].j = 3, tsm.data[2].e = 9;
	tsm.data[3].i = 3, tsm.data[3].j = 1, tsm.data[3].e = -3;
	tsm.data[4].i = 3, tsm.data[4].j = 6, tsm.data[4].e = 14;
	tsm.data[5].i = 4, tsm.data[5].j = 3, tsm.data[5].e = 24;
	tsm.data[6].i = 5, tsm.data[6].j = 2, tsm.data[6].e = 18;
	tsm.data[7].i = 6, tsm.data[7].j = 1, tsm.data[7].e = 15;
	tsm.data[8].i = 6, tsm.data[8].j = 4, tsm.data[8].e = -7;
	// ����ת��
	TSMatrix tst;
	TransTSMatrix(tsm, &tst);
	printf("Transpose TSMatrix by column:\n");
	for (int i = 1; i <= tst.tu; i++)
	{
		printf("(%d, %d, %lld)\n", tst.data[i].i, tst.data[i].j, tst.data[i].e);
	}
	// ����ת��
	TSMatrix tstf;
	TransTSMatrix(tsm, &tstf);
	printf("Fast transpose TSMatrix by column:\n");
	for (int i = 1; i <= tstf.tu; i++)
	{
		printf("(%d, %d, %lld)\n", tstf.data[i].i, tstf.data[i].j, tstf.data[i].e);
	}

	// ������
	BiTree bt;
	// ��ʼ��
	InitBiTree(&bt);
	// ���ɶ�����
	CreateBiTree(&bt, "A(B(D(,G),E),C(F,))");
	// �������-�ݹ�ʵ��
	printf("Traverse binary tree recursively by pre order: ");
	PreOrderTraverseRecursively(bt);
	printf("\n");
	// �������-�ݹ�ʵ��
	printf("Traverse binary tree recursively by in order: ");
	InOrderTraverseRecursively(bt);
	printf("\n");
	// �������-�ݹ�ʵ��
	printf("Traverse binary tree recursively by post order: ");
	PostOrderTraverseRecursively(bt);
	printf("\n");
	// �������
	printf("Traverse binary tree by pre order: ");
	PreOrderTraverse(bt);
	printf("\n");
	// �������
	printf("Traverse binary tree by in order: ");
	InOrderTraverse(bt);
	printf("\n");
	// �������
	printf("Traverse binary tree by post order: ");
	PostOrderTraverse(bt);
	printf("\n");
	// ����
	DestroyBiTree(&bt);

	// ������������
	HuffmanTree ht;
	float warr[] = { 0.2f, 0.3f, 0.5f, 0.2f, 0.1f, 0.3f };
	int n = sizeof(warr) / sizeof(warr[0]); // Ҷ�ӽ�����
	CreateHuffmanTree(&ht, warr, n);
	// ��ӡ
	printf("Huffman tree:\n");
	for (int i = 0; i < 2 * n - 1; i++)
	{
		printf("weight: %f, par: %d, lch: %d, rch: %d\n", ht[i].weight, ht[i].parent, ht[i].lch, ht[i].rch);
	}
	// ����������
	char carr[] = { 'A','B', 'C', 'D', 'E', 'F' };
	HuffmanCode hc;
	HuffmanCoding(ht, &hc, n);
	printf("Huffman code:\n");
	for (int i = 0; i < n; i++)
	{
		printf("%c: %s\n", carr[i], hc[i]);
	}
	// ����
	DestroyHuffmanTree(&ht);

	// ͼ
	VertexType vexs[] = { 1, 2, 3, 4, 5, 6 }; // ͼ�Ķ��㼯��
	int vexnum = sizeof(vexs) / sizeof(vexs[0]); // ͼ�Ķ������
	char* adjs = "(1,2,3)(1,4,2)(1,5,5)(2,3,2)(2,4,1)(2,6,5)(3,5,4)(3,6,4)(4,6,3)"; // �����ߵ��ַ���
	char* arcs = "<2,3,2><2,5,3><2,6,4><3,5,1><3,1,6><5,4,2><6,4,2><6,1,3><4,1,2>"; // ���������ַ���
	// ����˳��洢����ͼ
	MGraph mg;
	CreateMGraph(&mg, vexs, vexnum, adjs);
	// ��ӡ˳��洢�ṹͼ
	printf("MGraph: kind: %d, vexnum: %d, arcnum: %d\n", mg.kind, mg.vexnum, mg.arcnum);
	for (int i = 0; i < vexnum; i++)
	{
		for (int k = 0; k < vexnum; k++)
		{
			if (mg.arcs[i][k].adj == INFINITY)
			{
				printf("infi ");
			}
			else
			{
				printf("%4d ", mg.arcs[i][k].adj);
			}
		}
		printf("\b \n");
	}
	// �����������
	DFSTraverse(mg);
	// �����������
	BFSTraverse(mg);
	// ������С������-����ķ�㷨
	MiniSpanTreePrim(mg);
	// ������С������-��³˹�����㷨
	MiniSpanTreeKruskal(mg);
	// �����ڽӱ���ͼ
	ALGraph ag;
	CreateALGraph(&ag, vexs, vexnum, arcs);
	// ��ӡ�ڽӱ�ṹͼ
	printf("ALGraph: kind: %d, vexnum: %d, arcnum: %d\n", ag.kind, ag.vexnum, ag.arcnum);
	for (int i = 0; i < ag.vexnum; i++)
	{
		printf("%d ->", ag.vertices[i].data);
		ArcNode* p_arc = ag.vertices[i].p_arc;
		if (p_arc)
		{
			while (p_arc)
			{
				printf(" %d", ag.vertices[p_arc->adjvex].data);
				p_arc = p_arc->p_next;
			}
		}
		else
		{
			printf(" NULL");
		}
		printf("\n");
	}
	// ��������
	int tparr[MAX_VERTEX_NUM];
	TopologicalSort(ag, tparr);
	printf("TopologicalSort: ");
	for (int i = 0; i < ag.vexnum; i++)
	{
		printf("%d, ", ag.vertices[tparr[i]].data);
	}
	printf("\b\b \n");
	// �ؼ�·��
	CriticalPath(ag);
	// �Ͻ�˹�������·��
	Dijkstra(ag, 2);
	// �����������·��
	Floyd(ag);
}