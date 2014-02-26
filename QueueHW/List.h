//
//  List.h
//  HW7
//
//  Created by Raymond Dam on 11/1/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef LIST_H
#define LIST_H

#include <iostream>

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
    
    Type &get(int position) const;
    void set(int position, const Type &input);
    void remove(int position);
    void insert(int position, const Type &input);
    
    int getlength();
    
private:
    element<Type> *head, *tail;
    
    element<Type> *locate(int i) const;
    
    int length;
    bool inRange(int i) const;
    
    void removeelement(element<Type> *remove);
};

#endif
