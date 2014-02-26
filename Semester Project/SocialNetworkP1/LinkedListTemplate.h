//
//  LinkedListTemplate.h
//  Social Network
//
//  Created by Raymond Dam on 9/22/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef LINKEDLISTTEMPLATE_H
#define LINKEDLISTTEMPLATE_H

#include <iostream>

using namespace std;

template <class type>
class LinkedList
{
    private:
        struct elements                                                     //handles items in the list
        {
            type data;
        
            elements *next, *previous;
        };
    
        elements *head, *tail;
    
        void removehelper (elements *temp);                                 //helper function for public remove functon

    public:
        LinkedList();                                                       //constructor: initiates pointers to null
        ~LinkedList();
    
        void add (const type input);                                        //add/remove elements
        void remove (const type input);                                     //NOTE: Will remove +1 element from what you specify
    
        bool find (const type input);                                       //functions to manipulate linked list
    
        void testprintlist ();                                              //printout list contents to command line
        void printlist (string output);                                     //outputs the full contents of the list into a string
};

//#include "LinkedListTemplate.cpp"

#endif
