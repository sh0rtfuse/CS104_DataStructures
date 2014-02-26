//
//  main.cpp
//  HW2_LinkedLists
//
//  Raymond Dam
//

#include <iostream>

using namespace std;

//global variables
int counter = 0;

//helps recursive function by figuring out which path the ant should take next
void recursionhelper (int D20 [3][20], int trace [21], int &traceindex, int &currentnum, int &prevnum, int &nextnum, int &energy)
{
    //the energy used to go the next die face
    int path1, path2;
    
    //besides the number you were just at, there are 2 faces the ant could go to
    int nextstep [2] = {0};
    int index = 0;
    
    //searches for those 2 and stores them both as options
    for (int i = 0; i < 3; i++)
    {
        //ignore the face you were just at
        if (D20 [i][currentnum-1] != prevnum)
        {
            //ignore the previously visited faces
            for (int j = 0; j < traceindex; j++)
            {
                if (trace[j] != currentnum)
                {
                    nextstep [index] = D20 [i][currentnum-1];
                    
                    index++;
                }
            }
        }
    }
    
    //sets the currentnum to the next number for the next function call
    prevnum = currentnum;
    
    //calculates energy used for both paths
    path1 = abs(currentnum-nextstep[0]);
    path2 = abs(currentnum-nextstep[1]);
    
    //the program will pick the path utilizing the least energy and pass back the next face and energy used
    if (path1 > path2)
    {
        nextnum = nextstep[1];
        energy = path2;
        
        //keep track of the value you just passed
        trace[traceindex] = nextnum;
        traceindex++;
    }
    
    else if (path1 < path2)
    {
        nextnum = nextstep[0];
        energy = path1;
        
        //keep track of the value you just passed
        trace[traceindex] = nextnum;
        traceindex++;
    }
}

//recursive function that will find the optimal energy in traversing the die
int recursion (int D20 [3][20], int sum, int step, int startx, int starty, int nextnum, int prevnum, int trace [21], int traceindex)
{
    if (step == 0)
    {
        counter++;
        
        return sum;
    }
    
    else
    {
        int currentnum;
        
        if (step == 19)
        {
            currentnum = D20 [startx][starty];
        }
        
        else
        {
            currentnum = nextnum;
        }
        
        int nextnum = 0;
        int energy = 0;
        
        recursionhelper(D20, trace, traceindex, currentnum, prevnum, nextnum, energy);
        
        counter++;
        
        return recursion(D20, sum += energy, step-1, startx, starty, nextnum, prevnum, trace, traceindex);
    }
}

int main()
{
    //Hardcoded Die Information:
    //Index of the array (0 to 19) is the number the ant is currently on 
    //Each column of the array (0 to 2) contains the adjacent numbers to the number the ant is on
    int D20 [3][20] =
    {
        {10, 3, 2, 5, 4, 1, 2, 2, 3, 1, 3, 13, 1, 15, 5, 11, 10, 12, 9, 7},
        {6, 7, 9, 8, 7, 8, 5, 4, 6, 4, 16, 17, 12, 18, 14, 18, 12, 14, 13, 11},
        {13, 8, 11, 10, 15, 9, 20, 6, 19, 17, 20, 18, 19, 20, 17, 19, 15, 16, 16, 14}
    };
    
    int sum1 = 0, sum2 = 0, sum3 = 0;
    
    int nextnum = 0, prevsum = 1, trace [21], traceindex = 1;
    
    
    //we run this 3 times because from 1, the ant has 3 different side it could take and 2 subsequent sides after
    sum1 = recursion(D20, sum1, 19, 0, 0, nextnum, prevsum, trace, traceindex);
    
    sum2 = recursion(D20, sum2, 19, 0, 1, nextnum, prevsum, trace, traceindex);
    
    sum3 = recursion(D20, sum3, 19, 0, 2, nextnum, prevsum, trace, traceindex);
    
    cout << endl;
    cout << sum1 << endl;
    cout << sum2 << endl;
    cout << sum3 << endl;
    
    cout << endl;
    cout << "Counter Order: " << counter << endl;
    
    return 0;
}

