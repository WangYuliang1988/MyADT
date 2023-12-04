#include "search.h"

int SearchSeq(SSTable st, ElemType key)
{
	// 插入监视哨，用于提升查找效率
	st.earr[st.length] = key;

	// 查找指定元素
	int i;
	for (i = 0; key != st.earr[i] ; i++);
	
	// 返回查找结果
	if (i == st.length) return -1;
	return i;
}

int SearchBin(SSTable st, ElemType key)
{
	// 前提：SSTable 有序

	int low = 0, high = st.length - 1;
	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (key < st.earr[mid])
		{
			high = mid - 1;
		}
		else if (key > st.earr[mid])
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

int SearchBlk(SSTable st, ElemType key)
{
	// 前提：SSTable 分块有序
	
	// 假设查找表按 3 个元素为一个子表分块有序
	int itemc = 3, blockc = (st.length / itemc) + (st.length % itemc == 0 ? 0 : 1);
	Index* idxarr = (Index*)malloc(sizeof(Index) * blockc);
	if (idxarr == NULL)
	{
		printf("Error: -- SearchBlk -- fail to alloc memory.\n");
	}

	// 划分子表，建立索引
	int max = -1, start = 0, arri = 0;
	for (int i = 0; i < st.length; i++)
	{
		if (st.earr[i] > max)
		{
			max = (int)st.earr[i];
		}

		if ((i + 1) % itemc == 0 || i == st.length - 1)
		{
			idxarr[arri].max = max;
			idxarr[arri].start = start;
			start = i + 1;
			arri++;
		}
	}

	// 二分查找索引表，确定子表
	int low = 0, high = blockc;
	while (low < high) // 二分查找进行到 low 和 high 指向同一个索引时，该索引对应子表即为目标子表
	{
		int mid = (low + high) / 2;
		if (key > idxarr[mid].max)
		{
			low = mid + 1;
		}
		else
		{
			high = mid; // key 小于或等于索引的最大值时，key 都可能存在于该索引对应的子表内
		}
	}
	int starti = -1;
	if (low == high)
	{
		starti = idxarr[low].start;
	}

	// 顺序查找子表，返回目标元素位置
	int keypos = -1;
	if (starti > -1)
	{
		for (int i = starti; i < starti + itemc && i < st.length; i++)
		{
			if (st.earr[i] == key)
			{
				keypos = i;
				break;
			}
		}
	}
	free(idxarr);
	return keypos;
}

/*
* 构造次优二叉树
* 
* swarr 是关键字的概率累积和的集合
* 
* low 和 high 分别表示本次构建所用的有序表的起始和结束位置
*/
void CreateOptimal(BiTree* p_bt, ElemType karr[], float swarr[], int low, int high)
{
	// 寻找本次构建所用的有序表中具有最小左右概率之和差值的关键字。
	// 
	// 若采用直接的方式计算关键字 k 左右概率之和的差值，每次递归都需要使用双层循环。
	// 
	// 为提升算法效率，引入关键字的概率累积和（sw）概念：设 w 为关键字 k 的查询概率，则：
	//		sw[k] = w[0] + w[1] +...+ w[k] = sw[k-1] + w[k]。
	// 
	// 计算 k 左右概率之和的差值时，设给定有序表的起始位置为 l，结束位置为 h，则：
	//		diff[k] = |(w[k+1] +...+ w[h]) - (w[l] +...+ w[k-1])|
	//				= |(sw[h] - sw[k]) - (sw[k-1] - sw[l-1])|
	//				= |sw[h] + sw[l-1] - sw[k] - sw[k-1]
	// 
	// 注意当 k 或 l 小于 1 时， sw[l-1] 或 sw[k-1] 不参与运算。
	int midx = -1;
	float mind = (float)INFINITY;
	float stad = low < 1 ? swarr[high] : swarr[high] + swarr[low - 1];
	for (int i = low; i <= high; i++)
	{
		float vard = i < 1 ? stad - swarr[i] : stad - swarr[i] - swarr[i - 1];
		vard = vard < 0 ? -1 * vard : vard; // 取差值的绝对值
		if (vard < mind)
		{
			mind = vard;
			midx = i;
		}
	}

	// 将找到的具有最小左右概率之和差值的关键字作为本次构造出的根结点
	// 然后以该关键字做分割，将有序表划分为左右两个子有序表，递归构建本次根结点的左右子树
	*p_bt = (BiTree)malloc(sizeof(BiTNode));
	if (*p_bt == NULL) {
		printf("Error: -- CreateOptimal -- fail to alloc memory.\n");
		return;
	}
	(*p_bt)->e = midx; // 注意结点存储的是关键字在有序表中的位置，而不是关键字本身

	if (midx > low)
	{
		CreateOptimal(&((*p_bt)->p_lch), karr, swarr, low, midx - 1);
	}
	else
	{
		(*p_bt)->p_lch = NULL;
	}
	if (midx < high)
	{
		CreateOptimal(&((*p_bt)->p_rch), karr, swarr, midx + 1, high);
	}
	else
	{
		(*p_bt)->p_rch = NULL;
	}
}

/*
* 先序遍历次优二叉树，寻找指定关键字的位置
*/
int PreSearchOptiTree(BiTree bt, ElemType karr[], ElemType key)
{
	if (!bt)
	{
		return -1;
	}
	else if (key == karr[bt->e])
	{
		return (int)bt->e;
	}
	else
	{
		int pos = PreSearchOptiTree(bt->p_lch, karr, key);
		if (pos == -1)
		{
			pos = PreSearchOptiTree(bt->p_rch, karr, key);
		}
		return pos;
	}
}

int SearchOpt(ElemType karr[], float parr[], int len, ElemType key)
{
	// 前提：karr 有序且关键字的查询概率不等

	// 计算各关键字的概率累积和
	float* swarr = (float*)malloc(sizeof(float) * len);
	if (swarr == NULL)
	{
		printf("Error: -- SearchOpt -- fail to alloc memory.\n");
		return - 1;
	}
	swarr[0] = parr[0];
	for (int i = 1; i < len; i++)
	{
		swarr[i] = swarr[i - 1] + parr[i];
	}

	// 构建次优查找树
	BiTree bt;
	CreateOptimal(&bt, karr, swarr, 0, len - 1);

	// 先序遍历次优查找树，找出 key 所在位置
	free(swarr);
	return PreSearchOptiTree(bt, karr, key);
}

void SearchBST(BiTree bt, ElemType key, BiTree* p_pos)
{
	while (bt)
	{
		if (key == bt->e)
		{
			(*p_pos) = bt;
			break;
		}
		else if (key < bt->e)
		{
			bt = bt->p_lch;
		}
		else
		{
			bt = bt->p_rch;
		}
	}
}

void InsertBST(BiTree* p_bt, ElemType key)
{
	// 若当前树为空树，则直接添加 key 为当前树的根结点
	if (!(*p_bt))
	{
		(*p_bt) = (BiTree)malloc(sizeof(BiTNode));
		if ((*p_bt) == NULL)
		{
			printf("Error: -- InsertBST -- fail to alloc memory.\n");
			return;
		}
		(*p_bt)->e = key;
		(*p_bt)->p_lch = NULL;
		(*p_bt)->p_rch = NULL;
	}
	else if (key == (*p_bt)->e)
	{
		printf("Error: -- InsertBST -- %lld is alreay in this BST.\n", key);
	}
	// 若 key 小于当前结点的值，说明需将 key 插入到当前结点的左子树中
	else if (key < (*p_bt)->e)
	{
		InsertBST(&((*p_bt)->p_lch), key);
	}
	// 若 key 大于当前结点的值，说明需将 key 插入到当前结点的右子树中
	else
	{
		InsertBST(&((*p_bt)->p_rch), key);
	}
}

/*
* DeleteBST 的辅助函数，用于删除 BST 中的结点
*/
void DelBstNode(BiTree* p_bt)
{
	// 注意：待删除的结点是 *p_bt

	// 待删除的结点为叶子结点，直接删除
	if ((*p_bt)->p_lch == NULL && (*p_bt)->p_rch == NULL)
	{
		(*p_bt) = NULL;
		free((*p_bt));
	}
	// 待删除结点只有一个左孩子，用左孩子代替待删除结点
	else if ((*p_bt)->p_lch != NULL && (*p_bt)->p_rch == NULL)
	{
		BiTNode* p_n = (*p_bt);
		(*p_bt) = (*p_bt)->p_lch;
		free(p_n);
	}
	// 待删除结点只有一个右孩子，用右孩子代替待删除结点
	else if ((*p_bt)->p_rch == NULL && (*p_bt)->p_rch != NULL)
	{
		BiTNode* p_n = (*p_bt);
		(*p_bt) = (*p_bt)->p_rch;
		free(p_n);
	}
	// 待删除结点有两个孩子，需找到待删结点在中序序列下的直接前驱，将前驱结点的值复制给待删结点，再删除直接前驱
	else
	{
		BiTNode* p_pre = NULL; // 待删结点的直接前驱
		BiTNode* p_pre_par = NULL; // 直接前驱的父结点

		// 寻找待删结点中序序列下的直接前驱
		// 二叉排序树中，拥有两个孩子的结点在中序序列下的直接前驱，肯定在该结点的左子树中
		// 同时，该前驱结点要么是叶子结点，要么只有左孩子，换言之，前驱结点肯定没有右孩子
		// 在待删结点的左子树中，从根结点开始，第一个没有右孩子的结点，就是待删结点的前驱
		p_pre_par = (*p_bt);
		p_pre = (*p_bt)->p_lch;
		while (p_pre->p_rch)
		{
			p_pre_par = p_pre;
			p_pre = p_pre->p_rch;
		}

		// 将前驱结点的值复制给待删结点，删除待删结点转为删除前驱结点
		(*p_bt)->e = p_pre->e;

		// 删除前驱结点
		// 前驱结点要么是叶子结点，要么只有左孩子
		// 若是叶子结点，则根据前驱结点是其父结点的左（右）孩子，将父结点的左（右）孩子设为 NULL
		// 若只有左孩子，则根据前驱结点是其父结点的左（右）孩子，将父结点的左（右）孩子设为前驱结点的左孩子
		// 综合上面两个判断，可以用只有左孩子的逻辑，覆盖是叶子结点时的逻辑，因为前驱结点是叶子结点时，其左孩子就是 NULL
		if (p_pre == p_pre_par->p_lch)
		{
			p_pre_par->p_lch = p_pre->p_lch;
		}
		else
		{
			p_pre_par->p_rch = p_pre->p_lch;
		}
		free(p_pre);
	}
}

void DeleteBST(BiTree* p_bt, ElemType key)
{
	// 如果当前树不存在，删除失败
	if (!(*p_bt))
	{
		return;
	}
	else if ((*p_bt)->e == key)
	{
		DelBstNode(p_bt);
	}
	// 如果 key 小于当前结点的值，说明需到当前结点的左子树进行删除
	else if (key < (*p_bt)->e)
	{
		DeleteBST(&((*p_bt)->p_lch), key);
	}
	// 如果 key 大于当前结点的值，说明需到当前结点的右子树进行删除
	else
	{
		DeleteBST(&((*p_bt)->p_rch), key);
	}
}

void LeftRotate(AVLTree* p_avt)
{
	// 设根结点为 P，P 的左孩子为 L，P 的右孩子为 R
	// 
	// 左旋：P 作为 R 的左孩子，R 原来的左孩子作为 P 的右孩子，L 依然为 P 的左孩子，R 代替 P 成为根结点

	AVLNode* p_r = (*p_avt)->p_rch;
	(*p_avt)->p_rch = p_r->p_lch;
	p_r->p_lch = (*p_avt);
	(*p_avt) = p_r;
}

void RightRotate(AVLTree* p_avt)
{
	// 设根结点为 P，P 的左孩子为 L，P 的右孩子为 R
	//
	// 右旋：P 作为 L 的右孩子，L 原来的右孩子作为 P 的左孩子，R 依然为 P 的右孩子，L 代替 P 成为根结点

	AVLNode* p_l = (*p_avt)->p_lch;
	(*p_avt)->p_lch = p_l->p_rch;
	p_l->p_rch = (*p_avt);
	(*p_avt) = p_l;
}

void LeftBalance(AVLTree* p_avt)
{
	// 树 p_avt 因其左子树插入结点导致失衡（即 p_avt 根结点的平衡因子为 2），需旋转以恢复平衡。
	// 
	// 设 p_avt 根结点为 P，P 的左孩子为 L，则：
	//	若 L 的平衡因子为 1，说明插入的结点位于 L 的左子树，即 LL 型失衡，需对 P 右旋；
	//	若 L 的平衡因子为 -1，说明插入的结点位于 L 的右子树，即 LR 型失衡，需先对 L 左旋，再对 P 右旋。
	// 
	// 注：根据插入函数 InsertAVL，对结点 P 的左子树插入结点导致失衡时，P 的左孩子 L 的平衡因子只会是 1 或 -1。
	
	AVLTree lch = (*p_avt)->p_lch;
	if (lch->bf == 1)
	{
		// P 右旋：
		//	P 的左子树深度将减 2，P 的平衡因子将变为 0；
		//	L 的右子树深度将加 1，L 的平衡因子将变为 0。
		(*p_avt)->bf = lch->bf = 0;

		RightRotate(p_avt);
	}
	else if (lch->bf == -1)
	{
		// 设 R' 是 L 左旋前的右孩子，则：
		// 
		// 先 L 左旋：
		//	若 R' 的平衡因子是 1，则 L 的右子树深度将减 1，L 的平衡因子将变为 0；
		//	若 R' 的平衡因子是 0，则 L 的右子树深度将减 1，L 的平衡因子将变为 0；
		//	若 R' 的平衡因子是 -1，则 L 的右子树深度将减 2，L 的平衡因子将变为 1；
		// 
		// 后 P 右旋：
		//	若 R' 的平衡因子是 1，则 P 的左子树深度将减 3，P 的平衡因子将变为 -1；
		//	若 R' 的平衡因子是 0，则 P 的左子树深度将减 2，P 的平衡因子将变为 0；
		//	若 R' 的平衡因子是 -1，则 P 的左子树深度将减 2，P 的平衡因子将变为 0；
		// 
		// 旋转完后，R' 将成为新的根结点，且其平衡因子为 0。

		AVLTree lrch = lch->p_rch;
		if (lrch->bf == 1)
		{
			lch->bf = 0;
			(*p_avt)->bf = -1;
		}
		else if (lrch->bf == 0)
		{
			lch->bf = (*p_avt)->bf = 0;
		}
		else if (lrch->bf == -1)
		{
			lch->bf = 1;
			(*p_avt)->bf = 0;
		}
		lrch->bf = 0;

		LeftRotate(&((*p_avt)->p_lch));
		RightRotate(p_avt);
	}
}

void RightBalance(AVLTree* p_avt)
{
	// 树 p_avt 因其右子树插入结点导致失衡（即 p_avt 根结点的平衡因子为 -2），需旋转以恢复平衡。
	//
	// 设 p_avt 根结点为 P，P 的左孩子为 R，则：
	//	若 R 的平衡因子为 -1，说明插入的结点位于 R 的右子树，即 RR 型失衡，需对 P 左旋；
	//	若 R 的平衡因子为 1，说明插入的结点位于 R 的左子树，即 RL 型失衡，需先对 R 右旋，再对 P 左旋。
	// 
	// 注：根据插入函数 InsertAVL，对结点 P 的右子树插入结点导致失衡时，P 的右孩子 R 的平衡因子只会是 1 或 -1。

	AVLTree rch = (*p_avt)->p_rch;
	if (rch->bf == -1)
	{
		// P 左旋：
		//	P 的右子树深度将减 2，P 的平衡因子将变为 0；
		//	R 的左子树深度将加 1，R 的平衡因子将变为 0。
		(*p_avt)->bf = rch->bf = 0;

		LeftRotate(p_avt);
	}
	else if (rch->bf == 1)
	{
		// 设 L' 是 R 右旋前的左孩子，则：
		// 
		// 先 R 右旋：
		//	若 L' 的平衡因子是 1，则 R 的左子树深度将减 2，R 的平衡因子将变为 -1；
		//	若 L' 的平衡因子是 0，则 R 的左子树深度将减 1，R 的平衡因子将变为 0；
		//	若 L' 的平衡因子是 -1，则 R 的左子树深度将减 1，R 的平衡因子将变为 0；
		// 
		// 后 P 左旋：
		//	若 L' 的平衡因子是 1，则 P 的右子树深度将减 2，P 的平衡因子将变为 0；
		//	若 L' 的平衡因子是 0，则 P 的右子树深度将减 2，P 的平衡因子将变为 0；
		//	若 L' 的平衡因子是 -1，则 P 的右子树深度将减 3，P 的平衡因子将变为 1；
		// 
		// 旋转完后，L' 将成为新的根结点，且其平衡因子为 0。

		AVLTree rlch = rch->p_lch;
		if (rlch->bf == 1)
		{
			rch->bf = -1;
			(*p_avt)->bf = 0;
		}
		else if (rlch->bf == 0)
		{
			rch->bf = (*p_avt)->bf = 0;
		}
		else if (rlch->bf == -1)
		{
			rch->bf = 0;
			(*p_avt)->bf = 1;
		}
		rlch->bf = 0;

		RightRotate(&((*p_avt)->p_rch));
		LeftRotate(p_avt);
	}
}

int InsertAVL(AVLTree* p_avt, ElemType e, int* p_deeper)
{
	// 如果树为空树，则直接添加 e 为根结点
	if (!(*p_avt))
	{
		(*p_avt) = (AVLTree)malloc(sizeof(AVLNode));
		if ((*p_avt) == NULL)
		{
			printf("Error: -- InsertAVL -- fail to alloc memory.\n");
			return 0;
		}
		(*p_avt)->e = e;
		(*p_avt)->p_lch = NULL;
		(*p_avt)->p_rch = NULL;
		(*p_avt)->bf = 0;

		// p_deeper 指针指向的值，始终标识本次插入对应的 p_avt 树的深度是否增加。因为本次插入对应的 p_avt
		// 是空树，深度为 0，插入后树拥有一个结点，深度变为 1。插入后深度有增加，所以 (*p_deeper) 设为真值。
		// 
		// 同时，因为该插入函数是递归函数，本次插入的结点，可能是上层某个结点的子结点，本层树深度的变化，可能
		// 会影响上层树的深度。因此，在本次插入返回后，外层调用还要判断其对应层次的 p_avt 树的深度是否增加，
		// 并设置对应的 (*p_deeper) 值。因此，(*p_deeper) 始终标识本次插入对应的 p_avt 的深度是否增加。
		(*p_deeper) = 1;
	}
	else if (e == (*p_avt)->e)
	{
		printf("Error: -- InsertAVL -- %lld is alreay in this AVL.\n", e);
		return 0;
	}
	// 若待插值小于当前结点值，则需插入当前结点的左子树中
	else if (e < (*p_avt)->e)
	{
		int rs = InsertAVL(&((*p_avt)->p_lch), e, p_deeper);

		// 若左子树插入失败，则本次插入也告失败
		if (!rs)
		{
			return 0;
		}
		// 若左子树插入成功，则看插入后左子树的深度是否增加：
		// 若有增加，则需根据当前结点的平衡因子再次进行判断：
		//		若平衡因子为 1，则插入后平衡因子将变为 2，需旋转以保持平衡；
		//		若平衡因子为 0，则更新平衡因子为 1，并设 (*p_deeper) 为真；
		//		若平衡因子为 -1，则更新平衡因子为 0，并设 (*p_deeper) 为假；
		// 若无增加，则插入操作结束。
		else if (*p_deeper)
		{
			if ((*p_avt)->bf == 1)
			{
				LeftBalance(p_avt);
				(*p_deeper) = 0;
			}
			else if ((*p_avt)->bf == 0)
			{
				(*p_avt)->bf = 1;
				(*p_deeper) = 1;
			}
			else
			{
				(*p_avt)->bf = 0;
				(*p_deeper) = 0;
			}
		}
		return 1;
	}
	// 若待插值大于当前结点值，则需插入当前结点的右子树中
	else
	{
		int rs = InsertAVL(&((*p_avt)->p_rch), e, p_deeper);

		// 若右子树插入失败，则本次插入也告失败
		if (!rs)
		{
			return 0;
		}
		// 若右子树插入成功，则看插入后右子树的深度是否增加：
		// 若有增加，则需根据当前结点的平衡因子再次进行判断：
		//		若平衡因子为 1，则更新平衡因子为 0，并设 (*p_deeper) 为假；
		//		若平衡因子为 0，则更新平衡因子为 1，并设 (*p_deeper) 为真；
		//		若平衡因子为 -1，则插入后平衡因子将变为 -2，需旋转以保持平衡；
		// 若无增加，则插入操作结束。
		else if (*p_deeper)
		{
			if ((*p_avt)->bf == 1)
			{
				(*p_avt)->bf = 0;
				(*p_deeper) = 0;
			}
			else if ((*p_avt)->bf == 0)
			{
				(*p_avt)->bf = -1;
				(*p_deeper) = 1;
			}
			else
			{
				RightBalance(p_avt);
				(*p_deeper) = 0;
			}
		}
	}
	return 1;
}

void SearchAVL(AVLTree avt, ElemType key, AVLTree* p_pos)
{
	while (avt)
	{
		if (key == avt->e)
		{
			(*p_pos) = avt;
			break;
		}
		else if (key < avt->e)
		{
			avt = avt->p_lch;
		}
		else
		{
			avt = avt->p_rch;
		}
	}
}

int Hash(int key)
{
	// 除留余数法实现的哈希函数

	return key % 31;
}

void InitHashTable(HashTable* p_ht)
{
	p_ht->larr = (LinkList*)malloc(sizeof(LinkList) * MAX_HASH_SIZE);
	if (p_ht->larr == NULL)
	{
		printf("Error: -- InitHashTable -- fail to alloc memory.\n");
		return;
	}
	for (int i = 0; i < MAX_HASH_SIZE; i++)
	{
		p_ht->larr[i] = NULL;
	}
	p_ht->count = 0;
}

void InsertHashTable(HashTable* p_ht, ElemType e)
{
	// 使用数据本身作为代表数据的关键字
	// 使用链地址法解决哈希冲突

	if (p_ht->count > MAX_HASH_SIZE)
	{
		printf("Error: -- InsertHashTable -- hash table is already full.\n");
		return;
	}

	// 根据关键字，计算哈希地址
	int key = (int)e;
	int addr = Hash(key);

	// 若 addr 位置没有值，说明没有冲突，则创建链表，将 e 存入
	if (p_ht->larr[addr] == NULL)
	{
		LinkList list;
		InitLinkList(&list);
		InsertLinkElem(&list, 0, e);
		p_ht->larr[addr] = list;
	}
	// 若 addr 位置已有值，说明发生冲突，将 e 存入链表末尾
	else
	{
		LinkList list = p_ht->larr[addr];
		int lenght = GetLinkLength(list);
		InsertLinkElem(&list, lenght, e);
	}

	p_ht->count++;
}

LNode* SearchHashTable(HashTable ht, int key)
{
	// 此处用于查找的关键字即数据本身

	// 根据关键字，获取哈希地址
	int addr = Hash(key);

	// 若 addr 位置没有值，查找失败
	if (ht.larr[addr] == NULL)
	{
		return NULL;
	}
	// 若 addr 位置有值，则在对应的链表中查找
	else
	{
		for (LNode* p_n = ht.larr[addr]->p_next; p_n; p_n = p_n->p_next)
		{
			if (p_n->elem == key)
			{
				return p_n;
			}
		}

		// 链表中也没有找到
		return NULL;
	}
}
