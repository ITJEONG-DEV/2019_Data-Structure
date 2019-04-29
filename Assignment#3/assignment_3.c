#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 10*2+4
#define MAX_OPTION 2

typedef struct NODE
{
	char str[MAX_LEN];
	struct NODE *next;
}NODE;

typedef struct HEAD
{
	struct NODE *next;
}HEAD;

// make stack name
int GetNumberofDigits(int n);
char* IntToString(int _n);
char* MakeStackName(int _stackNumber, int _stackCount);

// stack
void push(HEAD * head_ptr, HEAD ** barrier, int * currentStackCount, int stackNum, int numofStack, int sizeofStack);
void pop(HEAD * head_ptr, HEAD ** barrier, int * currentStackCount, int stackNum, int numofStack, int sizeofStack);

// print
int print(HEAD * head_ptr);
void printBarrier(HEAD * heat_ptr, HEAD ** barrier, int numofStack);
void printNodeNum(int * currentStackCount, int numofStack);

int main(int argc, char * argv[])
{
	HEAD * head_ptr;
	HEAD ** barrier;
	int * currentStackCount;
	int numofStack, sizeofStack;
	char tmpChar[MAX_LEN];
	int i;

	srand(time(NULL));

	// scan value
	if (argc < 3)
	{
		printf("less argv.\n");
		return 0;
	}

	numofStack = atoi(argv[1]);
	if (numofStack < 1)
	{
		printf("numofStack < 1\n");
		return 0;
	}

	sizeofStack = atoi(argv[2]);
	if (sizeofStack < 0)
	{
		printf("sizeofstack <0\n");
		return 0;
	}

	// init
	currentStackCount = (int*)calloc(numofStack, sizeof(int));

	head_ptr = (HEAD*)malloc(sizeof(HEAD));
	head_ptr->next = NULL;

	barrier = (HEAD**)malloc(sizeof(HEAD*)*numofStack);
	for (i = 0; i < numofStack; i++)
	{
		barrier[i] = (HEAD*)malloc(sizeof(HEAD));
		barrier[i]->next = NULL;
	}

	// loop
	for (i = 0; i < sizeofStack * 4; i++)
	{
		int selected_st_number = rand() % numofStack;
		int selected_op_number = rand() % MAX_OPTION + 1;

		printf("[%2d] %s : stack %d\n", i + 1, selected_op_number == 1 ? "push" : "pop", selected_st_number + 1);

		if (selected_op_number == 1)
			push(&*head_ptr, &*barrier, &*currentStackCount, selected_st_number, numofStack, sizeofStack);

		else
			pop(&*head_ptr, &*barrier, &*currentStackCount, selected_st_number, numofStack, sizeofStack);

		//print(head_ptr);
		//printBarrier(head_ptr, barrier, numofStack);
		//printNodeNum(currentStackCount, numofStack);
	}

	print(head_ptr);

	// free
	free(head_ptr);
	for (i = 0; i < numofStack; i++)
	{
		free(barrier[i]);
	}
	free(barrier);

	free(currentStackCount);

	return 0;
}

// make stack name
int GetNumberofDigits(int n)
{
	int len = 1;

	while (1)
	{
		n /= 10;

		if (n == 0) break;
		else len++;
	}
	return len;
}
char* IntToString(int _n)
{
	int i, length = GetNumberofDigits(_n) + 2;
	char * str = (char*)malloc(sizeof(char)*length);

	for (i = length; i > 0; i--)
	{

		if (i == length)
		{
			str[i - 1] = '\0';
			continue;
		}
		str[i - 1] = (char)(_n % 10 + '0');
		_n /= 10;

	}

	return str;
}
char* MakeStackName(int _stackNumber, int _stackCount)
{
	char * stackNumber = IntToString(_stackNumber + 1);
	char * stackCount = IntToString(_stackCount + 1);

	//printf("stacknumber : %s   stackcount : %s   ", stackNumber, stackCount);
	//printf("len number : %d   len count : %d\n", strlen(stackNumber), strlen(stackCount));

	int i, length = strlen(stackNumber) + strlen(stackCount) + 4;

	char * str = (char*)malloc(sizeof(char)*length);

	for (i = 0; i < length; i++)
	{
		if (i == 0)
			str[i] = 's';
		else if (i == 1)
			str[i] = 't';
		else if (i >= 2 && i < strlen(stackNumber) + 2)
			str[i] = stackNumber[i - 2];
		else if (i == strlen(stackNumber) + 2)
			str[i] = '_';
		else
			str[i] = stackCount[i - strlen(stackNumber) - 3];
	}

	//printf("%s", str);

	return str;
}

// stack
void push(HEAD * head_ptr, HEAD ** barrier, int * currentStackCount, int stackNum, int numofStack, int sizeofStack)
{
	// check overflow
	int currentSumofStack = 0, i;
	for (i = 0; i < numofStack; i++)
		currentSumofStack += currentStackCount[i];
	if (currentSumofStack == sizeofStack)
	{
		printf("\n[notice] stack overflow\n\n");
		return;
	}

	// init node
	NODE* node = (NODE*)malloc(sizeof(NODE));
	strcpy(node->str, MakeStackName(stackNum, currentStackCount[stackNum]));

	if (head_ptr->next == NULL)
	{
		head_ptr->next = node;
		node->next = NULL;
	}
	else
	{
		if (stackNum == 0)
		{
			node->next = head_ptr->next;
			head_ptr->next = node;
		}
		else
		{
			NODE * tmp = barrier[stackNum - 1]->next;

			if (tmp == NULL)
			{
				node->next = head_ptr->next;
				head_ptr->next = node;
			}
			else
			{
				if (tmp->next == NULL) node->next = NULL;
				else node->next = tmp->next;
				tmp->next = node;
			}
		}
	}

	for (i = stackNum; i < numofStack; i++)
	{
		if (currentStackCount[i] == 0)
			barrier[i]->next = node;
		else break;
	}
	currentStackCount[stackNum]++;

	return;
}
void pop(HEAD * head_ptr, HEAD ** barrier, int * currentStackCount, int stackNum, int numofStack, int sizeofStack)
{
	int i;
	char tmpChar[MAX_LEN];
	NODE * node;

	// check null
	if (currentStackCount[stackNum] == 0)
	{
		printf("\n[notice] %d%s stack is empty.\n\n", stackNum + 1, stackNum == 0 ? "st" : (stackNum == 1 ? "nd" : "th"));
		return;
	}

	if (stackNum == 0)
	{
		node = head_ptr->next;

		if (node->next == NULL) // total number of node = 1
			head_ptr->next = NULL;
		else
			head_ptr->next = node->next;
	}
	else
	{
		// you have to edit this part
		NODE * tmp;
		if (barrier[stackNum - 1]->next == NULL)
		{
			node = head_ptr->next;
			head_ptr->next = node->next;
		}
		else
		{
			tmp = barrier[stackNum - 1]->next;
			node = tmp->next;

			if (node->next == NULL) // the end of the node
				tmp->next = NULL;
			else
				tmp->next = node->next;
		}
	}

	strcpy(tmpChar, node->str);

	free(node);
	currentStackCount[stackNum]--;

	for (i = stackNum; i < numofStack; i++)
		if (currentStackCount[i] == 0 && stackNum == 0) barrier[i]->next = NULL;
		else if (currentStackCount[i] == 0) barrier[i]->next = barrier[i - 1]->next;
		else break;

}

// print
int print(HEAD * head_ptr)
{
	NODE* node = head_ptr->next;

	printf("\n<print stack>\n");

	if (node == NULL)
	{
		printf("empty\n\n");
	}
	else
	{
		while (1)
		{
			printf("%s\n", node->str);

			if (node->next == NULL) break;
			else node = node->next;
		}

		printf("\n");
	}
}
void printBarrier(HEAD * heat_ptr, HEAD ** barrier, int numofStack)
{
	int i;
	for (i = 0; i < numofStack; i++)
	{
		if (barrier[i]->next == NULL)
		{
			printf("barrier[%d] : head_ptr\n", i + 1);
		}
		else printf("barrier[%d] : %s\n", i + 1, barrier[i]->next->str);
	}

	printf("\n");
}
void printNodeNum(int * currentStackCount, int numofStack)
{
	int i;
	for (i = 0; i < numofStack; i++)
	{
		printf("stack %d : %d\n", i + 1, currentStackCount[i]);
	}

	printf("\n");
}
