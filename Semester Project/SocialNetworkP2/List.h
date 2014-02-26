//
//  List.h
//  HW6
//
//  Created by Raymond Dam on 10/29/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef LIST_H
#define LIST_H

#include <iostream>

template<class Type>
class ListIterator;

template<class Type>
class element
{
    public:
        Type Data;
    
        element *next, *prev;
};

template<class Type>
class List
{
    public:
        List();
        ~List();
    
        Type get(int position);
        void set(int position, const Type &input);
        void remove(int position);
        void insert(int position, const Type &input);
    
        int getlength();
    
        ListIterator<Type> begin();
        ListIterator<Type> end();
    
    private:
        element<Type> *head, *tail;
    
        element<Type> *locate(int i);
    
        int length;
        bool inRange(int i);
    
        void removeelement(element<Type> *remove);
};

template<class Type>
class ListIterator
{
    public:
        ListIterator(const List<Type> *List, element<Type> *position);
    
        ListIterator operator++ () const;
        ListIterator operator-- () const;
    
    private:
        const List<Type> *Traversing;
        element<Type> *current;
};
#endif
