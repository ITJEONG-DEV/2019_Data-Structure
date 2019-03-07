#include "LinearList.h"

List::List()
{
	initializeArray(0);
}

void List::initializeArray(int _length)
{
	_array = (int*)malloc(sizeof(int)*_length);
}

int List::getLength()
{
	if (!_array) return 0;

	int _length = _msize(_array) / sizeof(int);

	return _length;
}

void List::changeArraySize(int _changed)
{
	int _length = getLength();

	_array = (int*)realloc(_array, sizeof(int)*(_length + _changed));
}

void List::insertValue(int _index, int _value)
{
	int _length = getLength();

	changeArraySize(1);

	for (int i = _length; i > _index; i--)
	{
		_array[i] = _array[i - 1];
	}
}

void List::addValue(int _value)
{
	int _length = getLength();

	changeArraySize(1);

	_array[_length] = _value;
}

void List::printArray()
{
	int _length = getLength();

	for (int i = 0; i < _length; i++)
		printf("%d : %d\b", i + 1, _array[i]);

	printf("\n\n");
}

int main(void)
{
}