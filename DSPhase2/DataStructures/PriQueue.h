#include "../ADT/QueueADT.h"

#ifndef PRI_QUEUE_
#define PRI_QUEUE_

template <class T>
class priQueue
{

    priNode<T>* head;
    int itemCount = 0;

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

    bool peek(T& topEntry, int& pri)
    {
        if (isEmpty()) return false;
        topEntry = head->getItem(pri);
        pri = head->getPri();
        return true;
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

    int getCount() 
    {
        return itemCount;
    }
    priNode<T>* getfrontPtr()
    {
        return head;
    }

    priNode<T>* gethead()
    {
        return head;
    }
    void PrintPriQueue()
    {
        Node<T*>* Traversal = head;
        while (Traversal->getNext())
        {
            cout << Traversal->getItem() << ", ";
            Traversal = Traversal->getNext();
        }
        cout << Traversal->getItem();
    }

    ~priQueue()
    {
        T tmp;
        int p;
        while (dequeue(tmp, p));
    }

};
#endif