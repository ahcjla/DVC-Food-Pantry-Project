//
// Created by alsha on 11/18/2021.
//

#ifndef _DVC_FOOD_PANTRY_PRIORITYQUEUE_H
#define _DVC_FOOD_PANTRY_PRIORITYQUEUE_H

template<typename V>
class PriorityQueue
{
    V* values;
    int cap;
    int count;
    void capacity(int);

public:
    PriorityQueue(int = 2);
    PriorityQueue(const PriorityQueue<V>&);
    ~PriorityQueue() {delete [ ] values;}
    PriorityQueue<V>& operator=(const PriorityQueue<V>&);

    void push(const V&);
    void pop();
    V top() const {return count == 0 ? V() : values[0];}
    int size() const {return count;}
    bool empty() const {return count == 0 ? true : false;}
    void clear() { count = 0;}

    void sorting(int);
};

// Main Constructor
template<typename V>
PriorityQueue<V>::PriorityQueue(int size)
{
    cap = size;
    count = 0;
    values = new V[cap];
}

// Copy Constructor
template<typename V>
PriorityQueue<V>::PriorityQueue(const PriorityQueue<V>& original)
{
    // initialize data members
    cap = original.cap;
    count = original.count;
    values = new V[cap];

    for (int index = 0; index < count; index++) // copy the contents of the array from the original...
        values[index] = original.values[index]; // ...to the copy
}

// Assignment Operator
template<typename V>
PriorityQueue<V>& PriorityQueue<V>::operator=(const PriorityQueue<V>& original)
{
    // Check if self copy
    if (this != &original)
    {
        // Delete existing array
        delete [ ] values;

        // initialize data members
        cap = original.cap;
        count = original.count;
        values = new V[cap];

        for (int index = 0; index < count; index++) // copy the contents of the array from the original...
            values[index] = original.values[index]; // ...to the copy
    }
    return *this;
}

// Capacity function
template<typename V>
void PriorityQueue<V>::capacity(int newCap)
{
    // allocate a new array with the new capacity
    V* temp = new V[newCap];

    // copy the contents
    for (int i = 0; i < count; i++)
        temp[i] = values[i];

    // deallocate original array
    delete [ ] values;

    // Switch newly allocated array into the object
    values = temp;

    // Update the capacity
    cap = newCap;

}

// push function
template<typename V>
void PriorityQueue<V>::push(const V& val)
{
    // Check if array is full
    if (count == cap)
        capacity(cap * 2);

    int index = count;

    // Copy the new value to V* values; array at index
    values[index] = val;

    while (index != 0)
    {
        int parent =  (index - 1) / 2;

        if ( values[index] < values[parent])
            break;

        V temp = values[index];
        values[index] = values[parent];
        values[parent] = temp;

        index = parent;
    }

    ++count;
}

// pop function
template<typename V>
void PriorityQueue<V>::pop( )
{
    // check there are values to remove
    if (count == 0) return;

    // To traverse the array
    int index = 0;

    while (true)
    {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;

        //  Reached the bottom of the heap if no left child
        if ((count - 1) < leftChild)
            break;

        // only left child

        if ((count - 1) < rightChild)
        {
            values[index] = values[leftChild];
            index = leftChild;
        }
        else if (values[rightChild] < values[leftChild])
        {
            // left child's value is higher than right child's
            values[index] = values[leftChild];
            index = leftChild;
        }
        else
        {
            values[index] = values[rightChild];
            index = rightChild;
        }
    }
    --count;

    values[index] = values[count];

    while (index !=0) {
        int parent = (index - 1) / 2;

        if (values[index] < values[parent])
            break;

        V temp = values[index];
        values[index] = values[parent];
        values[parent] = temp;

        index = parent;
    }
}

// sorting function
template<typename V>
void PriorityQueue<V>::sorting(int count)
{
    V* temp = new V[count];
    for (int d_track = 1; d_track < count; d_track *= 2)
    {
        int index = 0;
        for (int i = 0; i < count; i++) temp[i] = values[i];
        for (int j = 0; j < count; j += 2 * d_track)
        {
            int left = j;
            int leftMax = (count < left + d_track ? count : left + d_track);
            int right = leftMax;
            int rightMax = (count < right + d_track ? count : right + d_track);
            while (left < leftMax || right < rightMax)
            {
                if (left == leftMax) values[index++] = temp[right++];
                else if (right == rightMax) values[index++] = temp[left++];
                else if (temp[right] < temp[left]) values[index++] = temp[right++];
                else values[index++] = temp[left++];
            }
        }
    }
    delete[] temp;
}

#endif //_DVC_FOOD_PANTRY_PRIORITYQUEUE_H
