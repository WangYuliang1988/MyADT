//
// tree.h
//
// 用于学习数据解构树相关知识
//
#ifndef _WYL_TREE
#define _WYL_TREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unidef.h"
#include "stack.h"

//
// 树
// 
// 定义：
//	树（Tree）是 n (n>=0) 个结点的有限集。若 n = 0，称为空树；若 n > 0，则满足以下两个条件：
//		1. 有且仅有一个称为根（Root）的结点；
//		2. 其余结点可分为 m (m>=0) 个互不相交的有限集，每个有限集本身又是一棵树，称为根的子树（SubTree）。
// 
// 术语：
//	结点的度：
//		结点拥有的子树的个数称为结点的度（degree）；
//	分支结点：
//		度大于 0 的结点；
//	叶子结点：
//		度等于 0 的结点；
//	树的度：
//		比较一棵树中所有结点的度，最大的度即为树的度；
//	结点的层次：
//		根结点所在的层为第一层，某结点在第 i 层，其子结点在第 i+1 层；
//	树的深度：
//		树中结点层次的最大值，称为树的深度（depth）；
//	有序树/无序树：
//		如果一棵树的子树位置不能交换，称这棵树为有序树；反之，称为无序树；
//	森林：
//		m (m>=0) 棵互不相交的树的集合称为森林（Forest）。
// 
// 特点：
//	树是一种非线性存储结构，通常用来存储逻辑关系为“一对多”的数据。
// 
// 存储：
//	1. 双亲表示法（顺序表）：
//		使用数组存储树结点，每个结点包含两个域：数据域和双亲域，双亲域存放其父（双亲）结点在数组中的位置；
//		特点：找双亲易，找孩子难；
//	2. 孩子表示法（顺序表 + 链表）：
//		使用数组存储树结点，每个结点包含两个域：数据域和孩子域，孩子域存放其子（孩子）结点按从左到右顺序构成的单链表的头指针；
//		特点：找孩子易，找双亲难；
//		在孩子表示法的基础上，可以为每个结点增加一个双亲域，存放其父（双亲）结点在数组中的位置；
//		特点：找孩子易，找双亲易；
//	3. 孩子兄弟表示法（二叉链表）：
//		使用二叉链表（定义见下方二叉树部分）存储树结点，左指针域指向结点的第一个（从左到右）孩子，右指针域指向结点右侧第一个兄弟；
//		特点：
//			(1) 找孩子易，找双亲易；
//			(2) 可以将普通树转化为二叉树。
// 
// 遍历：
//	1. 先（根）序遍历：先访问根结点，再从左到右依次先根遍历各棵子树；
//	2. 后（根）序遍历：先从左到右依次后根遍历各棵子树，然后访问根结点；
//	3. 按层次遍历：自上而下、自左至右访问树中每个结点。
//

/*
* 双亲表示法-树结点
*/
typedef struct
{
	ElemType e;
	int parent; // 结点的父（双亲）结点在数组中的位置
}PTNode;

/*
* 双亲表示法-树结构体
*/
typedef struct
{
	PTNode nodes[TREE_MAX_SIZE];
	int r; // 根结点在数组中的位置
	int n; // 树包含的结点个数
}PTree;

/*
* 孩子表示法-孩子链表结点
*/
typedef struct CTNode
{
	int position; // 该孩子结点在数组中的位置
	struct CTNode* next; // 指向下一个孩子结点的指针
}CTNode;

/*
* 孩子表示法-树结点
*/
typedef struct
{
	ElemType e;
	CTNode* p_child; // 孩子链表的头指针
	int parent; // 结点的父（双亲）结点在数组中的位置
}CTBox;

/*
* 孩子表示法-树结构体
*/
typedef struct
{
	CTBox nodes[TREE_MAX_SIZE];
	int r; // 根结点在数组中的位置
	int n; // 树包含的结点个数
}CTree;

/*
* 孩子兄弟表示法-树结构体
*/
typedef struct CSNode
{
	ElemType e;
	struct CSNode* p_child; // 指向结点第一个（从左到右）孩子
	struct CSNode* p_sibling; // 指向结点右侧第一个兄弟
}CSNode, *CSTree;

//
// 二叉树
// 
// 定义：
//	二叉树（Binary Tree）是 n (n>=0) 个结点的有限集。若 n = 0，称为空二叉树；若 n > 0，则满足以下两个条件：
//		1. 有且仅有一个称为根的结点；
//		2. 其余结点最多可分为 2 个互不相交的有限集，且有限集必须指定左右（即使只有一个），称为左子树或右子树，左右子树本身又是一棵二叉树。
// 
// 术语：
//	满二叉树（Full Binary Tree）：
//		一棵深度为 k 且有 [(2 的 k 次方) - 1] 个结点的二叉树称为满二叉树，结点编号规则：自上而下，自左而右；
//	完全二叉树（Complete Binary Tree）：
//		若一棵二叉树去除最后一层结点后为满二叉树，且最后一层结点依次从左到右分布，则此二叉树称为完全二叉树。
// 
// 特点：
//	1. 二叉树是有序树；
//	2. 二叉树的结点的度不大于 2，二叉树的度也不大于 2；
//	3. 满二叉树一定是完全二叉树，完全二叉树不一定是满二叉树。
// 
// 性质：
//	1. 二叉树的第 i (i>=1) 层至多有 [2 的 (i-1) 次方] 个结点；
//	2. 深度为 k (k>=1) 的二叉树至多有 [(2 的 k 次方) - 1] 个结点；
//	3. 设二叉树的叶子结点个数为 m，度为 2 的结点个数为 n，则有：m = n + 1；
//	4. 具有 n 个结点的完全二叉树的深度为 [(以 2 为底 n 的对数) 向下取整 + 1]；
//	5. 对一棵具有 n 个结点的完全二叉树，按自上而下、自左而右的顺序，对每个结点进行编号，则对于结点 i (1<=i<=n) 有：
//		(1) 若 i > 1，则其双亲结点是 [(i/2) 向下取整]；
//		(2) 若 2*i > n，则结点 i 无左孩子，否则，其左孩子是结点 [2*i]；
//		(3) 若 2*i+1 > n，则结点 i 无右孩子，否则，其右孩子是结点 [2*i+1]。
// 
// 存储：
//	1. 顺序存储：用一组地址连续的存储单元按照自上而下、自左而右的顺序依次存储树的结点；
//	2. 链式存储：用一组地址任意的存储单元存储树的结点。
// 
// 顺序存储：
//	适用于存储完全二叉树（包括满二叉树），具体实现是使用一维数组存储，将编号为 i 的结点存储在数组的 i-1 位置；
//	若要存储一般二叉树，需要先将二叉树虚拟填充为完全二叉树，虚拟添加的结点对应在数组中存一个无效值，会造成大量的空间浪费；
//	若要存储一般二叉树，最坏的情况下，即深度为 k 且只有 k 个结点的右单支树，需要使用长度为 [(2 的 k 次方)-1] 的一维数组。
// 
// 链式存储：
//	可以存储各种类型的二叉树，具体实现是使用由结点（包括一个数据域和两个分别指向左右孩子的指针域）组成的链表进行存储；
//	若链表的结点由：一个数据域和两个分别指向左右孩子的指针域组成，则称该链表为二叉链表；
//	若链表的结点由：一个数据域和三个分别指向左右孩子和双亲的指针域组成，则称该链表为三叉链表；
//	由 n 个结点组成的二叉链表共有 n + 1 个空指针域。
// 
// 遍历：
//	遍历二叉树时，若规定先左后右，则对于根结点来说，有：
//		先（根）序遍历，D-L-R
//		中（根）序遍历，L-D-R
//		后（根）序遍历，L-R-D
//	二叉树的遍历算法可以分为递归和非递归两类，非递归的实现需要显式借助栈。
// 
// 意义：
//	二叉树的存储和操作比较简单，而任何树均可与二叉树相互转换，从而解决树的存储和操作较为复杂的问题。
//

/*
* 基于顺序存储的二叉树
* 
* 用于存储完全二叉树（包括满二叉树）
*/
typedef ElemType SqBiTree[TREE_MAX_SIZE];

/*
* 基于链式存储的二叉树
* 
* 可存储各种类型的二叉树
*/
typedef struct BiTNode
{
	ElemType e;
	struct BiTNode* p_lch; // 指向左孩子的指针
	struct BiTNode* p_rch; // 指向右孩子的指针
	// struct BiTNode* p_par; // 指向双亲的指针，若结点中包含该指针，则结点组成的链表为三叉链表，否则，为二叉链表
}BiTNode, *BiTree; // 链表由头指针唯一确定，即一个 BiTNode* 类型的变量可以代表一个二叉树链表，所以将 BiTNode* 类型定义为 BiTree 类型，方便使用

/*
* 初始化
*/
void InitBiTree(BiTree* p_bt);

/*
* 构建
*/
void CreateBiTree(BiTree* p_bt, char* p_desc);

/*
* 销毁
*/
void DestroyBiTree(BiTree* p_bt);

/*
* 先序遍历-递归实现
*/
void PreOrderTraverseRecursively(BiTree bt);

/*
* 中序遍历-递归实现
*/
void InOrderTraverseRecursively(BiTree bt);

/*
* 后序遍历-递归实现
*/
void PostOrderTraverseRecursively(BiTree bt);

/*
* 先序遍历
*/
void PreOrderTraverse(BiTree bt);

/*
* 中序遍历
*/
void InOrderTraverse(BiTree bt);

/*
* 后序遍历
*/
void PostOrderTraverse(BiTree bt);

//
// 线索二叉树
// 
// 背景：
//	对于二叉树，不论采用哪种遍历（前/中/后序），都可以得到树中所有结点的一个线性序列。
//	在该序列中，除首结点外，每个结点都有且只有一个直接前驱，除尾结点外，每个结点都有且只有一个直接后继。
//	若某个算法，需要多次对二叉树进行遍历，则需要借助栈结构做重复性的操作，浪费资源且效率低下。
//	由此想到，能否在第一次遍历时，使用二叉树中空闲的内存空间记录结点的前驱和后继结点位置？
//	这样一来，后面再遍历二叉树时，就可以利用已保存的前驱后继信息，提高遍历效率。
//	若要保存结点的前驱后继，最直接的想法就是改变结点结构，添加两个指针域，分别指向结点的前驱和后继。
//	但是这样会造成空间浪费，因为对于使用二叉链表实现的二叉树来说，很多结点都含有指向 NULL 的未使用的指针域。
//	实际上，对于含有 n 个结点的二叉链表，必定存在 n+1 个空指针域。
//	我们可以利用这些空指针域，来存储部分（不是全部）结点的前驱和后继。
//	由此形成的二叉树，就是线索二叉树。
// 
// 定义：
//	线索二叉树是指利用结点的空指针域来存储结点之间前驱和后继关系的一种特殊二叉树。
// 
// 特点：
//	1. 若结点有左孩子，则 p_lch 指向左孩子，否则 p_lch 指向该结点的直接前驱；
//	2. 若结点有右孩子，则 p_rch 指向右孩子，否则 p_rch 指向该结点的直接后继；
//	3. 为避免指针域指向混淆，结点须增加两个标志域，表明当前指针域指向的是孩子还是前驱/后继。
// 
// 线索化：
//	二叉树经过某种遍历方法转化为线索二叉树的过程称为线索化，其具体实现就是在遍历过程中为标识域赋值并修改空指针的指向。
//	需要注意的是线索化时需要借助一个指向当前结点前一个结点的指针，如果是通过递归实现，该指针须定义在递归函数体外。
// 
// 线索二叉树的初始化、构建、销毁和普通二叉树基本一致。
// 
// 先序线索二叉树的遍历：
//	1. 设当前结点 = 根结点；
//	2. 访问当前结点，若当前结点为 NULL 则结束，否则寻找其后继结点：
//		(1) 若当前结点右指针域存的是后继（右标识域标识后继），则设当前结点 = 后继结点；
//		(2) 若当前结点存指针域存的右孩子（右标识域标识右孩子），则：
//			若当前结点有左孩子，则当前结点的后继就是其左孩子，设当前结点 = 左孩子；
//			若当前结点无左孩子，则当前结点的后继就是其右孩子，设当前结点 = 右孩子；
//		(3) 若当前结点右指针域存的是 NULL，说明已遍历至末尾，设当前结点 = NULL；
//	3. 重复执行 2 直至结束。
// 
// 中序线索二叉树的遍历：
//	1. 从根结点开始，重复寻找其左孩子，直至某个结点没有左孩子，设当前结点 = 该结点；
//	2. 访问当前结点，若当前结点为 NULL 则结束，否则寻找其后继结点：
//		(1) 若当前结点右指针域存的是后继（右标识域标识后继），则设当前结点 = 后继结点；
//		(2) 若当前结点右指针域存的右孩子（右标识域标识右孩子），则：
//			从右孩子开始，重复寻找其左孩子，直至某个结点没有左孩子，设当前结点 = 该结点；
//		(3) 若当前结点右指针域存的是 NULL，说明已遍历至末尾，设当前结点 = NULL；
//	3. 重复执行 2 直至结束。
// 
// 后序线索二叉树的遍历：
//	1. 从根结点开始，重复寻找其左孩子，直至某个结点没有左孩子，对于该结点：
//		若其左指针域存储的是 NULL，则设当前结点 = 该结点；
//		否则，其左指针域存储的是其前驱，设当前结点 = 前驱结点；
//	2. 访问当前结点，若当前结点为 NULL 则结束，否则寻找其后继结点：：
//		(1) 若当前结点右指针域存的是后继（右标识域标识后继），则设当前结点 = 后继结点；
//		(2) 若当前结点右指针域存的右孩子（右标识域标识右孩子），则：
//			若当前结点是父结点的右孩子，则设当前结点 = 父结点；
//			若当前结点是父结点的左孩子，则：
//				若父结点没有右孩子，则设当前结点 = 父结点；
//				若父结点有右孩子，则从右孩子开始，重复寻找其左孩子，直至某个结点没有左孩子，对于该结点：
//					若其左指针域存储的是 NULL，则设当前结点 = 该结点；
//					否则，其左指针域存储的是其前驱，设当前结点 = 前驱结点；
//		(3) 若当前结点是该线索二叉树的根结点，则设当前结点 = NULL；
//	3. 重复执行 2 直至结束。
//	注意：后序线索二叉树需要用到父结点，宜使用三叉链表作为存储结构。
// 
// 备注：
//	1. 上述线索二叉树的遍历思路，都是基于没有增设头结点的情况；
//	2. 线索二叉树结点包含前驱和后继指针，可以通过增设头结点（左指针域指向首结点（孩子），右指针域指向尾结点（线索））以支持双向遍历。
//

/*
* 用于标识指针域指向的枚举
* 
* 使用枚举不一定能节省空间，不同的 C 编译器分配给枚举的内存可能不同
*/
typedef enum PointerTag
{
	Link, // 表示指针域指向的是子树
	Thread // 表示指针域指向的是线索（即前驱或后继）
}PointerTag;

/*
* 线索二叉树
*/
typedef struct BiThrNode
{
	ElemType e;
	PointerTag ltag; // 左标识域，标识左指针指向
	PointerTag rtag; // 右标识域，标识右指针指向
	struct BiThrNode* p_lch; // 左指针域，左标识域为 Link 时指向左孩子，为 Thread 时指向前驱
	struct BiThrNode* p_rch; // 右指针域，右标识域为 Link 时指向右孩子，为 Thread 时指向后继
}BiThrNode, *BiThrTree;

//
// 哈夫曼树
// 
// 术语：
//	路径：
//		在一棵树中，一个结点到另一个结点之间的通路，称为路径；
//	路径长度：
//		在一条路径中，从起点出发，每到达一个结点，路径长度加 1，到达终点后得到的长度值，即为路径长度；
//	树的路径长度：
//		从树的根结点到树中每个结点的路径长度之和，称为树的路径长度，记作：TL；完全二叉树是路径长度最短的二叉树；
//	结点的权：
//		给结点赋一个具有某种含义的数值，则该数值称为该结点的权；
//	结点的带权路径长度：
//		树的根结点到该结点的路径长度 x 该结点的权 = 该结点的带权路径长度；
//	树的带权路径长度：
//		树中所有叶子结点的带权路径长度之和，称为树的带权路径长度，记作：WPL。
// 
// 定义：
//	使用 n 个具有权值的结点作为叶子结点构造一棵度为 d 且树中只有度为 d 和度为 0 的结点的树时，
//	若构造出的树在所有可能构造出的同度树中具有最小带权路径长度，则称该树为哈夫曼树，也称最优树。
// 
// 备注：
//	计算机学中哈夫曼树在二叉树中应用最广，所以下面所指的哈夫曼树，若无特殊说明均指二叉树形态的哈夫曼树。
// 
// 存储：
//	使用数组存储，数组元素是哈夫曼树结点，结点由：权值和双亲/左孩子/右孩子在数组中的位置构成。
// 
// 特点：
//	1. 相同的带权叶子结点构造出的哈夫曼树不唯一，即对于同样的结点，可能构造出不同形状的具有相同最小带权路径长度的二叉树；
//	2. 由哈夫曼树只有度为 2 和度为 0 的结点这一特性可知，包含 n 个叶子结点的哈夫曼树中共有 2n-1 个结点；
//	3. 权值越大的叶子结点离根越近，满二叉树不一定是哈夫曼树。
// 
// 构造方法：
//	1. 构造森林全是根：
//		将 n 个给定权值 {W[1], W[2], ..., W[n]} 的结点，构造成含有 n 棵二叉树的森林 F，
//		即 F={T[1], T[2], ..., T[n]}，其中任一棵树 T[i] 都只含有一个权为 W[i] 的根结点；
//	2. 选用两小造新树：
//		在 F 中寻找根结点权值最小的两棵树 T[x] 和 T[y]，作为左右子树构造一棵新的二叉树 T[z]，
//		并置新二叉树 T[z] 根结点的权值为其左右子树根节点的权值之和；
//	3. 删除两小添新人：
//		从 F 中删除 T[x] 和 T[y]，加入将新构造的二叉树 T[z]；
//	4. 重复 2-3 至单根：
//		重复步骤 2 和 3，直到森林中只剩下一棵二叉树为止，该二叉树即为哈夫曼树。
// 
// 哈夫曼编码
// 
// 背景：
//	计算机通信行业中，使用二进制（0, 1）编码来表示和传递信息。
// 
//	比如要传递电文 ABACCDA，假设 A, B, C, D 的编码分别为 00, 01, 10, 11，则电文编码为：
//	00010010101100，接收方按将接收到的编码序列按顺序两位一组进行译码，即可得到电文 ABACCDA。
//	该编码方式简单直接，但编码序列的长度较长，空间占用较多，不利于传输和校验。
// 
//	为了减少编码序列的总长，可以根据电文中字符出现频率的不同，让出现频率越高的字符对应的编码长度越短。
//	则对于电文 ABACCDA，假设 A, B, C, D 的编码分别为 0, 00, 1, 01，则电文编码为：000011010。
//	编码序列长度变小，但会造成译码的多义性，如前两个编码 00，可以译为 AA，也可以译为 B。
//	造成多义性的原因，在于某个字符（A）的编码（0），是别的字符（B）的编码（01）的前缀。
//	解决多义性的方法，就是要求任一字符的编码都不能是另一字符编码的前缀，称为前缀编码。
// 
//	综上，为了减少编码序列的长度，同时保证译码的唯一性，在编码时需要满足两个条件：
//		1. 出现频率越高的字符对应的编码长度越短；
//		2. 任一字符的编码都不能是另一字符编码的前缀。
// 
//	假设以电文中的字符作为叶子结点（字符出现频率作为结点权值）构建哈夫曼树，则：
//		1. 权值越大的结点（出现频率越高的字符）离根结点越近；
//		2. 根结点到任一叶子结点的路径唯一且不经过其它叶子结点。
//	然后，将哈夫曼树中结点引向其左孩子的分支标 0，引向其右孩子的分支标 1，每个
//	字符的编码即从根结点到该字符对应的叶子结点路径上得到的 0,1 序列，以此形成
//	的编码正好满足减少编码序列长度且保证译码唯一性的两个条件要求。
//	
//	译码时，对编码序列逐个取码。使用同一棵哈夫曼树，从根结点开始，若得到的码是 0，
//	则向左走，编码是 1，则向右走。一旦到达叶子结点，则译出该叶子结点对应的字符，
//	然后重新从根开始，重复上述过程，直到编码序列结束，即可获得正确的电文。
//

/*
* 哈夫曼树结构体
*/
typedef struct HTNode
{
	float weight; // 结点权值
	int parent; // 父结点在数组中的位置
	int lch; // 左孩子在数组中的位置
	int rch; // 右孩子在数组中的位置
}HTNode, *HuffmanTree;

/*
* 构建哈夫曼树
* 
* warr 是存储叶子结点权值得数组，n 为叶子结点个数
*/
void CreateHuffmanTree(HuffmanTree* p_ht, float* warr, int n);

/*
* 销毁哈夫曼树
*/
void DestroyHuffmanTree(HuffmanTree* p_ht);

/*
* HuffmanCode 即存储字符对应的由 0,1 组成的字符串的数组，如 "010"
* 
* 或者说是存储指向 char 数组指针的数组，因为 C 中字符串就是由 char 组成且以 '\0' 结尾的数组
*/
typedef char** HuffmanCode;

/*
* 哈夫曼编码
* 
* ht 是将字符作为叶子结点、字符出现频率作为权值构建的哈夫曼树
* p_hc 是指向存储字符对应的二进制编码字符串的数组的指针，*p_hc 即存储字符对应的二进制编码字符串的数组
* n 是叶子结点（即待编码的字符）个数
*/
void HuffmanCoding(HuffmanTree ht, HuffmanCode* p_hc, int n);

#endif // !_WYL_TREE
