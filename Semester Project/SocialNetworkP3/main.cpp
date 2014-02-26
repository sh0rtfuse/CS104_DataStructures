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

using namespace std;

//prototypes
void welcomescreen();
void login();
void newuser();
void loggedinmenu(User theUser);

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
    User input = theDatabase.getUser(user);
    
    //search for name
    if (input.getName() == user)
    {
        string password;
        
        cout << endl;
        cout << "Please enter your password, then press enter." << endl;
        cout << "User Entry: ";
        
        cin >> password;
        
        //password validation
        User theUser = theDatabase.getUser(user);
        
        if (theUser.getPassword() == password)
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
    loggedinmenu(newUser);
}

//Show Wall
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
        string temp = printWallpost.getAuthor();
        
        if (!temp.empty())
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
            string temp2 = printComment.getAuthor();
            
            if (!temp2.empty())
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
            string temp = SortedWallpost.getAuthor();
            
            if (!temp.empty())
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
            string temp = SortedWallpost.getAuthor();
            
            //if wallpost is in the right order, than printout
            if (SortedWallpost.getOrder() == order)
            {
                if (!temp.empty())
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
                string temp2 = printComment.getAuthor();
                
                if (printComment.getOrder() == order)
                {
                    if (!temp2.empty())
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
        cout << "6. Log Out." << endl;
        cout << "User Entry: ";
        
        cin >> input;
    }
    while ((input != 0) && (input != 1) && (input != 2) && (input != 3) && (input != 4) && (input != 5) && (input != 6));
    
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
                    string you = theUser.getName();
                    
                    Userwall(yourFriend, you);
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
        string searchquery;
        cout << endl;
        cout << "Please Enter a name to search for users in the network." << endl;
        cout << "User Entry: ";
        cin >> searchquery;
        
        //perform search
        string results = theDatabase.DatabaseSearch(searchquery);
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
                cout << "You are no longer friends with " << remove << "returning to menu..." << endl;
            }
        }
        
        //update user
        cout << endl;
        cout << "Sorry, the person you entered is not registered or not your friend..." << endl;
        loggedinmenu(theUser);
    }
    
    else if (input == 6)
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

int main()
{
    loadDatabase();
    
    return 0;
}









