//
// ds_array.h
//
// 用于学习数组数据结构相关知识
//
#ifndef _WYL_DS_ARRAY
#define _WYL_DS_ARRAY

#include <stdio.h>
#include <stdlib.h>
#include "unidef.h"

//
// 数组
// 
// 注意：
//	下方论及的数组，是作为数据结构的数组，不是作为编程语言中基本数据类型的数组。
//
// 定义：
//	数组是一种线性表数据结构，使用一组连续的内存空间，来存储一组具有相同类型的数据。
// 
// 特点：
//	1. 数组同栈、队列等其他线性表最大的不同在于：数组可以存储包含多种“一对一”逻辑关系的数据；
//	2. 实际场景中，存储具有 n 种“一对一”逻辑关系的数据时，通常会建立 n 维数组：
//		一维数组同队列等其他线性表非常类似，用来存储只有一种“一对一”逻辑关系的数据；
//		二维数组用来存储包含两种“一对一”逻辑关系的数据，可以看作是存储一维数组的一维数组；
//		n 维数组用老存储包含 n 种“一对一”逻辑关系的数据，可以看作是存储 n-1 维数组的一维数组；
//	3. 数组一旦建立，维数将不再改变，且不论维数是多少，数组数据的类型都必须一致；
//	4. 数组的基本操作只有：初始化、销毁、取元素值、改元素值，没有插入和删除操作。
// 
// 存储结构：
//	1. 基于数组没有插入和删除操作的特点，数组一般采用顺序存储结构（顺序表）来实现；
//	2. 数组可以是多维的，而顺序表只能是一维的线性空间，要将 n 维数组存储到顺序表中，有以下两种方案：
//		以行序为主序，左侧下标先固定，让右侧下标增加，右侧下标达到最大值后，再增加左侧下标；
//		以列序为主序，右侧下标先固定，让左侧下标增加，左侧下标达到最大值后，再增加右侧下标；
// 
// 查找元素：
//	在 n 维数组中查找目标元素，需要提前具备以下信息：
//		1. 数组的存储方式（行序为主序 or 列序为主序）；
//		2. 首元素的地址；
//		3. 目标元素的坐标；
//		4. 单个元素占据的内存大小，通常用 L 表示。
//	以二维数组为例：
//		若数组采用行序为主序的存储方式，则在数组 a[m][n] 中寻找 a[i][j] 位置的公式为：
//			Loc(i, j) = Loc(0, 0) + (i * n + j) * L
//		若数组采用列序为主序的存储方式，则在数组 a[m][n] 中寻找 a[i][j] 位置的公式为：
//			Loc(i, j) = Loc(0, 0) + (j * m + i) * L
// 
// 应用场景：
//	数组的典型应用是用于存储矩阵，特别是对称矩阵、上（下）三角矩阵、稀疏矩阵的压缩存储。
//

/*
* 基于顺序存储的数组结构
*/
typedef struct
{
	ElemType* p_base; // 数组首元素地址
	int dim;		  // 数组维度
	int* bounds;	  // 存放数组各维长度的数组，比如一个三维数组 arr[3, 4, 5]，其 bounds 为：{ 3, 4, 5 }
	int* constants;   // 存放数组每变化一维的跨度的数组，比如上述三维数组，以行序为主序存储，其 constants 为：{ 20, 5, 1 }
}Array;

// 
// 矩阵
// 
// 定义：
//	矩阵是一个数学概念，指由 m * n 个元素组成的 m 行（横向）n 列（纵向）的一种数学结构。
// 
// 注意：
//	矩阵中元素的行标和列标都是从 1 开始。
// 
// 存储：
//	1. 普通矩阵一般通过二维数组存储，一个数组单元存储一个矩阵数据；
//	2. 特殊矩阵，如对称矩阵、稀疏矩阵等，各自有基于数组的经过优化的存储方式。
// 
// 对称矩阵
//	1. 定义：满足 m = n 且 Mtx[i,j] = Mtx[j,i] 的矩阵称为对称矩阵；
//	2. 存储：使用一维数组进行存储，只存储上三角或下三角的元素，存储的元素总数为 n(n+1)/2：
//		若以行序为主序存储上三角元素：
//			Mtx[i,j] = Arr[j*(j-1)/2+(i-1)]；
//		若以行序为主序存储下三角元素：
//			Mtx[i,j] = Arr[i*(i-1)/2+(j-1)]。
// 
// 上（下）三角矩阵
//	1. 定义：上（下）三角（包括主对角线）中的元素为有效元素，其余元素均为某一相同值（比如 0）的矩阵；
//	2. 存储：同对称矩阵（有效元素之外具有相同值的元素通过一个额外的变量存储）。
// 
// 稀疏矩阵
//	1. 定义：设在 m*n 的矩阵中有 t 个非零元素，若 t/(m*n) <= 0.05，则称该矩阵为稀疏矩阵；
//	2. 实现：使用由三元组 (行序, 列序, 值) 组成的一维数组，以及 m, n, t 来唯一确定稀疏矩阵；
//	3. 存储：
//		顺序存储：
//			三元组顺序表，优点：便于进行按顺序处理的矩阵运算；缺点：不能随机存取，不能插入删除；
//			行逻辑链接的顺序表，优点：拥有三元组顺序表的优点，并可随机存取；缺点：无法进行插入删除；
//		链式存储：
//			十字链表，优点：可以对稀疏矩阵进行添加或删除非零元素的操作，缺点：不能随机存取。
//

#define MATRIX_MAX_SIZE 100
#define MATRIX_MAX_RC 100

/*
* 用于标识矩阵元素的三元组结构体
*/
typedef struct
{
	int i; // 行序
	int j; // 列序
	ElemType e; // 元素值
}Triple;

/*
* 三元组顺序表结构体
*/
typedef struct
{
	// 用于存放稀疏矩阵非零元素的数组，可存放的最大元素数是 MATRIX_MAX_SIZE
	// 加 1 是为了把数组 0 位置空出来，从位置 1 开始存储，以同矩阵元素下标从 1 开始计数保持一致，方便存储位置的计算
	Triple data[MATRIX_MAX_SIZE + 1];
	int mu; // 矩阵行数
	int nu; // 矩阵列数
	int tu; // 矩阵非零元素个数
}TSMatrix;

/*
* 行逻辑链接的顺序表结构体
* 
* 即在三元组顺序表的基础上，增加一个指示各行第一个非零元素位置的数组
*/
typedef struct
{
	// 用于存放稀疏矩阵非零元素的数组，可存放的最大元素数是 SEQ_INIT_SIZE
	// 加 1 是为了把数组 0 位置空出来，从位置 1 开始存储，以同矩阵元素下标从 1 开始计数保持一致，方便存储位置的计算
	Triple data[MATRIX_MAX_SIZE + 1];
	int rpos[MATRIX_MAX_RC + 1]; // 存放各行第一个非零元素位置，加 1 的原因同上
	int mu; // 矩阵行数
	int nu; // 矩阵列数
	int tu; // 矩阵非零元素个数
}RLSMatrix;

/*
* 基于三元组顺序表的矩阵转置-按列转置
* 
* 矩阵转置：将一个 m*n 的矩阵 M，转置为 n*m 的矩阵 T，且 T(i,j) = M(j, i)。
* 
* 算法思想：
*	遍历矩阵 M 的三元组数组，依次寻找列序 1...n 的项，将该项的行序、列序、值分别作为目标项的列序、行序、值存入矩阵 T 的三元组数组中。
* 
* 注意：
*	矩阵的三元组数组从位置 1 开始存储。
* 
* tsm 为原矩阵， p_tst 为指向转置矩阵的指针。
*/
void TransTSMatrix(TSMatrix tsm, TSMatrix* p_tst);

/*
* 基于三元组顺序表的矩阵转置-快速转置
*
* 矩阵转置：将一个 m*n 的矩阵 M，转置为 n*m 的矩阵 T，且 T(i,j) = M(j, i)。
*
* 算法思想：
*	1. 核心思想仍是按列转置，通过前置处理，实现一次遍历即可完成转置；
*	2. 前置处理是指，先按列遍历一次原矩阵，得出每列（即转置矩阵的每行）包含的元素个数，存入一个数组中；
*	3. 然后，新建一个数组，记录原矩阵每列当前项应该存入转置矩阵三元组数组中的位置，并在每次存入后更新；
*	4. 最后，按列遍历原矩阵，并直接将每次遍历的项，按步骤 3 数组指定的位置，存入转置矩阵三元组数组中。
*
* 注意：
*	矩阵的三元组数组从位置 1 开始存储。
*
* tsm 为原矩阵， p_tst 为指向转置矩阵的指针。
*/
void FastTransTSMatrix(TSMatrix tsm, TSMatrix* p_tst);

/*
* 十字链表的结点结构体
*/
typedef struct OLNode
{
	int i; // 行序
	int j; // 列序
	ElemType e; // 元素值
	struct OLNode* p_right; // 指向结点在行上右侧结点的指针
	struct OLNode* p_down; // 指向结点在列上下方结点的指针
}OLNode, *OLink;

/*
* 十字链表结构体
*/
typedef struct
{
	OLink* p_rhead; // 指向行链表头结点的指针
	OLink* p_chead; // 指向列链表头结点的指针
	int mu; // 矩阵行数
	int nu; // 矩阵列数
	int tu; // 矩阵非零元素个数
	// p_rhead 和 p_chead 这两个指针就是十字链表中“十字”的由来
}CrossList;

//
// 广义表
// 
// 定义：
//	广义表，又称列表，是一种可以同时存储不可再分的元素和广义表的线性存储结构。
// 
// 特点：
//	1. 广义表相当于数组的扩展，数组中存储的项，要么都是不可再分的元素，要么都是数组，不能混在一起存储，而广义表可以；
//	2. 广义表存储的单个元素称为“原子”，存储的广义表称为“子表”，如 {1,{2,3}} 表示广义表存储了原子 1 和 子表 {2,3}；
//	3. 广义表非空时，第一个数据（原子或子表）称为“表头”，剩下的数据构成的广义表称为“表尾”，如 {1,{2},3} 的表头是 1，表尾是 {{2},3}；
//	4. 非空的广义表一定有表头和表尾，且表尾一定是一个广义表，如 {1} 的表头是 1，表尾是 {}，即表尾是一个空表。
// 
// 存储：
//	根据广义表的特点，通常情况下广义表采用链表实现（若用顺序表实现，不仅操作困难，而且浪费空间）。
//

/*
* 广义表结点结构体
*/
struct GLNode
{
	int tag; // 标记结点存储的数据类型，0 原子，1 子表
	union // union 是一种特殊的数据类型，允许在相同的内存位置存储不同类型的数据
	{
		ElemType atom; // 原子结点的值
		struct GLNode* p_child; // 指向子表结点的指针
	}un; // 广义表结点存储的数据，要么是原子，要么是子表
	struct GLNode* p_next; // 指向下一个结点的指针
}GLNode, *GList;

#endif // !_WYL_DS_ARRAY
