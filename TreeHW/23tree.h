//
//  23tree.h
//  HW9
//
//  Created by Raymond Dam on 11/20/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef __HW9___3tree__
#define __HW9___3tree__

#include <iostream>
#include <vector>

using namespace std;

template <class KeyType, class ValueType>
class Node
{
    public:
        int numberOfKeys = 0;
    
        KeyType leftKey, rightKey;
        ValueType leftValue, rightValue;
    
        int leftChild, middleChild, rightChild;
    
        Node (const KeyType & key, const ValueType & value); // one key only
        Node (const KeyType & lKey, const ValueType & lValue, const KeyType & rKey, const ValueType & rValue); // two keys
        ~Node ();
};

template <class KeyType, class ValueType>
class TwoThreeTree : private vector<Node<KeyType, ValueType>>
{
    public:
        void add (const KeyType & key, const ValueType & value);
        void remove (const KeyType & key);
    
        ValueType get (const KeyType & key) const;
    
        TwoThreeTree();
        ~TwoThreeTree();
    
    private:
        vector<Node<KeyType, ValueType>> Tree;
};

#endif
