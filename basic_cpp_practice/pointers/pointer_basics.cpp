/*
    This is a simple code to check for pointers in C++
    Pointers can be of any type given the declaration.
    
    In this code a pointer is defined as auto to 
    take the reference of the type of value being assigned

    *p = &a[0] and *p = a work the same as they store the reference to the array

    In addition to this, pointers can also be used to iterate through an array
    which has been shown in the code here
    
*/
#include<iostream>

int main()
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};

    auto *p = a;
    int search = 6;

    for(*p = 0; *p < int(sizeof(a)/sizeof(a[0])); ++*p )
    {
        if(*p == search)
        {
            std::cout << "Value found \t"<< std::endl; //linear search for an element, takes O(n) time where 'n' is the length of array
        }
        
        
    }
    //to print the last element of an array regardless of the size of array
    std::cout << a[sizeof(a)/(sizeof(a[0])) - 1] << std::endl;
    
    return 0;
}