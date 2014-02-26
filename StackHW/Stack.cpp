//
//  Stack.cpp
//  HW5
//
//  Created by Raymond Dam on 10/8/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "Stack.h"
#include <iostream>

using namespace std;

template <class Type>
Stack<Type>::Stack()
{
    
}

template <class Type>
Stack<Type>::~Stack()
{
    S.~LinkedList();
}

template <class Type>
void Stack<Type>::push(Type input)
{
    S.add(input);
}

template <class Type>
void Stack<Type>::pop()
{
    if (S.remove() == true)
    {
        //cout << "Element Removed" << endl;
    }
    
    else
    {
        cout << "Error. Stack is empty." << endl;
    }
}

template <class Type>
Type Stack<Type>::top()
{
    //The exception for an empty stack is handled within the getValue object
    //In other words, getValue knows when there isn't a value for it to get
    
    return S.getValue();
}

//type instantiations
template class Stack<int>;
template class Stack<float>;
template class Stack<string>;

