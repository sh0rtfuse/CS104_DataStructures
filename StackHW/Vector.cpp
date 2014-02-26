//
//  Vector.cpp
//  HW5
//
//  Created by Raymond Dam on 10/8/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "Vector.h"
#include <sstream>
#include <stdlib.h> //for exit
#include <cassert>  //for assert
#include <string>

//default constructor
Vector::Vector(int size)
{
    arrayptr = new double [size];
}

//copy constructor
Vector::Vector(Vector const &input, int size)
{
    arrayptr = new double [size];
}

//takes in double and creates one demensional vector
Vector::Vector(double input)
{
    //takes input and formats it into a vector of form [input]
    std::string V;
    std::stringstream S;
    
    S << "[" << input << "]";
    
    V = S.str();
}

//takes in string converts into a vector
Vector::Vector(std::string input)
{
    //check for formating
    try
    {
        std::stringstream R(input);
        if (R.get() == '[')
        {
            while(!R.eof())
            {
                if (R.get() == ']')
                {
                    goto here;
                }
            }
            
            //if closing bracket is missing
            throw 1;
        }
        
        //if opening bracket is missing
        throw 1;
    }
    catch (int e)
    {
        std::cout << "Bad Format Error." << std::endl;
        
        //if the format is bad, exit program
        exit(0);
    }

//if the format is ok, code jumps to here
here:
    std::stringstream S(input);
    
    //figures out how big the array needs to be
    dimension = 0;
    
    //this first while loop just figure outs how many dimensions there are
    while (!S.eof())
    {
        //checks for open bracket
        if (S.get() == '[')
        {
            std::string temp;
            std::getline(S, temp, ',');
            dimension++;
        }
        
        //if no open bracket, puts back the character
        else
        {
            S.unget();
        }
        
        //grab the dimension normally
        std::string temp;
        std::getline(S, temp, ',');
        
        //Once we get to the last dimension, remove closing bracket
        if (S.eof())
        {
            std::stringstream S2(temp);
            std::getline(S2, temp, ']');
        }
        
        //iterates the size to dynamically allocate the array
        dimension++;
    }
    
    //intialize dynamic array
    arrayptr = new double [dimension];
    
    //interates the array
    int i = 0;
    
    //reintialize stringstream
    std::stringstream T(input);
    
    //second while loop to store dimensions into array
    while (!T.eof())
    {
        if (T.get() == '[')
        {
            std::string temp;
            std::getline(T, temp, ',');
            
            //convert string to double and store
            double value;
            std::stringstream store(temp);
            store >> value;
            arrayptr[i] = value;
            i++;
        }
        
        else
        {
            T.unget();
        }
        
        std::string temp;
        std::getline(T, temp, ',');
        
        //convert string to double and store
        double value;
        std::stringstream store(temp);
        store >> value;
        arrayptr[i] = value;
        i++;
    
        if (T.eof())
        {
            std::stringstream T2(temp);
            std::getline(T2, temp, ']');
            
            //convert string to double and store
            double value;
            std::stringstream store(temp);
            store >> value;
            arrayptr[i] = value;
            i++;
        }
    }
}

Vector::~Vector()
{
    //memory management
    delete [] arrayptr;
}

Vector Vector::operator+(const Vector &input)
{
    Vector result(dimension);
    result.dimension = dimension;
    
    try
    {
        if (dimension == input.dimension)
        {
            for (int i = 0; i < dimension; i++)
            {
                result.arrayptr[i] = arrayptr[i] + input.arrayptr[i];
            }
        }
        
        else
        {
            throw 1;
        }
    }
    catch (int e)
    {
        std::cout << "Vector Dimension Error." << std::endl;
        
        exit(0);
    }
    
    return result;
}

Vector Vector::operator-(Vector const &input)
{
    Vector result(dimension);
    result.dimension = dimension;
    
    try
    {
        if (dimension == input.dimension)
        {
            for (int i = 0; i < dimension; i++)
            {
                result.arrayptr[i] = arrayptr[i] - input.arrayptr[i];
            }
        }
        
        else
        {
            throw 1;
        }
    }
    catch (int e)
    {
        std::cout << "Vector Dimension Error." << std::endl;
        
        exit(0);
    }
    
    return result;
}

Vector Vector::operator*(Vector const &input)
{
    Vector result(dimension);
    result.dimension = dimension;
    
    try
    {
        if (dimension == input.dimension)
        {
            for (int i = 0; i < dimension; i++)
            {
                result.arrayptr[i] = arrayptr[i] * input.arrayptr[i];
            }
        }
        
        else
        {
            throw 1;
        }
    }
    catch (int e)
    {
        std::cout << "Vector Dimension Error." << std::endl;
        
        exit(0);
    }
    
    return result;
}

Vector & Vector::operator=(Vector const &input)
{
    try
    {
        if (dimension == input.dimension)
        {
            for (int i = 0; i < dimension; i++)
            {
                input.arrayptr[i] = arrayptr[i];
            }
        }
        
        else
        {
            throw 1;
        }
    }
    catch (int e)
    {
        std::cout << "Vector Dimension Error." << std::endl;
        
        exit(0);
    }
    
    return *this;
}

bool Vector::operator==(const Vector &input)
{
    //keeps track of the matching components of the vector
    int matches = 0;
    
    for (int i = 0; i < dimension; i++)
    {
        if (arrayptr[i] == input.arrayptr[i])
        {
            matches++;
        }
    }

    if (dimension == matches)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

bool Vector::operator!=(const Vector &input)
{
    //keeps track of the matching components of the vector
    int matches = 0;
    
    for (int i = 0; i < dimension; i++)
    {
        if (arrayptr[i] == input.arrayptr[i])
        {
            matches++;
        }
    }
    
    if (dimension != matches)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

double Vector::operator[](const int index)
{
    assert(index >= 0 && index < dimension);
    
    return this->arrayptr[index];
}

std::string Vector::tostring()
{
    std::string temp;
    
    std::stringstream stream(temp);
    
    stream << "[";
    
    for (int i = 0; i < dimension; i++)
    {
        stream << arrayptr[i];
        
        //no comma on the last dimension
        if (i != dimension-1)
        {
            stream.put(',');
        }
    }
    
    stream << "]";
    
    std::string output = stream.str();
    
    return output;
}





