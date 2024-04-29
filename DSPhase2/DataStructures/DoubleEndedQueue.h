#pragma once
#include"../ADT/QueueADT.h"

#ifndef DOUBLE_ENDED_QUEUE_LIST
#define DOUBLE_ENDED_QUEUE_LIST

template <class T>
class DoubleEndedQueueList : public QueueADT<T>
{

	Node<T>* frontPtr;
	Node<T>* backPtr;
	int itemCount;

public:

	DoubleEndedQueueList()
	{
		frontPtr = nullptr;
		backPtr = nullptr;
		itemCount = 0;
	}

	bool isEmpty() const
	{
		return (frontPtr == nullptr);
	}

	bool peek(T& FrontEntry) const
	{
		if (isEmpty()) return false;
		FrontEntry = frontPtr->getItem();
		return true;
	}

	bool peekBack(T& BackEntry) const
	{
		if (isEmpty()) return false;
		BackEntry = backPtr->getItem();
		return true;
	}

	bool enqueue(const T& newEntry)
	{
		Node<T>* newNodePtr = new Node<T>(newEntry);
		if (isEmpty()) frontPtr = newNodePtr;
		else backPtr->setNext(newNodePtr);
		backPtr = newNodePtr;
		itemCount++;
		return true;
	}

	bool enqueueFront(const T& newEntry)
	{
		Node<T>* newNodePtr = new Node<T>(newEntry);
		if (isEmpty())
		{
			frontPtr = newNodePtr;
			backPtr = newNodePtr;
		}
		else
		{
			newNodePtr->setNext(frontPtr);
			frontPtr = newNodePtr;
		}
		itemCount++;
		return true;
	}

	bool dequeue(T& FrontEntry)
	{
		if (isEmpty()) return false;
		Node<T>* nodeToDeletePtr = frontPtr;
		FrontEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		if (nodeToDeletePtr == backPtr)	backPtr = nullptr;
		delete nodeToDeletePtr;
		itemCount--;
		return true;
	}

	bool dequeueBack(T& BackEntry)
	{
		if (isEmpty()) return false;
		else
		{
			Node<T>* Prev = frontPtr;
			while (Prev->getNext()->getNext()) Prev = Prev->getNext();
			backPtr = Prev->getNext();
			Node<T>* nodeToDeletePtr = backPtr;
			BackEntry = backPtr->getItem();
			Prev->setNext(nullptr);
			delete nodeToDeletePtr;
			nodeToDeletePtr = nullptr;
			backPtr = Prev;
			itemCount--;
			return true;
		}
	}

	int getCount()
	{
		return itemCount;
	}

	Node<T>* getfrontPtr()
	{
		return frontPtr;
	}

	~DoubleEndedQueueList()
	{
		T temp;
		while (dequeue(temp));
	}

};
#endif