//
// queue.h
//
// 用于学习数据结构队列相关知识
//
#ifndef _WYL_QUEUE
#define _WYL_QUEUE

//
// 队列
//
// 定义：
//	队列是一种操作受限的线性表，限定只能在队尾进行插入，在队首进行删除。
// 
// 特点：
//	1. 先进先出（first in first out，FIFO）。
// 
// 存储结构：
//	1. 顺序存储，用一组地址连续的存储单元依次存放队列中的元素，称为顺序队列；
//	2. 链式存储，用一组地址任意的存储单元存放队列中的元素，称为链队列。
// 
// 顺序队列：
//	1. 基于数组 + 队首指针 + 队尾指针实现，队首和队尾指针通过数组下标模拟，初始状态下两个指针均置为 0；
//	2. 队列非空时，队首指针始终指向队首元素，队尾指针始终指向队尾元素的下一个位置；
//	3. 插入元素时，队尾指针加一；删除元素时，队首指针加一；
//	4. 根据插入和删除规则：
//		当队空时，队首和队尾指针相同（不一定是 0）；
//		当队尾指针超出数组大小时，队列不一定已满，因为之前可能进行过删除；
// 
//	   为合理利用空间，规定：
//		当队尾指针超出数组大小且队列未满时，将队尾指针置为 0（类似循环），再进行插入；
// 
//	   而这会带来一个新的问题，即：
//		若是将队尾指针置为 0 后再进行插入，则队尾指针和队首指针可能在队满的情况下相等；
//		因此，在该规定下，无法只根据队首指针和队尾指针相等与否来判断队空还是队满；
// 
//	   解决办法：
//		使用 [队尾指针 == 队首指针] 作为队列判空的条件；
//		牺牲一个数组空间，使用 [(队尾指针 + 1) % 数组大小 == 队首指针] 作为队列判满的条件；
// 
//	   综上：
//		顺序队列实际变为牺牲一个数组空间的循环结构，且长度固定，无法动态扩展；
//		顺序队列长度变为：[(队尾指针 + 数组大小 - 队首指针) % 数组大小]，指针的加一变为：[(指针 + 1) % 数组大小]。
// 

#include <stdio.h>
#include <stdlib.h>
#include "unidef.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 基于链式存储结构的队列（链队列）
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
* 链队列结点
*/
typedef struct QNode
{
	ElemType elem;
	struct QNode* p_next;
}QNode;

/*
* 链队列
* 
* 队首指针和队尾指针可以唯一确定一个队列
*/
typedef struct LinkQueue
{
	QNode* p_front; // 队首指针，指向头结点，注意头结点是人为附加的结点
	QNode* p_rear; // 队尾指针，指向尾结点
}LinkQueue;

/*
* 初始化
*/
void InitLinkQueue(LinkQueue* p_queue);

/*
* 插入
* 
* 队列只能在队尾插入
*/
void EnLinkQueue(LinkQueue* p_queue, ElemType elem);

/*
* 删除
* 
* 队列只能在队首删除
*/
void DeLinkQueue(LinkQueue* p_queue, ElemType* p_elem);

/*
* 销毁
*/
void DestroyLinkQueue(LinkQueue* p_queue);

/*
* 获取队头元素
*/
void GetLinkQueueHead(LinkQueue queue, ElemType* p_elem);

/*
* 判断队列是否为空
* 
* 1 空，0 非空
*/
int IsLinkQueueEmpty(LinkQueue queue);

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 基于顺序存储结构的队列（顺序队列）
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
* 顺序队列
*/
typedef struct
{
	ElemType* p_base; // 顺序队列第一个元素地址
	int front; // 队头指针（使用数组下标模拟），初始为 0，队列非空时指向队首元素
	int rear; // 队尾指针（使用数组下标模拟），初始为 0，队列非空时指向队尾元素的下一个位置
}SeqQueue;

/*
* 初始化
*/
void InitSeqQueue(SeqQueue* p_seq_queue);

/*
* 插入
* 
* 只能在队尾插入，插入时队尾指针加 1
*/
void EnSeqQueue(SeqQueue* p_seq_queue, ElemType elem);

/*
* 删除
* 
* 只能在队首删除，删除时队首指针加 1
*/
void DeSeqQueue(SeqQueue* p_seq_queue, ElemType* p_elem);

/*
* 销毁
*/
void DestroySeqQueue(SeqQueue* p_seq_queue);

/*
* 获取顺序表长度
*/
int GetSeqQueueLength(SeqQueue seq_queue);

#endif // !_WYL_QUEUE
