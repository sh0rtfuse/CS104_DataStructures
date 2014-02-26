//
//  main2.cpp
//  HW5
//
//  Created by Raymond Dam on 10/15/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Stack.h"
#include "Vector.h"

using namespace std;

int main ()
{
    Vector A("[34.4322,232.33312,3.14159]");
    
    Vector B("[23,23,21]");
    
    Vector C = A + B;
    
    cout << endl;
    cout << "Answer: ";
    cout << C.tostring() << endl;
    cout << endl;
    
    return 0;
}
