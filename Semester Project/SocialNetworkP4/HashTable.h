//
//  HashTable.h
//  HW10
//
//  Created by Raymond Dam on 11/26/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <stack>

using std::list;
using std::vector;
using std::stack;

template <class KeyType, class ValueType>
class Node
{
    public:
        Node();
        Node(const KeyType &inKey, const ValueType &inValue);
    
        KeyType getKey();
        ValueType getValue();
    
    private:
        KeyType key;
        ValueType value;
};

template <class KeyType, class ValueType>
class hashtable: private Node<KeyType, ValueType>
{
    public:
        hashtable(int initialSize);
    
        void add (const KeyType &key, const ValueType &value);
        void remove (const KeyType &key);
        ValueType &get (const KeyType &key) const;
        stack<ValueType> get2(const KeyType &key);
    
    private:
        vector <list<Node<KeyType,ValueType> > > Table;
    
        int s; //number nodes stored
        int m; //size of the array
        int loadfactor; //tracks load factor of table
};

#endif

