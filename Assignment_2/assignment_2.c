#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Term // term
{
	int coefficient;
	int degree;
	struct Term *next;
} Term;

typedef struct TermHead // head
{
	struct Term *next;
} TermHead;

enum ScanPhase // scan phase
{
	NONE = 0, BEGIN, COEFFICIENT, DEGREE, END
};

TermHead *CreateTermHead(void);// create term head
void AddTerm(TermHead *_head, int _coefficient, int _degree);// add term (if same degree exist, add coefficient)
void PrintPolynomial(TermHead *_head); // print polynomial
TermHead *ReadPolynomial(void);// read char until char == ')'
TermHead *MultiplicationPolynomial(TermHead *_A, TermHead *_B);
void DeletePolynomial(TermHead *_head); // free

int main(void)
{
	TermHead *A = NULL, *B = NULL;

	printf("? ");
	A = ReadPolynomial();

	char tempChar;

	while (1)
	{
		scanf("%1c", &tempChar);
		
		if (tempChar == '*')
		{
			if (B != NULL) { DeletePolynomial(B); }
			B = ReadPolynomial();
			TermHead *C = MultiplicationPolynomial(A, B);
			DeletePolynomial(A);
			A = C;
		}
		else
		{
			break;
		}
	}

	PrintPolynomial(A);

	DeletePolynomial(A);
	if (B != NULL) DeletePolynomial(B);
	return 0;
}

TermHead *CreateTermHead(void)
{
	TermHead *termHead = (TermHead*)malloc(sizeof(TermHead));

	termHead->next = NULL;

	return termHead;
}

void AddTerm(TermHead *_head, int _coefficient, int _degree)
{
	Term *newTerm = (Term*)malloc(sizeof(Term));

	newTerm->coefficient = _coefficient;
	newTerm->degree = _degree;
	newTerm->next = NULL;

	Term *now = _head->next;

	if (now == NULL)
	{
		_head->next = newTerm;
		newTerm->next = NULL;

	}
	else if (now->degree < newTerm->degree)
	{
		_head->next = newTerm;
		newTerm->next = now;
	}
	else if (now->degree == newTerm->degree)
	{
		now->coefficient += newTerm->coefficient;
		free(newTerm);
	}
	else
	{
		while (1)
		{
			//printf("now : coefficient : %d   degree : %d\n", now->coefficient, now->degree);
			//printf("new : coefficient : %d   degree : %d\n", _coefficient, _degree);
			if (now->next == NULL)
			{
				now->next = newTerm;
				break;
			}
			else if (now->next->degree < newTerm->degree)
			{
				newTerm->next = now->next;
				now->next = newTerm;
				break;
			}
			else if (now->next->degree == newTerm->degree)
			{
				now->next->coefficient += newTerm->coefficient;
				free(newTerm);
				break;
			}

			now = now->next;
		}
	}
	
}

void PrintPolynomial(TermHead *_head)
{
	Term *now = _head->next;
	int isStart = 0;

	//printf("\n<print polynomial>\n\n");
	printf("=");
	if (now == NULL)
	{
		printf("0\n");
	}
	else
	{
		while (1)
		{
			// + sign
			if (isStart && now->coefficient > 0) printf("+");
			else isStart = 1;

			// coefficient
			if (now->coefficient != 1 || now->coefficient == 1 && now->degree == 0)
				printf("%d", now->coefficient);

			// degree
			if (now->degree == 1)
				printf("x");
			else if (now->degree != 0)
				printf("x^%d", now->degree);
			
			if (now->next == NULL)
			{
				printf("\n");
				break;
			}

			now = now->next;
		}
	}
}

TermHead *ReadPolynomial(void)
{
	TermHead *head = CreateTermHead();

	// reading state
	int readingState = NONE;

	// variable for add term
	int coefficient = 0;
	int degree = 0;

	// temp variable for reading
	char tempChar;
	int tempSign;
	int tempNumber;

	while (1)
	{
		if (readingState == END) break;

		scanf("%1c", &tempChar);

		switch (tempChar)
		{
		case '(':
			tempSign = 1;
			tempNumber = 0;
			readingState = BEGIN;
			break;
		case ')':
			if (readingState == DEGREE) // ( ... + x^3)
			{
				degree = tempNumber * tempSign;
				AddTerm(head, coefficient, degree);
			}
			else if (readingState == COEFFICIENT) // ( ... + 3)
			{
				coefficient = tempNumber * tempSign;
				AddTerm(head, coefficient, 0);
			}

			readingState = END;
			break;
		case '-':
			if (readingState == BEGIN) readingState = COEFFICIENT;
			else if (readingState == COEFFICIENT) // 1 - 3x
			{
				coefficient = tempNumber * tempSign;
				
				readingState = DEGREE;
			}
			else if (readingState == DEGREE) // x^3 - 5
			{
				degree = tempNumber * tempSign;
				AddTerm(head, coefficient, degree);

				readingState = COEFFICIENT;
			}

			tempNumber = 0;
			tempSign = -1;
			break;
		case '+':
			if (readingState == BEGIN) readingState = COEFFICIENT;
			else if (readingState == COEFFICIENT) // 1 + 3x
			{
				coefficient = tempNumber * tempSign;

				readingState = DEGREE;
			}
			else if (readingState == DEGREE) // x^3 + 5
			{
				degree = tempNumber * tempSign;
				AddTerm(head, coefficient, degree);

				readingState = COEFFICIENT;
			}

			tempNumber = 0;
			tempSign = 1;
			break;
		case 'X':
		case 'x':
			coefficient = tempNumber == 0 ? 1 : tempNumber * tempSign; // coefficient of x = 1
			tempNumber = 1; // degree of x >= 1
			tempSign = 1;

			readingState = DEGREE;
			break;
		case '^':
			tempNumber = 0;
			break;
		default:
			if (tempChar >= '0' && tempChar <= '9')
			{
				if (readingState == BEGIN) readingState = COEFFICIENT;
				tempNumber *= 10;
				tempNumber += tempChar - '0';
			}
			break;

		}
	}

	return head;
}

TermHead *MultiplicationPolynomial(TermHead *_A, TermHead *_B)
{
	if (_A == NULL || _B == NULL) return NULL;

	TermHead * head = CreateTermHead();

	Term * A = _A->next, *B;
	while (A != NULL)
	{
		B = _B->next;
		while (B != NULL)
		{
			AddTerm(head, A->coefficient*B->coefficient, A->degree + B->degree);

			B = B->next;
		}
		A = A->next;
	}

	return head;
}

void DeletePolynomial(TermHead *_head)
{
	Term *now = _head->next;
	free(_head);

	if(now!=NULL)
		while (1)
		{
			if (now->next == NULL)
			{
				free(now);
				break;
			}
			Term * tmp = now;
			now = now->next;
			free(tmp);
		}
}