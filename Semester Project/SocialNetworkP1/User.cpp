//
//  User.cpp
//  Social Network
//
//  Created by Raymond Dam on 9/22/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "User.h"

#include <iostream>
#include <sstream>
#include "Wall.h"

using namespace std;

user::user ()
{
    wall userwall;
}

user::~user()
{
    //delete stuff
}

//setter functions
void user::editname(string input)
{
    name = input;
}

void user::editpassword(string input)
{
    password = input;
}

void user::editbirthday(string input)
{
    birthday = input;
}

//adds all of users wallposts into a list that makes up the wall
//name is taken from private variable to ensure same user
void user::posttowall(string post, string date)
{
    userwall.addwallpost(post, name, date);
}

//remove a wallpost from the wall
void user::deletefromwall(string posttodelete)
{
    userwall.removewallpost(posttodelete);
}

//combines user data into one string
void user::printuserinfo(string output)
{
    output += name;
    output += " ";
    output += password;
    output += " ";
    output += birthday;
}

void user::readinuserdata(string input)
{
    //reading user data as soon as class is called
    //turns the temp string into a stream
    istringstream stream(input);
    
    //parses the temp string stream and stores each element in a private variable
    getline(stream, name, ' ');
    getline(stream, password, ' ');
    getline(stream, birthday, ' ');
}
