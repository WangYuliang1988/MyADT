#include "graph.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// ���幤�ߺ��������ڽ�������ͼ�ı߻򻡼��ϵ�Լ����ʽ���ַ���
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
* ��¼��������Ľṹ��
*/
typedef struct
{
	VertexType v; // �߶����β
	VertexType w; // �߶����ͷ
	int weight; // �߻򻡵�Ȩֵ
}ArcItem;

/*
* ��ȡͼ����
*/
void GetGraphKind(char* adjs, GraphKind* p_kind)
{
	GraphKind kind = -1;
	int comnum = 0; // ���Ÿ�����һ�� () �� <> �����������ţ�˵������Ȩֵ
	for (int i = 0; adjs[i] != '\0'; i++)
	{
		if (adjs[i] == ',')
		{
			comnum++;
		}
		else if (adjs[i] == ')') // ����
		{
			kind = (comnum == 2) ? UDN : UDG;
			break;
		}
		else if (adjs[i] == '>') // ����
		{
			kind = (comnum == 2) ? DN : DG;
			break;
		}
	}
	(*p_kind) = kind;
}

/*
* ��ȡ�����õ��ı߻���Ϣ
*/
void GetArcInfo(char* adjs, ArcItem* arc_arr, int* p_arcnum)
{
	int arcnum = 0; // �߻򻡵�����
	VertexType v = 0; // �߻򻡵Ķ���
	VertexType w = 0; // �߻򻡵Ķ���
	int weight = 0; // �߻򻡵�Ȩ��
	int to_set_v = 0, to_set_w = 0, to_set_weight = 0; // �Ƿ�Ҫ���� v/w/weight
	char numstr[6]; // �����ַ����������ʾ�����˴������������Ϊ 5 λ������
	int curi = 0; // ���ν������������ַ���Ӧ��д�뵽��ʾ�����ַ���������λ��

	for (int i = 0; adjs[i] != '\0'; i++)
	{
		switch (adjs[i])
		{
		case '(':
		case '<':
			to_set_v = 1;
			break;
		case ',':
			numstr[curi] = '\0', curi = 0;
			if (to_set_w)
			{
				w = atoi(numstr);
				to_set_weight = 1;
			}
			else if (to_set_v)
			{
				v = atoi(numstr);
				to_set_w = 1;
			}
			break;
		case ')':
		case '>':
			numstr[curi] = '\0', curi = 0;
			if (to_set_weight)
			{
				weight = atoi(numstr);
			}
			else if (to_set_w)
			{
				w = atoi(numstr);
			}
			arc_arr[arcnum].v = v;
			arc_arr[arcnum].w = w;
			arc_arr[arcnum].weight = weight;
			arcnum++;
			to_set_v = to_set_w = to_set_weight = 0;
			break;
		default:
			numstr[curi] = adjs[i];
			curi++;
			break;
		}
	}
	(*p_arcnum) = arcnum;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// ����ͼ��˳��洢��ز���
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
int LocateMVex(MGraph mg, VertexType v)
{
	int i = 0;
	// �����������飬Ѱ�� v
	while (i < mg.vexnum)
	{
		if (mg.vexs[i] == v)
		{
			break;
		}
		i++;
	}
	// δ�ҵ������� -1
	if (i == mg.vexnum)
	{
		return -1;
	}
	return i;
}

void CreateMGraph(MGraph* p_g, VertexType vexs[], int vexnum, char* adjs)
{
	// ��������˳��ṹ��ͼ��ʵ�ʾ��������������飺
	//	1. �洢������Ϣ��һά���飬������Ϣ�ɴ��뺯���Ĳ���ֱ�Ӹ�����
	//	2. �洢�߻���Ϣ�Ķ�ά���飬�߻򻡵���Ϣͨ������ adjs �ַ�����á�
	
	// ���ö�����Ϣ
	for (int i = 0; i < vexnum; i++)
	{
		p_g->vexs[i] = vexs[i];
	}
	p_g->vexnum = vexnum;

	// ����ͼ���Ͳ���ʼ�����б߻���Ϣ
	GetGraphKind(adjs, &(p_g->kind));
	for (int i = 0; i < vexnum; i++)
	{
		for (int k = 0; k < vexnum; k++)
		{
			p_g->arcs[i][k].adj = (p_g->kind == DG || p_g->kind == UDG) ? 0 : INFINITY;
			p_g->arcs[i][k].p_info = NULL;
		}
	}

	// ���������߻���Ϣ���ַ��������ݽ����������
	ArcItem* arc_arr = (ArcItem*)malloc(sizeof(ArcItem) * vexnum * vexnum);
	if (arc_arr == NULL)
	{
		printf("Error: -- CreateMGraph -- fail to alloc memory.\n");
		exit(EXIT_FAILURE);
	}
	GetArcInfo(adjs, arc_arr, &(p_g->arcnum));
	for (int i = 0; i < p_g->arcnum; i++)
	{
		VertexType v = arc_arr[i].v;
		VertexType w = arc_arr[i].w;
		int weight = arc_arr[i].weight;

		int m = LocateMVex(*p_g, v);
		int n = LocateMVex(*p_g, w);
		if (m == -1 || n == -1)
		{
			printf("Error: -- CreateMGraph -- vertex %d or %d isn't in graph.\n", v, w);
			exit(EXIT_FAILURE);
		}
		if (p_g->kind == DN || p_g->kind == UDN)
		{
			// ���ı߻�����ΪȨֵ
			p_g->arcs[m][n].adj = weight;

			if (p_g->kind == UDN)
			{
				p_g->arcs[n][m].adj = weight;
			}
		}
		else
		{
			// ͼ�ı߻�����Ϊ 1
			p_g->arcs[m][n].adj = 1;

			if (p_g->kind == UDG)
			{
				p_g->arcs[n][m].adj = 1;
			}
		}
	}
	free(arc_arr);
}

void DFSTraverse(MGraph mg)
{
	// 1. ��ͼ����ѡһ�����㣬��Ϊ��ʼ��ǰ������ջ��
	// 2. ��ȡջ��Ԫ����Ϊ��ǰ���� cv������ cv δ�������򣩷��� cv��
	// 3. Ѱ�Һ͵㵱ǰ���� cv ������δ�����ʹ��Ķ��㣬��Ϊ cn��
	//		�����ҵ����� cn ��ջ��
	//		��δ�ҵ�����ջ��Ԫ�س�ջ�����ж��Ƿ�ջ�գ�ջ������ѡһ��δ���ʹ��Ķ�����ջ��
	// 4. �ظ�ִ�� 2-3��ֱ��ջ�գ�����������

	// ���ڼ�¼�����Ƿ񱻷��ʹ�������
	int visarr[MAX_VERTEX_NUM] = { 0 };

	// �洢���ε�ǰ�����ջ
	SeqStack stack;
	InitSeqStack(&stack);

	// ��ȡջ��Ԫ�صı�������ջ��Ԫ����������ͬͼ�����������Ͳ�һ�£���Ҫ������ת
	ElemType elem = -1;

	// ��ǰ����
	VertexType cv = -1;

	// ͬ��ǰ����������δ�����ʵĶ���
	VertexType cn = -1;

	// ��ǰ������ͼ�Ķ��������е�λ��
	int cvloc = -1;

	// ѡһ��������Ϊ��ʼ��ǰ������ջ
	Push(&stack, mg.vexs[0]);
	printf("DFSTraverse: ");

	while (!IsStackEmpty(stack))
	{
		cn = -1; // ��ʼѰ��ǰ������ cn

		// ��ջ����ȡ��ǰ���㣬��δ���ʹ�����з���
		GetTop(stack, &elem);
		cv = (VertexType)elem;
		cvloc = LocateMVex(mg, cv);
		if (visarr[cvloc] == 0)
		{
			printf("%d, ", cv);
			visarr[cvloc] = 1;
		}

		// Ѱ��ͬ��ǰ����������δ�����ʵĶ��� cn
		for (int i = 0; i < mg.vexnum; i++)
		{
			// arcs[cvloc][i] �� arcs[i][cvloc]��������ͼ����������ͬ�ߣ�������ͼ�������ǲ�ͬ�ߣ�
			// �˴����ж��ǿ���ͬʱ��������ͼ������ͼ������жϣ�ʵ���ϣ���������ͼ��Ȼ����������ͼ����
			if (visarr[i] == 0 &&
				((mg.arcs[cvloc][i].adj > 0 && mg.arcs[cvloc][i].adj != INFINITY) ||
					(mg.arcs[i][cvloc].adj > 0 && mg.arcs[i][cvloc].adj != INFINITY)))
			{
				cn = mg.vexs[i];
				break;
			}
		}

		// �����ҵ����� cn ��Ϊ�µĵ�ǰ������ջ��
		// ����ջ��Ԫ�س�ջ���������ϸ���ǰ���㡣
		if (cn != -1)
		{
			Push(&stack, cn);
		}
		else
		{
			Pop(&stack, &elem);

			// ��ջ��գ�����ѡһ��δ�����ʵĶ�����Ϊ��ǰ������ջ
			if (IsStackEmpty(stack))
			{
				int i;
				for (i = 0; i < mg.vexnum; i++)
				{
					if (visarr[i] == 0)
					{
						Push(&stack, mg.vexs[i]);
						break;
					}
				}
				// ������ж��㶼�ѷ��ʹ���˵��������ɣ�������ӡ�ϵĸ�ʽ�Ż�
				if (i == mg.vexnum)
				{
					printf("\b\b \n");
				}
			}
		}
	}
	DestroySeqStack(&stack);
}

void BFSTraverse(MGraph mg)
{
	// 1. ��ͼ����ѡһ���㣬���ʣ�����Ϊ��ʼ��ǰ������ӣ�
	// 2. ��ȡ����Ԫ����Ϊ��ǰ���� cv ��Ѱ�Һ� cv ������δ�����ʵĶ��� cn��
	//		�����ҵ�������� cn ���� cn ��ӣ�
	//		��δ�ҵ��������Ԫ�س��ӣ����ж��Ƿ�ӿգ��ӿ�����ѡһ��δ�����ʹ��Ķ�����ӣ�
	// 3. �ظ� 2 ֱ���ӿգ�����������

	// ������¼ͼ�ܶ����Ƿ񱻷��ʹ�������
	int visarr[MAX_VERTEX_NUM] = { 0 };

	// ��˳��洢�����ʹ��Ķ���Ķ���
	LinkQueue queue;
	InitLinkQueue(&queue);

	// ��ȡ����Ԫ�صı����������Ԫ���������ͺ�ͼ�����������Ͳ�һ�£���Ҫ������ת
	ElemType elem = -1;

	// ��ǰ����
	VertexType cv = -1;

	// ͬ��ǰ����������δ�����ʵĶ���
	VertexType cn = -1;

	// cv ��ͼ�Ķ��������е�λ��
	int cvloc = -1;

	// cn ��ͼ�Ķ��������е�λ��
	int cnloc = -1;

	// ѡһ��������ʣ�����Ϊ��ʼ��ǰ�������
	cvloc = 0;
	visarr[cvloc] = 1;
	cv = mg.vexs[cvloc];
	EnLinkQueue(&queue, cv);
	printf("BFSTraverse: %d, ", cv);

	while (!IsLinkQueueEmpty(queue))
	{
		cn = cnloc = -1; // ��ʼѰ��ǰ������ cn �� cnloc

		// ��ȡ����Ԫ����Ϊ��ǰ����
		GetLinkQueueHead(queue, &elem);
		cv = (VertexType)elem;
		cvloc = LocateMVex(mg, cv);

		// Ѱ��ͬ��ǰ����������δ�����ʵĶ��� cn
		for (int i = 0; i < mg.vexnum; i++)
		{
			// arcs[cvloc][i] �� arcs[i][cvloc]��������ͼ����������ͬ�ߣ�������ͼ�������ǲ�ͬ�ߣ�
			// �˴����ж��ǿ���ͬʱ��������ͼ������ͼ������жϣ�ʵ���ϣ���������ͼ��Ȼ����������ͼ����
			if (visarr[i] == 0 &&
				((mg.arcs[cvloc][i].adj > 0 && mg.arcs[cvloc][i].adj != INFINITY) ||
					(mg.arcs[i][cvloc].adj > 0 && mg.arcs[i][cvloc].adj != INFINITY)))
			{
				cn = mg.vexs[i];
				cnloc = i;
				break;
			}
		}

		// �����ҵ�������� cn ���� cn ��ӣ�ע�⣺�����Ƕ�β���롢����ɾ�������� cn �����βԪ�����ǵ�ǰ���� cv����
		// ��δ�ҵ��������Ԫ�أ�����ǰ���� cv�����ӣ�ע�⣺�˺��µĶ���Ԫ�أ��� cv �ĵ�һ�� cn������Ϊ�µ� cv����
		if (cn != -1)
		{
			visarr[cnloc] = 1;
			printf("%d, ", cn);
			EnLinkQueue(&queue, cn);
		}
		else
		{
			DeLinkQueue(&queue, &elem);

			// �ж��Ƿ�ӿգ��ӿ�����ѡһ��δ�����ʹ��Ķ��㣬���ʲ����
			if (IsLinkQueueEmpty(queue))
			{
				int i;
				for (i = 0; i < mg.vexnum; i++)
				{
					if (visarr[i] == 0)
					{
						visarr[i] = 1;
						printf("%d, ", mg.vexs[i]);
						EnLinkQueue(&queue, mg.vexs[i]);
						break;
					}
				}
				// ������ж��㶼�ѷ��ʹ���˵��������ɣ�������ӡ�ϵĸ�ʽ�Ż�
				if (i == mg.vexnum)
				{
					printf("\b\b \n");
				}
			}
		}
	}

	DestroyLinkQueue(&queue);
}

void MiniSpanTreePrim(MGraph mg)
{
	// ˵��������ͼ��˳��洢���ʣ�����ʹ�ö����������е�λ����ָ�����㱾��
	// ��˼·�У�uarr �� varr �ڴ���ʵ��ʱ����ͨ���洢����λ�����򻯲�����
	// 
	// 1. ������������ uarr �� varr����ʼʱ uarr Ϊ�գ�varr ����ͼ�����ж��㣻
	// 2. �� varr ����ѡһ��������� uarr �У������ö���� varr ��ɾ����
	// 3. �� varr ��Ѱ��һ�����㣬�ö����� varr �����ܺ� uarr �ж��㹹�ɵı��У�
	//    ������СȨֵ��Ȼ�󽫸ö������ uarr �У�ͬʱ�� varr ��ɾ���ö��㣻
	// 5. �ظ� 3 ֱ�� uarr �а���ͼ��ȫ�����㡣

	printf("MiniSpanTreePrim: ");

	// �����С����������λ�õ�����
	VertexType uarr[MAX_VERTEX_NUM];

	// ��ų���С������������ͼ��ʣ�ඥ��λ�õ�����
	VertexType varr[MAX_VERTEX_NUM];

	// ��¼ uarr �����Ķ���λ�ø���
	int unum = 0;

	// ���� varr ����ͼ��ȫ������λ��
	for (int i = 0; i < mg.vexnum; i++)
	{
		varr[i] = i; // ����ͼ��˳��洢�ص㣬ͼ�Ķ����ڶ��������е�λ�ô� 0 ��ʼ���δ��
	}

	// �� varr ��ѡ��һ������λ�÷��� uarr��Ȼ���� varr ��ɾ������Ϊ -1���ö���λ��
	uarr[unum++] = varr[0];
	varr[0] = -1;

	while (unum < mg.vexnum)
	{
		int mini = INFINITY; // �����ҵ�����СȨֵ
		int ui = -1; // ӵ����СȨֵ�ı߰����� uarr �еĶ����ڶ��������е�λ��
		int vi = -1; // ӵ����СȨֵ�ı߰����� varr �еĶ����ڶ��������е�λ��

		// ���� varr �п��Ժ� uarr �ж��㹹����СȨֵ�ߵĶ���λ��
		for (int i = 0; i < unum; i++)
		{
			ui = uarr[i];
			for (int k = 0; k < mg.vexnum; k++)
			{
				if (varr[k] != -1)
				{
					int vloc = varr[k];
					if (mg.arcs[ui][vloc].adj < mini)
					{
						mini = mg.arcs[ui][vloc].adj;
						vi = vloc;
					}
				}
			}
		}

		// �������ҵ��Ķ���λ�÷��� uarr������ varr ��ɾ���ö���λ��
		if (vi != -1)
		{
			uarr[unum++] = vi;
			for (int i = 0; i < mg.vexnum; i++)
			{
				if (varr[i] == vi)
				{
					varr[i] = -1;
					break;
				}
			}

			// ��ӡ���ι�����СȨֵ�ߵ���������
			printf("%d-%d, ", mg.vexs[ui], mg.vexs[vi]);
		}
		// û���� varr ���ҵ������������㣬˵������δ��ͨ�Ķ��㣬��ͼ������ͨͼ
		else
		{
			printf("Error: This graph is not connented.\n");
			return;
		}
	}
	printf("\b\b \n");
}

void MiniSpanTreeKruskal(MGraph mg)
{
	// 1. �������� earr�����ڴ洢�·����������ıߣ�ʵ�ʴ洢���ǱߵĶ����±���������� p_arc[i][j] ��Ϊ i*10+j����
	// 2. ����ͼ�����бߣ��ҳ������������������ı� a[i][j]��������� earr �У�
	//    (1) Ȩֵ��С��
	//	  (2) ���� earr �У�����˳��洢���ص㣬������ i*10+j �� j*10+i ������ earr �У���
	//	  (3) ������ earr �����еı��γɻ�·����·�жϷ������·�˵������
	// 3. �ظ� 2 ֱ�� earr �бߵ����� = ͼ�Ķ������ - 1��
	// 
	// ����жϻ�·��
	//	(1) ����һ������ farr�����ڴ洢ͼ�и�������ı�ʶ��
	//	(2) ����ͼ�Ķ��㣬��ȡ����λ�� i �Ͷ�����Ϣ v��Ȼ���� farr[i] = v����ʼʱ�����ʶ������ͬ���ʿ���Ϊ������Ϣ����
	//	(3) �Ժ�ѡ�ߣ��ж������������� farr �б�ʶ�Ƿ���ͬ����ͬ����γɻ�·����ͬ�򲻻��γɻ�·��
	//	(4) �����γɻ�·�������������������Դ��� earr �У����轫����һ�����㣨�Լ�����
	//		��ö����ʶ��ͬ�Ķ��㣩�ı�ʶ����Ϊ��һ������ı�ʶ����Ϊ�����ж����ݡ�

	printf("MiniSpanTreeKruskal: ");

	// �洢Ŀ��ߵ����飨ʵ�ʴ洢���ǱߵĶ����±���������� p_arc[i][j] ��Ϊ i*10+j��
	int earr[MAX_VERTEX_NUM * MAX_VERTEX_NUM];

	// earr �д���ıߵ�����
	int enm = 0;

	// �洢ͼ�и��������ʶ������
	VertexType farr[MAX_VERTEX_NUM];

	// ��ʼʱ���ø�������ı�ʶΪ�䶥����Ϣ
	for (int i = 0; i < mg.vexnum; i++)
	{
		farr[i] = mg.vexs[i]; // ����ͼ��˳��洢�ص㣬ͼ�Ķ����ڶ��������е�λ�ô� 0 ��ʼ���δ��
	}

	while (enm < mg.vexnum - 1)
	{
		// ������������СȨֵ
		int mini = INFINITY;
		// ��СȨֵ�ߵ���������
		int ui = -1, vi = -1;

		// Ѱ�����������ı�
		for (int i = 0; i < mg.vexnum; i++)
		{
			for (int k = 0; k < mg.vexnum; k++)
			{
				if (mg.arcs[i][k].adj < mini) // Ȩֵ��С
				{
					int in = 0;
					for (int m = 0; m < mg.arcnum; m++)
					{
						if (earr[m] == i * 10 + k || earr[m] == k * 10 + i)
						{
							in = 1;
							break;
						}
					}
					if (!in && farr[i] != farr[k]) // ���� earr �У������ڻ�·
					{
						mini = mg.arcs[i][k].adj;
						ui = i, vi = k;
					}
				}
			}
		}

		// ���ҵ��ıߴ��� earr�������¶����ʶ
		if (ui != -1 && vi != -1)
		{
			earr[enm++] = ui * 10 + vi;
			for (int i = 0; i < mg.vexnum; i++)
			{
				if (farr[i] == farr[vi])
				{
					farr[i] = farr[ui];
				}
			}

			// ��ӡ���ι�����СȨֵ�ߵ���������
			printf("%d-%d, ", mg.vexs[ui], mg.vexs[vi]);
		}
		// û���ҵ����������ıߣ�˵������δ��ͨ�Ķ��㣬��ͼ������ͨͼ
		else
		{
			printf("Error: This graph is not connected.\n");
			return;
		}
	}
	printf("\b\b \n");
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// ����ͼ���ڽӱ�洢��ز���
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
int LocateALVex(ALGraph ag, VertexType v)
{
	for (int i = 0; i < ag.vexnum; i++)
	{
		if (ag.vertices[i].data == v)
		{
			return i;
		}
	}
	return -1;
}

void CreateALGraph(ALGraph* p_a, VertexType vexs[], int vexnum, char* arcs)
{
	// ��ʼ�������ڽӱ��ͼ�ṹ�壬����������ö��������
	// ���� arcs �ַ�������ȡͼ���͡��߻��������߻����飻
	// ����ͼ�����͡��߻����������ݱ߻�����Ϊÿ������������Ӧ����
	// ������ζ������顢������Ӧ��������ͼ�Ķ������飬���ͼ�Ĺ�����

	// �������
	p_a->vexnum = vexnum;

	// ��ʼ����������
	for (int i = 0; i < vexnum; i++)
	{
		p_a->vertices[i].data = vexs[i];
		p_a->vertices[i].p_arc = NULL;
	}

	// ͼ����
	GetGraphKind(arcs, &(p_a->kind));

	// �߻���Ϣ
	ArcItem* arc_arr = (ArcItem*)malloc(sizeof(ArcItem) * vexnum * vexnum);
	if (arc_arr == NULL)
	{
		printf("Error: -- CreateALGraph -- fail to alloc memory.\n");
		exit(EXIT_FAILURE);
	}
	GetArcInfo(arcs, arc_arr, &(p_a->arcnum));

	// Ϊÿ���������ɶ�Ӧ����������ͼ��������Ϊ��β������洢��ͷλ�ã�
	for (int i = 0; i < vexnum; i++)
	{
		// ����������Ķ���
		VertexType v = p_a->vertices[i].data;

		// ָ������β����ָ��
		ArcNode* p_tail = NULL;

		// �����߻����飬��ȡͬ����һ�𹹳ɱ߻򻡵���һ�����ͷ
		for (int k = 0; k < p_a->arcnum; k++)
		{
			// ���� v ��Ӧ����һ�����ͷ
			VertexType w = -1;

			// ��������ͼ��������ֻҪ������������һ�������� v ����
			if (p_a->kind == UDG || p_a->kind == UDN)
			{
				if (v == arc_arr[k].v)
				{
					w = arc_arr[k].w;
				}
				else if (v == arc_arr[k].w)
				{
					w = arc_arr[k].v;
				}
			}
			// ��������ͼ�������������ϸ��� v �ǻ�β��������ж�
			else
			{
				if (v == arc_arr[k].v)
				{
					w = arc_arr[k].w;
				}
			}

			// Ϊ w ���ɶ�Ӧ��������
			if (w != -1)
			{
				ArcNode* p_n = (ArcNode*)malloc(sizeof(ArcNode));
				if (p_n == NULL)
				{
					printf("Error: -- CreateALGraph -- fail to alloc memory.\n");
					exit(EXIT_FAILURE);
				}
				p_n->adjvex = LocateALVex(*p_a, w);
				p_n->p_info = (InfoType*)malloc(sizeof(InfoType));
				*(p_n->p_info) = arc_arr[k].weight;
				p_n->p_next = NULL;

				// ��δ�������䱸������ p_n ��Ϊ����ͷ���
				if (p_a->vertices[i].p_arc == NULL)
				{
					p_a->vertices[i].p_arc = p_n;
				}
				// ���䱸���� p_n ��Ϊ����β���
				else
				{
					p_tail->p_next = p_n;
				}
				p_tail = p_n;
			}
		}
	}

	free(arc_arr);
}

void TopologicalSort(ALGraph ag, int tparr[])
{
	// 1. ��� AOV ͼ�и����������ȣ��������飻
	// 2. �ҳ����Ϊ 0 �Ķ��� v����ӡ��������� -1��
	// 3. �ҳ������� v Ϊ��β�Ļ�ͷ w��������� -1��
	// 4. �ظ� 2-3 ֱ��û�����Ϊ 0 �Ķ��㣬������ɡ�

	// ����洢ͼ�и�������ȵ����飬ע�������ʹ�ö���λ��
	// ���涥�㱾��ind_arr[i] ��ʾλ��Ϊ i �Ķ������ȡ�
	int ind_arr[MAX_VERTEX_NUM] = { 0 };

	// ���ͼ�и�����������
	// �����ڽӱ�洢�ص㣬ÿ����������һ��������������ö����Ӧ�����л�ͷ��λ�ã�
	// ��ˣ�����ͼ�ж�����˵��ÿ������һ���������У��Ͷ�һ��ָ�����Ļ�����ȼ�һ��
	for (int i = 0; i < ag.vexnum; i++)
	{
		for (ArcNode* p_arc = ag.vertices[i].p_arc; p_arc; p_arc = p_arc->p_next)
		{
			ind_arr[p_arc->adjvex]++; // p_arc->adjvex �Ƕ���λ�ã�����ͬ ind_arr ʹ�ö���λ�ô��涥��������
		}
	}

	// ind_arr �������Ϊ 0 �Ķ������
	int zcount = 0;

	// �ظ�Ѱ�����Ϊ 0 �Ķ��㣬�����з��ʵȴ���
	for (int i = 0; i < ag.vexnum; i++)
	{
		// �ҳ����Ϊ 0 �Ķ���
		if (ind_arr[i] == 0)
		{
			// ���ʸö��㣬��������� -1
			ind_arr[i] -= 1;
			tparr[zcount++] = i;

			// �������Ըö���Ϊ��β�Ļ�ͷ�������� -1
			for (ArcNode* p_arc = ag.vertices[i].p_arc; p_arc; p_arc = p_arc->p_next)
			{
				ind_arr[p_arc->adjvex]--;
			}

			i = -1; // �ظ�Ѱ�����Ϊ 0 �Ķ��㣬ֱ���޷��ҵ�
		}
	}

	// ind_arr �������Ϊ 0 �Ķ������С��ͼ�Ķ��������˵���л�
	if (zcount < ag.vexnum)
	{
		printf("Error: There is circle in this graph.\n");
	}
}

void CriticalPath(ALGraph ag)
{
	// 1. ��� AOE �ж����Ӧ���������У���Ϊ��[a, b, c, d, e]��
	// 2. ����һ���������δ洢 [Ve(a), Ve(b), Ve(c), Ve(d), Ve(e)]����ʼֵ��Ϊ 0��
	// 3. ����������������У���
	//		a ��Դ�㣬Ve(a) = 0��Ѱ�� a �ڽӵĻ�ͷ���㣨���� b �� c������
	//			Ve(b) = max{ Ve(b), Ve(a) + <a,b> ����Ȩֵ }��
	//			Ve(c) = max{ Ve(c), Ve(a) + <a,c> ����Ȩֵ }��
	//		b �� Ve(b) �������Ѱ�� b �ڽӵĻ�ͷ���㣨��ֻ�� d������
	//			Ve(d) = max{ Ve(d), Ve(b) + <b,d> ����Ȩֵ }��
	//		c �� Ve(c) �������Ѱ�� c �ڽӵĻ�ͷ���㣨��ֻ�� d������
	//			Ve(d) = max{ Ve(d), Ve(c) + <c,d> ����Ȩֵ }��
	//		d �� Ve(d) �������Ѱ�� d �ڽӵĻ�ͷ���㣨��ֻ�� e������
	//			Ve(e) = max{ Ve(e), Ve(d) + <d,e> ����Ȩֵ }��
	//		e �� Ve(e) ����������ǻ�㣬������
	// 4. ����һ���������δ洢 [Vl(a), Vl(b), Vl(c), Vl(d), Vl(e)]����ʼֵ��Ϊ�����
	// 5. �������������������У���
	//		e �ǻ�㣬 Vl(e) = Ve(e)��
	//		Ѱ�� d �ڽӵĻ�ͷ���㣨ֻ�� e������ Vl(d) = min{ Vl(d), Vl(e) - <d,e> ����Ȩֵ }��
	//		Ѱ�� c �ڽӵĻ�ͷ���㣨ֻ�� d������ Vl(c) = min{ Vl(c), Vl(d) - <c,d> ����Ȩֵ }��
	//		Ѱ�� b �ڽӵĻ�ͷ���㣨ֻ�� d������ Vl(b) = min{ Vl(b), Vl(d) - <b,d> ����Ȩֵ }��
	//		Ѱ�� a �ڽӵĻ�ͷ���㣨�� b �� c������
	//			Vl(a) = min{ Vl(a), Vl(b) - <a,b> ����Ȩֵ, Vl(c) - <a,c> ����Ȩֵ }��
	// 6. ������֪������� Ve �� Vl��������� e �� l���軡�Ļ�β����ͷ�ֱ�Ϊ v��w����
	//		e = Ve(v)��l = Vl(w) - <v,w> ����Ȩֵ��
	// 7. ��������������У����������Դ�㵽���Ĺؼ������ e == l �Ļ��������ɵõ��ؼ�·����

	// ��ȡ������������У�tparr ��ʵ�ʴ洢���Ƕ�����ͼ�Ķ��������е�λ��
	int tparr[MAX_VERTEX_NUM] = { 0 };
	TopologicalSort(ag, tparr);

	printf("CriticalPath: ");

	// �洢�������紥��ʱ������飬������˳��ͬͼ�Ķ�������
	VertexType vearr[MAX_VERTEX_NUM] = { 0 };

	// ������˳���󶥵�����紥��ʱ�䣬���� vearr
	for (int i = 0; i < ag.vexnum; i++)
	{
		int idx = tparr[i];
		VexNode v = ag.vertices[idx];

		// Ѱ�������� v �ڽӵĻ�ͷ w������ Ve(w)
		for (ArcNode* p_arc = v.p_arc; p_arc; p_arc = p_arc->p_next)
		{
			int wpos = p_arc->adjvex;
			int weight = *(p_arc->p_info);
			if (vearr[idx] + weight > vearr[wpos])
			{
				vearr[wpos] = vearr[idx] + weight;
			}
		}
	}

	// �洢����������ʱ������飬������˳��ͬͼ�Ķ�������
	VertexType vlarr[MAX_VERTEX_NUM];
	// ����ĳ�ʼ������ʱ����Ϊ�����
	for (int i = 0; i < ag.vexnum; i++)
	{
		vlarr[i] = INFINITY;
	}

	// ������˳���󶥵���������¼������� vlarr
	for (int i = ag.vexnum - 1; i > -1; i--)
	{
		int idx = tparr[i];
		VexNode v = ag.vertices[idx];

		if (v.p_arc == NULL)
		{
			// ����������ʱ��������紥��ʱ��
			vlarr[idx] = vearr[idx];
		}
		else
		{
			// Ѱ�������� v �ڽӵĻ�ͷ w������ Vl(w)
			for (ArcNode* p_arc = v.p_arc; p_arc; p_arc = p_arc->p_next)
			{

				int wpos = p_arc->adjvex;
				int weight = *(p_arc->p_info);
				if (vlarr[wpos] - weight < vlarr[idx])
				{
					vlarr[idx] = vlarr[wpos] - weight;
				}
			}
		}
	}

	// ������˳������������飬����������еĶ���Ϊ��β�����л������翪ʼʱ�������ʼʱ��
	for (int i = 0; i < ag.vexnum - 1; i++)
	{
		// ��β�����ڶ��������е�λ��
		int idx = tparr[i];

		// �������翪ʼʱ������仡β��������紥��ʱ��
		int e = vearr[idx];

		// ������β�����Ӧ�������������������ʼʱ��
		for (ArcNode* p_arc = ag.vertices[idx].p_arc; p_arc; p_arc = p_arc->p_next)
		{
			// ��������ʼʱ�䣬���ڻ�ͷ�����������ʱ�� - �û�Ȩֵ
			int l = vlarr[p_arc->adjvex] - *(p_arc->p_info);
			
			// ���������翪ʼʱ���������ʼʱ�䣬˵���ǹؼ��
			if (e == l)
			{
				// ��ӡ���йؼ�������и��Ǵ�Դ�㵽���Ĺؼ����ɵ�·������Ϊ�ؼ�·���������ж���
				printf("%d-%d(%d), ", ag.vertices[idx].data, ag.vertices[p_arc->adjvex].data, *(p_arc->p_info));
			}
		}
	}
	printf("\b\b \n");
}

void Dijkstra(ALGraph ag, VertexType startv)
{
	// ���� darr �����㵽����������·�����ȣ�darr[i] ��ʾ��㵽���� i �����·�����ȣ�
	// ���� farr ����Ƿ����ҵ���������������·���ı�ʶ��farr[i] = 1 ��ʾ���ҵ���㵽���� i �����·����
	// ��ά���� parr ������·�����ξ����Ķ������У�parr[i][x]���� i �У������㵽���� i �����·���������У�
	// 
	// 1. ��ʼ���� darr[i] �� parr[i][x]��
	//		(1) ��㵽����������·������Ϊ 0�����·����������ֻ�������㱾��
	//		(2) ����㵽���� i ���� i Ϊ��ͷ�Ļ����� darr[i] ΪȨֵ��parr[i][0] Ϊ��ͷ��
	// 2. ��ȡ darr �������������·�����ȵ���Сֵ�������Ӧ�Ķ���Ϊ v������ farr[v] = 1��
	// 3. ��������Ϊ��ͷ�� v �ڽӵĶ��㣨��Ϊ w������ farr[v] != 1 �� darr[v] + <v,w> ����Ȩֵ < darr[w] ʱ��
	//		(1) ���� darr[w] = darr[v] + <v,w> ����Ȩֵ��
	//		(2) ��������� w �����·����������Ϊ����� v �����·���������� + w��
	// 4. �ظ� 2-3 ֱ�� farr �еĶ����ʶȫΪ 1��

	// �ж����λ���Ƿ�Ϸ�
	int svidx = LocateALVex(ag, startv);
	if (svidx < 0 || svidx >= ag.vexnum)
	{
		printf("Error: -- Dijkstra -- the index of start vertex is invalid.\n");
		return;
	}

	// �����㵽����������·������
	int darr[MAX_VERTEX_NUM] = { 0 };
	for (int i = 0; i < ag.vexnum; i++)
	{
		if (i != svidx)
		{
			darr[i] = INFINITY;
		}
	}

	// ��Ŷ�������ҵ����·���ı�ʶ
	int farr[MAX_VERTEX_NUM] = { 0 };

	// �����������������·����Ӧ�Ķ�������
	int parr[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			parr[i][j] = -1;
		}
	}

	// ���ҵ����·���Ķ������
	int fcount = 0;
	// Ѱ�����������������·��
	while (fcount < ag.vexnum)
	{
		int mval = INFINITY, midx = -1;

		// ��ȡ��δȷ�����·���� darr �����·������ֵ��С�Ķ���
		for (int i = 0; i < ag.vexnum; i++)
		{
			if (darr[i] < mval && farr[i] == 0)
			{
				mval = darr[i];
				midx = i;
			}
		}

		// �����ҵ����� midx ��Ϊ���ο���ȷ�����·���Ķ���
		if (midx != -1)
		{
			// ���� midx ��Ӧ�� farr ��ʶ
			farr[midx] = 1;
			fcount++;

			// ������Ϊ��ͷ�� midx �ڽӵĶ�������·�����ȼ���Ӧ�Ķ�������
			for (ArcNode* p_arc = ag.vertices[midx].p_arc; p_arc; p_arc = p_arc->p_next)
			{
				int weight = *(p_arc->p_info); // ����Ȩֵ

				if (darr[midx] + weight < darr[p_arc->adjvex])
				{
					// ����ͷ�����·������
					darr[p_arc->adjvex] = darr[midx] + weight;

					// ���»�ͷ��ǰ���·�������Ķ�������
					for (int k = 0; k < ag.vexnum; k++)
					{
						if (parr[midx][k] != -1)
						{
							parr[p_arc->adjvex][k] = parr[midx][k];
						}
						else
						{
							parr[p_arc->adjvex][k] = p_arc->adjvex;
							break;
						}
					}
				}
			}

			// ������㱾���������벻����������·����������
			// ��ָ�����������·������ֻ����һ�����㣬���䱾��
			if (midx == svidx)
			{
				parr[midx][0] = midx;
			}
		}
		// ��δ�ҵ���˵�����ڲ��������ͨ�Ķ��㣬ֱ�Ӹ�����Щ�����Ӧ�� farr ��ʶ
		else
		{
			for (int i = 0; i < ag.vexnum; i++)
			{
				if (darr[i] == INFINITY)
				{
					farr[i] = 1;
					fcount++;
				}
			}
		}
	}

	// ��ӡ���·��
	for (int i = 0; i < ag.vexnum; i++)
	{ 
		printf("Dijkstra for vertex %d to vertex %d: ", startv, ag.vertices[i].data);

		if (darr[i] == INFINITY)
		{
			printf("No connection.\n");
		}
		else
		{
			printf("%d-", startv);
			for (int j = 0; j < ag.vexnum; j++)
			{
				if (parr[i][j] != -1)
				{
					printf("%d-", ag.vertices[parr[i][j]].data);
				}
			}
			printf("\b, distance: %d.\n", darr[i]);
		}
	}
}

void Floyd(ALGraph ag)
{
	// 1. ��������ά���� D �� P��
	//		D[i][j] ��ʾ���� i �� j �����·�����ȣ�
	//		P[i][j] ��ʾ���� i �� j �����·�������ĵ�һ�����㣻
	// 2. ��ʼ���� D �� P ��ֵ��
	//		D[i][j]�������ڻ� <i,j> ����ֵΪ��Ȩ����������Ϊ 0��i == j���������i != j����
	//		P[i][j]����ʼ����Ϊ j��
	// 3. �� V ��ͼ�����ж��㼯�ϣ����δ� V ��ȡ���� k���ж��Ƿ� D[i][k] + D[k][j] < D[i][j]��
	//		���ǣ������ D[i][j] = D[i][k] + D[k][j]������ P[i][j] = k��
	//		������������
	// 4. ���� D ��Ϊ������������֮������·������P ��Ϊ���·�������ĵ�һ������ľ���

	// �洢��������·�����ȵĶ�ά����
	int darr[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = { 0 };

	// �洢��������·�������ĵ�һ������Ķ�ά����
	int parr[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = { 0 };

	// ���� darr �� parr ��ֵ
	for (int i = 0; i < ag.vexnum; i++)
	{
		ArcNode* p_arc = ag.vertices[i].p_arc;

		for (int j = 0; j < ag.vexnum; j++)
		{
			if (p_arc != NULL && j == p_arc->adjvex)
			{
				darr[i][j] = *(p_arc->p_info);
			}
			else if (j != i && darr[i][j] == 0)
			{
				darr[i][j] = INFINITY;
			}
			parr[i][j] = j;
		}
	}

	// ������ͼ�����ж����ۻ����� darr �� parr
	for (int k = 0; k < ag.vexnum; k++)
	{
		for (int i = 0; i < ag.vexnum; i++)
		{
			for (int j = 0; j < ag.vexnum; j++)
			{
				if (darr[i][k] + darr[k][j] < darr[i][j])
				{
					darr[i][j] = darr[i][k] + darr[k][j];
					parr[i][j] = k;
				}
			}
		}
	}

	// ��ӡ���
	printf("Floyd distance matrix:\n");
	for (int i = 0; i < ag.vexnum; i++)
	{
		for (int j = 0; j < ag.vexnum; j++)
		{
			if (darr[i][j] != INFINITY)
			{
				printf("%4d ", darr[i][j]);
			}
			else
			{
				printf("infi ");
			}
		}
		printf("\n");
	}
	printf("Floyd path matrix:\n");
	for (int i = 0; i < ag.vexnum; i++)
	{
		for (int j = 0; j < ag.vexnum; j++)
		{
			if (darr[i][j] != INFINITY)
			{
				printf("%4d ", ag.vertices[parr[i][j]].data);
			}
			else
			{
				printf("null ");
			}
		}
		printf("\n");
	}
}
