﻿//
// grapgh.h
// 
// 用于学习图数据结构相关知识
//
#ifndef _WYL_GRAPH
#define _WYL_GRAPH

//
// 图
// 
// 术语：
//	顶点：
//		图中的数据元素；
//	弧：
//		若顶点 v 和顶点 w 直接相连且连线有方向，则称该连线为弧，若方向是从 v 到 w，则称 v 为弧尾，w 为弧头，表示为 <v, w>；
//	有向图：
//		由顶点和弧组成的图称为有向图；
//	有向完全图：
//		有向图中弧的取值范围是 0~n*(n-1)，拥有 n*(n-1) 条边的有向图称为完全有向图（即每两个顶点之间都存在方向相反的两条弧）；
//	边：
//		若顶点 v 和顶点 w 直接相连且连线无方向，则称该连线为边，表示为 (v, w) 或 (w, v)；
//	无向图：
//		由顶点和边组成的图称为无向图；
//	完全图：
//		无向图中边的取值范围是 0~n*(n-1)/2，拥有 n*(n-1)/2 条边的无向图称为完全图（即每两个顶点之间都存在边）；
//	稀疏图：
//		含有很少条边或弧的图；
//	稠密图：
//		含有很多条边或弧（接近完全）的图；
//	权：
//		和图的边或弧相关的数，比如一个顶点到另一个顶点的距离，称为边或弧权；
//	网：
//		带权的图称为网；
//	子图：
//		若图 A 顶点的集合是图 B 顶点的集合的子集，且图 A 边或弧的集合是图 B 边或弧的集合的子集，则称图 A 是图 B 的子图；
//		注意：空集是任何集合的子集；
//	邻接点：
//		若有边 (v, w)，则称顶点 v 和 w 互为邻接点（或相邻接），称边 (v, w) 依附于 v 和 w（或与 v 和 w 相关联）；
//		若有弧 <v, w>，则称顶点 v 邻接到 w，顶点 w 邻接自 v，称弧 <v, w> 与顶点 v 和 w 相关联；
//	度/入度/出度：
//		无向图中顶点 v 的度是和 v 相关联的边的数目，记作：TD(v)；
//		有向图中以顶点 v 为头的弧的数目称为 v 的入度，记为：ID(v)；
//		有向图中以顶点 v 为尾的弧的数目称为 v 的出度，记为：OD(v)；
//		有向图中的顶点 v 的度是该顶点入度和出度之和，即：TD(v) = ID(v) + OD(v)；
//		规律：图（不论有向无向）中边或弧的数目 = 图中所有顶点度的和 / 2；
//	路径：
//		若顶点 A 可以同过若干个其它顶点到达顶点 B，则称 A 到 B 之前存在路径；
//	路径长度：
//		路径中包含的边或弧的总数；
//	回路（环）：
//		从顶点 A 出发，最后又回到顶点 A 的路径称为回路，也称环；
//	简单路径：
//		除两个端点外，路径中不存在重复顶点的路径称为简单路径；
//	简单回路（简单环）：
//		即两个端点相同的简单路径；
//	连通：
//		从顶点 A 到顶点 B 之间有路径，则称 A 和 B 是连通的；
//	连通图：
//		无向图中，若任意两个顶点都是连通的，称该无向图为连通图；
//	非连通图：
//		无向图中，若至少有两个结点，其之间是不连通的，称该无向图为非连通图；
//		规律：n 个顶点的非连通图其边或弧小于 n-1；
//	连通分量：
//		非连通图中，若存在某个子图是连通图，且该子图不被任何其它连通的子图所包含，则称该子图为极大连通子图，也称连通分量；
//	强连通图：
//		有向图中，若任意两个顶点都是连通的，称该有向图为强连通图；
//	非强连通图：
//		有向图中，若至少有两个结点，其之间是不连通的，称该有向图为非强连通图；
//	强连通分量：
//		非强连通图中，若存在某个子图是强连通图，且该子图不被任何其它强连通的子图所包含，则称该子图为极大强连通子图，也称强连通分量；
//	生成树：
//		对于连通图，可以构造若干所有顶点均由边连接在一起且不存在回路的树，称为生成树；
//		规律：
//			(1) n 个顶点的连通图的生成树有 n-1 条边；
//			(2) 生成树中任意两个顶点间的路径是唯一的；
//			(3) 生成树中再加一条边必然形成回路；
//	生成森林：
//		对于非连通图，每个连通分量都可以构造若干生成树，合起来就是生成森林。
// 
// 定义：
//	图是一种数据元素之间存在多对多关系的非线性数据结构，由顶点集合及顶点间的关系（边或弧）集合组成。
//	
// 特点：
//	1. 图是一种非线性结构，用来表示逻辑关系为”多对多“的数据；
//	2. 图中顶点的前驱和后继个数无限制，任意两个顶点之前都可能相关。
// 
// 存储：
//	1. 顺序存储：邻接矩阵；
//	2. 链式存储：邻接表、十字链表（有向图）、邻接多重表（无向图）。
// 
// 注意：
//	1. 邻接表中，一个链表结点只包含一个顶点信息。链表结点必须和链表“依附”的
//	   顶点结点一起，才能构成一条边或弧。一个链表结点只能属于一个链表。
//	2. 十字链表和邻接多重表中，一个链表结点就包含了边或弧的两端顶点信息。
//	   一个链表结点本身就是一条边或弧。一个链表结点可以属于多个链表。
// 
// 邻接矩阵：
//	通过两个数组存储图的信息，一个一维数组存储图的顶点，一个二维数组（邻接矩阵）存储图的边或弧。
//	当两个顶点之间有边或弧时，其对应邻接矩阵中元素的值为 1（网为权值），否则为 0（网为无穷大）。
//	特点：无向图的邻接矩阵是对称矩阵。
// 
// 邻接表：
//	将图的所有顶点存储到数组中，同时为每个顶点配备一个单链表，用来记录和当前顶点相关的所有边或弧。
//	数组存储的顶点结点，包含 2 个域：
//		data 数据域存储顶点信息；
//		arc 指针域指向记录该顶点相关的所有边或弧的链表的第一个结点。
//	单链表存储的边或弧结点，包含 3 个域：
//		adjvex 数据域存储本条边或弧除链表对应顶点外另一顶点在数组中的位置；
//		next 指针域指向链表下一个结点（即链表对应顶点的下一条边或弧）；
//		info 指针域指向有关边或弧的信息（如权值）。
//	特点：
//		1. 对于 n 个顶点 e 条边的无向图，需要 n 个顶点结点和 2e 个边或弧结点；
//		2. 对有向图，顶点搭配链表时，顶点是弧尾，链表中存储弧头位置；
//		2. 无向图中顶点 v 的度为该顶点对应单链表中的结点个数。
// 
// 十字链表（有向图）：
//	将有向图的所有顶点存储到数组中，同时为每个顶点各配备两个链表，分别记录以当前顶点为弧头或弧尾的所有弧。
//	数组存储的顶点结点，包含 3 个域：
//		data 数据域存储顶点信息；
//		in 指针域指向记录以该顶点为弧头的所有弧的链表的第一个结点；
//		out 指针域指向记录以该顶点为弧尾的所有弧的链表的第一个结点。
//	链表存储的弧结点，包含 5 个域：
//		headvex 数据域存储本条弧中弧头顶点在数组中的位置；
//		tailvex 数据域存储本条弧中弧尾顶点在数组中的位置；
//		hlink 指针域指向下一个具有相同 headvex 的弧结点；
//		tlink 指针域指向下一个具有相同 tailvex 的弧结点；
//		info 指针域指向有关弧的信息（如权值）。
//	特点：
//		1. 十字链表只能用于存储有向图；
//		2. 十字链表可以方便地计算出每个顶点的入度和出度（作为对比，邻接表只能快速计算出出度）。
// 
// 邻接多重表（无向图）
//	将无向图的所有顶点存储到数组中，同时为每个顶点配备一个链表，记录和该顶点相关的所有边。
//	数组存储的顶点结点，包含 2 个域：
//		data 数据域存储顶点信息；
//		edge 指针域指向记录该顶点相关的所有边的链表的第一个结点。
//	链表存储的边结点，包含 6 个域：
//		ivex, jvex 数据域存储本条边的两个顶点在数组中的位置；
//		ilink 指针域指向下一个具有相同 ivex 的边结点；
//		jlink 指针域指向下一个具有相同 jvex 的边结点；
//		mark 标识该边是否被访问过，主要用于边的遍历；
//		info 指针域指向有关边的信息（如权值）。
//	特点：
//		1. 邻接多重表只能用于存储无向图；
//		2. 邻接多重表对无向图中边的插入和删除只需操作一次（作为对比，邻接表增/删一条边需要重复操作两次）。
// 
// 深度优先搜索（DFS，Depth First Search）：
//	1. 从图中任选一个顶点，设为当前顶点 cv；
//	2. 访问 cv，寻找和 cv 相邻且未被访问过的顶点，设为 cn：
//		若能找到，则设 cv = cn；
//		若未找到，则设 cv = 上一个被访问的顶点（若不存在，则为 NULL）；
//	3. 重复执行 2，直至 cv == NULL;
//	4. 遍历图中所有顶点，寻找未被访问过的顶点：
//		若有，则设该顶点为 cv，执行 2-3；
//		若无，则所有顶点均已访问，搜索结束。
// 
// 广度优先搜索（BFS，Breadth First Search）：
//	1. 从图中任选一顶点，访问，并设为当前顶点 cv；
//	2. 寻找和 cv 相邻且未被访问的顶点 cn：
//		若能找到，则访问，并继续寻找和访问该 cv 的下一个 cn，直至无法找到，然后设 cv = 该 cv 第一个被访问的 cn；
//		若未找到，则设 cv = 该 cv 第一个被访问的 cn（若不存在，则为 NULL）；
//	3. 重复执行 2，直至 cv == NULL;
//	4. 遍历图中所有顶点，寻找未被访问过的顶点：
//		若有，则设该顶点为 cv，执行 2-3；
//		若无，则所有顶点均已访问，搜索结束。
// 
// 最小生成树：
//	定义：
//		对于连通网，在该网的所有生成树中，各边权值之和最小的生成树，称为该连通网的最小生成树，也称最小代价生成树。
//	应用：
//		比如要在多个城市间铺设通信网，每两个城市间铺设网络的成本相同，此时就可以利用最小生成树，确保网络连通且代价最小。
//	性质：
//		MST 性质：设 N = (V, E) 是连通网，U 是顶点集合 V 的非空子集。若边 (u, v) 是条具
//		有最小权值的边，其中 u 属于 U，v 属于 V-U，则必存在一棵包含边 (u, v) 的最小生成树。
//	构建：
//		普里姆（Prim）算法：
//			(1). 设 N = (V, E) 是连通网，U 和 TE 是 N 的最小生成树的顶点集和边集；
//			(2). 初始令 U = { u }，u 是从 V 中任选的一个顶点，令 TE = {}；
//			(3). 从 V-U 中选一个顶点，该顶点和 U 中某个顶点构成的边，在所有 V-U 中顶点
//				 和 U 中顶点能构成的边中具有最小权值，将该顶点加入 U，将对应的边加入 TE；
//			(4). 重复 (3) 直至 U = V，则 T = (V, TE) 就是 N 的最小生成树。
//		注：普里姆算法的运行效率与连通网包含的顶点数有关，和网包含的边数无关，适合边稠密的网。
// 
//		克鲁斯卡尔（Kruskal）算法：
//			(1). 设 N = (V, E) 是连通网，TE 是 N 的最小生成树的边集；
//			(2). 初始令 T = (V, TE)，TE = {}；
//			(3). 从 E 中选择权值最小的边，若该边不会与 TE 中已有的边形成回路，则加入 TE 中；
//			(4). 重复 (3) 直至 TE 中边的条数 = 顶点个数 -1，此时的 T 就是 N 的最小生成树。
//		注：克鲁斯卡尔算法的运行效率与连通网包含的边数有关，和网包含的顶点数无关，适合边稀疏的网。
// 
// 拓扑（Topology）排序：
//	定义：
//		拓扑排序是将有向无环图（又称 DAG 图, Directed Acycline Graph）中的顶点按照弧尾在先、弧头在后的顺序进行排序。
//	思路：
//		1. 寻找一个没有前驱的顶点 V；
//		2. 删除 V 及以 V 为弧尾的弧；
//		3. 重复 1-2 直至不存在没有前驱的顶点。
//	应用：
//		对 AOV 网进行拓扑排序，获得完成多个活动时需要遵循的先后顺序，或称拓扑有序序列。
//		AOV（Activity On Vertex）网：有向无环图中，用顶点表示活动，用有向边表示活动之间的先后顺序。
// 
// 关键路径：
//	术语：
//		AOE（Activity On Edge）网：
//			有向无环网中：弧表示活动；弧权表示活动完成所需时间；顶点表示一个触发
//			点，当其被触发时表明其作为弧头的活动已完成，其作为弧尾的活动可以开始；
//			AOE 网中：有且只有一个入度为 0 的顶点，有且只有一个出度为 0 的顶点；
//		Ve(j)：
//			对 AOE 中的某个顶点 j 来说，从源点（即起始点，入度为 0）到该顶点的最
//			长（即权值之和最大）路径表示为 Ve(j)，代表该顶点的最早触发时间；
//		Vl(j)：
//			对 AOE 中的某个顶点 j 来说，在确保汇点（即结束点，出度为 0）的最早触
//			发时间不变的情况下，顶点 j 被允许的最晚触发时间，表示为 Vl(j)，其值等
//			于 [汇点的最早触发时间 - 汇点倒溯至该顶点的最长路径权值之和]；
//		e(i)：
//			对 AOE 中的某条弧 i 来说，将其最早开始时间表示为 e(i)，等于该弧弧尾
//			顶点的最早触发时间，即：若该弧的弧尾是顶点 j，则 e(i) = Ve(j)；
//		l(i)：
//			对 AOE 中的某条弧 i 来说，将其最晚开始时间表示为 l(i)，等于 [该弧弧头
//			的最晚触发时间 - 该弧权值]，设弧头是 j，则 l(i) = [Vl(j) - 该弧权值]。
//	定义：
//		关键路径是 AOE 网从源点到汇点的所有路径中最长（权值最大）的路径，可能有多条。
//		或者描述为，若某条边的最早开始时间等于最晚开始时间，即 e(i) == l(i)，则称
//		这条边代表的活动为关键活动，由关键活动组成的从源点到汇点的路径称为关键路径。
//	思路：
//		1. 求 AOE 中各顶点的 Ve(j) 和 Vl(j)（需依赖拓扑排序）；
//		2. 根据顶点的 Ve(j) 和 Vl(j)，求出各弧的 e(i) 和 l(i)；
//		3. 根据顶点的拓扑序列，依次输出从源点到汇点的关键活动，即可得到关键路径。
// 
// 最短路径：
//	定义：
//		在网中，一个顶点到另一个顶点可能有多条路径，其中权值之和最小的路径称为最短路径。
//	分类：
//		迪杰斯特拉（Dijkstra）算法：从某个顶点到其余各顶点之间的最短路径；
//		弗洛伊德（Floyd）算法：任意两个顶点之间的最短路径。
//	迪杰斯特拉算法：
//		用于求解从某个顶点（称为起点）到其余各个顶点之间的最短路径。
//		算法思想为：
//			1. 把顶点集合 V 分成两组：
//				(1) S 存放已求出最短路径的顶点（包含起点至该顶点的最短路径长度）集合，初始为起点；
//				(2) T = V-S 存放尚未确定最短路径的顶点（包含起点经 S 中顶点至该顶点的临时最短路径长度，之所以
//					称为“临时”，是因为随着S 中顶点的增加，可能会有新的更短路径）集合，初始为除起点外的其它顶点；
//			2. 重复将当前 T 中路径长度最短的顶点移入 S 中，同时更新 T 中各顶点的临时最短路径长度，直至 S == V。
//		数学依据是：
//			从起点至 T 中某顶点的最短路径，要么是起点至该顶点的直接路径，要么是起点经 S 中顶点至该顶点的路径（反证）。
//	弗洛伊德算法：
//		用于求解任意两个顶点之间的最短路径。
//		算法思想为：
//			1. 设两个二维数组 D 和 P：
//				D[i][j] 表示顶点 i 到 j 的最短路径长度；
//				P[i][j] 表示顶点 i 到 j 的最短路径经过的第一个顶点；
//			2. 初始设置 D 和 P 的值：
//				D[i][j]，若存在弧 <i,j> 则设值为弧权，否则设置为 0（i == j）或无穷大（i != j）；
//				P[i][j]，初始均设为 j；
//			3. 设 V 是图中所有顶点集合，依次从 V 中取顶点 k，判断是否 D[i][k] + D[k][j] < D[i][j]：
//				若是，则更新 D[i][j] = D[i][k] + D[k][j]，更新 P[i][j] = k；
//				若否，则不做处理；
//			4. 最终 D 即为任意两个顶点之间的最短路径矩阵，P 即为最短路径经过的第一个顶点的矩阵。
//

#include <stdio.h>
#include <stdlib.h>
#include "unidef.h"
#include "stack.h"
#include "queue.h"

#define MAX_VERTEX_NUM 20	// 图可包含的最大顶点数
#define VertexType int		// 图中顶点的数据类型
#define VRType int			// 表示图中顶点之间关系（边或弧）的数据类型
#define InfoType int		// 表示边或弧包含的额外信息的数据类型

typedef enum { 
	DG, // 有向图
	DN, // 有向网
	UDG, // 无向图
	UDN // 无向网
}GraphKind; // 图类型枚举

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 图的顺序存储
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
* 边或弧结构体
*/
typedef struct
{
	VRType adj; // 边或弧，1 表示有（网为权值），0 表示无（网为无穷大）
	InfoType* p_info; // 指向边或弧包含的额外信息
}ArcCell;

/*
* 图结构体
* 
* 基于数组存储，支持有向图和无向图
*/
typedef struct
{
	GraphKind kind; // 图的种类
	int vexnum; // 顶点个数
	int arcnum; // 边或弧条数
	VertexType vexs[MAX_VERTEX_NUM]; // 存储顶点的一维数组
	ArcCell arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 存放边或弧的二维数组
}MGraph;

/*
* 获取基于顺序存储的图中顶点 v 在顶点数组中的位置
*/
int LocateMVex(MGraph mg, VertexType v);

/*
* 基于顺序存储构建图
* 
* vexs，图的顶点集合
* vexnum，图的顶点个数
* adjs，使用约定格式描述图的边或弧集合的字符串：
*	(x,y,z) 表示构建无向图（网），x、y 为顶点，z 为权值（可选）；
*	<x,y,z> 表示构建有向图（网），x 为弧尾，y 为弧头，z 为权值（可选）。
*/
void CreateMGraph(MGraph* p_g, VertexType vexs[], int vexnum, char* adjs);

/*
* 深度优先搜索图
*/
void DFSTraverse(MGraph mg);

/*
* 广度优先搜索图
*/
void BFSTraverse(MGraph mg);

/*
* 普里姆（Prim）算法构建最小生成树
*/
void MiniSpanTreePrim(MGraph mg);

/*
* 克鲁斯卡尔（Kruskal）算法构建最小生成树
*/
void MiniSpanTreeKruskal(MGraph mg);

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 图的邻接表存储
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
* 边或弧结构体
*/
typedef struct ArcNode
{
	int adjvex; // 本条边或弧除链表对应顶点（弧尾）外另一顶点（弧头）在数组中的位置
	struct ArcNode* p_next; // 指向链表下一个结点（即链表对应顶点的下一条边或弧）
	InfoType* p_info; // 指向边或弧包含的额外信息（如权值）
}ArcNode;

/*
* 顶点结构体
*/
typedef struct
{
	VertexType data; // 存储顶点信息，对有向图，在搭配链表时该顶点作为弧尾
	ArcNode* p_arc; // 指向记录该顶点相关的所有边或弧的链表的第一个结点
}VexNode;

/*
* 图结构体
* 
* 基于邻接表（数组+单链表），支持有向图和无向图
*/
typedef struct
{
	GraphKind kind; // 图类型
	int vexnum; // 顶点个数
	int arcnum; // 边或弧条数
	VexNode vertices[MAX_VERTEX_NUM]; // 存储顶点的数组
}ALGraph;

/*
* 获取基于邻接表的图中顶点 v 在顶点数组中的位置
*/
int LocateALVex(ALGraph ag, VertexType v);

/*
* 基于邻接表构建图
*
* vexs，图的顶点集合
* vexnum，图的顶点个数
* arcs，使用约定格式描述图的边或弧集合的字符串：
*	(x,y,z) 表示构建无向图（网），x、y 为顶点，z 为权值（可选）；
*	<x,y,z> 表示构建有向图（网），x 为弧尾，y 为弧头，z 为权值（可选）。
*/
void CreateALGraph(ALGraph* p_a, VertexType vexs[], int vexnum, char* arcs);

/*
* 拓扑排序
* 
* tparr 为存储顶点拓扑序列的数组，其实际存储的是顶点在图的顶点数组中的位置，用于代替顶点本身
*/
void TopologicalSort(ALGraph ag, int tparr[]);

/*
* 寻找关键路径
*/
void CriticalPath(ALGraph ag);

/*
* 寻找某点至其它各点的最短距离
* 
* 迪杰斯特拉（Dijkstra）算法
*/
void Dijkstra(ALGraph ag, VertexType startv);

/*
* 寻找任意两点之间的最短路径
* 
* 弗洛伊德（Floyd）算法
*/
void Floyd(ALGraph ag);

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 有向图的十字链表存储
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
* 弧结构体
*/
typedef struct ArcBox
{
	int headvex; // 弧头顶点在数组中的位置
	int tailvex; // 弧尾顶点在数组中的位置
	struct ArcBox* p_hlink; // 指向下一个具有相同 headvex 的弧结点
	struct ArcBox* p_tlink; // 指向下一个具有相同 tailvex 的弧结点
	InfoType* p_info; // 指向有关弧的信息（如权值）
}ArcBox;

/*
* 顶点结构体
*/
typedef struct
{
	VertexType data; // 顶点信息
	ArcBox* p_in; // 指向记录以该顶点为弧头的所有弧的链表的第一个结点
	ArcBox* p_out; // 指向记录以该顶点为弧尾的所有弧的链表的第一个结点
}VexBox;

/*
* 图结构体
*/
typedef struct
{
	int vexnum; // 顶点数
	int arcnum; // 弧条数
	VexBox xlist[MAX_VERTEX_NUM]; // 存储顶点的数组
}OLGraph;

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 无向图的邻接多重表存储
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/*
* 边访问标识枚举
*/
typedef enum { Unvisited, Visited }VisitMark;

/*
* 边结构体
*/
typedef struct EdgeNode
{
	int ivex, jvex; // 边的两个顶点在数组中的位置
	struct EdgeNode* p_ilink; // 指向下一个具有相同 ivex 的边结点
	struct EdgeNode* p_jlink; // 指向下一个具有相同 jvex 的边结点
	VisitMark mark; // 标识该边是否被访问过，主要用于边的遍历
	InfoType* p_info; // 指向有关边的信息（如权值）
}EdgeNode;

/*
* 顶点结构体
*/
typedef struct
{
	VertexType data; // 顶点信息
	EdgeNode* p_edge; // 指向记录该顶点相关的所有边的链表的第一个结点
}VxNode;

/*
* 图结构体
*/
typedef struct
{
	int vexnum; // 顶点数
	int arcnum; // 边条数
	VxNode mulist[MAX_VERTEX_NUM]; // 存储顶点的数组
}AMLGraph;

#endif // !_WYL_GRAPH
