//
//  main.cpp
//  Social Network
//
//  Created by Raymond Dam on 9/22/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>

#include "LinkedListTemplate.h"
#include "WallPost.h"
#include "Wall.h"
#include "User.h"
#include "UserList.h"

using namespace std;

void loggedin (string user)
{
    int input = 0;
    
    //display wall posts
    cout << endl;
    cout << user << "'s Wall:" << endl;
    
    userlist U3;
    U3.printall();
    
    //declare classes
    wall W;
    
    do
    {
        //logged in prompt
        cout << endl;
        cout << "**********************Logged in as " << user << "**********************" << endl;
        cout << endl;
        cout << "What would you like to do?" << endl;
        cout << "(Please enter the number for your choice and press enter)" << endl;
        cout << endl;
        cout << "1. Post to your Wall." << endl;
        cout << "2. Delete a Post." << endl;
        cout << "3. Log Out." << endl;
        cout << "User Entry: ";
        
        cin >> input;
    }
    while ((input != 0) && (input != 1) && (input != 2) && (input != 3));
    
    if (input == 1)
    {
        string post, date;
        
        //new wallpost prompt
        cout << endl;
        cout << "**********************New Wall Post**********************" << endl;
        cout << "Please enter your post." << endl;
        cout << "User Entry: ";
        
        cin >> post;
        
        cout << endl;
        cout << "Please enter the date." << endl;
        cout << "User Entry: ";
        
        cin >> date;
        
        //Add as a wall post and print
        W.addwallpost(post, user, date);
        
        string display;
        W.printwall(display);
        
        //call function again
        loggedin(user);
    }
    
    else if (input == 2)
    {
        string input;
        
        //delete wallpost prompt
        cout << endl;
        cout << "**********************Delete Wall Post**********************" << endl;
        cout << "Please enter the post you would like to delete." << endl;
        cout << "User Entry: ";
        
        cin >> input;
        
        //Delete Wall Post
        W.removewallpost(input);
        
        //call function again
        loggedin(user);
    }
    
    else if (input == 3)
    {
        //save everything to a file
        U3.printall();
        
        //program exits
    }
}

void newuser ()
{
    string name, password, birthday;
    
    //new user prompt
    cout << endl;
    cout << "**********************Creating a New Account**********************" << endl;
    cout << "Please your name, a password, and your birthday in that order with a space in between." << endl;
    cout << "User Entry: ";
    
    cin >> name >> password >> birthday;
    
    //add to UserList
    userlist U2;
    U2.adduser(name, password, birthday);
    
    //save it all to a file
    U2.printall();
    
    //notify user
    cout << endl;
    cout << "New account has been created!" << endl;;
}

int main ()
{
    //read in user file
    string inputfile = "userin.txt";
    string temp;
    ifstream filein(inputfile.c_str());
    
    //use getline to grab each row of the network file and store in temp
    getline(filein, temp);
    
    userlist U;
    
    U.loadall(temp);
    
    //Menu
    int input = 0;
    
    //Do...While loop for input verification
    do
    {
        cout << endl;
        cout << "**********************Welcome to Ye Olde Social Network!**********************" << endl;
        cout << endl;
        cout << "What would you like to do?" << endl;
        cout << "(Please enter the number for your choice and press enter)" << endl;
        cout << endl;
        cout << "1. Log in as an existing user." << endl;
        cout << "2. Create a new user." << endl;
        cout << "3. Quit Program." << endl;
        cout << "User Entry: ";
    
        cin >> input;
    }
    while ((input != 0) && (input != 1) && (input != 2) && (input != 3));
    
    if (input == 1)
    {
        string user;
        
        cout << endl;
        cout << "Please enter your username, then press enter." << endl;
        cout << "User Entry: ";
        
        cin >> user;
        
        //check to see if user name exists.
        bool searchresult = U.usersearch(user);
        
        //if yes, call logged in function
        if (searchresult == true)
        {
            //call loggedin function
            loggedin(user);
        }
        
        else
        {
            //error message
            cout << endl;
            cout << "This user does not exist. Please try again." << endl;
        }
    }
    
    else if (input == 2)
    {
        //call newuser function
        newuser();
    }
    
    else if (input == 3)
    {
        return 0;
    }
    
    return 0;
}

/*
int main()
{
    LinkedList<int> test;
    
    for (int i = 0; i < 10; i++)
    {
        test.add(i);
    }
    
    cout << endl;
    
    string input = "This is going to be ";
    string input2 = "a long night.";
    
    input += input2;
    
    cout << input << endl;
    
    cout << endl;
    
    bool value = test.find(2);
    
    cout << endl;
    cout << value << endl;
    cout << endl;
    
    test.testprintlist();
    
    return 0;
}
*/
