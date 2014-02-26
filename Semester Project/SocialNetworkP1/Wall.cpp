//
//  Wall.cpp
//  Social Network
//
//  Created by Raymond Dam on 9/22/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "Wall.h"

#include <iostream>
#include <sstream>
#include "LinkedListTemplate.h"
#include "WallPost.h"

using namespace std;

wall::wall ()
{
    LinkedList<string> thewall;
}

wall::~wall ()
{
    
}

void wall::addwallpost(string post, string name, string date)
{
    wallpost wall;
    
    //call setter functions to store components of the post
    wall.newpost(post);
    wall.newauthor(name);
    wall.newdate(date);
    
    //combine them into one string, then add them to the list of wallposts
    string completepost;
    wall.printpost(completepost);
    thewall.add(completepost);
}

void wall::removewallpost(string wallpost)
{
    //check if the wallpost user wants to delete exists
    bool search = thewall.find(wallpost);
    
    //if yes, then go ahead and remove
    if (search == true)
    {
        thewall.remove(wallpost);
    }
    
    //if not, return error
    else
    {
        cout << "Sorry, the post you want to delete does not exist" << endl;
    }
}

//prints out all the wallposts
void wall::printwall(string output)
{
    thewall.printlist(output);
}

void wall::readinwall(string input)
{
    //turns the temp string into a stream
    istringstream stream(input);
    
    while (!stream.eof())
    {
        string parse;
    
        //parses the temp string stream and stores each element
        //separated by a space as an element in the list
        getline(stream, parse, ' ');
        
        //add the element parsed from the string into the list
        thewall.add(parse);
    }
}



