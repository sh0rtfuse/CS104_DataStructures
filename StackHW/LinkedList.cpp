//
//  LinkedList.cpp
//  HW5
//
//  Created by Raymond Dam on 10/9/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "LinkedList.h"

#include <iostream>

using namespace std;

template<class Type>
LinkedList<Type>::LinkedList()
{
    //intialize private variables
    head = new Node<Type>();
    head->setNext(NULL);
    head->setPrev(NULL);
    position = NULL;
    index = 0;
}

template<class Type>
LinkedList<Type>::~LinkedList()
{
    //memory management
    while (index != 0)
    {
        remove();
    }
    
    position = NULL;
    delete position;
    head = NULL;
    delete head;
    tail = NULL;
    delete tail;
}

template<class Type>
void LinkedList<Type>::add(Type input)
{
    Node<Type> *addNode = new Node<Type>();
    
    addNode->set(input);
    
    index++;
    
    if(position != NULL)
    {
        tail = position;
        addNode->setNext(position->getNext());
        
        if (addNode->getNext()!= NULL)
        {
            position = position->getNext();
            position->setPrev(addNode);
        }
        
        addNode->setPrev(tail);
        position = addNode;
        tail->setNext(addNode);
        addNode->setIndex(index);
    }
    
    else
    {
        addNode->setNext(NULL);
        head->setNext(addNode);
        addNode->setPrev(head);
        position = addNode;
        addNode->setIndex(index);
    }
}

template<class Type>
bool LinkedList<Type>::remove()
{
    Node<Type> *rmNode = position;
    
    if (position != NULL)
    {
        if (position->getPrev() == head)
        {
            position = head;
            position->setNext(NULL);
            position->setPrev(NULL);
            
            delete rmNode;
            
            index--;
            
            return true;
        }
        
        else if (position->getNext() == NULL)
        {
            back();
            position->setNext(NULL);
            
            //delete rmNode;
            
            index--;
            
            return true;
        }
        
        else
        {
            back();
            position->setNext(rmNode->getNext());
            next();
            position->setPrev(rmNode->getPrev());

            delete rmNode;
            
            index--;
            
            return true;
        }
    }
    
    else
    {
        return false;
    }
}

template<class Type>
void LinkedList<Type>::clear()
{
    //cycles the remove function until the list has been deleted
    while (index != 0)
    {
        remove ();
    }
    
    delete position;
}

template<class Type>
Type LinkedList<Type>::getValue()
{
    if (position != NULL)
    {
        return position->getValue();
    }
    
    if (position == head)
    {
        cout << "Error Node has no value" << endl;
    }
    
    cout << "Error Node has no value" << endl;
    return 0;
}

template<class Type>
bool LinkedList<Type>::next()
{
    //if the list is at the end
    if (position->getNext() == NULL)
    {
        return false;
    }
    
    position = position->getNext();
    
    return position;
}

template<class Type>
bool LinkedList<Type>::back()
{
    if (position->getPrev() == head)
    {
        return false;
    }
    
    position = position->getPrev();
    
    return position;
}

template<class Type>
bool LinkedList<Type>::first()
{
    if (head->getNext()!= NULL)
    {
        position = head->getNext();
    }
    
    return position;
}

template<class Type>
bool LinkedList<Type>::last()
{
    while (position->getNext() != NULL)
    {
        position = position->getNext();
    }
    
    return position;
}

//type instantiations
template class LinkedList<int>;
template class LinkedList<float>;
template class LinkedList<string>;










