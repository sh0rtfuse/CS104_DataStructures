//
//  Vector.h
//  HW5
//
//  Created by Raymond Dam on 10/8/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vector
{
    public:
        Vector (int size);
        Vector (Vector const &input, int size);
        Vector (double input);
        Vector (std::string input);
        ~Vector ();
    
        Vector operator+(Vector const &input);
        Vector operator-(Vector const &input);
        Vector operator*(Vector const &input);
    
        Vector & operator=(Vector const &input);
        bool operator==(Vector const &input);
        bool operator!=(Vector const &input);
        double operator[](const int index);
    
        std::string tostring();
    
    private:
        double *arrayptr;
        int dimension;
};

#endif

/*
 Operator Overloading notes:
 - Complex(double real, double img): Real(real), Img(img)
    - Diiferent way of initializing variables
 
 - Complex & operator+(Complex const & rhs);
    - function prototype of operator overloading
    - This is will pass reference to the object
 
 - Copy Constructor: defines how you would copy
    Complex (Complex const & other)
    {
        Img = other.Img;
        Real = other.Real;
    }
 
 - Exceptions
    if (index > 1)
    {
        throw std::out_of_range("index has to be less than 2");
    }
 
    keywords: throw, try, catch 
 
    now you can write the logic that recovers from such an error w/o/ crashing
 
    try
    {
        std::cout << a[i];
    }
 
    catch (std:: exception & ex)
    {
        std::cout << "Error: Bad Input!" << ex. what() << std::endl;
    }
 
    ** You can put the whole thing inside a while loop to a bool to see if program will crash
    ** Don't catch other types beside exception and out_of_range
*/
