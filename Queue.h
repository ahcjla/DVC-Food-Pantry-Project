//
// Created by alsha on 11/22/2021.
//

#ifndef _DVC_FOOD_PANTRY_QUEUE_H
#define _DVC_FOOD_PANTRY_QUEUE_H

template<typename T>
class Queue{
    struct Node {
        T value;
        Node* next = nullptr;
    };
    Node* firstNode;
    Node* lastNode;
    T dummy;
    int count;

public:
    Queue( );
    Queue(const Queue<T>&);
    ~Queue( );
    Queue<T>& operator=(const Queue<T>&);
    void push(const T&);
    const T& front() const;
    const T& back() const;
    void pop( );
    int size( ) const {return count;};
    bool empty( ) const {return size() == 0;};
    void clear( );
};

template<typename T>
Queue<T>::Queue( )
{
    firstNode = nullptr;
    lastNode = nullptr;
    dummy = T( );
    count = 0;
}

template<typename T>
Queue<T>::Queue(const Queue<T>& original)
{
    firstNode = nullptr;
    lastNode = nullptr;
    count = 0;

    for (Node* p = original.firstNode; p; p = p->next)
    {
        push(p->value);
    }
}

template<typename T>
Queue<T>::~Queue( )
{
    clear();
    delete firstNode;
    delete lastNode;
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& original)
{
    if (this != &original)
    {
        // deallocate existing nodes
        clear();

        // build new queue
        for (Node* p = original.firstNode; p; p = p->next)
        {
            push(p->value);
        }
    }
    return *this;
}

template<typename T>
void Queue<T>::push(const T &value)
{
    Node* temp = new Node;
    temp->value = value;
    temp->next = nullptr;
    if (lastNode)
    {
        lastNode->next = temp;
    }
    else
    {
        firstNode = temp;
    }
    lastNode = temp;
    ++count;
}

template<typename T>
const T &Queue<T>::front( ) const
{
    if (empty( ))
    {
        return dummy;
    }
    return firstNode->value;
}

template<typename T>
const T &Queue<T>::back( ) const
{
    if (empty( ))
    {
        return dummy;
    }
    return lastNode->value;
}

template<typename T>
void Queue<T>::pop( )
{
    if (firstNode)
    {
        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
        --count;
        if (!size( ))
        {
            lastNode = nullptr;
        }
    }
}

template<typename T>
void Queue<T>::clear( )
{
    while (firstNode)
    {
        pop();
    }
    // reinitialize firstNode and lastNode
    firstNode = nullptr;
    lastNode = nullptr;
}


#endif //_DVC_FOOD_PANTRY_QUEUE_H
