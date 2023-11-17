//
// unidef.h
// 
// �����Ŀ���õ���ͨ�ö���
//
#ifndef _WYL_UNIDEF
#define _WYL_UNIDEF

/*
* Ϊ��ʾ���ݽṹ���㣬�� ElemType ����Ϊ long long �ı���
* 
* ֮����ѡ�� long long������Ϊ long long ռ 8 ���ֽ��ڴ棬���Դ���ָ��ָ��ĵ�ַ
*/
typedef long long ElemType;

/*
* ˳��洢�ṹ����˳���˳��ջ����ʼ��С
*/
#define SEQ_INIT_SIZE 100

/*
* ˳��洢�ṹ����˳���˳��ջ��������С
*/
#define SEQ_INCREAMENT 10

/*
* ���洢�ṹ�ɴ洢���������
*/
#define TREE_MAX_SIZE 100

/*
* ���������
* 
* ���� 0x3f3f3f3f Ϊ�����������ԭ��
*	1. ��ֵ�ǳ���ͬ 32 λ�����ܱ�ʾ�����ֵ 0x7fffffff ��ͬһ��������
*	2. ��ֵ�� 0x7fffffff ����һ�ξ��룬�������㣺����������������������������������������󣬶����������
*	3. ����ʹ�� memset ������һ���������������Ԫ�س�ʼ��Ϊ�������Ϊ 0x3f3f3f3f ��ÿ���ֽڶ�����ͬ�� 0x3f����
*/
#define INFINITY 0x3f3f3f3f

#endif // !_WYL_UNIDEF
