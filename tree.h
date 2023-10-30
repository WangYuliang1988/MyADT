//
// tree.h
//
// ����ѧϰ���ݽ⹹�����֪ʶ
//
#ifndef _WYL_TREE
#define _WYL_TREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unidef.h"
#include "stack.h"

//
// ��
// 
// ���壺
//	����Tree���� n (n>=0) ���������޼����� n = 0����Ϊ�������� n > 0����������������������
//		1. ���ҽ���һ����Ϊ����Root���Ľ�㣻
//		2. ������ɷ�Ϊ m (m>=0) �������ཻ�����޼���ÿ�����޼���������һ��������Ϊ����������SubTree����
// 
// ���
//	���Ķȣ�
//		���ӵ�е������ĸ�����Ϊ���Ķȣ�degree����
//	��֧��㣺
//		�ȴ��� 0 �Ľ�㣻
//	Ҷ�ӽ�㣺
//		�ȵ��� 0 �Ľ�㣻
//	���Ķȣ�
//		�Ƚ�һ���������н��Ķȣ����Ķȼ�Ϊ���Ķȣ�
//	���Ĳ�Σ�
//		��������ڵĲ�Ϊ��һ�㣬ĳ����ڵ� i �㣬���ӽ���ڵ� i+1 �㣻
//	������ȣ�
//		���н���ε����ֵ����Ϊ������ȣ�depth����
//	������/��������
//		���һ����������λ�ò��ܽ������������Ϊ����������֮����Ϊ��������
//	ɭ�֣�
//		m (m>=0) �û����ཻ�����ļ��ϳ�Ϊɭ�֣�Forest����
// 
// �ص㣺
//	����һ�ַ����Դ洢�ṹ��ͨ�������洢�߼���ϵΪ��һ�Զࡱ�����ݡ�
// 
// �洢��
//	1. ˫�ױ�ʾ����˳�������
//		ʹ������洢����㣬ÿ���������������������˫����˫�������丸��˫�ף�����������е�λ�ã�
//		�ص㣺��˫���ף��Һ����ѣ�
//	2. ���ӱ�ʾ����˳��� + ��������
//		ʹ������洢����㣬ÿ��������������������ͺ����򣬺����������ӣ����ӣ���㰴������˳�򹹳ɵĵ�������ͷָ�룻
//		�ص㣺�Һ����ף���˫���ѣ�
//		�ں��ӱ�ʾ���Ļ����ϣ�����Ϊÿ���������һ��˫���򣬴���丸��˫�ף�����������е�λ�ã�
//		�ص㣺�Һ����ף���˫���ף�
//	3. �����ֵܱ�ʾ����������������
//		ʹ�ö���������������·����������֣��洢����㣬��ָ����ָ����ĵ�һ���������ң����ӣ���ָ����ָ�����Ҳ��һ���ֵܣ�
//		�ص㣺
//			(1) �Һ����ף���˫���ף�
//			(2) ���Խ���ͨ��ת��Ϊ��������
// 
// ������
//	1. �ȣ�������������ȷ��ʸ���㣬�ٴ����������ȸ���������������
//	2. �󣨸�����������ȴ��������κ����������������Ȼ����ʸ���㣻
//	3. ����α��������϶��¡��������ҷ�������ÿ����㡣
//

/*
* ˫�ױ�ʾ��-�����
*/
typedef struct
{
	ElemType e;
	int parent; // ���ĸ���˫�ף�����������е�λ��
}PTNode;

/*
* ˫�ױ�ʾ��-���ṹ��
*/
typedef struct
{
	PTNode nodes[TREE_MAX_SIZE];
	int r; // ������������е�λ��
	int n; // �������Ľ�����
}PTree;

/*
* ���ӱ�ʾ��-�����������
*/
typedef struct CTNode
{
	int position; // �ú��ӽ���������е�λ��
	struct CTNode* next; // ָ����һ�����ӽ���ָ��
}CTNode;

/*
* ���ӱ�ʾ��-�����
*/
typedef struct
{
	ElemType e;
	CTNode* p_child; // ����������ͷָ��
	int parent; // ���ĸ���˫�ף�����������е�λ��
}CTBox;

/*
* ���ӱ�ʾ��-���ṹ��
*/
typedef struct
{
	CTBox nodes[TREE_MAX_SIZE];
	int r; // ������������е�λ��
	int n; // �������Ľ�����
}CTree;

/*
* �����ֵܱ�ʾ��-���ṹ��
*/
typedef struct CSNode
{
	ElemType e;
	struct CSNode* p_child; // ָ�����һ���������ң�����
	struct CSNode* p_sibling; // ָ�����Ҳ��һ���ֵ�
}CSNode, *CSTree;

//
// ������
// 
// ���壺
//	��������Binary Tree���� n (n>=0) ���������޼����� n = 0����Ϊ�ն��������� n > 0����������������������
//		1. ���ҽ���һ����Ϊ���Ľ�㣻
//		2. ���������ɷ�Ϊ 2 �������ཻ�����޼��������޼�����ָ�����ң���ʹֻ��һ��������Ϊ��������������������������������һ�ö�������
// 
// ���
//	����������Full Binary Tree����
//		һ�����Ϊ k ���� [(2 �� k �η�) - 1] �����Ķ�������Ϊ��������������Ź������϶��£�������ң�
//	��ȫ��������Complete Binary Tree����
//		��һ�ö�����ȥ�����һ�����Ϊ���������������һ�������δ����ҷֲ�����˶�������Ϊ��ȫ��������
// 
// �ص㣺
//	1. ����������������
//	2. �������Ľ��ĶȲ����� 2���������Ķ�Ҳ������ 2��
//	3. ��������һ������ȫ����������ȫ��������һ��������������
// 
// ���ʣ�
//	1. �������ĵ� i (i>=1) �������� [2 �� (i-1) �η�] ����㣻
//	2. ���Ϊ k (k>=1) �Ķ����������� [(2 �� k �η�) - 1] ����㣻
//	3. ���������Ҷ�ӽ�����Ϊ m����Ϊ 2 �Ľ�����Ϊ n�����У�m = n + 1��
//	4. ���� n ��������ȫ�����������Ϊ [(�� 2 Ϊ�� n �Ķ���) ����ȡ�� + 1]��
//	5. ��һ�þ��� n ��������ȫ�������������϶��¡�������ҵ�˳�򣬶�ÿ�������б�ţ�����ڽ�� i (1<=i<=n) �У�
//		(1) �� i > 1������˫�׽���� [(i/2) ����ȡ��]��
//		(2) �� 2*i > n������ i �����ӣ������������ǽ�� [2*i]��
//		(3) �� 2*i+1 > n������ i ���Һ��ӣ��������Һ����ǽ�� [2*i+1]��
// 
// �洢��
//	1. ˳��洢����һ���ַ�����Ĵ洢��Ԫ�������϶��¡�������ҵ�˳�����δ洢���Ľ�㣻
//	2. ��ʽ�洢����һ���ַ����Ĵ洢��Ԫ�洢���Ľ�㡣
// 
// ˳��洢��
//	�����ڴ洢��ȫ����������������������������ʵ����ʹ��һά����洢�������Ϊ i �Ľ��洢������� i-1 λ�ã�
//	��Ҫ�洢һ�����������Ҫ�Ƚ��������������Ϊ��ȫ���������������ӵĽ���Ӧ�������д�һ����Чֵ������ɴ����Ŀռ��˷ѣ�
//	��Ҫ�洢һ����������������£������Ϊ k ��ֻ�� k �������ҵ�֧������Ҫʹ�ó���Ϊ [(2 �� k �η�)-1] ��һά���顣
// 
// ��ʽ�洢��
//	���Դ洢�������͵Ķ�����������ʵ����ʹ���ɽ�㣨����һ��������������ֱ�ָ�����Һ��ӵ�ָ������ɵ��������д洢��
//	�������Ľ���ɣ�һ��������������ֱ�ָ�����Һ��ӵ�ָ������ɣ���Ƹ�����Ϊ����������
//	�������Ľ���ɣ�һ��������������ֱ�ָ�����Һ��Ӻ�˫�׵�ָ������ɣ���Ƹ�����Ϊ����������
//	�� n �������ɵĶ����������� n + 1 ����ָ����
// 
// ������
//	����������ʱ�����涨������ң�����ڸ������˵���У�
//		�ȣ������������D-L-R
//		�У������������L-D-R
//		�󣨸����������L-R-D
//	�������ı����㷨���Է�Ϊ�ݹ�ͷǵݹ����࣬�ǵݹ��ʵ����Ҫ��ʽ����ջ��
// 
// ���壺
//	�������Ĵ洢�Ͳ����Ƚϼ򵥣����κ���������������໥ת�����Ӷ�������Ĵ洢�Ͳ�����Ϊ���ӵ����⡣
//

/*
* ����˳��洢�Ķ�����
* 
* ���ڴ洢��ȫ����������������������
*/
typedef ElemType SqBiTree[TREE_MAX_SIZE];

/*
* ������ʽ�洢�Ķ�����
* 
* �ɴ洢�������͵Ķ�����
*/
typedef struct BiTNode
{
	ElemType e;
	struct BiTNode* p_lch; // ָ�����ӵ�ָ��
	struct BiTNode* p_rch; // ָ���Һ��ӵ�ָ��
	// struct BiTNode* p_par; // ָ��˫�׵�ָ�룬������а�����ָ�룬������ɵ�����Ϊ��������������Ϊ��������
}BiTNode, *BiTree; // ������ͷָ��Ψһȷ������һ�� BiTNode* ���͵ı������Դ���һ�����������������Խ� BiTNode* ���Ͷ���Ϊ BiTree ���ͣ�����ʹ��

/*
* ��ʼ��
*/
void InitBiTree(BiTree* p_bt);

/*
* ����
*/
void CreateBiTree(BiTree* p_bt, char* p_desc);

/*
* ����
*/
void DestroyBiTree(BiTree* p_bt);

/*
* �������-�ݹ�ʵ��
*/
void PreOrderTraverseRecursively(BiTree bt);

/*
* �������-�ݹ�ʵ��
*/
void InOrderTraverseRecursively(BiTree bt);

/*
* �������-�ݹ�ʵ��
*/
void PostOrderTraverseRecursively(BiTree bt);

/*
* �������
*/
void PreOrderTraverse(BiTree bt);

/*
* �������
*/
void InOrderTraverse(BiTree bt);

/*
* �������
*/
void PostOrderTraverse(BiTree bt);

//
// ����������
// 
// ������
//	���ڶ����������۲������ֱ�����ǰ/��/���򣩣������Եõ��������н���һ���������С�
//	�ڸ������У����׽���⣬ÿ����㶼����ֻ��һ��ֱ��ǰ������β����⣬ÿ����㶼����ֻ��һ��ֱ�Ӻ�̡�
//	��ĳ���㷨����Ҫ��ζԶ��������б���������Ҫ����ջ�ṹ���ظ��ԵĲ������˷���Դ��Ч�ʵ��¡�
//	�ɴ��뵽���ܷ��ڵ�һ�α���ʱ��ʹ�ö������п��е��ڴ�ռ��¼����ǰ���ͺ�̽��λ�ã�
//	����һ���������ٱ���������ʱ���Ϳ��������ѱ����ǰ�������Ϣ����߱���Ч�ʡ�
//	��Ҫ�������ǰ����̣���ֱ�ӵ��뷨���Ǹı���ṹ����������ָ���򣬷ֱ�ָ�����ǰ���ͺ�̡�
//	������������ɿռ��˷ѣ���Ϊ����ʹ�ö�������ʵ�ֵĶ�������˵���ܶ��㶼����ָ�� NULL ��δʹ�õ�ָ����
//	ʵ���ϣ����ں��� n �����Ķ����������ض����� n+1 ����ָ����
//	���ǿ���������Щ��ָ�������洢���֣�����ȫ��������ǰ���ͺ�̡�
//	�ɴ��γɵĶ�����������������������
// 
// ���壺
//	������������ָ���ý��Ŀ�ָ�������洢���֮��ǰ���ͺ�̹�ϵ��һ�������������
// 
// �ص㣺
//	1. ����������ӣ��� p_lch ָ�����ӣ����� p_lch ָ��ý���ֱ��ǰ����
//	2. ��������Һ��ӣ��� p_rch ָ���Һ��ӣ����� p_rch ָ��ý���ֱ�Ӻ�̣�
//	3. Ϊ����ָ����ָ����������������������־�򣬱�����ǰָ����ָ����Ǻ��ӻ���ǰ��/��̡�
// 
// ��������
//	����������ĳ�ֱ�������ת��Ϊ�����������Ĺ��̳�Ϊ�������������ʵ�־����ڱ���������Ϊ��ʶ��ֵ���޸Ŀ�ָ���ָ��
//	��Ҫע�����������ʱ��Ҫ����һ��ָ��ǰ���ǰһ������ָ�룬�����ͨ���ݹ�ʵ�֣���ָ���붨���ڵݹ麯�����⡣
// 
// �����������ĳ�ʼ�������������ٺ���ͨ����������һ�¡�
// 
// ���������������ı�����
//	1. �赱ǰ��� = ����㣻
//	2. ���ʵ�ǰ��㣬����ǰ���Ϊ NULL �����������Ѱ�����̽�㣺
//		(1) ����ǰ�����ָ�������Ǻ�̣��ұ�ʶ���ʶ��̣������赱ǰ��� = ��̽�㣻
//		(2) ����ǰ����ָ�������Һ��ӣ��ұ�ʶ���ʶ�Һ��ӣ�����
//			����ǰ��������ӣ���ǰ���ĺ�̾��������ӣ��赱ǰ��� = ���ӣ�
//			����ǰ��������ӣ���ǰ���ĺ�̾������Һ��ӣ��赱ǰ��� = �Һ��ӣ�
//		(3) ����ǰ�����ָ�������� NULL��˵���ѱ�����ĩβ���赱ǰ��� = NULL��
//	3. �ظ�ִ�� 2 ֱ��������
// 
// ���������������ı�����
//	1. �Ӹ���㿪ʼ���ظ�Ѱ�������ӣ�ֱ��ĳ�����û�����ӣ��赱ǰ��� = �ý�㣻
//	2. ���ʵ�ǰ��㣬����ǰ���Ϊ NULL �����������Ѱ�����̽�㣺
//		(1) ����ǰ�����ָ�������Ǻ�̣��ұ�ʶ���ʶ��̣������赱ǰ��� = ��̽�㣻
//		(2) ����ǰ�����ָ�������Һ��ӣ��ұ�ʶ���ʶ�Һ��ӣ�����
//			���Һ��ӿ�ʼ���ظ�Ѱ�������ӣ�ֱ��ĳ�����û�����ӣ��赱ǰ��� = �ý�㣻
//		(3) ����ǰ�����ָ�������� NULL��˵���ѱ�����ĩβ���赱ǰ��� = NULL��
//	3. �ظ�ִ�� 2 ֱ��������
// 
// ���������������ı�����
//	1. �Ӹ���㿪ʼ���ظ�Ѱ�������ӣ�ֱ��ĳ�����û�����ӣ����ڸý�㣺
//		������ָ����洢���� NULL�����赱ǰ��� = �ý�㣻
//		��������ָ����洢������ǰ�����赱ǰ��� = ǰ����㣻
//	2. ���ʵ�ǰ��㣬����ǰ���Ϊ NULL �����������Ѱ�����̽�㣺��
//		(1) ����ǰ�����ָ�������Ǻ�̣��ұ�ʶ���ʶ��̣������赱ǰ��� = ��̽�㣻
//		(2) ����ǰ�����ָ�������Һ��ӣ��ұ�ʶ���ʶ�Һ��ӣ�����
//			����ǰ����Ǹ������Һ��ӣ����赱ǰ��� = ����㣻
//			����ǰ����Ǹ��������ӣ���
//				�������û���Һ��ӣ����赱ǰ��� = ����㣻
//				����������Һ��ӣ�����Һ��ӿ�ʼ���ظ�Ѱ�������ӣ�ֱ��ĳ�����û�����ӣ����ڸý�㣺
//					������ָ����洢���� NULL�����赱ǰ��� = �ý�㣻
//					��������ָ����洢������ǰ�����赱ǰ��� = ǰ����㣻
//		(3) ����ǰ����Ǹ������������ĸ���㣬���赱ǰ��� = NULL��
//	3. �ظ�ִ�� 2 ֱ��������
//	ע�⣺����������������Ҫ�õ�����㣬��ʹ������������Ϊ�洢�ṹ��
// 
// ��ע��
//	1. ���������������ı���˼·�����ǻ���û������ͷ���������
//	2. ����������������ǰ���ͺ��ָ�룬����ͨ������ͷ��㣨��ָ����ָ���׽�㣨���ӣ�����ָ����ָ��β��㣨����������֧��˫�������
//

/*
* ���ڱ�ʶָ����ָ���ö��
* 
* ʹ��ö�ٲ�һ���ܽ�ʡ�ռ䣬��ͬ�� C �����������ö�ٵ��ڴ���ܲ�ͬ
*/
typedef enum PointerTag
{
	Link, // ��ʾָ����ָ���������
	Thread // ��ʾָ����ָ�������������ǰ�����̣�
}PointerTag;

/*
* ����������
*/
typedef struct BiThrNode
{
	ElemType e;
	PointerTag ltag; // ���ʶ�򣬱�ʶ��ָ��ָ��
	PointerTag rtag; // �ұ�ʶ�򣬱�ʶ��ָ��ָ��
	struct BiThrNode* p_lch; // ��ָ�������ʶ��Ϊ Link ʱָ�����ӣ�Ϊ Thread ʱָ��ǰ��
	struct BiThrNode* p_rch; // ��ָ�����ұ�ʶ��Ϊ Link ʱָ���Һ��ӣ�Ϊ Thread ʱָ����
}BiThrNode, *BiThrTree;

//
// ��������
// 
// ���
//	·����
//		��һ�����У�һ����㵽��һ�����֮���ͨ·����Ϊ·����
//	·�����ȣ�
//		��һ��·���У�����������ÿ����һ����㣬·�����ȼ� 1�������յ��õ��ĳ���ֵ����Ϊ·�����ȣ�
//	����·�����ȣ�
//		�����ĸ���㵽����ÿ������·������֮�ͣ���Ϊ����·�����ȣ�������TL����ȫ��������·��������̵Ķ�������
//	����Ȩ��
//		����㸳һ������ĳ�ֺ������ֵ�������ֵ��Ϊ�ý���Ȩ��
//	���Ĵ�Ȩ·�����ȣ�
//		���ĸ���㵽�ý���·������ x �ý���Ȩ = �ý��Ĵ�Ȩ·�����ȣ�
//	���Ĵ�Ȩ·�����ȣ�
//		��������Ҷ�ӽ��Ĵ�Ȩ·������֮�ͣ���Ϊ���Ĵ�Ȩ·�����ȣ�������WPL��
// 
// ���壺
//	ʹ�� n ������Ȩֵ�Ľ����ΪҶ�ӽ�㹹��һ�ö�Ϊ d ������ֻ�ж�Ϊ d �Ͷ�Ϊ 0 �Ľ�����ʱ��
//	����������������п��ܹ������ͬ�����о�����С��Ȩ·�����ȣ���Ƹ���Ϊ����������Ҳ����������
// 
// ��ע��
//	�����ѧ�й��������ڶ�������Ӧ����㣬����������ָ�Ĺ�����������������˵����ָ��������̬�Ĺ���������
// 
// �洢��
//	ʹ������洢������Ԫ���ǹ���������㣬����ɣ�Ȩֵ��˫��/����/�Һ����������е�λ�ù��ɡ�
// 
// �ص㣺
//	1. ��ͬ�Ĵ�ȨҶ�ӽ�㹹����Ĺ���������Ψһ��������ͬ���Ľ�㣬���ܹ������ͬ��״�ľ�����ͬ��С��Ȩ·�����ȵĶ�������
//	2. �ɹ�������ֻ�ж�Ϊ 2 �Ͷ�Ϊ 0 �Ľ����һ���Կ�֪������ n ��Ҷ�ӽ��Ĺ��������й��� 2n-1 ����㣻
//	3. ȨֵԽ���Ҷ�ӽ�����Խ��������������һ���ǹ���������
// 
// ���췽����
//	1. ����ɭ��ȫ�Ǹ���
//		�� n ������Ȩֵ {W[1], W[2], ..., W[n]} �Ľ�㣬����ɺ��� n �ö�������ɭ�� F��
//		�� F={T[1], T[2], ..., T[n]}��������һ���� T[i] ��ֻ����һ��ȨΪ W[i] �ĸ���㣻
//	2. ѡ����С��������
//		�� F ��Ѱ�Ҹ����Ȩֵ��С�������� T[x] �� T[y]����Ϊ������������һ���µĶ����� T[z]��
//		�����¶����� T[z] ������ȨֵΪ�������������ڵ��Ȩֵ֮�ͣ�
//	3. ɾ����С�����ˣ�
//		�� F ��ɾ�� T[x] �� T[y]�����뽫�¹���Ķ����� T[z]��
//	4. �ظ� 2-3 ��������
//		�ظ����� 2 �� 3��ֱ��ɭ����ֻʣ��һ�ö�����Ϊֹ���ö�������Ϊ����������
// 
// ����������
// 
// ������
//	�����ͨ����ҵ�У�ʹ�ö����ƣ�0, 1����������ʾ�ʹ�����Ϣ��
// 
//	����Ҫ���ݵ��� ABACCDA������ A, B, C, D �ı���ֱ�Ϊ 00, 01, 10, 11������ı���Ϊ��
//	00010010101100�����շ��������յ��ı������а�˳����λһ��������룬���ɵõ����� ABACCDA��
//	�ñ��뷽ʽ��ֱ�ӣ����������еĳ��Ƚϳ����ռ�ռ�ý϶࣬�����ڴ����У�顣
// 
//	Ϊ�˼��ٱ������е��ܳ������Ը��ݵ������ַ�����Ƶ�ʵĲ�ͬ���ó���Ƶ��Խ�ߵ��ַ���Ӧ�ı��볤��Խ�̡�
//	����ڵ��� ABACCDA������ A, B, C, D �ı���ֱ�Ϊ 0, 00, 1, 01������ı���Ϊ��000011010��
//	�������г��ȱ�С�������������Ķ����ԣ���ǰ�������� 00��������Ϊ AA��Ҳ������Ϊ B��
//	��ɶ����Ե�ԭ������ĳ���ַ���A���ı��루0�����Ǳ���ַ���B���ı��루01����ǰ׺��
//	��������Եķ���������Ҫ����һ�ַ��ı��붼��������һ�ַ������ǰ׺����Ϊǰ׺���롣
// 
//	���ϣ�Ϊ�˼��ٱ������еĳ��ȣ�ͬʱ��֤�����Ψһ�ԣ��ڱ���ʱ��Ҫ��������������
//		1. ����Ƶ��Խ�ߵ��ַ���Ӧ�ı��볤��Խ�̣�
//		2. ��һ�ַ��ı��붼��������һ�ַ������ǰ׺��
// 
//	�����Ե����е��ַ���ΪҶ�ӽ�㣨�ַ�����Ƶ����Ϊ���Ȩֵ������������������
//		1. ȨֵԽ��Ľ�㣨����Ƶ��Խ�ߵ��ַ���������Խ����
//		2. ����㵽��һҶ�ӽ���·��Ψһ�Ҳ���������Ҷ�ӽ�㡣
//	Ȼ�󣬽����������н�����������ӵķ�֧�� 0���������Һ��ӵķ�֧�� 1��ÿ��
//	�ַ��ı��뼴�Ӹ���㵽���ַ���Ӧ��Ҷ�ӽ��·���ϵõ��� 0,1 ���У��Դ��γ�
//	�ı�������������ٱ������г����ұ�֤����Ψһ�Ե���������Ҫ��
//	
//	����ʱ���Ա����������ȡ�롣ʹ��ͬһ�ù����������Ӹ���㿪ʼ�����õ������� 0��
//	�������ߣ������� 1���������ߡ�һ������Ҷ�ӽ�㣬�������Ҷ�ӽ���Ӧ���ַ���
//	Ȼ�����´Ӹ���ʼ���ظ��������̣�ֱ���������н��������ɻ����ȷ�ĵ��ġ�
//

/*
* ���������ṹ��
*/
typedef struct HTNode
{
	float weight; // ���Ȩֵ
	int parent; // ������������е�λ��
	int lch; // �����������е�λ��
	int rch; // �Һ����������е�λ��
}HTNode, *HuffmanTree;

/*
* ������������
* 
* warr �Ǵ洢Ҷ�ӽ��Ȩֵ�����飬n ΪҶ�ӽ�����
*/
void CreateHuffmanTree(HuffmanTree* p_ht, float* warr, int n);

/*
* ���ٹ�������
*/
void DestroyHuffmanTree(HuffmanTree* p_ht);

/*
* HuffmanCode ���洢�ַ���Ӧ���� 0,1 ��ɵ��ַ��������飬�� "010"
* 
* ����˵�Ǵ洢ָ�� char ����ָ������飬��Ϊ C ���ַ��������� char ������� '\0' ��β������
*/
typedef char** HuffmanCode;

/*
* ����������
* 
* ht �ǽ��ַ���ΪҶ�ӽ�㡢�ַ�����Ƶ����ΪȨֵ�����Ĺ�������
* p_hc ��ָ��洢�ַ���Ӧ�Ķ����Ʊ����ַ����������ָ�룬*p_hc ���洢�ַ���Ӧ�Ķ����Ʊ����ַ���������
* n ��Ҷ�ӽ�㣨����������ַ�������
*/
void HuffmanCoding(HuffmanTree ht, HuffmanCode* p_hc, int n);

#endif // !_WYL_TREE