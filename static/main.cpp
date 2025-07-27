#include <iostream>

int globalVar = 17; // static 
// global objects are static variables, even without the static keyword.

namespace myConstants
{
    constexpr double PI = 3.14159265; // static
}
// object defined on a namespace scope is also static.

int& counter()
{
    static int count = 0; // static
    ++count;
    return count;
}
// static variables inside functions are local static variables.


int main()
{
    int tempInt = 42; // stack allocated, not static
    counter();
    std::cout << "globalVar: " << globalVar << "\n";
    std::cout << "myConstants::PI: " << myConstants::PI << "\n";
    std::cout << "tempInt: " << tempInt << "\n";
    std::cout << "counter():"  << counter() << "\n";

}


/*

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

*/
