#include <iostream>
#include "Student.h"
#include "Faculty.h"
using namespace std;

template <class T>
class TreeNode
{
public:
	int key;
	T* data;
	TreeNode<T> *left;
	TreeNode<T> *right;

	TreeNode();
	TreeNode(T* d, int k);
	~TreeNode();
};

template <class T>
TreeNode<T>::TreeNode()
{
	key = -1;
	data = T();
	left = NULL;
	right = NULL;
}

template <class T>
TreeNode<T>::TreeNode(T* d, int k)
{
	key = k;
	data = d;
	left = NULL;
	right = NULL;
}

template <class T>
TreeNode<T>::~TreeNode()
{
	delete data;
	delete left;
	delete right;
}

// -------- BINARY SEARCH TREE ---------- //
template <class T>
class BST
{
private:
	TreeNode<T> *root;
	int size;
public:
	BST();
	~BST();

	bool inside(int s);
	T* search(int s);
	void insert(TreeNode<T> *node);

	TreeNode<T>* getSuccessor(TreeNode<T> *s);
	bool remove(int s);

	void print(TreeNode<T> *node);
	void printTree();

	TreeNode<T>* getRoot();
	int getSize();
	bool isEmpty();
};

template <class T>
BST<T>::BST()
{
	root = NULL;
	size = 0;
}

template <class T>
BST<T>::~BST()
{

}

template <class T>
bool BST<T>::inside(int s)
{
	if (root == NULL)
		return false;

	TreeNode<T> *curr = root;

	while (curr->key != s)
	{
		//looking for node in left side
		if (s < curr->key)
			curr = curr->left;
		//looking in right side
		else
			curr = curr->right;

		//node isn't here
		if (curr == NULL)
			return false;
	}
	return true;

}

template <class T>
T* BST<T>::search(int s)
{
	if (inside(s))
	{
		TreeNode<T> *curr = root;

		while (curr->key != s)
		{
			//looking for node in left side
			if (s < curr->key)
				curr = curr->left;
			//looking in right side
			else
				curr = curr->right;
		}

		return curr->data;
	}
	else
		return NULL;
}

template <class T>
void BST<T>::insert(TreeNode<T> *node)
{
	if (root == NULL)
		root = node;
	else
	{
		TreeNode<T> *curr = root;
		TreeNode<T> *parent;

		while (true)
		{
			parent = curr;

			if (node->key < curr->key)
			{
				curr = curr->left;

				if (curr == NULL)
				{
					parent->left = node;
					break;
				}
			}
			else
			{
				curr = curr->right;

				if (curr == NULL)
				{
					parent->right = node;
					break;
				}
			}
		}
	}
	size++;
}

template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *s)
{
	TreeNode<T> *psuccessor = s;
	TreeNode<T> *successor = s;
	TreeNode<T> *curr = s->right;

	while (curr != NULL)
	{
		psuccessor = successor;
		successor = curr;
		curr = curr->left;
	}

	if (successor != s->right)
	{
		psuccessor->left = successor->right;
		successor->right = s->right;
	}

	return successor;
}

template <class T>
bool BST<T>::remove(int s)
{
	if (root == NULL)
		return false;

	TreeNode<T> *curr = root;
	TreeNode<T> *parent = root;
	bool isLeft = true;

	while (curr->key != s)
	{
		parent = curr;

		if (s < curr->key)
		{
			isLeft = true;
			curr = curr->left;
		}
		else
		{
			isLeft = false;
			curr = curr->right;
		}

		if (curr == NULL)
			return false;

		if (curr->left == NULL && curr->right == NULL)
		{
			if (curr == root)
				root == NULL;
			else if (isLeft)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else if (curr->right == NULL)
		{
			if (curr == root)
				root = curr->left;
			else if (isLeft)
				parent->left = curr->left;
			else
				parent->right = curr->left;
		}
		else if (curr->right == NULL)
		{
			if (curr == root)
				root = curr->right;
			else if (isLeft)
				parent->left = curr->right;
			else
				parent->right = curr->right;
		}
		else
		{
			TreeNode<T> *successor = getSuccessor(curr);

			if (curr == root)
				root = successor;
			else if (isLeft)
				parent->left = successor;
			else
				parent->right = successor;

			successor->left = curr->left;
		}
		size--;
		return true;
	}
}

template <class T>
void BST<T>::print(TreeNode<T> *node)
{
	if (node == NULL)
		return;

	print(node->left);
	cout << node->data << " | ";
	print(node->right);
}

template <class T>
void BST<T>::printTree()
{
	print(root);
}

template<class T>
TreeNode<T>* BST<T>::getRoot()
{
	return root;
}

template <class T>
int BST<T>::getSize()
{
	return size;
}

template <class T>
bool BST<T>::isEmpty()
{
	return (size == 0);
}