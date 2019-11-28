#include <iostream>
using namespace std;

template <class T>
class ListNode
{
public:
	T data;
	ListNode<T> *next;
	ListNode<T> *prev;

	ListNode();
	ListNode(T d);
	~ListNode();
};

template <class T>
ListNode<T>::ListNode()
{
	next = NULL;
	prev = NULL;
}

template <class T>
ListNode<T>::ListNode(T d)
{
	data = d;
	next = NULL;
	prev = NULL;
}

template <class T>
ListNode<T>::~ListNode()
{
	if (next != NULL)
	{
		next = NULL;
		prev = NULL;

		delete next;
		delete prev;
	}
}

template <class T>
class DoubleLinkedList
{
public:
	ListNode<T> *front;
	ListNode<T> *back;
	unsigned int size;

	DoubleLinkedList();
	~DoubleLinkedList();

	void insertBack(T d);

	T removeFront();
	void deletePosition(int p);

	T peekFront();
	T peekBack();

	void printList();
	bool isEmpty();
	unsigned int getSize();
};

template <class T>
DoubleLinkedList<T>::DoubleLinkedList()
{
	front = NULL;
	back = NULL;
	size = 0;
}

template <class T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
	delete front;
	delete back;
}

template <class T>
void DoubleLinkedList<T>::insertBack(T d)
{
	ListNode<T> *node = new ListNode<T>(d);

	//if it's empty
	if (size == 0)
	{
		front = node;
	}
	//else if it's not empty
	else
	{
		back->next = node;
		node->prev = back;
	}

	back = node;
	size++;
}

template <class T>
T DoubleLinkedList<T>::removeFront()
{
	if (!isEmpty())
	{
		ListNode<T> *node = front;

		//if it's the only node
		if (front->next == NULL)
		{
			back = NULL;
		}
		//else if there is more than one node
		else
		{
			front->next->prev = NULL;
			front = front->next;
		}

		T node2 = node->data;

		node->next = NULL;
		delete node;
		size--;

		return node2;
	}
	else
	{
		return T();
	}
}

template <class T>
void DoubleLinkedList<T>::deletePosition(int p)
{
	int index = 0;

	ListNode<T> *curr = front;
	ListNode<T> *prev = front;

	while (index != p)
	{
		prev = curr;
		curr = curr->next;
		index++;
	}

	prev->next = curr->next;
	curr->next->prev = prev;
	curr->next = NULL;
	curr->prev = NULL;

	size--;
	delete curr;
}

template <class T>
T DoubleLinkedList<T>::peekFront()
{
	return front->data;
}

template <class T>
T DoubleLinkedList<T>::peekBack()
{
	return back->data;
}

template <class T>
void DoubleLinkedList<T>::printList()
{
	if (front == NULL)
	{
		cout << "There is nothing to print." << endl;
	}

	ListNode<T> *curr = front;

	while (true)
	{
		if (curr == NULL)
		{
			break;
		}

		cout << curr->data << ", ";
		curr = curr->next;
	}
}

template <class T>
bool DoubleLinkedList<T>::isEmpty()
{
	return (size == 0);
}

template <class T>
unsigned int DoubleLinkedList<T>::getSize()
{
	return size;
}

