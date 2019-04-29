#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 10

enum { PREORDER, INORDER, POSTORDER };

typedef int DATA;

typedef struct NODE
{
	DATA data;
	struct NODE * left;
	struct NODE * right;
}NODE;

typedef struct HEAD
{
	struct NODE * target;
}HEAD;

HEAD * initHead(void);
void freeHead(HEAD * _head);
void insertNode(int n, HEAD * _head);
void printTree(HEAD * _head, int type);

// preorder
void printPreorder(HEAD * _head);
void preorder(NODE * node);

// inorder
void printInorder(HEAD * _head);
void inorder(NODE * node);

// postorder
void printPostorder(HEAD * _head);
void postorder(NODE * node);

int main(void)
{
	srand((unsigned)time(NULL));

	HEAD * head = initHead();

	int arr[MAX] = {0,}, i, j;

	printf("\n<insert tree>\n");

	for (i = 0; i < MAX; i++)
	{
		int n = rand() % MAX;

		if (arr[n] == 0)
		{
			arr[n] = 1;
			insertNode(n + 1, head);
		}
		else
		{
			j = n;
			while (1)
			{
				n = (n + 1) % MAX;
				if (arr[n] == 0)
				{
					arr[n] = 1;
					insertNode(n + 1, head);
					break;
				}
			}
		}

		printf("%d  ", n + 1);
	}

	printf("\n");

	printTree(head, PREORDER);

	printTree(head, INORDER);

	printTree(head, POSTORDER);

	freeHead(head);

	return 0;
}

HEAD * initHead(void)
{
	HEAD * head = (HEAD *)malloc(sizeof(HEAD));
	head->target = NULL;

	return head;
}
void freeHead(HEAD * _head)
{
	free(_head);
}
void insertNode(int n, HEAD * _head)
{
	NODE * node = (NODE*)malloc(sizeof(NODE));
	node->data = n;
	node->left = NULL;
	node->right = NULL;


	if (_head->target == NULL)
		_head->target = node;
	else
	{
		NODE * tmp = _head->target;

		while (tmp != NULL)
		{
			if (node->data > tmp->data)
			{
				if (tmp->right == NULL)
				{
					tmp->right = node;
					break;
				}
				else
					tmp = tmp->right;
			}
			else
			{
				if (tmp->left == NULL)
				{
					tmp->left = node;
					break;
				}
				else
					tmp = tmp->left;
			}
		}
	}
}
void printTree(HEAD * _head, int type)
{
	switch (type)
	{
	case PREORDER:
		printPreorder(_head);
		break;
	case INORDER:
		printInorder(_head);
		break;
	case POSTORDER:
	default:
		printPostorder(_head);
	}
}

// preorder
void printPreorder(HEAD * _head)
{
	if (_head->target == NULL)
	{
		printf("TREE IS EMPTY\n");
		return;
	}

	printf("\n<print by preorder traversal>\n");
	
	preorder(_head->target);

	printf("\n");
}
void preorder(NODE * node)
{
	if (node == NULL) return;

	printf("%d  ", node->data);

	preorder(node->left);
	
	preorder(node->right);
}

// inorder
void printInorder(HEAD * _head)
{
	if (_head->target == NULL)
	{
		printf("TREE IS EMPTY\n");
		return;
	}

	printf("\n<print by inorder traversal>\n");

	inorder(_head->target);

	printf("\n");
}
void inorder(NODE * node)
{
	if (node == NULL) return;

	inorder(node->left);

	printf("%d  ", node->data);

	inorder(node->right);
}

// postorder
void printPostorder(HEAD * _head)
{
	if (_head->target == NULL)
	{
		printf("TREE IS EMPTY\n");
		return;
	}

	printf("\n<print by postorder traversal>\n");
	
	postorder(_head->target);

	printf("\n");
}
void postorder(NODE * node)
{
	if (node == NULL) return;

	postorder(node->left);

	postorder(node->right);

	printf("%d  ", node->data);
}