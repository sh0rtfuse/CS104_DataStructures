//
//  Q4.cpp
//  HW7
//
//  Created by Raymond Dam on 11/1/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include <iostream>
#include "PQueue.h"
#include <stdlib.h> //ONLY FOR RAND AND SRAND
#include <time.h>
#include <ctime>

using namespace std;

void Q4a()
{
    for (int d = 2; d <= 100; d++)
    {
        const int ITERATE = 1000;
        clock_t start, finish;
        double  dur;
        
        start  = clock();
            PQueue<int> Heap(2, false);
            srand(time(NULL));
        
            for (int i = 0; i < 10000; i++)
            {
                int random = rand() % 1000000 + 0;
            
                Heap.add(random);
            }
        finish = clock();
        
        dur = (double)(finish - start);
        dur /= (CLOCKS_PER_SEC * ITERATE);
        cout << "Elapsed seconds: "
        << scientific << dur << endl;
    }
}

void Q4b()
{
    for (int d = 2; d <= 100; d++)
    {
        const int ITERATE = 1000;
        clock_t start, finish;
        double  dur;
        
        PQueue<int> Heap(2, false);
        srand(time(NULL));
        
        for (int i = 0; i < 10000; i++)
        {
            int random = rand() % 1000000 + 0;
            
            Heap.add(random);
        }
        
        start  = clock();
            for (int i = 0; i < 10000; i++)
            {
                Heap.remove();
            }
        finish = clock();
        
        dur = (double)(finish - start);
        dur /= (CLOCKS_PER_SEC * ITERATE);
        cout << "Elapsed seconds: "
        << scientific << dur << endl;
    }
}

int main()
{
    int input = 0;
    
    cout << "Type 1 for 4a and 2 for 4b" << endl;
    cout << "User entry: ";
    cin >> input;
    
    if (input == 1)
    {
        Q4a();
    }
    
    else if (input == 2)
    {
        Q4b();
    }
    
    return 0;
}
