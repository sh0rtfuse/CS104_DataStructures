//
//  main.cpp
//  HW8
//
//  Created by Raymond Dam on 11/7/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <ctime>
#include <chrono>
#include <thread>
#include <list>
#include <string>

#include "Wall.h"
#include "User.h"
#include "UserList.h"
#include "Sorting.h"
#include "md5.h"

using namespace std;

//prototypes
void welcomescreen();
void login();
void newuser();
void loggedinmenu(User theUser);
void friendprofile(User theUser, User Friend);
int NetworkSearch(string SearchFor, User theUser, string results);

//run-time database
UserList theDatabase;

//tracks number of calls made to print out default wall
int callcount = 0;

//load existing Database or create new one
void loadDatabase()
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
        cout << "2. Quit Program." << endl;
        cout << "User Entry: ";
        
        cin >> input;
    }
    while ((input != 0) && (input != 1) && (input != 2));
    
    if (input == 1)
    {
        //reads in file "UserDatabase.txt"
        theDatabase.readDatabase();
        
        //call welcome screen
        welcomescreen();
    }
    
    else if (input == 2)
    {
        cout << endl;
        cout << "Exiting..." << endl;
    }
    
    else
    {
        loadDatabase();
    }
}

void welcomescreen()
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
    
    else
    {
        welcomescreen();
    }
}

void login()
{
    string user;
    
    cout << endl;
    cout << "Please enter your username, then press enter." << endl;
    cout << "User Entry: ";
    
    cin >> user;
    
    //get user from database
    User input = theDatabase.getUser2(user);
    
    //search for name
    if (input.getUsername() == user)
    {
        string password;
        
        cout << endl;
        cout << "Please enter your password, then press enter." << endl;
        cout << "User Entry: ";
        
        cin >> password;
        
        //HW11: Hash User Entry and compare to hash on file
        auto hash = md5(password.c_str(), password.size() * sizeof(char));
        stringstream key;
        key << hash;
        string pw_hash = key.str();
        
        //password validation
        User theUser = theDatabase.getUser2(user);
        
        if (theUser.getPassword() == pw_hash)
        {
            cout << endl;
            cout << "Password Correct! Logging in..." << endl;
            
            //call logged in menu
            loggedinmenu(theUser);
        }
        
        else
        {
            cout << endl;
            cout << "Username and/or Password is incorrect." << endl;
            cout << "Please Try Again" << endl;
            
            //call welcomescreen
            welcomescreen();
        }
    }
    
    else
    {
        cout << endl;
        cout << "Username and/or Password is incorrect." << endl;
        cout << "Please Try Again" << endl;
        
        //call welcomescreen
        welcomescreen();
    }
}

void newuser()
{
    string yname, ypassword, ybirthday, yusername;
    
    cout << endl;
    cout << "***********************************Getting Started...*********************************" << endl;
    cout << endl;
    cout << "Please enter your username (no spaces): ";
    cin >> yusername;
    cout << "Please enter your name (no spaces): ";
    cin >> yname;
    cout << "Please enter your password (no spaces): ";
    cin >> ypassword;
    cout << "Please enter your birthday (no spaces): ";
    cin >> ybirthday;
    
    //HW11: make sure that the username is unique
    list<User> DatabaseList = theDatabase.getUserDatabase();
    for (list<User>::iterator DatabaseList_iter = DatabaseList.begin(); DatabaseList_iter != DatabaseList.end(); DatabaseList_iter++)
    {
        User oldUsers = *DatabaseList_iter;
        
        if (yusername == oldUsers.getUsername())
        {
            cout << endl;
            cout << "oops! " << yusername << " has already been taken. Please try again." << endl;
            
            newuser();
        }
    }
    
    //HW11: Hash new pw before storage
    auto hash = md5(ypassword.c_str(), ypassword.size() * sizeof(char));
    
    stringstream key;
    key << hash;
    
    string pw_hash = key.str();
    
    User newUser;
    newUser.setUsername(yusername);
    newUser.setName(yname);
    newUser.setPassword(pw_hash);
    newUser.setBirthday(ybirthday);
    
    theDatabase.addUser(newUser);
    
    cout << endl;
    cout << "You're all set to go! Logging in..." << endl;
    
    //call logged in menu
    loggedinmenu(newUser);
}

//Shows the wall of a given user
void DefaultWall(User theUser, int callcount)
{
    cout << endl;
    cout << "**********************" << theUser.getName() << "'s Wall**********************" << endl;
    cout << endl;
    
    //printout User's Wall
    wall theWall = theUser.getUserwall();
    
    std::list <wallpost> ListofWallposts = theWall.gettheWall();
    
    //iterate through printing out wallposts
    for (std::list<wallpost>::iterator ListofWallposts_iter = ListofWallposts.begin(); ListofWallposts_iter != ListofWallposts.end(); ListofWallposts_iter++)
    {
        wallpost printWallpost = *ListofWallposts_iter;
        
        if (!printWallpost.empty())
        {
            //Pretty formatting
            cout << endl;
            cout << "From " << printWallpost.getAuthor() << " to " << theUser.getName() << endl;
            cout << "Date: " <<printWallpost.getDate() << endl;
            cout << "Post: " << printWallpost.getPost() << endl;
            cout << endl;
        }
        
        std::list <wallpostcomment> ListofComments = printWallpost.getComments();
        for (std::list<wallpostcomment>::iterator ListofComments_iter = ListofComments.begin(); ListofComments_iter != ListofComments.end(); ListofComments_iter++)
        {
            wallpostcomment printComment = *ListofComments_iter;
            
            if (!printComment.empty())
            {
                cout << "       Comments" << endl;
                cout << "           Author: " << printComment.getAuthor() << endl;
                cout << "           Post: " << printComment.getComment() << endl;
            }
        }
    }
    
    //tracks number of calls made to this function
    callcount++;
}

//logged in User's wall
void Userwall(User theUser, string LoginAs)
{
    if (callcount == 0)
    {
        DefaultWall(theUser, callcount);
    }
    
    int input = 0;
    do
    {
        cout << endl;
        cout << "************************************* Menu **************************************" << endl;
        cout << "What would you like to do?" << endl;
        cout << "(Please enter the number for your choice and press enter)" << endl;
        cout << endl;
        cout << "1. Show my most recent wallposts." << endl;
        cout << "2. Show past activity (wallposts and comments)" << endl;
        cout << "3. Make a Wallpost." << endl;
        cout << "4. Make a Comment." << endl;
        cout << "5. Delete a Wallpost." << endl;         //implement check: delete your own posts/comments, delete anything if your own wall
        cout << "6. Delete a Comment." << endl;
        cout << "7. Back." << endl;
        cout << "User Entry: ";
        
        cin >> input;
    }
    while ((input != 0) && (input != 1) && (input != 2) && (input != 3) && (input != 4) && (input != 5) && (input != 6) && (input != 7));
    
    if (input == 1)
    {
        cout << endl;
        cout << "*************" << theUser.getName() << "'s Most Recent Wallposts************" << endl;
        cout << endl;
        
        //sort the user's wallposts
        Sort Sorted(theUser, false);
        std::list <wallpost> SortedWall = Sorted.OrderedResults();
        for (std::list<wallpost>::iterator SortedWall_iter = SortedWall.begin(); SortedWall_iter != SortedWall.end(); SortedWall_iter++)
        {
            wallpost SortedWallpost = *SortedWall_iter;
            
            if (!SortedWallpost.empty())
            {
                cout << endl;
                cout << "From " << SortedWallpost.getAuthor() << "to " << theUser.getName() << endl;
                cout << "Date: " << SortedWallpost.getDate() << endl;
                cout << "Post: " << SortedWallpost.getPost() << endl;
                cout << endl;
            }
        }
        
        callcount++;
        Userwall(theUser, LoginAs);
    }
    
    else if (input == 2)
    {
        cout << endl;
        cout << "*************" << theUser.getName() << "'s Recent Activities ************" << endl;
        cout << endl;
        
        //sort the user's wallposts and comments
        Sort Sorted(theUser, true);
        std::list <wallpost> SortedWall = Sorted.OrderedResults();
        int order = 0;
        
        for (std::list<wallpost>::iterator SortedWall_iter = SortedWall.begin(); SortedWall_iter != SortedWall.end(); SortedWall_iter++)
        {
            wallpost SortedWallpost = *SortedWall_iter;
            
            //if wallpost is in the right order, than printout
            if (SortedWallpost.getOrder() == order)
            {
                if (!SortedWallpost.empty())
                {
                    cout << endl;
                    cout << "From " << SortedWallpost.getAuthor() << "to " << theUser.getName() << endl;
                    cout << "Date: " << SortedWallpost.getDate() << endl;
                    cout << "Post: " << SortedWallpost.getPost() << endl;
                    cout << endl;
                    
                    order++;
                }
            }
            
            //if comment is in the right order, then printout
            std::list <wallpostcomment> SortedComments = SortedWallpost.getComments();
            for (std::list<wallpostcomment>::iterator SortedComments_iter = SortedComments.begin(); SortedComments_iter != SortedComments.end(); SortedComments_iter++)
            {
                wallpostcomment printComment;
                
                if (printComment.getOrder() == order)
                {
                    if (!printComment.empty())
                    {
                        cout << "       Comments" << endl;
                        cout << "           Author: " << printComment.getAuthor() << endl;
                        cout << "           Post: " << printComment.getComment() << endl;
                        cout << endl;
                        
                        order++;
                    }
                }
            }
        }
        
        callcount++;
        Userwall(theUser, LoginAs);
    }
    
    else if (input == 3)
    {
        string post;
        wallpost NewPost;
        
        cout << endl;
        cout << "************* Post on " << theUser.getName() << "'s Wall************" << endl;
        cout << endl;
        cout << "Please Enter your message: ";
        cin >> post;
        
        NewPost.newPost(post);
        NewPost.newAuthor(LoginAs);
        NewPost.setDateandTime();
        
        theUser.setUserwall(NewPost);
        
        //update user
        cout << endl;
        cout << "Wallpost Submitted!" << endl;
        
        callcount++;
        Userwall(theUser, LoginAs);
    }
    
    else if (input == 4)
    {
        //prints out all wallposts and comments of the user
        DefaultWall(theUser, callcount);
        string choice;
        
        cout << endl;
        cout << "************************************************************************" << endl;
        cout << "Please Enter the author of the post you would like to comment on." << endl;
        cout << "User Entry: ";
        cin >> choice;
        
        //finds the right wallpost
        std::list <wallpost> UserWallposts = theUser.getUserwall().gettheWall();
        for (std::list<wallpost>::iterator UserWallposts_iter = UserWallposts.begin(); UserWallposts_iter != UserWallposts.end(); UserWallposts_iter++)
        {
            wallpost temp = *UserWallposts_iter;
            
            if (choice == temp.getAuthor())
            {
                //set comment for that wallpost
                wallpostcomment temp2;
                
                //make a comment
                string post;
                cout << endl;
                cout << "****************************** Make a Comment********************************" << endl;
                cout << "Please Enter your message: ";
                cin >> post;
                
                temp2.setCommentPost(post);
                temp2.setAuthor(LoginAs);
                temp2.setTime();
                
                //add to selected wallpost
                temp.setComment(temp2);
                
                //update user
                cout << endl;
                cout << "Comment Submitted!" << endl;
            }
        }
        
        callcount++;
        Userwall(theUser, LoginAs);
    }
    
    else if (input == 5)
    {
        //prints out all wallposts and comments of the user
        DefaultWall(theUser, callcount);
        string choice;
        
        cout << endl;
        cout << "************************************************************************" << endl;
        cout << "Please Enter the author of the wallpost you would like to delete." << endl;
        cout << "User Entry: ";
        cin >> choice;
        
        //if you are on your own wall = you can delete any wallpost
        if (LoginAs == theUser.getName())
        {
            theUser.removeUserwall(choice);
            
            //update user
            cout << endl;
            cout << "Wallpost Deleted." << endl;
        }
        
        //if not, you can only delete your posts
        else
        {
            //go thru user's wallposts to find only the one made by you
            std::list <wallpost> UserWallposts = theUser.getUserwall().gettheWall();
            for (std::list<wallpost>::iterator UserWallposts_iter = UserWallposts.begin(); UserWallposts_iter != UserWallposts.end(); UserWallposts_iter++)
            {
                wallpost temp = *UserWallposts_iter;
                
                if (LoginAs == temp.getAuthor())
                {
                    theUser.removeUserwall(choice);
                    
                    //update user
                    cout << endl;
                    cout << "Wallpost Deleted." << endl;
                }
            }
        }
        
        callcount++;
        Userwall(theUser, LoginAs);
    }
    
    else if (input == 6)
    {
        //prints out all wallposts and comments of the user
        DefaultWall(theUser, callcount);
        string choice;
        
        cout << endl;
        cout << "************************************************************************" << endl;
        cout << "Please Enter the author of the comment you would like to delete." << endl;
        cout << "User Entry: ";
        cin >> choice;
        
        if (LoginAs == theUser.getName())
        {
            std::list <wallpost> UserWallposts = theUser.getUserwall().gettheWall();
            for (std::list<wallpost>::iterator UserWallposts_iter = UserWallposts.begin(); UserWallposts_iter != UserWallposts.end(); UserWallposts_iter++)
            {
                wallpost temp = *UserWallposts_iter;
                
                temp.removeComment(choice);
            }
        }
        
        else
        {
            std::list <wallpost> UserWallposts = theUser.getUserwall().gettheWall();
            for (std::list<wallpost>::iterator UserWallposts_iter = UserWallposts.begin(); UserWallposts_iter != UserWallposts.end(); UserWallposts_iter++)
            {
                wallpost temp = *UserWallposts_iter;
                
                std::list <wallpostcomment> ListofComments = temp.getComments();
                for (std::list<wallpostcomment>::iterator ListofComments_iter = ListofComments.begin(); ListofComments_iter != ListofComments.end(); ListofComments_iter++)
                {
                    wallpostcomment temp2 = *ListofComments_iter;
                    
                    if (LoginAs == temp2.getAuthor())
                    {
                        temp.removeComment(choice);
                    }
                }
            }
        }
        
        callcount++;
        Userwall(theUser, LoginAs);
    }
    
    else if (input == 7)
    {
        //save changes
        theDatabase.UpdateUser(theUser);
        
        //reset callcout for next user wall
        callcount = 0;
        
        //call logginmenu menu
        loggedinmenu(theUser);
    }
    
    else
    {
        callcount++;
        Userwall(theUser, LoginAs);
    }
}

//logged in User's Profile
void loggedinmenu(User theUser)
{
    int input = 0;
    do
    {
        cout << endl;
        cout << "**********************Logged in as " << theUser.getName() << "**********************" << endl;
        cout << endl;
        cout << "What would you like to do?" << endl;
        cout << "(Please enter the number for your choice and press enter)" << endl;
        cout << endl;
        cout << "1. Go to your wall." << endl;
        cout << "2. Show my friends." << endl;              //give option to access their wall; confirm if friend before granting access
        cout << "3. Network Search." << endl;               //give option to make friend request
        cout << "4. Pending Friend Requests" << endl;       //users confirm or deny friend requests
        cout << "5. Remove a friend." << endl;
        cout << "6. Degrees of Separation." << endl;
        cout << "7. I'm feel like meeting someone new..." << endl;
        cout << "8. Log Out." << endl;
        cout << "User Entry: ";
        
        cin >> input;
    }
    while ((input != 0) && (input != 1) && (input != 2) && (input != 3) && (input != 4) && (input != 5) && (input != 6) && (input != 7) && (input != 8));
    
    if (input == 1)
    {
        Userwall(theUser, theUser.getName());
    }
    
    else if (input == 2)
    {
        string friendslist = theUser.getfriends();
        
        cout << endl;
        cout << "***********************" << theUser.getName() << "'s Friends ************************" << endl;
        cout << endl;
        cout << friendslist << endl;
        
        //Give option to access a friend's wall
        string yesorno;
        cout << endl;
        cout << "Would you like to go to your friend's profile? (yes or no)" << endl;
        cout << "User Entry: ";
        cin >> yesorno;
        
        if (yesorno == "yes")
        {
            string name;
            cout << endl;
            cout << "Please Enter your friend's name." << endl;
            cout << "User Entry: ";
            cin >> name;
            
            //confirm that person is your friend
            std::list <string> friends = theUser.FriendsList();
            for (std::list<string>::iterator friends_iter = friends.begin(); friends_iter != friends.end(); friends_iter++)
            {
                string temp = *friends_iter;
                
                if (temp == name)
                {
                    cout << endl;
                    cout << "Taking you to " << name << "'s profile..." << endl;
                
                    User yourFriend = theDatabase.getUser(name);
                    
                    friendprofile(theUser, yourFriend);
                }
            }
            
            //update user
            cout << endl;
            cout << "Sorry, the person you entered is not registered or not your friend." << endl;
            loggedinmenu(theUser);
        }
        
        else if (yesorno == "no")
        {
            loggedinmenu(theUser);
        }
        
        else
        {
            loggedinmenu(theUser);
        }
    }
    
    else if (input == 3)
    {
        int searchoption = 0;
        string searchquery;
        bool choice = true;
        
        do
        {
            cout << endl;
            cout << "Search Options: Pick one." << endl;
            cout << "(Please enter the number for your choice and press enter)" << endl;
            cout << endl;
            cout << "1. By Username" << endl;
            cout << "2. By Name" << endl;
            cout << "User Entry: ";
            cin >> searchoption;
        }
        while ((searchoption != 0) && (searchoption != 1) && (searchoption != 2));
        
        if (searchoption == 1)
        {
            choice = true;
            
            cout << endl;
            cout << "Please Enter a username to search for users in the network." << endl;
            cout << "User Entry: ";
            cin >> searchquery;
        }
        
        else if (searchoption == 2)
        {
            choice = false;
            
            cout << endl;
            cout << "Please Enter a name to search for users in the network." << endl;
            cout << "User Entry: ";
            cin >> searchquery;
        }
        
        else
        {
            cout << endl;
            cout << "Error. Please Try Again." << endl;
            
            loggedinmenu(theUser);
        }
        
        //perform search
        string results = theDatabase.HashDatabaseSearch(searchquery, choice);
        cout << endl;
        cout << "Searching..." << endl;
        
        if (results.empty())
        {
            cout << endl;
            cout << "Sorry, there are no users with the name matching your entry." << endl;
            loggedinmenu(theUser);
        }
        
        else
        {
            cout << endl;
            cout << "Results:" << endl;
            cout << results << endl;
            
            //Give option to add as a friend
            string yesorno;
            cout << endl;
            cout << "Would you like to add one of the users above as a friend? (yes or no)" << endl;
            cout << "User Entry: ";
            cin >> yesorno;
            
            if (yesorno == "yes")
            {
                string newfriend;
                cout << endl;
                cout << "Please Enter the name of the user you wish to add as a friend." << endl;
                cout << "User Entry: ";
                cin >> newfriend;
                
                //check to see if user is already a friend
                std::list <string> friends = theUser.FriendsList();
                for (std::list<string>::iterator friends_iter = friends.begin(); friends_iter != friends.end(); friends_iter++)
                {
                    string temp = *friends_iter;
                    
                    if (temp == newfriend)
                    {
                        cout << endl;
                        cout << "Error. " << newfriend << " is already your friend" << endl;
                        
                        loggedinmenu(theUser);
                    }
                }
                
                //find user from database
                User potentialfriend = theDatabase.getUser(newfriend);
                
                //add logged in your to newuser's pending friends list
                potentialfriend.setpendingfriend(theUser.getName());
                
                //update database
                theDatabase.UpdateUser(potentialfriend);
                
                //update user
                cout << endl;
                cout << "Friend request pending..." << endl;
                
                loggedinmenu(theUser);
            }
            
            else if (yesorno == "no")
            {
                loggedinmenu(theUser);
            }
            
            else
            {
                loggedinmenu(theUser);
            }
        }
    }
    
    else if (input == 4)
    {
        //get pendingfriends list
        std::list <string> pendingfriends = theUser.PendingFriendsList();
        
        cout << endl;
        cout << theUser.getName() << ", you currently have " << pendingfriends.size() << " pending friend requests." << endl;
        cout << endl;
        cout << "Pending Requests: " << theUser.getpendingfriends() << endl;
        
        int submenu = 0;
        do
        {
            cout << endl;
            cout << "What would you like to do?" << endl;
            cout << "(Please enter the number for your choice and press enter)" << endl;
            cout << endl;
            cout << "1. Accept a friend request." << endl;
            cout << "2. Reject a friend request." << endl;
            cout << "3. Ignore requests." << endl;
            cout << "User Entry: ";
            cin >> submenu;
        }
        
        while ((submenu != 0) && (submenu != 1) && (submenu != 2) && (submenu != 3));
        
        if (submenu == 1)
        {
            string accept;
            cout << endl;
            cout << "Please Enter the name of a user listed above who has requested your friendship." << endl;
            cout << "User Entry: ";
            cin >> accept;
            
            //add as a friend to both users
            theUser.addfriend(accept);
            User temp = theDatabase.getUser(accept);
            temp.addfriend(theUser.getName());
            theDatabase.UpdateUser(temp);
            
            //remove friend from the pending list
            theUser.removependingfriend(accept);
            
            //update user
            cout << endl;
            cout << "Friend added. Returned to menu..." << endl;
            
            loggedinmenu(theUser);
        }
        
        else if (submenu == 2)
        {
            string reject;
            cout << endl;
            cout << "Please Enter the name of a user listed above who has requested your friendship." << endl;
            cout << "User Entry: ";
            cin >> reject;
            
            //remove friend from pending list
            theUser.removependingfriend(reject);
            
            //update user
            cout << endl;
            cout << "Request rejected. Returned to menu..." << endl;
            
            loggedinmenu(theUser);
        }
        
        else if (submenu == 3)
        {
            loggedinmenu(theUser);
        }
        
        else
        {
            loggedinmenu(theUser);
        }
    }
    
    else if (input == 5)
    {
        string remove;
        bool found = false;
        
        cout << endl;
        cout << "Please Enter the name of a user who you would like to unfriend." << endl;
        cout << "User Entry: ";
        cin >> remove;
        
        //confirm that person is your friend
        std::list <string> friends = theUser.FriendsList();
        for (std::list<string>::iterator friends_iter = friends.begin(); friends_iter != friends.end(); friends_iter++)
        {
            string temp = *friends_iter;
            
            if (temp == remove)
            {
                //remove friends from both user
                theUser.unfriend(remove);
                User notFriends = theDatabase.getUser(remove);
                notFriends.unfriend(theUser.getName());
                
                //update user
                cout << endl;
                cout << "You are no longer friends with " << remove << " returning to menu..." << endl;
                
                found = true;
            }
        }
        
        if (found == false)
        {
            //update user
            cout << endl;
            cout << "Sorry, the person you entered is not registered or not your friend..." << endl;
        }
    
        loggedinmenu(theUser);
    }
    
    else if (input == 6)
    {
        string input, results;
        cout << endl;
        cout << "Degrees of Separation: How far are you from someone else in the network?" << endl;
        cout << "Please Enter a name: ";
        cin >> input;
        
        int Degree = NetworkSearch(input, theUser, results);
        
        cout << endl;
        cout << "Result: " << results << endl;
        cout << "Degree(s): " << Degree << endl;
        
        loggedinmenu(theUser);
    }
    
    else if (input == 7)
    {
        list<User> allUsers = theDatabase.getUserDatabase();
        
        srand(time(NULL));
        int num = rand() % allUsers.size();
        
        list<User>::iterator allUsers_iter = allUsers.begin();
        
        for (int i = 0; i < num; i++)
        {
            allUsers_iter++;
        }
        
        User rand_User = *allUsers_iter;
        
        cout << endl;
        cout << rand_User.getName() << ". Added as a Friend." << endl;
        theUser.addfriend(rand_User.getName());
        rand_User.addfriend(theUser.getName());
        
        cout << "Oh... Looks like you're being taken to " << rand_User.getName() << "'s profile..." << endl;
        
        friendprofile(theUser, rand_User);
    }
    
    else if (input == 8)
    {
        cout << endl;
        cout << "Logging Out..." << endl;
        
        //save changes
        theDatabase.UpdateUser(theUser);
        
        //call main menu
        welcomescreen();
    }
    
    else
    {
        welcomescreen();
    }
}

//visiting a friend
void friendprofile(User theUser, User Friend)
{
    int input = 0;
    do
    {
        cout << endl;
        cout << "******************************* " << Friend.getName() << "'s Profile*******************************" << endl;
        cout << "User: " << theUser.getName() << endl;
        cout << endl;
        cout << "What would you like to do?" << endl;
        cout << "(Please enter the number for your choice and press enter)" << endl;
        cout << endl;
        cout << "1. Show " << Friend.getName() << "'s recent wallposts." << endl;
        cout << "2. Show " << Friend.getName() << "'s past activity (wallposts and comments)" << endl;
        cout << "3. Make a Wallpost." << endl;
        cout << "4. Make a Comment." << endl;
        cout << "5. Delete a Wallpost." << endl;
        cout << "6. Delete a Comment." << endl;
        cout << "7. Back your own profile." << endl;
        cout << "User Entry: ";
        
        cin >> input;
    }
    while ((input != 0) && (input != 1) && (input != 2) && (input != 3) && (input != 4) && (input != 5) && (input != 6) && (input != 7));
    
    if (input == 1)
    {
        cout << endl;
        cout << "*************" << Friend.getName() << "'s Most Recent Wallposts************" << endl;
        cout << endl;
        
        //sort the friend's wallposts
        Sort Sorted(Friend, false);
        std::list <wallpost> SortedWall = Sorted.OrderedResults();
        for (std::list<wallpost>::iterator SortedWall_iter = SortedWall.begin(); SortedWall_iter != SortedWall.end(); SortedWall_iter++)
        {
            wallpost SortedWallpost = *SortedWall_iter;
            
            if (!SortedWallpost.empty())
            {
                cout << endl;
                cout << "From " << SortedWallpost.getAuthor() << "to " << Friend.getName() << endl;
                cout << "Date: " << SortedWallpost.getDate() << endl;
                cout << "Post: " << SortedWallpost.getPost() << endl;
                cout << endl;
            }
        }
        
        friendprofile(theUser, Friend);
    }
    
    else if (input == 2)
    {
        cout << endl;
        cout << "*************" << Friend.getName() << "'s Recent Activities ************" << endl;
        cout << endl;
        
        //sort the user's wallposts and comments
        Sort Sorted(Friend, true);
        std::list <wallpost> SortedWall = Sorted.OrderedResults();
        int order = 0;
        
        for (std::list<wallpost>::iterator SortedWall_iter = SortedWall.begin(); SortedWall_iter != SortedWall.end(); SortedWall_iter++)
        {
            wallpost SortedWallpost = *SortedWall_iter;
            
            //if wallpost is in the right order, than printout
            if (SortedWallpost.getOrder() == order)
            {
                if (!SortedWallpost.empty())
                {
                    cout << endl;
                    cout << "From " << SortedWallpost.getAuthor() << "to " << Friend.getName() << endl;
                    cout << "Date: " << SortedWallpost.getDate() << endl;
                    cout << "Post: " << SortedWallpost.getPost() << endl;
                    cout << endl;
                    
                    order++;
                }
            }
            
            //if comment is in the right order, then printout
            std::list <wallpostcomment> SortedComments = SortedWallpost.getComments();
            for (std::list<wallpostcomment>::iterator SortedComments_iter = SortedComments.begin(); SortedComments_iter != SortedComments.end(); SortedComments_iter++)
            {
                wallpostcomment printComment;
                
                if (printComment.getOrder() == order)
                {
                    if (!printComment.empty())
                    {
                        cout << "       Comments" << endl;
                        cout << "           Author: " << printComment.getAuthor() << endl;
                        cout << "           Post: " << printComment.getComment() << endl;
                        cout << endl;
                        
                        order++;
                    }
                }
            }
        }
        
        friendprofile(theUser, Friend);
    }
    
    else if (input == 3)
    {
        string post;
        wallpost NewPost;
        
        cout << endl;
        cout << "************* Post on " << Friend.getName() << "'s Wall************" << endl;
        cout << "User: " << theUser.getName() << endl;
        cout << endl;
        cout << "Please Enter your message: ";
        cin >> post;
        
        NewPost.newPost(post);
        NewPost.newAuthor(theUser.getName());
        NewPost.setDateandTime();
        
        theUser.setUserwall(NewPost);
        
        //update user
        cout << endl;
        cout << "Wallpost Submitted!" << endl;
        
        friendprofile(theUser, Friend);
    }
    
    else if (input == 4)
    {
        //prints out all wallposts and comments of the user
        DefaultWall(Friend, callcount);
        string choice;
        
        cout << endl;
        cout << "************************************************************************" << endl;
        cout << "Please Enter the author of the post you would like to comment on." << endl;
        cout << "User Entry: ";
        cin >> choice;
        
        //finds the right wallpost
        std::list <wallpost> UserWallposts = Friend.getUserwall().gettheWall();
        for (std::list<wallpost>::iterator UserWallposts_iter = UserWallposts.begin(); UserWallposts_iter != UserWallposts.end(); UserWallposts_iter++)
        {
            wallpost temp = *UserWallposts_iter;
            
            if (choice == temp.getAuthor())
            {
                //set comment for that wallpost
                wallpostcomment temp2;
                
                //make a comment
                string post;
                cout << endl;
                cout << "****************************** Make a Comment********************************" << endl;
                cout << "Please Enter your message: ";
                cin >> post;
                
                temp2.setCommentPost(post);
                temp2.setAuthor(theUser.getName());
                temp2.setTime();
                
                //add to selected wallpost
                temp.setComment(temp2);
                
                //update user
                cout << endl;
                cout << "Comment Submitted!" << endl;
            }
        }
        
        friendprofile(theUser, Friend);
    }
    
    else if (input == 5)
    {
        //prints out all wallposts and comments of the user
        DefaultWall(Friend, callcount);
        string choice;
        
        cout << endl;
        cout << "************************************************************************" << endl;
        cout << "Please Enter the author of the wallpost you would like to delete." << endl;
        cout << "(Note: You may only delete your own posts)" << endl;
        cout << "User Entry: ";
        cin >> choice;
        
        //if you are the author, you may delete the post
        if (choice == theUser.getName())
        {
            Friend.removeUserwall(choice);
            
            //update user
            cout << endl;
            cout << "Wallpost Deleted." << endl;
        }
        
        //if not, throw an error
        else
        {
            cout << endl;
            cout << "oops! Either you are not" << choice << " or " << choice << " is not a valid user." << endl;
        }
        
        friendprofile(theUser, Friend);
    }
    
    else if (input == 6)
    {
        //prints out all wallposts and comments of the user
        DefaultWall(Friend, callcount);
        string choice;
        
        cout << endl;
        cout << "************************************************************************" << endl;
        cout << "Please Enter the author of the comment you would like to delete." << endl;
        cout << "User Entry: ";
        cin >> choice;
        
        //if your are the author, you may delete the comment
        if (choice == theUser.getName())
        {
            std::list <wallpost> UserWallposts = Friend.getUserwall().gettheWall();
            for (std::list<wallpost>::iterator UserWallposts_iter = UserWallposts.begin(); UserWallposts_iter != UserWallposts.end(); UserWallposts_iter++)
            {
                wallpost temp = *UserWallposts_iter;
                
                std::list <wallpostcomment> ListofComments = temp.getComments();
                for (std::list<wallpostcomment>::iterator ListofComments_iter = ListofComments.begin(); ListofComments_iter != ListofComments.end(); ListofComments_iter++)
                {
                    wallpostcomment temp2 = *ListofComments_iter;
                    
                    if (choice == temp2.getAuthor())
                    {
                        temp.removeComment(choice);
                    }
                }
            }
        }
        
        else
        {
            cout << endl;
            cout << "oops! Either you are not" << choice << " or " << choice << " is not a valid user." << endl;
        }
        
        friendprofile(theUser, Friend);
    }
    
    else if (input == 7)
    {
        loggedinmenu(theUser);
    }
    
    else
    {
        friendprofile(theUser, Friend);
    }
}

//HW11: Degrees of separation by name
int NetworkSearch(string SearchFor, User theUser, string results)
{
    int Degrees = 0;
    bool isUser = false;
    
    list<User> check = theDatabase.getUserDatabase();
    for (list<User>::iterator check_iter = check.begin(); check_iter != check.end(); check_iter++)
    {
        User iUser = *check_iter;
        
        if (SearchFor == iUser.getName())
        {
            isUser = true;
        }
    }
    
    if ((SearchFor != theUser.getName()) && (isUser == true))
    {
        string temp;
        
        list<string> theUserFriends = theUser.FriendsList();
        for (list<string>::iterator iUserFriends_iter = theUserFriends.begin(); iUserFriends_iter != theUserFriends.end(); iUserFriends_iter++)
        {
            string iFriend = *iUserFriends_iter;
            
            if (SearchFor == iFriend)
            {
                results += "You -> ";
                results += iFriend;
                Degrees++;
                
                return Degrees;
            }
        }
        
        Degrees++;
        
        list<string> theUserFriends2 = theUser.FriendsList();
        for (list<string>::iterator iUserFriends_iter2 = theUserFriends2.begin(); iUserFriends_iter2 != theUserFriends2.end(); iUserFriends_iter2++)
        {
            string iFriend = *iUserFriends_iter2;
            
            User iUser = theDatabase.getUser(iFriend);
            list<string> iUserFriends = iUser.FriendsList();
            for (list<string>::iterator iUserFriends_iter = iUserFriends.begin(); iUserFriends_iter != iUserFriends.end(); iUserFriends_iter++)
            {
                string iFriend2 = *iUserFriends_iter;
                
                if (SearchFor == iFriend2)
                {
                    results += "You -> ";
                    results += iFriend;
                    results += " -> ";
                    results += iFriend2;
                    Degrees++;
                    
                    return Degrees;
                }
            }
        }
        
        Degrees++;
        
        list<string> theUserFriends3 = theUser.FriendsList();
        for (list<string>::iterator iUserFriends_iter3 = theUserFriends3.begin(); iUserFriends_iter3 != theUserFriends3.end(); iUserFriends_iter3++)
        {
            string iFriend = *iUserFriends_iter3;
            
            User iUser = theDatabase.getUser(iFriend);
            list<string> iUserFriends = iUser.FriendsList();
            for (list<string>::iterator iUserFriends_iter = iUserFriends.begin(); iUserFriends_iter != iUserFriends.end(); iUserFriends_iter++)
            {
                string iFriend2 = *iUserFriends_iter;
                
                User iUser2 = theDatabase.getUser(iFriend2);
                list<string> iUserFriends = iUser2.FriendsList();
                for (list<string>::iterator iUser2Friends_iter = iUserFriends.begin(); iUser2Friends_iter != iUserFriends.end(); iUser2Friends_iter++)
                {
                    string iFriend3 = *iUser2Friends_iter;
                    
                    if (SearchFor == iFriend3)
                    {
                        results += "You -> ";
                        results += iFriend;
                        results += " -> ";
                        results += iFriend2;
                        results += " -> ";
                        results += iFriend3;
                        Degrees++;
                        
                        return Degrees;
                    }
                }
            }
        }
        
        Degrees++;
        
        list<string> theUserFriends4 = theUser.FriendsList();
        for (list<string>::iterator iUserFriends_iter4 = theUserFriends3.begin(); iUserFriends_iter4 != theUserFriends3.end(); iUserFriends_iter4++)
        {
            string iFriend = *iUserFriends_iter4;
            
            User iUser = theDatabase.getUser(iFriend);
            list<string> iUserFriends = iUser.FriendsList();
            for (list<string>::iterator iUserFriends_iter = iUserFriends.begin(); iUserFriends_iter != iUserFriends.end(); iUserFriends_iter++)
            {
                string iFriend2 = *iUserFriends_iter;
                
                User iUser2 = theDatabase.getUser(iFriend2);
                list<string> iUserFriends = iUser2.FriendsList();
                for (list<string>::iterator iUser2Friends_iter = iUserFriends.begin(); iUser2Friends_iter != iUserFriends.end(); iUser2Friends_iter++)
                {
                    string iFriend3 = *iUser2Friends_iter;
                    
                    User iUser3 = theDatabase.getUser(iFriend3);
                    list<string> iUserFriends = iUser3.FriendsList();
                    for (list<string>::iterator iUser3Friends_iter = iUserFriends.begin(); iUser3Friends_iter != iUserFriends.end(); iUser3Friends_iter++)
                    {
                        string iFriend4 = *iUser3Friends_iter;
                        
                        if (SearchFor == iFriend4)
                        {
                            results += "You -> ";
                            results += iFriend;
                            results += " -> ";
                            results += iFriend2;
                            results += " -> ";
                            results += iFriend3;
                            results += " -> ";
                            results += iFriend4;
                            Degrees++;
                            
                            return Degrees;
                        }
                    }
                }
            }
        }
        
        Degrees++;
        
        list<string> theUserFriends5 = theUser.FriendsList();
        for (list<string>::iterator iUserFriends_iter5 = theUserFriends3.begin(); iUserFriends_iter5 != theUserFriends3.end(); iUserFriends_iter5++)
        {
            string iFriend = *iUserFriends_iter5;
            
            User iUser = theDatabase.getUser(iFriend);
            list<string> iUserFriends = iUser.FriendsList();
            for (list<string>::iterator iUserFriends_iter = iUserFriends.begin(); iUserFriends_iter != iUserFriends.end(); iUserFriends_iter++)
            {
                string iFriend2 = *iUserFriends_iter;
                
                User iUser2 = theDatabase.getUser(iFriend2);
                list<string> iUserFriends = iUser2.FriendsList();
                for (list<string>::iterator iUser2Friends_iter = iUserFriends.begin(); iUser2Friends_iter != iUserFriends.end(); iUser2Friends_iter++)
                {
                    string iFriend3 = *iUser2Friends_iter;
                    
                    User iUser3 = theDatabase.getUser(iFriend3);
                    list<string> iUserFriends = iUser3.FriendsList();
                    for (list<string>::iterator iUser3Friends_iter = iUserFriends.begin(); iUser3Friends_iter != iUserFriends.end(); iUser3Friends_iter++)
                    {
                        string iFriend4 = *iUser3Friends_iter;
                        
                        User iUser3 = theDatabase.getUser(iFriend4);
                        list<string> iUserFriends = iUser3.FriendsList();
                        for (list<string>::iterator iUser3Friends_iter = iUserFriends.begin(); iUser3Friends_iter != iUserFriends.end(); iUser3Friends_iter++)
                        {
                            string iFriend5 = *iUser3Friends_iter;
                            
                            if (SearchFor == iFriend5)
                            {
                                results += "You -> ";
                                results += iFriend;
                                results += " -> ";
                                results += iFriend2;
                                results += " -> ";
                                results += iFriend3;
                                results += " -> ";
                                results += iFriend4;
                                results += " -> ";
                                results += iFriend5;
                                Degrees++;
                                
                                return Degrees;
                            }
                        }
                    }
                }
            }
        }
        
        Degrees++;
        
        cout << endl;
        cout << "Sorry, no user has this person added." << endl;
        return Degrees;
    }
    
    else
    {
        cout << endl;
        cout << "Oops! Search Error. Please try again." << endl;
        
        return Degrees;
    }
    
    return Degrees;
}

int main()
{
    loadDatabase();
    
    return 0;
}








