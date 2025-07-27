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

A static object is one that exists from the time it’s constructed until the
end of the program. 
Excluded:
    * Stack allocated objects.
    * Heap allocated objects.
Included:
    * global objects.
    * objects defined at namespace scope.
    * objects declared static inside classe.
    * objects declared static inside functions.
    * objects declared static at file scope.
Static objects inside functions are known as local static
objects (because they’re local to a function), and the other
kinds of static objects are known as non-local static objects. 
Static objects are destroyed when the program exits,
i.e., their destructors are called when main finishes executing.

A translation unit is the source code giving rise to a single object file.
It’s basically a single source file, plus all of its #include files.

In C++, the initialization order of non-local static objects across different translation units (.cpp files)
is undefined. This means that if one static object uses another from a different translation unit
during its initialization, it might access it before it's been constructed*— resulting in undefined behavior.

Best practice:
Avoid global static variables when possible. Instead, use functions that return references to
local static objects (a common Singleton pattern implementation). This defers initialization
until first use and ensures the object is initialized safely and predictably.

*/