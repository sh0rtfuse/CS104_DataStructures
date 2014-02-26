//
//  main.cpp
//  HW6
//
//  Created by Raymond Dam on 10/27/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include <iostream>
#include "Wall.h"
#include "WallPost.h"
#include "User.h"
#include "UserList.h"
#include "List.h"

using namespace std;

//protypes
void welcomescreenNEW();
void welcomescreenOLD();
void login();
void newuser();
void loggedinmenu(string username, User theUser);

//run-time database
UserList theDatabase;

//load existing Database or create new one
void networksaving()
{
    int input = 0;
    
    do
    {
        cout << endl;
        cout << "**********************Database Options**********************" << endl;
        cout << endl;
        cout << "What would you like to do?" << endl;
        cout << "(Please enter the number for your choice and press enter)" << endl;
        cout << endl;
        cout << "1. Load existing database." << endl;
        cout << "2. Create a new database." << endl;
        cout << "3. Quit Program." << endl;
        cout << "User Entry: ";
        
        cin >> input;
    }
    while ((input != 0) && (input != 1) && (input != 2) && (input != 3));
    
    if (input == 1)
    {
        //reads in file "UserDatabase.txt"
        theDatabase.readDatabase();
        
        //call welcome screen
        welcomescreenOLD();
    }
    
    else if (input == 2)
    {
        //Database is already initialized as a Global Variable
        cout << endl;
        cout << "New Database prepping..." << endl;
        
        //call welcome screen
        welcomescreenNEW();
    }
    
    else if (input == 3)
    {
        cout << endl;
        cout << "Exiting..." << endl;
    }
}

void welcomescreenNEW()
{
    int input = 0;
    
    //Do...While loop for input verification
    do
    {
        cout << endl;
        cout << "**********************Welcome to the Social Network!**********************" << endl;
        cout << endl;
        cout << "What would you like to do?" << endl;
        cout << "(Please enter the number for your choice and press enter)" << endl;
        cout << endl;
        cout << "1. Create a new user." << endl;
        cout << "2. Quit Program." << endl;
        cout << "User Entry: ";
        
        cin >> input;
    }
    while ((input != 0) && (input != 1) && (input != 2) && (input != 3));
    
    if (input == 1)
    {
        newuser();
    }
    
    else if (input == 2)
    {
        cout << endl;
        cout << "Saving Database..." << endl;
        theDatabase.writeDatabase();
    }
}

void welcomescreenOLD()
{
    int input = 0;
    
    //Do...While loop for input verification
    do
    {
        cout << endl;
        cout << "**********************Welcome to the Social Network!**********************" << endl;
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
        login();
    }
    
    else if (input == 2)
    {
        newuser();
    }
    
    else if (input == 3)
    {
        cout << endl;
        cout << "Saving Database..." << endl;
        theDatabase.writeDatabase();
    }
}

void login()
{
    string user;
    
    cout << endl;
    cout << "Please enter your username, then press enter." << endl;
    cout << "User Entry: ";
    
    cin >> user;
    
    //search for name
    if (theDatabase.friendfinder(user) == user)
    {
        string password;
        
        cout << endl;
        cout << "Please enter your password, then press enter." << endl;
        cout << "User Entry: ";
        
        cin >> password;
        
        //password validation
        User theUser = theDatabase.getUser();
        
        if (theUser.getPassword() == password)
        {
            cout << endl;
            cout << "Password Correct! Logging in..." << endl;
            
            //call logged in menu
            loggedinmenu(user, theUser);
        }
    }
    
    else
    {
        cout << endl;
        cout << "Username and/or Password is incorrect." << endl;
        cout << "Please Try Again" << endl;
        
        //call welcomescreen
        welcomescreenOLD();
    }
}

void newuser()
{
    string yname, ypassword, ybirthday;
    
    cout << endl;
    cout << "***********************************Getting Started...*********************************" << endl;
    cout << endl;
    cout << "Please your name, a password, and your birthday in that order with a space in between." << endl;
    cout << "User Entry: ";
    
    cin >> yname >> ypassword >> ybirthday;
    
    User newUser;
    newUser.setName(yname);
    newUser.setPassword(ypassword);
    newUser.setBirthday(ybirthday);
    
    theDatabase.addUser(newUser);
    
    cout << endl;
    cout << "You're all set to go! Logging in..." << endl;
    
    //call logged in menu
    loggedinmenu(yname, newUser);
}

void loggedinmenu(string username, User theUser)
{
    int input = 0;
    do
    {
        cout << endl;
        cout << "**********************Logged in as " << username << "**********************" << endl;
        cout << endl;
        cout << "What would you like to do?" << endl;
        cout << "(Please enter the number for your choice and press enter)" << endl;
        cout << endl;
        cout << "1. Post to your Wall." << endl;
        cout << "2. Delete a Post." << endl;
        cout << "3. Find Friends." << endl;
        cout << "4. Log Out." << endl;
        cout << "User Entry: ";
        
        cin >> input;
    }
    while ((input != 0) && (input != 1) && (input != 2) && (input != 3) && (input != 4));
    
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
        
        wallpost temp;
        temp.newPost(post);
        temp.newDate(date);
        temp.newAuthor(username);
        
        theUser.setUserwall(temp);
        
        //call function again
        loggedinmenu(username, theUser);
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
        
        wallpost temp;
        if (temp.getPost() == input)
        {
            theUser.removeUserwall();
        }
        
        //call function again
        loggedinmenu(username, theUser);
    }
    
    else if (input == 3)
    {
        string input, useroutput;

        cout << endl;
        cout << "**********************Finding a Friend**********************" << endl;
        cout << "Please enter the friend you would like to find." << endl;
        cout << "User Entry: ";
        
        cin >> input;
        
        useroutput = theDatabase.friendfinder(input);
        
        //print out friends
        cout << endl;
        cout << useroutput << endl;
        
        //call function again
        loggedinmenu(username, theUser);
    }
    
    else if (input == 4)
    {
        cout << endl;
        cout << "Logging Out..." << endl;
        
        //call main menu
        welcomescreenOLD();
    }
}

int main ()
{
    //call first function
    networksaving();
    
    return 0;
}




/*
int main()
{
    wall mywall;
    wallpost mypost;
    
    string post = "Yoooo. Wasup Dawg?";
    string author = "Raymond";
    string date = "10/29/13";
    
    mypost.newPost(post);
    mypost.newAuthor(author);
    mypost.newDate(date);
    
    mywall.setWallpost(mypost);
    
    string output = mywall.writeWall();
    
    cout << output << endl;
    
    wall newwall;
    
    newwall.readWall(output);
    
    string output2 = newwall.writeWall();
    
    cout << output2 << endl;
    
    User test;
    User test2;
    
    string teststring = "Raymond Dam|qwerty|04/03/1993|Yoooo. Wasup Dawg?|Raymond|10/29/13|";
    string teststring2= "Lotso-Hugin'-Bear|toystory|02/12/1990|Nm. Just emotionally damaged. :(|Lotso|10/30/13|";
    
    test.readUser(teststring);
    test2.readUser(teststring2);
    
    string output3 = test.writeUser();
    
    cout << output3 << endl;
    
    UserList network;
    
    network.addUser(test);
    network.addUser(test2);
    
    network.writeDatabase();
    
    network.readDatabase();
    
    User result, result2;
    
    result = network.getUser();
    
    network.removeUser();
    
    result2 = network.getUser();
    
    string print = result.writeUser();
    string print2 = result2.writeUser();
    
    cout << print << endl;
    cout << print2 << endl;
    
    return 0;
}
*/


