#include<iostream>
#define SIZE 100
using namespace std;
template<class X>
class Stack
{
public:
	X arr[SIZE];
	int top = -1;
	int length = 0;
	bool isEmpty()
	{
		if (top < 0)
		{
			return true;
		}
		else
			return false;
	}
	bool isFull()
	{
		if (top == SIZE - 1)
		{
			return true;
		}
		else
			return false;
	}
	void Push(X element)
	{
		if (!isFull())
		{
			arr[++top] = element;
			length++;
		}
		else
			cout << "Array is Full" << endl;
	}
	X Pop()
	{
		X data;
		if (!isEmpty())
		{
			data = arr[top--];
			length--;
			return data;
		}
		else
		{
			cout << "Array is Empty " << endl;
		}
	}
	X peek()
	{
		if (!isEmpty())
		{
			return arr[top];
		}
		else
		{
			cout << "Array is Empty " << endl;
		}
	}
	void clear()
	{
		while (!isEmpty())
		{
			Pop();
		}
	}
};