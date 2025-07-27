#include "Directory_safe.h"
#include <iostream>

int main()
{
    std::cout << "Main started.\n";
    tempDir(); // creates a directory
    return 0;
}

/*
Singleton pattern helps us out of this conundrum.
When we replace non-local static objects (such as tfs and tempDir before) with local static objects 
inside a function that returns a reference to such object, these are guaranteed to be constructed once
and when the function call happens, it is even thread safe.

Solution; Replace direct accesses to non-local static objects 
with calls to functions that return references to local
static objects, you’re guaranteed that the references you get back will
refer to initialized objects.
*/