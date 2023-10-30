#include "tree.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 定义二叉树基本操作
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void InitBiTree(BiTree* p_bt)
{
	// 初始化，即将头指针设为 NULL
	*p_bt = NULL;
}

void CreateBiTree(BiTree* p_bt, char* p_desc)
{
	// 根据描述 p_desc，构建对应结构的二叉树
	// 
	// 首先，如何描述一棵二叉树？
	//	一般是借助广义表的定义，使用括号表示法来描述二叉树。
	//	即：根(左子树,右子树)，其中左右子树又各自用“根(左子树,右子树)”表示，直至叶子结点。
	//	如：A(B(D(,G),E),C(F,)) 表示 A 有左右子树 BC；B 有左右子树 DE，C 有左子树 F 且 F 为叶子；D 有右子树 G 且 G 为叶子。
	// 
	// 然后，如何根据描述完成构建？
	//	基于二叉树的特点以及括号表示法的规律，可以借助栈来实现二叉树的构建。
	//	(1) 初始化栈 stack，变量 ch 表示 p_desc 中的字符，变量 k 表示当前需要构建左子树（0）还是右子树（1）。
	//	(2) 遍历 p_desc，依次将每个字符写入 ch：
	//		若 ch 为字母，则创建一个二叉树结点，并判断：
	//			若当前二叉树为空树，则将该结点设为二叉树根节点；
	//			若当前二叉树不为空，根据 k 值将该结点设置为栈顶结点的左或右孩子；
	//		若 ch 为左括号 (，则设 k = 0，表示之后的结点将作为之前结点的左孩子，并将之前的结点入栈；
	//		若 ch 为逗号 ,，则设 k = 1，表示之后的结点将作为之前结点的右孩子；
	//		若 ch 为右括号 )，表明以当前栈顶结点为根的（子）二叉树已构建完毕，将栈顶结点出栈。

	SeqStack stack;
	InitSeqStack(&stack);

	char ch;
	int k = -1; // 0左 1右
	BiTNode* p_new = NULL; // 遍历字符串遇到字母时创建的结点
	BiTNode* p_top = NULL; // 用作（子）二叉树根节点的当前栈顶结点
	for (int i = 0; p_desc[i] != '\0'; i++)
	{
		ch = p_desc[i];
		switch (ch)
		{
			case '(':
				k = 0;
				Push(&stack, (ElemType)p_new);
				break;
			case ',':
				k = 1;
				break;
			case ')':
			{
				k = -1;
				ElemType e;
				Pop(&stack, &e);
				break;
			}
			default:
			{
				p_new = (BiTNode*)malloc(sizeof(BiTNode));
				if (p_new == NULL)
				{
					printf("Error: -- CreateBiTree -- fail to allc memory.\n");
					exit(EXIT_FAILURE);
				}
				p_new->e = ch;
				p_new->p_lch = NULL;
				p_new->p_rch = NULL;

				if (*p_bt == NULL) // 头指针（*p_bt）唯一确定二叉链表，头指针为 NULL，说明是空链表，即空二叉树
				{
					*p_bt = p_new;
				}
				else // 头指针不为 NULL，说明正在构建以栈顶结点为根的（子）二叉树
				{
					GetTop(stack, (ElemType*)(&p_top));
					if (k == 0)
					{
						p_top->p_lch = p_new;
					}
					else if (k == 1)
					{
						p_top->p_rch = p_new;
					}
				}

				break;
			}
		}
	}

	DestroySeqStack(&stack);
}

void DestroyBiTree(BiTree* p_bt)
{
	// 递归销毁，思路清晰，实现简单，缺点是需使用大量栈空间
	BiTree bt = *p_bt;
	if (bt != NULL)
	{
		DestroyBiTree(&(bt->p_lch));
		DestroyBiTree(&(bt->p_rch));
		free(bt);
		bt = NULL;
	}
}

void PreOrderTraverseRecursively(BiTree bt)
{
	// 先序遍历二叉树，递归遍历，思路清晰，实现简单，缺点是需使用大量栈空间
	// 
	// 若二叉树为空，则空操作，否则：
	//	1. 访问根结点
	//	2. 先序遍历左子树
	//	3. 先续遍历右子树

	if (bt)
	{
		printf("%c", (int)bt->e);
		PreOrderTraverseRecursively(bt->p_lch);
		PreOrderTraverseRecursively(bt->p_rch);
	}
}

void InOrderTraverseRecursively(BiTree bt)
{
	// 中序遍历二叉树，递归遍历，思路清晰，实现简单，缺点是需使用大量栈空间
	// 
	// 若二叉树为空，则空操作，否则：
	//	1. 中序遍历左子树
	//	2. 访问根结点
	//	3. 中续遍历右子树

	if (bt)
	{
		InOrderTraverseRecursively(bt->p_lch);
		printf("%c", (int)bt->e);
		InOrderTraverseRecursively(bt->p_rch);
	}
}

void PostOrderTraverseRecursively(BiTree bt)
{
	// 后序遍历二叉树，递归遍历，思路清晰，实现简单，缺点是需使用大量栈空间
	// 
	// 若二叉树为空，则空操作，否则：
	//	1. 后序遍历左子树
	//	2. 后续遍历右子树
	//	3. 访问根结点

	if (bt)
	{
		PostOrderTraverseRecursively(bt->p_lch);
		PostOrderTraverseRecursively(bt->p_rch);
		printf("%c", (int)bt->e);
	}
}

void PreOrderTraverse(BiTree bt)
{
	// 先序遍历二叉树，非递归遍历，需显式借助栈实现
	// 
	// 1. 设当前结点为根结点；
	// 2. 若当前结点不为 NULL，则:
	//		(1) 访问当前结点;
	//		(2) 若当前结点有右孩子，则当前结点入栈；
	//		(3) 将当前结点设为其左孩子;
	// 3. 若当前结点为 NULL 且栈不为空，则：
	//		(1) 将当前结点设为栈顶结点的右孩子；
	//		(2) 将栈顶结点出栈；
	// 4. 重复 2-3 直至当前结点为 NULL 且栈为空。

	SeqStack stack;
	InitSeqStack(&stack);

	BiTNode* p_cur = bt;
	while (p_cur || !IsStackEmpty(stack))
	{
		if (p_cur)
		{
			printf("%c", (int)p_cur->e);
			if (p_cur->p_rch)
			{
				Push(&stack, (ElemType)p_cur);
			}
			p_cur = p_cur->p_lch;
		}
		else
		{
			Pop(&stack, (ElemType*)(&p_cur));
			p_cur = p_cur->p_rch;
		}
	}

	DestroySeqStack(&stack);
}

void InOrderTraverse(BiTree bt)
{
	// 中序遍历二叉树，非递归遍历，需显式借助栈实现
	// 
	// 1. 设当前结点为根结点；
	// 2. 若当前结点不为 NULL，则:
	//		(1) 将当前结点入栈；
	//		(2) 将当前结点设为其左孩子;
	// 3. 若当前结点为 NULL 且栈不为空，则：
	//		(1) 访问栈顶结点；
	//		(2) 将当前结点设为栈顶结点的右孩子；
	//		(3) 将栈顶结点出栈；
	// 4. 重复 2-3 直至当前结点为 NULL 且栈为空。

	SeqStack stack;
	InitSeqStack(&stack);

	BiTNode* p_cur = bt;
	while (p_cur || !IsStackEmpty(stack))
	{
		if (p_cur)
		{
			Push(&stack, (ElemType)p_cur);
			p_cur = p_cur->p_lch;
		}
		else
		{
			Pop(&stack, (ElemType*)(&p_cur));
			printf("%c", (int)p_cur->e);
			p_cur = p_cur->p_rch;
		}
	}

	DestroySeqStack(&stack);
}

void PostOrderTraverse(BiTree bt)
{
	// 后序遍历二叉树，非递归遍历，需显式借助栈实现
	// 
	// 1. 设当前结点为根结点；
	// 2. 若当前结点不为 NULL，则:
	//		(1) 将当前结点入栈；
	//		(2) 将当前结点设为其左孩子;
	// 3. 若当前结点为 NULL 且栈不为空，则：
	//		(1) 获取栈顶结点；
	//		(2) 判断：栈顶结点有右孩子且右孩子不是上次出栈的结点：
	//			若是，则将当前结点设为栈顶结点的右孩子；
	//			若否，则访问栈顶结点，将栈顶结点出栈，更新上次出栈结点；
	// 4. 重复 2-3 直至当前结点为 NULL 且栈为空。

	SeqStack stack;
	InitSeqStack(&stack);

	BiTNode* p_cur = bt;
	BiTNode* p_top = NULL; // 栈顶结点
	BiTNode* p_prev = NULL; // 上次出栈结点
	while (p_cur || !IsStackEmpty(stack))
	{
		if (p_cur)
		{
			Push(&stack, (ElemType)p_cur);
			p_cur = p_cur->p_lch;
		}
		else
		{
			GetTop(stack, (ElemType*)(&p_top));
			if (p_top->p_rch && p_top->p_rch != p_prev)
			{
				p_cur = p_top->p_rch;
			}
			else
			{
				printf("%c", (int)p_top->e);
				Pop(&stack, (ElemType*)(&p_prev));
			}
		}
	}

	DestroySeqStack(&stack);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 定义哈夫曼树相关操作
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
* 寻找森林中权值最小的两个根节点的位置
* 
* 该方法用于辅助创建哈夫曼树，end 是本次查找的结束索引值，p_left、p_right 分别是指向存储权值最小的两个根节点位置的指针
* 
*/
void SeekTowMin(HuffmanTree htarr, int end, int* p_left, int* p_right)
{
	// 首先，寻找两个根结点（即 parent 为无效索引）并保存下来；
	// 然后，继续寻找剩余的根结点，并比较根结点权值：
	//	若权值比之前的两个都小，则将之前较大的替换为之前较小的，然后将该结点设为较小的；
	//	若权值位于之前两个之间，则将之前较大的替换为该结点；
	// 重复寻找剩余根结点并进行比较，直至结束。
	
	float ml, mr; // 比较所有根结点权值，得到的两个最小的权值，且 ml <= mr

	int i = 0;

	// 找到第一个根结点，记录权值及结点位置
	while (i <= end && htarr[i].parent != -1)
	{
		i++; // 若结点的 parant != -1，说明其不是根结点，继续寻找
	}
	ml = htarr[i].weight;
	*p_left = i;

	// 找到第二个根结点，同第一个根结点权值比较后，再记录权值和结点位置，确保 ml <= mr
	i++;
	while (i <= end && htarr[i].parent != -1)
	{
		i++;
	}
	if (htarr[i].weight < ml)
	{
		mr = ml;
		*p_right = *p_left;
		ml = htarr[i].weight;
		*p_left = i;
	}
	else
	{
		mr = htarr[i].weight;
		*p_right = i;
	}

	// 继续寻找根结点，然后同前两个根结点权值比较
	while (++i <= end && htarr[i].parent == -1)
	{
		// 若权值比之前两个都小，则先将 mr 和 p_right 分别设为 ml 和 p_left，再将 ml 和 p_left 分别设为该权值及结点位置
		if (htarr[i].weight < ml)
		{
			mr = ml;
			*p_right = *p_left;
			ml = htarr[i].weight;
			*p_left = i;
		}
		// 若权值位于前两个之间，则将 mr 和 p_right 分别设为该权值及结点位置
		else if (htarr[i].weight >= ml && htarr[i].weight < mr)
		{
			mr = htarr[i].weight;
			*p_right = i;
		}
	}
}

void CreateHuffmanTree(HuffmanTree* p_ht, float* warr, int n)
{
	// 四步法构建哈夫曼树
	// 
	// 使用四步法，对应到实际的编码中，就是：
	//	1. 初始化一个长度为 2n-1 的数组，用于存储哈夫曼树的全部结点（具有 n 个叶子结点的哈夫曼树共有 2n-1 个结点）；
	//	2. 根据叶子结点权值数组 warr，初始化数组的前 n 个结点，其双亲/左孩子/右孩子位置均设为无效值 -1；（构造森林全是根）
	//	3. 从数组前 n 个结点中，寻找权值最小的两个根（双亲位置为 -1）结点，设为 L 和 R；
	//	4. 初始化数组第 n + 1 个结点，设为 P，其权值为 L 和 R 权值之和，双亲位置设为 -1；（3-4 选用两小造新树）
	//	5. 将 P 的左右孩子分别设为 L 和 R，同时将 L 和 R 的双亲设为 P，；（删除两小添新人）
	//	6. 将 n 加 1，重复直至数组满。（重复 2-3 至单根）

	// 初始化用于存储哈夫曼树结点的数组
	// 注意：p_ht 为指向待构建的哈夫曼树的指针，*p_ht 即哈夫曼树本身，它是一个存储树中全部结点的数组
	int m = 2 * n - 1;
	*p_ht = (HuffmanTree)malloc(sizeof(HTNode) * m);
	if (*p_ht == NULL)
	{
		printf("Error: -- CreateHuffmanTree -- fail to alloc memory.\n");
		exit(EXIT_FAILURE);
	}
	
	// 初始化 n 个已知的叶子结点
	for (int i = 0; i < n; i++)
	{
		(*p_ht)[i].weight = warr[i];
		(*p_ht)[i].parent = -1;
		(*p_ht)[i].lch = -1;
		(*p_ht)[i].rch = -1;
	}

	// 逐个初始化剩余的 n-1 个结点
	for (int i = n; i < m; i++)
	{
		// 寻找已初始化结点中权值最小的两个根结点位置
		int ml, mr;
		SeekTowMin(*p_ht, i - 1, &ml, &mr);
		// 新初始化一个结点
		(*p_ht)[i].weight = (*p_ht)[ml].weight + (*p_ht)[mr].weight;
		(*p_ht)[i].parent = -1;
		(*p_ht)[i].lch = ml;
		(*p_ht)[i].rch = mr;
		// 将两个最小结点的双亲设为新初始化的结点
		(*p_ht)[ml].parent = (*p_ht)[mr].parent = i;
	}
}

void DestroyHuffmanTree(HuffmanTree* p_ht)
{
	free((*p_ht)); // p_ht 为指向待构建的哈夫曼树的指针，*p_ht 即哈夫曼树本身，它是一个存储树中全部结点的数组
}

void HuffmanCoding(HuffmanTree ht, HuffmanCode* p_hc, int n)
{
	// 从哈夫曼树 ht 的叶子结点开始，寻找根结点
	// 此方式对比从根结点开始寻找叶子结点，代码更少，但得到的编码是逆序的，存储时要倒序存储

	// p_hc 是指向存储字符对应的二进制编码字符串的数组的指针，*p_hc 即存储字符对应的二进制编码字符串的数组
	(*p_hc) = (HuffmanCode)malloc(sizeof(char*) * n);
	if (*p_hc == NULL)
	{
		printf("Error: -- HuffmanCoding -- fail to alloc memory.\n");
		exit(EXIT_FAILURE);
	}

	// cstr 为当前字符对应的二进制编码字符串，注意 C 中的字符串即由字符组成且以 '\0' 结尾的数组
	// 设存储字符串的数组长度为 n，因为 n 个字符在保证编码唯一的前提下每个字符编码最大长度不会超过 n
	char* cstr = (char*)malloc(sizeof(char) * n);
	if (cstr == NULL)
	{
		printf("Error: -- HuffmanCoding -- fail to alloc memory.\n");
		exit(EXIT_FAILURE);
	}
	cstr[n - 1] = '\0';

	// ht 实际是存放哈夫曼树结点的数组，根据其构建函数可知，前 n 个结点存储的是叶子结点
	for (int i = 0; i < n; i++)
	{
		int start = n - 1; // 从叶子结点出发得到的编码字符串是逆序的，存储时也要逆序

		int cpos = i; // 从叶子结点开始寻找根结点过程中，每次访问的结点在数组中的位置
		int ppos = ht[cpos].parent;// 每次访问的结点的父结点在数组中的位置

		// 寻找根结点
		while (ppos != -1)
		{
			// 如果本次访问结点是其父结点的左孩子，则路径编码为 '0'
			if (ht[ppos].lch == cpos)
			{
				cstr[--start] = '0';
			}
			// 否则为 '1'
			else
			{
				cstr[--start] = '1';
			}
			// 设本次访问结点为其父结点，继续寻找根结点
			cpos = ppos;
			ppos = ht[cpos].parent;
		}

		// 找到根结点，则位置为 i 的叶子结点对应的编码已形成
		(*p_hc)[i] = (char*)malloc(sizeof(char) * (n - start));
		strcpy((*p_hc)[i], &cstr[start]);
	}

	free(cstr);
}
