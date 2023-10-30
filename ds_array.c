#include "ds_array.h"

void TransTSMatrix(TSMatrix tsm, TSMatrix* p_tst)
{
	// ���ȣ�����ԭ��������ת�þ��������������������Ԫ�ظ�����
	// Ȼ�󣬱���ԭ���� tsm ����Ԫ�����飬����Ѱ������Ϊ 1...n ���
	// ���������������ֵ���ֱ���ΪĿ�������������ֵ������ p_tst ָ���ת�þ������Ԫ�������С�
	//
	// ע�⣺�������Ԫ�������λ�� 1 ��ʼ�洢��

	p_tst->mu = tsm.nu;
	p_tst->nu = tsm.mu;
	p_tst->tu = tsm.tu;

	int cur_col = 1; // ��ǰ��Ҫ��ԭ������Ѱ�ҵ���Ԫ������򣬰� 1, 2, 3...����
	int cur_index = 1; // ת�þ���ǰӦ�����õ���Ԫ�������Ԫ��������ע���Ǵ����� 1 ��ʼ�洢
	
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
	// ���ȣ�����ԭ��������ת�þ��������������������Ԫ�ظ�����
	// Ȼ�󣬱���ԭ���� tsm ����Ԫ�����飬�ó�ÿ�У���ת�þ����ÿ�У�������Ԫ�ظ���������һ�������У�
	// ���ţ��½�һ�����飬��¼ԭ����ÿ�е�ǰ��Ӧ�ô���ת�þ�����Ԫ�������е�λ�ã�����ÿ�δ������£�
	// ��󣬰��б���ԭ���󣬲�ֱ�ӽ�ÿ�α������������ 3 ����ָ����λ�ã�����ת�þ�����Ԫ�������С�
	//
	// ע�⣺�������Ԫ�������λ�� 1 ��ʼ�洢��

	p_tst->mu = tsm.nu;
	p_tst->nu = tsm.mu;
	p_tst->tu = tsm.tu;

	// ��Ҫ������ǰ�����������ڴ��С��Ϊ������������ͬ����һ�£��� 1 ��ʼ�����ʶ���� 1 ����λ�ڴ�
	int mem_size = sizeof(int) * (tsm.nu + 1);

	// �洢ԭ����ÿ�а���Ԫ�ظ���������
	// ����������ֵ�����а�����Ԫ�ظ���
	int* col_count_arr = (int*)malloc(mem_size);
	if (col_count_arr == NULL)
	{
		printf("Error: -- FastTransTSMatrix -- fail to malloc memory.\n");
		exit(EXIT_FAILURE);
	}
	// �Ƚ�ÿ��Ԫ�ظ�����ʼ��Ϊ 0
	for (int col = 1; col <= tsm.nu; col++)
	{
		col_count_arr[col] = 0;
	}
	// Ȼ�����ԭ���󣬵ó�ÿ�а�����Ԫ�ظ���
	for (int k = 1; k <= tsm.tu; k++)
	{
		col_count_arr[tsm.data[k].j]++;
	}

	// �洢ԭ����ÿ�е�ǰ��Ӧ�ô���ת�þ�����Ԫ��������λ�õ�����
	// ����������ֵ�����е�ǰ��Ӧ����λ��
	int* col_cur_idx_arr = (int*)malloc(mem_size);
	if (col_cur_idx_arr == NULL)
	{
		printf("Error: -- FastTransTSMatrix -- fail to malloc memory.\n");
		exit(EXIT_FAILURE);
	}
	// �� 1 �е�һ��Ӧ�����λ���� 1
	col_cur_idx_arr[1] = 1;
	// ���μ���� 2 �п�ʼÿ�е�һ��Ӧ�����λ��
	for (int col = 2; col <= tsm.nu; col++)
	{
		col_cur_idx_arr[col] = col_cur_idx_arr[col - 1] + col_count_arr[col - 1];
	}
	
	// ���б���ԭ�������ת��
	// ע��ÿ��ԭ������ĳ�е������ת�þ������ͬ�����¸���λ�������е�ֵ��һ
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
