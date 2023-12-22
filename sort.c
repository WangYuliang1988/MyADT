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
	// �� arr ����Ϊ��������һ���������������һ���Ǵ����������
	// ��ʼʱ������������Ϊ arr[0]������������Ϊ arr[1] ~ arr[n-1]
	// �������������򣬽���������λ�ò������������򣬽����ݲ�������������ĺ���λ��

	for (int i = 1; i < n; i++)
	{
		// i ֮ǰ������������ݣ��� i-1 λ�õ������������������е�������ݣ�����Ϊ����
		// ��ˣ��� arr[i] > arr[i-1]���� arr[i] �Ĳ���λ�þ����䵱ǰλ�ã����账��
		// ������Ҫ������������Ѱ�Һ��ʵĲ���λ�ã�����Ѱ�ҹ������ƶ��������ڳ��ռ�

		if (arr[i] < arr[i-1])
		{
			int tmp = arr[i];

			// ʹ��˳����ҵķ�ʽ���Ҵ�����λ�ã����ô������� arr[i] �������������ĩβ���ݿ�ʼ������
			// ���Ƚϣ�ֱ�� arr[i] ���ڵ���ĳ��λ�õ����ݻ�λ�õ��� -1�����λ�� + 1 ���Ǵ�����λ��
			int k = i - 1;
			while (tmp < arr[k] && k > -1)
			{
				arr[k + 1] = arr[k]; // Ѱ��λ�õĹ������ƶ����ݣ��������������ڳ��ռ�
				k--;
			}
			arr[k + 1] = tmp;
		}

		// ÿѭ��һ�Σ����������򶼻�����һ������
	}

	// ��ӡ������
	Print("InsertSort: ", arr, n);
}

void BiInsertSort(int arr[], int n)
{
	// �۰���������˼·��ֱ�Ӳ�����ͬ
	// ��֮ͬ������ʹ���۰����ȷ��λ��
	// ���������ҵ�λ�ã�Ȼ�����ƶ�����

	for (int i = 1; i < n; i++)
	{
		int tmp = arr[i];

		// ͨ���۰���ң����Һ� arr[i] ��ȵ�����
		// ����֤�������ҽ�����low ��Ϊ������λ��
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

		// �� i - 1 �� low ������ͳһ���ƣ��ڳ��ռ䣬Ȼ�����
		for (int j = i - 1; j >= low; j--)
		{
			arr[j + 1] = arr[j];
		}
		arr[low] = tmp;

		// ÿѭ��һ�Σ����������򶼻�����һ������
	}

	// ��ӡ������
	Print("BiInsertSort: ", arr, n);
}

void TwInsertSort(int arr[], int n)
{
	// ���帨�����飬��������ʹ��ʱӦ��Ϊ��β��ӵĻ�������
	// ���������±�ļ�һ��һ�ֱ�Ϊ (i+1+n) % n �� (i-1+n) % n
	int* tarr = (int*)malloc(sizeof(int) * n);
	if (!tarr)
	{
		printf("Error: -- TwInsertSort -- fail to alloc memory.\n");
		return;
	}

	// ��ʼ������������ĵ�һ�����ݷ��븨������ 0 λ��
	tarr[0] = arr[0];

	// ���� first �� final �ֱ�ָ���������е���С���������
	int first = 0, final = 0;

	// �������������飬����ȡ�����ݷ��븨������ĺ���λ��
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
			final = (final + 1 + n) % n; // ��������ǰ���������Ҳ������һλ
		}
	}

	// �� first - final ��˳�� tarr �е����ݿ����� arr ��
	for (int i = 0; i < n; i++)
	{
		arr[i] = tarr[(first + i) % n];
	}

	// �ͷŸ�������ռ�ÿռ�
	free(tarr);

	// ��ӡ������
	Print("TwInsertSort: ", arr, n);
}

void ShellInsert(int arr[], int n)
{
	// ѡ�񲻶϶� n ���ж���ֱ�� 1 ��Ϊ��������
	for (int i = n / 2; i > 0; i = i / 2)
	{
		// ʹ�������������������Ϊ���������飬��ÿ�����������ֱ�Ӳ�������
		// ֱ��������Ϊ 1 ʱ���൱�ڶ������������������ս���һ��ֱ�Ӳ�������

		// ����Ϊ i ʱ���൱�ڻ��ֳ� i - 1 ��������
		for (int j = 0; j < i; j++)
		{
			// ��ÿ�����������ֱ�Ӳ�������ע�����������������ݵ��±����� i
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
	// �� n �����ݽ��� n-1 �������Ƚ�
	for (int i = 1; i < n; i++)
	{
		// �� i �˱Ƚϣ�i �� 1 ��ʼ��������Ҫ���еıȽϴ����� n-i
		for (int j = 0; j < n - i; j++)
		{
			// ����ǰԪ��С�ڵ������Ԫ�أ��������
			// ���򣬵�ǰԪ�غ����Ԫ�ؽ���λ�ý���
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
		int k = arr[begin]; // ѡȡ�����������һ����Ϊ��׼�� k

		int left = begin; // left ���ڴ�����Ѱ�Ҵ��� k ��������ʼʱָ�������һ������Ҳ��ָ�� k
		int right = end; // right ���ڴ��ҵ���Ѱ��С�� k ��������ʼʱָ���������һ����

		while (left < right)
		{
			// �ȴ� right ��ʼ������Ѱ�ҵ�һ��С�� k ������
			while (left < right && arr[right] >= k)
			{
				right--;
			}
			// �����ҵ����򽻻� arr[right] �� k ��λ�ã�������left ָ�������
			// ��Ϊ arr[right]��right ָ������ݱ�Ϊ k����Ϊ arr[right] �Ѵ���
			// ����λ�ã������ٲ���֮��ıȽϣ������轫 left++
			if (left < right)
			{
				arr[left] = arr[right];
				arr[right] = k;
				left++;
			}

			// �ٴ� left ��ʼ������Ѱ�ҵ�һ������ k ������
			while (left < right && arr[left] <= k)
			{
				left++;
			}
			// �����ҵ����򽻻� arr[left] �� k ��λ�ã�������left ָ�������
			// ��Ϊ k��right ָ������ݱ�Ϊ arr[left]����Ϊ arr[left] �Ѵ���
			// ����λ�ã������ٲ���֮��ıȽϣ������轫 right--
			if (left < right)
			{
				arr[right] = arr[left];
				arr[left] = k;
				right--;
			}
		}

		// ѭ��������k ���ڵ�λ�� pos == left == right���� pos Ϊ�ָ�
		// �㣬�ֱ�� beign ~ pos - 1 �� pos + 1 ~ end �ݹ���п�������
		QuickSort(arr, n, begin, left - 1);
		QuickSort(arr, n, left + 1, end);

		// ��ӡ������
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
* �����������ͱ�����ֵ
* 
* HeapSort �ĸ�������
*/
void Swap(int* ptr_m, int* ptr_n)
{
	int tmp = *ptr_m;
	*ptr_m = *ptr_n;
	*ptr_n = tmp;
}

/*
* ���Ѻ�����HeapSort �ĸ�������
* 
* arr Ϊ���������飬�Ӹ�������ѡ��һ����Ԫ�ؽ���
* start Ϊѡ�񲿷ֵĿ�ʼλ��
* end Ϊѡ�񲿷ֵĽ���λ��
*/
void Heapify(int arr[], int start, int end)
{
	int idx_par = start; // �����λ��
	int idx_chi = 2 * idx_par + 1; // �ӽ��λ�ã���ʼΪ���ӽ��λ�ã��� 1 ��Ϊ���ӽ��λ��

	// �Ӹ���㿪ʼ��������£������Ӷ�
	while (idx_chi <= end)
	{
		// �ȱȽ����ҽ��Ĵ�С��ȡ�ϴ��ߺ͸����Ƚϣ����ٽ�������
		if (idx_chi + 1 <= end && arr[idx_chi] < arr[idx_chi + 1])
		{
			idx_chi++;
		}

		// ��������С�ڽϴ���ӽ�㣬�򽻻�
		// �����󣬿��ܻ��ƻ���ԭ�ϴ��ӽ��Ϊ���Ķѽṹ
		// ��ˣ���Ҫ��ԭ�ϴ��ӽ�����ڵ�λ����Ϊ�����λ�ã��������µ���
		if (arr[idx_par] < arr[idx_chi])
		{
			Swap(&(arr[idx_par]), &(arr[idx_chi]));

			idx_par = idx_chi;
			idx_chi = 2 * idx_par + 1;
		}
		// ���򣬸���㲻С���ӽ�㣬���轻��
		// ���Ҳ����Ӱ�����ӽ��Ϊ���Ķѽṹ����������ɣ�����ѭ��
		else
		{
			break;
		}
	}
}

void HeapSort(int arr[], int n)
{
	// ע�⣺�ڱ������У�����������ݴ洢������ arr ��
	// ����Щ���������ݹ����Ķѣ�ͬ���洢������ arr ��
	// ������֮ǰ��arr �洢������������
	// �����ɶѺ�arr �洢���Ƕ�
	// ��β������arr ��Ϊ���飺
	//	һ���������ٴι����ѵ�����������ɵ�����
	//	һ�������ν�����β��������������ɵ�����

	// ���������������鹹��Ϊ�ѣ��������Ϊ�������һ����Ҷ�������λ
	// �ÿ�ʼ�������ǰΪÿ����Ҷ��㹹���Ӷѣ�ֱ����ʼλ�ã���ɹ���
	for (int i = n / 2 -1; i >= 0; i--)
	{
		Heapify(arr, i, n - 1);
	}

	// �ظ����н��������½��Ѳ��������Ƚ�����ĵ�һ��Ԫ�غ����һ��Ԫ�ؽ�����ע�⽨�Ѻ�������
	// ���Ƕѣ������һ��Ԫ���Ƕѵĸ���㣩���ٽ������һ��Ԫ��֮�������Ԫ����Ϊ��������������
	// ���ѣ�Ȼ���ٴΣ�����-�ؽ�-����-�ؽ�...��ֱ���ؽ��Ķ�ֻ���� 1 ��Ԫ�أ����轻�����������
	for (int i = n - 1; i >= 1; i--)
	{
		// ����
		Swap(&(arr[0]), &(arr[i]));

		// ����
		Heapify(arr, 0, i - 1);
	}

	// ��ӡ������
	Print("HeapSort: ", arr, n);
}

void MergeSort(int arr[], int n)
{
	// ��������� arr ��ַ������������ɺ�ȷ������� arr ��������������
	int* ori_arr = arr;

	// ���帨������ tarr�����ڴ������������
	int* tarr = (int*)malloc(sizeof(int) * n);
	if (!tarr)
	{
		printf("Error: -- MergeSort -- fail to alloc memory.\n");
		return;
	}

	// ��ʼʱ���Ӵ�������������ɷ֣�ÿ��Ԫ�ض���һ��������������飬������Ҫ����Щ����������Σ��ϲ���

	// �� i Ϊ�������ϲ�����������԰�������������������ʼ i = 1��ÿ�ϲ�һ�� i ��ֵ����
	for (int i = 1; i < n; i = i * 2)
	{
		int k = 0; // �� k Ϊ�������������λ��

		// �������������飬����ȡ���� i ���������������кϲ����ϲ�������븨��������
		for (int j = 0; j < n; j = j + i + i)
		{
			// ��ȡ��������������Ϊ M�������±귶Χ��j~j+i-1���� N�������±귶Χ��j+i~Min(j+i+i-1,n)��
			// ���� i �� j �����������±����Խ�磬M �� N ��ʵ���±귶ΧΪ j~Min(j+i-1,n) �� Min(j+i,n)~Min(j+i+i-1,n)

			int mr = j + i < n ? j + i : n; // M ���Ҳ���ޣ��������� M �ڣ���ͬʱ�� N �������ʼλ�ã������� N �ڣ�
			int nr = j + i + i < n ? j + i + i : n; // N ���Ҳ���ޣ��������� N �ڣ�
			
			int x = j; // �� x Ϊ M �Ŀ�ʼλ��
			int y = mr; // �� y Ϊ N �Ŀ�ʼλ��

			// ���ϱȽ� x �� y ָ������ݣ�����С�ߴ��븨�����飬������Ӧ�� x �� y �� 1
			while (x < mr && y < nr)
			{
				tarr[k++] = (arr[x] < arr[y]) ? arr[x++] : arr[y++];
			}

			// ��� x ��Խ�磬�� N ʣ����������δ��븨��������
			while (y < nr)
			{
				tarr[k++] = arr[y++];
			}

			// ��� y ��Խ�磬�� M ʣ����������δ��븨��������
			while (x < mr)
			{
				tarr[k++] = arr[x++];
			}
		}

		// ���α����󣬸��������ŵ��Ǿ����ϲ��������������ݣ��´α���ʱ��
		// �轫���εĸ���������Ϊ���������飬�����εĴ�����������Ϊ��������
		int* ptr = arr;
		arr = tarr;
		tarr = ptr;
	}

	// ����������� arr �� tarr ����ֵ�Ľ����߼���֪��������ɺ�arr ����ָ��������ŵ�
	// �����������ݣ��� arr ָ��Ĳ�һ����ԭʼ�Ĵ��������飬�������Ǵ����д����ĸ������飬
	// Ҳ����˵��������������ݵģ�������ԭʼ�Ĵ��������飬Ҳ�����Ǵ����д����ĸ������飬��
	// ����Ҫ�����жϣ�ȷ��ԭʼ�Ĵ�������������������ݣ���������ȷ�ͷŴ����д����ĸ�������
	if (arr != ori_arr)
	{
		for (int i = 0; i < n; i++)
		{
			ori_arr[i] = arr[i];
		}
		tarr = arr;
	}

	// �ͷŸ�������ռ�
	free(tarr);

	// ��ӡ������
	Print("MergeSort: ", ori_arr, n);
}

void CountSort(int arr[], int n, int k)
{
	// ���帨������ carr �� tarr
	// tarr ���ڴ��������������Ϊ n
	// carr ���ڴ�� arr �и�Ԫ�صĸ������� carr[m] ��ʾ arr �е��� m ��Ԫ�صĸ���������Ϊ k + 1
	int* tarr = (int*)malloc(sizeof(int) * n);
	int* carr = (int*)malloc(sizeof(int) * (k + 1));
	if (!tarr || !carr)
	{
		printf("Error: -- CountSort -- fail to alloc memory.\n");
		return;
	}

	// ��ʼ�� carr ��Ԫ��ֵ��Ϊ 0
	for (int i = 0; i <= k; i++)
	{
		carr[i] = 0;
	}

	// �������� arr��ͳ�Ƹ�Ԫ�صĸ��������� carr ��
	for (int i = 0; i < n; i++)
	{
		int v = arr[i];
		carr[v] += 1;
	}

	// �������� carr����ÿ��Ԫ�ظ���Ϊ��Ԫ�ؼ���֮ǰԪ�ص��ۼӺ�
	int cur_sum = carr[0];
	for (int i = 1; i <= k; i++)
	{
		carr[i] += cur_sum;
		cur_sum = carr[i];
	}

	// ����������� arr���� arr[i] == m �� carr[m] == n
	// ˵��Ԫ�� m Ӧλ���������еĵ� n ��λ�ã������� n-1 �±� ������� tarr[n-1] = m
	// ͬʱ��arr �п��ܺ��ж�� m��δ������ú��� m ʱλ���ظ������轫 carr[m] ��ֵ��һ
	for (int i = n -1; i > -1; i--)
	{
		int v = arr[i];
		int pos = carr[v] - 1;
		tarr[pos] = v;
		carr[v]--;
	}

	// ��������д�� arr
	for (int i = 0; i < n; i++)
	{
		arr[i] = tarr[i];
	}

	// ��ӡ������
	Print("CountSort: ", arr, n);

	// �ͷŸ���������ڴ�ռ�
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

	// ���帨������ larr��larr[i] ���ĳһλ�ϵĵ���ֵ���� i ��������ֵ����ɵ�����
	// ����ʮ����������Ϊλ�ϵ���ֵȡֵ��Χ��Ϊ 0~9���� 10 ������ larr �ĳ���Ϊ 10
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

	// Ϊÿ�����������ݴ���һ����㣬����������������������
	// ÿ������ַ�����������У����� narr[i]->v = arr[i]
	// ��˿ɱ�������������н��н��Ĵ����ͻ��գ���������Ч��
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

	// �������� arr���ҳ����ֵ
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}

	// �������ֵ��������λ��
	int deg = 0;
	for (int i = max; i > 0; i = i / k)
	{
		deg++;
	}

	// ���ӵ�λ����λ��˳�򣬶�α������� arr
	for (int i = 0; i < deg; i++)
	{
		// �������� arr������������ֵĳһλ�ϵ���ֵ����������ֵ���� larr ��Ӧ������
		for (int m = 0; m < n; m++)
		{
			// ��ȡ������ֵĳһλ�ϵ���ֵ
			int dv = 0;
			int wv = arr[m];
			for (int r = 0; r <= i; r++)
			{
				dv = wv % 10;
				wv = wv / 10;
			}

			// ��������ֵ��Ӧ�Ľ����� larr ��Ӧ������
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

		// ���� larr�����������н�����ֵд�� arr ��ͬ������ narr��Ȼ������¸�ѭ��
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

	// ��ӡ������
	Print("RadixSort: ", arr, n);

	// �ͷ��ڴ�
	for (int i = 0; i < n; i++)
	{
		free(narr[i]);
	}
	free(larr);
}

void BucketSort(int arr[], int n, int k)
{
	// ���� 0 ��ʼ��ÿ��Ͱ��ŵ����ݷ�Χ�� 10 ���������ݵĹ���������Ͱ
	// ע�⣺Ͱ�ڴ�ŵ����ݷ�Χ�� 10 ���������ݣ�������˵Ͱ��ֻ�ܴ�� 10 ������
	// ��Ϊ�����������п������ظ����ݣ������� 0~9 ��Χ�ڵ������� 20 ��������Ͱ������Ӧ���õĴ�һЩ
	int buc_num = 0;
	int buc_ran = 10;
	int buc_cap = 30;
	for (int i = 0; i <= k; i += buc_ran)
	{
		buc_num++;
	}

	// �����������Ͱ�����飬��ΪͰ����Ҳ�����飬���Դ��Ͱ��������һ����ά����
	// ע�⣺��ΪͰ����Ҳ�����飬���Դ��Ͱ�������У�ÿ��Ԫ�ض���ָ�������ָ��
	int** tdarr = (int**)malloc(sizeof(int*) * buc_num);
	if (!tdarr)
	{
		printf("Error: -- BucketSort -- fail to alloc memory.\n");
		return;
	}
	for (int i = 0; i < buc_num; i++)
	{
		// �����������ʾ��Ͱ���������������Ͱ��������
		// Ϊ����֮�����ݷ���Ͱ�У����ڱ�ʾͰ�������Ͱ�������� 1
		// ��������һ���ռ䣬���ͰĿǰ���������ݵ�λ�ã���ʼΪ 0
		tdarr[i] = (int*)malloc(sizeof(int) * (buc_cap + 1));
		if (!tdarr[i])
		{
			printf("Error: -- BucketSort -- fail to alloc memory.\n");
			return;
		}
		tdarr[i][buc_cap] = 0;
	}

	// �� arr �е����ݷ����Ӧ��Ͱ��
	for (int i = 0; i < n; i++)
	{
		// �ȼ���Ҫ�����ĸ�Ͱ
		int idx = arr[i] / 10;
		// �ٷ���Ͱ�к���λ��
		int pos = tdarr[idx][buc_cap];
		if (pos == 30)
		{
			// Ͱ�������޷��ٷ������ݣ�˵�����õ�Ͱ����ƫС������
			printf("Error: -- BucketSort -- bucket is already full.\n");
			return;
		}
		tdarr[idx][pos] = arr[i];
		tdarr[idx][buc_cap]++;
	}

	// ��ÿ��������Ч���ݵ�Ͱ�������������㷨û��Ҫ�󣬴˴�ѡ��ֱ�Ӳ�������
	for (int i = 0; i < buc_num; i++)
	{
		int count = tdarr[i][buc_cap];
		if (count > 0)
		{
			// ʹ��ֱ�Ӳ��������㷨��Ͱ�����ݽ�������
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

	// ���򽫸����������Ͱ�е�����д�� arr
	int cur_pos = 0;
	for (int i = 0; i < buc_num; i++)
	{
		int count = tdarr[i][buc_cap];
		for (int k = 0; k < count; k++)
		{
			arr[cur_pos++] = tdarr[i][k];
		}
	}
	
	// ��ӡ������
	Print("BucketSort: ", arr, n);

	// �ͷ�Ͱ�ռ䣬�Լ����Ͱ������Ŀռ�
	for (int i = 0; i < buc_num; i++)
	{
		free(tdarr[i]);
	}
	free(tdarr);
}
