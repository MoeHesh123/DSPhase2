#include"../ADT/QueueADT.h"

#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

template <class T>
class LinkedQueue : public QueueADT <T>
{

	Node<T>* backPtr;
	Node<T>* frontPtr;
	int itemCount;

public:

	LinkedQueue()
	{
		backPtr = nullptr;
		frontPtr = nullptr;
		itemCount = 0;
	}

	bool isEmpty() const
	{
		return (frontPtr == nullptr);
	}

	bool enqueue(const T& newEntry)
	{
		Node<T>* newNodePtr = new Node<T>(newEntry);
		if (isEmpty())
			frontPtr = newNodePtr;
		else
			backPtr->setNext(newNodePtr);

		backPtr = newNodePtr;
		return true;
	}

	bool dequeue(T& FrontEntry)
	{
		if (isEmpty()) return false;
		Node<T>* nodeToDeletePtr = frontPtr;
		FrontEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		if (nodeToDeletePtr == backPtr) backPtr = nullptr;
		delete nodeToDeletePtr;
		itemCount--;
		return true;
	}

	bool peek(T& FrontEntry)  const
	{
		if (isEmpty()) return false;
		FrontEntry = frontPtr->getItem();
		return true;
	}

	Node<T>* getfrontPtr()
	{
		return frontPtr;
	}

	~LinkedQueue()
	{
		T temp;
		while (dequeue(temp));
	}

	LinkedQueue(const LinkedQueue<T>& LQ)
	{
		frontPtr = backPtr = nullptr;
		Node<T>* NodePtr = LQ.frontPtr;
		while (NodePtr)
		{
			enqueue(NodePtr->getItem());
			NodePtr = NodePtr->getNext();
		}
	}

};
#endif