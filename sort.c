#include "sort.h"

void Print(char* desc, int arr[], int n)
{
	printf("%s", desc);
	for (int i = 0; i < n; i++)
	{
		printf("%d,", arr[i]);
	}
	printf("\b \n");
}

void InsertSort(int arr[], int n)
{
	// 将 arr 划分为两个区域，一个是已排序的区域，一个是待排序的区域
	// 初始时，已排序区域为 arr[0]，待排序区域为 arr[1] ~ arr[n-1]
	// 遍历待排序区域，将数据所在位置并入已排序区域，将数据插入已排序区域的合适位置

	for (int i = 1; i < n; i++)
	{
		// i 之前是已排序的数据，且 i-1 位置的数据是已排序数据中的最大数据（排序为升序）
		// 因此，若 arr[i] > arr[i-1]，则 arr[i] 的插入位置就是其当前位置，无需处理
		// 否则，需要在已排序区域寻找合适的插入位置，并在寻找过程中移动数据以腾出空间

		if (arr[i] < arr[i-1])
		{
			int tmp = arr[i];

			// 使用顺序查找的方式查找待插入位置，即让待插数据 arr[i] 从已排序区域的末尾数据开始倒序逐
			// 个比较，直到 arr[i] 大于等于某个位置的数据或位置等于 -1，则该位置 + 1 就是待插入位置
			int k = i - 1;
			while (tmp < arr[k] && k > -1)
			{
				arr[k + 1] = arr[k]; // 寻找位置的过程中移动数据，给待插入数据腾出空间
				k--;
			}
			arr[k + 1] = tmp;
		}

		// 每循环一次，已排序区域都会增加一个数据
	}

	// 打印排序结果
	Print("InsertSort: ", arr, n);
}

void BiInsertSort(int arr[], int n)
{
	// 折半插入的整体思路和直接插入相同
	// 不同之处在于使用折半查找确认位置
	// 并且是先找到位置，然后再移动数据

	for (int i = 1; i < n; i++)
	{
		int tmp = arr[i];

		// 通过折半查找，查找和 arr[i] 相等的数据
		// 可以证明，查找结束后，low 即为待插入位置
		int low = 0, high = i - 1;
		while (low <= high)
		{
			int mid = (low + high) / 2;
			if (tmp < arr[mid])
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}

		// 将 i - 1 至 low 的数据统一后移，腾出空间，然后插入
		for (int j = i - 1; j >= low; j--)
		{
			arr[j + 1] = arr[j];
		}
		arr[low] = tmp;

		// 每循环一次，已排序区域都会增加一个数据
	}

	// 打印排序结果
	Print("BiInsertSort: ", arr, n);
}

void TwInsertSort(int arr[], int n)
{
	// 定义辅助数组，该数组在使用时应视为首尾相接的环形数组
	// 环形数组下标的加一减一分别为 (i+1+n) % n 和 (i-1+n) % n
	int* tarr = (int*)malloc(sizeof(int) * n);
	if (!tarr)
	{
		printf("Error: -- TwInsertSort -- fail to alloc memory.\n");
		return;
	}

	// 初始将待排序数组的第一个数据放入辅助数组 0 位置
	tarr[0] = arr[0];

	// 设置 first 和 final 分别指向辅助数组中的最小和最大数据
	int first = 0, final = 0;

	// 遍历待排序数组，依次取出数据放入辅助数组的合适位置
	for (int i = 1; i < n; i++)
	{
		if (arr[i] <= tarr[first])
		{
			first = (first - 1 + n) % n;
			tarr[first] = arr[i];
		}
		else if (arr[i] >= tarr[final])
		{
			final = (final + 1 + n) % n;
			tarr[final] = arr[i];
		}
		else
		{
			int k = (final + 1 + n) % n;

			while (arr[i] < tarr[(k - 1 + n) % n])
			{
				tarr[k] = tarr[(k - 1 + n) % n];
				k = (k - 1 + n) % n;
			}

			tarr[k] = arr[i];
			final = (final + 1 + n) % n; // 插入数据前，最大数据也后移了一位
		}
	}

	// 按 first - final 的顺序将 tarr 中的数据拷贝至 arr 中
	for (int i = 0; i < n; i++)
	{
		arr[i] = tarr[(first + i) % n];
	}

	// 释放辅助数组占用空间
	free(tarr);

	// 打印排序结果
	Print("TwInsertSort: ", arr, n);
}

void ShellInsert(int arr[], int n)
{
	// 选择不断对 n 进行二分直至 1 作为增量序列
	for (int i = n / 2; i > 0; i = i / 2)
	{
		// 使用增量将待排序数组分为若干子数组，对每个子数组进行直接插入排序
		// 直至增量变为 1 时，相当于对整个待排序数组最终进行一次直接插入排序

		// 增量为 i 时，相当于划分出 i - 1 个子数组
		for (int j = 0; j < i; j++)
		{
			// 对每个子数组进行直接插入排序，注意子数组中相邻数据的下标间隔是 i
			for (int k = j + i; k < n; k = k + i)
			{
				if (arr[k] < arr[k - i])
				{
					int tmp = arr[k];

					while (tmp < arr[k - i] && k > j)
					{
						arr[k] = arr[k - i];
						k -= i;
					}

					arr[k] = tmp;
				}
			}
		}
	}

	Print("ShellInsert: ", arr, n);
}

void BubbleSort(int arr[], int n)
{
	// 对 n 个数据进行 n-1 趟两两比较
	for (int i = 1; i < n; i++)
	{
		// 第 i 趟比较（i 从 1 开始计数）需要进行的比较次数是 n-i
		for (int j = 0; j < n - i; j++)
		{
			// 若当前元素小于等于其后元素，无需操作
			// 否则，当前元素和其后元素进行位置交换
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}

	Print("BubbleSort: ", arr, n);
}

void QuickSort(int arr[], int n, int begin, int end)
{
	if (begin < end)
	{
		int k = arr[begin]; // 选取待排序数组第一个数为基准数 k

		int left = begin; // left 用于从左到右寻找大于 k 的数，初始时指向数组第一个数，也即指向 k
		int right = end; // right 用于从右到左寻找小于 k 的数，初始时指向数组最后一个数

		while (left < right)
		{
			// 先从 right 开始，往左寻找第一个小于 k 的数据
			while (left < right && arr[right] >= k)
			{
				right--;
			}
			// 若能找到，则交换 arr[right] 和 k 的位置，交换后，left 指向的数据
			// 变为 arr[right]，right 指向的数据变为 k，因为 arr[right] 已处于
			// 合适位置，无需再参与之后的比较，所以需将 left++
			if (left < right)
			{
				arr[left] = arr[right];
				arr[right] = k;
				left++;
			}

			// 再从 left 开始，往右寻找第一个大于 k 的数据
			while (left < right && arr[left] <= k)
			{
				left++;
			}
			// 若能找到，则交换 arr[left] 和 k 的位置，交换后，left 指向的数据
			// 变为 k，right 指向的数据变为 arr[left]，因为 arr[left] 已处于
			// 合适位置，无需再参与之后的比较，所以需将 right--
			if (left < right)
			{
				arr[right] = arr[left];
				arr[left] = k;
				right--;
			}
		}

		// 循环结束后，k 所在的位置 pos == left == right，以 pos 为分割
		// 点，分别对 beign ~ pos - 1 和 pos + 1 ~ end 递归进行快速排序
		QuickSort(arr, n, begin, left - 1);
		QuickSort(arr, n, left + 1, end);

		// 打印排序结果
		if (end - begin + 1 == n)
		{
			Print("QuickSort: ", arr, n);
		}
	}
}

void SelectSort(int arr[], int n)
{
	int min, pos;

	for (int i = 0; i < n - 1; i++)
	{
		min = arr[i];
		pos = i;

		for (int j = i + 1; j < n; j++)
		{
			if (arr[j] < min)
			{
				min = arr[j];
				pos = j;
			}
		}

		arr[pos] = arr[i];
		arr[i] = min;
	}

	Print("SelectSort: ", arr, n);
}

/*
* 交换两个整型变量的值
* 
* HeapSort 的辅助函数
*/
void Swap(int* ptr_m, int* ptr_n)
{
	int tmp = *ptr_m;
	*ptr_m = *ptr_n;
	*ptr_n = tmp;
}

/*
* 建堆函数，HeapSort 的辅助函数
* 
* arr 为待排序数组，从该数组中选择一部分元素建堆
* start 为选择部分的开始位置
* end 为选择部分的结束位置
*/
void Heapify(int arr[], int start, int end)
{
	int idx_par = start; // 父结点位置
	int idx_chi = 2 * idx_par + 1; // 子结点位置，初始为左子结点位置，加 1 即为右子结点位置

	// 从父结点开始，逐层向下，构建子堆
	while (idx_chi <= end)
	{
		// 先比较左右结点的大小，取较大者和父结点比较，减少交换次数
		if (idx_chi + 1 <= end && arr[idx_chi] < arr[idx_chi + 1])
		{
			idx_chi++;
		}

		// 如果父结点小于较大的子结点，则交换
		// 交换后，可能会破坏以原较大子结点为根的堆结构
		// 因此，需要将原较大子结点所在的位置设为父结点位置，继续向下调整
		if (arr[idx_par] < arr[idx_chi])
		{
			Swap(&(arr[idx_par]), &(arr[idx_chi]));

			idx_par = idx_chi;
			idx_chi = 2 * idx_par + 1;
		}
		// 否则，父结点不小于子结点，无需交换
		// 因此也不会影响以子结点为根的堆结构，即调整完成，结束循环
		else
		{
			break;
		}
	}
}

void HeapSort(int arr[], int n)
{
	// 注意：在本函数中，待排序的数据存储在数组 arr 中
	// 用这些待排序数据构建的堆，同样存储在数组 arr 中
	// 构建堆之前，arr 存储的是无序数据
	// 构建成堆后，arr 存储的是堆
	// 首尾交换后，arr 分为两块：
	//	一块是用于再次构建堆的无序数据组成的数组
	//	一块是历次交换至尾部的有序数据组成的数组

	// 将整个待排序数组构建为堆，具体过程为：从最后一个非叶结点所在位
	// 置开始，逐个向前为每个非叶结点构建子堆，直至起始位置，完成构建
	for (int i = n / 2 -1; i >= 0; i--)
	{
		Heapify(arr, i, n - 1);
	}

	// 重复进行交换和重新建堆操作，即先将数组的第一个元素和最后一个元素交换（注意建堆后数组存放
	// 的是堆，数组第一个元素是堆的根结点），再将除最后一个元素之外的其余元素作为待排序数据重新
	// 建堆，然后再次：交换-重建-交换-重建...，直至重建的堆只包含 1 个元素，无需交换，排序完成
	for (int i = n - 1; i >= 1; i--)
	{
		// 交换
		Swap(&(arr[0]), &(arr[i]));

		// 建堆
		Heapify(arr, 0, i - 1);
	}

	// 打印排序结果
	Print("HeapSort: ", arr, n);
}

void MergeSort(int arr[], int n)
{
	// 保留传入的 arr 地址，用于排序完成后，确保传入的 arr 数组存放有序数据
	int* ori_arr = arr;

	// 定义辅助数组 tarr，用于存放排序后的数据
	int* tarr = (int*)malloc(sizeof(int) * n);
	if (!tarr)
	{
		printf("Error: -- MergeSort -- fail to alloc memory.\n");
		return;
	}

	// 初始时，视待排序数组已完成分，每个元素都是一个已排序的子数组，接下来要对这些子数组进行治（合并）

	// 设 i 为待两两合并的子数组可以包含的数据最大个数，初始 i = 1，每合并一次 i 的值翻倍
	for (int i = 1; i < n; i = i * 2)
	{
		int k = 0; // 设 k 为辅助数组待插入位置

		// 遍历待排序数组，两两取包含 i 个数组的子数组进行合并，合并结果存入辅助数组中
		for (int j = 0; j < n; j = j + i + i)
		{
			// 设取出的两个子数组为 M（理论下标范围：j~j+i-1）和 N（理论下标范围：j+i~Min(j+i+i-1,n)）
			// 随着 i 和 j 的增大，理论下标可能越界，M 和 N 的实际下标范围为 j~Min(j+i-1,n) 和 Min(j+i,n)~Min(j+i+i-1,n)

			int mr = j + i < n ? j + i : n; // M 的右侧界限（不包含在 M 内），同时是 N 的左侧起始位置（包含在 N 内）
			int nr = j + i + i < n ? j + i + i : n; // N 的右侧界限（不包含在 N 内）
			
			int x = j; // 设 x 为 M 的开始位置
			int y = mr; // 设 y 为 N 的开始位置

			// 不断比较 x 和 y 指向的数据，将较小者存入辅助数组，并将对应的 x 或 y 加 1
			while (x < mr && y < nr)
			{
				tarr[k++] = (arr[x] < arr[y]) ? arr[x++] : arr[y++];
			}

			// 如果 x 先越界，则将 N 剩余的数据依次存入辅助数组中
			while (y < nr)
			{
				tarr[k++] = arr[y++];
			}

			// 如果 y 先越界，则将 M 剩余的数据依次存入辅助数组中
			while (x < mr)
			{
				tarr[k++] = arr[x++];
			}
		}

		// 本次遍历后，辅助数组存放的是经过合并后相对有序的数据，下次遍历时，
		// 需将本次的辅助数组作为待排序数组，将本次的待排序数组作为辅助数组
		int* ptr = arr;
		arr = tarr;
		tarr = ptr;
	}

	// 由排序过程中 arr 和 tarr 变量值的交换逻辑可知，排序完成后，arr 变量指向的数组存放的
	// 是排序后的数据，但 arr 指向的不一定是原始的待排序数组，而可能是代码中创建的辅助数组，
	// 也就是说，最后存放有序数据的，可能是原始的待排序数组，也可能是代码中创建的辅助数组，因
	// 此需要做个判断，确保原始的待排序数组存放有序的数据，并可以正确释放代码中创建的辅助数组
	if (arr != ori_arr)
	{
		for (int i = 0; i < n; i++)
		{
			ori_arr[i] = arr[i];
		}
		tarr = arr;
	}

	// 释放辅助数组空间
	free(tarr);

	// 打印排序结果
	Print("MergeSort: ", ori_arr, n);
}

void CountSort(int arr[], int n, int k)
{
	// 定义辅助数组 carr 和 tarr
	// tarr 用于存放排序结果，长度为 n
	// carr 用于存放 arr 中个元素的个数，即 carr[m] 表示 arr 中等于 m 的元素的个数，长度为 k + 1
	int* tarr = (int*)malloc(sizeof(int) * n);
	int* carr = (int*)malloc(sizeof(int) * (k + 1));
	if (!tarr || !carr)
	{
		printf("Error: -- CountSort -- fail to alloc memory.\n");
		return;
	}

	// 初始设 carr 中元素值均为 0
	for (int i = 0; i <= k; i++)
	{
		carr[i] = 0;
	}

	// 遍历数组 arr，统计各元素的个数，存入 carr 中
	for (int i = 0; i < n; i++)
	{
		int v = arr[i];
		carr[v] += 1;
	}

	// 遍历数组 carr，将每个元素更新为该元素及其之前元素的累加和
	int cur_sum = carr[0];
	for (int i = 1; i <= k; i++)
	{
		carr[i] += cur_sum;
		cur_sum = carr[i];
	}

	// 倒序遍历数组 arr，若 arr[i] == m 且 carr[m] == n
	// 说明元素 m 应位于有序序列的第 n 个位置，即数组 n-1 下标 ，因此设 tarr[n-1] = m
	// 同时，arr 中可能含有多个 m，未避免放置后续 m 时位置重复，还需将 carr[m] 的值减一
	for (int i = n -1; i > -1; i--)
	{
		int v = arr[i];
		int pos = carr[v] - 1;
		tarr[pos] = v;
		carr[v]--;
	}

	// 将排序结果写回 arr
	for (int i = 0; i < n; i++)
	{
		arr[i] = tarr[i];
	}

	// 打印排序结果
	Print("CountSort: ", arr, n);

	// 释放辅助数组的内存空间
	free(carr);
	free(tarr);
}

typedef struct RNode
{
	int v;
	struct RNode* next;
}RNode, *RList;

void RadixSort(int arr[], int n)
{
	int k = 10;

	// 定义辅助数组 larr，larr[i] 存放某一位上的的数值等于 i 的完整数值数组成的链表
	// 对于十进制数，因为位上的数值取值范围均为 0~9，共 10 个，故 larr 的长度为 10
	RList* larr = (RList*)malloc(sizeof(RList) * k);
	if (!larr)
	{
		printf("Error: -- RadixSort -- fail to alloc memory.\n");
		return;
	}
	for (int i = 0; i < k; i++)
	{
		larr[i] = NULL;
	}

	// 为每个待排序数据创建一个结点，用于在排序过程中组成链表
	// 每个结点地址保存在数组中，且有 narr[i]->v = arr[i]
	// 如此可避免在排序过程中进行结点的创建和回收，提升整体效率
	RNode** narr = (RNode**)malloc(sizeof(RNode*) * n);
	if (!narr)
	{
		printf("Error: -- RadixSort -- fail to alloc memory.\n");
		return;
	}
	for (int i = 0; i < n; i++)
	{
		RNode* p_rn = (RNode*)malloc(sizeof(RNode));
		if (!p_rn)
		{
			printf("Error: -- RadixSort -- fail to alloc memory.\n");
			return;
		}
		p_rn->v = arr[i];
		p_rn->next = NULL;
		narr[i] = p_rn;
	}

	// 遍历数组 arr，找出最大值
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}

	// 根据最大值，求出最大位数
	int deg = 0;
	for (int i = max; i > 0; i = i / k)
	{
		deg++;
	}

	// 按从低位到高位的顺序，多次遍历数组 arr
	for (int i = 0; i < deg; i++)
	{
		// 遍历数组 arr，根据完整数值某一位上的数值，将完整数值存入 larr 对应链表中
		for (int m = 0; m < n; m++)
		{
			// 获取完整数值某一位上的数值
			int dv = 0;
			int wv = arr[m];
			for (int r = 0; r <= i; r++)
			{
				dv = wv % 10;
				wv = wv / 10;
			}

			// 将完整数值对应的结点存入 larr 对应链表中
			if (larr[dv] == NULL)
			{
				larr[dv] = narr[m];
			}
			else
			{
				RNode* ptr = larr[dv];
				while (ptr->next)
				{
					ptr = ptr->next;
				}
				ptr->next = narr[m];
			}
		}

		// 遍历 larr，按序将链表中结点的数值写回 arr 并同步调整 narr，然后进入下个循环
		int pos = 0;
		for (int m = 0; m < k; m++)
		{
			RList rs = larr[m];
			while (rs)
			{
				arr[pos] = rs->v;
				narr[pos] = rs;
				rs = rs->next;
				narr[pos]->next = NULL;
				pos++;
			}
			larr[m] = NULL;
		}
	}

	// 打印排序结果
	Print("RadixSort: ", arr, n);

	// 释放内存
	for (int i = 0; i < n; i++)
	{
		free(narr[i]);
	}
	free(larr);
}

void BucketSort(int arr[], int n, int k)
{
	// 按从 0 开始，每个桶存放的数据范围是 10 个连续数据的规则来划分桶
	// 注意：桶内存放的数据范围是 10 个连续数据，并不是说桶内只能存放 10 个数据
	// 因为待排序数据中可能有重复数据，比如在 0~9 范围内的数据有 20 个，所以桶的容量应设置的大一些
	int buc_num = 0;
	int buc_ran = 10;
	int buc_cap = 30;
	for (int i = 0; i <= k; i += buc_ran)
	{
		buc_num++;
	}

	// 定义用来存放桶的数组，因为桶本身也是数组，所以存放桶的数组是一个二维数组
	// 注意：因为桶本身也是数组，所以存放桶的数组中，每个元素都是指向数组的指针
	int** tdarr = (int**)malloc(sizeof(int*) * buc_num);
	if (!tdarr)
	{
		printf("Error: -- BucketSort -- fail to alloc memory.\n");
		return;
	}
	for (int i = 0; i < buc_num; i++)
	{
		// 创建用数组表示的桶，并存入用来存放桶的数组中
		// 为方便之后将数据放入桶中，用于表示桶的数组比桶的容量多 1
		// 这多出来的一个空间，存放桶目前待存入数据的位置，初始为 0
		tdarr[i] = (int*)malloc(sizeof(int) * (buc_cap + 1));
		if (!tdarr[i])
		{
			printf("Error: -- BucketSort -- fail to alloc memory.\n");
			return;
		}
		tdarr[i][buc_cap] = 0;
	}

	// 将 arr 中的数据放入对应的桶中
	for (int i = 0; i < n; i++)
	{
		// 先计算要放入哪个桶
		int idx = arr[i] / 10;
		// 再放入桶中合适位置
		int pos = tdarr[idx][buc_cap];
		if (pos == 30)
		{
			// 桶已满，无法再放置数据，说明设置的桶容量偏小，报错
			printf("Error: -- BucketSort -- bucket is already full.\n");
			return;
		}
		tdarr[idx][pos] = arr[i];
		tdarr[idx][buc_cap]++;
	}

	// 对每个含有有效数据的桶进行排序，排序算法没有要求，此处选用直接插入排序
	for (int i = 0; i < buc_num; i++)
	{
		int count = tdarr[i][buc_cap];
		if (count > 0)
		{
			// 使用直接插入排序算法对桶内数据进行排序
			for (int m = 1; m < count; m++)
			{
				int tmp = tdarr[i][m];

				int n = m - 1;
				while (n > -1 && tmp < tdarr[i][n])
				{
					tdarr[i][n + 1] = tdarr[i][n];
					n--;
				}
				
				tdarr[i][n + 1] = tmp;
			}
		}
	}

	// 按序将各个已排序的桶中的数据写回 arr
	int cur_pos = 0;
	for (int i = 0; i < buc_num; i++)
	{
		int count = tdarr[i][buc_cap];
		for (int k = 0; k < count; k++)
		{
			arr[cur_pos++] = tdarr[i][k];
		}
	}
	
	// 打印排序结果
	Print("BucketSort: ", arr, n);

	// 释放桶空间，以及存放桶的数组的空间
	for (int i = 0; i < buc_num; i++)
	{
		free(tdarr[i]);
	}
	free(tdarr);
}
