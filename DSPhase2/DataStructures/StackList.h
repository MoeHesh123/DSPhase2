#include"../ADT/StackADT.h"

#ifndef STACK_LIST_
#define STACK_LIST_

template <class T>
class StackList : public StackADT<T>
{

	Node<T>* top;
	int itemCount;

public:

	StackList()
	{
		top = nullptr;
		itemCount = 0;
	}

	bool isEmpty() const
	{
		return (top == nullptr);
	}

	bool peek(T& item) const
	{
		if (isEmpty()) return false;
		item = top->getItem();
		return true;
	}

	bool push(const T& item)
	{
		Node<T>* newNode = new Node<T>();
		newNode->setItem(item);
		newNode->setNext(top);
		top = newNode;
		itemCount++;
		return true;
	}

	bool pop(T& item)
	{
		if (isEmpty()) return false;
		else
		{
			item = top->getItem();
			Node<T>* nodeToBeDeleted = top;
			top = top->getNext();
			nodeToBeDeleted->setNext(nullptr);
			delete nodeToBeDeleted;
			nodeToBeDeleted = nullptr;
			itemCount--;
			return true;
		}
	}

	int getCount() 
	{
		return itemCount;
	}

	Node<T>* gettop()
	{
		return top;
	}

	/*~StackList()
	{
		T temp;
		while (pop(temp));
	}*/

};
#endif