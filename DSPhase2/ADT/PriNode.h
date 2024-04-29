#pragma once
#ifndef _PRINODE
#define _PRINODE

template < class T>
class priNode
{

	T item;
	int pri;
	priNode<T>* next;

public:

	priNode(const T& r_Item, int PRI)
	{
		setItem(r_Item, PRI);
		next = nullptr;
	}

	void setItem(const T& r_Item, int PRI)
	{
		item = r_Item;
		pri = PRI;
	}

	void setNext(priNode<T>* nextNodePtr)
	{
		next = nextNodePtr;
	}

	T getItem(int& PRI) const
	{
		PRI = pri;
		return item;
	}

	priNode<T>* getNext() const
	{
		return next;
	}

	int getPri() const
	{
		return pri;
	}

};
#endif