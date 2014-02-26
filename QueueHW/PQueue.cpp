//
//  PQueue.cpp
//  HW7
//
//  Created by Raymond Dam on 11/1/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "PQueue.h"

using namespace std;

template <class Type>
PQueue<Type>::PQueue(int d, bool maxHeap)
{
    Darray = d;
    HeapOption = maxHeap;
    Listindex = 0;
}

template <class Type>
PQueue<Type>::~PQueue()
{
    
}

template <class Type>
int PQueue<Type>::nthChild(int index, int n)
{
    return ((index << 1) + n); //formula: 2x+n
}

template <class Type>
int PQueue<Type>::parent(int index)
{
    return ((index - 1) >> Darray); //formula: (x-1)/d
}

//swaps node A with node B
template <class Type>
void PQueue<Type>::swap(int &A, int &B)
{
    int temp = A;
    A = B;
    B = temp;
}

template <class Type>
void PQueue<Type>::trickleUp(int index)
{
    //maintains heap property by swapping until parent node is bigger/smaller
    if (HeapOption == false)
    {
        while ((index > 0) && (parent(index) >= 0) && (Heap.get(parent(index) > Heap.get(index))))
        {
            swap(Heap.get(parent(index)), Heap.get(index));
        }
    }
    
    else if (HeapOption == true)
    {
        while ((index > 0) && (parent(index) >= 0) && (Heap.get(parent(index) < Heap.get(index))))
        {
            swap(Heap.get(parent(index)), Heap.get(index));
        }
    }
}

template <class Type>
void PQueue<Type>::trickleDown(int index)
{
    int firstchild = nthChild(index, 1);
    int child;
    
    //for loops checks each child
    for (int i = 1; i < Darray; i++)
    {
        //checks to see if next child is smaller
        //for 1st child node
        if (i == 1)
        {
            if ((firstchild > 0) && (nthChild(index, 2) > 0) && (Heap.get(firstchild) > Heap.get(nthChild(index, 2))))
            {
                child = nthChild(index, 2);
            }
            
            if (child > 0)
            {
                swap(Heap.get(firstchild), Heap.get(nthChild(index, 2)));
            }
        }
        
        //every subseqent node in the d-ary tree
        else
        {
            if ((child > 0) && (nthChild(index, i+1) > 0) && (Heap.get(child) > Heap.get(nthChild(index, i+1))))
            {
                child = nthChild(index, i+1);
            }
            
            if (child > 0)
            {
                swap(Heap.get(child), Heap.get(nthChild(index, i+1)));
            }
        }
    }
}

template <class Type>
void PQueue<Type>::add(const Type &item)
{
    Heap.set(Listindex, item);
    trickleUp(Listindex);
    Listindex++;
}

template <class Type>
void PQueue<Type>::remove()
{
    //remove root
    Heap.remove(0);
    
    //replace root with latest node
    Heap.set(0, Heap.get(Listindex));
    Heap.remove(Listindex);
    Listindex--;
    
    //restore heap property
    trickleDown(0);
}

template <class Type>
Type & PQueue<Type>::peek() const
{
    return Heap.get(0);
}

//type instantiations
template class PQueue<int>;












