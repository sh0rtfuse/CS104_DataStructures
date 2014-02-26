//
//  Q4.cpp
//  HW9
//
//  Created by Raymond Dam on 11/20/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* Methodology
 My algorithm stores everything to a dynamic array (since I need
 quick access), and finds the sum by checking each subsequent number
 after the base, which is determined by interating through each element
 in the array.
*/

void fileio()
{
    string filename;
    int *arrayptr;
    int n,t;
    int index = 0;
    
    cout << endl;
    cout << "Please enter the name of your file." << endl;
    cout << "User Entry: ";
    cin >> filename;
    
    ifstream filein;
    filein.open(filename);
    
    //grab n number of lines
    string nlines;
    getline(filein, nlines, ' ');
    n = atoi(nlines.c_str());
    
    //grab t target integer
    string t_target;
    getline(filein, t_target);
    t = atoi(t_target.c_str());
    
    //declare a dynamic array to store integers
    arrayptr = new int [n];
    
    //grab rest of the list
    while (!filein.eof())
    {
        string line;
        getline(filein, line);
        int num = atoi(line.c_str());
        
        arrayptr[index] = num;
        index++;
    }
    
    //main processing loop
    for (int i = 0; i < n; i++)
    {
        //tracks the subsequent numbers to check
        int subindex = i + 1;
        
        //grab base number
        int base = arrayptr[i];
        
        //adding every subsequent number to base number to check for target
        while (subindex < n)
        {
            int sum;
            sum = base + arrayptr[subindex];
            
            //if the sum is equal the target, print result
            if (sum == t)
            {
                cout << t << " = " << base << " + " << arrayptr[subindex] << endl;
            }
            
            //increment
            subindex++;
        }
    }
}


int main()
{
    fileio();
    
    return 0;
}








