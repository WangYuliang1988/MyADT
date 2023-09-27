#include "stack.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// ����˳��ջ��������
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void InitSeqStack(SeqStack* p_seq_stack)
{
	p_seq_stack->base = (ElemType*)malloc(sizeof(ElemType) * SEQ_INIT_SIZE);
	if (p_seq_stack->base == NULL)
	{
		printf("Error: -- InitSeqStack -- fail to alloc memory.\n");
		exit(EXIT_FAILURE);
	}
	p_seq_stack->top = p_seq_stack->base; // ��ʼ��ʱ��base �� top ָ��ͬһ���ַ
	p_seq_stack->stack_size = SEQ_INIT_SIZE;
}

void Push(SeqStack* p_seq_stack, ElemType elem)
{
	long long length = p_seq_stack->top - p_seq_stack->base;

	// �жϵ�ǰ�Ƿ�ջ�������ǣ�����չջ�Ŀռ�
	if (length == p_seq_stack->stack_size)
	{
		ElemType* nbase = (ElemType*)realloc(p_seq_stack->base, sizeof(ElemType) * (p_seq_stack->stack_size + SEQ_INCREAMENT));
		if (nbase == NULL)
		{
			printf("Error: -- Push -- fail to realloc memory.\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			p_seq_stack->base = nbase;
			p_seq_stack->top = nbase + length;
			p_seq_stack->stack_size += SEQ_INCREAMENT;
		}
	}

	// ��Ԫ����ջ��ע�� top ʼ��ָ��ջ��Ԫ�ص���һλ��
	*(p_seq_stack->top) = elem;
	p_seq_stack->top += 1;
}

ElemType Pop(SeqStack* p_seq_stack)
{
	if (p_seq_stack->top == p_seq_stack->base)
	{
		printf("Error: -- Pop -- stack is empty.\n");
		exit(EXIT_FAILURE);
	}

	p_seq_stack->top -= 1;
	return *(p_seq_stack->top);
}

void DestroySeqStack(SeqStack* p_seq_stack)
{
	if (p_seq_stack != NULL)
	{
		free(p_seq_stack->base);
		p_seq_stack->base = NULL;
		p_seq_stack->top = NULL;
		p_seq_stack->stack_size = 0;
	}
}

ElemType GetTop(SeqStack seq_stack)
{
	if (seq_stack.top == seq_stack.base)
	{
		printf("Error: -- Pop -- stack is empty.\n");
		exit(EXIT_FAILURE);
	}

	return *(seq_stack.top - 1);
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

	while (stack.top > stack.base)
	{
		ElemType i = Pop(&stack);
		if (i < 10)
		{
			printf("%d", i);
		}
		else
		{
			printf("%c", i + 55);
		}
	}

	DestroySeqStack(&stack);
}

int MatchBracket(char* exp)
{
	SeqStack stack;
	InitSeqStack(&stack);

	while (*exp != '\0')
	{
		char c = *exp;

		if (c == '(' || c == '[' || c == '{')
		{
			Push(&stack, c);
		}
		else if (c == ')' || c == ']' || c == '}')
		{
			// ��ջ�ѿգ���ƥ��
			if (stack.top == stack.base)
			{
				return 0;
			}
			else {
				char top = GetTop(stack);

				if ((top == '(' && c == ')') || (top == '[' && c == ']') || (top == '{' && c == '}'))
				{
					Pop(&stack);
				}
				else {
					return 0;
				}
			}
		}

		exp++;
	}

	// ����ʱջΪ�ձ�ʾƥ�䣬��Ϊ�ձ�ʾ��ƥ��
	if (stack.top == stack.base)
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

	char op = Pop(opStack);
	if (numStack->base == numStack->top)
	{
		printf("Error: -- CalcExpression -- invalid expression.\n");
		exit(EXIT_FAILURE);
	}
	int right = Pop(numStack);
	if (numStack->base == numStack->top)
	{
		printf("Error: -- CalcExpression -- invalid expression.\n");
		exit(EXIT_FAILURE);
	}
	int left = Pop(numStack);

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

int CalcExpression(char* exp)
{
	// ����������ջ�������ջ
	SeqStack numStack;
	SeqStack opStack;
	InitSeqStack(&numStack);
	InitSeqStack(&opStack);

	// �����ұ�������������ʽ�������������ջ��ջ
	char prec = '\0';
	char curc = '\0';
	while (*exp != '\0')
	{
		curc = *exp;

		// ���ֽ��������ջ
		if (curc >= '0' && curc <= '9')
		{
			int n = curc - 48;

			// �ϸ��ַ�Ҳ�����֣����������������֣����� 20
			// ��Ҫ�Ƚ��ϸ����ֳ�ջ��ͬ��ǰ���ֽ�Ϻ��ٽ�ջ
			if (prec >= '0' && prec <= '9')
			{
				int pren = Pop(&numStack);
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
			while (opStack.base < opStack.top && !IsHigher(curc, GetTop(opStack)))
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
		exp++;
	}

	// ������
	while (opStack.base < opStack.top)
	{
		CalcTwoNum(&opStack, &numStack);
	}
	return Pop(&numStack);
}
