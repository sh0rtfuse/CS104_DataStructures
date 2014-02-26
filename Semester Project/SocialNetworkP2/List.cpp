//
//  List.cpp
//  HW6
//
//  Created by Raymond Dam on 10/29/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "List.h"
#include "WallPost.h"
#include "User.h"

template<class Type>
List<Type>::List()
{
    head = tail = NULL;
    
    //list starts out empty;
    length = 0;
}

template<class Type>
List<Type>::~List()
{
    head = NULL;
    delete head;
    tail = NULL;
    delete tail;
}

template<class Type>
element<Type>* List<Type>::locate(int i)
{
    element<Type> *position = head;
    
    for (int j = 0; j < i; j++)
    {
        position = position->next;
    }

    return position;
}

//makes sure that i is in the list
template<class Type>
bool List<Type>::inRange(int i)
{
    if (i <= length)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

//return data at position
template<class Type>
Type List<Type>::get(int position)
{
    if(inRange(position) == true)
    {
        return locate(position)->Data;
    }
    
    else
    {
        std::cout << "Out of Bounds" << std::endl;
        return locate(position)->Data;
    }
}

//replace data at "position" with "input"
template<class Type>
void List<Type>::set(int position, const Type &input)
{
    try
    {
        if(inRange(position) == true)
        {
            //find the pointer to "position" and overwrite
            element<Type> *temp = locate(position);
            if (temp)
            {
                temp->Data = input;
            }
        }
        
        else if(inRange(position) == false)
        {
            throw "Out of Bounds";;
        }
    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }
}

//remove element at "position" from list
template<class Type>
void List<Type>::remove(int position)
{
    try
    {
        if(inRange(position) == true)
        {
            //call "removeelement" to remove node at "position
            removeelement(locate(position));
            
            //decrement index
            length--;
        }
        
        else if(inRange(position) == false)
        {
            throw "Out of Bounds";
        }
    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }
}

//removes an element from the linkedlist
template<class Type>
void List<Type>::removeelement(element<Type> *remove)
{
    //if...else statements to bypass deleted node
    if (remove != head)
    {
        remove->prev->next = remove->next;
    }
    
    else
    {
        head = remove->next;
    }
    
    if (remove != tail)
    {
        remove->next->prev = remove->prev;
    }
    else
    {
        tail = remove->prev;
    }
    
    remove = NULL;
    delete remove;
}

template<class Type>
void List<Type>::insert(int position, const Type &input)
{
    try
    {
        if(inRange(position) == true)
        {
            element<Type> *Node = locate(position);
            element<Type> *newNode = new element<Type>;
            newNode->Data = input;
            newNode->next = Node;
            newNode->prev = NULL;
            
            //inserts in the middle of the list
            if (Node)
            {
                newNode->prev = Node->prev;
                Node->prev = newNode;
                
                if (newNode->prev)
                {
                    newNode->prev->next = newNode;
                }
            }
            
            //inserts at the end
            else
            {
                newNode->prev = tail;
            }
            
            //update head and tail
            if (position == 0)
            {
                if (head)
                {
                    head->prev = newNode;
                }
                
                head = newNode;
            }
            if (position == length)
            {
                if (tail)
                {
                    tail->next = newNode;
                }
                
                tail = newNode;
            }

            //increment index
            length++;
        }
        
        else if(inRange(position) == false)
        {
            throw "Out of Bounds";
        }
    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }
}

//getter function
template <class Type>
int List<Type>::getlength()
{
    return length;
}

template<class Type>
ListIterator<Type> List<Type>::begin()
{
    return ListIterator<Type>(this, head);
}

template<class Type>
ListIterator<Type> List<Type>::end()
{
    return ListIterator<Type>(this, tail);
}

//Iterator Implementation
template<class Type>
ListIterator<Type>::ListIterator(const List<Type> *List, element<Type> *position)
{
    Traversing = List;
    current = position;
}

template<class Type>
ListIterator<Type> ListIterator<Type>::operator++() const
{
    current = current->next;
    return *this;
}

template<class Type>
ListIterator<Type> ListIterator<Type>::operator--() const
{
    current = current->prev;
    return *this;
}

//datatype instantiations
template class List<wallpost>;
template class element<wallpost>;
template class List<User>;
template class element<User>;
template class List<std::string>;
template class element<std::string>;






