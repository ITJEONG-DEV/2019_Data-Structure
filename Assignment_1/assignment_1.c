#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** initMatrix(int _row, int _column);
void freeMatrix(int** _matrix, int _row, int _column);
void printMatrix(int** _matrix, int _row, int _column);
int** matrixMultiplication(int** _A, int** _B, int _a, int _b, int _c);

int main(int argc, char* argv[])
{
	srand(time(NULL));

	int a, b, c;

	if(argc<4)
	{
		printf("Terminated due to error.");
		printf(" Should enter each a, b, c value.\n");
		return;
	}

	a = atoi(*(argv+1));
	if(a<1)
	{
		printf("Terminated due to error.");
		printf(" a < 1\n");
		return;
	}

	b = atoi(*(argv+2));
	if(b<1)
	{
		printf("Terminated due to error.");
		printf(" b < 1\n");
		return;
	}

	c = atoi(*(argv+3));
	if(c<1)
	{
		printf("Terminated due to error.");
		printf(" c < 1\n");
		return;
	}

	int** M = initMatrix(a, b);
	int** N = initMatrix(b, c);

	printMatrix(M, a, b);
	printMatrix(N, b, c);

	int** L = matrixMultiplication(M, N, a, b, c);

	printMatrix(L, a, c);

	freeMatrix(M, a, b);
	freeMatrix(N, b, c);
	freeMatrix(L, a, c);

	return 0;
}

int** initMatrix(int _row, int _column)
{
	int** matrix = (int**)malloc(sizeof(int*)*_row);

	int row, column;

	for(row=0; row<_row; row++)
	{
		*(matrix+row) = (int*)malloc(sizeof(int)*_column);

		for(column=0; column<_column; column++)
		{
			*(*(matrix+row)+column) = rand()%10000+1;
		}
	}

	return matrix;
}

void freeMatrix(int** _matrix, int _row, int _column)
{
	int row;

	for(row=0; row<_row; row++)
		free(*(_matrix+row));

	free(_matrix);
}

void printMatrix(int** _matrix, int _row, int _column)
{
	int row, column;

	printf("\n<%d X %d Matrix>\n", _row, _column);

	for(row=0; row<_row; row++)
	{
		printf(" | ");
		for(column=0; column<_column; column++)
		{
			printf("%10d ", *(*(_matrix+row)+column));
		}
		printf(" |\n");
	}
}

int** matrixMultiplication(int** _A, int** _B, int _a, int _b, int _c)
{
	int** matrix = initMatrix(_a, _c);

	int row, column, i, value;

	for(row=0; row<_a; row++)
	{
		for(column=0; column<_c; column++)
		{
			value=0;

			for(i=0; i<_b; i++)
				value += (*(*(_A+row)+i)) * (*(*(_B+i)+column));

		*(*(matrix+row)+column) = value;
		}
	}

	return matrix;
}


