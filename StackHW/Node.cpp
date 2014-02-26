//
//  Node.cpp
//  HW5
//
//  Created by Raymond Dam on 10/9/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "Node.h"
#include <iostream>

using namespace std;

template <class Type>
Node<Type>::Node()
{
    Next = Prev = NULL;
    index = 0;
    
    
}

template <class Type>
Node<Type>::~Node()
{
    delete Next;
    delete Prev;
}

template <class Type>
Type Node<Type>::getValue ()
{
    return Data;
}

template <class Type>
void Node<Type>::set(Type Data)
{
    this->Data = Data;
}

template <class Type>
Node<Type>* Node<Type>::getNext()
{
    return Next;
}

template <class Type>
Node<Type>* Node<Type>::getPrev()
{
    return Prev;
}

template <class Type>
void Node<Type>::setNext(Node<Type> *Next)
{
    this->Next = Next;
}

template <class Type>
void Node<Type>::setPrev(Node<Type> *Prev)
{
    this->Prev = Prev;
}

template <class Type>
void Node<Type>::setIndex(int input)
{
    this->index = input;
}

template <class Type>
int Node<Type>::getIndex()
{
    return index;
}

//type instantiations
template class Node<int>;
template class Node<float>;
template class Node<string>;


