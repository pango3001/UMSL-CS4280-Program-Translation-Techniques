// Name:    Jesse McCarville-Schueths
// Course:  4280
// Date:    Feb 7, 2021
// Project: P0
// File:    main.cpp

#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char** argv) {
    
    // Pointer to an integer
    int* p;

    // Pointer to an array of 5 integers
    int(*ptr)[5];
    int arr[5];

    // Points to 0th element of the arr.
    p = arr;

    // Points to the whole array arr.
    ptr = &arr;

    std::cout << "p =" << p << ", ptr = " << ptr << std::endl;
    p++;
    ptr++;
    std::cout << "p =" << p << ", ptr = " << ptr << std::endl;
    

    return 0;
}
