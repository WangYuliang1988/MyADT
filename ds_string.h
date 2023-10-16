//
// ds_string.h
//
// 用于学习数据结构串（字符串）相关知识
//
#ifndef WYL_DS_STRING
#define WYL_DS_STRING

//
// 串（字符串）
//
// 定义：
//	串（字符串）是由 0 个或多个字符组成的一种数据受限的线性表。
// 
// 特点：
//	1. 数据受限，只能由字符组成；
//	2. 基本操作（插入、删除等）通常以“子串”作为操作对象，而非单个字符。
// 
// 存储结构：
//	1. 定长顺序存储，又称静态存储分配的字符串，即用一组地址连续且总长固定的存储单元依次存放串中的字符序列；
//	2. 变长顺序存储，又称堆存储，即以一组地址连续且总长可变的存储单元依次存放串中的字符序列，存储空间在程序运行过程中动态分配；
//	3. 链式存储，即使用单链表存储串。同时，为提高空间利用率，可使每个结点数据域存放多个字符（变为顺序结构和链式结构的综合），称为块链存储。
// 
// 基于串的三种存储结构的优缺点，实际应用中一般使用堆存储结构存储串。
//

#include <stdio.h>

/*
* 基于定长顺序存储的串
* 
* 通过定长数组实现，数组索引 0 位置存放串的长度，串包含的字符序列从索引 1 开始存放
*/
#define MAX_STR_LEN 255
typedef unsigned char SString[MAX_STR_LEN + 1]; // 定义一个元素类型为 unsigned char，元素个数为 256 的数组类型 SString

int SStringIndex(SString s, SString p, int pos);
int SStringIndexKMP(SString s, SString p, int pos);

/*
* 基于堆存储的串
*/
typedef struct
{
	char* p_base;
	int length;
}HString;

/*
* 基于块链存储的串
*/
#define CHUNK_SIZE 80 // 定义每个结点可存放的字符个数
typedef struct Chunk // 定义结点数据结构
{
	char ch[CHUNK_SIZE];
	struct Chunk* p_next;
}Chunk;
// 根据单链表的特点，可以通过头指针唯一确定单链表，因此可以直接在定义结点时增加 *LString 来定义链串
// 但为了便于进行串的操作，因此除头指针外还可附设一个尾指针指向链表最后一个结点，同时附设串的长度
typedef struct // 定义链串数据结构
{
	Chunk* p_head;
	Chunk* p_tail;
	int length;
}LString;

#endif // !WYL_DS_STRING
