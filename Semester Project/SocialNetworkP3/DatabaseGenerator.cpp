//
//  DatabaseGenerator.cpp
//  HW8
//
//  Created by Raymond Dam on 11/11/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <ctime>
#include <chrono>
#include <thread>
#include <list>
#include <stdlib.h>

#include "Wall.h"
#include "User.h"
#include "UserList.h"
#include "Sorting.h"
#include "WallpostComment.h"

using namespace std;

//global time: I use this to artifically delay time
//between wallposts/comments to demonstrate sorting
using std::chrono::system_clock;

system_clock::time_point now = system_clock::now();

std::time_t t = system_clock::to_time_t(now);

string tempTime = ctime(&t);

int runtime_time = t;
//**************************************************

int main()
{
    int Usernum, WallpostNum, CommentsNum, FriendsNum;
    
    cout << endl;
    cout << "Enter Number of Users: ";
    cin >> Usernum;
    cout << endl;
    cout << "Enter Number of Wallposts per User: ";
    cin >> WallpostNum;
    cout << endl;
    cout << "Enter Number of Comments per Wallposts: ";
    cin >> CommentsNum;
    cout << endl;
    cout << "Enter Number of Friends per User: ";
    cin >> FriendsNum;
    
    UserList database;
    
    //number of users
    for (int j = 1; j < Usernum+1; j++)
    {
        //converts int to string
        stringstream convert;
        convert << j;
        
        string name = "Batman";
        name += convert.str();
        string pw = "Batster";
        pw += convert.str();
        string Bday = "01/01/1986";
        
        User one;
        one.setName(name);
        one.setPassword(pw);
        one.setBirthday(Bday);
        
        //number of wallposts per user
        for (int i = 1; i < WallpostNum+1; i++)
        {
            wallpost temp;
            
            //converts int to string
            stringstream convert;
            convert << i;
            
            string post = "post";
            post += convert.str();
            string author = "author";
            author += convert.str();
            
            temp.newPost(post);
            temp.newAuthor(author);
            
            //time kill between each wallpost, but its also a time kill IR :(
            //std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(5));
            
            //add five seconds between each wallpost
            int time = runtime_time + 5;
            runtime_time = time;
            stringstream timestream;
            timestream << time;
            string time2 = timestream.str();
            
            temp.newTime(time2);
            temp.newDate(tempTime);
            
            
            //adding comments per wallpost
            for (int k = 1; k < CommentsNum+1; k++)
            {
                wallpostcomment temp2;
                
                //converts int to string
                stringstream convert;
                convert << k;
                
                string comment = "comment";
                comment += convert.str();
                string Cauthor = "Cauthor";
                Cauthor += convert.str();
                
                temp2.setCommentPost(comment);
                temp2.setAuthor(Cauthor);
                
                //time kill between each comment, but its also a time kill IR :(
                //std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(5));
                
                //add five seconds between each wallpost
                int time = runtime_time + 5;
                runtime_time = time;
                stringstream timestream;
                timestream << time;
                string time2 = timestream.str();
                
                temp2.newTime(time2);
                
                temp.setComment(temp2);
            }
            
            one.setUserwall(temp);
        }
        
        //adding friends per user
        for (int i = 1; i < FriendsNum+1; i++)
        {
            stringstream convert;
            convert << i;
            
            string friends = "Batman";
            friends += convert.str();
            
            one.addfriend(friends);
            
            //you can't be your own friend
            if (one.getName() == friends)
            {
                one.unfriend(friends);
            }
        }
        
        database.addUser(one);
    }
    
    database.writeDatabase();
}