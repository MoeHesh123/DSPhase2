#include "../ADT/QueueADT.h"

#ifndef PRI_QUEUE_
#define PRI_QUEUE_

template <class T>
class priQueue
{

    priNode<T>* head;
    int itemCount;

public:

    priQueue()
    {
        head = nullptr;
        itemCount = 0;
    }

    bool isEmpty() const
    {
        return (head == nullptr);
    }

    void enqueue(const T& data, int priority)
    {
        priNode<T>* newNode = new priNode<T>(data, priority);
        if (head == nullptr || priority > head->getPri())
        {
            newNode->setNext(head);
            head = newNode;
            return;
        }
        priNode<T>* current = head;
        while (current->getNext() && priority <= current->getNext()->getPri()) current = current->getNext();
        newNode->setNext(current->getNext());
        current->setNext(newNode);
        itemCount++;
    }

    bool dequeue(T& topEntry, int& pri)
    {
        if (isEmpty()) return false;
        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        itemCount--;
        return true;
    }

    bool peek(T& topEntry, int& pri)
    {
        if (isEmpty()) return false;
        topEntry = head->getItem();
        pri = head->getPri();
        return true;
    }

    priNode<T>* gethead()
    {
        return head;
    }

    ~priQueue()
    {
        T tmp;
        int p;
        while (dequeue(tmp, p));
    }

};
#endif