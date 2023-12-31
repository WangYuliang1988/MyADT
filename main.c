#include <stdio.h>
#include "linear_list.h"
#include "stack.h"
#include "queue.h"
#include "ds_string.h"
#include "ds_array.h"
#include "tree.h"
#include "graph.h"
#include "search.h"
#include "sort.h"

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
		printf("%lld, ", elem);
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
		printf("%lld, ", elem);
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
		printf("%lld, ", elem);
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
		printf("%lld, ", elem);
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
		printf("%lld, ", elem);
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
	// 按列转置
	TSMatrix tst;
	TransTSMatrix(tsm, &tst);
	printf("Transpose TSMatrix by column:\n");
	for (int i = 1; i <= tst.tu; i++)
	{
		printf("(%d, %d, %lld)\n", tst.data[i].i, tst.data[i].j, tst.data[i].e);
	}
	// 快速转置
	TSMatrix tstf;
	TransTSMatrix(tsm, &tstf);
	printf("Fast transpose TSMatrix by column:\n");
	for (int i = 1; i <= tstf.tu; i++)
	{
		printf("(%d, %d, %lld)\n", tstf.data[i].i, tstf.data[i].j, tstf.data[i].e);
	}

	// 二叉树
	BiTree bt;
	// 生成二叉树
	CreateBiTree(&bt, "A(B(D(,G),E),C(F,))");
	// 先序遍历-递归实现
	printf("Traverse binary tree recursively by pre order: ");
	PreOrderTraverseRecursively(bt);
	printf("\n");
	// 中序遍历-递归实现
	printf("Traverse binary tree recursively by in order: ");
	InOrderTraverseRecursively(bt);
	printf("\n");
	// 后序遍历-递归实现
	printf("Traverse binary tree recursively by post order: ");
	PostOrderTraverseRecursively(bt);
	printf("\n");
	// 先序遍历
	printf("Traverse binary tree by pre order: ");
	PreOrderTraverse(bt);
	printf("\n");
	// 中序遍历
	printf("Traverse binary tree by in order: ");
	InOrderTraverse(bt);
	printf("\n");
	// 后序遍历
	printf("Traverse binary tree by post order: ");
	PostOrderTraverse(bt);
	printf("\n");
	// 销毁
	DestroyBiTree(&bt);

	// 构建哈夫曼树
	HuffmanTree ht;
	float warr[] = { 0.2f, 0.3f, 0.5f, 0.2f, 0.1f, 0.3f };
	int n = sizeof(warr) / sizeof(warr[0]); // 叶子结点个数
	CreateHuffmanTree(&ht, warr, n);
	// 打印
	printf("Huffman tree:\n");
	for (int i = 0; i < 2 * n - 1; i++)
	{
		printf("weight: %f, par: %d, lch: %d, rch: %d\n", ht[i].weight, ht[i].parent, ht[i].lch, ht[i].rch);
	}
	// 哈夫曼编码
	char carr[] = { 'A','B', 'C', 'D', 'E', 'F' };
	HuffmanCode hc;
	HuffmanCoding(ht, &hc, n);
	printf("Huffman code:\n");
	for (int i = 0; i < n; i++)
	{
		printf("%c: %s\n", carr[i], hc[i]);
	}
	// 销毁
	DestroyHuffmanTree(&ht);

	// 图
	VertexType vexs[] = { 1, 2, 3, 4, 5, 6 }; // 图的顶点集合
	int vexnum = sizeof(vexs) / sizeof(vexs[0]); // 图的顶点个数
	char* adjs = "(1,2,3)(1,4,2)(1,5,5)(2,3,2)(2,4,1)(2,6,5)(3,5,4)(3,6,4)(4,6,3)"; // 描述边的字符串
	char* arcs = "<2,3,2><2,5,3><2,6,4><3,5,1><3,1,6><5,4,2><6,4,2><6,1,3><4,1,2>"; // 描述弧的字符串
	// 基于顺序存储构建图
	MGraph mg;
	CreateMGraph(&mg, vexs, vexnum, adjs);
	// 打印顺序存储结构图
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
	// 深度优先搜索
	DFSTraverse(mg);
	// 广度优先搜索
	BFSTraverse(mg);
	// 构建最小生成树-普里姆算法
	MiniSpanTreePrim(mg);
	// 构建最小生成树-克鲁斯卡尔算法
	MiniSpanTreeKruskal(mg);
	// 基于邻接表构建图
	ALGraph ag;
	CreateALGraph(&ag, vexs, vexnum, arcs);
	// 打印邻接表结构图
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
	// 拓扑排序
	int tparr[MAX_VERTEX_NUM];
	TopologicalSort(ag, tparr);
	printf("TopologicalSort: ");
	for (int i = 0; i < ag.vexnum; i++)
	{
		printf("%d, ", ag.vertices[tparr[i]].data);
	}
	printf("\b\b \n");
	// 关键路径
	CriticalPath(ag);
	// 迪杰斯特拉最短路径
	Dijkstra(ag, 2);
	// 弗洛伊德最短路径
	Floyd(ag);

	// 静态查找表
	ElemType earr[] = { 10, 14, 19, 26, 27, 31, 33, 35, 42, 44, 0 }; // 前 10 个是有效数据，最后一位用于放监视哨
	SSTable st = { earr, sizeof(earr) / sizeof(ElemType) - 1 }; // earr 数组最后一位是预留位，不应算作查找表的长度
	printf("SSTable: ");
	for (int i = 0; i < st.length; i++)
	{
		printf("%lld, ", st.earr[i]);
	}
	printf("\b\b \n");
	// 查找目标
	ElemType target = 31;
	// 顺序查找
	printf("SearchSeq: %lld is at index %d.\n", target, SearchSeq(st, target));
	// 折半查找
	printf("SearchBin: %lld is at index %d.\n", target, SearchBin(st, target));
	// 分块查找
	printf("SearchBlk: %lld is at index %d.\n", target, SearchBlk(st, target));
	// 次优查找树查找-用于关键字查找概率不同的场景
	float parr[] = { 0.1f, 0.1f, 0.2f, 0.5f, 0.3f, 0.4f, 0.4f, 0.3f, 0.5f, 0.2f };
	printf("SearchOpt: %lld is at index %d.\n", target, SearchOpt(st.earr, parr, st.length, target));

	// 二叉排序树
	BiTree bst = NULL;
	ElemType bearr[] = { 41, 20, 11, 29, 32, 65, 50, 91, 72, 99 };
	// 插入
	for (int i = 0; i < sizeof(bearr) / sizeof(bearr[0]); i++)
	{
		InsertBST(&bst, bearr[i]);
	}
	// 删除
	DeleteBST(&bst, 65);
	// 查找
	BiTree bstpos = NULL;
	SearchBST(bst, 50, &bstpos);
	printf("SearchBST: %d is at address %p.\n", 50, bstpos);

	// 平衡二叉排序树
	AVLTree avt = NULL;
	ElemType avarr[] = { 1, 23, 45, 34, 98, 9, 4, 35, 24 };
	// 插入
	int deeper;
	for (int i = 0; i < sizeof(avarr) / sizeof(avarr[0]); i++)
	{
		InsertAVL(&avt, avarr[i], &deeper);
	}
	// 查找
	AVLTree avpos = NULL;
	SearchAVL(avt, 98, &avpos);
	printf("SearchAVL: %d is at address %p.\n", 98, avpos);

	// 哈希表
	HashTable hat;
	// 初始化
	InitHashTable(&hat);
	// 插入
	for (int i = 0; i < MAX_HASH_SIZE; i++)
	{
		InsertHashTable(&hat, i);
	}
	// 查找
	printf("SearchHashTable: %d is at adress %p.\n", 20, SearchHashTable(hat, 20));

	// 排序
	int sarr[] = { 3, 2, 5, 1, 9, 20, 20, 16, 18, 1 };
	int alen = sizeof(sarr) / sizeof(sarr[0]);
	// 直接插入排序
	InsertSort(sarr, alen);
	// 折半插入排序
	BiInsertSort(sarr, alen);
	// 二路插入排序
	TwInsertSort(sarr, alen);
	// 希尔排序
	ShellInsert(sarr, alen);
	// 冒泡排序
	BubbleSort(sarr, alen);
	// 快速排序
	QuickSort(sarr, alen, 0, alen - 1);
	// 简单选择排序
	SelectSort(sarr, alen);
	// 堆排序
	HeapSort(sarr, alen);
	// 归并排序
	MergeSort(sarr, alen);
	// 计数排序
	CountSort(sarr, alen, 20);
	// 桶排序
	BucketSort(sarr, alen, 20);
	// 基数排序
	RadixSort(sarr, alen);
}