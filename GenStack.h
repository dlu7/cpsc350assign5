#include <iostream>
using namespace std;

template<class T>
class GenStack
{
private:
	T* myArray;
	T* tArray;

	int max;
	int top;

public:
	GenStack(int size);
	~GenStack();

	void push(int data);
	T* peek();
	T* pop();

	int isEmpty();
	int isFull();
	int getSize();
};

template<class T>
GenStack<T>::GenStack(int size)
{
	max = size;
	top = -1;
	myArray = new T[size];
	tArray = new T[max];
}

template<class T>
GenStack<T>::~GenStack()
{
	delete[]myArray;
	delete[]tArray;
}

template<class T>
void GenStack<T>::push(int data)
{
	if (isFull() == 1)
		push(data);
	else
		myArray[++top] = data;
}

template<class T>
T* GenStack<T>::peek()
{
	if (top == -1)
	{
		//empty?
	}
	else
		return myArray[top];
}

template<class T>
T* GenStack<T>::pop()
{
	if (isEmpty() == 1)
		cout << "it's an empty stack" << endl;
	else
		return myArray[top--];
}

template<class T>
int GenStack<T>::isEmpty()
{
	return(top == -1);
}

template<class T>
int GenStack<T>::isFull()
{
	return(top == (max - 1));
}

template<class T>
int GenStack<T>::getSize()
{
	return (top + 1);
}