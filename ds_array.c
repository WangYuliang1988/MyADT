#include "ds_array.h"

void TransTSMatrix(TSMatrix tsm, TSMatrix* p_tst)
{
	// 首先，根据原矩阵设置转置矩阵的行数、列数、非零元素个数；
	// 然后，遍历原矩阵 tsm 的三元组数组，依次寻找列序为 1...n 的项；
	// 将该项的行序、列序、值，分别作为目标项的列序、行序、值，存入 p_tst 指向的转置矩阵的三元组数组中。
	//
	// 注意：矩阵的三元组数组从位置 1 开始存储。

	p_tst->mu = tsm.nu;
	p_tst->nu = tsm.mu;
	p_tst->tu = tsm.tu;

	int cur_col = 1; // 当前需要从原矩阵中寻找的三元组的列序，按 1, 2, 3...递增
	int cur_index = 1; // 转置矩阵当前应该设置的三元组数组的元素索引，注意是从索引 1 开始存储
	
	while (cur_col <= tsm.nu)
	{
		for (int k = 1; k <= tsm.tu; k++)
		{
			if (tsm.data[k].j == cur_col)
			{
				p_tst->data[cur_index].i = tsm.data[k].j;
				p_tst->data[cur_index].j = tsm.data[k].i;
				p_tst->data[cur_index].e = tsm.data[k].e;
				cur_index++;
			}
		}
		cur_col++;
	}
}

void FastTransTSMatrix(TSMatrix tsm, TSMatrix* p_tst)
{
	// 首先，根据原矩阵设置转置矩阵的行数、列数、非零元素个数；
	// 然后，遍历原矩阵 tsm 的三元组数组，得出每列（即转置矩阵的每行）包含的元素个数，存入一个数组中；
	// 接着，新建一个数组，记录原矩阵每列当前项应该存入转置矩阵三元组数组中的位置，并在每次存入后更新；
	// 最后，按列遍历原矩阵，并直接将每次遍历的项，按步骤 3 数组指定的位置，存入转置矩阵三元组数组中。
	//
	// 注意：矩阵的三元组数组从位置 1 开始存储。

	p_tst->mu = tsm.nu;
	p_tst->nu = tsm.mu;
	p_tst->tu = tsm.tu;

	// 需要建立的前置数组所需内存大小，为保持数组索引同列序一致（从 1 开始），故多分配 1 个单位内存
	int mem_size = sizeof(int) * (tsm.nu + 1);

	// 存储原矩阵每列包含元素个数的数组
	// 索引即列序，值即该列包含的元素个数
	int* col_count_arr = (int*)malloc(mem_size);
	if (col_count_arr == NULL)
	{
		printf("Error: -- FastTransTSMatrix -- fail to malloc memory.\n");
		exit(EXIT_FAILURE);
	}
	// 先将每列元素个数初始化为 0
	for (int col = 1; col <= tsm.nu; col++)
	{
		col_count_arr[col] = 0;
	}
	// 然后遍历原矩阵，得出每列包含的元素个数
	for (int k = 1; k <= tsm.tu; k++)
	{
		col_count_arr[tsm.data[k].j]++;
	}

	// 存储原矩阵每列当前项应该存入转置矩阵三元组数组中位置的数组
	// 索引即列序，值即该列当前项应存入位置
	int* col_cur_idx_arr = (int*)malloc(mem_size);
	if (col_cur_idx_arr == NULL)
	{
		printf("Error: -- FastTransTSMatrix -- fail to malloc memory.\n");
		exit(EXIT_FAILURE);
	}
	// 第 1 列第一项应存入的位置是 1
	col_cur_idx_arr[1] = 1;
	// 依次计算第 2 列开始每列第一项应存入的位置
	for (int col = 2; col <= tsm.nu; col++)
	{
		col_cur_idx_arr[col] = col_cur_idx_arr[col - 1] + col_count_arr[col - 1];
	}
	
	// 按列遍历原矩阵，完成转置
	// 注意每将原矩阵中某列的项存入转置矩阵后，需同步更新该列位置数组中的值加一
	for (int k = 1; k <= tsm.tu; k++)
	{
		int col = tsm.data[k].j;
		int cur_index = col_cur_idx_arr[col];
		p_tst->data[cur_index].i = tsm.data[k].j;
		p_tst->data[cur_index].j = tsm.data[k].i;
		p_tst->data[cur_index].e = tsm.data[k].e;
		col_cur_idx_arr[col]++;
	}

	free(col_count_arr);
	free(col_cur_idx_arr);
	col_count_arr = NULL;
	col_cur_idx_arr = NULL;
}
