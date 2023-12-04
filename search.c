#include "search.h"

int SearchSeq(SSTable st, ElemType key)
{
	// ��������ڣ�������������Ч��
	st.earr[st.length] = key;

	// ����ָ��Ԫ��
	int i;
	for (i = 0; key != st.earr[i] ; i++);
	
	// ���ز��ҽ��
	if (i == st.length) return -1;
	return i;
}

int SearchBin(SSTable st, ElemType key)
{
	// ǰ�᣺SSTable ����

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
	// ǰ�᣺SSTable �ֿ�����
	
	// ������ұ� 3 ��Ԫ��Ϊһ���ӱ�ֿ�����
	int itemc = 3, blockc = (st.length / itemc) + (st.length % itemc == 0 ? 0 : 1);
	Index* idxarr = (Index*)malloc(sizeof(Index) * blockc);
	if (idxarr == NULL)
	{
		printf("Error: -- SearchBlk -- fail to alloc memory.\n");
	}

	// �����ӱ���������
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

	// ���ֲ���������ȷ���ӱ�
	int low = 0, high = blockc;
	while (low < high) // ���ֲ��ҽ��е� low �� high ָ��ͬһ������ʱ����������Ӧ�ӱ�ΪĿ���ӱ�
	{
		int mid = (low + high) / 2;
		if (key > idxarr[mid].max)
		{
			low = mid + 1;
		}
		else
		{
			high = mid; // key С�ڻ�������������ֵʱ��key �����ܴ����ڸ�������Ӧ���ӱ���
		}
	}
	int starti = -1;
	if (low == high)
	{
		starti = idxarr[low].start;
	}

	// ˳������ӱ�����Ŀ��Ԫ��λ��
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
* ������Ŷ�����
* 
* swarr �ǹؼ��ֵĸ����ۻ��͵ļ���
* 
* low �� high �ֱ��ʾ���ι������õ���������ʼ�ͽ���λ��
*/
void CreateOptimal(BiTree* p_bt, ElemType karr[], float swarr[], int low, int high)
{
	// Ѱ�ұ��ι������õ�������о�����С���Ҹ���֮�Ͳ�ֵ�Ĺؼ��֡�
	// 
	// ������ֱ�ӵķ�ʽ����ؼ��� k ���Ҹ���֮�͵Ĳ�ֵ��ÿ�εݹ鶼��Ҫʹ��˫��ѭ����
	// 
	// Ϊ�����㷨Ч�ʣ�����ؼ��ֵĸ����ۻ��ͣ�sw������� w Ϊ�ؼ��� k �Ĳ�ѯ���ʣ���
	//		sw[k] = w[0] + w[1] +...+ w[k] = sw[k-1] + w[k]��
	// 
	// ���� k ���Ҹ���֮�͵Ĳ�ֵʱ���������������ʼλ��Ϊ l������λ��Ϊ h����
	//		diff[k] = |(w[k+1] +...+ w[h]) - (w[l] +...+ w[k-1])|
	//				= |(sw[h] - sw[k]) - (sw[k-1] - sw[l-1])|
	//				= |sw[h] + sw[l-1] - sw[k] - sw[k-1]
	// 
	// ע�⵱ k �� l С�� 1 ʱ�� sw[l-1] �� sw[k-1] ���������㡣
	int midx = -1;
	float mind = (float)INFINITY;
	float stad = low < 1 ? swarr[high] : swarr[high] + swarr[low - 1];
	for (int i = low; i <= high; i++)
	{
		float vard = i < 1 ? stad - swarr[i] : stad - swarr[i] - swarr[i - 1];
		vard = vard < 0 ? -1 * vard : vard; // ȡ��ֵ�ľ���ֵ
		if (vard < mind)
		{
			mind = vard;
			midx = i;
		}
	}

	// ���ҵ��ľ�����С���Ҹ���֮�Ͳ�ֵ�Ĺؼ�����Ϊ���ι�����ĸ����
	// Ȼ���Ըùؼ������ָ���������Ϊ����������������ݹ鹹�����θ�������������
	*p_bt = (BiTree)malloc(sizeof(BiTNode));
	if (*p_bt == NULL) {
		printf("Error: -- CreateOptimal -- fail to alloc memory.\n");
		return;
	}
	(*p_bt)->e = midx; // ע����洢���ǹؼ�����������е�λ�ã������ǹؼ��ֱ���

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
* ����������Ŷ�������Ѱ��ָ���ؼ��ֵ�λ��
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
	// ǰ�᣺karr �����ҹؼ��ֵĲ�ѯ���ʲ���

	// ������ؼ��ֵĸ����ۻ���
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

	// �������Ų�����
	BiTree bt;
	CreateOptimal(&bt, karr, swarr, 0, len - 1);

	// ����������Ų��������ҳ� key ����λ��
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
	// ����ǰ��Ϊ��������ֱ����� key Ϊ��ǰ���ĸ����
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
	// �� key С�ڵ�ǰ����ֵ��˵���轫 key ���뵽��ǰ������������
	else if (key < (*p_bt)->e)
	{
		InsertBST(&((*p_bt)->p_lch), key);
	}
	// �� key ���ڵ�ǰ����ֵ��˵���轫 key ���뵽��ǰ������������
	else
	{
		InsertBST(&((*p_bt)->p_rch), key);
	}
}

/*
* DeleteBST �ĸ�������������ɾ�� BST �еĽ��
*/
void DelBstNode(BiTree* p_bt)
{
	// ע�⣺��ɾ���Ľ���� *p_bt

	// ��ɾ���Ľ��ΪҶ�ӽ�㣬ֱ��ɾ��
	if ((*p_bt)->p_lch == NULL && (*p_bt)->p_rch == NULL)
	{
		(*p_bt) = NULL;
		free((*p_bt));
	}
	// ��ɾ�����ֻ��һ�����ӣ������Ӵ����ɾ�����
	else if ((*p_bt)->p_lch != NULL && (*p_bt)->p_rch == NULL)
	{
		BiTNode* p_n = (*p_bt);
		(*p_bt) = (*p_bt)->p_lch;
		free(p_n);
	}
	// ��ɾ�����ֻ��һ���Һ��ӣ����Һ��Ӵ����ɾ�����
	else if ((*p_bt)->p_rch == NULL && (*p_bt)->p_rch != NULL)
	{
		BiTNode* p_n = (*p_bt);
		(*p_bt) = (*p_bt)->p_rch;
		free(p_n);
	}
	// ��ɾ��������������ӣ����ҵ���ɾ��������������µ�ֱ��ǰ������ǰ������ֵ���Ƹ���ɾ��㣬��ɾ��ֱ��ǰ��
	else
	{
		BiTNode* p_pre = NULL; // ��ɾ����ֱ��ǰ��
		BiTNode* p_pre_par = NULL; // ֱ��ǰ���ĸ����

		// Ѱ�Ҵ�ɾ������������µ�ֱ��ǰ��
		// �����������У�ӵ���������ӵĽ�������������µ�ֱ��ǰ�����϶��ڸý�����������
		// ͬʱ����ǰ�����Ҫô��Ҷ�ӽ�㣬Ҫôֻ�����ӣ�����֮��ǰ�����϶�û���Һ���
		// �ڴ�ɾ�����������У��Ӹ���㿪ʼ����һ��û���Һ��ӵĽ�㣬���Ǵ�ɾ����ǰ��
		p_pre_par = (*p_bt);
		p_pre = (*p_bt)->p_lch;
		while (p_pre->p_rch)
		{
			p_pre_par = p_pre;
			p_pre = p_pre->p_rch;
		}

		// ��ǰ������ֵ���Ƹ���ɾ��㣬ɾ����ɾ���תΪɾ��ǰ�����
		(*p_bt)->e = p_pre->e;

		// ɾ��ǰ�����
		// ǰ�����Ҫô��Ҷ�ӽ�㣬Ҫôֻ������
		// ����Ҷ�ӽ�㣬�����ǰ��������丸�������ң����ӣ������������ң�������Ϊ NULL
		// ��ֻ�����ӣ������ǰ��������丸�������ң����ӣ������������ң�������Ϊǰ����������
		// �ۺ����������жϣ�������ֻ�����ӵ��߼���������Ҷ�ӽ��ʱ���߼�����Ϊǰ�������Ҷ�ӽ��ʱ�������Ӿ��� NULL
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
	// �����ǰ�������ڣ�ɾ��ʧ��
	if (!(*p_bt))
	{
		return;
	}
	else if ((*p_bt)->e == key)
	{
		DelBstNode(p_bt);
	}
	// ��� key С�ڵ�ǰ����ֵ��˵���赽��ǰ��������������ɾ��
	else if (key < (*p_bt)->e)
	{
		DeleteBST(&((*p_bt)->p_lch), key);
	}
	// ��� key ���ڵ�ǰ����ֵ��˵���赽��ǰ��������������ɾ��
	else
	{
		DeleteBST(&((*p_bt)->p_rch), key);
	}
}

void LeftRotate(AVLTree* p_avt)
{
	// ������Ϊ P��P ������Ϊ L��P ���Һ���Ϊ R
	// 
	// ������P ��Ϊ R �����ӣ�R ԭ����������Ϊ P ���Һ��ӣ�L ��ȻΪ P �����ӣ�R ���� P ��Ϊ�����

	AVLNode* p_r = (*p_avt)->p_rch;
	(*p_avt)->p_rch = p_r->p_lch;
	p_r->p_lch = (*p_avt);
	(*p_avt) = p_r;
}

void RightRotate(AVLTree* p_avt)
{
	// ������Ϊ P��P ������Ϊ L��P ���Һ���Ϊ R
	//
	// ������P ��Ϊ L ���Һ��ӣ�L ԭ�����Һ�����Ϊ P �����ӣ�R ��ȻΪ P ���Һ��ӣ�L ���� P ��Ϊ�����

	AVLNode* p_l = (*p_avt)->p_lch;
	(*p_avt)->p_lch = p_l->p_rch;
	p_l->p_rch = (*p_avt);
	(*p_avt) = p_l;
}

void LeftBalance(AVLTree* p_avt)
{
	// �� p_avt ���������������㵼��ʧ�⣨�� p_avt ������ƽ������Ϊ 2��������ת�Իָ�ƽ�⡣
	// 
	// �� p_avt �����Ϊ P��P ������Ϊ L����
	//	�� L ��ƽ������Ϊ 1��˵������Ľ��λ�� L ������������ LL ��ʧ�⣬��� P ������
	//	�� L ��ƽ������Ϊ -1��˵������Ľ��λ�� L ������������ LR ��ʧ�⣬���ȶ� L �������ٶ� P ������
	// 
	// ע�����ݲ��뺯�� InsertAVL���Խ�� P �������������㵼��ʧ��ʱ��P ������ L ��ƽ������ֻ���� 1 �� -1��
	
	AVLTree lch = (*p_avt)->p_lch;
	if (lch->bf == 1)
	{
		// P ������
		//	P ����������Ƚ��� 2��P ��ƽ�����ӽ���Ϊ 0��
		//	L ����������Ƚ��� 1��L ��ƽ�����ӽ���Ϊ 0��
		(*p_avt)->bf = lch->bf = 0;

		RightRotate(p_avt);
	}
	else if (lch->bf == -1)
	{
		// �� R' �� L ����ǰ���Һ��ӣ���
		// 
		// �� L ������
		//	�� R' ��ƽ�������� 1���� L ����������Ƚ��� 1��L ��ƽ�����ӽ���Ϊ 0��
		//	�� R' ��ƽ�������� 0���� L ����������Ƚ��� 1��L ��ƽ�����ӽ���Ϊ 0��
		//	�� R' ��ƽ�������� -1���� L ����������Ƚ��� 2��L ��ƽ�����ӽ���Ϊ 1��
		// 
		// �� P ������
		//	�� R' ��ƽ�������� 1���� P ����������Ƚ��� 3��P ��ƽ�����ӽ���Ϊ -1��
		//	�� R' ��ƽ�������� 0���� P ����������Ƚ��� 2��P ��ƽ�����ӽ���Ϊ 0��
		//	�� R' ��ƽ�������� -1���� P ����������Ƚ��� 2��P ��ƽ�����ӽ���Ϊ 0��
		// 
		// ��ת���R' ����Ϊ�µĸ���㣬����ƽ������Ϊ 0��

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
	// �� p_avt ���������������㵼��ʧ�⣨�� p_avt ������ƽ������Ϊ -2��������ת�Իָ�ƽ�⡣
	//
	// �� p_avt �����Ϊ P��P ������Ϊ R����
	//	�� R ��ƽ������Ϊ -1��˵������Ľ��λ�� R ������������ RR ��ʧ�⣬��� P ������
	//	�� R ��ƽ������Ϊ 1��˵������Ľ��λ�� R ������������ RL ��ʧ�⣬���ȶ� R �������ٶ� P ������
	// 
	// ע�����ݲ��뺯�� InsertAVL���Խ�� P �������������㵼��ʧ��ʱ��P ���Һ��� R ��ƽ������ֻ���� 1 �� -1��

	AVLTree rch = (*p_avt)->p_rch;
	if (rch->bf == -1)
	{
		// P ������
		//	P ����������Ƚ��� 2��P ��ƽ�����ӽ���Ϊ 0��
		//	R ����������Ƚ��� 1��R ��ƽ�����ӽ���Ϊ 0��
		(*p_avt)->bf = rch->bf = 0;

		LeftRotate(p_avt);
	}
	else if (rch->bf == 1)
	{
		// �� L' �� R ����ǰ�����ӣ���
		// 
		// �� R ������
		//	�� L' ��ƽ�������� 1���� R ����������Ƚ��� 2��R ��ƽ�����ӽ���Ϊ -1��
		//	�� L' ��ƽ�������� 0���� R ����������Ƚ��� 1��R ��ƽ�����ӽ���Ϊ 0��
		//	�� L' ��ƽ�������� -1���� R ����������Ƚ��� 1��R ��ƽ�����ӽ���Ϊ 0��
		// 
		// �� P ������
		//	�� L' ��ƽ�������� 1���� P ����������Ƚ��� 2��P ��ƽ�����ӽ���Ϊ 0��
		//	�� L' ��ƽ�������� 0���� P ����������Ƚ��� 2��P ��ƽ�����ӽ���Ϊ 0��
		//	�� L' ��ƽ�������� -1���� P ����������Ƚ��� 3��P ��ƽ�����ӽ���Ϊ 1��
		// 
		// ��ת���L' ����Ϊ�µĸ���㣬����ƽ������Ϊ 0��

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
	// �����Ϊ��������ֱ����� e Ϊ�����
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

		// p_deeper ָ��ָ���ֵ��ʼ�ձ�ʶ���β����Ӧ�� p_avt ��������Ƿ����ӡ���Ϊ���β����Ӧ�� p_avt
		// �ǿ��������Ϊ 0���������ӵ��һ����㣬��ȱ�Ϊ 1���������������ӣ����� (*p_deeper) ��Ϊ��ֵ��
		// 
		// ͬʱ����Ϊ�ò��뺯���ǵݹ麯�������β���Ľ�㣬�������ϲ�ĳ�������ӽ�㣬��������ȵı仯������
		// ��Ӱ���ϲ�������ȡ���ˣ��ڱ��β��뷵�غ������û�Ҫ�ж����Ӧ��ε� p_avt ��������Ƿ����ӣ�
		// �����ö�Ӧ�� (*p_deeper) ֵ����ˣ�(*p_deeper) ʼ�ձ�ʶ���β����Ӧ�� p_avt ������Ƿ����ӡ�
		(*p_deeper) = 1;
	}
	else if (e == (*p_avt)->e)
	{
		printf("Error: -- InsertAVL -- %lld is alreay in this AVL.\n", e);
		return 0;
	}
	// ������ֵС�ڵ�ǰ���ֵ��������뵱ǰ������������
	else if (e < (*p_avt)->e)
	{
		int rs = InsertAVL(&((*p_avt)->p_lch), e, p_deeper);

		// ������������ʧ�ܣ��򱾴β���Ҳ��ʧ��
		if (!rs)
		{
			return 0;
		}
		// ������������ɹ����򿴲����������������Ƿ����ӣ�
		// �������ӣ�������ݵ�ǰ����ƽ�������ٴν����жϣ�
		//		��ƽ������Ϊ 1��������ƽ�����ӽ���Ϊ 2������ת�Ա���ƽ�⣻
		//		��ƽ������Ϊ 0�������ƽ������Ϊ 1������ (*p_deeper) Ϊ�棻
		//		��ƽ������Ϊ -1�������ƽ������Ϊ 0������ (*p_deeper) Ϊ�٣�
		// �������ӣ���������������
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
	// ������ֵ���ڵ�ǰ���ֵ��������뵱ǰ������������
	else
	{
		int rs = InsertAVL(&((*p_avt)->p_rch), e, p_deeper);

		// ������������ʧ�ܣ��򱾴β���Ҳ��ʧ��
		if (!rs)
		{
			return 0;
		}
		// ������������ɹ����򿴲����������������Ƿ����ӣ�
		// �������ӣ�������ݵ�ǰ����ƽ�������ٴν����жϣ�
		//		��ƽ������Ϊ 1�������ƽ������Ϊ 0������ (*p_deeper) Ϊ�٣�
		//		��ƽ������Ϊ 0�������ƽ������Ϊ 1������ (*p_deeper) Ϊ�棻
		//		��ƽ������Ϊ -1��������ƽ�����ӽ���Ϊ -2������ת�Ա���ƽ�⣻
		// �������ӣ���������������
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
	// ����������ʵ�ֵĹ�ϣ����

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
	// ʹ�����ݱ�����Ϊ�������ݵĹؼ���
	// ʹ������ַ�������ϣ��ͻ

	if (p_ht->count > MAX_HASH_SIZE)
	{
		printf("Error: -- InsertHashTable -- hash table is already full.\n");
		return;
	}

	// ���ݹؼ��֣������ϣ��ַ
	int key = (int)e;
	int addr = Hash(key);

	// �� addr λ��û��ֵ��˵��û�г�ͻ���򴴽������� e ����
	if (p_ht->larr[addr] == NULL)
	{
		LinkList list;
		InitLinkList(&list);
		InsertLinkElem(&list, 0, e);
		p_ht->larr[addr] = list;
	}
	// �� addr λ������ֵ��˵��������ͻ���� e ��������ĩβ
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
	// �˴����ڲ��ҵĹؼ��ּ����ݱ���

	// ���ݹؼ��֣���ȡ��ϣ��ַ
	int addr = Hash(key);

	// �� addr λ��û��ֵ������ʧ��
	if (ht.larr[addr] == NULL)
	{
		return NULL;
	}
	// �� addr λ����ֵ�����ڶ�Ӧ�������в���
	else
	{
		for (LNode* p_n = ht.larr[addr]->p_next; p_n; p_n = p_n->p_next)
		{
			if (p_n->elem == key)
			{
				return p_n;
			}
		}

		// ������Ҳû���ҵ�
		return NULL;
	}
}
