﻿/*
* sort.h
* 
* 用于学习排序算法相关知识
*/
#ifndef _WYL_SORT
#define _WYL_SORT

#include <stdio.h>
#include <stdlib.h>
#include "unidef.h"

//
// 排序算法性能概述
// 
// --------------------------------------------------------------------------
// |  排序算法  |  最好时间  |  平均时间  |  最坏时间  |  空间复杂度  |   稳定性   |
// --------------------------------------------------------------------------
// |  插入排序  |    O(n)   |   O(n²)   |   O(n²)   |    O(1)    |    稳定    |
// --------------------------------------------------------------------------
// |  希尔排序  |  Unknown  |   O(n²)   |   O(n²)   |    O(1)    |   不稳定   |
// --------------------------------------------------------------------------
// |  冒泡排序  |    O(n)   |   O(n²)   |   O(n²)   |    O(1)    |    稳定    |
// --------------------------------------------------------------------------
// |  快速排序  |  O(nlogn) |  O(nlogn) |   O(n²)   |   O(logn)  |   不稳定   |
// --------------------------------------------------------------------------
// |  选择排序  |   O(n²)   |   O(n²)   |   O(n²)   |    O(1)    |   不稳定   |
// --------------------------------------------------------------------------
// |   堆排序   |  O(nlogn) |  O(nlogn) |  O(nlogn) |    O(1)    |   不稳定   |
// --------------------------------------------------------------------------
// |  归并排序  |  O(nlogn) |  O(nlogn) |  O(nlogn) |    O(n)    |    稳定    |
// --------------------------------------------------------------------------
// |  计数排序  |   O(n+k)  |   O(n+k)  |   O(n+k)  |   O(n+k)   |    稳定    |
// --------------------------------------------------------------------------
// |  基数排序  |   O(n*d)  |   O(n*d)  |   O(n*d)  |   O(n*d)   |    稳定    |
// --------------------------------------------------------------------------
// |   桶排序   |   O(n+m)  |   O(n+m)  |   O(n²)   |    O(m)    |    稳定    |
// --------------------------------------------------------------------------
// 
// 备注：
//	1. 算法稳定性是指，假设数据中有 A 和 B 两个具有相同值的数据，且排序前 A 位于 B 之前（或之后），
//	   若排序后 A 依然位于 B 之前（或之后），则称该排序算法是稳定的，否则，称该排序算法是不稳定的；
//  2. 计数排序时间和空间复杂度中的 k，指的是待排序数据的最大值；
//	3. 基数排序时间和空间复杂度中的 d，指的是待排序数据的最大位数；
//	4. 桶排序时间和空间复杂度中的 m，指的是桶的个数。
//

//
// 插入排序
// 
// 定义：
//	插入排序是将待排序数据逐个插入到有序序列中的合适位置，最终有序序列中存储的就是排序后的数据。
// 
//	插入排序可以细分为：直接插入排序、折半插入排序、2-路插入排序、表插入排序、希尔排序多种类型。
//

//
// 直接插入排序
// 
// 定义：
//	使用顺序查找的方式找到要插入的位置，然后将元素插入。
// 
// 描述：
//	1. 将待排序数组 A 划分为两个区域：已排序的区域，待排序的区域；
//	2. 初始时，已排序区域为 A[0]，待排序区域为 A[1] ~ A[n-1]；
//	3. 遍历待排序区域，依次取出数据进行插入，设本次遍历至位置 i 的数据，则：
//		首先，将位置 i 并入已排序区域（不需要编写额外代码，遍历待排序区域时，每次遍历就是一次并入）；
//		然后，判断：
//			(1) 若 A[i] >= A[i-1]，即待插数据 A[i] 大于已排序数据中的最大值 A[i-1]，则 A[i] 应
//			插入的位置就是其当前所在的位置，无需操作；
//			(2) 若 A[i] < A[i-1]，即待插数据的插入位置应位于 i-1 之前，则倒序遍历已排序区域，寻找
//			合适的插入位置，设当前遍历至位置 j，则：
//				若 A[i] < A[j]，则将位置 j 对应的数据后移，为之后的插入操作腾出空间；
//				若 A[i] >= A[j] 或者 j == -1，则 j + 1 就是待插入的位置，进行插入。
// 
// 性能：
//	直接插入排序的时间复杂度：最好为 O(n)，平均为 O(n²)，最坏为 O(n²)。空间复杂度为 O(1)。稳定排序。
//

/*
* 直接插入排序
* 
* arr 为待排序数组，n 为数组包含的数据个数
*/
void InsertSort(int arr[], int n);

//
// 折半插入排序
// 
// 定义：
//	使用折半查找的方式找到要插入的位置，然后将元素插入。
// 
// 描述：
//	1. 将待排序数组 A 划分为两个区域：已排序的区域，待排序的区域；
//	2. 初始时，已排序区域为 A[0]，待排序区域为 A[1] ~ A[n-1]；
//	3. 遍历待排序区域，依次取出数据进行插入，设本次遍历至位置 i 的数据，则：
//		(1) 设 low = 0, high = i - 1，通过折半查找，查找和 A[i] 值相等的数据，
//			可以证明，当折半查找结束后，low 就是待插入位置（此处省略具体证明过程）；
//		(2) 将位置 i-1 至 位置 low 的数据统一后移一位，然后在 low 位置插入 A[i]。
// 
// 性能：
//	折半插入排序相比直接插入排序，只是减少了数据的比较次数，数据的移动次数没有优化。整体来说，折半
//	插入排序的时间复杂度：最好为 O(n)，平均为 O(n²)，最坏为 O(n²)。空间复杂度为 O(1)。稳定排序。
//

/*
* 折半插入排序
*
* arr 为待排序数组，n 为数组包含的数据个数
*/
void BiInsertSort(int arr[], int n);

//
// 2-路插入排序
// 
// 定义：
//	2-路插入排序是在折半插入排序的基础上进行的改进，通过额外的 n 个辅助空间，来减少数据的移动次数，以提升效率。
// 
// 描述：
//	1. 定义一个和待排序数组 A 大小相同的数组 T 作为辅助数组，设置 first 和 final 标记 T 的最小数据和最大数据；
//	2. 初始令 T[0] = A[0]，令 first 和 final 均指向 T[0]；
//	3. 从位置 1 开始，遍历待排序数组 A，对本次遍历至的数据 A[i]，判断：
//		若 A[i] <= T[first]，则将 first 前移一位，然后将 A[i] 插入 first 位置；
//		若 A[i] >= T[final]，则将 final 后移一位，然后将 A[i] 插入 final 位置；
//		若 T[first] < A[i] < T[final]，则采用直接插入排序的思路，查找位置并移动元素，然后插入。
// 
//	注意：辅助数组 T 在使用时应视为一个首尾相接的环形数组，环形数组下标的加一和减一分别为：[(i+1+n) % n] 和 [(i-1+n) % n]。
// 
// 性能：
//	2-路插入排序能减少移动次数，不过依然未能实现数量级的提升。整体来说，2-路插入排序的时间复杂度：最好为 O(n)，平均为 O(n²)，
//	最坏为 O(n²)。空间复杂度为 O(n)。稳定排序。

/*
* 2-路插入排序
* 
* arr 为待排序数组，n 为数组包含的数据个数
*/
void TwInsertSort(int arr[], int n);

//
// 希尔排序
// 
// 背景：
//	使用直接插入排序时，若待排序数组包含的数据总量很小，或者待排序数组中只有个别数据是无序的，算法的效率会很高。
// 
// 定义：
//	希尔排序，又称“缩小增量排序”，是插入排序的一种，排序时先将整个待排序数组分割成若干子数组分别进行直接插入排序
//	（待排序数组包含的数据总量很小），然后对整个待排序作数组进行一次直接插入排序（待排序数组中只有个别数据无序）。
// 
// 描述：
//	1. 选择增量序列，如选用 { n/2, n/4, n/8,..., 1 } 作为增量序列，n 为待排序数组长度；
//	2. 遍历增量序列，设本次遍历至增量 g，则：
//		从 0 递增 1 到 g-1 进行循环，设本次循环至 i，则：
//			对由 i, i+g, i+g+g,..., m (m <= n) 位置对应的数据组成的数组进行直接插入排序。
// 
// 性能：
//	希尔排序效率的好坏和增量序列的选择有关，目前还没有理论能证明如何获取最好的增量序列，已知相对最好的增量序
//	列是 1,5,19,41,109...，序列偶数项由算式 9 * [4 的 i 次方] - 9 * [2 的 i 次方] + 1 得出，奇数项由
//	算式 [2 的 (i + 2) 次方] * ([2 的 (i + 2) 次方] - 3) + 1 得出。希尔排序的时间复杂度：最好未知，平
//	均为 O(n²)，最坏为 O(n²)。空间复杂度为 O(1)。不稳定排序。
//

/*
* 希尔排序
* 
* arr 为待排序数组，n 为数组包含的数据个数
*/
void ShellInsert(int arr[], int n);

//
// 冒泡排序
// 
// 定义：
//	通过两两比较的方式，依次将待排序数组中的最大值、次大值...移动（冒泡）至数组尾部，完成排序。
// 
// 描述：
//	设待排序数组 A 的长度为 n，则需进行 n-1 趟两两比较，第一趟比较 n-1 次，将最大值移至数组最后位置，
//	第二趟比较 n-2 次，将次大值移至数组倒数第二个位置，依此类推，当第 n-1 趟两两比较完成时，排序完成。
// 
// 性能：
//	冒泡排序的时间复杂度：最好为 O(n)，平均为 O(n²)，最坏为 O(n²)。空间复杂度为 O(1)。稳定排序。
//

/*
* 冒泡排序
* 
* arr 为待排序数组，n 为数组包含的数据个数
*/
void BubbleSort(int arr[], int n);

//
// 快速排序
// 
// 定义：
//	快速排序是对冒泡排序的一种改进，采用分治思想，通过一趟排序将待排序数组分割成两个部分，其中一个部分的数据均
//	小于另一部分的数据，然后再分别对这两个部分进行快速排序，直至每个部分不可再分，最终得到的序列就是有序序列。
// 
// 描述：
//	1. 从待排序数组 A 中选择第一个数据作为基准数（可任选，为编码方便一般选择第一个数据），设为 k；
//	2. 设 left 和 right 两个指针，初始时分别指向 A 的第一个数和最后一个数，即初始时 left 指向 k；
//	3. 启动循环，当 left < right 时：
//		(1) 在保证 right > left 的前提下，从 right 开始向左（right--）不断寻找小于 k 的数，若能找到，则交
//			换 A[right] 和 k 位置，即交换后 left 指向的数据变为 A[right]，right 指向的数据变为 k，因为交
//			换后 A[right] 已经位于合适位置，不再需要参与之后的比较，所以交换后需将 left++；
//		(2) 在保证 left < right 的前提下，从 left 开始向右（left++）不断寻找大于 k 的数，若能找到，则交换
//			A[left] 和 k 位置，即交换后 left 指向的数据变为 k，right 指向的数据变为 A[left]，因为交换后
//			A[left] 已经位于合适位置，不再需要参与之后的比较，所以交换后需将 right--；
//	3. 步骤 3 的循环结束时，k 所处的位置要么是 left，要么是 right，又因为循环体内对 left 和 right 的递增或
//	   递减进行的限制，当循环结束时必有 left == right，所以 k 所在位置 pos == left == right；
//	4. 设 A 的开始位置为 begin，若 begin < pos-1，则将 begin ~ pos-1 作为待排序数组，从步骤 1 开始执行；
//	5. 设 A 的结束位置为 end，若 end > pos+1，则将 end ~ pos+1 的数据作为待排序数组，从步骤 1 开始执行。
// 
// 性能：
//	快速排序是在冒泡排序的基础上改进而来的，冒泡排序每次只能交换相邻的两个元素，而快速排序是跳跃式的交换，总的比较
//	次数和交换次数减少，效率因此提升。快速排序的时间复杂度：最好为 O(nlogn)，平均为 O(nlogn)，最坏为 O(n²)。空
//	间复杂度为 O(logn)。不稳定排序。大多数情况下，快速排序的时间都快于平均时间复杂。一般认为，快速排序是所有排序
//	算法中平均性能最好的。
// 
// 备注：
//	C 语言自带函数库 <stdlib.h> 中的 qsort 函数就是快速排序函数。
//

/*
* 快速排序
* 
* arr 为整个待排序数组，n 为 arr 包含的数据个数
* 
* 本次待排序数组为 arr 的某个部分，begin 为该部分的开始位置，end 为该部分的结束位置
*/
void QuickSort(int arr[], int n, int begin, int end);

//
// 简单选择排序
// 
// 定义：
//	对具有 n 个数据的待排序数组进行 n-1 次遍历，第 i 次遍历时，找出 i 及其之后所有数据中的最小值，放到位置 i 上。
// 
// 描述：
//	1. 设待排序数组 A 的长度为 n，从 0~n-2 进行循环，设本次循环至 i，本次找到的最小值 min = A[i]，则：
//		从 i+1~n-2 进行嵌套循环，设嵌套循环至 j，则：若 A[j] < min，则 min = A[j]，然后 j++；否则，直接 j++；
//	2. 步骤 1 的循环结束后，即完成排序。
// 
// 性能：
//	简单选择排序同冒泡排序很相似，区别在于，简单选择排序不是两两比较出较小的数就交换，而是在每次遍历中通过两两比
//	较找出最小数后，才将最小数和本次遍历开始的数进行交换。简单选择排序的时间复杂度：最好为 O(n)，平均为 O(n²)，
//	最坏为 O(n²)。空间复杂度为 O(1)。不稳定排序。
//

/*
* 简单选择排序
* 
* arr 为待排序数组，n 为数组包含的数据个数
*/
void SelectSort(int arr[], int n);

//
// 堆排序
// 
// 定义：
//	在数据结构中，堆是一棵父结点的值总是不大于（或不小于）其子结点值的完全二叉树。
// 
//	该定义也可描述为，在含有 n 个元素的序列中，对于第 i 个元素 k[i]，若满足 k[i] <= k[2*i] 且 k[i] <= k[2*i+1]
// （或 k[i] >= k[2*i] 且 k[i] >= k[2*i+1]），则该序列可称为堆。之所以能如此描述，是因为完全二叉树中第 i 个结点
//	的左孩子正好是第 2*i 个结点，右孩子正好是第 2*i+1 个结点。需要注意的是，上面描述中涉及的 i 都是从 1 开始计数，
//	且完全二叉树中第 1 个结点是根结点，然后按从上到下、从左到右的顺序依次给结点编号。
// 
//	堆排序，就是通过将待排序数据构建为堆，取得最小值（完全二叉树的根结点），然后再将剩余数据再次构建为堆，取出次小值，
//	反复执行，即可得到一个有序序列，完成排序。
// 
// 描述：
//	1. 选择用数组来存储堆，下标 0 存储根结点，根据完全二叉树的性质，对下标为 i 的结点，其：父结点的下标为 (i-1)/2，
//	   左子结点的下标为 2*i+1，右子结点的下标为 2*i+2，并且，若数组长度为 n，则最后一个非叶结点的下标为 (n/2)-1；
//	2. 将待排序数据构建为数组存储的堆，具体过程为：设 i = (n/2)-1，将 i 及 2*i+1 和 2*i+2 三个位置的结点构建为
//	   堆（使 i 位置的结点值最大，因为 (n/2)-1 是最后一个非叶结点所在位置，所以构建时只考虑子结点即可），然后 i--，
//	   再将 i 及其子结点（若子结点有后代结点，则还需包括所有后代结点）构建为堆，重复直至 i == 0；
//	3. 取出数组首个元素（即堆的根结点），将其与数组末尾元素交换，然后将末尾元素之前的元素作为待排序数据，再次构建为以
//	   数组存储的堆（再次构建出的数组的长度长度相比之前减 1）；
//	4. 重复步骤 3 直至构建出的数组长度为 2，排序完成。
// 
// 性能：
//	堆排序的时间复杂度：最好为 O(nlogn)，平均为 O(nlogn)，最坏为 O(nlogn)。空间复杂度为 O(1)。不稳定排序。
// 
// 备注：
//	数据结构中的堆和内存管理中的堆不是一个概念，不要混淆。
//

/*
* 堆排序
* 
* arr 为待排序数组，同时也是用于存储堆的数组，n 为 arr 包含的数据个数
*/
void HeapSort(int arr[], int n);

//
// 归并排序
// 
// 定义：
//	归并排序是基于分治（Divide & Conquer）思想的一种排序算法，其主要思路是先分后治。分，是指将待排序数组不断二分为若干
//	子数组，直到每个子数组都只包含一个数据，这时，可以认为每个子数组都是包含一个数据的有序数组；治，是指将子数组不断两两
//	合并，并在合并时进行排序，每合并一次，就形成一个更长的有序子数组，直到合并至只剩一个子数组时，排序完成。
// 
// 描述：
//	1. 设 S 是长度为 n 的待排序数组，定义一个相同长度的辅助数组 T，用来存放排序后的数据；
//	2. 初始时，将 S 视为已完成分，即将 S 中每个元素都看作一个单独的数组，接下来需要开始进行治；
//	3. 设 i 是待合并的子数组可以包含的元素的最大个数，初始为 1，之所以说是子数组可以包含的元素最大个数，
//	   是因为合并一次 i 就会翻倍，而 S 不一定能正好按 i 进行均等两分，比如 S 共有 5 个数，第二次合并
//	   时，i = 2，会有一个子数组的元素个数为 1，第三次合并时，i = 4，同样会有一个子数组的元素个数为 1；
//	4. 当 i < n 时，按 i = i * 2 递进进行循环：
//		遍历数组 S，设 j 为当前遍历位置，设 k 为 T 待插入数据位置，初始时 j = k = 0，当 j < n 时：
//			(1) 设 M 和 N 是本次要进行合并的子数组，M 的理论下标范围为：j~j+i-1，N 的理论
//				下标范围为：j+i~j+i+i-1，随着 i 和 j 的增大，M 和 N 的理论下标范围可能越
//				界，加入越界因素的考虑后，M 和 N 的实际下标范围分别为 j~Min(j+i-1,n) 和
//				Min(j+i,n)~Min(j+i+i-1,n)；
//			(2) 视 S[j]~S[Min(j+i-1,n)] 为子数组 M，并设 x = j；
//				视 S[Min(j+i,n)]~S[Min(j+i+i-1,n)] 为子数组 N，并设 y = Min(j+i,n)；
//			(3) 当 x < Min(j+i-1,n) 且 y < Min(j+i+i-1,n) 时，进行循环：
//					若 M[x] < N[y]，则将 M[x] 放入 T[k]，x 和 k 均加 1；
//					若 N[y] < M[x]，则将 N[y] 放入 T[k]，y 和 k 均加 1；
//				循环结束时，若是 x（y）越界，则将 N（M）中剩余元素依次放入 T 中；
//			(4) j = j + i + i；
//		数组 S 遍历完成后，数组 T 中存储的是本次两两合并后相对有序的数据，下次遍历时，需基于 T 包含的数据进行两两
//		合并，并且同样需要一个相同长度的数组存储合并后的数据，对此，可以通过将 S 和 T 互换，巧妙满足下次遍历的要求；
//	5. 步骤 4 的循环结束后，排序完成。
// 
// 性能：
//	归并排序的时间复杂度：最好为 O(nlogn)，平均为 O(nlogn)，最坏为 O(nlogn)。空间复杂度为 O(n)。稳定排序。
//

/*
* 归并排序
* 
* arr 为待排序数组，n 为数组包含的数据个数
*/
void MergeSort(int arr[], int n);

//
// 计数排序
// 
// 背景：
//	插入排序、归并排序等排序算法，都是对数据直接进行比较和移动，得出排序结果，统称为比较排序算法。可以证明，任何
//	比较排序算法的时间复杂度在最坏情况下都不低于 O(nlogn)。若要使排序算法突破这一限制，就需要一些额外的条件和限
//	制。计数排序和基数排序、桶排序三个算法，都是在限制数据取值范围的条件下，使算法的时间复杂度可以接近 O(n)。
// 
// 定义：
//	计数排序是对已知数值范围的待排序数据，计算每个数据出现的次数，根据出现次数进行排序。
// 
// 描述：
//	1. 待排序数组 A 长度为 n，数组中每个元素 A[i] 均满足：0 <= A[i] <= k；
//	2. 定义一个长度为 k + 1 的辅助数组 C，C[m] 表示 A 中等于 m 的元素的个数；
//	3. 遍历数组 A，统计每个元素出现的次数，写入数组 C 中的对应位置，如 A 中有 6 个元素 2，则 C[2] = 6；
//	4. 遍历数组 C，将 C 中每个元素更新为该元素及其之前元素的累加和，即令 C[i] = C[0] + C[1] +...+ C[i]；
//	5. 倒序遍历 A，若 A[i] = 2，则取 C[2]，若 C[2] = 6，则说明 A 中有 6 个数小于等于 2，2 的排序位置应该
//	   是 6，同时，A 中可能包含多个元素 2，未避免将多个相同元素放置同一个排序位置，还需令 C[2] = C[2] - 1；
//	6. 步骤 5 完成后，即得出 A 中每个元素的排序位置，排序完成。
//	
//	注意：步骤 5 可以选择正序遍历 A，同样可以得到有序的结果，但会使相等元素的相对顺序发生反转，从而使算法失去
//	稳定性，而倒序遍历可以保证算法的稳定性。
// 
// 性能：
//	计数排序要求待排序的 n 个数据中，每个数据都是 0~k 之间的整数。计数排序的时间复杂度：最好为 O(n+k)，平均为
//	O(n+k)，最坏为 O(n+k) 。空间复杂度为 O(n+k)。稳定排序。当 k 远大于 n 时，计数排序将不再适用，而应该使用
//	下面介绍的基数排序，使时间复杂度仍然维持在接近 O(n) 的水平。
//

/*
* 计数排序
* 
* arr 为待排序数组
* n 为待排序数组长度
* k 为所有待排序数据中的最大值（注意：最小值默认为 0）
*/
void CountSort(int arr[], int n, int k);

//
// 基数排序
// 
// 定义：
//	基数排序是依次按照待排序数据个位、十位、百位...上的数值大小对待排序数据进行排序，最终实现对整体待排序数据的
//	排序。基数排序有两种实现方式，一种是从低位向高位进行排序，称为最低位优先法（LSD），一种是从高位向低位进行排
//	序，称为最高位优先法（MSD）。
// 
//	基数排序基于计数排序，计数排序要求 n 个待排序数据中，每个待排序数据都是 0~k 之间的整数，而基数排序因为是对
//	待排序数据某一位上的数值进行排序，而某一位上数值的取值范围，是由数据的进制决定的，比如待排序数据是十进制，则
//	某一位上的数必是 0~9 之间的整数，因此基数排序中直接参与排序的必是某个已知区间内的整数。
// 
// 描述：
//	LSD 实现：
//	1. 待排序数组 A 长度为 n，A 中每个元素都是一个十进制数；
//	2. 定义一个长度为 10 的辅助数组 C，C 中每个元素都是一个链表的首地址；
//	3. 遍历数组 A，取得 A 中所有元素的最大值，并根据最大值，求出 A 中元素的最大位数 d；
//	4. 设 i = 1，当 i <= d 时，进行循环：
//		(1) 遍历数组 A，对 A 中的每个元素，按从右到左的方向用 0 补齐最大位数 d，然后按从右到左的方向，取该元素
//			第 i 位上的值，并根据该值将元素存入数组 C 中对应元素指向的链表中，如 A 中元素是 30，位数 d = 4，则
//			该元素实际为 0030，从右往左第 1 位数是 0，则将 30 存入 C[0] 指向的链表中；
//		(2) 遍历数组 C，依次取出 C[m] 指向的链表中的每个元素，从位置 0 开始依次存入数组 A 中，并置 C[m] = NULL；
//		(3) 令 i = i + 1，继续下次循环；
//	5. 步骤 4 的循环结束后，排序完成，A 中数据即为排序后的数据。
// 
//	MSD 实现：
//	1. 待排序数组 A 长度为 n，A 中每个元素都是一个十进制数；
//	2. 定义一个长度为 10 的辅助数组 C，C 中每个元素都是一个链表的首地址；
//	3. 遍历数组 A，取得 A 中所有元素的最大值，并根据最大值，求出 A 中元素的最大位数 d；
//	4. 设 i = 1，当 i <= d 时，进行循环：
//		(1) 遍历数组 A，对 A 中的每个元素，按从右到左的方向用 0 补齐最大位数 d，然后按从左到右的方向，取该元素
//			第 i 位上的值，并根据该值将元素存入数组 C 中对应元素指向的链表中，如 A 中元素是 30，位数 d = 4，则
//			该元素实际为 0030，从左往右第 1 位数是 0，则将 30 存入 C[0] 指向的链表中；
//		(2) 遍历数组 C，依次取出每个元素指向的链表，若链表中包含的元素个数大于 1，则将该链表中的元素形成一个新的
//			数组，遍历完成后，可能会形成多个新的数组 A'、A''...；
//		(3) 令 i = i + 1，继续下次循环，下次循环时，是分别对 A'、A''... 进行操作，并有对应的 C'、C''...；
//	5. 步骤 4 的循环结束后，依次输出 ...C''、C'、C 中只有一个元素的链表中的元素，即可得到有序数据。
// 
// 性能：
//	大多数情况下，我们都是对使用十进制表示的数进行排序。不过，我们完全可以根据需要将待排序数据表示为合适的进制，再
//	根据进制确定 k 的取值，然后进行基数排序。具体来说，就是：先比较待排序数据中的最大数和待排序数据的个数 n，如果
//	相差不大，可按十进制数进行排序；如果最大数远大于 n，则使用 n 进制来表示待排序数据，此时 k = n - 1，然后进行
//	排序。设待排序数据的最大位数为 d，则基数排序的时间复杂度：最好为 O(n*d)，平均为 O(n*d)，最坏为 O(n*d)。空间
//	复杂度为 O(n*d)。稳定排序。
//

/*
* 基数排序
* 
* arr 为待排序数组
* n 为待排序数组长度
*/
void RadixSort(int arr[], int n);

//
// 桶排序
// 
// 定义：
//	桶排序基于计数排序，对 n 个取值范围均为 0~k 的数据进行桶排序时，先根据 k 划分出大小相同且有序的若干部分，称为桶，
//	如 k = 100 时，可以分为 0~39，40~79，80~119 共 3 个桶，然后把 n 个数据放入对应的桶中，再分别对每个桶数据进行
//	排序，最后按序输出桶及桶中的数据，即可得到有序数据。桶的划分没有固定规则，应尽量使待排序数据均匀地分配在各个桶中。
// 
// 描述：
//	1. 待排序数组 A 长度为 n，数组中每个元素 A[i] 均满足：0 <= A[i] <= k；
//	2. 根据 k 划分出若干相同且有序的部分（桶），设 T 为存放桶的二维数组，T[0] 表示第一个桶中存放的数据组成的数组；
//	3. 遍历数组 A，将 A 中元素放入 T 对应的桶中；
//	4. 遍历数组 T，对每个桶中的数据进行排序（排序算法自选，比如选用直接插入排序），并依次存入数组 A 中。
// 
// 性能：
//	设桶的个数为 m，则桶排序的时间复杂度：最好为 O(n+m)，平均为 O(n+m)，最坏为 O(n²)。空间复杂度为 O(m)。稳定排序。
//

/*
* 桶排序
* 
* arr 为待排序数组
* n 为待排序数组长度
* k 为所有待排序数据中的最大值（注意：最小值默认为 0）
*/
void BucketSort(int arr[], int n, int k);

#endif // !_WYL_SORT
