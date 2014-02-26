//
//  Stack.h
//  HW5
//
//  Created by Raymond Dam on 10/8/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "LinkedList.h"

template <class Type>
class Stack
{
    public:
        Stack();
        ~Stack();
    
        void push(Type input);
        void pop();
        Type top();
    
    private:
        LinkedList<Type> S;
};

#endif
