//
// unidef.h
// 
// 存放项目中用到的通用定义
//
#ifndef _WYL_UNIDEF
#define _WYL_UNIDEF

/*
* 为演示数据结构方便，将 ElemType 定义为 long long 的别名
* 
* 之所以选择 long long，是因为 long long 占 8 个字节内存，可以存下指针指向的地址
*/
typedef long long ElemType;

/*
* 顺序存储结构（如顺序表、顺序栈）初始大小
*/
#define SEQ_INIT_SIZE 100

/*
* 顺序存储结构（如顺序表、顺序栈）增量大小
*/
#define SEQ_INCREAMENT 10

/*
* 树存储结构可存储的最大结点数
*/
#define TREE_MAX_SIZE 100

/*
* 无穷大整数
* 
* 定义 0x3f3f3f3f 为无穷大整数的原因：
*	1. 该值非常大，同 32 位整数能表示的最大值 0x7fffffff 是同一数量级；
*	2. 该值距 0x7fffffff 还有一段距离，可以满足：无穷大加有穷数仍是无穷大、无穷大加无穷大仍是无穷大，而不会溢出；
*	3. 可以使用 memset 方法将一个整型数组的所有元素初始化为无穷大（因为 0x3f3f3f3f 中每个字节都是相同的 0x3f）。
*/
#define INFINITY 0x3f3f3f3f

#endif // !_WYL_UNIDEF
