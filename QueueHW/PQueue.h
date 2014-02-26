//
//  PQueue.h
//  HW7
//
//  Created by Raymond Dam on 11/1/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef PQUEUE_H
#define PQUEUE_H

#include <iostream>
#include "List.h"

template <class Type>
class PQueue
{
    public:
        PQueue (int d, bool maxHeap);
        ~PQueue ();
    
        Type & peek () const;
        void remove ();
        void add (const Type &item);
    
    private:
        int nthChild(int index, int n);
        int parent(int index);
        void swap(int &A, int &B);
        void trickleUp(int index);      //add
        void trickleDown(int index);    //remove
    
        List<Type> Heap;
        int Listindex;
        int Darray;
        bool HeapOption;
};

#endif
