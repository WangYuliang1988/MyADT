#include "graph.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 定义工具函数，用于解析描述图的边或弧集合的约定格式的字符串
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
* 记录解析结果的结构体
*/
typedef struct
{
	VertexType v; // 边顶点或弧尾
	VertexType w; // 边顶点或弧头
	int weight; // 边或弧的权值
}ArcItem;

/*
* 获取图类型
*/
void GetGraphKind(char* adjs, GraphKind* p_kind)
{
	GraphKind kind = -1;
	int comnum = 0; // 逗号个数，一个 () 或 <> 内有两个逗号，说明带有权值
	for (int i = 0; adjs[i] != '\0'; i++)
	{
		if (adjs[i] == ',')
		{
			comnum++;
		}
		else if (adjs[i] == ')') // 无向
		{
			kind = (comnum == 2) ? UDN : UDG;
			break;
		}
		else if (adjs[i] == '>') // 有向
		{
			kind = (comnum == 2) ? DN : DG;
			break;
		}
	}
	(*p_kind) = kind;
}

/*
* 获取解析得到的边或弧信息
*/
void GetArcInfo(char* adjs, ArcItem* arc_arr, int* p_arcnum)
{
	int arcnum = 0; // 边或弧的条数
	VertexType v = 0; // 边或弧的顶点
	VertexType w = 0; // 边或弧的顶点
	int weight = 0; // 边或弧的权重
	int to_set_v = 0, to_set_w = 0, to_set_weight = 0; // 是否将要设置 v/w/weight
	char numstr[6]; // 数字字符串（数组表示），此处假设数字最大为 5 位正整数
	int curi = 0; // 本次解析出的数字字符，应该写入到表示数字字符串的数组位置

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
// 定义图的顺序存储相关操作
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
int LocateMVex(MGraph mg, VertexType v)
{
	int i = 0;
	// 遍历顶点数组，寻找 v
	while (i < mg.vexnum)
	{
		if (mg.vexs[i] == v)
		{
			break;
		}
		i++;
	}
	// 未找到，返回 -1
	if (i == mg.vexnum)
	{
		return -1;
	}
	return i;
}

void CreateMGraph(MGraph* p_g, VertexType vexs[], int vexnum, char* adjs)
{
	// 构建基于顺序结构的图，实际就是设置两个数组：
	//	1. 存储顶点信息的一维数组，顶点信息由传入函数的参数直接给出；
	//	2. 存储边或弧信息的二维数组，边或弧的信息通过解析 adjs 字符串获得。
	
	// 设置顶点信息
	for (int i = 0; i < vexnum; i++)
	{
		p_g->vexs[i] = vexs[i];
	}
	p_g->vexnum = vexnum;

	// 设置图类型并初始化所有边或弧信息
	GetGraphKind(adjs, &(p_g->kind));
	for (int i = 0; i < vexnum; i++)
	{
		for (int k = 0; k < vexnum; k++)
		{
			p_g->arcs[i][k].adj = (p_g->kind == DG || p_g->kind == UDG) ? 0 : INFINITY;
			p_g->arcs[i][k].p_info = NULL;
		}
	}

	// 解析描述边或弧信息的字符串并根据结果进行设置
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
			// 网的边或弧设置为权值
			p_g->arcs[m][n].adj = weight;

			if (p_g->kind == UDN)
			{
				p_g->arcs[n][m].adj = weight;
			}
		}
		else
		{
			// 图的边或弧设置为 1
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
	// 1. 从图中任选一个顶点，作为初始当前顶点入栈；
	// 2. 获取栈顶元素作为当前顶点 cv，（若 cv 未被访问则）访问 cv；
	// 3. 寻找和点当前顶点 cv 相邻且未被访问过的顶点，设为 cn：
	//		若能找到，则将 cn 入栈；
	//		若未找到，则将栈顶元素出栈，并判断是否栈空，栈空则重选一个未访问过的顶点入栈；
	// 4. 重复执行 2-3，直至栈空，搜索结束。

	// 用于记录顶点是否被访问过的数组
	int visarr[MAX_VERTEX_NUM] = { 0 };

	// 存储历次当前顶点的栈
	SeqStack stack;
	InitSeqStack(&stack);

	// 获取栈中元素的变量，因栈中元素数据类型同图顶点数据类型不一致，需要做个中转
	ElemType elem = -1;

	// 当前顶点
	VertexType cv = -1;

	// 同当前顶点相邻且未被访问的顶点
	VertexType cn = -1;

	// 当前顶点在图的顶点数组中的位置
	int cvloc = -1;

	// 选一个顶点作为初始当前顶点入栈
	Push(&stack, mg.vexs[0]);
	printf("DFSTraverse: ");

	while (!IsStackEmpty(stack))
	{
		cn = -1; // 开始寻找前先重置 cn

		// 从栈顶获取当前顶点，若未访问过则进行访问
		GetTop(stack, &elem);
		cv = (VertexType)elem;
		cvloc = LocateMVex(mg, cv);
		if (visarr[cvloc] == 0)
		{
			printf("%d, ", cv);
			visarr[cvloc] = 1;
		}

		// 寻找同当前顶点相邻且未被访问的顶点 cn
		for (int i = 0; i < mg.vexnum; i++)
		{
			// arcs[cvloc][i] 和 arcs[i][cvloc]，对无向图（网）是相同边，对有向图（网）是不同边；
			// 此处的判断是可以同时满足有向图和无向图的最大判断（实际上，满足有向图自然就满足无向图）。
			if (visarr[i] == 0 &&
				((mg.arcs[cvloc][i].adj > 0 && mg.arcs[cvloc][i].adj != INFINITY) ||
					(mg.arcs[i][cvloc].adj > 0 && mg.arcs[i][cvloc].adj != INFINITY)))
			{
				cn = mg.vexs[i];
				break;
			}
		}

		// 若能找到，则 cn 作为新的当前顶点入栈；
		// 否则，栈顶元素出栈，回退至上个当前顶点。
		if (cn != -1)
		{
			Push(&stack, cn);
		}
		else
		{
			Pop(&stack, &elem);

			// 若栈变空，则重选一个未被访问的顶点作为当前顶点入栈
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
				// 如果所有顶点都已访问过，说明查找完成，做个打印上的格式优化
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
	// 1. 从图中任选一顶点，访问，并作为初始当前顶点入队；
	// 2. 获取队首元素作为当前顶点 cv ，寻找和 cv 相邻且未被访问的顶点 cn：
	//		若能找到，则访问 cn 并将 cn 入队；
	//		若未找到，则队首元素出队，并判断是否队空，队空则重选一个未被访问过的顶点入队；
	// 3. 重复 2 直至队空，搜索结束。

	// 用来记录图总顶点是否被访问过的数组
	int visarr[MAX_VERTEX_NUM] = { 0 };

	// 按顺序存储被访问过的顶点的队列
	LinkQueue queue;
	InitLinkQueue(&queue);

	// 获取队列元素的变量，因队列元素数据类型和图顶点数据类型不一致，需要做个中转
	ElemType elem = -1;

	// 当前顶点
	VertexType cv = -1;

	// 同当前顶点相邻且未被访问的顶点
	VertexType cn = -1;

	// cv 在图的顶点数组中的位置
	int cvloc = -1;

	// cn 在图的顶点数组中的位置
	int cnloc = -1;

	// 选一个顶点访问，并作为初始当前顶点入队
	cvloc = 0;
	visarr[cvloc] = 1;
	cv = mg.vexs[cvloc];
	EnLinkQueue(&queue, cv);
	printf("BFSTraverse: %d, ", cv);

	while (!IsLinkQueueEmpty(queue))
	{
		cn = cnloc = -1; // 开始寻找前先重置 cn 和 cnloc

		// 获取队首元素作为当前顶点
		GetLinkQueueHead(queue, &elem);
		cv = (VertexType)elem;
		cvloc = LocateMVex(mg, cv);

		// 寻找同当前顶点相邻且未被访问的顶点 cn
		for (int i = 0; i < mg.vexnum; i++)
		{
			// arcs[cvloc][i] 和 arcs[i][cvloc]，对无向图（网）是相同边，对有向图（网）是不同边；
			// 此处的判断是可以同时满足有向图和无向图的最大判断（实际上，满足有向图自然就满足无向图）。
			if (visarr[i] == 0 &&
				((mg.arcs[cvloc][i].adj > 0 && mg.arcs[cvloc][i].adj != INFINITY) ||
					(mg.arcs[i][cvloc].adj > 0 && mg.arcs[i][cvloc].adj != INFINITY)))
			{
				cn = mg.vexs[i];
				cnloc = i;
				break;
			}
		}

		// 若能找到，则访问 cn 并将 cn 入队（注意：队列是队尾插入、队首删除，插入 cn 后队首尾元素仍是当前顶点 cv）；
		// 若未找到，则队首元素（即当前顶点 cv）出队（注意：此后，新的队首元素，即 cv 的第一个 cn，将作为新的 cv）。
		if (cn != -1)
		{
			visarr[cnloc] = 1;
			printf("%d, ", cn);
			EnLinkQueue(&queue, cn);
		}
		else
		{
			DeLinkQueue(&queue, &elem);

			// 判断是否队空，队空则重选一个未被访问过的顶点，访问并入队
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
				// 如果所有顶点都已访问过，说明查找完成，做个打印上的格式优化
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
	// 说明：根据图的顺序存储性质，可以使用顶点在数组中的位置来指代顶点本身，
	// 本思路中，uarr 和 varr 在代码实现时，即通过存储顶点位置来简化操作。
	// 
	// 1. 定义两个数组 uarr 和 varr，开始时 uarr 为空，varr 包含图的所有顶点；
	// 2. 从 varr 中任选一个顶点放入 uarr 中，并将该顶点从 varr 中删除；
	// 3. 在 varr 中寻找一个顶点，该顶点在 varr 所有能和 uarr 中顶点构成的边中，
	//    具有最小权值，然后将该顶点放入 uarr 中，同时从 varr 中删除该顶点；
	// 5. 重复 3 直至 uarr 中包含图的全部顶点。

	printf("MiniSpanTreePrim: ");

	// 存放最小生成树顶点位置的数组
	VertexType uarr[MAX_VERTEX_NUM];

	// 存放除最小生成树顶点外图中剩余顶点位置的数组
	VertexType varr[MAX_VERTEX_NUM];

	// 记录 uarr 包含的顶点位置个数
	int unum = 0;

	// 设置 varr 包含图的全部顶点位置
	for (int i = 0; i < mg.vexnum; i++)
	{
		varr[i] = i; // 根据图的顺序存储特点，图的顶点在顶点数组中的位置从 0 开始依次存放
	}

	// 从 varr 中选择一个顶点位置放入 uarr，然后在 varr 中删除（设为 -1）该顶点位置
	uarr[unum++] = varr[0];
	varr[0] = -1;

	while (unum < mg.vexnum)
	{
		int mini = INFINITY; // 本次找到的最小权值
		int ui = -1; // 拥有最小权值的边包含的 uarr 中的顶点在顶点数组中的位置
		int vi = -1; // 拥有最小权值的边包含的 varr 中的顶点在顶点数组中的位置

		// 查找 varr 中可以和 uarr 中顶点构成最小权值边的顶点位置
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

		// 将本次找到的顶点位置放入 uarr，并从 varr 中删除该顶点位置
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

			// 打印本次构成最小权值边的两个顶点
			printf("%d-%d, ", mg.vexs[ui], mg.vexs[vi]);
		}
		// 没能在 varr 中找到符合条件顶点，说明存在未连通的顶点，该图不是连通图
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
	// 1. 定义数组 earr，用于存储下方满足条件的边（实际存储的是边的顶点下标计算结果，如 p_arc[i][j] 存为 i*10+j）；
	// 2. 遍历图的所有边，找出满足下面三个条件的边 a[i][j]，将其存入 earr 中：
	//    (1) 权值最小；
	//	  (2) 不在 earr 中（基于顺序存储的特点，需满足 i*10+j 和 j*10+i 都不在 earr 中）；
	//	  (3) 不会与 earr 中已有的边形成回路（回路判断方法见下方说明）；
	// 3. 重复 2 直至 earr 中边的条数 = 图的顶点个数 - 1。
	// 
	// 如何判断回路：
	//	(1) 定义一个数组 farr，用于存储图中各个顶点的标识；
	//	(2) 遍历图的顶点，获取顶点位置 i 和顶点信息 v，然后令 farr[i] = v（初始时顶点标识各不相同，故可设为顶点信息）；
	//	(3) 对候选边，判断其两个顶点在 farr 中标识是否相同：相同则会形成回路，不同则不会形成回路；
	//	(4) 若不形成回路且满足所有条件，可以存入 earr 中，则还需将其中一个顶点（以及所有
	//		与该顶点标识相同的顶点）的标识，设为另一个顶点的标识，作为后续判断依据。

	printf("MiniSpanTreeKruskal: ");

	// 存储目标边的数组（实际存储的是边的顶点下标计算结果，如 p_arc[i][j] 存为 i*10+j）
	int earr[MAX_VERTEX_NUM * MAX_VERTEX_NUM];

	// earr 中存入的边的数量
	int enm = 0;

	// 存储图中各个顶点标识的数组
	VertexType farr[MAX_VERTEX_NUM];

	// 初始时设置各个顶点的标识为其顶点信息
	for (int i = 0; i < mg.vexnum; i++)
	{
		farr[i] = mg.vexs[i]; // 根据图的顺序存储特点，图的顶点在顶点数组中的位置从 0 开始依次存放
	}

	while (enm < mg.vexnum - 1)
	{
		// 满足条件的最小权值
		int mini = INFINITY;
		// 最小权值边的两个顶点
		int ui = -1, vi = -1;

		// 寻找满足条件的边
		for (int i = 0; i < mg.vexnum; i++)
		{
			for (int k = 0; k < mg.vexnum; k++)
			{
				if (mg.arcs[i][k].adj < mini) // 权值较小
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
					if (!in && farr[i] != farr[k]) // 不在 earr 中，不存在回路
					{
						mini = mg.arcs[i][k].adj;
						ui = i, vi = k;
					}
				}
			}
		}

		// 将找到的边存入 earr，并更新顶点标识
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

			// 打印本次构成最小权值边的两个顶点
			printf("%d-%d, ", mg.vexs[ui], mg.vexs[vi]);
		}
		// 没能找到满足条件的边，说明存在未连通的顶点，该图不是连通图
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
// 定义图的邻接表存储相关操作
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
	// 初始化基于邻接表的图结构体，根据入参设置顶点个数；
	// 解析 arcs 字符串，获取图类型、边或弧条数、边或弧数组；
	// 设置图的类型、边或弧条数，根据边或弧数组为每个顶点生成相应链表；
	// 根据入参顶点数组、顶点相应链表，设置图的顶点数组，完成图的构建。

	// 顶点个数
	p_a->vexnum = vexnum;

	// 初始化顶点数组
	for (int i = 0; i < vexnum; i++)
	{
		p_a->vertices[i].data = vexs[i];
		p_a->vertices[i].p_arc = NULL;
	}

	// 图类型
	GetGraphKind(arcs, &(p_a->kind));

	// 边或弧信息
	ArcItem* arc_arr = (ArcItem*)malloc(sizeof(ArcItem) * vexnum * vexnum);
	if (arc_arr == NULL)
	{
		printf("Error: -- CreateALGraph -- fail to alloc memory.\n");
		exit(EXIT_FAILURE);
	}
	GetArcInfo(arcs, arc_arr, &(p_a->arcnum));

	// 为每个顶点生成对应链表（对有向图，顶点作为弧尾，链表存储弧头位置）
	for (int i = 0; i < vexnum; i++)
	{
		// 待分配链表的顶点
		VertexType v = p_a->vertices[i].data;

		// 指向链表尾结点的指针
		ArcNode* p_tail = NULL;

		// 遍历边或弧数组，获取同顶点一起构成边或弧的另一顶点或弧头
		for (int k = 0; k < p_a->arcnum; k++)
		{
			// 顶点 v 对应的另一顶点或弧头
			VertexType w = -1;

			// 对于无向图（网），只要两个顶点中有一个顶点是 v 即可
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
			// 对于有向图（网），必须严格按照 v 是弧尾顶点进行判断
			else
			{
				if (v == arc_arr[k].v)
				{
					w = arc_arr[k].w;
				}
			}

			// 为 w 生成对应的链表结点
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

				// 还未给顶点配备链表，则将 p_n 作为链表头结点
				if (p_a->vertices[i].p_arc == NULL)
				{
					p_a->vertices[i].p_arc = p_n;
				}
				// 已配备，则将 p_n 作为链表尾结点
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
	// 1. 求出 AOV 图中各个顶点的入度，存入数组；
	// 2. 找出入度为 0 的顶点 v，打印，将其入度 -1；
	// 3. 找出所有以 v 为弧尾的弧头 w，将其入度 -1；
	// 4. 重复 2-3 直至没有入度为 0 的顶点，排序完成。

	// 定义存储图中各顶点入度的数组，注意该数组使用顶点位置
	// 代替顶点本身，ind_arr[i] 表示位置为 i 的顶点的入度。
	int ind_arr[MAX_VERTEX_NUM] = { 0 };

	// 求出图中各个顶点的入度
	// 根据邻接表存储特点，每个顶点配有一个链表，链表包含该顶点对应的所有弧头的位置；
	// 因此，对于图中顶点来说，每出现在一个链表结点中，就多一条指向它的弧，入度加一。
	for (int i = 0; i < ag.vexnum; i++)
	{
		for (ArcNode* p_arc = ag.vertices[i].p_arc; p_arc; p_arc = p_arc->p_next)
		{
			ind_arr[p_arc->adjvex]++; // p_arc->adjvex 是顶点位置，正好同 ind_arr 使用顶点位置代替顶点相契合
		}
	}

	// ind_arr 中入度曾为 0 的顶点个数
	int zcount = 0;

	// 重复寻找入度为 0 的顶点，并进行访问等处理
	for (int i = 0; i < ag.vexnum; i++)
	{
		// 找出入度为 0 的顶点
		if (ind_arr[i] == 0)
		{
			// 访问该顶点，并将其入度 -1
			ind_arr[i] -= 1;
			tparr[zcount++] = i;

			// 将所有以该顶点为弧尾的弧头顶点的入度 -1
			for (ArcNode* p_arc = ag.vertices[i].p_arc; p_arc; p_arc = p_arc->p_next)
			{
				ind_arr[p_arc->adjvex]--;
			}

			i = -1; // 重复寻找入度为 0 的顶点，直至无法找到
		}
	}

	// ind_arr 中入度曾为 0 的顶点个数小于图的顶点个数，说明有环
	if (zcount < ag.vexnum)
	{
		printf("Error: There is circle in this graph.\n");
	}
}

void CriticalPath(ALGraph ag)
{
	// 1. 求出 AOE 中顶点对应的拓扑序列，设为：[a, b, c, d, e]；
	// 2. 定义一个数组依次存储 [Ve(a), Ve(b), Ve(c), Ve(d), Ve(e)]，初始值均为 0；
	// 3. 遍历顶点的拓扑序列，则：
	//		a 是源点，Ve(a) = 0，寻找 a 邻接的弧头顶点（设有 b 和 c），则：
	//			Ve(b) = max{ Ve(b), Ve(a) + <a,b> 弧的权值 }；
	//			Ve(c) = max{ Ve(c), Ve(a) + <a,c> 弧的权值 }；
	//		b 的 Ve(b) 已求出，寻找 b 邻接的弧头顶点（设只有 d），则：
	//			Ve(d) = max{ Ve(d), Ve(b) + <b,d> 弧的权值 }；
	//		c 的 Ve(c) 已求出，寻找 c 邻接的弧头顶点（设只有 d），则：
	//			Ve(d) = max{ Ve(d), Ve(c) + <c,d> 弧的权值 }；
	//		d 的 Ve(d) 已求出，寻找 d 邻接的弧头顶点（设只有 e），则：
	//			Ve(e) = max{ Ve(e), Ve(d) + <d,e> 弧的权值 }；
	//		e 的 Ve(e) 已求出，且是汇点，结束；
	// 4. 定义一个数组依次存储 [Vl(a), Vl(b), Vl(c), Vl(d), Vl(e)]，初始值均为无穷大；
	// 5. 逆序遍历顶点的拓扑序列，则：
	//		e 是汇点， Vl(e) = Ve(e)；
	//		寻找 d 邻接的弧头顶点（只有 e），则 Vl(d) = min{ Vl(d), Vl(e) - <d,e> 弧的权值 }；
	//		寻找 c 邻接的弧头顶点（只有 d），则 Vl(c) = min{ Vl(c), Vl(d) - <c,d> 弧的权值 }；
	//		寻找 b 邻接的弧头顶点（只有 d），则 Vl(b) = min{ Vl(b), Vl(d) - <b,d> 弧的权值 }；
	//		寻找 a 邻接的弧头顶点（有 b 和 c），则：
	//			Vl(a) = min{ Vl(a), Vl(b) - <a,b> 弧的权值, Vl(c) - <a,c> 弧的权值 }；
	// 6. 根据已知各顶点的 Ve 和 Vl，求各弧的 e 和 l，设弧的弧尾、弧头分别为 v、w，则：
	//		e = Ve(v)，l = Vl(w) - <v,w> 弧的权值；
	// 7. 按顶点的拓扑序列，依次输出从源点到汇点的关键活动（即 e == l 的弧），即可得到关键路径。

	// 获取顶点的拓扑序列，tparr 中实际存储的是顶点在图的顶点数组中的位置
	int tparr[MAX_VERTEX_NUM] = { 0 };
	TopologicalSort(ag, tparr);

	printf("CriticalPath: ");

	// 存储顶点最早触发时间的数组，顶点存放顺序同图的顶点数组
	VertexType vearr[MAX_VERTEX_NUM] = { 0 };

	// 按拓扑顺序求顶点的最早触发时间，更新 vearr
	for (int i = 0; i < ag.vexnum; i++)
	{
		int idx = tparr[i];
		VexNode v = ag.vertices[idx];

		// 寻找所有与 v 邻接的弧头 w，更新 Ve(w)
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

	// 存储顶点最晚触发时间的数组，顶点存放顺序同图的顶点数组
	VertexType vlarr[MAX_VERTEX_NUM];
	// 顶点的初始最晚触发时间设为无穷大
	for (int i = 0; i < ag.vexnum; i++)
	{
		vlarr[i] = INFINITY;
	}

	// 逆拓扑顺序求顶点的最晚触发事件，更新 vlarr
	for (int i = ag.vexnum - 1; i > -1; i--)
	{
		int idx = tparr[i];
		VexNode v = ag.vertices[idx];

		if (v.p_arc == NULL)
		{
			// 汇点的最晚触发时间等于最早触发时间
			vlarr[idx] = vearr[idx];
		}
		else
		{
			// 寻找所有与 v 邻接的弧头 w，更新 Vl(w)
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

	// 按拓扑顺序遍历顶点数组，求出以数组中的顶点为弧尾的所有弧的最早开始时间和最晚开始时间
	for (int i = 0; i < ag.vexnum - 1; i++)
	{
		// 弧尾顶点在顶点数组中的位置
		int idx = tparr[i];

		// 弧的最早开始时间等于其弧尾顶点的最早触发时间
		int e = vearr[idx];

		// 遍历弧尾顶点对应的链表，求出各弧的最晚开始时间
		for (ArcNode* p_arc = ag.vertices[idx].p_arc; p_arc; p_arc = p_arc->p_next)
		{
			// 弧的最晚开始时间，等于弧头顶点的最晚触发时间 - 该弧权值
			int l = vlarr[p_arc->adjvex] - *(p_arc->p_info);
			
			// 若弧的最早开始时间等于最晚开始时间，说明是关键活动
			if (e == l)
			{
				// 打印所有关键活动，其中覆盖从源点到汇点的关键活动组成的路径，即为关键路径，可能有多条
				printf("%d-%d(%d), ", ag.vertices[idx].data, ag.vertices[p_arc->adjvex].data, *(p_arc->p_info));
			}
		}
	}
	printf("\b\b \n");
}

void Dijkstra(ALGraph ag, VertexType startv)
{
	// 数组 darr 存放起点到各顶点的最短路径长度，darr[i] 表示起点到顶点 i 的最短路径长度；
	// 数组 farr 存放是否已找到起点至各顶点最短路径的标识，farr[i] = 1 表示已找到起点到顶点 i 的最短路径；
	// 二维数组 parr 存放最短路径依次经过的顶点序列，parr[i][x]（第 i 行）存放起点到顶点 i 的最短路径顶点序列；
	// 
	// 1. 初始设置 darr[i] 和 parr[i][x]：
	//		(1) 起点到其自身的最短路径长度为 0，最短路径顶点序列只包含顶点本身；
	//		(2) 若起点到顶点 i 有以 i 为弧头的弧，则 darr[i] 为权值，parr[i][0] 为弧头；
	// 2. 获取 darr 数组中所有最短路径长度的最小值，设其对应的顶点为 v，更新 farr[v] = 1；
	// 3. 对所有作为弧头与 v 邻接的顶点（设为 w），当 farr[v] != 1 且 darr[v] + <v,w> 弧的权值 < darr[w] 时：
	//		(1) 更新 darr[w] = darr[v] + <v,w> 弧的权值；
	//		(2) 更新起点至 w 的最短路径顶点序列为起点至 v 的最短路径顶点序列 + w；
	// 4. 重复 2-3 直至 farr 中的顶点标识全为 1。

	// 判断起点位置是否合法
	int svidx = LocateALVex(ag, startv);
	if (svidx < 0 || svidx >= ag.vexnum)
	{
		printf("Error: -- Dijkstra -- the index of start vertex is invalid.\n");
		return;
	}

	// 存放起点到各顶点的最短路径长度
	int darr[MAX_VERTEX_NUM] = { 0 };
	for (int i = 0; i < ag.vexnum; i++)
	{
		if (i != svidx)
		{
			darr[i] = INFINITY;
		}
	}

	// 存放顶点否已找到最短路径的标识
	int farr[MAX_VERTEX_NUM] = { 0 };

	// 存放起点至各顶点最短路径对应的顶点序列
	int parr[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			parr[i][j] = -1;
		}
	}

	// 已找到最短路径的顶点个数
	int fcount = 0;
	// 寻找起点至各顶点的最短路径
	while (fcount < ag.vexnum)
	{
		int mval = INFINITY, midx = -1;

		// 获取尚未确认最短路径且 darr 中最短路径长度值最小的顶点
		for (int i = 0; i < ag.vexnum; i++)
		{
			if (darr[i] < mval && farr[i] == 0)
			{
				mval = darr[i];
				midx = i;
			}
		}

		// 若能找到，则 midx 即为本次可以确认最短路径的顶点
		if (midx != -1)
		{
			// 更新 midx 对应的 farr 标识
			farr[midx] = 1;
			fcount++;

			// 更新作为弧头与 midx 邻接的顶点的最短路径长度及对应的顶点序列
			for (ArcNode* p_arc = ag.vertices[midx].p_arc; p_arc; p_arc = p_arc->p_next)
			{
				int weight = *(p_arc->p_info); // 弧的权值

				if (darr[midx] + weight < darr[p_arc->adjvex])
				{
					// 更弧头的最短路径长度
					darr[p_arc->adjvex] = darr[midx] + weight;

					// 更新弧头当前最短路径包含的顶点序列
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

			// 对于起点本身，上述代码不会更新其最短路径顶点序列
			// 需指定更新其最短路径序列只包含一个顶点，即其本身
			if (midx == svidx)
			{
				parr[midx][0] = midx;
			}
		}
		// 若未找到，说明存在不与起点连通的顶点，直接更新这些顶点对应的 farr 标识
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

	// 打印最短路径
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
	// 1. 设两个二维数组 D 和 P：
	//		D[i][j] 表示顶点 i 到 j 的最短路径长度；
	//		P[i][j] 表示顶点 i 到 j 的最短路径经过的第一个顶点；
	// 2. 初始设置 D 和 P 的值：
	//		D[i][j]，若存在弧 <i,j> 则设值为弧权，否则设置为 0（i == j）或无穷大（i != j）；
	//		P[i][j]，初始均设为 j；
	// 3. 设 V 是图中所有顶点集合，依次从 V 中取顶点 k，判断是否 D[i][k] + D[k][j] < D[i][j]：
	//		若是，则更新 D[i][j] = D[i][k] + D[k][j]，更新 P[i][j] = k；
	//		若否，则不做处理；
	// 4. 最终 D 即为任意两个顶点之间的最短路径矩阵，P 即为最短路径经过的第一个顶点的矩阵。

	// 存储两点间最短路径长度的二维数组
	int darr[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = { 0 };

	// 存储两点间最短路径经过的第一个顶点的二维数组
	int parr[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = { 0 };

	// 设置 darr 和 parr 初值
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

	// 依次用图中所有顶点累积更新 darr 和 parr
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

	// 打印结果
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
