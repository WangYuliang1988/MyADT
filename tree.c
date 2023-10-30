#include "tree.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// �����������������
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void InitBiTree(BiTree* p_bt)
{
	// ��ʼ��������ͷָ����Ϊ NULL
	*p_bt = NULL;
}

void CreateBiTree(BiTree* p_bt, char* p_desc)
{
	// �������� p_desc��������Ӧ�ṹ�Ķ�����
	// 
	// ���ȣ��������һ�ö�������
	//	һ���ǽ��������Ķ��壬ʹ�����ű�ʾ����������������
	//	������(������,������)���������������ָ����á���(������,������)����ʾ��ֱ��Ҷ�ӽ�㡣
	//	�磺A(B(D(,G),E),C(F,)) ��ʾ A ���������� BC��B ���������� DE��C �������� F �� F ΪҶ�ӣ�D �������� G �� G ΪҶ�ӡ�
	// 
	// Ȼ����θ���������ɹ�����
	//	���ڶ��������ص��Լ����ű�ʾ���Ĺ��ɣ����Խ���ջ��ʵ�ֶ������Ĺ�����
	//	(1) ��ʼ��ջ stack������ ch ��ʾ p_desc �е��ַ������� k ��ʾ��ǰ��Ҫ������������0��������������1����
	//	(2) ���� p_desc�����ν�ÿ���ַ�д�� ch��
	//		�� ch Ϊ��ĸ���򴴽�һ����������㣬���жϣ�
	//			����ǰ������Ϊ�������򽫸ý����Ϊ���������ڵ㣻
	//			����ǰ��������Ϊ�գ����� k ֵ���ý������Ϊջ����������Һ��ӣ�
	//		�� ch Ϊ������ (������ k = 0����ʾ֮��Ľ�㽫��Ϊ֮ǰ�������ӣ�����֮ǰ�Ľ����ջ��
	//		�� ch Ϊ���� ,������ k = 1����ʾ֮��Ľ�㽫��Ϊ֮ǰ�����Һ��ӣ�
	//		�� ch Ϊ������ )�������Ե�ǰջ�����Ϊ���ģ��ӣ��������ѹ�����ϣ���ջ������ջ��

	SeqStack stack;
	InitSeqStack(&stack);

	char ch;
	int k = -1; // 0�� 1��
	BiTNode* p_new = NULL; // �����ַ���������ĸʱ�����Ľ��
	BiTNode* p_top = NULL; // �������ӣ����������ڵ�ĵ�ǰջ�����
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

				if (*p_bt == NULL) // ͷָ�루*p_bt��Ψһȷ����������ͷָ��Ϊ NULL��˵���ǿ��������ն�����
				{
					*p_bt = p_new;
				}
				else // ͷָ�벻Ϊ NULL��˵�����ڹ�����ջ�����Ϊ���ģ��ӣ�������
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
	// �ݹ����٣�˼·������ʵ�ּ򵥣�ȱ������ʹ�ô���ջ�ռ�
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
	// ����������������ݹ������˼·������ʵ�ּ򵥣�ȱ������ʹ�ô���ջ�ռ�
	// 
	// ��������Ϊ�գ���ղ���������
	//	1. ���ʸ����
	//	2. �������������
	//	3. ��������������

	if (bt)
	{
		printf("%c", (int)bt->e);
		PreOrderTraverseRecursively(bt->p_lch);
		PreOrderTraverseRecursively(bt->p_rch);
	}
}

void InOrderTraverseRecursively(BiTree bt)
{
	// ����������������ݹ������˼·������ʵ�ּ򵥣�ȱ������ʹ�ô���ջ�ռ�
	// 
	// ��������Ϊ�գ���ղ���������
	//	1. �������������
	//	2. ���ʸ����
	//	3. ��������������

	if (bt)
	{
		InOrderTraverseRecursively(bt->p_lch);
		printf("%c", (int)bt->e);
		InOrderTraverseRecursively(bt->p_rch);
	}
}

void PostOrderTraverseRecursively(BiTree bt)
{
	// ����������������ݹ������˼·������ʵ�ּ򵥣�ȱ������ʹ�ô���ջ�ռ�
	// 
	// ��������Ϊ�գ���ղ���������
	//	1. �������������
	//	2. ��������������
	//	3. ���ʸ����

	if (bt)
	{
		PostOrderTraverseRecursively(bt->p_lch);
		PostOrderTraverseRecursively(bt->p_rch);
		printf("%c", (int)bt->e);
	}
}

void PreOrderTraverse(BiTree bt)
{
	// ����������������ǵݹ����������ʽ����ջʵ��
	// 
	// 1. �赱ǰ���Ϊ����㣻
	// 2. ����ǰ��㲻Ϊ NULL����:
	//		(1) ���ʵ�ǰ���;
	//		(2) ����ǰ������Һ��ӣ���ǰ�����ջ��
	//		(3) ����ǰ�����Ϊ������;
	// 3. ����ǰ���Ϊ NULL ��ջ��Ϊ�գ���
	//		(1) ����ǰ�����Ϊջ�������Һ��ӣ�
	//		(2) ��ջ������ջ��
	// 4. �ظ� 2-3 ֱ����ǰ���Ϊ NULL ��ջΪ�ա�

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
	// ����������������ǵݹ����������ʽ����ջʵ��
	// 
	// 1. �赱ǰ���Ϊ����㣻
	// 2. ����ǰ��㲻Ϊ NULL����:
	//		(1) ����ǰ�����ջ��
	//		(2) ����ǰ�����Ϊ������;
	// 3. ����ǰ���Ϊ NULL ��ջ��Ϊ�գ���
	//		(1) ����ջ����㣻
	//		(2) ����ǰ�����Ϊջ�������Һ��ӣ�
	//		(3) ��ջ������ջ��
	// 4. �ظ� 2-3 ֱ����ǰ���Ϊ NULL ��ջΪ�ա�

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
	// ����������������ǵݹ����������ʽ����ջʵ��
	// 
	// 1. �赱ǰ���Ϊ����㣻
	// 2. ����ǰ��㲻Ϊ NULL����:
	//		(1) ����ǰ�����ջ��
	//		(2) ����ǰ�����Ϊ������;
	// 3. ����ǰ���Ϊ NULL ��ջ��Ϊ�գ���
	//		(1) ��ȡջ����㣻
	//		(2) �жϣ�ջ��������Һ������Һ��Ӳ����ϴγ�ջ�Ľ�㣺
	//			���ǣ��򽫵�ǰ�����Ϊջ�������Һ��ӣ�
	//			���������ջ����㣬��ջ������ջ�������ϴγ�ջ��㣻
	// 4. �ظ� 2-3 ֱ����ǰ���Ϊ NULL ��ջΪ�ա�

	SeqStack stack;
	InitSeqStack(&stack);

	BiTNode* p_cur = bt;
	BiTNode* p_top = NULL; // ջ�����
	BiTNode* p_prev = NULL; // �ϴγ�ջ���
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
// �������������ز���
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
* Ѱ��ɭ����Ȩֵ��С���������ڵ��λ��
* 
* �÷������ڸ�����������������end �Ǳ��β��ҵĽ�������ֵ��p_left��p_right �ֱ���ָ��洢Ȩֵ��С���������ڵ�λ�õ�ָ��
* 
*/
void SeekTowMin(HuffmanTree htarr, int end, int* p_left, int* p_right)
{
	// ���ȣ�Ѱ����������㣨�� parent Ϊ��Ч������������������
	// Ȼ�󣬼���Ѱ��ʣ��ĸ���㣬���Ƚϸ����Ȩֵ��
	//	��Ȩֵ��֮ǰ��������С����֮ǰ�ϴ���滻Ϊ֮ǰ��С�ģ�Ȼ�󽫸ý����Ϊ��С�ģ�
	//	��Ȩֵλ��֮ǰ����֮�䣬��֮ǰ�ϴ���滻Ϊ�ý�㣻
	// �ظ�Ѱ��ʣ�����㲢���бȽϣ�ֱ��������
	
	float ml, mr; // �Ƚ����и����Ȩֵ���õ���������С��Ȩֵ���� ml <= mr

	int i = 0;

	// �ҵ���һ������㣬��¼Ȩֵ�����λ��
	while (i <= end && htarr[i].parent != -1)
	{
		i++; // ������ parant != -1��˵���䲻�Ǹ���㣬����Ѱ��
	}
	ml = htarr[i].weight;
	*p_left = i;

	// �ҵ��ڶ�������㣬ͬ��һ�������Ȩֵ�ȽϺ��ټ�¼Ȩֵ�ͽ��λ�ã�ȷ�� ml <= mr
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

	// ����Ѱ�Ҹ���㣬Ȼ��ͬǰ���������Ȩֵ�Ƚ�
	while (++i <= end && htarr[i].parent == -1)
	{
		// ��Ȩֵ��֮ǰ������С�����Ƚ� mr �� p_right �ֱ���Ϊ ml �� p_left���ٽ� ml �� p_left �ֱ���Ϊ��Ȩֵ�����λ��
		if (htarr[i].weight < ml)
		{
			mr = ml;
			*p_right = *p_left;
			ml = htarr[i].weight;
			*p_left = i;
		}
		// ��Ȩֵλ��ǰ����֮�䣬�� mr �� p_right �ֱ���Ϊ��Ȩֵ�����λ��
		else if (htarr[i].weight >= ml && htarr[i].weight < mr)
		{
			mr = htarr[i].weight;
			*p_right = i;
		}
	}
}

void CreateHuffmanTree(HuffmanTree* p_ht, float* warr, int n)
{
	// �Ĳ���������������
	// 
	// ʹ���Ĳ�������Ӧ��ʵ�ʵı����У����ǣ�
	//	1. ��ʼ��һ������Ϊ 2n-1 �����飬���ڴ洢����������ȫ����㣨���� n ��Ҷ�ӽ��Ĺ����������� 2n-1 ����㣩��
	//	2. ����Ҷ�ӽ��Ȩֵ���� warr����ʼ�������ǰ n ����㣬��˫��/����/�Һ���λ�þ���Ϊ��Чֵ -1��������ɭ��ȫ�Ǹ���
	//	3. ������ǰ n ������У�Ѱ��Ȩֵ��С����������˫��λ��Ϊ -1����㣬��Ϊ L �� R��
	//	4. ��ʼ������� n + 1 ����㣬��Ϊ P����ȨֵΪ L �� R Ȩֵ֮�ͣ�˫��λ����Ϊ -1����3-4 ѡ����С��������
	//	5. �� P �����Һ��ӷֱ���Ϊ L �� R��ͬʱ�� L �� R ��˫����Ϊ P������ɾ����С�����ˣ�
	//	6. �� n �� 1���ظ�ֱ�������������ظ� 2-3 ��������

	// ��ʼ�����ڴ洢����������������
	// ע�⣺p_ht Ϊָ��������Ĺ���������ָ�룬*p_ht ������������������һ���洢����ȫ����������
	int m = 2 * n - 1;
	*p_ht = (HuffmanTree)malloc(sizeof(HTNode) * m);
	if (*p_ht == NULL)
	{
		printf("Error: -- CreateHuffmanTree -- fail to alloc memory.\n");
		exit(EXIT_FAILURE);
	}
	
	// ��ʼ�� n ����֪��Ҷ�ӽ��
	for (int i = 0; i < n; i++)
	{
		(*p_ht)[i].weight = warr[i];
		(*p_ht)[i].parent = -1;
		(*p_ht)[i].lch = -1;
		(*p_ht)[i].rch = -1;
	}

	// �����ʼ��ʣ��� n-1 �����
	for (int i = n; i < m; i++)
	{
		// Ѱ���ѳ�ʼ�������Ȩֵ��С�����������λ��
		int ml, mr;
		SeekTowMin(*p_ht, i - 1, &ml, &mr);
		// �³�ʼ��һ�����
		(*p_ht)[i].weight = (*p_ht)[ml].weight + (*p_ht)[mr].weight;
		(*p_ht)[i].parent = -1;
		(*p_ht)[i].lch = ml;
		(*p_ht)[i].rch = mr;
		// ��������С����˫����Ϊ�³�ʼ���Ľ��
		(*p_ht)[ml].parent = (*p_ht)[mr].parent = i;
	}
}

void DestroyHuffmanTree(HuffmanTree* p_ht)
{
	free((*p_ht)); // p_ht Ϊָ��������Ĺ���������ָ�룬*p_ht ������������������һ���洢����ȫ����������
}

void HuffmanCoding(HuffmanTree ht, HuffmanCode* p_hc, int n)
{
	// �ӹ������� ht ��Ҷ�ӽ�㿪ʼ��Ѱ�Ҹ����
	// �˷�ʽ�ԱȴӸ���㿪ʼѰ��Ҷ�ӽ�㣬������٣����õ��ı���������ģ��洢ʱҪ����洢

	// p_hc ��ָ��洢�ַ���Ӧ�Ķ����Ʊ����ַ����������ָ�룬*p_hc ���洢�ַ���Ӧ�Ķ����Ʊ����ַ���������
	(*p_hc) = (HuffmanCode)malloc(sizeof(char*) * n);
	if (*p_hc == NULL)
	{
		printf("Error: -- HuffmanCoding -- fail to alloc memory.\n");
		exit(EXIT_FAILURE);
	}

	// cstr Ϊ��ǰ�ַ���Ӧ�Ķ����Ʊ����ַ�����ע�� C �е��ַ��������ַ�������� '\0' ��β������
	// ��洢�ַ��������鳤��Ϊ n����Ϊ n ���ַ��ڱ�֤����Ψһ��ǰ����ÿ���ַ�������󳤶Ȳ��ᳬ�� n
	char* cstr = (char*)malloc(sizeof(char) * n);
	if (cstr == NULL)
	{
		printf("Error: -- HuffmanCoding -- fail to alloc memory.\n");
		exit(EXIT_FAILURE);
	}
	cstr[n - 1] = '\0';

	// ht ʵ���Ǵ�Ź��������������飬�����乹��������֪��ǰ n �����洢����Ҷ�ӽ��
	for (int i = 0; i < n; i++)
	{
		int start = n - 1; // ��Ҷ�ӽ������õ��ı����ַ���������ģ��洢ʱҲҪ����

		int cpos = i; // ��Ҷ�ӽ�㿪ʼѰ�Ҹ��������У�ÿ�η��ʵĽ���������е�λ��
		int ppos = ht[cpos].parent;// ÿ�η��ʵĽ��ĸ�����������е�λ��

		// Ѱ�Ҹ����
		while (ppos != -1)
		{
			// ������η��ʽ�����丸�������ӣ���·������Ϊ '0'
			if (ht[ppos].lch == cpos)
			{
				cstr[--start] = '0';
			}
			// ����Ϊ '1'
			else
			{
				cstr[--start] = '1';
			}
			// �豾�η��ʽ��Ϊ�丸��㣬����Ѱ�Ҹ����
			cpos = ppos;
			ppos = ht[cpos].parent;
		}

		// �ҵ�����㣬��λ��Ϊ i ��Ҷ�ӽ���Ӧ�ı������γ�
		(*p_hc)[i] = (char*)malloc(sizeof(char) * (n - start));
		strcpy((*p_hc)[i], &cstr[start]);
	}

	free(cstr);
}
