//
//  Node.h
//  HW5
//
//  Created by Raymond Dam on 10/9/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef NODE_H
#define NODE_H

/*
 This class manages each node in the linkedlist
 with a bunch of getter and setter functions.
 The class is meant to be as generic as possible
 for reuse in other Data Structure implementations.
*/

template <class Type>
class Node
{
    public:
        Node();
        ~Node();
    
        Type getValue ();
        void set(Type Data);
    
        Node<Type> *getNext();
        Node<Type> *getPrev();
        void setNext(Node<Type> *Next);
        void setPrev(Node<Type> *Prev);
    
        void setIndex (int input);
        int getIndex ();
    
    private:
        Type Data;
        Node<Type> *Next;
        Node<Type> *Prev;
        int index;
};

#endif
