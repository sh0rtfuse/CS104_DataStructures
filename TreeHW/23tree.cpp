//
//  23tree.cpp
//  HW9
//
//  Created by Raymond Dam on 11/20/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "23tree.h"

template <class KeyType, class ValueType>
Node<KeyType, ValueType>::Node(const KeyType & key, const ValueType & value)
{
    leftKey = key;
    leftValue = value;
    numberOfKeys++;
}

template <class KeyType, class ValueType>
Node<KeyType, ValueType>::Node(const KeyType & lKey, const ValueType & lValue, const KeyType & rKey, const ValueType & rValue)
{
    leftKey = lKey;
    leftValue = lValue;
    numberOfKeys++;
    rightKey = rKey;
    rightValue = rValue;
    numberOfKeys++;
}

template <class KeyType, class ValueType>
Node<KeyType, ValueType>::~Node()
{
    
}

template <class KeyType, class ValueType>
TwoThreeTree<KeyType, ValueType>::TwoThreeTree()
{
    
}

template <class KeyType, class ValueType>
TwoThreeTree<KeyType, ValueType>::~TwoThreeTree()
{
    
}

template <class KeyType, class ValueType>
void TwoThreeTree<KeyType, ValueType>::add(const KeyType & key, const ValueType & value)
{
    Node<KeyType, ValueType> RootNode(key, value);
        
    Tree.push_back(RootNode);
}

template <class KeyType, class ValueType>
void TwoThreeTree<KeyType, ValueType>::remove(const KeyType &key)
{
    for (int i = 0; i < Tree.size(); i++)
    {
        Node<KeyType, ValueType> iNode = Tree[i];
        
        if (iNode.leftKey == key)
        {
            //swap with last element and pop
            Node<KeyType, ValueType> TempNode = Tree.back();
            Tree[Tree.size()-1] = iNode;
            Tree[i] = TempNode;
            Tree.pop_back();
        }
    }
}

template <class KeyType, class ValueType>
ValueType TwoThreeTree<KeyType, ValueType>::get(const KeyType &key) const
{
    ValueType output;
    
    for (int i = 0; i < Tree.size(); i++)
    {
        Node<KeyType, ValueType> iNode = Tree[i];
        
        if (iNode.leftKey == key)
        {
            output = iNode.leftValue;
            
            return output;
        }
    }
    
    return 0;
}

template class Node<int, string>;
template class TwoThreeTree<int, string>;
template class Node<string, float>;
template class TwoThreeTree<string, float>;









