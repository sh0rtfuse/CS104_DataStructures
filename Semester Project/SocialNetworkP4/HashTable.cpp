//
//  HashTable.cpp
//  HW10
//
//  Created by Raymond Dam on 11/26/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "HashTable.h"
#include "User.h"

#include <list>
#include <vector>
#include <stack>

using namespace std;

template<class KeyType, class ValueType>
Node<KeyType, ValueType>::Node(const KeyType &inKey, const ValueType &inValue)
{
    key = inKey;
    value = inValue;
}

template<class KeyType, class ValueType>
Node<KeyType, ValueType>::Node()
{
    
}

template<class KeyType, class ValueType>
KeyType Node<KeyType,ValueType>::getKey()
{
    return key;
}

template<class KeyType, class ValueType>
ValueType Node<KeyType, ValueType>::getValue()
{
    return value;
}

template<class KeyType, class ValueType>
hashtable<KeyType, ValueType>::hashtable(int initialSize)
{
    //intialize vector intial size
    Table.resize(initialSize);
    
    //set all pointers in vector to null, then add pointer to a linkedlist
    for (int i = 0; i < Table.size(); i++)
    {
        std::list<Node<KeyType,ValueType>> iBucket;
        
        Table [i] = iBucket;
    }
    
    s = 0;
    m = initialSize;
    loadfactor = 0;
}

template<class KeyType, class ValueType>
void hashtable<KeyType, ValueType>::add(const KeyType &key, const ValueType &value)
{
    //check to see if table needs to be doubled
    if(loadfactor >= 0.5)
    {
        Table.resize(m*2);
        m = m*2;
    }
    
    Node<KeyType, ValueType> input(key, value);
    
    //use hash key to assign data to a bucket
    KeyType index = key % Table.size();
    
    //grabs assigned bucket
    std::list<Node<KeyType, ValueType>> Bucket = Table[index];
    
    //insert node
    Bucket.push_back(input);
    
    //update bucket after add
    Table[index] = Bucket;
    
    //track load factor
    s++;
    loadfactor = s/m;
}

template<class KeyType, class ValueType>
void hashtable<KeyType, ValueType>::remove(const KeyType &key)
{
    typename std::list<Node<KeyType, ValueType>>::iterator Temp_iter;
    
    //hash key to find the right index
    KeyType index = key % Table.size();
    
    //grabs assigned bucket
    std::list<Node<KeyType, ValueType>> Bucket = Table[index];
    
    //search bucket for key
    for (typename std::list<Node<KeyType, ValueType>>::iterator Bucket_iter = Bucket.begin(); Bucket_iter != Bucket.end(); Bucket_iter++)
    {
        Node<KeyType, ValueType> temp = *Bucket_iter;
        
        KeyType tempKey = temp.getKey();
        
        if (tempKey == key)
        {
            Temp_iter = Bucket_iter;
        }
    }
    
    //delete node if found
    Node<KeyType, ValueType> temp = *Temp_iter;
    KeyType tempKey = temp.getKey();
    if (tempKey == key)
    {
        Bucket.erase(Temp_iter);
        //update bucket after erase
        Table[index] = Bucket;
    }
}

template<class KeyType, class ValueType>
ValueType &hashtable<KeyType, ValueType>::get(const KeyType &key) const
{
    ValueType output;
    ValueType output2;
    
    //hash key to find the right index
    KeyType index = key % Table.size();
    
    //grabs assigned bucket
    std::list<Node<KeyType, ValueType>> Bucket = Table[index];
    
    //search bucket for key
    for (typename std::list<Node<KeyType, ValueType>>::iterator Bucket_iter = Bucket.begin(); Bucket_iter != Bucket.end(); Bucket_iter++)
    {
        Node<KeyType, ValueType> temp = *Bucket_iter;
        
        KeyType tempKey = temp.getKey();
        
        if (tempKey == key)
        {
            output = temp.getValue();

            return output;
        }
    }
    
    return output2;
}

//for returning multiple results at once
template<class KeyType, class ValueType>
stack<ValueType> hashtable<KeyType, ValueType>::get2(const KeyType &key)
{
    stack<ValueType> output;
    
    //hash key to find the right index
    KeyType index = key % Table.size();
    
    //grabs assigned bucket
    std::list<Node<KeyType, ValueType>> Bucket = Table[index];
    
    //search bucket for key
    for (typename std::list<Node<KeyType, ValueType>>::iterator Bucket_iter = Bucket.begin(); Bucket_iter != Bucket.end(); Bucket_iter++)
    {
        Node<KeyType, ValueType> temp = *Bucket_iter;
        
        KeyType tempKey = temp.getKey();
        
        if (tempKey == key)
        {
            ValueType result = temp.getValue();
            
            output.push(result);
        }
    }
    
    return output;
}

template class Node<int, string>;
template class hashtable<int, string>;

template class Node<int, User>;
template class hashtable<int, User>;


