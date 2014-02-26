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
#include <cstddef>

#include "Wall.h"
#include "User.h"
#include "UserList.h"
#include "Sorting.h"
#include "WallpostComment.h"
#include "md5.h"

using namespace std;

//global time: I use this to artifically delay time
//between wallposts/comments to demonstrate sorting
using std::chrono::system_clock;

system_clock::time_point now = system_clock::now();

std::time_t t = system_clock::to_time_t(now);

string tempTime = ctime(&t);

std::size_t iter = tempTime.find_last_of(" ");

string subtempTime = tempTime.substr(0, iter);

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
        
        string username = "Batman";
        username += convert.str();
        string name = "Bruce_Wayne";
        name += convert.str();
        string pw = "Batster";
        pw += convert.str();
        string Bday = "01/01/1986";
        
        //HW11: Hash passwords
        auto hash = md5(pw.c_str(), pw.size() * sizeof(char));
        
        stringstream key;
        key << hash;
        
        string pw_hash = key.str();
        
        User one;
        one.setUsername(username);
        one.setName(name);
        one.setPassword(pw_hash);
        one.setBirthday(Bday);
        
        //number of wallposts per user
        for (int i = 1; i < WallpostNum+1; i++)
        {
            wallpost temp;
            
            //converts int to string
            stringstream convert2;
            convert2 << i;
            
            string post = "post";
            post += convert2.str();
            string author = "author";
            author += convert2.str();
            
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
            temp.newDate(subtempTime);
            
            
            //adding comments per wallpost
            for (int k = 1; k < CommentsNum+1; k++)
            {
                wallpostcomment temp2;
                
                //converts int to string
                stringstream convert3;
                convert3 << k;
                
                string comment = "comment";
                comment += convert3.str();
                string Cauthor = "Cauthor";
                Cauthor += convert3.str();
                
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
        srand(time(NULL));
        int tracker[FriendsNum];
        for (int r = 0; r < FriendsNum; r++)
        {
            tracker[r] = 0;
        }
        
        for (int m = 0; m < FriendsNum; m++)
        {
            int num = rand() % Usernum + 1;
            bool isNew = false;
            int unique = 0;
            
            for (int r = 0; r < FriendsNum; r++)
            {
                if (num != tracker[r])
                {
                    unique++;
                }
            }
            
            if (unique > 0)
            {
                isNew = true;
                tracker[m] = num;
            }
            
            if ((num != j) && (isNew == true))
            {
                //converts int to string
                stringstream convert3;
                convert3 << num;
                
                string friends = "Bruce_Wayne";
                friends += convert3.str();
                
                one.addfriend(friends);
                
                //you can't be your own friend
                if (one.getName() == friends)
                {
                    one.unfriend(friends);
                }
            }
        }
        
        database.addUser(one);
    }
    
    database.writeDatabase();
}
