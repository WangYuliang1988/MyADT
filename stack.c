#include "stack.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// ����˳��ջ��������
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
	p_seq_stack->p_top = p_seq_stack->p_base; // ��ʼ��ʱ��base �� p_top ָ��ͬһ���ַ
	p_seq_stack->stack_size = SEQ_INIT_SIZE;
}

void Push(SeqStack* p_seq_stack, ElemType elem)
{
	long long length = p_seq_stack->p_top - p_seq_stack->p_base;

	// �жϵ�ǰ�Ƿ�ջ�������ǣ�����չջ�Ŀռ�
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

	// ��Ԫ����ջ��ע�� p_top ʼ��ָ��ջ��Ԫ�ص���һλ��
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
// �������ջ���㷨Ӧ��
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
			// ��ջ�ѿգ���ƥ��
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

	// ����ʱջΪ�ձ�ʾƥ�䣬��Ϊ�ձ�ʾ��ƥ��
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
* �ж� opLeft �����ȼ��Ƿ���� opRight
* 
* �ú����� CalcExpression() �ĸ�������
* 
* ������������ȼ���[* == /] > [+ == -]
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
* ��ȡ�������ֵ�����������
* 
* �ú����� CalcExpression() �ĸ�������
*/
void CalcTwoNum(SeqStack* opStack, SeqStack* numStack)
{
	// �������ջ��ȡ��һ����������Ӳ�����ջ��ȡ�����������������м��㣬������ѹ�������ջ��
	// ������ջ��ȡ���ĵ�һ��ջ��Ԫ�����Ҳ��������ڶ���ջ��Ԫ�����������
	// ���޷�ȡ��������������˵����������ı��ʽ��ʽ������ֹ����

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
	// ����������ջ�������ջ
	SeqStack numStack;
	SeqStack opStack;
	InitSeqStack(&numStack);
	InitSeqStack(&opStack);

	// �����ұ�������������ʽ�������������ջ��ջ
	char prec = '\0';
	char curc = '\0';
	while (*p_exp != '\0')
	{
		curc = *p_exp;

		// ���ֽ��������ջ
		if (curc >= '0' && curc <= '9')
		{
			int n = curc - 48;

			// �ϸ��ַ�Ҳ�����֣����������������֣����� 20
			// ��Ҫ�Ƚ��ϸ����ֳ�ջ��ͬ��ǰ���ֽ�Ϻ��ٽ�ջ
			if (prec >= '0' && prec <= '9')
			{
				int pren;
				Pop(&numStack, (ElemType*)(&pren));
				n = pren * 10 + n;
			}
			
			Push(&numStack, n);
		}
		// ��������������ջ
		else if (curc == '+' || curc == '-' || curc == '*' || curc == '/')
		{
			// �����ջ������Ԫ�أ���Ƚϵ�ǰ�������ջ����������ȼ���
			//	1. ����ǰ > ջ������ǰ�������ջ��
			//	2. ����ǰ <= ջ������ջ�����������Ӧ�Ĳ�������ջ���м��㣬Ȼ���������һ��ջ����������бȽϣ�ֱ����ǰ�������ջ��
			char topc;
			GetTop(opStack, (ElemType*)(&topc));
			while (opStack.p_base < opStack.p_top && !IsHigher(curc, topc))
			{
				CalcTwoNum(&opStack, &numStack);
			}
			Push(&opStack, curc);
		}
		// ���ַǷ��ַ�����ֹ����
		else
		{
			printf("Error: -- CalcExpression -- expreesion with invalid char %c.\n", curc);
			exit(EXIT_FAILURE);
		}

		prec = curc;
		p_exp++;
	}

	// ������
	while (opStack.p_base < opStack.p_top)
	{
		CalcTwoNum(&opStack, &numStack);
	}
	int rs;
	Pop(&numStack, (ElemType*)(&rs));
	return rs;
}
