//
//  Q5.cpp
//  HW10
//
//  Created by Raymond Dam on 11/28/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* Methodology
 I attempted to maintain targeted runtime by keeping all the
 data on one array so I would only have to search the array once.
 To differentiate between the turkey and side dishes, I used some 
 simply arithmetic to find the appropriate index.
*/

void fileio()
{
    string filename;
    int *Dinnerptr;
    int n,m,C;
    int index = 0;
    int size = 0;
    
    cout << endl;
    cout << "Please enter the name of your file." << endl;
    cout << "User Entry: ";
    cin >> filename;
    
    ifstream filein;
    filein.open(filename);
    
    //grab n number of turkey pieces
    string nTurkey;
    getline(filein, nTurkey, ' ');
    n = atoi(nTurkey.c_str());
    
    //grab m number of side dishes
    string mSide;
    getline(filein, mSide, ' ');
    m = atoi(mSide.c_str());
    
    //grab C target calories
    string target_cal;
    getline(filein, target_cal);
    C = atoi(target_cal.c_str());
    
    size = n + m;
    
    //declare storage
    Dinnerptr = new int[size];
    
    //grab dinner
    while (!filein.eof())
    {
        string line;
        getline(filein, line);
        int num = atoi(line.c_str());
        
        Dinnerptr[index] = num;
        index++;
    }
    
    //main processing loop
    for (int nTurkey = 0; nTurkey < size; nTurkey++)
    {
        int mSide = n;
        
        while (mSide < size)
        {
            int Calories = Dinnerptr[nTurkey] + Dinnerptr[mSide];
            
            if (C == Calories)
            {
                cout << Calories << " = " << Dinnerptr[nTurkey] << " + " << Dinnerptr[mSide] << endl;
            }
            
            mSide++;
        }
    }
}

int main()
{
    fileio();
    
    return 0;
}


