//
// linear_list.h
//
// 用于学习数据解构之线性表相关知识
//
#ifndef _WYL_LINEAR_LIST
#define _WYL_LINEAR_LIST

//
// 线性表
//
// 定义：
//	一个线性表是 n 个数据元素的有限序列。
// 
// 特点：
//	1. 存在唯一的一个被称作“第一个”的数据元素；
//	1. 存在唯一的一个被称作“最后一个”的数据元素；
//	3. 除第一个元素之外的数据元素均有且只有一个前驱；
//	4. 除最后一个元素之外的数据元素均有且只有一个后继。
//
// 一个数据元素由若干数据项组成，可称数据元素为“记录”，称含有大量数据元素的线性表为“文件”。
// 
// 存储结构：
//	1. 顺序存储：用一组地址连续的存储单元依次存储线性表的各个数据元素；
//	2. 链式存储：用一组地址任意的存储单元存储线性表的各个数据元素。
// 
// 顺序存储（顺序表）
//	特点：以物理位置相邻表示逻辑关系相邻，所有元素的存储位置均可通过第一个元素的位置计算得到，元素的读取效率高。
//	实现：基于数组实现，并可分为静态实现和动态实现，一般使用动态实现方式，实用性更高。
//	疑问：动态扩展顺序表的空间时，如何确保新分配的地址跟之前的地址是相邻的？
//	解答：使用 realloc() 调整之前已分配的内存块的大小，确保内存地址的连续。
//
// 链式存储（链表）
//	特点：逻辑相邻的元素物理位置未必相邻，通过指针来查找元素的存储位置，元素的增加/删除效率高。
//	实现：基于结点（数据+指针）实现，并可分为单链表、单循环链表、双向链表、双向循环链表等实现方式。
//	单链表：头指针 -> 头结点 -> 元素结点；头指针是一个指针变量，可唯一确定单链表；头结点是人为附加的结点，用于简化链表操作。
//	单循环链表：末尾元素结点指针域指向头结点的单链表，从表中任一结点出发均可找到其它任一结点。可灵活设置头、尾指针简化头插、尾插、合并等操作。
//	双向链表：类似单链表，不同的是每个结点包含两个指针域，一个指向前驱结点（prior），一个指向后继结点（next）。
//	双向循环链表：类似单循环链表，不同的是每个结点包含两个指针域，一个指向前驱结点（prior），一个指向后继结点（next）。
//

#include <stdio.h>
#include <stdlib.h>
#include "unidef.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 基于顺序存储结构的线性表（顺序表）
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
* 顺序表
*/
typedef struct
{
	ElemType* elem; // 顺序表第一个元素的地址
	int length; // 顺序表当前已包含的元素个数
	int list_size; // 顺序表当前可容纳的元素个数
}SeqList;

/*
* 初始化
*/
void InitSeqList(SeqList* p_seq);

/*
* 向位置 i 插入一个元素
* 
* 注意：元素位置索引从 0 开始
*/
void InsertSeqElem(SeqList* p_seq, int i, ElemType elem);

/*
* 删除位置 i 的元素
*/
void DeleteSeqElem(SeqList* p_seq, int i);

/*
* 销毁
*/
void DestroySeqList(SeqList* p_seq);

/*
* 获取位置 i 的元素
*/
ElemType GetSeqElem(SeqList seq, int i);

/*
* 获取某个元素的前驱元素
*/
ElemType GetSeqElemPre(SeqList seq, ElemType cur_e);

/*
* 获取某个元素的后继元素
*/
ElemType GetSeqElemNext(SeqList seq, ElemType cur_e);

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 基于链式存储结构的线性表（链表）
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
* 单链表结点
*/
typedef struct LNode // 当结构体内部使用该结构体做类型时，结构体名称（即 LNode）不能省略
{
	ElemType elem; // 数据域，存储数据
	struct LNode* next; // 指针域，指向其后续结点，末尾结点的 next 为 NULL
}LNode, *LinkList; // LNode 为 struct LNode 的别名，LinkList 为 LNode* 的别名

/*
* 初始化
*/
void InitLinkList(LinkList* p_list);

/*
* 向位置 i 插入一个元素
* 
* 注意：元素位置索引从 0 开始
*/
void InsertLinkElem(LinkList* p_list, int i, ElemType elem);

/*
* 删除位置 i 的元素
*/
void DeleteLinkElem(LinkList* p_list, int i);

/*
* 逆置链表元素
*/
void ReverseLinkList(LinkList* p_list);

/*
* 销毁
*/
void DestroyLinkList(LinkList* p_list);

/*
* 获取链表长度
*/
int GetLinkLength(LinkList list);

/*
* 获取位置 i 的元素
*/
ElemType GetLinkElem(LinkList list, int i);

#endif // !_WYL_LINEAR_LIST

