//
//  LinkedList.h
//  HW5
//
//  Created by Raymond Dam on 10/9/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "Node.h"

template <class Type>
class LinkedList
{
    public:
        LinkedList ();
        ~LinkedList ();
    
        void add (Type input);
        bool remove ();
        void clear ();
    
        Type getValue ();
        bool next ();
        bool back ();
        bool first ();
        bool last ();
    
    private:
        Node<Type> *head;
        Node<Type> *tail;
        Node<Type> *position;
        int index;
};

#endif
