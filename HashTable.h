//
// Created by alsha on 11/22/2021.
//

#ifndef _DVC_FOOD_PANTRY_HASHTABLE_H
#define _DVC_FOOD_PANTRY_HASHTABLE_H


#include <list>
#include "Queue.h"

template<typename K, typename V, int CAP>
class HashTable
{
    struct Node
    {
        K key;
        V value;
    };
    list<Node> data[CAP]; // array with chaining to avoid collision
    int(*hashCode) (const K&); // pointer to the hash function in the main application
    int count;

public:
    HashTable(int(*)(const K&)= 0); // assign nullptr if no hash function givn
    double loadFactor() const {return  1.0 * count / CAP;} // getter function showing the used space in %
    V operator[ ] (const K&) const; // getter version for data retrieval
    V& operator[ ] (const K&); // setter version to populate index with data
    bool containsKey(const K&) const; // getter function checking if key exists
    void deleteKey(const K&); // setter deleting data and key
    Queue<K> keys() const; //getter function retrieving all keys in the array
    int size( ) const {return count;}
    void clear( ); //clear the array from all keys and value sets
};

template<typename K, typename V, int CAP>
HashTable<K, V, CAP>::HashTable(int (*hash)(const K &))
{
    hashCode = hash;
    count = 0;
}


template<typename K, typename V, int CAP>
V HashTable<K, V, CAP>::operator[ ](const K& key) const
{
    // default alias for the result
    V result = V();

    int index = hashCode(key) % CAP;
    // Check index is in rage
    if (index < 0)
        index += CAP;

    // find a matching value for the key
    typename list<Node>::const_iterator it; // use const iterator for cost functions
    for (it = data[index].begin(); it != data[index].end(); it++)
    {
        if (key == it->key)
        {
            result = it->value;
            break;
        }

    }

    return result;

}

template<typename K, typename V, int CAP>
V& HashTable<K, V, CAP>::operator[ ](const K& key)
{
    int index = hashCode(key) % CAP;
    // Check index is in rage
    if (index < 0)
        index += CAP;

    typename list<Node>::iterator it; // non-constant iterator
    for (it = data[index].begin(); it != data[index].end(); it++)
    {
        if (key == it->key)
        {
            return it->value;
        }
    }

    // Create new node
    Node temp;
    temp.value = V();
    temp.key = key;

    // add node to the list at the index
    data[index].push_back(temp);

    // update count
    ++count;

    return data[index].back().value;
}

template<typename K, typename V, int CAP>
bool HashTable<K, V, CAP>::containsKey(const K& key) const
{
    bool result = false;

    int index = hashCode(key) % CAP;
    // Check index is in rage
    if (index < 0)
        index += CAP;

    // find a matching value for the key
    typename list<Node>::const_iterator it; // use const iterator for cost functions
    for (it = data[index].begin(); it != data[index].end(); it++)
    {
        if (key == it->key)
        {
            result = true;
            break;
        }

    }

    return result;

}

template<typename K, typename V, int CAP>
void HashTable<K, V, CAP>::deleteKey(const K& key)
{
    int index = hashCode(key) % CAP;
    // Check index is in rage
    if (index < 0)
        index += CAP;

    typename list<Node>::iterator it;
    for (it = data[index].begin(); it != data[index].end(); it++)
    {
        if (key == it->key)
        {
            data[index].erase(it);

            //update count
            --count;
            break;
        }

    }

}

template<typename K, typename V, int CAP>
Queue<K> HashTable<K, V, CAP>::keys() const
{
    Queue<K> keys;
    typename list<Node>::const_iterator it;

    for (int i = 0; i < CAP; i++)
    {
        for (it = data[i].begin(); it != data[i].end(); it++)
        {
            keys.push(it->key);
        }
    }

    return keys;
}

template<typename K, typename V, int CAP>
void HashTable<K, V, CAP>::clear()
{
    typename list<Node>::iterator it;

    for (int i = 0; i < CAP; i++)
    {

        data[i].clear();

    }

    count = 0;
}

#endif //_DVC_FOOD_PANTRY_HASHTABLE_H
