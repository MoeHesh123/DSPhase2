
#define MAX_SIZE 1000

#ifndef _BAG
#define _BAG

template <typename T>
class bag
{

    T* arr[MAX_SIZE];
    int count = 0;

public:

    bag()
    {
        for (int i = 0; i < MAX_SIZE; i++) arr[i] == nullptr;
    }

    bool isFull()
    {
        return (count == MAX_SIZE);
    }

    bool insert(T& newEntry)
    {
        if (count != MAX_SIZE)
        {
            arr[count] = new T(newEntry);
            count++;
            return true;
        }
        return false;
    }

    bool isEmpty()
    {
        return count == 0;
    }

    bool isFound(const int& x)
    {
        for (int i = 0; i < count; i++)
        {
            if (*arr[x] == *arr[i]) return true;
        }
        return false;
    }

    bool remove(T& value, const int& i)
    {
        if (isEmpty() || !isFound(i)) return false;
        else
        {
            value = *arr[i];
            arr[i] = arr[count - 1];
            count--;
        }
        return true;
    }

    int getCount()
    {
        return count;
    }

    T getitem(int i)
    {
        return *arr[i];
    }

    ~bag()
    {
        for (int i = 0; i < count; i++) delete arr[i];
    }

};
#endif#pragma once
