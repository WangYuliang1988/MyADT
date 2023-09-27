//
// stack.h
//
// 用于学习数据结构栈相关知识
//
#ifndef _WYL_STACK
#define _WYL_STACK

//
// 栈
// 
// 定义：
//	栈是一种操作受限的线性表，限定只能在表的尾部进行插入或删除操作。
// 
// 特点：
//	1. 后进先出（last in first out, LIFO）；
//	2. 第一个元素称为栈底元素（base），最后一个元素称为栈顶元素（top）；
//	3. 插入元素称为进栈，删除元素称为出栈。
// 
// 存储结构：
//	1. 顺序存储，用一组地址连续的存储单元依次存放自栈底至栈顶的元素，称为顺序栈；
//	2. 链式存储，用一组地址任意的存储单元存放栈中的元素，称为链栈。
//

#include <stdio.h>
#include <stdlib.h>
#include "unidef.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 基于顺序存储结构的栈（顺序栈）
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
* 顺序栈
*/
typedef struct {
	ElemType* base; // 栈底指针
	ElemType* top;  // 指向栈顶元素下一个位置
	int stack_size; // 栈当前可容纳的元素个数
	// int length;  // 根据 base/top 的定义以及指针求差的意义，top - base = 栈当前已包含的元素个数
}SeqStack;

/*
* 初始化
*/
void InitSeqStack(SeqStack* p_seq_stack);

/*
* 入栈
*/
void Push(SeqStack* p_seq_stack, ElemType elem);

/*
* 出栈
*/
ElemType Pop(SeqStack* p_seq_stack);

/*
* 销毁
*/
void DestroySeqStack(SeqStack* p_seq_stack);

/*
* 获取栈顶元素
*/
ElemType GetTop(SeqStack seq_stack);

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 基于栈的算法应用
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
* 进制转换
* 
* 十进制 N 转换为 D 进制的算法为：除 D 取余，余数倒排。
*/
void Convert(int dec, int target);

/*
* 括号匹配
* 
* 算法：左括号进栈。右括号检测是否与栈顶元素匹配，匹配则栈顶出栈，不匹配则整体不匹配。结束时栈为空表示匹配，不为空表示不匹配。
*/
int MatchBracket(char* exp);

/*
* 四则运算
* 
* 算法：设立操作数栈、运算符栈两个栈，然后根据四则运算符优先级，分别对两个栈进行入栈出栈，得出计算结果。
*/
int CalcExpression(char* exp);

#endif // !_WYL_STACK
