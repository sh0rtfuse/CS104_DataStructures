//
//  LinkedListTemplate.cpp
//  Social Network
//
//  Created by Raymond Dam on 9/22/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "LinkedListTemplate.h"

#include <iostream>
#include <sstream>

using namespace std;


//constructor
template <class type>
LinkedList<type>::LinkedList()
{
    head = tail = NULL;
}

//destructor
template <class type>
LinkedList<type>::~LinkedList()
{
    //delete some stuff
}

//adds an element to the linked list
template <class type>
void LinkedList<type>::add(const type input)
{
    //initialize temporary node to store new data
    elements *temp = new elements;
    
    //store input into data inside the node
    temp->data = input;
    
    //the next node hasn't be created yet so set its pointer to null
    temp->next = NULL;
    
    //as the lastest node its other end points back to the 1st node at the end
    temp->previous = tail;
    
    //when node is the head, set head and tail node to the current node
    if (head == NULL)
    {
        head = tail = temp;
    }
    
    //otherwise, set current node as the tail node
    else
    {
        tail->next = temp;
        
        tail = temp;
    }
    
    //clean up!
    temp = NULL;
    delete temp;
}


//helps remove a given element by finding and bypassing the pointer to said element
template <class type>
void LinkedList<type>::removehelper(elements *temp)
{
    //if head node, sets pointer to bypass deleted node
    if (temp == head)
    {
		head = temp->next;
    }
    
	else
    {
        temp->previous->next = temp->next;
    }
    
    //if tail node, sets pointer to bypass deleted node
	if (temp == tail)
    {
		tail = temp->previous;
    }
    
	else
    {
        temp->next->previous = temp->previous;
    }
    
    //clean up!
    temp = NULL;
    delete temp;
}

//removes inputted element from the linked list
//NOTE: Will remove +1 element from what you specify
template <class type>
void LinkedList<type>::remove(const type input)
{
    //used to parse the linked list
    elements *temp1 = head;
    
    //searchs from head to tail for the inputted element
    while (temp1 != NULL)
    {
        //when found, we enlist the helper function to bypass the pointer to the element
        if (temp1->data == input)
        {
            //temporary holds pointer to the node
            elements *temp2 = temp1->next;
            
            //bypassing (deleting) the node
            removehelper(temp2);
            
            //now the pointer will be directed at the next node
            temp1 = temp2;
            
            //clean up!
            temp2 = NULL;
            delete temp2;
        }
        
        //if element is not found, we move on to the next node
        else
        {
            temp1 = temp1->next;
        }
    }
    
    //clean up!
    temp1 = NULL;
    delete temp1;
}

//searches for specificed element
template <class type>
bool LinkedList<type>::find(const type input)
{
    //used to parse the linked list
    elements *temp1 = head;
    
    //searchs from head to tail for the inputted element
    while (temp1 != NULL)
    {
        //if found, function returns true
        if (temp1->data == input)
        {
            return true;
        }
    
        //if element is not found, we move on to the next node
        else
        {
            temp1 = temp1->next;
        }
    }
    
    //clean up
    temp1 = NULL;
    delete temp1;
    
    //if the element is not in the list then return false
    return false;
}

//prints out content of the array
template <class type>
void LinkedList<type>::testprintlist()
{
    for (elements *i = head; i != NULL; i = i->next)
    {
        cout << i->data << endl;
    }
}

//outputs contents of the linked list into a string
template <class type>
void LinkedList<type>::printlist(string output)
{
    for (elements *i = head; i != NULL; i = i->next)
    {
        output += i->data;
        output += " ";
    }
}

//datatype declarations
template class LinkedList <int>;
template class LinkedList <float>;
template class LinkedList <string>;
