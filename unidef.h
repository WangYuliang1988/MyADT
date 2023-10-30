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

#endif // !_WYL_UNIDEF
