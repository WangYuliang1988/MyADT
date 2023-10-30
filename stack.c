#include "stack.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 定义顺序栈基本操作
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void InitSeqStack(SeqStack* p_seq_stack)
{
	p_seq_stack->p_base = (ElemType*)malloc(sizeof(ElemType) * SEQ_INIT_SIZE);
	if (p_seq_stack->p_base == NULL)
	{
		printf("Error: -- InitSeqStack -- fail to alloc memory.\n");
		exit(EXIT_FAILURE);
	}
	p_seq_stack->p_top = p_seq_stack->p_base; // 初始化时，base 和 p_top 指向同一块地址
	p_seq_stack->stack_size = SEQ_INIT_SIZE;
}

void Push(SeqStack* p_seq_stack, ElemType elem)
{
	long long length = p_seq_stack->p_top - p_seq_stack->p_base;

	// 判断当前是否栈满，若是，则扩展栈的空间
	if (length == p_seq_stack->stack_size)
	{
		ElemType* nbase = (ElemType*)realloc(p_seq_stack->p_base, sizeof(ElemType) * (p_seq_stack->stack_size + SEQ_INCREAMENT));
		if (nbase == NULL)
		{
			printf("Error: -- Push -- fail to realloc memory.\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			p_seq_stack->p_base = nbase;
			p_seq_stack->p_top = nbase + length;
			p_seq_stack->stack_size += SEQ_INCREAMENT;
		}
	}

	// 将元素入栈，注意 p_top 始终指向栈顶元素的下一位置
	*(p_seq_stack->p_top) = elem;
	p_seq_stack->p_top += 1;
}

void Pop(SeqStack* p_seq_stack, ElemType* p_elem)
{
	if (p_seq_stack->p_top == p_seq_stack->p_base)
	{
		printf("Error: -- Pop -- stack is empty.\n");
		exit(EXIT_FAILURE);
	}

	p_seq_stack->p_top -= 1;
	*p_elem = *(p_seq_stack->p_top);
}

void DestroySeqStack(SeqStack* p_seq_stack)
{
	if (p_seq_stack != NULL)
	{
		free(p_seq_stack->p_base);
		p_seq_stack->p_base = NULL;
		p_seq_stack->p_top = NULL;
		p_seq_stack->stack_size = 0;
	}
}

void GetTop(SeqStack seq_stack, ElemType* p_elem)
{
	if (seq_stack.p_top == seq_stack.p_base)
	{
		printf("Error: -- Pop -- stack is empty.\n");
		exit(EXIT_FAILURE);
	}

	*p_elem = *(seq_stack.p_top - 1);
}

int IsStackEmpty(SeqStack seq_stack)
{
	return seq_stack.p_top == seq_stack.p_base;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// 定义基于栈的算法应用
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void Convert(int dec, int target)
{
	if (dec <= 0 || target < 2 || target > 16)
	{
		printf("Error: -- Convert -- can only convert positive integer to 2-16 numberic system.\n");
		exit(EXIT_FAILURE);
	}

	SeqStack stack;
	InitSeqStack(&stack);

	while (dec > 0)
	{
		Push(&stack, dec % target);
		dec = dec / target;
	}

	ElemType i;
	while (stack.p_top > stack.p_base)
	{
		Pop(&stack, &i);
		if (i < 10)
		{
			printf("%lld", i);
		}
		else
		{
			printf("%c", (int)i + 55);
		}
	}

	DestroySeqStack(&stack);
}

int MatchBracket(char* p_exp)
{
	SeqStack stack;
	InitSeqStack(&stack);

	while (*p_exp != '\0')
	{
		char c = *p_exp;

		if (c == '(' || c == '[' || c == '{')
		{
			Push(&stack, c);
		}
		else if (c == ')' || c == ']' || c == '}')
		{
			// 若栈已空，则不匹配
			if (stack.p_top == stack.p_base)
			{
				return 0;
			}
			else {
				char p_top;
				GetTop(stack, (ElemType*)(&p_top));

				if ((p_top == '(' && c == ')') || (p_top == '[' && c == ']') || (p_top == '{' && c == '}'))
				{
					ElemType elem;
					Pop(&stack, &elem);
				}
				else {
					return 0;
				}
			}
		}

		p_exp++;
	}

	// 结束时栈为空表示匹配，不为空表示不匹配
	if (stack.p_top == stack.p_base)
	{
		return 1;
	}
	else {
		return 0;
	}

	DestroySeqStack(&stack);
}

/*
* 判断 opLeft 的优先级是否高于 opRight
* 
* 该函数是 CalcExpression() 的辅助函数
* 
* 四则运算符优先级：[* == /] > [+ == -]
*/
int IsHigher(char opLeft, char opRight)
{
	if ((opLeft == '*' || opLeft == '/') && (opRight == '+' || opRight == '-'))
	{
		return 1;
	}

	return 0;
}

/*
* 获取两个数字的四则运算结果
* 
* 该函数是 CalcExpression() 的辅助函数
*/
void CalcTwoNum(SeqStack* opStack, SeqStack* numStack)
{
	// 从运算符栈中取出一个运算符，从操作数栈中取出两个操作数，进行计算，计算结果压入操作数栈中
	// 操作数栈中取出的第一个栈顶元素是右操作数，第二个栈顶元素是左操作数
	// 若无法取出两个操作数，说明四则运算的表达式格式有误，终止计算

	char op;
	Pop(opStack, (ElemType*)(&op));
	if (numStack->p_base == numStack->p_top)
	{
		printf("Error: -- CalcExpression -- invalid expression.\n");
		exit(EXIT_FAILURE);
	}
	int right;
	Pop(numStack, (ElemType*)(&right));
	if (numStack->p_base == numStack->p_top)
	{
		printf("Error: -- CalcExpression -- invalid expression.\n");
		exit(EXIT_FAILURE);
	}
	int left;
	Pop(numStack, (ElemType*)(&left));

	int r = 0;
	switch (op)
	{
	case '+':
		r = left + right;
		break;
	case '-':
		r = left - right;
		break;
	case '*':
		r = left * right;
		break;
	case '/':
		r = left / right;
		break;
	default:
		printf("Error: -- CalcExpression -- invalid operator %c.\n", op);
		exit(EXIT_FAILURE);
	}
	Push(numStack, r);
}

int CalcExpression(char* p_exp)
{
	// 设立操作数栈、运算符栈
	SeqStack numStack;
	SeqStack opStack;
	InitSeqStack(&numStack);
	InitSeqStack(&opStack);

	// 从左到右遍历四则运算表达式，按规则进行入栈出栈
	char prec = '\0';
	char curc = '\0';
	while (*p_exp != '\0')
	{
		curc = *p_exp;

		// 数字进入操作数栈
		if (curc >= '0' && curc <= '9')
		{
			int n = curc - 48;

			// 上个字符也是数字，数明是连续的数字，比如 20
			// 需要先将上个数字出栈，同当前数字结合后再进栈
			if (prec >= '0' && prec <= '9')
			{
				int pren;
				Pop(&numStack, (ElemType*)(&pren));
				n = pren * 10 + n;
			}
			
			Push(&numStack, n);
		}
		// 运算符进入运算符栈
		else if (curc == '+' || curc == '-' || curc == '*' || curc == '/')
		{
			// 运算符栈顶已有元素，则比较当前运算符与栈顶运算符优先级：
			//	1. 若当前 > 栈顶，则当前运算符进栈；
			//	2. 若当前 <= 栈顶，则栈顶运算符及对应的操作数出栈进行计算，然后继续与下一个栈顶运算符进行比较，直至当前运算符进栈。
			char topc;
			GetTop(opStack, (ElemType*)(&topc));
			while (opStack.p_base < opStack.p_top && !IsHigher(curc, topc))
			{
				CalcTwoNum(&opStack, &numStack);
			}
			Push(&opStack, curc);
		}
		// 出现非法字符，终止运算
		else
		{
			printf("Error: -- CalcExpression -- expreesion with invalid char %c.\n", curc);
			exit(EXIT_FAILURE);
		}

		prec = curc;
		p_exp++;
	}

	// 计算结果
	while (opStack.p_base < opStack.p_top)
	{
		CalcTwoNum(&opStack, &numStack);
	}
	int rs;
	Pop(&numStack, (ElemType*)(&rs));
	return rs;
}
