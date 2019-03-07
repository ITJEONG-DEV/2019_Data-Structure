#pragma once
#include <stdio.h>
#include <stdlib.h>

class List
{
private:
	int* _array;
	List();
	void initializeArray(int _length);
	void changeArraySize(int _changed);
public:
	int getLength();
	void insertValue(int _index, int _value);
	void addValue(int _value);
	void printArray();
};
