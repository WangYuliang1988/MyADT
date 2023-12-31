#include "ds_string.h"

//
// 串的模式匹配算法
//
// 模式匹配，即在主串中寻找子串出现的位置
//
// 算法基于串的定长顺序存储结构实现，共有两种思路：朴素匹配 & KMP算法
//

/*
* 朴素匹配
* 
* 算法思想：
*	从主串的某个指定位置起和子串的第一个字符进行匹配，相同则继续匹配下个字符，不同则从主串指定位置加 1 起重新和子串进行匹配。
* 
* s 为主串，p 为子串，pos 为主串中开始进行匹配查找的位置。
* 
* 注意：SString 中位置 0 存放串长度，字符序列从位置 1 开始存放。
*/
int SStringIndex(SString s, SString p, int pos)
{
	// 首先，进行边界判断：
	//	1. 子串（p）长度不能大于主串（s）长度；
	//	2. 主串开始匹配位置（pos）需合法（1 <= pos <= s[0] - p[0] + 1）；
	// 
	// 然后，开始进行遍历：
	//	1. 设 m = pos 为主串遍历索引，n = 1 为子串遍历索引，同步对主串和子串进行遍历；
	//	2. 若子串和主串字符相同，则 m、n 各加 1，继续遍历；
	//	3. 若子串和主串字符不同，则 m 回退至主串本次开始遍历位置的下一个位置，即：m - (n - 1) + 1，n 回退至 1，继续遍历；
	//	4. 若子串能够完成遍历，说明子串所有字符均和主串中字符对应，匹配成功，返回子串首字符对应主串中的位置；否则，匹配失败，返回 0。

	if (p[0] > s[0])
	{
		printf("Error: -- SStringIndex -- The substring is longer than main string.\n");
		return 0;
	}

	if (pos < 1 || pos > s[0] - p[0] + 1)
	{
		printf("Error: -- SStringIndex -- invalid positon: %d.\n", pos);
		return 0;
	}

	int m = pos, n = 1;
	while (m <= s[0] && n <= p[0])
	{
		if (s[m] == p[n])
		{
			if (n == p[0])
			{
				return m - (n - 1);
			}
			else {
				m++, n++;
			}
		}
		else
		{
			m = m - (n - 1) + 1, n = 1;
		}
	}

	return 0;
}

void NextP(SString p, int next[]);
/*
* KMP 匹配
* 
* 背景介绍：
*	KMP 算法由 D.E.Knuth、J.H.Morris 和 V.R.Pratt 三人共同提出，在朴素匹配的基础上，通过消除主串指针的回溯，达到效率的提升。
* 
* 算法思想：
*	从主串的某个指定位置起和子串的第一个字符进行匹配，相同则继续匹配下个字符；
*	不同则保持主串此刻位置不变，子串根据下方推导过程得出的某个位置开始再次进行匹配；
*	若子串中找不到再次进行匹配的位置，则主串移动到下一个位置，子串从第一个字符开始重新匹配。
* 
* 推导过程：
*	主串：S[1]S[2]...S[X]，子串：P[1]P[2]...P[Y]，m 为主串遍历索引，n 为子串遍历索引。
* 
*	当某次匹配失效时，有 S[m] != P[n] 且：
*		S[m-n+1]...S[m-1] = P[1]...P[n-1]
* 
*	假设子串存在位置 k (k < n)，可使主串遍历索引 m 不变而直接从子串的位置 k 继续匹配，则应满足：
*		S[m-k+1]...S[m-1] = P[1]...P[k-1]
* 
*	综上可得：
*		1. S[m-n+1]...S[m-1] = P[1]...P[n-1]
*		2. S[m-k+1]...S[m-1] = P[1]...P[k-1]
* 
*	因为 k < n，可知等式 2 中的 S 串包含在等式 1 的 S 串中，且为等式 1 中 S 串的后段。
*	此时，若将等式 1 中的 S 串进行截断，也只取从 m-k+1 到 m-1 这一后段，即取下标增加 n-k 后的元素作为首元素。
*	那么，为保持等式 1 平衡，其 P 串也需同步进行截断，即同样取下标增加 n-k 后的元素作为首元素，则等式 1 变为：
*		3. S[m-k+1]...S[m-1] = P[n-k+1]...P[n-1]
* 
*	将上述等式 2 和等式 3 进行对比，可得：
*		4. P[1]...P[k-1] = P[n-k+1]...P[n-1]
* 
*	因此，当主串的第 m 个字符和子串的第 n 个字符不相等时，若子串中存在位置 k 满足上述等式 4，则可直接将 n 设为 k，继续进行匹配。
* 
*	综上，可以事先对子串进行分析，求出每个位置上的字符不匹配时，下一个继续匹配的字符位置，形成一个数组。
*	匹配失效时，直接从数组中取子串继续匹配位置，再次匹配。数组的生成即依据上述等式 4，具体实现见 NextP() 函数。
* 
* s 为主串，p 为子串，pos 为主串中开始进行匹配查找的位置。
* 
* 注意：SString 中位置 0 存放串长度，字符序列从位置 1 开始存放。
*/
int SStringIndexKMP(SString s, SString p, int pos)
{
	// 首先，进行边界判断：
	//	1. 子串（p）长度不能大于主串（s）长度；
	//	2. 主串开始匹配位置（pos）需合法（1 <= pos <= s[0] - p[0] + 1）；
	// 
	// 然后，求出子串的 next 数组，用于匹配失效时子串回退；
	// 
	// 最后，开始进行遍历：
	//	1. 设 m = pos 为主串遍历索引，n = 1 为子串遍历索引，同步对主串和子串进行遍历；
	//	2. 若子串和主串字符相同，则 m、n 各加 1，继续遍历；
	//	3. 若子串和主串字符不同，则查看 next[n]：
	//		若 next[n] 大于 0，则 m 不变，n 回退至 next[n]，继续遍历；
	//		若 next[n] 等于 0，则 m 加 1，n 设为 1，继续遍历；
	//	4. 若子串能够完成遍历，说明子串所有字符均和主串中字符对应，匹配成功，返回子串首字符对应主串中的位置；否则，匹配失败，返回 0。

	if (p[0] > s[0])
	{
		printf("Error: -- SStringIndexKMP -- The substring is longer than main string.\n");
		return 0;
	}

	if (pos < 1 || pos > s[0] - p[0] + 1)
	{
		printf("Error: -- SStringIndexKMP -- invalid positon: %d.\n", pos);
		return 0;
	}

	int next[sizeof(p) / sizeof(p[0])];
	NextP(p, next);

	int m = pos, n = 1;
	while (m <= s[0] && n <= p[0])
	{
		if (s[m] == p[n])
		{
			if (n == p[0])
			{
				return m - (n - 1);
			}
			else {
				m++, n++;
			}
		}
		else
		{
			n = next[n];
			if (n == 0)
			{
				m++;
				n = 1;
			}
		}
	}

	return 0;
}

/*
* 求子串 next 数组
* 
* 分析子串，求出子串每个位置字符同主串匹配失效时，下一个继续匹配的字符位置，存入数组 next 中。
* 
* 根据 KMP 算法，当子串位置 n 的字符匹配失效时：
*	若 n = 1，即子串首字符就不匹配，则应移动主串而非子串，即 next[1] 的值应是一个无效位置，故设 next[1] = 0；
*	若 n > 1，且：
*		存在 k 使 P[1]...P[k-1] = P[n-k+1]...P[n-1]，则有 next[n] = k；
*		不存在满足上述条件的 k，则应从子串的首字符开始匹配，则有 next[n] = 1。
* 
* 注意：
*	为同 SString 结构保持一致，next 数组的有效索引从 1 开始，索引 0 存放内容无需关注。
* 
* 思路：
*	已知 next[1] = 0，采用递推法依次求得子串中每个位置匹配失效时对应的下一匹配位置。
* 
*	假设 next[n] = k，求 next[n+1]，可分两种情况求解：
* 
*	情况一：P[n] = P[k]
*		因 next[n] = k，则 P[1]...P[k-1] = P[n-k+1]...P[n-1]；
*		又因 P[k] = P[n]，则 P[1]...P[k-1]P[k] = P[n-k+1]...P[n-1]P[n]；
*		即存在位置 k+1，满足当子串位置 n+1 匹配失效时使 P[1]...P[k] = P[n-k+1]...P[n]；
*		因此 next[n+1] = k + 1，又 k = next[n]，故 next[n+1] = next[n] + 1。
*	可得：next[n+1] = k + 1 = next[n] + 1。
* 
*	情况二：P[n] != P[k]
*		即：P[1]...P[k-1] = P[n-k+1]...P[n-1] 且 P[k] != P[n]；
*		此时，我们把 P[n-k+1]...P[n] 看作主串，把 P[1]...P[k] 看作子串；
*		当 P[k] != P[n] 时，根据 KMP 算法思想，应保持主串位置不变，子串从 next[k] 位置起重新匹配；
*		问题演变为比较 P[n] 是否等于 P[next[k]]：
*			若 P[n] == P[next[k]]，则 P[1]...P[next[k]] = P[n-next[k]+1]...P[n]，则 next[n+1] = next[k] + 1；
*			若 P[n] != P[next[k]]，则再次将 P[n-netx[k]+1]...P[n] 看作主串，把 P[1]...P[next[k]] 看作子串；
*			问题再次演变为比较 P[n] 是否等于 P[next[next[k]]]...
*	可得：P[n] != P[k] 时会触发一个递归寻找，结束的条件是某次比较时 P[n] 等于当时的 P[next[k]] 或者当时的 P[next[k]] = 0。
*/
void NextP(SString p, int next[])
{
	int k = next[1] = 0; // 初始已知，递推求解的基础

	int n = 1;
	while (n < p[0]) // 该循环是依次求 next[n+1] 的值（因 next[n] 已知），故 n 须小于而不能等于子串长度
	{
		if (k == 0 || p[n] == p[k])
		{
			next[++n] = ++k; // 求得 next[n+1] 并同步更新 k（语句执行后 k == next[n+1]），作为下次循环求 next[n+2] 的基础
		}
		else
		{
			k = next[k]; // 递归寻找满足 k == 0 或 p[n] == p[k] 的 k 值
		}
	}
}